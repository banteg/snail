"""Independently verify the complete Supertramp encoded-body match."""

import copy
import hashlib
import json
from pathlib import Path

import capstone

RECEIPT = Path(__file__).with_name("supertramp-halfpipe-owners-20260921.json")


def verify(proof):
    retained = proof["retained"]
    native = bytes.fromhex(retained["native_hex"])
    candidate = bytes.fromhex(retained["candidate_hex"])
    assert native == bytes.fromhex(proof["baseline"]["native_hex"])
    assert len(native) == 1936
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
    assert len(target) == len(compiled) == status["target_instructions"] == 552
    assert [(i.address, i.size) for i in target.values()] == [
        (i.address, i.size) for i in compiled.values()
    ]
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
        assert to == co and entry["target_index"] == entry["candidate_index"]
        positional += 1
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
    assert left == right
    assert status["body_byte_exact"] is True
    assert len(consumed) == positional == 36
    return {
        "body_bytes": end,
        "padding_bytes": len(native) - end,
        "instructions": len(target),
        "audited_relocations": len(consumed),
        "positional_reference_instructions": positional,
        "literal_local_branches": len(branches),
        "unequal_literal_offsets": [],
        "masked_body_sha256": hashlib.sha256(left).hexdigest(),
        "body_byte_exact": True,
    }


def main():
    receipt = json.loads(RECEIPT.read_text())
    for name, proof in receipt["partial_proofs"].items():
        source = RECEIPT.parent / "scratches" / name / "scratch.cpp"
        assert hashlib.sha256(source.read_bytes()).hexdigest() == proof[
            "canonical_source_sha256"
        ]
        before, after = proof["baseline"], proof["retained"]
        assert before["candidate_hex"][: 575 * 2] == after["candidate_hex"][: 575 * 2]
        assert [r for r in before["relocations"] if r["offset"] < 575] == [
            r for r in after["relocations"] if r["offset"] < 575
        ]
        assert after["measured"]["body_byte_exact"] is False
        print(name, "575-byte prefix and relocation identities preserved; partial")
    for name, proof in receipt["proofs"].items():
        source = RECEIPT.parent / "scratches" / name / "scratch.cpp"
        assert (
            hashlib.sha256(source.read_bytes()).hexdigest()
            == proof["canonical_source_sha256"]
        )
        result = verify(proof)
        assert result == proof["expected"]
        for corrupt in ("body", "reference", "relocation", "padding"):
            # Byte, target-identity, COFF addend and padding corruption must fail.
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


if __name__ == "__main__":
    main()
