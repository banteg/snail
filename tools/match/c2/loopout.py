"""Check and reproduce LoopOut's preserving interpolation-order observations."""

import argparse
import copy
import hashlib
import json
import sys
from pathlib import Path

MATCH_ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(MATCH_ROOT))
from check_cage_loopbow_owners_20260921 import verify
from replay_four_builder_controls_20260912 import reconstruct

RECEIPT = MATCH_ROOT / "loopout-address-order-20260922.json"
FUNCTION = "initialize_loopout_path_template_pair"


def sha(data):
    return hashlib.sha256(data).hexdigest()


def address_order(nodes, label):
    baseline = label == "baseline"
    expected = (
        [0x16D, 0x16D, 0x16D, 0x16E, 0x162, 0x16F, 0x175, 0x16D, 0x16D, 0x16D, 0x15B]
        if baseline
        else [
            0x15B,
            0x15B,
            0x16D,
            0x16D,
            0x16D,
            0x16E,
            0x162,
            0x16F,
            0x175,
            0x16D,
            0x16D,
            0x16D,
            0x15B,
        ]
    )
    assert [node["op"] for node in nodes] == expected
    first, last = (2, 8) if baseline else (3, 10)
    sums = [nodes[first], nodes[last]]
    for node in sums:
        assert [operand["kind"] for operand in node["src"]] == [2, 2]
        assert node["dst"][0]["kind"] == 1
    common = {operand["raw"][5] for operand in sums[0]["src"]} & {
        operand["raw"][5] for operand in sums[1]["src"]
    }
    assert len(common) == 1
    bank = next(iter(common))
    rows = []
    for node in sums:
        operands = node["src"]
        bank_index = next(
            i for i, operand in enumerate(operands) if operand["raw"][5] == bank
        )
        costs = [operand["raw"][3] for operand in operands]
        assert costs[0] > costs[1]
        rows.append(
            {
                "bank_cost": costs[bank_index],
                "offset_cost": costs[1 - bank_index],
                "bank_first": bank_index == 0,
            }
        )
    assert rows[0]["bank_cost"] == rows[1]["bank_cost"]

    def edge(producer, consumer):
        value = nodes[producer]["dst"][0]["raw"][6]
        assert nodes[producer]["dst"][0]["kind"] == 1
        assert (
            sum(
                op["kind"] == 1 and op["raw"][6] == value
                for op in nodes[consumer]["src"]
            )
            == 1
        )

    if baseline:
        # The endpoint's +0x90 member displacement was folded into its offset.
        endpoint = next(op for op in sums[0]["src"] if op["raw"][5] != bank)
        assert endpoint["raw"][5] == nodes[0]["dst"][0]["raw"][5]
        assert nodes[0]["dst"][0]["kind"] == 2
        assert nodes[0]["src"][1]["kind"] == 7
        assert nodes[0]["src"][1]["raw"][6] == 0x90
        edges = [(2, 3), (3, 4), (4, 5), (5, 6), (6, 7), (7, 10)]
    else:
        # The borrowed bank is loaded before the two address sums.
        assert nodes[1]["dst"][0]["raw"][5] == bank
        assert nodes[1]["src"][0]["kind"] == 6
        assert nodes[4]["src"][1]["kind"] == 7
        assert nodes[4]["src"][1]["raw"][6] == 0x90
        edges = [(3, 4), (4, 5), (5, 6), (6, 7), (7, 8), (8, 9), (9, 12)]
    edges.extend([(last, last + 1), (last + 1, last + 2)])
    assert nodes[last + 1]["src"][1]["kind"] == 7
    assert nodes[last + 1]["src"][1]["raw"][6] == 0x90
    for producer, consumer in edges:
        edge(producer, consumer)
    return {"endpoint": rows[0], "destination": rows[1]}


def validate(receipt):
    for baseline in receipt["baselines"].values():
        assert sha(baseline["source"].encode()) == baseline["source_sha256"]
    for control in receipt["controls"]:
        reconstruct(receipt["baselines"][control["function"]]["source"], control)
        assert control["measured"]["body_byte_exact"] is False
        assert control["measured"]["error"] is None
    expected = {
        "baseline": {
            "endpoint": {
                "bank_cost": 0x102A0,
                "offset_cost": 0x16EC0,
                "bank_first": False,
            },
            "destination": {
                "bank_cost": 0x102A0,
                "offset_cost": 0x14A80,
                "bank_first": False,
            },
        },
        "borrow": {
            "endpoint": {
                "bank_cost": 0x16F00,
                "offset_cost": 0x16E80,
                "bank_first": True,
            },
            "destination": {
                "bank_cost": 0x16F00,
                "offset_cost": 0x14B00,
                "bank_first": True,
            },
        },
    }
    for label, observation in receipt["observations"].items():
        source = receipt["observed_sources"][label]
        manifest = observation["manifest"]
        capture = receipt["proofs"][label]
        assert (
            sha(source.encode())
            == observation["source_sha256"]
            == manifest["source_sha256"]
        )
        assert manifest["whole_coff_equal_except_timestamp"]
        assert manifest["missing_stream_rejected"]
        assert manifest["compiler_decisions_modified"] is False
        assert manifest["metrics"] == {
            "ratio": 1.0,
            "target_instructions": 718,
            "candidate_instructions": 718,
            "prefix_instructions": 718,
            "references_ok": 52,
            "reference_problems": 0,
            "exact": True,
            "body_byte_exact": False,
        }
        assert (
            sha(bytes.fromhex(capture["candidate_hex"]))
            == observation["observed_function_bytes_sha256"]
        )
        result = verify({"baseline": capture, "retained": capture})
        assert result == observation["expected_byte_audit"]
        assert result["unequal_literal_offsets"] == (
            [745] if label == "baseline" else [770]
        )
        assert (
            result["positional_reference_instructions"]
            == result["audited_relocations"]
            == 52
        )
        assert result["literal_local_branches"] == 26
        assert address_order(observation["nodes"], label) == expected[label]
        # Native requires endpoint bank-first and destination offset-first.
        # With fixed index trees these strict inequalities have no solution.
        assert (
            expected[label]["endpoint"]["offset_cost"]
            > expected[label]["destination"]["offset_cost"]
        )
    before, after = [receipt["proofs"][label] for label in ("baseline", "borrow")]
    assert before["references"] == after["references"]
    assert before["relocations"] == after["relocations"]
    old, new = [bytes.fromhex(capture["candidate_hex"]) for capture in (before, after)]
    assert [i for i, (a, b) in enumerate(zip(old, new, strict=True)) if a != b] == [
        745,
        770,
    ]
    assert [(old[i], new[i]) for i in (745, 770)] == [(0x01, 0x08), (0x07, 0x38)]
    return expected


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--out",
        type=Path,
        help="Reproduce both preserving observations in a fresh directory",
    )
    args = parser.parse_args()
    receipt = json.loads(RECEIPT.read_text())
    expected = validate(receipt)
    for corruption in ("address", "cost", "value", "byte", "reference", "padding"):
        bad = copy.deepcopy(receipt)
        nodes = bad["observations"]["baseline"]["nodes"]
        if corruption == "address":
            nodes[9]["src"][0]["raw"][6] ^= 1
        elif corruption == "cost":
            nodes[2]["src"][0]["raw"][3] ^= 1
        elif corruption == "value":
            nodes[10]["src"][0]["raw"][6] ^= 1
        elif corruption == "reference":
            bad["proofs"]["baseline"]["references"]["entries"][0]["target_references"][
                0
            ]["value"] ^= 1
        else:
            data = bytearray.fromhex(bad["proofs"]["baseline"]["candidate_hex"])
            data[745 if corruption == "byte" else -1] ^= 1
            bad["proofs"]["baseline"]["candidate_hex"] = data.hex()
        try:
            validate(bad)
        except (AssertionError, KeyError):
            pass
        else:
            raise AssertionError(f"Accepted {corruption} corruption")
    if args.out:
        from trace import m, trace

        args.out.mkdir(parents=True, exist_ok=False)
        for label, source in receipt["observed_sources"].items():
            scratch = args.out / (label + "-source")
            scratch.mkdir()
            (scratch / "scratch.cpp").write_text(source)
            (scratch / "scratch.conf").write_bytes(
                (MATCH_ROOT / "scratches" / FUNCTION / "scratch.conf").read_bytes()
            )
            manifest, events = trace(
                scratch, args.out / (label + "-observed"), passes_only=True
            )
            for path in manifest["object_paths"]:
                obj = m.parse_coff_object(
                    (args.out / (label + "-observed") / path).read_bytes()
                )
                function = m.extract_object_function(
                    obj,
                    FUNCTION,
                    reference_manifest=m.load_default_reference_symbol_manifest(),
                )
                assert function.data.hex() == receipt["proofs"][label]["candidate_hex"]
            assert (
                manifest["metrics"]
                == receipt["observations"][label]["manifest"]["metrics"]
            )
            (event,) = [event for event in events if event["target_rva"] == 0x281CD]
            nodes = [
                node
                for node in event["nodes"]
                if node["line"] == receipt["observations"][label]["line"]
            ]
            assert address_order(nodes, label) == expected[label]
    print(json.dumps(expected, indent=2))
    print(
        f"Validated {len(receipt['controls'])} recipes and six corruption controls; both bodies remain partial"
    )


if __name__ == "__main__":
    main()
