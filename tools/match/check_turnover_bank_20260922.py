"""Verify Turnover's one-byte improvement without claiming a complete match."""

import copy
import hashlib
import json
from pathlib import Path

from check_cage_loopbow_owners_20260921 import verify
from replay_four_builder_controls_20260912 import reconstruct

RECEIPT = Path(__file__).with_name("turnover-bank-20260922.json")


def verify_change(proof):
    before, after = proof["baseline"], proof["retained"]
    old = bytes.fromhex(before["candidate_hex"])
    new = bytes.fromhex(after["candidate_hex"])
    native = bytes.fromhex(after["native_hex"])
    assert len(old) == len(new) == len(native)
    assert [i for i, (a, b) in enumerate(zip(old, new)) if a != b] == [628]
    assert new[628] == native[628]
    assert before["relocations"] == after["relocations"]
    baseline = verify({"baseline": before, "retained": before})
    retained = verify(proof)
    assert baseline["unequal_literal_offsets"] == [628, 653]
    assert retained["unequal_literal_offsets"] == [653]
    assert not retained["body_byte_exact"]
    return retained


def main():
    receipt = json.loads(RECEIPT.read_text())
    for baseline in receipt["baselines"].values():
        assert hashlib.sha256(baseline["source"].encode()).hexdigest() == baseline[
            "source_sha256"
        ]
    for control in receipt["controls"]:
        reconstruct(receipt["baselines"][control["function"]]["source"], control)
    name = "initialize_turnover_path_template_pair"
    proof = receipt["proofs"][name]
    source = RECEIPT.parent / "scratches" / name / "scratch.cpp"
    assert hashlib.sha256(source.read_bytes()).hexdigest() == proof[
        "canonical_source_sha256"
    ]
    assert verify_change(proof) == proof["expected"]
    for corrupt in ("body", "reference", "relocation", "padding", "residual"):
        bad = copy.deepcopy(proof)
        if corrupt == "reference":
            bad["retained"]["references"]["entries"][0]["target_references"][0][
                "value"
            ] ^= 1
        elif corrupt == "relocation":
            bad["retained"]["relocations"][0]["addend"] ^= 1
        elif corrupt == "residual":
            bad["retained"]["measured"]["body_byte_exact"] = True
        else:
            data = bytearray.fromhex(bad["retained"]["candidate_hex"])
            data[20 if corrupt == "body" else -1] ^= 1
            bad["retained"]["candidate_hex"] = data.hex()
        try:
            assert verify_change(bad) == proof["expected"]
        except (AssertionError, KeyError):
            pass
        else:
            raise AssertionError(f"Accepted corrupt {corrupt}")
    print(json.dumps(proof["expected"], sort_keys=True))
    print(f"Validated {len(receipt['controls'])} source recipes; one literal byte remains")


if __name__ == "__main__":
    main()
