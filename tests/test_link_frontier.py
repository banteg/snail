"""Boundary tests for the inventory's evidence and COFF symbol scope."""

import importlib.util
import os
import struct
import sys
from dataclasses import replace
from pathlib import Path

import pytest

from snail.match import (
    CoffObject,
    CoffRelocation,
    CoffSection,
    CoffSymbol,
    ReferenceSymbol,
    ReferenceSymbolManifest,
    parse_coff_object,
)
from snail.symbols import FunctionSymbol, FunctionSymbolManifest

TOOL_PATH = Path(__file__).resolve().parents[1] / "tools/match/link_frontier.py"
SPEC = importlib.util.spec_from_file_location("snail_test_link_frontier", TOOL_PATH)
frontier = importlib.util.module_from_spec(SPEC)
sys.modules[SPEC.name] = frontier
SPEC.loader.exec_module(frontier)


def symbol(name, *, index=0, section=1, value=0, storage=2, function=False):
    return CoffSymbol(index, name, value, section, 0x20 if function else 0, storage)


def section(name=".text", *, size=32, flags=0x20, relocations=()):
    return CoffSection(name, bytes(size), flags, tuple(relocations))


def unit(caller, *, symbols=(), sections=None, start=0, size=8, address=0x401000, aux=None, storage=2):
    main = symbol(f"_{caller}", value=start, function=True, storage=storage)
    return frontier.Unit(
        caller,
        address,
        CoffObject(tuple(sections or [section()]), (main, *symbols)),
        main,
        size,
        aux or {},
    )


def native_index(*references, functions=()):
    return frontier.NativeIndex(
        FunctionSymbolManifest("fixture", "fixture.exe", "", 0x400000, "", None, functions),
        ReferenceSymbolManifest("fixture", references),
    )


def classify(current, target, *, definitions=None, owners=None, native=None, imports=None):
    return frontier.classify_reference(
        current, target, definitions or {}, owners or {}, native or native_index(), imports or {},
    )


def test_external_resolution_requires_exact_decorated_spelling():
    wanted = symbol("_foo", index=1, section=0)
    caller = unit("caller", symbols=[wanted], sections=[
        section(relocations=[CoffRelocation(0, 1, 0x14)]),
    ])
    wrong = unit("wrong", symbols=[symbol("_foo@4", index=1, function=True)])
    matching = unit("matching", symbols=[symbol("_foo", index=1, function=True)])

    unresolved = frontier.inventory([caller, wrong], native_index(), {})
    assert unresolved["edges"][0]["category"] == "unmapped_external"
    resolved = frontier.inventory([caller, wrong, matching], native_index(), {})
    edge = resolved["edges"][0]
    assert edge["category"] == "exact_external_definition"
    assert [p["caller"] for p in edge["providers"]] == ["matching"]


def test_static_definition_is_local_and_cannot_satisfy_another_object():
    local = symbol("_private", index=2, storage=3)
    provider = unit("provider", symbols=[local])
    external = symbol("_private", index=1, section=0)
    caller = unit("caller", symbols=[external], sections=[
        section(relocations=[CoffRelocation(0, 1, 6)]),
    ])
    assert frontier.external_definition(provider, local) is None
    assert classify(provider, local)["category"] == "local_definition"
    report = frontier.inventory([caller, provider], native_index(), {})
    assert report["edges"][0]["category"] == "unmapped_external"


def test_shared_object_members_do_not_duplicate_definitions_or_exclusions():
    first = symbol("_first", index=0, value=0, function=True)
    second = symbol("_second", index=1, value=8, function=True)
    target = symbol("_external", index=2, section=0)
    obj = CoffObject((section(relocations=[
        CoffRelocation(0, 2, 20), CoffRelocation(8, 2, 20),
    ]),), (first, second, target))
    a = frontier.Unit("first", 0x401000, obj, first, 8, {}, "/physical/pair.obj")
    b = frontier.Unit("second", 0x401008, obj, second, 8, {}, "/physical/pair.obj")
    caller = unit("caller", symbols=[symbol("_second", index=1, section=0)], sections=[
        section(relocations=[CoffRelocation(0, 1, 20)]),
    ])
    report = frontier.inventory([a, b, caller], native_index(), {})
    assert report["summary"]["objects"] == 2
    assert report["summary"]["selected_functions"] == 3
    assert report["summary"]["other_image_relocations"] == 0
    edge = next(e for e in report["edges"] if e["caller"] == "caller")
    assert edge["category"] == "exact_external_definition"
    assert len(edge["providers"]) == 1
    assert edge["providers"][0]["caller"] == "second"
    assert edge["providers"][0]["selected_function"] is True
    assert edge["providers"][0]["native_address"] == 0x401008

    # Identical definitions in two different objects still need resolution.
    separate = replace(b, object_path="/physical/separate.obj")
    report = frontier.inventory([a, separate, caller], native_index(), {})
    edge = next(e for e in report["edges"] if e["caller"] == "caller")
    assert edge["category"] == "multiple_external_definitions"


@pytest.mark.parametrize("flags, expected", [(0x20, "code"), (0x40, "data"), (0x80, "data")])
def test_local_definition_kind_uses_the_target_section(flags, expected):
    target = symbol("_owned", index=1, section=2)
    current = unit("caller", symbols=[target], sections=[section(), section(flags=flags)])
    result = classify(current, target)
    assert result == {"category": "local_definition", "definition_kind": expected}
    assert frontier.external_definition(current, target)["kind"] == expected


@pytest.mark.parametrize("flags", [0, 0x20 | 0x200, 0x40 | 0x800])
def test_non_image_definitions_do_not_resolve_image_references(flags):
    target = symbol("_debug", index=1, section=2)
    current = unit("caller", symbols=[target], sections=[section(), section(flags=flags)])
    assert frontier.external_definition(current, target) is None
    assert classify(current, target)["category"] == "non_image_section_reference"


def test_debug_section_without_remove_flag_is_still_not_an_image_provider():
    target = symbol("_debug", index=1, section=2)
    current = unit("caller", symbols=[target], sections=[
        section(), section(".debug$S", flags=0x42000040),
    ])
    assert frontier.external_definition(current, target) is None
    assert classify(current, target)["category"] == "non_image_section_reference"


def test_manifest_alias_exposes_existing_data_owner_with_different_link_name():
    references = native_index(ReferenceSymbol(
        0x405000, "data_owner", "global", ("_owned_storage", "_old_storage"),
    ))
    provider = unit("provider", address=0x402000,
                    symbols=[symbol("_owned_storage", index=1, section=2)],
                    sections=[section(), section(".bss", flags=0x80)])
    caller = unit("caller", symbols=[symbol("_old_storage", index=1, section=0)],
                  sections=[section(relocations=[CoffRelocation(0, 1, 6)])])
    result = frontier.inventory([caller, provider], references, {})
    edge = result["edges"][0]
    assert edge["category"] == "data_link_name_mismatch"
    assert edge["native_owners"][0]["symbol"] == "_owned_storage"
    assert edge["native_mapping"]["address"] == 0x405000


def test_common_storage_and_absolute_symbols_are_distinct_from_unresolved_externals():
    common = symbol("_buffer", index=1, section=0, value=24)
    absolute = symbol("_zero", index=2, section=-1)
    current = unit("caller", symbols=[common, absolute])
    assert classify(current, common) == {"category": "common_storage", "minimum_bytes": 24}
    assert classify(current, absolute) == {"category": "local_absolute_definition"}
    assert frontier.external_definition(current, common)["kind"] == "common"
    absolute_definition = frontier.external_definition(current, absolute)
    assert absolute_definition["kind"] == "absolute"
    wanted = symbol("_zero", section=0)
    result = classify(current, wanted, definitions={"_zero": [absolute_definition]})
    assert result["category"] == "exact_external_definition"


@pytest.mark.parametrize("storage, auxiliary_count", [(105, 0), (2, 1)])
def test_weak_external_is_not_treated_as_a_resolved_strong_symbol(storage, auxiliary_count):
    weak = symbol("_weak", index=3, section=0, storage=storage)
    current = unit("caller", symbols=[weak], aux={3: auxiliary_count})
    definition = frontier.external_definition(current, symbol("_weak", index=4))
    result = classify(current, weak, definitions={"_weak": [definition]})
    assert result == {"category": "unsupported_weak_external"}


@pytest.mark.parametrize(
    "providers, expected",
    [
        ([(0x20, 1, 0), (0x20, 1, 0)], "multiple_external_definitions"),
        ([(0x1020, 1, 0), (0x1020, 1, 0)], "multiple_definitions_require_comdat_selection"),
        ([(0x20, 0, 16), (0x20, 0, 32)], "common_storage"),
        ([(0x20, 1, 0), (0x20, 0, 32)], "multiple_external_definitions"),
    ],
)
def test_duplicate_definitions_keep_comdat_and_common_requirements_visible(providers, expected):
    definitions = []
    for number, (flags, target_section, value) in enumerate(providers):
        target = symbol("_shared", index=1, section=target_section, value=value)
        owner = unit(f"provider{number}", symbols=[target], sections=[section(flags=flags)])
        definitions.append(frontier.external_definition(owner, target))
    result = classify(unit("caller"), symbol("_shared", section=0), definitions={"_shared": definitions})
    assert result["category"] == expected
    assert len(result["providers"]) == 2


def test_fabricated_cpp_owner_can_only_produce_a_possible_mapping():
    address = 0x44CD40
    exact_name = "?Cross@tVector@@QAEXABU1@0@Z"
    references = native_index(ReferenceSymbol(address, "cross_vectors", "function", (exact_name,)))
    fabricated = "?cross_vectors@CompletelyDifferentOwner@@QAEXHH@Z"
    exact = references.lookup(exact_name)
    fallback = references.lookup(fabricated)
    assert exact["basis"] == "exact_manifest_spelling"
    assert fallback["address"] == address
    assert fallback["basis"] == "matcher_canonical_fallback_candidate"
    owners = {address: [{"caller": "cross_vectors", "symbol": exact_name, "externally_visible": True}]}
    result = classify(unit("caller"), symbol(fabricated, section=0), owners=owners, native=references)
    assert result["category"] == "possible_function_link_name_mismatch"
    assert "providers" not in result
    exact_result = classify(unit("caller"), symbol(exact_name, section=0), owners=owners, native=references)
    assert exact_result["category"] == "function_link_name_mismatch"


def test_selected_static_function_is_an_owner_but_does_not_export_its_identity():
    address = 0x402000
    references = native_index(ReferenceSymbol(address, "private", "function", ("_private",)))
    provider = unit("private", address=address, storage=3)
    caller = unit("caller", symbols=[symbol("_private", index=1, section=0)], sections=[
        section(relocations=[CoffRelocation(0, 1, 20)]),
    ])
    report = frontier.inventory([caller, provider], references, {})
    edge = report["edges"][0]
    assert edge["category"] == "canonical_function_has_no_external_export"
    assert edge["native_owners"] == [{
        "caller": "private", "symbol": "_private", "externally_visible": False,
    }]


def test_manifest_conflicts_remain_ambiguous_and_do_not_choose_an_owner():
    references = native_index(
        ReferenceSymbol(0x402000, "other", "function", ("shared",)),
        functions=(FunctionSymbol(0x401000, "shared"),),
    )
    result = classify(unit("caller"), symbol("shared", section=0), native=references)
    assert result["category"] == "ambiguous_native_mapping"
    assert result["native_mapping"]["addresses"] == [0x401000, 0x402000]


def test_selected_extent_excludes_helper_and_data_relocations_but_keeps_their_definitions():
    selected = symbol("_selected_dep", index=2, section=0)
    helper_dep = symbol("_helper_dep", index=3, section=0)
    data_dep = symbol("_data_dep", index=4, section=0)
    debug_dep = symbol("_debug_dep", index=5, section=0)
    helper = symbol("_helper", index=6, value=16, function=True)
    table = symbol("_table", index=7, section=2)
    current = unit(
        "caller", start=8, size=8,
        symbols=[selected, helper_dep, data_dep, debug_dep, helper, table],
        sections=[
            section(relocations=[CoffRelocation(0, 3, 20), CoffRelocation(8, 2, 20), CoffRelocation(16, 3, 20)]),
            section(".data", flags=0x40, relocations=[CoffRelocation(0, 4, 6)]),
            section(".debug", flags=0x40 | 0x800, relocations=[CoffRelocation(0, 5, 6)]),
        ],
    )
    other = unit(
        "other", address=0x402000,
        symbols=[symbol("_helper", index=1, section=0), symbol("_table", index=2, section=0)],
        sections=[section(relocations=[CoffRelocation(0, 1, 20), CoffRelocation(4, 2, 6)])],
    )
    report = frontier.inventory([current, other], native_index(), {})
    assert report["summary"]["selected_function_relocations"] == 3
    assert report["summary"]["other_image_relocations"] == 3
    assert [(e["caller"], e["offset"], e["symbol"]) for e in report["edges"]] == [
        ("caller", 0, "_selected_dep"), ("other", 0, "_helper"), ("other", 4, "_table"),
    ]
    assert report["objects"][0]["undefined_symbols_not_referenced_by_selected_function"] == [
        "_data_dep", "_debug_dep", "_helper_dep",
    ]
    for edge in report["edges"][1:]:
        assert edge["category"] == "exact_external_definition"
        assert edge["providers"][0]["selected_function"] is False
        assert edge["providers"][0]["native_address"] is None


@pytest.mark.parametrize(
    "relocation, expected",
    [
        (CoffRelocation(6, 2, 6), "relocation_crosses_selected_extent"),
        (CoffRelocation(0, 2, 7), "unsupported_relocation_type"),
        (CoffRelocation(0, 1, 6), "missing_coff_symbol"),
    ],
)
def test_invalid_relocation_edges_are_reported_without_claiming_resolution(relocation, expected):
    # Raw symbol index 1 is intentionally absent, as when it is an auxiliary record.
    current = unit("caller", symbols=[symbol("_target", index=2, section=0)], sections=[
        section(relocations=[relocation]),
    ])
    report = frontier.inventory([current], native_index(), {})
    assert report["edges"][0]["category"] == expected
    assert "providers" not in report["edges"][0]
    assert report["frontier"][0]["category"] == expected


def test_auxiliary_counts_use_raw_coff_indices_after_skipped_records():
    records = bytearray()
    for name, auxiliary_count in [(b"_first", 2), (b"_weak", 1)]:
        records.extend(struct.pack("<8sIhHBB", name, 0, 0, 0, 2, auxiliary_count))
        records.extend(bytes(18 * auxiliary_count))
    header = struct.pack("<HHIIIHH", 0x14C, 0, 0, 20, 5, 0, 0)
    data = header + records + struct.pack("<I", 4)
    obj = parse_coff_object(data)
    assert [s.raw_index for s in obj.symbols] == [0, 3]
    assert frontier.symbol_aux_counts(data, obj) == {0: 2, 3: 1}


def test_runtime_and_platform_categories_are_evidence_not_external_resolution():
    current = unit("caller")
    runtime = classify(current, symbol("_malloc", section=0))
    assert runtime == {"category": "compiler_runtime_external", "evidence": "explicit_runtime_spelling"}
    imports = {"Sleep": [{"dll": "KERNEL32.dll", "iat_address": 0x405000}]}
    platform = classify(current, symbol("__imp__Sleep@4", section=0), imports=imports)
    assert platform == {"category": "native_platform_import", "native_imports": imports["Sleep"]}
    fabricated = classify(current, symbol("?Sleep@WrongOwner@@QAEXH@Z", section=0), imports=imports)
    assert fabricated["category"] == "unmapped_external"


def test_input_verification_detects_same_size_content_with_restored_timestamp(tmp_path):
    path = tmp_path / "source.cpp"
    path.write_text("first")
    original = path.stat()
    identities = {str(path): frontier.file_identity(path)}
    frontier.verify_input_identities(identities)
    path.write_text("other")
    os.utime(path, ns=(original.st_atime_ns, original.st_mtime_ns))
    with pytest.raises(RuntimeError, match="input changed during inventory"):
        frontier.verify_input_identities(identities)


def test_runner_selection_matches_launcher_override_and_local_fallback(tmp_path, monkeypatch):
    local = tmp_path / "bin/wibo"
    local.parent.mkdir()
    local.write_text("local")
    local.chmod(0o755)
    monkeypatch.delenv("WIBO", raising=False)
    assert frontier.resolve_runner(tmp_path) == local.resolve()
    alternative = tmp_path / "other-runner"
    alternative.write_text("other")
    alternative.chmod(0o755)
    monkeypatch.setenv("WIBO", str(alternative))
    assert frontier.resolve_runner(tmp_path) == alternative.resolve()
    monkeypatch.setenv("WIBO", "./relative-wibo")
    with pytest.raises(ValueError, match="absolute WIBO path"):
        frontier.resolve_runner(tmp_path)
