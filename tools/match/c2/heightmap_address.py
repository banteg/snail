"""Replay the heightmap pointer-origin controls and preserving C2 observations."""

import argparse
import copy
import hashlib
import json
import sys
from pathlib import Path

MATCH_ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(MATCH_ROOT))
from check_heightmap_coordinates_20260922 import replay
from replay_four_builder_controls_20260912 import reconstruct

RECEIPT = MATCH_ROOT / "heightmap-address-20260922.json"
FUNCTION = "sample_smtrack_heightmap"


def identity(operand):
    assert operand["kind"] in (1, 2)
    return operand["kind"], operand["raw"][6 if operand["kind"] == 1 else 5]


def chain(event, label):
    """Follow the pixel multiply through pointer formation into its local copy."""
    stage = event["target_rva"]
    assert event["boundary"] == "entry"
    assert stage in (0xFCDA, 0x29511, 0x296DE)
    nodes = event["nodes"]
    mul_op = 0xC1 if stage == 0x296DE else 0x16F
    (multiply,) = [n for n in nodes if n["line"] == 25 and n["op"] == mul_op]
    assert all(op["raw"][2] >> 28 == 1 for op in multiply["src"])
    value = identity(multiply["dst"][0])
    pos = nodes.index(multiply)
    address = nodes[pos + 1]
    address_ops = {
        0xFCDA: 0x16D,
        0x29511: 0x12 if label == "payload" else 0x2D,
        0x296DE: 0x12 if label == "payload" else 0x2D,
    }
    assert address["op"] == address_ops[stage] and address["line"] == 26
    sources = [op for op in address["src"] if op["kind"] in (1, 2)]
    assert len(sources) == 2 and identity(sources[0]) == value
    assert identity(sources[1]) != value
    value = identity(address["dst"][0])
    end = pos + 2
    bias = 0
    if stage == 0xFCDA and label == "payload":
        biased = nodes[end]
        assert biased["op"] == 0x16D
        assert identity(biased["src"][0]) == value
        assert biased["src"][1]["kind"] == 7
        bias = biased["src"][1]["raw"][6]
        assert bias == 18
        value = identity(biased["dst"][0])
        end += 1
    copied = nodes[end]
    assert copied["op"] == (1 if stage == 0x296DE else 0x15B)
    assert copied["line"] == 26
    assert identity(copied["src"][0]) == value
    destructive = identity(multiply["dst"][0]) == identity(address["dst"][0])
    assert destructive == (stage == 0x296DE and label == "header")
    return nodes[pos : end + 1], {
        "stage": stage,
        "address_opcode": address["op"],
        "explicit_early_bias": bias,
        "overwrites_pixel_offset": destructive,
        "pointer_assignment_survives": True,
    }


def select(event, label):
    selected, _ = chain(event, label)
    return {**event, "full_node_count": len(event["nodes"]), "nodes": selected}


def validate(observation, label):
    manifest = observation["manifest"]
    assert manifest["whole_coff_equal_except_timestamp"]
    assert manifest["missing_stream_rejected"]
    assert manifest["compiler_decisions_modified"] is False
    assert (
        hashlib.sha256(observation["source"].encode()).hexdigest()
        == manifest["source_sha256"]
    )
    events = observation["events"]
    assert [e["target_rva"] for e in events] == [0xFCDA, 0x29511, 0x296DE]
    signatures = [chain(event, label)[1] for event in events]
    assert signatures == observation["expected"]
    capture = observation["capture"]
    status = capture["measured"]
    relocations = copy.deepcopy(capture["relocations"])
    for relocation in relocations:
        # The original capture serializes these empty sets as strings. The
        # matcher's conservative fingerprint serializes them as sorted lists.
        assert relocation["symbol_relocation_offsets"] == "frozenset()"
        relocation["symbol_relocation_offsets"] = []
    fingerprint = {
        "data": capture["candidate_hex"],
        "relocation_offsets": sorted(r["offset"] for r in relocations),
        "relocation_references": relocations,
    }
    assert (
        hashlib.sha256(json.dumps(fingerprint, sort_keys=True).encode()).hexdigest()
        == status["code_sha256"]
    )
    assert status["match_ratio"] == (106 if label == "payload" else 97) / 109
    assert status["candidate_instructions"] == status["target_instructions"] == 109
    assert status["body_byte_exact"] is False
    assert status["references"] == {
        "ok": 13,
        "unresolved": 0,
        "mismatch": 0,
        "unaudited": 0,
    }
    assert manifest["metrics"] == {
        "ratio": status["match_ratio"],
        "target_instructions": 109,
        "candidate_instructions": 109,
        "prefix_instructions": status["prefix_instructions"],
        "references_ok": 13,
        "reference_problems": 0,
        "exact": False,
        "body_byte_exact": False,
    }
    return signatures


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--replay", action="store_true", help="Recompile all controls")
    parser.add_argument(
        "--out", type=Path, help="Repeat both traces in a new directory"
    )
    args = parser.parse_args()
    receipt = json.loads(RECEIPT.read_text())
    baseline = receipt["baselines"][FUNCTION]
    source = (MATCH_ROOT / "scratches" / FUNCTION / "scratch.cpp").read_text()
    assert source == baseline["source"]
    assert hashlib.sha256(source.encode()).hexdigest() == baseline["source_sha256"]
    assert len(receipt["controls"]) == 53
    for control in receipt["controls"]:
        reconstruct(source, control)
        assert control["measured"]["error"] is None
        assert control["measured"]["body_byte_exact"] is False
    for label, observation in receipt["compiler_observations"].items():
        control = receipt["controls"][observation["control_index"]]
        assert reconstruct(source, control) == observation["source"]
        assert control["measured"] == observation["capture"]["measured"]
        result = validate(observation, label)
        for corruption in ("source", "expression", "opcode", "claim", "bytes"):
            bad = copy.deepcopy(observation)
            if corruption == "source":
                bad["source"] += "\n"
            elif corruption == "expression":
                bad["events"][0]["nodes"][0]["dst"][0]["raw"][6] ^= 1
            elif corruption == "opcode":
                bad["events"][1]["nodes"][1]["op"] ^= 1
            elif corruption == "bytes":
                data = bytearray.fromhex(bad["capture"]["candidate_hex"])
                data[233] ^= 1
                bad["capture"]["candidate_hex"] = data.hex()
            else:
                bad["expected"][2]["overwrites_pixel_offset"] ^= True
            try:
                validate(bad, label)
            except (AssertionError, ValueError):
                pass
            else:
                raise AssertionError(f"Accepted corrupt {label}/{corruption}")
        if args.out:
            import trace

            scratch = args.out / (label + "-input")
            scratch.mkdir(parents=True)
            (scratch / "scratch.cpp").write_text(observation["source"])
            (scratch / "scratch.conf").write_text(receipt["config"])
            manifest, events = trace.trace(scratch, args.out / label, passes_only=True)
            fresh = {
                **observation,
                "manifest": manifest,
                "events": [select(events[i], label) for i in (1, 4, 5)],
            }
            assert validate(fresh, label) == result
            assert (
                manifest["normalized_coff_sha256"]
                == observation["manifest"]["normalized_coff_sha256"]
            )
        print(label, json.dumps(result, sort_keys=True))
    if args.replay:
        replay(receipt)
    print("Validated 53 source recipes and ten corrupt-observation rejections")


if __name__ == "__main__":
    main()
