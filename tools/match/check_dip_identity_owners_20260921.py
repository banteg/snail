"""Verify the paired Dip receiver recovery using captured bytes and relocations."""

import copy
import hashlib
import json
from pathlib import Path

import capstone

RECEIPT = Path(__file__).with_name("dip-identity-owners-20260921.json")


def verify(proof):
    baseline, retained = proof["baseline"], proof["retained"]
    native = bytes.fromhex(retained["native_hex"])
    before = bytes.fromhex(baseline["candidate_hex"])
    after = bytes.fromhex(retained["candidate_hex"])
    assert native == bytes.fromhex(baseline["native_hex"])
    assert len(native) == len(before) == len(after) == 2400
    assert before[:486] == after[:486] and before[575:] == after[575:]
    assert before[486:575] != after[486:575]
    for state in (baseline, retained):
        assert state["measured"]["compared_target_ranges"] == [[0, 2390]]
        assert state["measured"]["unexplained_target_ranges"] == []
        assert state["measured"]["candidate_instructions"] == 655
        assert state["measured"]["target_instructions"] == 655
    assert native[2390:] == after[2390:]
    moved = []
    for old, new in zip(baseline["relocations"], retained["relocations"], strict=True):
        assert {k: v for k, v in old.items() if k != "offset"} == {
            k: v for k, v in new.items() if k != "offset"
        }
        if old["offset"] != new["offset"]:
            moved.append((old["offset"], new["offset"]))
    assert moved == [(498, 496), (524, 522), (530, 528)]

    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    target = {i.address: i for i in md.disasm(native[:2390], 0)}
    candidate = {i.address: i for i in md.disasm(after[:2390], 0)}
    assert len(target) == len(candidate) == 655
    relocs = {r["offset"]: r for r in retained["relocations"]}
    left, right = bytearray(native), bytearray(after)
    consumed, positional, region_refs = set(), 0, 0
    entries = retained["references"]["entries"]
    assert len(entries) == 37
    for entry in entries:
        assert entry["status"] == "ok"
        to, co = entry["target_offset"], entry["candidate_offset"]
        a, b = target[to], candidate[co]
        assert a.size == b.size
        positional += to == co and entry["target_index"] == entry["candidate_index"]
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
            relocation = relocs[co + bo]
            assert relocation["explained"] and relocation["key"] == cr["key"]
            assert int.from_bytes(after[co + bo : co + bo + 4], "little") == (
                relocation["addend"] % (1 << 32)
            )
            value = int.from_bytes(native[to + ao : to + ao + 4], "little")
            if relocation["relocation_type"] == 20:
                value = (0x41E440 + to + a.size + value) % (1 << 32)
            else:
                assert relocation["relocation_type"] == 6
            assert value == tr["value"]
            assert co + bo not in consumed
            consumed.add(co + bo)
            aa[ao : ao + 4] = bb[bo : bo + 4] = bytes(4)
            left[to + ao : to + ao + 4] = right[co + bo : co + bo + 4] = bytes(4)
            if 486 <= co < 580:
                assert to == co and entry["target_index"] == entry["candidate_index"]
                region_refs += 1
        assert aa == bb
    assert consumed == set(relocs)
    assert region_refs == 4
    assert left[486:580] == right[486:580]
    region_target = [i for off, i in target.items() if 486 <= off < 580]
    assert len(region_target) == 27
    assert [(i.address, i.size) for i in region_target] == [
        (i.address, i.size) for off, i in candidate.items() if 486 <= off < 580
    ]
    sib_offsets = [i for i in range(420, 2390) if left[i] != right[i]]
    assert sib_offsets == [
        433,
        447,
        457,
        467,
        477,
        588,
        600,
        637,
        648,
        681,
        715,
        719,
        723,
        784,
        1000,
        1131,
        1146,
    ]
    for off in sib_offsets:
        a = next(i for i in target.values() if i.address <= off < i.address + i.size)
        b = candidate[a.address]
        assert a.size == b.size and a.mnemonic == b.mnemonic
        assert a.bytes[: off - a.address] == b.bytes[: off - b.address]
        assert a.bytes[off - a.address + 1 :] == b.bytes[off - b.address + 1 :]
        assert (native[off] & 0xC0) == (after[off] & 0xC0) == 0
        assert (native[off] & 7) == ((after[off] >> 3) & 7)
        assert (after[off] & 7) == ((native[off] >> 3) & 7)
        assert (native[off] & 7) not in (4, 5)
        assert (after[off] & 7) not in (4, 5)
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
        "region": [486, 580],
        "region_instructions": 27,
        "region_bytes_equal_after_four_audited_relocations": True,
        "region_sha256": hashlib.sha256(left[486:580]).hexdigest(),
        "outside_receiver_region_unchanged": True,
        "moved_relocations": moved,
        "references": len(consumed),
        "positional_references": positional,
        "literal_local_branches": len(branches),
        "remaining_post_header_sib_offsets": sib_offsets,
        "body_byte_exact": retained["measured"]["body_byte_exact"],
    }


def main():
    proof = json.loads(RECEIPT.read_text())["proof"]
    result = verify(proof)
    for label in ("receiver byte", "outside byte", "reference target"):
        bad = copy.deepcopy(proof)
        if label == "reference target":
            bad["retained"]["references"]["entries"][0]["target_references"][0][
                "value"
            ] ^= 1
        else:
            data = bytearray.fromhex(bad["retained"]["candidate_hex"])
            data[487 if label == "receiver byte" else 1500] ^= 1
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
