"""Verify partial Looptheloop/LoopBow byte and reference improvements."""

import copy
import hashlib
import json
from pathlib import Path

from check_cage_loopbow_owners_20260921 import verify
from replay_four_builder_controls_20260912 import reconstruct

RECEIPT = Path(__file__).with_name("loop-circle-owners-20260921.json")


def main():
    receipt = json.loads(RECEIPT.read_text())
    for baseline in receipt["baselines"].values():
        assert hashlib.sha256(baseline["source"].encode()).hexdigest() == baseline[
            "source_sha256"
        ]
    for control in receipt["controls"]:
        reconstruct(receipt["baselines"][control["function"]]["source"], control)
    for name, proof in receipt["proofs"].items():
        source = RECEIPT.parent / "scratches" / name / "scratch.cpp"
        assert hashlib.sha256(source.read_bytes()).hexdigest() == proof[
            "canonical_source_sha256"
        ]
        result = verify(proof)
        assert result == proof["expected"]
        assert not result["body_byte_exact"]
        if name == "initialize_loopbow_path_template_pair":
            before = bytes.fromhex(proof["baseline"]["candidate_hex"])
            after = bytes.fromhex(proof["retained"]["candidate_hex"])
            native = bytes.fromhex(proof["retained"]["native_hex"])
            assert len(before) == len(after)
            changed = [i for i, (a, b) in enumerate(zip(before, after)) if a != b]
            assert changed == [2581, 2586, 2763, 2768]
            assert all(after[i] == native[i] for i in changed)
            assert proof["baseline"]["relocations"] == proof["retained"]["relocations"]
        for corrupt in ("body", "reference", "relocation", "padding"):
            bad = copy.deepcopy(proof)
            if corrupt == "reference":
                bad["retained"]["references"]["entries"][0]["target_references"][0][
                    "value"
                ] ^= 1
            elif corrupt == "relocation":
                bad["retained"]["relocations"][0]["addend"] ^= 1
            else:
                data = bytearray.fromhex(bad["retained"]["candidate_hex"])
                data[20 if corrupt == "body" else -1] ^= 1
                bad["retained"]["candidate_hex"] = data.hex()
            try:
                assert verify(bad) == proof["expected"]
            except (AssertionError, KeyError):
                pass
            else:
                raise AssertionError(f"Accepted corrupt {corrupt}")
        print(name, json.dumps(result, sort_keys=True))
    print(f"Validated {len(receipt['controls'])} source recipes; both bodies remain partial")


if __name__ == "__main__":
    main()
