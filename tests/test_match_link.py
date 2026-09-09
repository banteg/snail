import struct
from types import SimpleNamespace

import pytest

from snail.match import (
    CoffObject,
    CoffRelocation,
    CoffSection,
    CoffSymbol,
    parse_coff_object,
)
from snail.match_link import (
    LinkSymbols,
    externalize_coff_function,
    verify_code_sections,
    verify_data_sections,
    verify_relocated_bytes,
    verify_runtime_control,
)

BASE = 0x400000


def two_function_object(*, interior_reference=False):
    """Independent i386 COFF fixture: peer calls the first function."""
    code = b"\xb8\x01\0\0\0\xc3\x90\x90" + b"\xe8\0\0\0\0\xc3\x90\x90"
    symbol_count = 3 if interior_reference else 2
    header = struct.pack("<HHIIIHH", 0x14C, 2, 0, 126, symbol_count, 0, 0)
    sections = b"".join(
        struct.pack("<8sIIIIIIHHI", b".text", 0, 0, 8, 100 + i * 8,
                    116 if i else 0, 0, int(bool(i)), 0, 0x60501020)
        for i in range(2)
    )
    relocation = struct.pack("<IIH", 1, 2 if interior_reference else 0, 0x14)
    symbols = struct.pack("<8sIhHBB", b"_swap", 0, 1, 0x20, 2, 0)
    symbols += struct.pack("<8sIhHBB", b"_peer", 0, 2, 0x20, 2, 0)
    if interior_reference:
        symbols += struct.pack("<8sIhHBB", b"_inner", 4, 1, 0, 3, 0)
    return header + sections + code + relocation + symbols + struct.pack("<I", 4)


def test_externalized_function_preserves_peer_code_and_call_symbol():
    original = two_function_object()
    transformed = externalize_coff_function(original, "_swap")
    before = parse_coff_object(original)
    after = parse_coff_object(transformed)
    assert after.sections[0].characteristics & 0x800
    assert not after.sections[0].characteristics & 0x1000
    assert after.sections[0].data == before.sections[0].data
    assert after.sections[1] == before.sections[1]
    assert after.symbols[0].name == "_swap"
    assert after.symbols[0].section_number == 0
    assert after.symbols[0].raw_index == 0
    assert after.symbols[1] == before.symbols[1]
    assert after.sections[1].relocations[0].symbol_index == after.symbols[0].raw_index
    changed = {i for i, (a, b) in enumerate(zip(original, transformed, strict=True)) if a != b}
    assert changed <= {*range(56, 60), *range(134, 140)}


def test_externalization_rejects_peer_reference_to_function_interior():
    with pytest.raises(ValueError, match="another symbol"):
        externalize_coff_function(two_function_object(interior_reference=True), "_swap")


def test_externalization_rejects_shared_function_section():
    data = bytearray(two_function_object())
    struct.pack_into("<Ih", data, 126 + 18 + 8, 4, 1)
    with pytest.raises(ValueError, match="dedicated function section"):
        externalize_coff_function(bytes(data), "_swap")


def test_externalization_rejects_missing_or_already_external_function():
    original = two_function_object()
    with pytest.raises(ValueError, match="one defined function"):
        externalize_coff_function(original, "_absent")
    once = externalize_coff_function(original, "_swap")
    with pytest.raises(ValueError, match="one defined function"):
        externalize_coff_function(once, "_swap")


@pytest.mark.parametrize("negative", [False, True])
def test_runtime_control_requires_exact_assertion_outcomes(negative):
    failures = int(negative)
    output = ("FAIL: deliberate corruption\n" if negative else "")
    output += f"rtext checks=22 failures={failures}\n"
    expected = {"expected_checks": 22, "expected_failures": failures}
    assert verify_runtime_control("rtext", output, failures, **expected) == {
        "checks": 22, "failures": failures,
    }
    with pytest.raises(ValueError, match="expected checks"):
        verify_runtime_control("rtext", output, 1 - failures, **expected)
    with pytest.raises(ValueError, match="expected checks"):
        verify_runtime_control("rtext", output.replace("checks=22", "checks=21"), failures, **expected)
    with pytest.raises(ValueError, match="one complete summary"):
        verify_runtime_control("rtext", output + output, failures, **expected)


def test_negative_control_rejects_collateral_failures_and_inconsistent_logs():
    expected = {"expected_checks": 22, "expected_failures": 1}
    for output in (
        "FAIL: deliberate corruption\nFAIL: unrelated regression\nrtext checks=22 failures=2\n",
        "FAIL: deliberate corruption\nFAIL: hidden regression\nrtext checks=22 failures=1\n",
        "rtext checks=22 failures=1\n",
    ):
        with pytest.raises(ValueError, match="expected checks"):
            verify_runtime_control("rtext", output, 1, **expected)
    for output in (
        "rtext checks=22 failures=1garbage\n",
        "prefix rtext checks=22 failures=1\n",
        "another-group checks=22 failures=1\n",
    ):
        with pytest.raises(ValueError, match="one complete summary"):
            verify_runtime_control("rtext", output, 1, **expected)


def linked_symbols(entries, map_rows="", *, section_size=0x100, characteristics=0xC0):
    """Build a COFF debug table independently of the source-object fixtures."""
    strings = bytearray(4)
    records = bytearray()
    for name, rva, storage in entries:
        encoded = name.encode("latin1") + b"\0"
        offset = len(strings)
        strings.extend(encoded)
        records.extend(struct.pack("<IIIhHBB", 0, offset, rva, 1, 0, storage, 0))
    struct.pack_into("<I", strings, 0, len(strings))
    image = bytes(32) + records + strings
    pe = SimpleNamespace(
        OPTIONAL_HEADER=SimpleNamespace(ImageBase=BASE),
        FILE_HEADER=SimpleNamespace(PointerToSymbolTable=32, NumberOfSymbols=len(entries)),
        sections=[SimpleNamespace(
            VirtualAddress=0x1000, Misc_VirtualSize=section_size,
            SizeOfRawData=section_size, Characteristics=characteristics, Name=b".data\0\0\0",
        )],
    )
    return LinkSymbols(image, pe, map_rows)


def symbol(name, *, storage=2, value=0, section=1, index=0):
    return CoffSymbol(index, name, value, section, 0, storage)


def object_with(data, symbols, relocations=(), *, bss=False):
    return CoffObject(
        (CoffSection(".bss" if bss else ".data", data, 0x80 if bss else 0x40, relocations),),
        tuple(symbols),
    )


def test_map_requires_matching_coff_symbol_and_decodes_linker_octal_names():
    symbols = linked_symbols(
        [("\x7fimport", 0x1000, 2)],
        " 0001:00000000 \\177import 00401000 library:member\n",
    )
    assert symbols.resolve("\x7fimport", "library:member") == BASE + 0x1000
    for row in (
        " 0001:00000000 _missing 00401000 source.obj\n",
        " 0001:00000000 _value 00401004 source.obj\n",
    ):
        with pytest.raises(ValueError, match="map/COFF symbol disagreement"):
            linked_symbols([("_value", 0x1000, 2)], row)


def test_static_symbols_use_map_owner_to_disambiguate_duplicate_names():
    symbols = linked_symbols(
        [("_local", 0x1000, 3), ("_local", 0x1020, 3)],
        " 0001:00000000 _local 00401000 first.obj\n"
        " 0001:00000020 _local 00401020 second.obj\n",
    )
    local = symbol("_local", storage=3)
    assert symbols.resolve_symbol(local, "first.obj") == BASE + 0x1000
    assert symbols.resolve_symbol(local, "second.obj") == BASE + 0x1020
    with pytest.raises(ValueError, match="static owner"):
        symbols.resolve_symbol(local, "absent.obj")


def test_mapless_static_requires_unique_source_owner_and_static_coff_class():
    local = symbol("_local", storage=3)
    obj = object_with(bytes(4), [local])
    symbols = linked_symbols([("_local", 0x1000, 3)])
    with pytest.raises(ValueError, match="static owner"):
        symbols.resolve_symbol(local, "first.obj")
    symbols.bind_objects({"first.obj": obj})
    assert symbols.resolve_symbol(local, "first.obj") == BASE + 0x1000
    symbols.bind_objects({"first.obj": obj, "second.obj": obj})
    with pytest.raises(ValueError, match="static owner"):
        symbols.resolve_symbol(local, "first.obj")
    symbols.bind_objects({"first.obj": obj})
    with pytest.raises(ValueError, match="static owner"):
        symbols.resolve_symbol(local, "first.obj")
    external = linked_symbols([("_local", 0x1000, 2)])
    external.bind_objects({"first.obj": obj})
    with pytest.raises(ValueError, match="linked static"):
        external.resolve_symbol(local, "first.obj")


def test_static_cannot_borrow_another_objects_map_owner():
    symbols = linked_symbols(
        [("_local", 0x1000, 3)],
        " 0001:00000000 _local 00401000 other.obj\n",
    )
    local = symbol("_local", storage=3)
    symbols.bind_objects({"source.obj": object_with(bytes(4), [local])})
    with pytest.raises(ValueError, match="static owner"):
        symbols.resolve_symbol(local, "source.obj")


def test_external_relocation_can_resolve_runtime_library_symbol():
    symbols = linked_symbols(
        [("_runtime", 0x1020, 2)],
        " 0001:00000020 _runtime 00401020 runtime:member\n",
    )
    source = object_with(bytes(4), [symbol("_runtime", section=0)])
    relocations = (CoffRelocation(0, 0, 0x14),)
    evidence = verify_relocated_bytes(
        bytes(4), struct.pack("<i", 0x1C), BASE + 0x1000,
        relocations, source, symbols, "source.obj",
    )
    assert evidence[0]["address"] == BASE + 0x1020


@pytest.mark.parametrize("relocation_type", [0x06, 0x14])
def test_relocation_addends_verified_and_wrong_destination_rejected(relocation_type):
    symbols = linked_symbols([("_target", 0x1080, 2)])
    original = b"abcd" + struct.pack("<i", -4) + b"efgh"
    source = object_with(original, [symbol("_target", section=0)])
    relocation = (CoffRelocation(4, 0, relocation_type),)
    value = BASE + 0x107C
    if relocation_type == 0x14:
        value -= BASE + 0x1000 + 8
    actual = original[:4] + struct.pack("<I", value) + original[8:]
    evidence = verify_relocated_bytes(
        original, actual, BASE + 0x1000, relocation, source, symbols, "source.obj",
    )
    assert evidence[0]["addend"] == -4
    assert evidence[0]["address"] == BASE + 0x107C
    for offset in (0, 4, 11):
        corrupted = bytearray(actual)
        corrupted[offset] ^= 1
        with pytest.raises(ValueError, match="linked bytes or relocation destination differ"):
            verify_relocated_bytes(
                original, corrupted, BASE + 0x1000, relocation, source, symbols, "source.obj",
            )


@pytest.mark.parametrize("relocations,reason", [
    ((CoffRelocation(1, 0, 0x06),), "out-of-bounds"),
    ((CoffRelocation(0, 0, 0x06), CoffRelocation(0, 0, 0x06)), "overlapping"),
    ((CoffRelocation(0, 9, 0x06),), "missing relocation symbol"),
    ((CoffRelocation(0, 0, 0x07),), "unsupported relocation"),
])
def test_invalid_relocations_fail_closed(relocations, reason):
    symbols = linked_symbols([("_target", 0x1000, 2)])
    source = object_with(bytes(4), [symbol("_target")])
    with pytest.raises(ValueError, match=reason):
        verify_relocated_bytes(bytes(4), bytes(4), BASE + 0x1000,
                               relocations, source, symbols, "source.obj")


def test_bss_extent_cannot_extend_into_mapped_padding():
    symbols = linked_symbols([("_bss", 0x1000, 2)], section_size=8)
    obj = object_with(bytes(12), [symbol("_bss")], bss=True)
    with pytest.raises(ValueError, match="single linked section"):
        verify_data_sections({"source.obj": obj}, bytes(0x2000), BASE, symbols)


def test_storage_checks_initial_bss_and_deduplicates_pooled_data():
    symbols = linked_symbols([("_constant", 0x1000, 2), ("_bss", 0x1010, 2)])
    constant = object_with(b"abcd", [symbol("_constant")])
    bss = object_with(bytes(8), [symbol("_bss")], bss=True)
    objects = {"first.obj": constant, "second.obj": constant, "bss.obj": bss}
    mapped = bytearray(0x2000)
    mapped[0x1000:0x1004] = b"abcd"
    result = verify_data_sections(objects, mapped, BASE, symbols)
    assert result["verified_unique_bytes"] == 12
    assert result["unverified_sections"] == []
    assert result["verified_sections"][-1]["zero_initialized"]
    mapped[0x1014] = 1
    with pytest.raises(ValueError, match="linked bytes or relocation destination differ"):
        verify_data_sections(objects, mapped, BASE, symbols)


def test_unanchored_static_data_remains_unverified():
    symbols = linked_symbols([("_local", 0x1000, 3)])
    local = object_with(bytes(4), [symbol("_local", storage=3)])
    result = verify_data_sections(
        {"first.obj": local, "second.obj": local}, bytes(0x2000), BASE, symbols,
    )
    assert result["verified_unique_bytes"] == 0
    assert len(result["unverified_sections"]) == 2


def test_coff_bss_with_no_file_payload_reads_as_zeroes():
    # COFF SizeOfRawData describes BSS extent while PointerToRawData is zero.
    # The header is deliberately nonzero, exposing the former offset-zero read.
    header = struct.pack("<HHIIIHH", 0x14C, 1, 0, 60, 0, 0, 0)
    section = b".bss\0\0\0\0" + struct.pack("<IIIIIIHHI", 0, 0, 12, 0, 0, 0, 0, 0, 0x80)
    parsed = parse_coff_object(header + section + struct.pack("<I", 4))
    assert parsed.sections[0].data == bytes(12)


def test_all_code_sections_include_compiler_helper_bytes_and_relocations():
    symbols = linked_symbols(
        [("_main", 0x1000, 2), ("_$E2", 0x1020, 3)],
        " 0001:00000020 _$E2 00401020 source.obj\n",
        characteristics=0x20,
    )
    source = CoffObject(
        (
            CoffSection(".text", b"\xe8\0\0\0\0\xc3", 0x20, (CoffRelocation(1, 1, 0x14),)),
            CoffSection(".text", b"\xc3\xcc\xcc\xcc", 0x20, ()),
        ),
        (symbol("_main"), symbol("_$E2", storage=3, section=2, index=1)),
    )
    mapped = bytearray(0x2000)
    mapped[0x1000:0x1006] = b"\xe8\x1b\0\0\0\xc3"
    mapped[0x1020:0x1024] = b"\xc3\xcc\xcc\xcc"
    result = verify_code_sections({"source.obj": source}, mapped, BASE, symbols)
    assert result["verified_unique_bytes"] == 10
    assert len(result["verified_sections"]) == 2
    assert result["unverified_sections"] == []
    assert result["verified_sections"][0]["verified_relocations"][0]["symbol"] == "_$E2"
    # The canonical function and call destination are unchanged; only the
    # compiler helper's body is corrupt, which function-only checks missed.
    mapped[0x1020] = 0xCC
    with pytest.raises(ValueError, match="linked bytes or relocation destination differ"):
        verify_code_sections({"source.obj": source}, mapped, BASE, symbols)


def test_code_section_with_partial_symbol_anchors_is_explicitly_unverified():
    symbols = linked_symbols([("_main", 0x1000, 2)], characteristics=0x20)
    source = CoffObject(
        (CoffSection(".text", b"\xc3\xc3", 0x20, ()),),
        (symbol("_main"), symbol("_unowned", storage=3, value=1, index=1)),
    )
    mapped = bytearray(0x2000)
    mapped[0x1000:0x1002] = b"\xc3\xc3"
    result = verify_code_sections({"source.obj": source}, mapped, BASE, symbols)
    assert result["verified_unique_bytes"] == 0
    assert result["unverified_sections"][0]["reason"] == "incomplete independent symbol anchors"
    assert result["unverified_sections"][0]["unresolved_symbols"][0]["name"] == "_unowned"
