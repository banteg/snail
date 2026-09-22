"""Reproduce the heightmap coordinate assignment's survival through C2+0x11afa."""

import argparse
import copy
import hashlib
import json
import sys
from pathlib import Path

MATCH_ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(MATCH_ROOT))
from replay_four_builder_controls_20260912 import reconstruct

RECEIPT = MATCH_ROOT / "heightmap-coordinates-20260922.json"
HOOKS = ((0x1315A, 0x11AFA), (0x13172, 0x789C), (0x13179, 0x6BD0), (0x13189, 0x11209))


def identity(operand):
    assert operand["kind"] in (1, 2)
    return operand["kind"], operand["raw"][6 if operand["kind"] == 1 else 5]


def signature(event, column_line, row_line):
    nodes = event["nodes"]
    (column,) = [n for n in nodes if n["op"] == 0x16F and n["line"] == column_line]
    (row,) = [n for n in nodes if n["op"] == 0x16F and n["line"] == row_line]
    assert all(op["raw"][2] >> 28 == 4 for op in column["src"])
    assert all(op["raw"][2] >> 28 == 1 for op in row["src"])
    (conversion,) = [
        n
        for n in nodes
        if n["op"] == 0x15F
        and len(n["src"]) == 1
        and n["src"][0]["kind"] in (1, 2)
        and identity(n["src"][0]) == identity(column["dst"][0])
    ]
    assert conversion["dst"][0]["raw"][2] >> 28 == 1

    def copied_value(node):
        value = identity(node["dst"][0])
        copies = [
            n
            for n in nodes
            if n["op"] == 0x15B
            and len(n["src"]) == 1
            and n["src"][0]["kind"] in (1, 2)
            and identity(n["src"][0]) == value
        ]
        assert len(copies) <= 1
        return identity(copies[0]["dst"][0]) if copies else value, bool(copies)

    column_value, column_copy = copied_value(conversion)
    row_value, row_copy = copied_value(row)
    (addition,) = [
        n
        for n in nodes
        if n["op"] == 0x16D
        and len(n["src"]) == 2
        and all(op["kind"] in (1, 2) for op in n["src"])
        and {identity(op) for op in n["src"]} == {column_value, row_value}
    ]
    assert nodes.index(column) < nodes.index(conversion) < nodes.index(addition)
    assert nodes.index(row) < nodes.index(addition)
    return {
        "column_before_row": nodes.index(conversion) < nodes.index(row),
        "column_assignment_survives": column_copy,
        "row_assignment_survives": row_copy,
        "both_results_feed_pixel_sum": True,
    }


def validate(observation):
    manifest = observation["manifest"]
    assert manifest["whole_coff_equal_except_timestamp"]
    assert manifest["missing_stream_rejected"]
    assert manifest["compiler_decisions_modified"] is False
    assert (
        hashlib.sha256(observation["source"].encode()).hexdigest()
        == manifest["source_sha256"]
    )
    result = []
    for boundary, event in zip(("entry", "return"), observation["events"], strict=True):
        assert event["target_rva"] == 0x11AFA and event["boundary"] == boundary
        result.append(
            signature(event, observation["column_line"], observation["row_line"])
        )
    assert result == observation["expected"]
    return result


def reproduce(source, config, out):
    import trace

    scratch = out.parent / (out.name + "-input")
    scratch.mkdir(parents=True)
    (scratch / "scratch.cpp").write_text(source)
    (scratch / "scratch.conf").write_text(config)
    loader = trace.c2.load_profile
    profile = loader()
    profile = {
        **profile,
        "name": profile["name"] + "-height-first-reorder",
        "hooks": [
            {"site": site, "target": target, "return": True} for site, target in HOOKS
        ],
    }
    trace.c2.load_profile = lambda: profile
    try:
        return trace.trace(scratch, out)
    finally:
        trace.c2.load_profile = loader


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--out", type=Path, help="Repeat both preserving traces in a new directory"
    )
    args = parser.parse_args()
    receipt = json.loads(RECEIPT.read_text())
    observations = receipt["compiler_observations"]
    for name, observation in observations.items():
        result = validate(observation)
        control = receipt["controls"][observation["control_index"]]
        baseline = receipt["baselines"][control["function"]]["source"]
        assert reconstruct(baseline, control) == observation["source"]
        status = control["measured"]
        assert observation["manifest"]["metrics"] == {
            "ratio": status["match_ratio"],
            "target_instructions": status["target_instructions"],
            "candidate_instructions": status["candidate_instructions"],
            "prefix_instructions": status["prefix_instructions"],
            "references_ok": status["references"]["ok"],
            "reference_problems": 0,
            "exact": False,
            "body_byte_exact": False,
        }
        for corruption in ("source", "expression", "claim"):
            bad = copy.deepcopy(observation)
            if corruption == "source":
                bad["source"] += "\n"
            elif corruption == "claim":
                bad["expected"][1]["column_before_row"] ^= True
            else:
                (column,) = [
                    n
                    for n in bad["events"][1]["nodes"]
                    if n["op"] == 0x16F and n["line"] == bad["column_line"]
                ]
                column["dst"][0]["raw"][6] ^= 1
            try:
                validate(bad)
            except (AssertionError, ValueError):
                pass
            else:
                raise AssertionError(f"Accepted corrupt {name}/{corruption}")
        if args.out:
            manifest, events = reproduce(
                observation["source"], receipt["config"], args.out / name
            )
            fresh = {**observation, "manifest": manifest, "events": events[:2]}
            assert validate(fresh) == result
            assert manifest["metrics"] == observation["manifest"]["metrics"]
        print(name, json.dumps(result, sort_keys=True))


if __name__ == "__main__":
    main()
