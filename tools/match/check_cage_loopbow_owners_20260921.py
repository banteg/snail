"""Verify the retained Cage2/LoopBow bytes, relocation identities and residuals."""

import copy
import hashlib
import json
from pathlib import Path

import capstone
from replay_four_builder_controls_20260912 import reconstruct

RECEIPT = Path(__file__).with_name("cage-loopbow-owners-20260921.json")


def verify(proof):
    retained = proof["retained"]
    native = bytes.fromhex(retained["native_hex"])
    candidate = bytes.fromhex(retained["candidate_hex"])
    assert native == bytes.fromhex(proof["baseline"]["native_hex"])
    status = retained["measured"]
    assert status["unexplained_target_ranges"] == []
    assert len(status["compared_target_ranges"]) == 1
    start, end = status["compared_target_ranges"][0]
    assert start == 0 and len(native) == len(candidate)
    assert status["excluded_target_ranges"] == [[end, len(native), "terminal-padding"]]
    assert candidate[end:] == native[end:]
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    target = {i.address: i for i in md.disasm(native[:end], 0)}
    compiled = {i.address: i for i in md.disasm(candidate[:end], 0)}
    assert len(target) == len(compiled) == status["target_instructions"]
    assert len(compiled) == status["candidate_instructions"]
    assert max(i.address + i.size for i in target.values()) == end
    assert max(i.address + i.size for i in compiled.values()) == end
    relocs = {r["offset"]: r for r in retained["relocations"]}
    assert len(relocs) == len(retained["relocations"])
    left, right = bytearray(native[:end]), bytearray(candidate[:end])
    consumed = set()
    positional = 0
    for entry in retained["references"]["entries"]:
        assert entry["status"] == "ok"
        to, co = entry["target_offset"], entry["candidate_offset"]
        a, b = target[to], compiled[co]
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
            assert int.from_bytes(candidate[co + bo : co + bo + 4], "little") == (
                relocation["addend"] % (1 << 32)
            )
            value = int.from_bytes(native[to + ao : to + ao + 4], "little")
            if relocation["relocation_type"] == 20:
                value = (status["address"] + to + a.size + value) % (1 << 32)
            else:
                assert relocation["relocation_type"] == 6
            assert value == tr["value"]
            assert co + bo not in consumed
            consumed.add(co + bo)
            aa[ao : ao + 4] = bb[bo : bo + 4] = bytes(4)
            left[to + ao : to + ao + 4] = right[co + bo : co + bo + 4] = bytes(4)
        assert aa == bb
    assert consumed == set(relocs)
    branches = []
    for off, insn in target.items():
        if insn.group(capstone.CS_GRP_JUMP):
            other = compiled[off]
            assert insn.bytes == other.bytes
            assert insn.operands[0].imm == other.operands[0].imm
            assert insn.operands[0].imm in target
            assert other.operands[0].imm in compiled
            branches.append(off)
    unequal = [i for i in range(end) if left[i] != right[i]]
    assert unequal and status["body_byte_exact"] is False
    # Contiguous equal runs must start/end on the same instruction boundaries.
    regions = []
    for off, insn in target.items():
        other = compiled.get(off)
        equal = (
            other is not None
            and insn.size == other.size
            and left[off : off + insn.size] == right[off : off + insn.size]
        )
        if equal:
            if regions and regions[-1][1] == off:
                regions[-1][1] += insn.size
                regions[-1][2] += 1
            else:
                regions.append([off, off + insn.size, 1])
    return {
        "body_bytes": end,
        "padding_bytes": len(native) - end,
        "instructions": len(target),
        "audited_relocations": len(consumed),
        "positional_reference_instructions": positional,
        "literal_local_branches": len(branches),
        "unequal_literal_offsets": unequal,
        "equal_instruction_regions": regions,
        "masked_native_sha256": hashlib.sha256(left).hexdigest(),
        "masked_candidate_sha256": hashlib.sha256(right).hexdigest(),
        "body_byte_exact": False,
    }


def main():
    receipt = json.loads(RECEIPT.read_text())
    for baseline in receipt["unit_source_bases"].values():
        assert (
            hashlib.sha256(baseline["source"].encode()).hexdigest()
            == baseline["source_sha256"]
        )
    for digest, recipe in receipt["unit_source_recipes"].items():
        assert recipe["source_sha256"] == digest
        reconstruct(receipt["unit_source_bases"][recipe["base"]]["source"], recipe)
    for control in receipt["unit_controls"]:
        assert control["source_sha256"] in receipt["unit_source_recipes"]
    for name, proof in receipt["proofs"].items():
        source = RECEIPT.parent / "scratches" / name / "scratch.cpp"
        assert (
            hashlib.sha256(source.read_bytes()).hexdigest()
            == proof["canonical_source_sha256"]
        )
        result = verify(proof)
        assert result == proof["expected"]
        for corrupt in ("body", "reference", "padding"):
            bad = copy.deepcopy(proof)
            if corrupt == "reference":
                bad["retained"]["references"]["entries"][0]["target_references"][0][
                    "value"
                ] ^= 1
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


if __name__ == "__main__":
    main()
