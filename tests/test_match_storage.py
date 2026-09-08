"""Storage evidence must survive independent data and relocation controls."""

import struct
from dataclasses import replace
from types import SimpleNamespace

import pytest

from snail.match import CoffObject, CoffRelocation, CoffSection, CoffSymbol
from snail.match_storage import (
    StorageContract,
    original_span,
    verify_native_storage,
    verify_owner,
)

ZERO = StorageContract("storage.obj", "_table", "table", 8, ("initialize_table",))
CALLBACK = StorageContract(
    "callbacks.obj",
    "_callbacks",
    "callbacks",
    4,
    ("initialize_callbacks", "callback"),
    False,
)


def source_owner(contract=ZERO, *, data=None, relocations=None, extra_symbols=()):
    if data is None:
        data = bytes(contract.size)
    if relocations is None:
        relocations = () if contract.zero_initialized else (CoffRelocation(0, 1, 0x06),)
    section = CoffSection(
        ".bss" if contract.zero_initialized else ".data",
        data,
        0x80 if contract.zero_initialized else 0x40,
        relocations,
    )
    symbols = [CoffSymbol(0, contract.symbol, 0, 1, 0, 2)]
    if not contract.zero_initialized:
        symbols.append(CoffSymbol(1, "_callback", 0, 0, 0x20, 2))
    return CoffObject((section,), (*symbols, *extra_symbols))


def native_pe(data=b"", *, virtual_size=0x20, characteristics=0xC0):
    section = SimpleNamespace(
        VirtualAddress=0x2000,
        Misc_VirtualSize=virtual_size,
        Characteristics=characteristics,
        get_data=lambda: data,
    )
    return SimpleNamespace(
        OPTIONAL_HEADER=SimpleNamespace(ImageBase=0x400000), sections=[section]
    )


def witness(name, *, exact=True):
    return {
        "function": name,
        "symbol": "_" + name,
        "normalized_exact": exact,
        "native_address": 0x401000,
    }


def reference(contract=ZERO, *, address=0x402000):
    return {
        "name": contract.native_name,
        "kind": "global" if contract.zero_initialized else "vtable",
        "address": hex(address),
        "size": hex(contract.size),
    }


def test_source_initial_storage_matches_raw_data_and_virtual_zero_tail():
    data = struct.pack("<I", 0x401000)
    report = verify_native_storage(
        {ZERO.object: source_owner(), CALLBACK.object: source_owner(CALLBACK)},
        native_pe(data),
        [reference(ZERO, address=0x402008), reference(CALLBACK)],
        [witness(name) for name in (*ZERO.proof_functions, *CALLBACK.proof_functions)],
        (ZERO, CALLBACK),
    )
    assert report["verified_bytes"] == 12
    assert {row["name"] for row in report["verified_owners"]} == {"table", "callbacks"}
    pointer = next(
        row for row in report["verified_owners"] if row["name"] == "callbacks"
    )
    assert pointer["pointers"] == [
        {"offset": 0, "symbol": "_callback", "native_target": 0x401000}
    ]


def test_corrupted_native_zero_initializer_is_rejected():
    with pytest.raises(ValueError):
        verify_owner(ZERO, source_owner(), b"\x01" + bytes(7), {})


def test_bss_contract_cannot_accept_matching_nonzero_initializers():
    corrupt = b"\x01" + bytes(7)
    with pytest.raises(ValueError):
        verify_owner(ZERO, source_owner(data=corrupt), corrupt, {})


@pytest.mark.parametrize("source_size", [7, 12])
def test_source_owner_extent_must_agree_with_recovered_contract(source_size):
    with pytest.raises(ValueError):
        verify_owner(ZERO, source_owner(data=bytes(source_size)), bytes(8), {})


def test_independent_source_owner_inside_claimed_storage_is_rejected():
    other = CoffSymbol(1, "_other", 4, 1, 0, 2)
    with pytest.raises(ValueError):
        verify_owner(ZERO, source_owner(extra_symbols=(other,)), bytes(8), {})


def test_adjacent_source_owner_is_not_counted_as_part_of_verified_storage():
    other = CoffSymbol(1, "_other", 8, 1, 0, 2)
    report = verify_owner(
        ZERO,
        source_owner(data=bytes(8) + b"different", extra_symbols=(other,)),
        bytes(8),
        {},
    )
    assert report["bytes"] == 8


def test_callback_destination_must_match_original_entry_point():
    with pytest.raises(ValueError):
        verify_owner(
            CALLBACK,
            source_owner(CALLBACK),
            struct.pack("<I", 0x401004),
            {"_callback": 0x401000},
        )


def test_callback_interior_addend_is_not_an_entry_point_witness():
    with pytest.raises(ValueError):
        verify_owner(
            CALLBACK,
            source_owner(CALLBACK, data=struct.pack("<I", 4)),
            struct.pack("<I", 0x401004),
            {"_callback": 0x401000},
        )


def test_literal_callback_address_without_source_relocation_is_rejected():
    address = struct.pack("<I", 0x401000)
    with pytest.raises(ValueError):
        verify_owner(
            CALLBACK,
            source_owner(CALLBACK, data=address, relocations=()),
            address,
            {"_callback": 0x401000},
        )


@pytest.mark.parametrize(
    "relocations",
    [
        (CoffRelocation(0, 1, 0x14),),
        (CoffRelocation(1, 1, 0x06),),
        (CoffRelocation(0, 1, 0x06), CoffRelocation(0, 1, 0x06)),
    ],
)
def test_callback_requires_one_complete_absolute_relocation(relocations):
    with pytest.raises(ValueError):
        verify_owner(
            CALLBACK,
            source_owner(CALLBACK, relocations=relocations),
            struct.pack("<I", 0x401000),
            {"_callback": 0x401000},
        )


def test_callback_target_needs_exact_source_definition():
    with pytest.raises(ValueError):
        verify_owner(CALLBACK, source_owner(CALLBACK), struct.pack("<I", 0x401000), {})


@pytest.mark.parametrize("functions", [[], [witness("initialize_table", exact=False)]])
def test_equal_zero_bytes_do_not_substitute_for_exact_accessor_witnesses(functions):
    with pytest.raises(ValueError):
        verify_native_storage(
            {ZERO.object: source_owner()},
            native_pe(),
            [reference()],
            functions,
            (ZERO,),
        )


def test_two_contracts_cannot_claim_overlapping_native_storage():
    second = replace(ZERO, object="second.obj", symbol="_second", native_name="second")
    with pytest.raises(ValueError):
        verify_native_storage(
            {ZERO.object: source_owner(), second.object: source_owner(second)},
            native_pe(),
            [reference(), reference(second, address=0x402004)],
            [witness("initialize_table")],
            (ZERO, second),
        )


@pytest.mark.parametrize(
    "address,size,characteristics",
    [
        (0x401FFF, 1, 0xC0),
        (0x40201F, 2, 0xC0),
        (0x402000, 0, 0xC0),
        (0x402000, 4, 0x20),
    ],
)
def test_native_span_cannot_extend_past_virtual_data_extent(
    address, size, characteristics
):
    with pytest.raises(ValueError):
        original_span(native_pe(characteristics=characteristics), address, size)


def sized_source_owner(*, emitted_size=8, relocated=False):
    obj = source_owner(data=bytes(12))
    size_section = CoffSection(
        ".rdata",
        struct.pack("<II", 0xDEAD, emitted_size),
        0x40,
        (CoffRelocation(4, 0, 0x06),) if relocated else (),
    )
    return CoffObject(
        (*obj.sections, size_section),
        (*obj.symbols, CoffSymbol(1, "_sizes", 0, 2, 0, 2)),
    )


def test_compiler_size_witness_separates_owned_bytes_from_alignment_padding():
    contract = replace(ZERO, size_symbol="_sizes", size_index=1)
    report = verify_owner(contract, sized_source_owner(), bytes(8), {})
    assert report["bytes"] == 8


def test_compiler_size_witness_rejects_changed_source_type_extent():
    contract = replace(ZERO, size_symbol="_sizes", size_index=1)
    with pytest.raises(ValueError):
        verify_owner(contract, sized_source_owner(emitted_size=12), bytes(8), {})


def test_missing_compiler_size_witness_cannot_fall_back_to_section_padding():
    contract = replace(ZERO, size_symbol="_sizes", size_index=1)
    with pytest.raises(ValueError):
        verify_owner(contract, source_owner(), bytes(8), {})


def test_compiler_size_witness_must_be_a_literal_size_not_a_relocated_address():
    contract = replace(ZERO, size_symbol="_sizes", size_index=1)
    with pytest.raises(ValueError):
        verify_owner(contract, sized_source_owner(relocated=True), bytes(8), {})
