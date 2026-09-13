"""Reproduce SlalomDouble's early commutative-operand ordering divergence."""

import argparse
import json
from pathlib import Path
from trace import c2, m, replay, trace

ROOT = Path(m.__file__).resolve().parents[2]
SCRATCH = ROOT / "tools/match/scratches/initialize_slalomdouble_path_template_pair"


def departure_control(source):
    begin = source.index(
        "        ((PathTemplateSample *)((char *)primary_samples + departure_sample_offset))",
        source.index("    int departure_index"),
    )
    end = source.index("        departure_sample_offset +=", begin)
    body = source[begin:end]
    helper_body = (
        body.replace("primary_samples", "primary")
        .replace("secondary_samples", "secondary")
        .replace("departure_sample_offset", "offset")
        .replace("departure_index", "index")
    )
    helper = (
        "static __forceinline void initialize_departure_pair(int offset, int index, PathTemplateSample *&primary, PathTemplateSample *&secondary)\n{\n"
        + helper_body
        + "}\n\n"
    )
    changed = (
        source[:begin]
        + "        initialize_departure_pair(departure_sample_offset, departure_index, primary_samples, secondary_samples);\n"
        + source[end:]
    )
    where = changed.index("void cRPath::initialize_slalomdouble_path_template_pair")
    return changed[:where] + helper + changed[where:]


def receivers(event):
    nodes = event["nodes"]
    calls = [i for i, node in enumerate(nodes) if node["op"] == 0x184][:5]
    assert len(calls) == 5
    rows = []
    for i in calls[1:]:
        add, copy, call = nodes[i - 2 : i + 1]
        assert add["op"] == 0x16D and copy["op"] == 0x15A
        # Follow the actual ADD result through the receiver COPY to the CALL.
        assert add["dst"][0]["raw"][6] == copy["src"][0]["raw"][6]
        assert copy["dst"][0]["raw"][6] == call["src"][1]["raw"][6]
        rows.append(
            {
                "add_node": add["id"],
                "call_node": call["id"],
                "line_raw": call["line"],
                "source_kinds": [op["kind"] for op in add["src"]],
                "cost_words": [op["raw"][3] for op in add["src"]],
                "raw_add": add,
                "raw_copy": copy,
                "raw_call": call,
            }
        )
    return rows


def guard_controls(source, root):
    scratch = root / "guard-source"
    scratch.mkdir()
    (scratch / "scratch.cpp").write_text(source)
    conf = (SCRATCH / "scratch.conf").read_text()
    (scratch / "scratch.conf").write_text(conf + "COMPILER=msvc6.0\n")
    try:
        trace(scratch, root / "wrong-compiler")
    except ValueError as exc:
        assert str(exc) == "Only the pinned msvc6.5 profile is supported"
        assert not (root / "wrong-compiler").exists()
    else:
        raise AssertionError("Wrong compiler accepted")
    (scratch / "scratch.conf").write_text(conf)
    loader = c2.load_profile
    profile = loader()
    profile = {**profile, "hooks": [dict(hook) for hook in profile["hooks"]]}
    profile["hooks"][0]["target"] += 1
    c2.load_profile = lambda: profile
    try:
        trace(scratch, root / "wrong-hook", passes_only=True)
    except RuntimeError as exc:
        assert "Command failed (95)" in str(exc), str(exc)
        assert not (root / "wrong-hook/manifest.json").exists()
        assert not (root / "wrong-hook/observed/replay.obj").exists()
    else:
        raise AssertionError("Wrong hook accepted")
    finally:
        c2.load_profile = loader
    return {"wrong_compiler_rejected": True, "wrong_call_destination_rejected": True}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--out", required=True, type=Path)
    args = parser.parse_args()
    args.out.mkdir(parents=True, exist_ok=False)
    source = (SCRATCH / "scratch.cpp").read_text()
    control = departure_control(source)
    runs = []
    for name, text in [("canonical", source), ("departure", control)]:
        scratch = args.out / (name + "-source")
        scratch.mkdir()
        (scratch / "scratch.cpp").write_text(text)
        (scratch / "scratch.conf").write_bytes((SCRATCH / "scratch.conf").read_bytes())
        for early in (False, True):
            out = args.out / (name + ("-early" if early else "-passes"))
            receipt, snapshots = trace(
                scratch, out, passes_only=True, early_addresses=early
            )
            assert receipt["metrics"]["candidate_instructions"] == 683
            assert receipt["metrics"]["target_instructions"] == 683
            assert receipt["metrics"]["prefix_instructions"] == (
                84 if name == "canonical" else 42
            )
            assert receipt["metrics"]["references_ok"] == 45
            assert receipt["metrics"]["reference_problems"] == 0
            assert not receipt["metrics"]["body_byte_exact"]
            row = {"name": name, "early": early, "receipt": receipt}
            if early:
                before, after = receivers(snapshots[4]), receivers(snapshots[5])
                assert snapshots[4]["target_rva"] == 0xFC45
                assert snapshots[5]["target_rva"] == 0xFCDA
                assert [r["source_kinds"] for r in before] == [[6, 2, 2]] * 4
                expected = [[6, 2, 2]] * 4
                expected[1 if name == "canonical" else 3] = [2, 6, 2]
                assert [r["source_kinds"] for r in after] == expected
                assert [r["call_node"] for r in before] == [
                    r["call_node"] for r in after
                ]
                row.update(before=before, after=after)
            runs.append(row)
            print(name, "early" if early else "passes", "preserved", flush=True)
    # An independent repeat tests comparison stability despite arena relocation.
    receipt, repeated = trace(
        args.out / "canonical-source", args.out / "repeat", passes_only=True
    )
    original = c2.read_verified(args.out / "canonical-passes")
    comparison = c2.compare(original, repeated)
    assert comparison["first_shape_difference"] is None
    result = {
        "schema_version": 1,
        "harness_sha256": replay.sha(Path(__file__).read_bytes()),
        "scope": "Compiler diagnostics only; no native match credit or compiler decision patches.",
        "runs": runs,
        "repeat_receipt": receipt,
        "repeat_comparison": comparison,
        "guard_controls": guard_controls(source, args.out),
    }
    (args.out / "results.json").write_text(json.dumps(result, indent=2) + "\n")


if __name__ == "__main__":
    main()
