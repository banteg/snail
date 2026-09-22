"""Check or recompile the frozen, byte-neutral Path.o context controls."""

import argparse
import copy
import dataclasses
import hashlib
import json
import re
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
RECEIPT = Path(__file__).with_name("path-context-20260922.json")
METRICS = (
    "state",
    "body_byte_exact",
    "match_ratio",
    "target_instructions",
    "candidate_instructions",
    "prefix_instructions",
    "references",
    "compiler",
    "cflags",
    "error",
)


def sha(data):
    return hashlib.sha256(data).hexdigest()


def source_for(receipt, control):
    sources = receipt["sources"]
    if control["label"] == "canonical":
        return sources[control["function"]]["source"]
    parts = []
    for name in control["members"]:
        source = sources[name]["source"]
        helpers = re.findall(
            r"^static (?:__forceinline |inline )?[\w *&]+? (\w+)\(",
            source,
            re.MULTILINE,
        )
        for helper in helpers:
            source = re.sub(r"\b" + helper + r"\b", name + "_" + helper, source)
        parts.append(source)
    source = "\n\n".join(parts)
    # These identical XYZ definitions are the only duplicate free operator.
    pattern = (
        r"inline Vector3 operator\*\(float (\w+), const Vector3& (\w+)\)\s*"
        r"\{\s*return Vector3\(\1 \* \2.x, \1 \* \2.y, \1 \* \2.z\);\s*\}"
    )
    for hit in reversed(list(re.finditer(pattern, source))[1:]):
        source = source[: hit.start()] + source[hit.end() :]
    return source


def verify(receipt):
    for source in receipt["sources"].values():
        assert sha(source["source"].encode()) == source["sha256"]
    members = receipt["member_order"]
    assert len(set(members)) == len(members) == 43
    assert set(members) == set(receipt["sources"])
    functions = receipt["functions"]
    assert len(receipt["controls"]) == 4 * len(functions) == 16
    for name in functions:
        controls = [c for c in receipt["controls"] if c["function"] == name]
        by_label = {c["label"]: c for c in controls}
        assert set(by_label) == {
            "canonical",
            "renamed_isolated",
            "native_predecessor",
            "source_object",
        }
        canonical = by_label["canonical"]
        index = members.index(name)
        assert (
            by_label["native_predecessor"]["members"] == members[index - 1 : index + 1]
        )
        assert by_label["source_object"]["members"] == members
        for control in controls:
            if control["label"] in ("canonical", "renamed_isolated"):
                assert control["members"] == [name]
            assert (
                sha(source_for(receipt, control).encode()) == control["source_sha256"]
            )
            assert control["data"] == canonical["data"]
            assert control["measured"] == canonical["measured"]
            assert control["measured"]["error"] is None
            assert control["measured"]["body_byte_exact"] is False
            assert control["measured"]["references"] == {
                "ok": functions[name]["references"],
                "unresolved": 0,
                "mismatch": 0,
                "unaudited": 0,
            }
            assert len(bytes.fromhex(control["data"])) == functions[name]["bytes"]
            equal = control["relocations"] == canonical["relocations"]
            assert equal == control["relocations_equal_to_canonical"]
            assert len(control["relocations"]) == len(canonical["relocations"])
            for current, original in zip(
                control["relocations"], canonical["relocations"]
            ):
                changed = {key for key in current if current[key] != original[key]}
                assert changed <= {"symbol_size"}
                if changed:
                    assert control["label"] == "source_object"
                    assert original["symbol_size"] is None
                    assert current["symbol_size"] > 0
    return len(receipt["controls"])


def json_value(value):
    if isinstance(value, bytes):
        return value.hex()
    if isinstance(value, (set, frozenset)):
        return sorted(value)
    raise TypeError(type(value).__name__)


def capture(receipt, control):
    from snail import match

    with tempfile.TemporaryDirectory(prefix="snail-path-context-replay-") as temp:
        directory = Path(temp)
        (directory / "scratch.cpp").write_text(source_for(receipt, control))
        (directory / "scratch.conf").write_text(receipt["configs"][control["function"]])
        config = match.load_scratch_config(directory)
        status = match.scratch_status_payload(match.evaluate_scratch(config))
        if status["error"] is not None:
            raise ValueError(status["error"])
        obj = match.extract_object_function(
            match.parse_coff_object((directory / "build/scratch.obj").read_bytes()),
            config.symbol or config.function,
            reference_manifest=match.load_default_reference_symbol_manifest(),
        )
        return {
            "measured": {key: status[key] for key in METRICS},
            "data": obj.data.hex(),
            "relocations": json.loads(
                json.dumps(
                    [dataclasses.asdict(r) for r in obj.relocation_references],
                    default=json_value,
                )
            ),
        }


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--replay", action="store_true")
    parser.add_argument("--function")
    args = parser.parse_args()
    receipt = json.loads(RECEIPT.read_text())
    count = verify(receipt)
    for field in ("data", "source_sha256", "measured", "relocations"):
        bad = copy.deepcopy(receipt)
        control = bad["controls"][-1]
        if field == "data":
            data = bytearray.fromhex(control[field])
            data[20] ^= 1
            control[field] = data.hex()
        elif field == "source_sha256":
            control[field] = "0" * 64
        elif field == "relocations":
            control[field][0]["addend"] ^= 1
        else:
            control[field]["body_byte_exact"] = True
        try:
            verify(bad)
        except AssertionError:
            pass
        else:
            raise AssertionError(f"Accepted corrupt {field}")
    print(
        f"Verified {count} frozen controls and four corruption rejections", flush=True
    )
    if args.replay:
        for filename, digest in receipt["build_inputs"].items():
            if sha((ROOT / filename).read_bytes()) != digest:
                raise ValueError(f"Build input changed: {filename}")
        selected = [
            c for c in receipt["controls"] if args.function in (None, c["function"])
        ]
        if not selected:
            parser.error("Unknown function")
        for control in selected:
            actual = capture(receipt, control)
            for key, value in actual.items():
                assert value == control[key], (
                    control["function"],
                    control["label"],
                    key,
                )
            print(
                f"Replay agrees: {control['function']} / {control['label']}", flush=True
            )


if __name__ == "__main__":
    main()
