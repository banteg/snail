from __future__ import annotations

from pathlib import Path
import struct

import pytest

from snail.match import (
    IDIOM_CASES_BY_NAME,
    LoadedImage,
    ObjectFunction,
    ScratchConfig,
    ScratchStatus,
    common_prefix_length,
    diff_regions,
    disassemble_normalized_function,
    extract_object_function,
    find_type_definitions,
    load_image,
    match_function,
    normalize_function,
    parse_coff_object,
    render_status_rows,
    resolve_function_extent,
    type_consolidation_findings,
)
from snail.symbols import (
    DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH,
    REPO_ROOT,
    load_function_symbol_manifest,
)


def build_object(code: bytes, symbols: list[tuple[str, int]], relocations: list[int]) -> bytes:
    """Hand-pack a minimal i386 COFF object with one .text section."""
    section_count = 1
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
        len(relocations),
        0,
        0x60000020,
    )
    reloc_records = b"".join(
        struct.pack("<IIH", address, 0, 6) for address in relocations
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


def test_scratch_status_cache_roundtrip(tmp_path: Path) -> None:
    from snail.match import ScratchConfig, _load_cached_status, _store_cached_status

    scratch_dir = tmp_path / "scratch"
    scratch_dir.mkdir()
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

    assert _load_cached_status(config, image) is None
    fields = {
        "target_size": 10,
        "ratio": 1.0,
        "target_instructions": 4,
        "candidate_instructions": 4,
        "error": None,
    }
    _store_cached_status(config, image, fields)
    assert _load_cached_status(config, image) == fields

    # editing the source invalidates the cache
    import os
    import time

    stamp = time.time() + 10
    os.utime(scratch_dir / "scratch.cpp", (stamp, stamp))
    assert _load_cached_status(config, image) is None
