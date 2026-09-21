"""Check the retained Tip definition lifetime against captured native bytes."""

import copy
import hashlib
import json
from pathlib import Path

import capstone

RECEIPT = Path(__file__).with_name("three-initializer-owners-20260921.json")


def verify(proof):
    baseline, retained = proof["baseline"], proof["retained"]
    native = bytes.fromhex(retained["native_hex"])
    before = bytes.fromhex(baseline["candidate_hex"])
    after = bytes.fromhex(retained["candidate_hex"])
    assert native == bytes.fromhex(baseline["native_hex"])
    assert len(native) == len(before) == len(after) == 512
    assert before[:382] == after[:382]
    assert before[511:] == after[511:] == native[511:]
    assert native[382:392].hex() == "8b56088d4c24088b4204"
    assert after[382:392].hex() == "8b46088d4c24088b4004"
    for state in (baseline, retained):
        assert state["measured"]["compared_target_ranges"] == [[0, 511]]
        assert state["measured"]["unexplained_target_ranges"] == []
        assert state["measured"]["candidate_instructions"] == 154
        assert state["measured"]["target_instructions"] == 154
    moves = []
    for old, new in zip(baseline["relocations"], retained["relocations"], strict=True):
        assert {k: v for k, v in old.items() if k != "offset"} == {
            k: v for k, v in new.items() if k != "offset"
        }
        if old["offset"] != new["offset"]:
            moves.append([old["offset"], new["offset"]])
    assert moves == [[464, 465], [489, 491]]

    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    target = {i.address: i for i in md.disasm(native[:511], 0)}
    candidate = {i.address: i for i in md.disasm(after[:511], 0)}
    assert len(target) == len(candidate) == 154
    left, right = bytearray(native), bytearray(after)
    relocations = {r["offset"]: r for r in retained["relocations"]}
    consumed = set()
    region_refs = 0
    entries = retained["references"]["entries"]
    assert len(entries) == 27
    for entry in entries:
        assert entry["status"] == "ok"
        assert entry["target_index"] == entry["candidate_index"]
        assert entry["target_offset"] == entry["candidate_offset"]
        off = entry["target_offset"]
        a, b = target[off], candidate[off]
        assert a.size == b.size
        aa, bb = bytearray(a.bytes), bytearray(b.bytes)
        for tr, cr in zip(
            entry["target_references"], entry["candidate_references"], strict=True
        ):
            assert tr["explained"] and cr["explained"]
            assert (tr["kind"], tr["operand_index"], tr["key"]) == (
                cr["kind"],
                cr["operand_index"],
                cr["key"],
            )
            assert tr["key"] is not None and cr["source"] == "reloc"
            field = "imm" if cr["kind"] == "imm" else "disp"
            ao, bo = getattr(a, field + "_offset"), getattr(b, field + "_offset")
            assert ao == bo
            assert getattr(a, field + "_size") == getattr(b, field + "_size") == 4
            reloc = relocations[off + bo]
            assert reloc["explained"] and reloc["key"] == cr["key"]
            assert int.from_bytes(after[off + bo : off + bo + 4], "little") == (
                reloc["addend"] % (1 << 32)
            )
            value = int.from_bytes(native[off + ao : off + ao + 4], "little")
            if reloc["relocation_type"] == 20:
                value = (0x448A40 + off + a.size + value) % (1 << 32)
            else:
                assert reloc["relocation_type"] == 6
            assert value == tr["value"]
            assert off + bo not in consumed
            consumed.add(off + bo)
            aa[ao : ao + 4] = bb[bo : bo + 4] = bytes(4)
            left[off + ao : off + ao + 4] = right[off + bo : off + bo + 4] = bytes(4)
            region_refs += 392 <= off < 511
        assert aa == bb
    assert consumed == set(relocations)
    assert region_refs == 6
    assert left[392:511] == right[392:511]
    region = [i for off, i in target.items() if 392 <= off < 511]
    assert len(region) == 36
    assert [(i.address, i.size) for i in region] == [
        (i.address, i.size) for off, i in candidate.items() if 392 <= off < 511
    ]
    branches = []
    for off, insn in target.items():
        if insn.group(capstone.CS_GRP_JUMP):
            other = candidate[off]
            assert insn.bytes == other.bytes
            assert insn.operands[0].imm == other.operands[0].imm
            assert insn.operands[0].imm in target
            assert other.operands[0].imm in candidate
            branches.append(off)
    return {
        "region": [392, 511],
        "region_instructions": 36,
        "region_audited_references": 6,
        "region_sha256": hashlib.sha256(left[392:511]).hexdigest(),
        "strict_positional_references": 27,
        "literal_local_branches": len(branches),
        "moved_relocations": moves,
        "outside_changed_branch_and_tail_unchanged": True,
        "remaining_literal_offsets": [i for i in range(511) if left[i] != right[i]],
        "body_byte_exact": retained["measured"]["body_byte_exact"],
    }


def main():
    proof = json.loads(RECEIPT.read_text())["proof"]
    result = verify(proof)
    for label in ("region byte", "outside byte", "reference target"):
        bad = copy.deepcopy(proof)
        if label == "reference target":
            bad["retained"]["references"]["entries"][0]["target_references"][0][
                "value"
            ] ^= 1
        else:
            data = bytearray.fromhex(bad["retained"]["candidate_hex"])
            data[440 if label == "region byte" else 50] ^= 1
            bad["retained"]["candidate_hex"] = data.hex()
        try:
            verify(bad)
        except (AssertionError, KeyError):
            pass
        else:
            raise AssertionError(f"Accepted corrupt {label}")
    result["three_corruption_controls_rejected"] = True
    print(json.dumps(result, indent=2))


if __name__ == "__main__":
    main()
