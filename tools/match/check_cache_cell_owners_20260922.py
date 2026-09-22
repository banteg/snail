"""Independently audit the complete cache builder, including its inline table."""

import argparse
import copy
import hashlib
import json
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

import capstone
import pefile
from replay_four_builder_controls_20260912 import reconstruct

ROOT = Path(__file__).resolve().parents[2]
RECEIPT = Path(__file__).with_name("cache-cell-owners-20260922.json")
ADDRESS = 0x433220
CODE_END = 1532
BODY_END = 1552
DESTINATIONS = [1439, 1449, 1459, 1469, 1479]
# Native instruction offset, operand, kind, identity and independently resolved VA.
REFERENCES = [
    (13, 0, "imm", "ref:noop_this_constructor", 0x44DB50),
    (25, 0, "imm", "ref:pack_color_rgba_u8", 0x44DBF0),
    (40, 0, "imm", "name:noop_runtime_ai", 0x407B50),
    (149, 0, "disp", "const:f32:41c00000", 0x497530),
    (297, 0, "imm", "name:append_track_cache_object", 0x433960),
    (451, 0, "imm", "name:append_track_cache_object", 0x433960),
    (496, 0, "imm", "ref:is_sub_loc_floor", 0x439A40),
    (606, 0, "imm", "name:append_track_cache_object", 0x433960),
    (655, 0, "imm", "ref:is_sub_loc_slide", 0x439AD0),
    (763, 0, "imm", "name:append_track_cache_object", 0x433960),
    (809, 0, "imm", "ref:is_sub_loc_ramp", 0x439A70),
    (901, 0, "imm", "name:append_track_cache_object", 0x433960),
    (1432, 0, "disp", "ref:build_track_render_caches_cache_name_jump_table", 0x43381C),
    (1439, 1, "imm", "str:Floor", 0x4A49BC),
    (1449, 1, "imm", "str:Slide", 0x4A49B4),
    (1459, 1, "imm", "str:Warn", 0x4A49AC),
    (1469, 1, "imm", "str:Ramp", 0x4A49A4),
    (1479, 1, "imm", "str:Fringe", 0x4A499C),
    (1494, 0, "imm", "str:Max Cache Type=%s Vertices=%i   Indices=%i\n", 0x4A4970),
    (1499, 0, "imm", "ref:debug_report_stub", 0x449C00),
]


def sha(data):
    return hashlib.sha256(data).hexdigest()


def verify(capture):
    native = bytes.fromhex(capture["native_hex"])
    candidate = bytes.fromhex(capture["candidate_hex"])
    assert len(native) == len(candidate) == BODY_END
    status = capture["measured"]
    assert status["address"] == ADDRESS
    assert status["compared_target_ranges"] == [[0, BODY_END]]
    assert status["excluded_target_ranges"] == status["unexplained_target_ranges"] == []
    assert status["target_inline_data_ranges"] == [[CODE_END, BODY_END]]
    assert status["candidate_inline_data_ranges"] == [[CODE_END, BODY_END]]
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    target = {i.address: i for i in md.disasm(native[:CODE_END], 0)}
    compiled = {i.address: i for i in md.disasm(candidate[:CODE_END], 0)}
    assert len(target) == len(compiled) == 476
    assert status["target_instructions"] == status["candidate_instructions"] == 476
    assert [(i.address, i.size) for i in target.values()] == [
        (i.address, i.size) for i in compiled.values()
    ]
    assert max(i.address + i.size for i in target.values()) == CODE_END
    assert max(i.address + i.size for i in compiled.values()) == CODE_END
    # The alignment NOP before the table is included, not discarded as padding.
    assert native[1531] == candidate[1531] == 0x90
    positions = {off: index for index, off in enumerate(target)}
    relocs = {r["offset"]: r for r in capture["relocations"]}
    assert len(relocs) == len(capture["relocations"]) == 25
    left, right = bytearray(native), bytearray(candidate)
    consumed = set()
    masks = []
    for entry, expected in zip(
        capture["references"]["entries"], REFERENCES, strict=True
    ):
        off, operand, field, key, value = expected
        assert entry["status"] == "ok"
        assert entry["target_offset"] == entry["candidate_offset"] == off
        assert entry["target_index"] == entry["candidate_index"] == positions[off]
        assert (
            len(entry["target_references"]) == len(entry["candidate_references"]) == 1
        )
        tr, cr = entry["target_references"][0], entry["candidate_references"][0]
        assert tr["explained"] and cr["explained"]
        assert tr["source"] == "image" and cr["source"] == "reloc"
        assert tr["operand_index"] == cr["operand_index"] == operand
        assert tr["kind"] == cr["kind"] == field
        assert tr["key"] == key and tr["value"] == value
        a, b = target[off], compiled[off]
        ao, bo = getattr(a, field + "_offset"), getattr(b, field + "_offset")
        assert ao == bo
        assert getattr(a, field + "_size") == getattr(b, field + "_size") == 4
        fixup = off + ao
        r = relocs[fixup]
        assert r["explained"] and r["key"] == cr["key"]
        assert r["addend"] == 0
        assert int.from_bytes(candidate[fixup : fixup + 4], "little") == r["addend"]
        encoded = int.from_bytes(native[fixup : fixup + 4], "little")
        if a.mnemonic == "call":
            assert r["relocation_type"] == 20
            encoded = (ADDRESS + off + a.size + encoded) % (1 << 32)
        else:
            assert r["relocation_type"] == 6
        assert encoded == value
        if off == 1432:
            assert r["symbol_offset"] == CODE_END and r["symbol_size"] == 20
            assert tr["jump_table_entries"] == cr["jump_table_entries"] == DESTINATIONS
            assert bytes.fromhex(r["symbol_data"]) == candidate[CODE_END:]
            mem = a.operands[0].mem
            assert a.mnemonic == b.mnemonic == "jmp"
            assert mem.base == 0 and mem.index == capstone.x86.X86_REG_ESI
            assert mem.scale == 4
        else:
            assert cr["key"] == key and r["symbol_offset"] is None
        assert fixup not in consumed
        consumed.add(fixup)
        masks.append([fixup, fixup + 4])
        left[fixup : fixup + 4] = right[fixup : fixup + 4] = bytes(4)
    for off, destination in zip(
        range(CODE_END, BODY_END, 4), DESTINATIONS, strict=True
    ):
        r = relocs[off]
        assert r["explained"] and r["relocation_type"] == 6 and r["addend"] == 0
        assert int.from_bytes(candidate[off : off + 4], "little") == 0
        assert r["symbol_offset"] == destination
        assert int.from_bytes(native[off : off + 4], "little") - ADDRESS == destination
        assert destination in target and destination in compiled
        assert (
            bytes.fromhex(r["symbol_data"])
            == candidate[destination : destination + r["symbol_size"]]
        )
        left[off : off + 4] = right[off : off + 4] = destination.to_bytes(4, "little")
        consumed.add(off)
    assert consumed == set(relocs)
    branches = []
    for off, insn in target.items():
        if insn.group(capstone.CS_GRP_JUMP):
            if insn.operands[0].type != capstone.x86.X86_OP_IMM:
                assert off == 1432  # Already audited the sole indirect dispatch.
                continue
            other = compiled[off]
            assert insn.bytes == other.bytes
            assert insn.operands[0].imm == other.operands[0].imm
            assert insn.operands[0].imm in target and other.operands[0].imm in compiled
            branches.append(off)
    assert left == right
    assert status["body_byte_exact"] is True
    return {
        "body_bytes": BODY_END,
        "code_bytes": CODE_END,
        "inline_table_bytes": BODY_END - CODE_END,
        "excluded_bytes": 0,
        "instructions": len(target),
        "positional_reference_instructions": len(REFERENCES),
        "audited_relocations": len(consumed),
        "literal_local_branches": len(branches),
        "jump_table_destinations": DESTINATIONS,
        "masked_relocation_ranges": masks,
        "relocation_audited_sha256": sha(left),
        "body_byte_exact": True,
    }


def reject_corruptions(capture, expected):
    cases = (
        "body",
        "sib",
        "reference",
        "addend",
        "table",
        "destination",
        "branch",
        "alignment",
        "claim",
    )
    for case in cases:
        bad = copy.deepcopy(capture)
        if case == "reference":
            bad["references"]["entries"][0]["target_references"][0]["value"] ^= 1
        elif case == "addend":
            bad["relocations"][0]["addend"] ^= 1
        elif case == "destination":
            bad["relocations"][20]["symbol_offset"] = DESTINATIONS[1]
        elif case == "claim":
            bad["measured"]["body_byte_exact"] = False
        else:
            data = bytearray.fromhex(bad["candidate_hex"])
            off = {
                "body": 20,
                "sib": 287,
                "table": 1532,
                "branch": 61,
                "alignment": 1531,
            }[case]
            data[off] ^= 1
            bad["candidate_hex"] = data.hex()
        try:
            assert verify(bad) == expected
        except (AssertionError, KeyError):
            pass
        else:
            raise AssertionError(f"Accepted corrupt {case}")
    return len(cases)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--replay-all", action="store_true")
    args = parser.parse_args()
    receipt = json.loads(RECEIPT.read_text())
    for path, digest in receipt["build_inputs"].items():
        assert sha((ROOT / path).read_bytes()) == digest, path
    name = "build_track_render_caches"
    canonical = ROOT / "tools/match/scratches" / name / "scratch.cpp"
    assert sha(canonical.read_bytes()) == receipt["canonical_source_sha256"]
    baseline = receipt["baselines"][name]
    assert sha(baseline["source"].encode()) == baseline["source_sha256"]
    sources = [reconstruct(baseline["source"], c) for c in receipt["controls"]]
    before, after = receipt["baseline"], receipt["retained"]
    assert before["native_hex"] == after["native_hex"]
    assert before["measured"]["body_byte_exact"] is False
    old, new = (
        bytes.fromhex(before["candidate_hex"]),
        bytes.fromhex(after["candidate_hex"]),
    )
    assert len(old) == len(new)
    assert [
        (i, a, b) for i, (a, b) in enumerate(zip(old, new, strict=True)) if a != b
    ] == [(287, 0x38, 0x07)]
    image = pefile.PE(str(ROOT / receipt["native_image"]), fast_load=True)
    image_base = image.OPTIONAL_HEADER.ImageBase
    assert image.get_data(ADDRESS - image_base, BODY_END) == bytes.fromhex(
        after["native_hex"]
    )
    for _, _, _, key, value in REFERENCES:
        if key.startswith("str:"):
            literal = key.removeprefix("str:").encode() + b"\x00"
            assert image.get_data(value - image_base, len(literal)) == literal
        elif key.startswith("const:"):
            assert image.get_data(value - image_base, 4) == bytes.fromhex("0000c041")
    result = verify(after)
    assert result == receipt["expected"]
    print(json.dumps(result, sort_keys=True))
    print(
        f"Rejected {reject_corruptions(after, result)} corruptions; reconstructed {len(sources)} controls"
    )
    if args.replay_all:
        from snail import match

        config = match.load_scratch_config(canonical.parent)
        keys = (
            "state",
            "body_byte_exact",
            "code_sha256",
            "match_ratio",
            "target_instructions",
            "candidate_instructions",
            "prefix_instructions",
            "references",
            "compiler",
            "cflags",
            "error",
        )

        def replay(item):
            control, source = item
            actual = match.scratch_status_payload(
                match.evaluate_source_overlay(config, source)
            )
            changes = {
                key: (control["measured"][key], actual[key])
                for key in keys
                if control["measured"][key] != actual[key]
            }
            assert not changes, (control["batch"], control["label"], changes)

        with ThreadPoolExecutor(max_workers=6) as pool:
            list(pool.map(replay, zip(receipt["controls"], sources, strict=True)))
        print(f"All {len(sources)} controls replay")


if __name__ == "__main__":
    main()
