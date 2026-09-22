"""Check the unpromoted survival-parcel prefix and cursor-ownership diagnostic."""

import argparse
import concurrent.futures
import copy
import hashlib
import json
from pathlib import Path

import capstone
from replay_four_builder_controls_20260912 import reconstruct

ROOT = Path(__file__).resolve().parents[2]
RECEIPT = Path(__file__).with_name("survival-projection-owners-20260922.json")
FUNCTION = "place_challenge_parcels_on_track"
PREFIX_END = 401
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
md.detail = True


def decode(data, records):
    end = records[-1]["offset"] + records[-1]["size"]
    instructions = list(md.disasm(data[:end], 0))
    assert [(i.address, i.size) for i in instructions] == [
        (i["offset"], i["size"]) for i in records
    ]
    assert instructions[-1].mnemonic == "ret"
    assert all(b in (0x90, 0xCC) for b in data[end:])
    return instructions, end


def verify(receipt):
    baseline = receipt["baselines"][FUNCTION]
    assert (
        hashlib.sha256(baseline["source"].encode()).hexdigest()
        == baseline["source_sha256"]
    )
    for control in receipt["controls"]:
        reconstruct(baseline["source"], control)
        assert control["measured"]["error"] is None
        assert control["measured"]["body_byte_exact"] is False
    selected = next(
        c
        for c in receipt["controls"]
        if c["batch"] == "projection-operation"
        and c["label"] == "reference-borrow-field-indexed"
    )
    r = receipt["proof"]["diagnostic"]
    before = receipt["proof"]["baseline"]
    assert r["native_hex"] == before["native_hex"]
    for key in (
        "code_sha256",
        "body_byte_exact",
        "match_ratio",
        "references",
        "candidate_instructions",
        "prefix_instructions",
    ):
        assert r["measured"][key] == selected["measured"][key]
    assert r["measured"]["body_byte_exact"] is False
    assert r["measured"]["references"] == {
        "ok": 33,
        "unresolved": 0,
        "mismatch": 1,
        "unaudited": 0,
    }
    native, candidate = (
        bytes.fromhex(r["native_hex"]),
        bytes.fromhex(r["candidate_hex"]),
    )
    ni, ne = decode(native, r["target_instructions"])
    ci, ce = decode(candidate, r["candidate_instructions"])
    assert len(ni) == 171 and len(ci) == 170
    assert ne == 617 and len(native) == 624
    assert ni[108].address == ci[108].address == PREFIX_END
    assert [(i.address, i.size) for i in ni[:108]] == [
        (i.address, i.size) for i in ci[:108]
    ]
    a, b = bytearray(native[:PREFIX_END]), bytearray(candidate[:PREFIX_END])
    relocations = {e["offset"]: e for e in r["relocations"]}
    consumed = set()
    literal_fields = 0
    for entry in r["references"]["entries"]:
        if entry["target_index"] >= 108:
            continue
        assert entry["status"] == "ok"
        assert entry["target_index"] == entry["candidate_index"]
        x, y = ni[entry["target_index"]], ci[entry["candidate_index"]]
        assert x.address == entry["target_offset"] == entry["candidate_offset"]
        for tr, cr in zip(
            entry["target_references"], entry["candidate_references"], strict=True
        ):
            assert tr["explained"] and cr["explained"]
            assert (tr["key"], tr["kind"], tr["operand_index"]) == (
                cr["key"],
                cr["kind"],
                cr["operand_index"],
            )
            field = "imm" if tr["kind"] == "imm" else "disp"
            offset = x.address + getattr(x, field + "_offset")
            assert offset == y.address + getattr(y, field + "_offset")
            assert getattr(x, field + "_size") == getattr(y, field + "_size") == 4
            if cr["source"] == "image":
                # These are numeric member displacements that happen to fall
                # within the image address range. Never mask their bytes.
                assert offset not in relocations
                value = int.from_bytes(a[offset : offset + 4], "little")
                assert value == tr["value"] == cr["value"]
                assert a[offset : offset + 4] == b[offset : offset + 4]
                literal_fields += 1
                continue
            assert cr["source"] == "reloc"
            rr = relocations[offset]
            assert rr["explained"] and rr["key"] == cr["key"]
            assert int.from_bytes(b[offset : offset + 4], "little") == rr["addend"] % (
                1 << 32
            )
            value = int.from_bytes(a[offset : offset + 4], "little")
            if rr["relocation_type"] == 20:
                value = (
                    value + r["target_instructions"][0]["address"] + x.address + x.size
                ) % (1 << 32)
            else:
                assert rr["relocation_type"] == 6
            assert value == tr["value"]
            assert offset not in consumed
            consumed.add(offset)
            a[offset : offset + 4] = b[offset : offset + 4] = bytes(4)
    assert consumed == {offset for offset in relocations if offset < PREFIX_END}
    assert len(consumed) == 17 and literal_fields == 11
    assert a == b
    branches = 0
    starts = {i.address for i in ni[:108]}
    for x, y in zip(ni[:108], ci[:108], strict=True):
        if x.group(capstone.CS_GRP_JUMP):
            assert x.bytes == y.bytes
            assert x.operands[0].imm == y.operands[0].imm
            assert x.operands[0].imm in starts
            branches += 1
    # The first excluded branch differs literally. The exact-prefix claim
    # stops before it, rather than masking a changed local destination.
    assert ni[108].mnemonic == ci[108].mnemonic == "jle"
    assert ni[108].bytes != ci[108].bytes
    # Both instructions derive a cursor from the SubGame receiver in EBP.
    for ins in (ni[109], ci[109]):
        assert ins.mnemonic == "lea" and ins.reg_name(ins.operands[0].reg) == "esi"
        assert ins.reg_name(ins.operands[1].mem.base) == "ebp"
        assert ins.operands[1].mem.index == 0
    assert ni[109].operands[1].mem.disp == 0x5CCAC8
    assert ci[109].operands[1].mem.disp == 0x5CCB58
    # The following flags read demonstrates the same effective row address,
    # while retaining both unequal instruction encodings in the residual.
    assert ni[110].operands[1].mem.disp == 0
    assert ci[110].operands[1].mem.disp == -0x90
    assert ni[110].bytes != ci[110].bytes
    return {
        "prefix_bytes": PREFIX_END,
        "prefix_instructions": 108,
        "positional_relocations": len(consumed),
        "unmasked_numeric_fields": literal_fields,
        "literal_branches": branches,
        "native_body_bytes": ne,
        "candidate_body_bytes": ce,
        "native_padding_bytes": len(native) - ne,
        "candidate_padding_bytes": len(candidate) - ce,
        "projection_cursor_shift": 0x90,
        "body_byte_exact": False,
    }


def replay(receipt):
    from snail import match

    for name, expected in receipt["build_inputs"].items():
        assert hashlib.sha256((ROOT / name).read_bytes()).hexdigest() == expected, name
    config = match.load_scratch_config(ROOT / "tools/match/scratches" / FUNCTION)
    keys = (
        "code_sha256",
        "body_byte_exact",
        "match_ratio",
        "references",
        "error",
        "candidate_instructions",
        "target_instructions",
        "prefix_instructions",
        "compiler",
        "cflags",
    )

    def one(control):
        source = reconstruct(receipt["baselines"][FUNCTION]["source"], control)
        result = match.scratch_status_payload(
            match.evaluate_source_overlay(config, source)
        )
        assert {k: result[k] for k in keys} == {
            k: control["measured"][k] for k in keys
        }, (control["batch"], control["label"])

    with concurrent.futures.ThreadPoolExecutor(max_workers=6) as pool:
        list(pool.map(one, receipt["controls"]))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--replay", action="store_true")
    args = parser.parse_args()
    receipt = json.loads(RECEIPT.read_text())
    result = verify(receipt)
    for corruption in (
        "frame",
        "numeric-field",
        "origin",
        "padding",
        "reference",
        "relocation",
        "claim",
    ):
        bad = copy.deepcopy(receipt)
        r = bad["proof"]["diagnostic"]
        if corruption in ("frame", "numeric-field", "origin", "padding"):
            data = bytearray.fromhex(r["candidate_hex"])
            index = {
                "frame": 2,
                "numeric-field": 98,
                "origin": 409,
                "padding": len(data) - 1,
            }[corruption]
            data[index] ^= 4
            r["candidate_hex"] = data.hex()
        elif corruption == "reference":
            r["references"]["entries"][0]["target_references"][0]["value"] += 4
        elif corruption == "relocation":
            r["relocations"][0]["addend"] += 4
        else:
            r["measured"]["body_byte_exact"] = True
        try:
            verify(bad)
        except (AssertionError, KeyError):
            continue
        raise AssertionError(f"Accepted corruption: {corruption}")
    if args.replay:
        replay(receipt)
        result["replayed_controls"] = len(receipt["controls"])
    result["rejected_corruptions"] = 7
    print(json.dumps(result, indent=2))


if __name__ == "__main__":
    main()
