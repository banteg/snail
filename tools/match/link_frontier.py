#!/usr/bin/env python3
"""Inventory canonical COFF linkage edges without awarding native/link credit."""

from __future__ import annotations

import argparse
import hashlib
import json
import os
import shutil
import struct
import sys
from collections import Counter, defaultdict
from concurrent.futures import ThreadPoolExecutor
from dataclasses import dataclass
from pathlib import Path

import pefile

from snail.match import (
    DEFAULT_MATCH_ROOT,
    DEFAULT_REFERENCE_SYMBOL_MANIFEST_PATH,
    CoffObject,
    CoffSymbol,
    _canonical_symbol_name,
    _reference_symbol_by_name,
    _scratch_build_dependencies,
    _ScratchIncludeResolver,
    compile_scratch,
    extract_object_function,
    load_reference_symbol_manifest,
    load_scratch_config,
    parse_coff_object,
    resolve_function_extent,
)
from snail.symbols import (
    DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH,
    REPO_ROOT,
    load_function_symbol_manifest,
)

EXTERNAL = 2
STATIC = 3
WEAK_EXTERNAL = 105
COMDAT = 0x1000
RUNTIME_NAMES = frozenset({
    "__fltused", "__ftol", "__chkstk", "__alloca_probe", "__except_list",
    "__CxxFrameHandler", "__EH_prolog", "__SEH_prolog", "__global_unwind2",
    "__local_unwind2", "__except_handler3", "__setjmp3", "_setjmp",
    "_memcpy", "_memmove", "_memset", "_memcmp", "_strlen", "_strcmp",
    "_stricmp", "_strcpy", "_strcat", "_malloc", "_calloc", "_realloc",
    "_free", "_printf", "_sprintf", "_vsprintf", "_fprintf", "_fopen",
    "_fclose", "_fread", "_fwrite", "_fseek", "_ftell", "_fflush",
    "_remove", "_getcwd", "__getcwd", "__chdir", "__findfirst",
    "__findnext", "__findclose", "__ftime", "_ctime", "_rand", "_srand",
    "_floor", "_ceil", "_sqrt", "_sin", "_cos", "_acos", "__CIacos",
    "_atexit", "__onexit", "_exit", "__exit", "_abort", "_assert",
    "??2@YAPAXI@Z", "??3@YAXPAX@Z", "??_U@YAPAXI@Z", "??_V@YAXPAX@Z",
})
RUNTIME_CANONICAL_NAMES = frozenset(
    _canonical_symbol_name(name) for name in RUNTIME_NAMES if not name.startswith("?")
)


def input_label(path: Path) -> str:
    path = path.resolve()
    return str(path.relative_to(REPO_ROOT)) if path.is_relative_to(REPO_ROOT) else str(path)


def file_identity(path: Path) -> dict:
    data = path.read_bytes()
    return {"sha256": hashlib.sha256(data).hexdigest(), "size": len(data)}


def verify_input_identities(identities: dict) -> None:
    for label, identity in identities.items():
        if file_identity(REPO_ROOT / label) != identity:
            raise RuntimeError(f"input changed during inventory: {label}; rerun")


def resolve_runner(match_root: Path) -> Path:
    requested = os.environ.get("WIBO")
    if requested and "/" in requested and not Path(requested).is_absolute():
        raise ValueError("use an absolute WIBO path so all scratch builds have one runner identity")
    if requested:
        selected = requested if "/" in requested else shutil.which(requested)
    elif os.access(match_root / "bin/wibo", os.X_OK):
        selected = match_root / "bin/wibo"
    else:
        selected = shutil.which("wibo")
    if not selected or not Path(selected).is_file() or not os.access(selected, os.X_OK):
        raise FileNotFoundError("the cl.sh Wibo runner is unavailable")
    return Path(selected).resolve()


@dataclass(frozen=True)
class Unit:
    caller: str
    native_address: int
    obj: CoffObject
    main_symbol: CoffSymbol
    main_size: int
    symbol_aux_counts: dict[int, int]


def symbol_aux_counts(data: bytes, obj: CoffObject) -> dict[int, int]:
    """Retain weak-external detection omitted by the general COFF model."""
    table_offset = struct.unpack_from("<I", data, 8)[0]
    return {s.raw_index: data[table_offset + 18 * s.raw_index + 17] for s in obj.symbols}


class NativeIndex:
    """Reuse curated parser semantics while keeping fallback evidence visible."""

    def __init__(self, functions, references):
        self.exact = defaultdict(set)
        self.targets = {}
        self.function_names = {}
        self.references = _reference_symbol_by_name(references)
        for f in functions.functions:
            self.targets[f.address] = {"name": f.name, "kind": "function"}
            for name in (f.name, *f.aliases):
                self.exact[name].add(f.address)
                self.function_names[name] = f.address
        for s in references.symbols:
            self.targets.setdefault(s.address, {"name": s.name, "kind": s.kind})
            for name in (s.name, *s.aliases):
                if not name.startswith("$L"):
                    self.exact[name].add(s.address)

    def lookup(self, name: str) -> dict | None:
        exact = self.exact.get(name)
        if exact:
            addresses, basis = exact, "exact_manifest_spelling"
        else:
            canonical = _canonical_symbol_name(name)
            reference = self.references.get(canonical)
            addresses = set()
            if reference is not None:
                addresses.add(reference.address)
            if canonical in self.function_names:
                addresses.add(self.function_names[canonical])
            basis = "matcher_canonical_fallback_candidate"
        if not addresses:
            return None
        if len(addresses) != 1:
            return {"basis": "ambiguous_manifest_mapping", "addresses": sorted(addresses)}
        address = next(iter(addresses))
        return {"address": address, "basis": basis, **self.targets[address]}


def image_section(section) -> bool:
    return not section.name.startswith(".debug") and bool(section.characteristics & 0xE0) and not bool(
        section.characteristics & (0x200 | 0x800)
    )


def external_definition(unit: Unit, symbol: CoffSymbol) -> dict | None:
    if symbol.storage_class != EXTERNAL:
        return None
    if symbol.section_number == -1:
        kind = "absolute"
        comdat = False
    elif symbol.section_number == 0 and symbol.value > 0:
        kind = "common"
        comdat = False
    elif 0 < symbol.section_number <= len(unit.obj.sections):
        section = unit.obj.sections[symbol.section_number - 1]
        if not image_section(section):
            return None
        kind = "code" if section.characteristics & 0x20 else "data"
        comdat = bool(section.characteristics & COMDAT)
    else:
        return None
    return {
        "caller": unit.caller,
        "symbol": symbol.name,
        "kind": kind,
        "comdat": comdat,
        "selected_function": symbol.raw_index == unit.main_symbol.raw_index,
        "native_address": (
            unit.native_address if symbol.raw_index == unit.main_symbol.raw_index else None
        ),
    }


def classify_reference(unit, symbol, definitions, native_owners, native_index, imports, data_owners=None):
    """Classify an actual relocation; raw COFF names alone resolve providers."""
    if symbol.storage_class == WEAK_EXTERNAL or (
        symbol.storage_class == EXTERNAL
        and symbol.section_number == 0 and symbol.value == 0
        and unit.symbol_aux_counts.get(symbol.raw_index, 0)
    ):
        return {"category": "unsupported_weak_external"}
    if symbol.section_number == -1:
        return {"category": "local_absolute_definition"}
    if symbol.section_number < -1:
        return {"category": "unsupported_symbol_section"}
    if symbol.section_number > 0:
        if symbol.section_number > len(unit.obj.sections):
            return {"category": "invalid_local_section"}
        section = unit.obj.sections[symbol.section_number - 1]
        if not image_section(section):
            return {"category": "non_image_section_reference"}
        return {"category": "local_definition", "definition_kind": (
            "code" if section.characteristics & 0x20 else "data"
        )}
    if symbol.storage_class != EXTERNAL:
        return {"category": "unsupported_symbol_class"}
    if symbol.value > 0:
        return {"category": "common_storage", "minimum_bytes": symbol.value}
    exact = definitions.get(symbol.name, [])
    if exact:
        if len(exact) == 1 and exact[0]["kind"] != "common":
            category = "exact_external_definition"
        elif any(d["comdat"] for d in exact):
            category = "multiple_definitions_require_comdat_selection"
        elif all(d["kind"] == "common" for d in exact):
            category = "common_storage"
        else:
            category = "multiple_external_definitions"
        return {"category": category, "providers": exact}
    if symbol.name in RUNTIME_NAMES:
        return {"category": "compiler_runtime_external", "evidence": "explicit_runtime_spelling"}
    canonical = _canonical_symbol_name(symbol.name)
    if not symbol.name.startswith("?") and canonical in imports:
        return {"category": "native_platform_import", "native_imports": imports[canonical]}
    native = native_index.lookup(symbol.name)
    if native is None:
        return {"category": "unmapped_external"}
    if "address" not in native:
        return {"category": "ambiguous_native_mapping", "native_mapping": native}
    if native["kind"] in ("function", "function_alias"):
        owners = native_owners.get(native["address"], [])
        if owners:
            if not any(owner["externally_visible"] for owner in owners):
                category = "canonical_function_has_no_external_export"
            else:
                category = (
                    "function_link_name_mismatch"
                    if native["basis"] == "exact_manifest_spelling"
                    else "possible_function_link_name_mismatch"
                )
            return {"category": category, "native_mapping": native, "native_owners": owners}
        if canonical in RUNTIME_CANONICAL_NAMES:
            return {
                "category": "possible_runtime_link_name_mismatch",
                "native_mapping": native,
            }
        return {"category": "missing_canonical_function_owner", "native_mapping": native}
    owners = (data_owners or {}).get(native["address"], [])
    if owners:
        return {
            "category": (
                "data_link_name_mismatch" if native["basis"] == "exact_manifest_spelling"
                else "possible_data_link_name_mismatch"
            ),
            "native_mapping": native, "native_owners": owners,
        }
    return {"category": "missing_data_storage_owner", "native_mapping": native}


def inventory(units: list[Unit], native_index: NativeIndex, imports: dict) -> dict:
    definitions = defaultdict(list)
    native_owners = defaultdict(list)
    data_owners = defaultdict(list)
    for unit in units:
        native_owners[unit.native_address].append({
            "caller": unit.caller, "symbol": unit.main_symbol.name,
            "externally_visible": unit.main_symbol.storage_class == EXTERNAL,
        })
        for symbol in unit.obj.symbols:
            definition = external_definition(unit, symbol)
            if definition:
                definitions[symbol.name].append(definition)
                if definition["kind"] in ("data", "common"):
                    mapping = native_index.lookup(symbol.name)
                    if (mapping and mapping.get("basis") == "exact_manifest_spelling"
                            and mapping["kind"] not in ("function", "function_alias")):
                        data_owners[mapping["address"]].append(definition)
    edges = []
    objects = []
    for unit in units:
        symbols = {s.raw_index: s for s in unit.obj.symbols}
        section = unit.obj.sections[unit.main_symbol.section_number - 1]
        start, end = unit.main_symbol.value, unit.main_symbol.value + unit.main_size
        selected = [r for r in section.relocations if start <= r.virtual_address < end]
        selected_indices = {r.symbol_index for r in selected}
        for relocation in selected:
            symbol = symbols.get(relocation.symbol_index)
            edge = {
                "caller": unit.caller,
                "caller_native_address": unit.native_address,
                "offset": relocation.virtual_address - start,
                "relocation_type": relocation.relocation_type,
                "symbol": symbol.name if symbol else None,
            }
            if relocation.virtual_address + 4 > end:
                result = {"category": "relocation_crosses_selected_extent"}
            elif relocation.relocation_type not in (6, 20):
                result = {"category": "unsupported_relocation_type"}
            elif symbol is None:
                result = {"category": "missing_coff_symbol"}
            else:
                edge["encoded_addend"] = struct.unpack_from(
                    "<I", section.data, relocation.virtual_address
                )[0]
                result = classify_reference(
                    unit, symbol, definitions, native_owners, native_index, imports, data_owners
                )
            edges.append({**edge, **result})
        objects.append({
            "caller": unit.caller,
            "selected_relocations": len(selected),
            "other_image_relocations": sum(
                len(s.relocations) for s in unit.obj.sections if image_section(s)
            ) - len(selected),
            "undefined_symbols_not_referenced_by_selected_function": sorted({
                s.name for s in unit.obj.symbols
                if s.section_number == 0 and s.value == 0
                and s.storage_class in (EXTERNAL, WEAK_EXTERNAL)
                and s.raw_index not in selected_indices
            }),
        })
    grouped = defaultdict(list)
    for edge in edges:
        if edge["category"] not in (
            "local_definition", "local_absolute_definition", "exact_external_definition"
        ):
            grouped[(edge["category"], edge["symbol"])].append(edge)
    frontier = []
    for (category, symbol), rows in grouped.items():
        row = {
            "category": category, "symbol": symbol, "relocations": len(rows),
            "callers": sorted({r["caller"] for r in rows}),
        }
        for field in ("native_mapping", "native_owners", "providers", "native_imports"):
            if field in rows[0]:
                row[field] = rows[0][field]
        frontier.append(row)
    frontier.sort(key=lambda r: (-len(r["callers"]), -r["relocations"], r["category"], r["symbol"] or ""))
    return {
        "summary": {
            "objects": len(units), "selected_function_relocations": len(edges),
            "categories": dict(sorted(Counter(r["category"] for r in edges).items())),
            "other_image_relocations": sum(r["other_image_relocations"] for r in objects),
        },
        "frontier": frontier, "edges": edges, "objects": objects,
    }


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--out", type=Path, default=REPO_ROOT / "artifacts/match/link-frontier.json")
    parser.add_argument("--jobs", "-j", type=int, default=4)
    args = parser.parse_args()
    if args.jobs < 1:
        parser.error("--jobs must be positive")
    args.out.unlink(missing_ok=True)
    match_root = DEFAULT_MATCH_ROOT.resolve()
    runner = resolve_runner(match_root)
    manifest = load_function_symbol_manifest(DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH)
    references = load_reference_symbol_manifest(DEFAULT_REFERENCE_SYMBOL_MANIFEST_PATH)
    native_index = NativeIndex(manifest, references)
    paths = sorted((match_root / "scratches").glob("*/scratch.conf"))
    resolver = _ScratchIncludeResolver(match_root)
    configs = [load_scratch_config(p.parent) for p in paths]
    dependencies = {
        path.resolve() for c in configs
        for path in _scratch_build_dependencies(c, match_root, include_resolver=resolver)
    }
    dependencies.update(paths)
    dependencies.update((
        DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH, DEFAULT_REFERENCE_SYMBOL_MANIFEST_PATH,
        REPO_ROOT / manifest.primary_target, Path(__file__).resolve(),
        REPO_ROOT / "src/snail/match.py", REPO_ROOT / "src/snail/symbols.py",
        runner,
    ))
    identities = {input_label(path): file_identity(path) for path in sorted(dependencies)}
    image = REPO_ROOT / manifest.primary_target
    if identities[str(image.relative_to(REPO_ROOT))]["sha256"] != manifest.unwrapped_sha256:
        raise ValueError("native image does not match the function manifest hash")
    pe = pefile.PE(str(image), fast_load=True)
    pe.parse_data_directories(directories=[pefile.DIRECTORY_ENTRY["IMAGE_DIRECTORY_ENTRY_IMPORT"]])
    imports = defaultdict(list)
    for dll in getattr(pe, "DIRECTORY_ENTRY_IMPORT", []):
        for entry in dll.imports:
            if entry.name:
                imports[entry.name.decode("ascii")].append({
                    "dll": dll.dll.decode("ascii"), "iat_address": entry.address,
                })
    pe.close()

    def read_unit(config):
        start, _ = resolve_function_extent(manifest, config.function, config.end_va)
        path = compile_scratch(config, match_root, include_resolver=resolver)
        data = path.read_bytes()
        obj = parse_coff_object(data)
        if any(s.characteristics & 0x1000000 for s in obj.sections):
            raise ValueError("COFF relocation overflow is unsupported")
        function = extract_object_function(obj, config.symbol or config.function)
        selected = [s for s in obj.symbols if s.name == function.name]
        if len(selected) != 1 or selected[0].section_number <= 0:
            raise ValueError("selected function has no unique section definition")
        unit = Unit(config.directory.name, start, obj, selected[0], len(function.data), symbol_aux_counts(data, obj))
        identity = {
            "caller": unit.caller, "native_address": start,
            "selected_symbol": function.name, "selected_object_bytes": len(function.data),
            "object_path": str(path.relative_to(REPO_ROOT)),
            "object_sha256": hashlib.sha256(data).hexdigest(),
            "compiler": config.compiler, "cflags": config.cflags,
            "dependency_paths": [input_label(p) for p in _scratch_build_dependencies(
                config, match_root, include_resolver=resolver
            )],
        }
        return unit, identity

    units, object_identities = [], []
    with ThreadPoolExecutor(max_workers=args.jobs) as executor:
        for unit, identity in executor.map(read_unit, configs):
            units.append(unit)
            object_identities.append(identity)
    verify_input_identities(identities)
    if resolve_runner(match_root) != runner:
        raise RuntimeError("compiler runner changed during inventory; rerun")
    for identity in object_identities:
        path = REPO_ROOT / identity["object_path"]
        if hashlib.sha256(path.read_bytes()).hexdigest() != identity["object_sha256"]:
            raise RuntimeError(f"compiled object changed during inventory: {path}; rerun")
    result = inventory(units, native_index, dict(imports))
    receipt = {
        "schema": 1, "complete": True,
        "scope": "Relocations in each selected canonical scratch function only; definitions from every emitted image section of those objects",
        "limits": [
            "No native functions are re-scored; partial and exact canonical scratches both participate.",
            "An exact external definition closes only that symbol edge, not the provider's dependencies or a complete object link.",
            "Auxiliary-function and data-section relocations, and undefined symbols absent from the selected function, remain separately enumerated scope exclusions.",
            "Matcher canonical-name fallback is heuristic; those native-owner candidates do not prove ABI or receiver identity.",
            "COMMON allocation, COMDAT selection, and weak-external auxiliary semantics are not link-verified.",
            "Runtime spellings and native imports identify external dependencies without proving a supplied library resolves them.",
            "Integration support/storage objects are excluded; no original TU ownership, original data layout, or game-link credit is inferred.",
        ],
        "runner": input_label(runner),
        "inputs": identities, "object_inputs": object_identities, **result,
    }
    args.out.parent.mkdir(parents=True, exist_ok=True)
    args.out.write_text(json.dumps(receipt, indent=2) + "\n")
    print(json.dumps(result["summary"], indent=2))
    print(f"Receipt: {args.out.resolve()}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
