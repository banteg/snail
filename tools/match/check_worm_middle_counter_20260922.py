"""Independently check Worm's bounded middle-counter recovery and residuals."""

import copy
import json
from pathlib import Path

import capstone

md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
md.detail = True
RECEIPT = Path(__file__).with_name("worm-middle-counter-20260922.json")


def decode(data, end, records):
    ins = list(md.disasm(data[:end], 0))
    assert sum(i.size for i in ins) == end
    assert [(i.address, i.size) for i in ins] == [
        (r["offset"], r["size"]) for r in records
    ]
    return ins


def audit_capture(r):
    native = bytes.fromhex(r["native_hex"])
    candidate = bytes.fromhex(r["candidate_hex"])
    te = r["target_instructions"][-1]
    ce = r["candidate_instructions"][-1]
    ends = (te["offset"] + te["size"], ce["offset"] + ce["size"])
    ni, ci = (
        decode(native, ends[0], r["target_instructions"]),
        decode(candidate, ends[1], r["candidate_instructions"]),
    )
    assert ni[-1].mnemonic == ci[-1].mnemonic == "ret"
    assert all(x in (0x90, 0xCC) for x in native[ends[0] :] + candidate[ends[1] :])
    reloc = {x["offset"]: x for x in r["relocations"]}
    consumed = set()
    fields = []
    for e in r["references"]["entries"]:
        assert e["status"] == "ok"
        a, b = ni[e["target_index"]], ci[e["candidate_index"]]
        assert (a.address, b.address) == (e["target_offset"], e["candidate_offset"])
        for tr, cr in zip(
            e["target_references"], e["candidate_references"], strict=True
        ):
            assert tr["explained"] and cr["explained"] and cr["source"] == "reloc"
            assert (tr["key"], tr["kind"], tr["operand_index"]) == (
                cr["key"],
                cr["kind"],
                cr["operand_index"],
            )
            f = "imm" if cr["kind"] == "imm" else "disp"
            ao, bo = getattr(a, f + "_offset"), getattr(b, f + "_offset")
            assert getattr(a, f + "_size") == getattr(b, f + "_size") == 4
            off = b.address + bo
            rr = reloc[off]
            assert rr["explained"] and rr["key"] == cr["key"]
            assert int.from_bytes(candidate[off : off + 4], "little") == rr[
                "addend"
            ] % (1 << 32)
            value = int.from_bytes(
                native[a.address + ao : a.address + ao + 4], "little"
            )
            if rr["relocation_type"] == 20:
                value = (
                    r["target_instructions"][0]["address"] + a.address + a.size + value
                ) % (1 << 32)
            else:
                assert rr["relocation_type"] == 6
            assert value == tr["value"]
            assert off not in consumed
            consumed.add(off)
            fields.append(
                (a.address + ao, off, e["target_index"], e["candidate_index"])
            )
    assert consumed == set(reloc) and len(consumed) == 37
    return native, candidate, ni, ci, ends, fields


def region(r, start, end, other, expected_differences=()):
    native, candidate, ni, ci, _ends, fields = audit_capture(r)
    n = {i.address: i for i in ni}
    c = {i.address: i for i in ci}
    assert start in n and end in n and other in c and other + end - start in c
    aa = bytearray(native[start:end])
    bb = bytearray(candidate[other : other + end - start])
    refs = 0
    branches = 0
    for no, co, _, _ in fields:
        if start <= no < end:
            assert co - other == no - start and no + 4 <= end
            aa[no - start : no - start + 4] = bb[co - other : co - other + 4] = bytes(4)
            refs += 1
        else:
            assert not other <= co < other + end - start
    differences = [
        (i, x, y) for i, (x, y) in enumerate(zip(aa, bb, strict=True)) if x != y
    ]
    assert differences == list(expected_differences), differences
    count = 0
    for off, ins in n.items():
        if not start <= off < end:
            continue
        cand = c[other + off - start]
        assert ins.size == cand.size
        count += 1
        if ins.group(capstone.CS_GRP_JUMP):
            assert ins.bytes == cand.bytes
            assert ins.operands[0].imm in n and cand.operands[0].imm in c
            assert ins.operands[0].imm - cand.operands[0].imm == start - other
            branches += 1
    return {
        "native": [start, end],
        "candidate": [other, other + end - start],
        "bytes": end - start,
        "instructions": count,
        "references": refs,
        "literal_branches": branches,
        "unequal_literal_bytes": differences,
    }


def verify(proof):
    before, after = proof["before"], proof["after"]
    b = audit_capture(before)
    a = audit_capture(after)
    assert b[0] == a[0] and len(b[1]) == len(a[1]) == 2688
    assert b[4] == (2759, 2676) and a[4] == (2759, 2680)
    assert len(b[3]) == len(a[3]) == 725
    bidx = {i.address: n for n, i in enumerate(b[3])}
    aidx = {i.address: n for n, i in enumerate(a[3])}
    branch_changes = []
    outside = []
    branches = 0
    sib_recovered = [288, 291, 293, 294, 295, 311, 315]
    for idx, (x, y) in enumerate(zip(b[3], a[3], strict=True)):
        if x.group(capstone.CS_GRP_JUMP):
            assert y.group(capstone.CS_GRP_JUMP)
            assert bidx[x.operands[0].imm] == aidx[y.operands[0].imm]
            assert x.mnemonic == y.mnemonic or (idx, x.mnemonic, y.mnemonic) == (
                153,
                "je",
                "jle",
            )
            branches += 1
            if x.bytes != y.bytes:
                branch_changes.append(idx)
            xb = (
                bytes(x.bytes[: x.imm_offset])
                + bytes(x.imm_size)
                + bytes(x.bytes[x.imm_offset + x.imm_size :])
            )
            yb = (
                bytes(y.bytes[: y.imm_offset])
                + bytes(y.imm_size)
                + bytes(y.bytes[y.imm_offset + y.imm_size :])
            )
        else:
            xb, yb = bytes(x.bytes), bytes(y.bytes)
        if idx in sib_recovered:
            assert y.bytes == a[2][idx + 1].bytes and x.bytes != y.bytes
            assert sum(u != v for u, v in zip(x.bytes, y.bytes, strict=True)) == 1
        elif not 126 <= idx < 154:
            assert xb == yb, (idx, x.mnemonic, x.op_str, y.mnemonic, y.op_str)
            outside.append(idx)
    for x, y in zip(before["relocations"], after["relocations"], strict=True):
        assert {k: v for k, v in x.items() if k != "offset"} == {
            k: v for k, v in y.items() if k != "offset"
        }
        assert y["offset"] == x["offset"] + (4 if x["offset"] >= 603 else 0)
    for x, y in zip(
        before["references"]["entries"], after["references"]["entries"], strict=True
    ):
        assert {
            k: v
            for k, v in x.items()
            if k not in ("candidate_offset", "candidate_address")
        } == {
            k: v
            for k, v in y.items()
            if k not in ("candidate_offset", "candidate_address")
        }
    # Finite counter domains and basis/identity choice agree on all iterations.
    old = [(i, j, j + 4, i - 1, j != 0) for j, i in enumerate(range(4, 20))]
    new = [(j + 4, j, j + 4, j + 3, j > 0) for j in range(16)]
    assert old == new
    return {
        "candidate_body_ends": [2676, 2680],
        "candidate_padding": [12, 8],
        "candidate_instructions": 725,
        "stable_outside_instructions": len(outside),
        "branches": branches,
        "branch_encoding_changes": branch_changes,
        "references": 37,
        "recovered_sib_instruction_indices": sib_recovered,
        "regions": [
            region(after, 6, 169, 3),
            region(after, 531, 645, 526, [(26, 23, 58), (48, 15, 57), (72, 23, 58)]),
            region(after, 2027, 2215, 1968),
        ],
    }


def main():
    proof = json.loads(RECEIPT.read_text())["proof"]
    result = verify(proof)
    for corruption in (
        "coordinate",
        "sib",
        "branch",
        "padding",
        "reference",
        "relocation",
    ):
        bad = copy.deepcopy(proof)
        if corruption == "reference":
            bad["after"]["references"]["entries"][0]["target_references"][0][
                "value"
            ] ^= 1
        elif corruption == "relocation":
            bad["after"]["relocations"][0]["addend"] ^= 1
        else:
            data = bytearray.fromhex(bad["after"]["candidate_hex"])
            off = {"coordinate": 527, "sib": 1174, "branch": 636, "padding": 2680}[
                corruption
            ]
            data[off] ^= 1
            bad["after"]["candidate_hex"] = data.hex()
        try:
            verify(bad)
        except (AssertionError, KeyError):
            pass
        else:
            raise AssertionError(f"Accepted {corruption} corruption")
    result["corruption_controls_rejected"] = 6
    print(json.dumps(result, indent=2))


if __name__ == "__main__":
    main()
