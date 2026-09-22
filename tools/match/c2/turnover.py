"""Check and reproduce Turnover's observed interpolation address ordering."""

import argparse
import copy
import hashlib
import json
import sys
from pathlib import Path

MATCH_ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(MATCH_ROOT))
from check_turnover_bank_20260922 import verify_change
from replay_four_builder_controls_20260912 import reconstruct

RECEIPT = MATCH_ROOT / "turnover-address-order-20260922.json"
FUNCTION = "initialize_turnover_path_template_pair"


def sha(data):
    return hashlib.sha256(data).hexdigest()


def address_order(nodes):
    """Follow both address sums through their center-field access, within one event."""
    assert len(nodes) == 12
    assert [n["op"] for n in nodes] == [
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
    bank = nodes[0]["dst"][0]["raw"][5]
    assert nodes[0]["src"][0]["kind"] == 6
    assert nodes[0]["dst"][0]["kind"] == 2
    rows = []
    for add_index, consumer_index in [(2, 4), (9, 11)]:
        add, field = nodes[add_index : add_index + 2]
        consumer = nodes[consumer_index]
        assert [op["kind"] for op in add["src"]] == [2, 2]
        assert [op["kind"] for op in field["src"]] == [1, 7]
        assert field["src"][1]["raw"][6] == 0x90
        assert add["dst"][0]["raw"][6] == field["src"][0]["raw"][6]
        address = field["dst"][0]["raw"][6]
        assert (
            sum(op["kind"] == 1 and op["raw"][6] == address for op in consumer["src"])
            == 1
        )
        operands = add["src"]
        bank_positions = [i for i, op in enumerate(operands) if op["raw"][5] == bank]
        assert len(bank_positions) == 1
        bank_position = bank_positions[0]
        costs = [op["raw"][3] for op in operands]
        assert costs[0] > costs[1]
        rows.append(
            {
                "bank_cost": costs[bank_position],
                "offset_cost": costs[1 - bank_position],
                "bank_first": bank_position == 0,
            }
        )
    # The computed interpolation value, not just its destination address, feeds the store.
    for left, right in [(4, 5), (5, 6), (6, 7), (7, 8), (8, 11)]:
        value = nodes[left]["dst"][0]["raw"][6]
        assert (
            sum(op["kind"] == 1 and op["raw"][6] == value for op in nodes[right]["src"])
            == 1
        )
    return {"endpoint": rows[0], "destination": rows[1]}


def select_nodes(events, line):
    (event,) = [e for e in events if e["target_rva"] == 0x281CD]
    nodes = [n for n in event["nodes"] if n["line"] == line]
    address_order(nodes)
    return nodes


def staged_witness(receipt, native_hex):
    import capstone

    witness = receipt["staged_byte_witness"]
    captures = witness["captures"]
    data = [bytes.fromhex(c["candidate_hex"]) for c in captures]
    assert len(data) == 2
    native = bytes.fromhex(native_hex)
    assert witness["native_interpolation_store"] == native[651:658].hex()
    assert witness["native_interpolation_store"] == "d99c0390000000"
    for index, (label, capture, code) in enumerate(
        zip(witness["labels"], captures, data, strict=True)
    ):
        (control,) = [c for c in receipt["controls"] if c["label"] == label]
        assert sha(code) == capture["extracted_bytes_sha256"]
        assert len(code) == witness["candidate_bytes"]
        assert control["measured"]["code_sha256"] == witness["code_sha256"][index]
        assert code[651:658] == native[651:658]
        instructions = list(
            capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32).disasm(code, 0)
        )
        # The body has a live branch tail after RET. Exclude only terminal padding.
        while instructions[-1].mnemonic in {"nop", "int3"}:
            instructions.pop()
        assert len(instructions) == witness["candidate_instructions"][index] == 674
        assert instructions[-1].address + instructions[-1].size == 2439
        assert code[2439:] == b"\x90" * 9
    assert witness["target_instructions"] == 671
    assert (
        witness["relocations_equal"]
        and captures[0]["relocations"] == captures[1]["relocations"]
    )
    assert witness["differences_between_staged_candidates"] == [
        [i, a, b] for i, (a, b) in enumerate(zip(*data, strict=True)) if a != b
    ]
    assert witness["body_byte_exact"] is False


def validate(receipt):
    earlier = json.loads((MATCH_ROOT / "turnover-bank-20260922.json").read_text())
    proof = earlier["proofs"][FUNCTION]
    assert verify_change(proof) == proof["expected"]
    staged_witness(receipt, proof["retained"]["native_hex"])
    for baseline in receipt["baselines"].values():
        assert sha(baseline["source"].encode()) == baseline["source_sha256"]
    for control in receipt["controls"]:
        reconstruct(receipt["baselines"][control["function"]]["source"], control)
        assert control["measured"]["body_byte_exact"] is False
    for name, run in receipt["observations"].items():
        source = receipt["observed_sources"][name]
        manifest = run["manifest"]
        assert sha(source.encode()) == manifest["source_sha256"]
        assert manifest["whole_coff_equal_except_timestamp"]
        assert manifest["missing_stream_rejected"]
        assert manifest["compiler_decisions_modified"] is False
        assert manifest["metrics"] == {
            "ratio": 1.0,
            "target_instructions": 671,
            "candidate_instructions": 671,
            "prefix_instructions": 671,
            "references_ok": 41,
            "reference_problems": 0,
            "exact": True,
            "body_byte_exact": False,
        }
        assert address_order(run["nodes"]) == run["expected"]
    assert (
        receipt["observed_sources"]["previous"]
        == earlier["baselines"][FUNCTION]["source"]
    )
    assert (
        sha(receipt["observed_sources"]["current"].encode())
        == proof["canonical_source_sha256"]
    )
    current = receipt["observations"]["current"]["expected"]
    previous = receipt["observations"]["previous"]["expected"]
    assert previous == {
        "endpoint": {"bank_cost": 0x13700, "offset_cost": 0x14BC0, "bank_first": False},
        "destination": {
            "bank_cost": 0x13700,
            "offset_cost": 0x102A0,
            "bank_first": True,
        },
    }
    assert current == {
        "endpoint": {"bank_cost": 0x14C40, "offset_cost": 0x14BC0, "bank_first": True},
        "destination": {
            "bank_cost": 0x14C40,
            "offset_cost": 0x102A0,
            "bank_first": True,
        },
    }
    return {name: row["expected"] for name, row in receipt["observations"].items()}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--out", type=Path, help="Reproduce both preserving traces in a new directory"
    )
    args = parser.parse_args()
    receipt = json.loads(RECEIPT.read_text())
    expected = validate(receipt)
    for corruption in ("address", "value", "cost", "staged-byte"):
        bad = copy.deepcopy(receipt)
        nodes = bad["observations"]["current"]["nodes"]
        if corruption == "address":
            nodes[10]["src"][0]["raw"][6] ^= 1
        elif corruption == "value":
            nodes[11]["src"][0]["raw"][6] ^= 1
        elif corruption == "cost":
            nodes[2]["src"][0]["raw"][3] ^= 1
        else:
            capture = bad["staged_byte_witness"]["captures"][0]
            data = bytearray.fromhex(capture["candidate_hex"])
            data[653] ^= 1
            capture["candidate_hex"] = data.hex()
        try:
            validate(bad)
        except AssertionError:
            pass
        else:
            raise AssertionError(f"Accepted corrupt {corruption}")
    if args.out:
        from trace import trace

        args.out.mkdir(parents=True, exist_ok=False)
        results = {}
        for name, source in receipt["observed_sources"].items():
            scratch = args.out / (name + "-source")
            scratch.mkdir()
            (scratch / "scratch.cpp").write_text(source)
            (scratch / "scratch.conf").write_bytes(
                (MATCH_ROOT / "scratches" / FUNCTION / "scratch.conf").read_bytes()
            )
            manifest, events = trace(scratch, args.out / name, passes_only=True)
            nodes = select_nodes(events, receipt["observations"][name]["line_raw"])
            assert address_order(nodes) == expected[name]
            assert (
                manifest["metrics"]
                == receipt["observations"][name]["manifest"]["metrics"]
            )
            results[name] = {
                "manifest": manifest,
                "nodes": nodes,
                "expected": expected[name],
            }
            print(name, "whole COFF preserved; address costs reproduced", flush=True)
        (args.out / "results.json").write_text(json.dumps(results, indent=2) + "\n")
    print(json.dumps(expected, sort_keys=True))
    print(
        f"Validated {len(receipt['controls'])} source controls; one encoded byte remains"
    )


if __name__ == "__main__":
    main()
