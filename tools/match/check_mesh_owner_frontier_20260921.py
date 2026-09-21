"""Independently verify the captured mesh-owner changes and literal residuals."""

import copy
import hashlib
import json
from pathlib import Path

import capstone

RECEIPT = Path(__file__).with_name("mesh-owner-frontier-20260921.json")


def verify(proof):
    baseline, retained = proof["baseline"], proof["retained"]
    native = bytes.fromhex(retained["native_hex"])
    before = bytes.fromhex(baseline["candidate_hex"])
    after = bytes.fromhex(retained["candidate_hex"])
    assert native == bytes.fromhex(baseline["native_hex"])
    assert len(native) == len(before) == len(after)
    assert baseline["relocations"] == retained["relocations"]
    assert (
        baseline["measured"]["compared_target_ranges"]
        == retained["measured"]["compared_target_ranges"]
    )
    assert retained["measured"]["unexplained_target_ranges"] == []
    body_end = retained["measured"]["compared_target_ranges"][-1][1]
    relocations = {r["offset"]: r for r in retained["relocations"]}
    relocation_bytes = {i for off in relocations for i in range(off, off + 4)}
    changed = [i for i, (a, b) in enumerate(zip(before, after, strict=True)) if a != b]
    assert changed
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    native_insns = {i.address: i for i in md.disasm(native[:body_end], 0)}
    candidate_insns = {i.address: i for i in md.disasm(after[:body_end], 0)}
    for off in changed:
        assert off < body_end and off not in relocation_bytes
        assert after[off] == native[off]
        insn = next(
            i for i in native_insns.values() if i.address <= off < i.address + i.size
        )
        other = candidate_insns[insn.address]
        assert insn.size == other.size and insn.bytes == other.bytes
    branches = []
    for off, insn in native_insns.items():
        if insn.group(capstone.CS_GRP_JUMP):
            other = candidate_insns[off]
            assert insn.bytes == other.bytes
            assert insn.operands[0].imm == other.operands[0].imm
            assert insn.operands[0].imm in native_insns
            assert other.operands[0].imm in candidate_insns
            branches.append(off)
    entries = retained["references"]["entries"]
    assert all(e["status"] == "ok" for e in entries)
    positional = all(
        e["target_index"] == e["candidate_index"]
        and e["target_offset"] == e["candidate_offset"]
        for e in entries
    )
    result = {
        "changed_offsets": changed,
        "changed_bytes_all_native_equal": True,
        "literal_local_branches": len(branches),
        "all_references_positional": positional,
    }
    if positional:
        left, right = bytearray(native[:body_end]), bytearray(after[:body_end])
        consumed = set()
        for entry in entries:
            off = entry["target_offset"]
            a, b = native_insns[off], candidate_insns[off]
            assert a.size == b.size
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
                assert (
                    ao == bo
                    and getattr(a, field + "_size") == getattr(b, field + "_size") == 4
                )
                relocation = relocations[off + bo]
                assert relocation["explained"] and relocation["key"] == cr["key"]
                assert int.from_bytes(
                    after[off + bo : off + bo + 4], "little"
                ) == relocation["addend"] % (1 << 32)
                native_value = int.from_bytes(native[off + ao : off + ao + 4], "little")
                if relocation["relocation_type"] == 20:
                    native_base = retained["target_instructions"][0]["address"]
                    native_value = (native_base + off + a.size + native_value) % (
                        1 << 32
                    )
                else:
                    assert relocation["relocation_type"] == 6
                assert native_value == tr["value"]
                assert off + bo not in consumed
                consumed.add(off + bo)
                left[off + ao : off + ao + 4] = right[off + bo : off + bo + 4] = bytes(
                    4
                )
        assert consumed == {off for off in relocations if off < body_end}
        result.update(
            strict_positional_references=len(consumed),
            unequal_literal_offsets=[
                i for i, (a, b) in enumerate(zip(left, right, strict=True)) if a != b
            ],
            target_sha256=hashlib.sha256(left).hexdigest(),
            candidate_sha256=hashlib.sha256(right).hexdigest(),
        )
    return result


def main():
    receipt = json.loads(RECEIPT.read_text())
    results = {}
    for name, proof in receipt["proofs"].items():
        results[name] = verify(proof)
        bad = copy.deepcopy(proof)
        data = bytearray.fromhex(bad["retained"]["candidate_hex"])
        data[results[name]["changed_offsets"][0]] ^= 1
        bad["retained"]["candidate_hex"] = data.hex()
        try:
            verify(bad)
        except AssertionError:
            pass
        else:
            raise AssertionError("Corrupt changed byte was accepted")
        if results[name]["all_references_positional"]:
            bad = copy.deepcopy(proof)
            bad["retained"]["references"]["entries"][0]["target_references"][0][
                "value"
            ] ^= 1
            try:
                verify(bad)
            except AssertionError:
                pass
            else:
                raise AssertionError("Corrupt reference target was accepted")
    print(json.dumps(results, indent=2))


if __name__ == "__main__":
    main()
