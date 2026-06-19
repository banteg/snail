from __future__ import annotations

from pathlib import Path
import struct

import pytest

from snail.match import (
    ClusterTotals,
    IDIOM_CASES_BY_NAME,
    ImageSection,
    LoadedImage,
    ObjectRelocationReference,
    ObjectFunction,
    ReferenceSymbol,
    ReferenceSymbolManifest,
    ScratchConfig,
    ScratchStatus,
    common_prefix_length,
    diff_regions,
    disassemble_normalized_function,
    extract_object_function,
    find_type_definitions,
    load_default_reference_symbol_manifest,
    load_image,
    load_reference_symbol_manifest,
    match_function,
    normalize_function,
    parse_coff_object,
    render_status_markdown,
    render_status_rows,
    render_status_table,
    resolve_function_extent,
    TypeConsolidationFinding,
    type_consolidation_findings,
)
from snail.symbols import (
    DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH,
    FunctionSymbol,
    FunctionSymbolManifest,
    REPO_ROOT,
    load_function_symbol_manifest,
)


def build_object(
    code: bytes,
    symbols: list[tuple[str, int]],
    relocations: list[int | tuple[int, int]],
) -> bytes:
    """Hand-pack a minimal i386 COFF object with one .text section."""
    section_count = 1
    relocation_records = [
        (item, 0) if isinstance(item, int) else item for item in relocations
    ]
    symbol_records = b""
    for name, value in symbols:
        symbol_records += struct.pack("<8sIhHBB", name.encode(), value, 1, 0x20, 2, 0)

    header_size = 20
    section_header_size = 40
    code_offset = header_size + section_header_size
    reloc_offset = code_offset + len(code)
    symtab_offset = reloc_offset + len(relocations) * 10

    header = struct.pack(
        "<HHIIIHH", 0x14C, section_count, 0, symtab_offset, len(symbols), 0, 0
    )
    section = struct.pack(
        "<8sIIIIIIHHI",
        b".text",
        0,
        0,
        len(code),
        code_offset,
        reloc_offset if relocations else 0,
        0,
        len(relocation_records),
        0,
        0x60000020,
    )
    reloc_records = b"".join(
        struct.pack("<IIH", address, symbol_index, 6)
        for address, symbol_index in relocation_records
    )
    string_table = struct.pack("<I", 4)
    return header + section + code + reloc_records + symbol_records + string_table


def test_parse_and_extract_object_function() -> None:
    # foo: mov eax, [esp+4]; ret    bar: xor eax, eax; ret
    code = bytes.fromhex("8b442404c3") + bytes.fromhex("31c0c3")
    obj = parse_coff_object(build_object(code, [("_foo", 0), ("_bar", 5)], []))
    foo = extract_object_function(obj, "foo")
    assert foo.name == "_foo"
    assert foo.data == bytes.fromhex("8b442404c3")
    bar = extract_object_function(obj, "bar")
    assert bar.data == bytes.fromhex("31c0c3")


def test_extract_object_function_collects_relocations() -> None:
    # mov eax, [0x0] (disp32 reloc at offset 1+1=2... a1 = mov eax, moffs32, disp at 1)
    code = bytes.fromhex("a100000000c3")
    obj = parse_coff_object(build_object(code, [("_foo", 0)], [1]))
    function = extract_object_function(obj, "foo")
    assert function.relocation_offsets == frozenset({1})


def test_extract_object_function_records_relocation_symbols() -> None:
    # call external-ish symbol; ret; callee: ret
    code = bytes.fromhex("e800000000c3c3")
    obj = parse_coff_object(build_object(code, [("_foo", 0), ("_callee", 6)], [(1, 1)]))
    function = extract_object_function(obj, "foo")
    assert function.relocation_references[0].offset == 1
    assert function.relocation_references[0].symbol_name == "_callee"
    assert function.relocation_references[0].key == "name:callee"


def test_normalize_masks_relocated_and_absolute_operands() -> None:
    # mov eax, [0x004a1234]; ret
    code = bytes.fromhex("a134124a00c3")
    masked_by_reloc = normalize_function(code, relocation_offsets=frozenset({1}))
    assert masked_by_reloc[0] == "mov eax, dword [ADDR]"
    masked_by_range = normalize_function(code, address_range=(0x400000, 0x500000))
    assert masked_by_range[0] == "mov eax, dword [ADDR]"
    unmasked = normalize_function(code)
    assert unmasked[0] == "mov eax, dword [0x4a1234]"


def test_normalize_masks_candidate_immediates_in_image_range() -> None:
    # push 0x400802; ret. Some widget flag literals fall inside the image VA
    # range, so candidate objects must normalize them the same way as the image
    # side without requiring fake relocation symbols in scratches.
    code = bytes.fromhex("6802084000c3")
    masked_by_range = normalize_function(code, address_range=(0x400000, 0x500000))
    assert masked_by_range[0] == "push ADDR"
    unmasked = normalize_function(code)
    assert unmasked[0] == "push 0x400802"


def test_normalize_labels_intra_function_branches() -> None:
    # jz +2 (to the ret); xor eax, eax; ret
    code = bytes.fromhex("7402") + bytes.fromhex("31c0") + bytes.fromhex("c3")
    lines = normalize_function(code)
    assert lines[0] == "je L4"
    # the label is stable regardless of load address
    rebased = normalize_function(code, base_address=0x445F00)
    assert rebased[0] == "je L4"


def test_normalize_keeps_struct_offsets_exact() -> None:
    # mov [ecx+0x14], 1
    code = bytes.fromhex("c741140100000090")
    lines = normalize_function(code)
    assert lines[0] == "mov dword [ecx+0x14], 0x1"


def test_common_prefix_length() -> None:
    assert common_prefix_length(("push ebp", "mov ebp, esp"), ("push ebp", "ret")) == 1
    assert common_prefix_length(("push ebp",), ("push ebp", "ret")) == 1
    assert common_prefix_length((), ("ret",)) == 0


def test_match_function_reports_prefix_and_first_mismatch() -> None:
    # target: push ebp; mov ebp, esp; xor eax, eax; ret
    target = bytes.fromhex("558bec31c0c3")
    # candidate: push ebp; mov ebp, esp; mov eax, 1; ret
    candidate = ObjectFunction(
        name="_foo",
        data=bytes.fromhex("558becb801000000c3"),
        relocation_offsets=frozenset(),
    )
    result = match_function(
        target,
        candidate,
        image=LoadedImage(mapped=b"", image_base=0x400000, size_of_image=0),
        target_va=0x401000,
    )
    assert result.prefix_instructions == 2
    assert result.first_target_mismatch == "xor eax, eax"
    assert result.first_candidate_mismatch == "mov eax, 0x1"


def test_match_function_reports_end_mismatch_for_short_candidate() -> None:
    # target: push ebp; ret    candidate: push ebp
    target = bytes.fromhex("55c3")
    candidate = ObjectFunction(
        name="_foo",
        data=bytes.fromhex("55"),
        relocation_offsets=frozenset(),
    )
    result = match_function(
        target,
        candidate,
        image=LoadedImage(mapped=b"", image_base=0x400000, size_of_image=0),
        target_va=0x401000,
    )
    assert result.prefix_instructions == 1
    assert result.first_target_mismatch == "ret"
    assert result.first_candidate_mismatch is None


def tiny_manifest() -> FunctionSymbolManifest:
    return FunctionSymbolManifest(
        name="test",
        primary_target="test.exe",
        reference_target="test.exe",
        image_base=0x401000,
        unwrapped_sha256="0" * 64,
        source_database=None,
        functions=(FunctionSymbol(address=0x401010, name="right_helper"),),
    )


def tiny_reference_manifest() -> ReferenceSymbolManifest:
    return ReferenceSymbolManifest(
        name="test references",
        symbols=(
            ReferenceSymbol(
                address=0x402000,
                name="g_game_base",
                kind="global",
                aliases=("g_app",),
            ),
        ),
    )


def test_default_reference_symbol_manifest_loads_curated_gameplay_refs() -> None:
    manifest = load_default_reference_symbol_manifest()
    by_name = {symbol.name: symbol for symbol in manifest.symbols}
    assert by_name["g_game_base"].address == 0x4DF904
    assert "g_app" in by_name["g_game_base"].aliases
    assert by_name["ftol"].kind == "function"
    assert by_name["g_math_random_table"].size == 0x7FFC


def test_reference_symbol_manifest_allows_duplicate_addresses(tmp_path: Path) -> None:
    manifest_path = tmp_path / "references.json"
    manifest_path.write_text(
        """
{
  "name": "duplicate address references",
  "symbols": [
    {
      "address": "0x402000",
      "name": "g_table_base",
      "kind": "offset"
    },
    {
      "address": "0x402000",
      "name": "foo_static_guard",
      "kind": "global",
      "aliases": [
        "?$S1@?1??foo@@4EA"
      ]
    }
  ]
}
""",
        encoding="utf-8",
    )
    manifest = load_reference_symbol_manifest(manifest_path)
    assert [symbol.name for symbol in manifest.symbols] == [
        "g_table_base",
        "foo_static_guard",
    ]


def relocated_candidate(symbol_name: str, key: str) -> ObjectFunction:
    return ObjectFunction(
        name="_foo",
        data=bytes.fromhex("e800000000c3"),
        relocation_offsets=frozenset({1}),
        relocation_references=(
            ObjectRelocationReference(
                offset=1,
                symbol_name=symbol_name,
                text=f"sym:{key.removeprefix('name:')}",
                key=key,
                explained=True,
            ),
        ),
    )


def test_masked_operand_audit_accepts_matching_callee_reference() -> None:
    # target: call 0x401010; ret. candidate: call relocated right_helper; ret.
    target = bytes.fromhex("e80b000000c3")
    result = match_function(
        target,
        relocated_candidate("_right_helper", "name:right_helper"),
        image=LoadedImage(mapped=b"\x00" * 0x2000, image_base=0x401000, size_of_image=0x2000),
        target_va=0x401000,
        manifest=tiny_manifest(),
    )
    assert result.ratio == 1.0
    assert result.masked_operand_audit.ok_count == 1
    assert result.masked_operand_audit.problem_count == 0


def test_masked_operand_audit_flags_wrong_callee_reference() -> None:
    target = bytes.fromhex("e80b000000c3")
    result = match_function(
        target,
        relocated_candidate("_wrong_helper", "name:wrong_helper"),
        image=LoadedImage(mapped=b"\x00" * 0x2000, image_base=0x401000, size_of_image=0x2000),
        target_va=0x401000,
        manifest=tiny_manifest(),
    )
    assert result.ratio == 1.0
    assert result.masked_operand_audit.mismatch_count == 1
    entry = result.masked_operand_audit.entries[0]
    assert entry.status == "mismatch"
    assert entry.target_references[0].text == "fn:right_helper@0x401010"
    assert entry.candidate_references[0].text == "sym:wrong_helper"


def test_masked_operand_audit_flags_unresolved_target_reference() -> None:
    # target: push 0x402000; ret. The image address has no function/string name,
    # so a matching ADDR shape against a candidate symbol is not proof-grade.
    target = bytes.fromhex("6800204000c3")
    candidate = ObjectFunction(
        name="_foo",
        data=bytes.fromhex("6800000000c3"),
        relocation_offsets=frozenset({1}),
        relocation_references=(
            ObjectRelocationReference(
                offset=1,
                symbol_name="_g_state",
                text="sym:g_state",
                key="name:g_state",
                explained=True,
            ),
        ),
    )
    result = match_function(
        target,
        candidate,
        image=LoadedImage(mapped=b"\x00" * 0x3000, image_base=0x400000, size_of_image=0x3000),
        target_va=0x401000,
    )
    assert result.ratio == 1.0
    assert result.masked_operand_audit.unresolved_count == 1
    assert (
        result.masked_operand_audit.entries[0].target_references[0].text
        == "image+0x2000@0x402000"
    )


def test_masked_operand_audit_accepts_matching_string_with_newline() -> None:
    mapped = bytearray(b"\x00" * 0x3000)
    mapped[0x2000 : 0x2006] = b"line\n\x00"
    target = bytes.fromhex("6800204000c3")
    candidate = ObjectFunction(
        name="_foo",
        data=bytes.fromhex("6800000000c3"),
        relocation_offsets=frozenset({1}),
        relocation_references=(
            ObjectRelocationReference(
                offset=1,
                symbol_name="??_C@line",
                text='str:"line\\n"',
                key="str:line\n",
                explained=True,
            ),
        ),
    )
    result = match_function(
        target,
        candidate,
        image=LoadedImage(mapped=bytes(mapped), image_base=0x400000, size_of_image=0x3000),
        target_va=0x401000,
    )
    assert result.ratio == 1.0
    assert result.masked_operand_audit.ok_count == 1
    assert result.masked_operand_audit.problem_count == 0
    assert (
        result.masked_operand_audit.entries[0].target_references[0].text
        == 'str:"line\\n"@0x402000'
    )


def test_extract_object_function_maps_reference_symbol_aliases() -> None:
    code = bytes.fromhex("a100000000c3")
    obj = parse_coff_object(build_object(code, [("_foo", 0), ("_g_app", 0)], [(1, 1)]))
    function = extract_object_function(
        obj,
        "foo",
        reference_manifest=tiny_reference_manifest(),
    )
    assert function.relocation_references[0].text == "sym:g_app"
    assert function.relocation_references[0].key == "ref:g_game_base"


def test_extract_object_function_preserves_reference_symbol_addends() -> None:
    code = bytes.fromhex("b808000000c3")
    obj = parse_coff_object(build_object(code, [("_foo", 0), ("_g_table", 0)], [(1, 1)]))
    function = extract_object_function(
        obj,
        "foo",
        reference_manifest=ReferenceSymbolManifest(
            name="test references",
            symbols=(
                ReferenceSymbol(
                    address=0x402000,
                    name="g_table",
                    kind="global",
                    size=0x10,
                ),
            ),
        ),
    )
    reference = function.relocation_references[0]
    assert reference.addend == 0x8
    assert reference.text == "sym:g_table+0x8"
    assert reference.key == "ref:g_table+0x8"
    assert reference.explained


def test_masked_operand_audit_accepts_reference_symbol_aliases() -> None:
    # target: mov eax, [0x402000]; ret. candidate: mov eax, [relocated g_app]; ret.
    target = bytes.fromhex("a100204000c3")
    candidate = ObjectFunction(
        name="_foo",
        data=bytes.fromhex("a100000000c3"),
        relocation_offsets=frozenset({1}),
        relocation_references=(
            ObjectRelocationReference(
                offset=1,
                symbol_name="_g_app",
                text="sym:g_app",
                key="ref:g_game_base",
                explained=True,
            ),
        ),
    )
    result = match_function(
        target,
        candidate,
        image=LoadedImage(mapped=b"\x00" * 0x3000, image_base=0x400000, size_of_image=0x3000),
        target_va=0x401000,
        reference_manifest=tiny_reference_manifest(),
    )
    assert result.ratio == 1.0
    assert result.masked_operand_audit.ok_count == 1
    assert result.masked_operand_audit.problem_count == 0


def test_masked_operand_audit_leaves_local_jump_table_label_unresolved() -> None:
    # target: jmp dword [eax*4+0x402000]; candidate: same shape through a
    # compiler-local switch-table label. VC6 may renumber that local label after
    # unrelated source/header changes.
    target = bytes.fromhex("ff248500204000c3")
    candidate = ObjectFunction(
        name="_foo",
        data=bytes.fromhex("ff248500000000c3"),
        relocation_offsets=frozenset({3}),
        relocation_references=(
            ObjectRelocationReference(
                offset=3,
                symbol_name="$L123",
                text="sym:$L123",
                key="name:$L123",
                explained=True,
            ),
        ),
    )
    result = match_function(
        target,
        candidate,
        image=LoadedImage(mapped=b"\x00" * 0x3000, image_base=0x400000, size_of_image=0x3000),
        target_va=0x401000,
        reference_manifest=ReferenceSymbolManifest(
            name="test references",
            symbols=(
                ReferenceSymbol(
                    address=0x402000,
                    name="foo_jump_table",
                    kind="jump_table",
                ),
            ),
        ),
    )
    assert result.ratio == 1.0
    assert result.masked_operand_audit.ok_count == 0
    assert result.masked_operand_audit.unresolved_count == 1
    assert result.masked_operand_audit.problem_count == 1
    entry = result.masked_operand_audit.entries[0]
    assert entry.status == "unresolved"
    assert entry.target_references[0].text == "jump_table:foo_jump_table@0x402000"
    assert entry.candidate_references[0].text == "sym:$L123"


def test_masked_operand_audit_accepts_same_address_reference_alternate() -> None:
    # target: mov cl, [0x402000]; ret. 0x402000 is the display name for one
    # global, but the candidate relocation can still honestly name a separate
    # compiler-emitted static guard at the same address.
    target = bytes.fromhex("8a0d00204000c3")
    candidate = ObjectFunction(
        name="_foo",
        data=bytes.fromhex("8a0d00000000c3"),
        relocation_offsets=frozenset({2}),
        relocation_references=(
            ObjectRelocationReference(
                offset=2,
                symbol_name="?$S1@?1??foo@@4EA",
                text="sym:?$S1@?1??foo@@4EA",
                key="ref:foo_static_guard",
                explained=True,
            ),
        ),
    )
    result = match_function(
        target,
        candidate,
        image=LoadedImage(mapped=b"\x00" * 0x3000, image_base=0x400000, size_of_image=0x3000),
        target_va=0x401000,
        reference_manifest=ReferenceSymbolManifest(
            name="test references",
            symbols=(
                ReferenceSymbol(
                    address=0x402000,
                    name="g_table_base",
                    kind="offset",
                ),
                ReferenceSymbol(
                    address=0x402000,
                    name="foo_static_guard",
                    kind="global",
                    aliases=("?$S1@?1??foo@@4EA",),
                ),
            ),
        ),
    )
    reference = result.masked_operand_audit.entries[0].target_references[0]
    assert reference.key == "ref:g_table_base"
    assert reference.alternate_keys == ("ref:foo_static_guard",)
    assert result.masked_operand_audit.ok_count == 1
    assert result.masked_operand_audit.problem_count == 0


def test_reference_symbol_overrides_same_address_function_symbol() -> None:
    # Game-base-relative data offsets can numerically collide with code VAs in
    # the stripped image. A curated reference entry should keep those operands
    # from resolving as unrelated functions.
    target = bytes.fromhex("8d8810104000c3")  # lea ecx, [eax+0x401010]; ret
    candidate = ObjectFunction(
        name="_foo",
        data=bytes.fromhex("8d8800000000c3"),
        relocation_offsets=frozenset({2}),
        relocation_references=(
            ObjectRelocationReference(
                offset=2,
                symbol_name="_g_squidge_offset",
                text="sym:g_squidge_offset",
                key="ref:g_squidge_offset",
                explained=True,
            ),
        ),
    )
    result = match_function(
        target,
        candidate,
        image=LoadedImage(mapped=b"\x00" * 0x3000, image_base=0x400000, size_of_image=0x3000),
        target_va=0x401000,
        manifest=tiny_manifest(),
        reference_manifest=ReferenceSymbolManifest(
            name="test references",
            symbols=(
                ReferenceSymbol(
                    address=0x401010,
                    name="g_squidge_offset",
                    kind="offset",
                    aliases=("unrelated_function_name",),
                ),
            ),
        ),
    )
    reference = result.masked_operand_audit.entries[0].target_references[0]
    assert reference.text == "offset:g_squidge_offset@0x401010"
    assert result.masked_operand_audit.ok_count == 1
    assert result.masked_operand_audit.problem_count == 0


def test_masked_operand_audit_accepts_sized_reference_end_addend() -> None:
    # target: cmp esi, 0x402010; ret. 0x402010 is also the next global, but the
    # candidate relocation is explicitly g_table + 0x10.
    target = bytes.fromhex("81fe10204000c3")
    candidate = ObjectFunction(
        name="_foo",
        data=bytes.fromhex("81fe10000000c3"),
        relocation_offsets=frozenset({2}),
        relocation_references=(
            ObjectRelocationReference(
                offset=2,
                symbol_name="_g_table",
                text="sym:g_table+0x10",
                key="ref:g_table+0x10",
                explained=True,
                addend=0x10,
            ),
        ),
    )
    result = match_function(
        target,
        candidate,
        image=LoadedImage(mapped=b"\x00" * 0x3000, image_base=0x400000, size_of_image=0x3000),
        target_va=0x401000,
        reference_manifest=ReferenceSymbolManifest(
            name="test references",
            symbols=(
                ReferenceSymbol(
                    address=0x402000,
                    name="g_table",
                    kind="global",
                    size=0x10,
                ),
                ReferenceSymbol(
                    address=0x402010,
                    name="g_next_global",
                    kind="global",
                ),
            ),
        ),
    )
    reference = result.masked_operand_audit.entries[0].target_references[0]
    assert reference.key == "ref:g_next_global"
    assert reference.alternate_keys == ("ref:g_table+0x10",)
    assert result.masked_operand_audit.ok_count == 1
    assert result.masked_operand_audit.problem_count == 0


def test_masked_operand_audit_does_not_treat_sized_reference_base_as_end() -> None:
    target = bytes.fromhex("81fe10204000c3")
    candidate = ObjectFunction(
        name="_foo",
        data=bytes.fromhex("81fe00000000c3"),
        relocation_offsets=frozenset({2}),
        relocation_references=(
            ObjectRelocationReference(
                offset=2,
                symbol_name="_g_table",
                text="sym:g_table",
                key="ref:g_table",
                explained=True,
                addend=0,
            ),
        ),
    )
    result = match_function(
        target,
        candidate,
        image=LoadedImage(mapped=b"\x00" * 0x3000, image_base=0x400000, size_of_image=0x3000),
        target_va=0x401000,
        reference_manifest=ReferenceSymbolManifest(
            name="test references",
            symbols=(
                ReferenceSymbol(
                    address=0x402000,
                    name="g_table",
                    kind="global",
                    size=0x10,
                ),
                ReferenceSymbol(
                    address=0x402010,
                    name="g_next_global",
                    kind="global",
                ),
            ),
        ),
    )
    assert result.masked_operand_audit.mismatch_count == 1


def test_masked_operand_audit_accepts_matching_rdata_constants() -> None:
    mapped = bytearray(b"\x00" * 0x3000)
    struct.pack_into("<f", mapped, 0x2000, 1.0)
    target = bytes.fromhex("d80d00204000c3")  # fmul dword [0x402000]; ret
    candidate = ObjectFunction(
        name="_foo",
        data=bytes.fromhex("d80d00000000c3"),
        relocation_offsets=frozenset({2}),
        relocation_references=(
            ObjectRelocationReference(
                offset=2,
                symbol_name="real@4@3fff8000000000000000",
                text="const:f32:1",
                key="const:f32:3f800000",
                explained=True,
            ),
        ),
    )
    result = match_function(
        target,
        candidate,
        image=LoadedImage(
            mapped=bytes(mapped),
            image_base=0x400000,
            size_of_image=0x3000,
            sections=(ImageSection(".rdata", 0x402000, 0x402004, 0),),
        ),
        target_va=0x401000,
    )
    assert result.ratio == 1.0
    assert result.masked_operand_audit.ok_count == 1
    assert result.masked_operand_audit.problem_count == 0


def test_x87_rdata_float_takes_priority_over_printable_bytes() -> None:
    mapped = bytearray(b"\x00" * 0x3000)
    struct.pack_into("<f", mapped, 0x2000, 0.7)
    target = bytes.fromhex("d80d00204000c3")  # fmul dword [0x402000]; ret
    candidate = ObjectFunction(
        name="_foo",
        data=bytes.fromhex("d80d00000000c3"),
        relocation_offsets=frozenset({2}),
        relocation_references=(
            ObjectRelocationReference(
                offset=2,
                symbol_name="real@4@3ffe99999a0000000000",
                text="const:f32:0.699999988",
                key="const:f32:3f333333",
                explained=True,
            ),
        ),
    )
    result = match_function(
        target,
        candidate,
        image=LoadedImage(
            mapped=bytes(mapped),
            image_base=0x400000,
            size_of_image=0x3000,
            sections=(ImageSection(".rdata", 0x402000, 0x402004, 0),),
        ),
        target_va=0x401000,
    )
    reference = result.masked_operand_audit.entries[0].target_references[0]
    assert reference.text == "const:f32:0.699999988@0x402000"
    assert result.masked_operand_audit.ok_count == 1
    assert result.masked_operand_audit.problem_count == 0


def test_rdata_image_pointer_is_not_reported_as_string_or_float() -> None:
    mapped = bytearray(b"\x00" * 0x3000)
    struct.pack_into("<I", mapped, 0x2000, 0x401000)
    lines = disassemble_normalized_function(
        bytes.fromhex("b800204000c3"),  # mov eax, 0x402000; ret
        address_range=(0x400000, 0x403000),
        base_address=0x401000,
        image=LoadedImage(
            mapped=bytes(mapped),
            image_base=0x400000,
            size_of_image=0x3000,
            sections=(ImageSection(".rdata", 0x402000, 0x402004, 0),),
        ),
    )
    reference = lines[0].masked_references[0]
    assert reference.text == "image+0x2000@0x402000"
    assert reference.key == "addr:0x402000"
    assert not reference.explained


def test_diff_regions_reports_localized_mismatch() -> None:
    target = bytes.fromhex("558bec31c040c3")  # push; mov; xor; inc; ret
    candidate = ObjectFunction(
        name="_foo",
        data=bytes.fromhex("558becb80100000040c3"),  # push; mov; mov; inc; ret
        relocation_offsets=frozenset(),
    )
    result = match_function(
        target,
        candidate,
        image=LoadedImage(mapped=b"", image_base=0x400000, size_of_image=0),
        target_va=0x401000,
    )
    regions = diff_regions(result, context=1)
    assert len(regions) == 1
    assert regions[0].target_span == "1:4"
    assert regions[0].candidate_span == "1:4"
    assert regions[0].changed_target_instructions == 1
    assert regions[0].changed_candidate_instructions == 1


def test_idiom_case_registry_contains_bitfield_probe() -> None:
    case = IDIOM_CASES_BY_NAME["bitfield-stride6-set"]
    assert "completed" in case.source
    assert case.symbol == "probe"


def test_find_type_definitions_and_consolidation_findings(tmp_path: Path) -> None:
    match_root = tmp_path / "match"
    include_dir = match_root / "include"
    include_dir.mkdir(parents=True)
    scratches = match_root / "scratches"
    (scratches / "a").mkdir(parents=True)
    (scratches / "b").mkdir()
    (scratches / "c").mkdir()
    (scratches / "a" / "scratch.cpp").write_text("struct Shared { int x; };\n")
    (scratches / "b" / "scratch.cpp").write_text("struct Shared { int x; };\n")
    (scratches / "c" / "scratch.cpp").write_text("struct Divergent { int x; };\n")
    (scratches / "d").mkdir()
    (scratches / "d" / "scratch.cpp").write_text("struct Divergent { float x; };\n")
    (include_dir / "covered.h").write_text("struct Covered { int x; };\n")
    (scratches / "e").mkdir()
    (scratches / "e" / "scratch.cpp").write_text("struct Covered { int x; };\n")

    definitions = find_type_definitions(scratches / "a" / "scratch.cpp")
    assert [(definition.kind, definition.name) for definition in definitions] == [
        ("struct", "Shared")
    ]

    findings = {finding.name: finding for finding in type_consolidation_findings(match_root)}
    assert findings["Shared"].status == "ready"
    assert findings["Divergent"].status == "divergent"
    assert findings["Covered"].status == "covered"

    filtered = type_consolidation_findings(match_root, names={"Shared", "Missing"})
    assert [finding.name for finding in filtered] == ["Shared"]


def test_render_status_rows_includes_prefix() -> None:
    config = ScratchConfig(
        directory=Path("scratch"),
        function="foo",
        compiler="msvc6.5",
        cflags="/O2 /G5 /W3",
        end_va=None,
        symbol=None,
    )
    status = ScratchStatus(
        config=config,
        address=0x401000,
        target_size=10,
        ratio=0.5,
        prefix_instructions=2,
        target_instructions=4,
        candidate_instructions=5,
        error=None,
    )
    assert render_status_rows([status])[0][6] == "2/4"


def test_render_status_rows_include_missing_manifest_functions() -> None:
    config = ScratchConfig(
        directory=Path("scratch/exact"),
        function="exact",
        compiler="msvc6.5",
        cflags="/O2 /G5 /W3",
        end_va=None,
        symbol=None,
    )
    status = ScratchStatus(
        config=config,
        address=0x1000,
        target_size=2,
        ratio=1.0,
        prefix_instructions=2,
        target_instructions=2,
        candidate_instructions=2,
        error=None,
    )
    manifest = FunctionSymbolManifest(
        name="test",
        primary_target="test.exe",
        reference_target="test.exe",
        image_base=0x1000,
        unwrapped_sha256="0" * 64,
        source_database=None,
        functions=(
            FunctionSymbol(address=0x1000, name="exact"),
            FunctionSymbol(address=0x1002, name="missing"),
        ),
    )
    image = LoadedImage(
        mapped=b"\x90\xc3\x90\xc3\xcc",
        image_base=0x1000,
        size_of_image=5,
    )

    rows = render_status_rows([status], manifest=manifest, image=image)

    assert rows[1] == (
        "⬜",
        "missing",
        "0x1002",
        "2",
        "0/2",
        "0.00%",
        "0/2",
        "-",
        "",
        "no scratch",
    )

    totals = ClusterTotals(
        function_count=2,
        byte_total=4,
        matched_functions=1,
        matched_bytes=2,
        scratched_functions=1,
        fuzzy_weighted_bytes=2.0,
    )
    markdown = render_status_markdown([status], totals, manifest=manifest, image=image)
    assert "| ⬜ | missing | 0x1002 | 2 | 0/2 | 0.00% | 0/2 | - |  |" in markdown


def test_render_status_markdown_splits_progress_sections() -> None:
    def make_status(name: str, address: int, ratio: float) -> ScratchStatus:
        config = ScratchConfig(
            directory=Path(f"scratch/{name}"),
            function=name,
            compiler="msvc6.5",
            cflags="/O2 /G5 /W3",
            end_va=None,
            symbol=None,
        )
        return ScratchStatus(
            config=config,
            address=address,
            target_size=16,
            ratio=ratio,
            prefix_instructions=0,
            target_instructions=4,
            candidate_instructions=4,
            error=None,
        )

    statuses = [
        make_status("near", 0x1000, 0.95),
        make_status("high", 0x1010, 0.80),
        make_status("mid", 0x1020, 0.50),
        make_status("early", 0x1030, 0.25),
        make_status("zero", 0x1040, 0.0),
    ]
    manifest = FunctionSymbolManifest(
        name="test",
        primary_target="test.exe",
        reference_target="test.exe",
        image_base=0x1000,
        unwrapped_sha256="0" * 64,
        source_database=None,
        functions=(
            FunctionSymbol(address=0x1000, name="near"),
            FunctionSymbol(address=0x1010, name="high"),
            FunctionSymbol(address=0x1020, name="mid"),
            FunctionSymbol(address=0x1030, name="early"),
            FunctionSymbol(address=0x1040, name="zero"),
            FunctionSymbol(address=0x1050, name="missing"),
        ),
    )
    image = LoadedImage(
        mapped=(b"\xc3" * 0x60) + b"\xcc",
        image_base=0x1000,
        size_of_image=0x61,
    )
    totals = ClusterTotals(
        function_count=6,
        byte_total=96,
        matched_functions=0,
        matched_bytes=0,
        scratched_functions=5,
        fuzzy_weighted_bytes=40.0,
    )

    markdown = render_status_markdown(statuses, totals, manifest=manifest, image=image)

    assert "## Near Match (95-99.99%) (1)" in markdown
    assert "## High Progress (80-94.99%) (1)" in markdown
    assert "## Mid Progress (50-79.99%) (1)" in markdown
    assert "## Early Progress (>0-49.99%) (1)" in markdown
    assert "## Zero Match (0%) (1)" in markdown
    assert "## No Scratch (0%) (1)" in markdown


def test_render_status_outputs_scratch_and_fuzzy_summary() -> None:
    exact_config = ScratchConfig(
        directory=Path("scratch/exact"),
        function="exact",
        compiler="msvc6.5",
        cflags="/O2 /G5 /W3",
        end_va=None,
        symbol=None,
    )
    wip_config = ScratchConfig(
        directory=Path("scratch/wip"),
        function="wip",
        compiler="msvc6.5",
        cflags="/O2 /G5 /W3",
        end_va=None,
        symbol=None,
    )
    statuses = [
        ScratchStatus(
            config=exact_config,
            address=0x401000,
            target_size=20,
            ratio=1.0,
            prefix_instructions=4,
            target_instructions=4,
            candidate_instructions=4,
            error=None,
        ),
        ScratchStatus(
            config=wip_config,
            address=0x401100,
            target_size=40,
            ratio=0.5,
            prefix_instructions=2,
            target_instructions=4,
            candidate_instructions=5,
            error=None,
        ),
    ]
    totals = ClusterTotals(
        function_count=4,
        byte_total=100,
        matched_functions=1,
        matched_bytes=20,
        scratched_functions=2,
        fuzzy_weighted_bytes=40.0,
    )

    assert totals.scratch_percentage == pytest.approx(0.5)
    assert totals.fuzzy_percentage == pytest.approx(0.4)

    status_table = render_status_table(statuses, totals)
    assert "1/4 functions proof-grade" in status_table
    assert "2/4 functions have scratches" in status_table
    assert "overall fuzzy 40.00%" in status_table
    assert "1/2 scratches at proof-grade 100%" in status_table

    markdown = render_status_markdown(statuses, totals)
    assert "**2/4** mapped gameplay functions have a scratch" in markdown
    assert "overall fuzzy is **40.00%**" in markdown
    assert "Byte totals are curated-extent upper bounds" not in markdown


def test_render_status_outputs_type_consolidation_summary() -> None:
    config = ScratchConfig(
        directory=Path("scratch"),
        function="foo",
        compiler="msvc6.5",
        cflags="/O2 /G5 /W3",
        end_va=None,
        symbol=None,
    )
    status = ScratchStatus(
        config=config,
        address=0x401000,
        target_size=10,
        ratio=1.0,
        prefix_instructions=4,
        target_instructions=4,
        candidate_instructions=4,
        error=None,
    )
    totals = ClusterTotals(
        function_count=1,
        byte_total=10,
        matched_functions=1,
        matched_bytes=10,
        scratched_functions=1,
        fuzzy_weighted_bytes=10.0,
    )
    findings = [
        TypeConsolidationFinding(
            name="Game",
            status="divergent",
            scratch_count=5,
            header_count=0,
            signature_count=3,
            paths=(),
            recommendation="same name has multiple scratch-local shapes; do not consolidate yet",
        ),
        TypeConsolidationFinding(
            name="Player",
            status="covered",
            scratch_count=4,
            header_count=1,
            signature_count=2,
            paths=(),
            recommendation="header exists; consider replacing matching scratch-local copies with includes",
        ),
        TypeConsolidationFinding(
            name="BodNode",
            status="ready",
            scratch_count=2,
            header_count=0,
            signature_count=1,
            paths=(),
            recommendation="same scratch-local definition appears repeatedly; consider a header",
        ),
    ]
    findings.extend(
        TypeConsolidationFinding(
            name=f"GameVariant{index}",
            status="divergent",
            scratch_count=2,
            header_count=0,
            signature_count=2,
            paths=(),
            recommendation="same name has multiple scratch-local shapes; do not consolidate yet",
        )
        for index in range(7)
    )

    status_table = render_status_table([status], totals, type_findings=findings)
    assert "types: 1 ready, 1 covered, 8 divergent" in status_table

    markdown = render_status_markdown([status], totals, type_findings=findings)
    assert "## Type Consolidation" in markdown
    assert "| divergent | Game | 5 | 0 | 3 |" in markdown
    assert "| divergent | GameVariant6 | 2 | 0 | 2 |" in markdown
    assert "more divergent finding(s)" not in markdown
    assert "`uv run snail match types --paths`" in markdown


MANIFEST_AVAILABLE = DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH.exists()


@pytest.mark.skipif(not MANIFEST_AVAILABLE, reason="symbol manifest not available")
def test_resolve_function_extent_uses_next_curated_function() -> None:
    manifest = load_function_symbol_manifest(DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH)
    start, end = resolve_function_extent(manifest, "change_snail_skin")
    assert start == 0x445FD0
    assert end == 0x446020
    assert resolve_function_extent(manifest, "change_snail_skin", 0x446000) == (
        0x445FD0,
        0x446000,
    )


SCRATCH_OBJ = REPO_ROOT / "tools/match/scratches/change_snail_skin/build/scratch.obj"
IMAGE_AVAILABLE = MANIFEST_AVAILABLE and (
    REPO_ROOT / "artifacts/bin/SnailMail_unwrapped.exe"
).exists()


@pytest.mark.skipif(
    not (IMAGE_AVAILABLE and SCRATCH_OBJ.exists()),
    reason="game image or compiled scratch not available",
)
def test_change_snail_skin_scratch_matches_image() -> None:
    manifest = load_function_symbol_manifest(DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH)
    obj = parse_coff_object(SCRATCH_OBJ.read_bytes())
    candidate = extract_object_function(obj, "change_snail_skin")
    start, end = resolve_function_extent(manifest, "change_snail_skin")
    image = load_image(REPO_ROOT / Path(manifest.primary_target), manifest.image_base)
    result = match_function(
        image.function_bytes(start, end),
        candidate,
        image=image,
        target_va=start,
    )
    assert result.ratio == 1.0


def test_normalize_masks_relocated_call_targets() -> None:
    # call rel32 (reloc at offset 1, zero displacement lands in-function); ret
    code = bytes.fromhex("e800000000") + bytes.fromhex("c3")
    relocated = normalize_function(code, relocation_offsets=frozenset({1}))
    assert relocated[0] == "call ADDR"
    relocated_dump = disassemble_normalized_function(code, relocation_offsets=frozenset({1}))
    assert relocated_dump[0].offset == 0
    assert relocated_dump[0].address == 0
    assert relocated_dump[0].text == "call ADDR"
    assert relocated_dump[1].offset == 5
    assert relocated_dump[1].text == "ret"
    # without a relocation the same encoding is an intra-function branch
    plain = normalize_function(code)
    assert plain[0] == "call L5"


def test_normalize_strips_untargeted_terminal_padding() -> None:
    code = bytes.fromhex("c3") + bytes.fromhex("8d4900") + (b"\x00" * 4) + (b"\x90" * 4)
    assert normalize_function(code) == ("ret",)


def test_normalize_strips_untargeted_terminal_data_after_ret() -> None:
    code = bytes.fromhex("c3") + bytes.fromhex("b8ad0039c341")
    assert normalize_function(code) == ("ret",)


def test_normalize_strips_tail_that_decodes_to_ret() -> None:
    code = bytes.fromhex("5bc3c2394380ad0043")
    assert normalize_function(code) == ("pop ebx", "ret")


def test_normalize_keeps_targeted_terminal_padding() -> None:
    # jmp targets the trailing nop, so it is code from the matcher perspective.
    code = bytes.fromhex("eb01") + bytes.fromhex("c3") + bytes.fromhex("90")
    assert normalize_function(code) == ("jmp L3", "ret", "nop")


def test_validate_scratch_source_rejects_inline_asm(tmp_path: Path) -> None:
    from snail.match import validate_scratch_source

    clean = tmp_path / "clean.cpp"
    clean.write_text("void f() { int x = 1; }\n")
    validate_scratch_source(clean)

    for token in ("__asm { mov eax, 1 }", "_asm mov eax, 1", "__declspec(naked)"):
        dirty = tmp_path / "dirty.cpp"
        dirty.write_text(f"void f() {{ {token} }}\n")
        with pytest.raises(ValueError, match="fakematching"):
            validate_scratch_source(dirty)


def test_load_scratch_config_rejects_match_args(tmp_path: Path) -> None:
    from snail.match import load_scratch_config

    scratch_dir = tmp_path / "scratch"
    scratch_dir.mkdir()
    (scratch_dir / "scratch.conf").write_text('FUNCTION=foo MATCH_ARGS="--end 0x401000"\n')

    with pytest.raises(ValueError, match="MATCH_ARGS is not supported"):
        load_scratch_config(scratch_dir)


def test_scratch_status_cache_roundtrip(tmp_path: Path) -> None:
    from snail.match import ScratchConfig, _load_cached_status, _store_cached_status

    match_root = tmp_path / "match"
    scratch_dir = match_root / "scratches/foo"
    scratch_dir.mkdir(parents=True)
    include_dir = match_root / "include"
    include_dir.mkdir()
    header = include_dir / "shared.h"
    header.write_text("struct Shared { int x; };\n")
    (scratch_dir / "scratch.cpp").write_text("// candidate\n")
    (scratch_dir / "scratch.conf").write_text("FUNCTION=foo\n")
    image = tmp_path / "image.exe"
    image.write_bytes(b"MZ")
    config = ScratchConfig(
        directory=scratch_dir,
        function="foo",
        compiler="msvc6.5",
        cflags="/O2 /G5 /W3",
        end_va=None,
        symbol=None,
    )

    assert _load_cached_status(config, image, match_root) is None
    fields = {
        "target_size": 10,
        "ratio": 1.0,
        "prefix_instructions": 4,
        "target_instructions": 4,
        "candidate_instructions": 4,
        "masked_ok": 0,
        "masked_unresolved": 0,
        "masked_mismatches": 0,
        "error": None,
    }
    _store_cached_status(config, image, fields, match_root)
    assert _load_cached_status(config, image, match_root) == fields

    changed_flags = ScratchConfig(
        directory=scratch_dir,
        function="foo",
        compiler="msvc6.5",
        cflags="/Od /G5 /W3",
        end_va=None,
        symbol=None,
    )
    assert _load_cached_status(changed_flags, image, match_root) is None

    changed_compiler = ScratchConfig(
        directory=scratch_dir,
        function="foo",
        compiler="msvc6.0",
        cflags="/O2 /G5 /W3",
        end_va=None,
        symbol=None,
    )
    assert _load_cached_status(changed_compiler, image, match_root) is None

    # editing the source or a shared include invalidates the cache
    import os
    import time

    stamp = time.time() + 10
    os.utime(scratch_dir / "scratch.cpp", (stamp, stamp))
    assert _load_cached_status(config, image, match_root) is None

    _store_cached_status(config, image, fields, match_root)
    stamp += 10
    os.utime(scratch_dir / "scratch.conf", (stamp, stamp))
    assert _load_cached_status(config, image, match_root) is None

    _store_cached_status(config, image, fields, match_root)
    stamp += 10
    os.utime(header, (stamp, stamp))
    assert _load_cached_status(config, image, match_root) is None


def test_scratch_object_current_tracks_build_inputs(tmp_path: Path) -> None:
    from snail.match import (
        ScratchConfig,
        _scratch_object_is_current,
        _store_scratch_build_key,
    )

    import os
    import time

    match_root = tmp_path / "match"
    scratch_dir = match_root / "scratches/foo"
    build_dir = scratch_dir / "build"
    include_dir = match_root / "include"
    compiler_dir = match_root / "compilers/msvc6.5/Bin"
    build_dir.mkdir(parents=True)
    include_dir.mkdir()
    compiler_dir.mkdir(parents=True)
    (match_root / "cl.sh").write_text("#!/bin/sh\n")
    (compiler_dir / "CL.EXE").write_bytes(b"cl")
    (scratch_dir / "scratch.cpp").write_text("// candidate\n")
    (scratch_dir / "scratch.conf").write_text("FUNCTION=foo\n")
    header = include_dir / "shared.h"
    header.write_text("struct Shared { int x; };\n")
    obj_path = build_dir / "scratch.obj"
    obj_path.write_bytes(b"obj")
    config = ScratchConfig(
        directory=scratch_dir,
        function="foo",
        compiler="msvc6.5",
        cflags="/O2 /G5 /W3",
        end_va=None,
        symbol=None,
    )

    base = time.time() + 10
    for path in (
        match_root / "cl.sh",
        compiler_dir / "CL.EXE",
        scratch_dir / "scratch.cpp",
        scratch_dir / "scratch.conf",
        header,
    ):
        os.utime(path, (base, base))
    os.utime(obj_path, (base + 10, base + 10))
    assert not _scratch_object_is_current(obj_path, config, match_root)

    _store_scratch_build_key(obj_path, config, match_root)
    assert _scratch_object_is_current(obj_path, config, match_root)

    changed_flags = ScratchConfig(
        directory=scratch_dir,
        function="foo",
        compiler="msvc6.5",
        cflags="/Od /G5 /W3",
        end_va=None,
        symbol=None,
    )
    assert not _scratch_object_is_current(obj_path, changed_flags, match_root)

    os.utime(header, (base + 20, base + 20))
    assert not _scratch_object_is_current(obj_path, config, match_root)

    os.utime(header, (base, base))
    os.utime(scratch_dir / "scratch.conf", (base + 20, base + 20))
    assert not _scratch_object_is_current(obj_path, config, match_root)
