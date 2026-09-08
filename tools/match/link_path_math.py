#!/usr/bin/env python3
"""Link and exercise recovered dependency groups (not a game build)."""

import argparse
import hashlib
import json
import os
import re
import shutil
import struct
import subprocess
from pathlib import Path

import pefile

from snail.match import (
    DEFAULT_MATCH_ROOT,
    compile_scratch,
    evaluate_scratch,
    extract_object_function,
    load_scratch_config,
    parse_coff_object,
)
from snail.symbols import (
    DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH,
    REPO_ROOT,
    load_function_symbol_manifest,
)

PATH_MATH_FUNCTIONS = (
    "calc_path_length_z",
    "cross_vectors",
    "dot_vector",
    "invert_matrix_from_source",
)
GROUPS = {
    "path-math": PATH_MATH_FUNCTIONS,
    "rmath": PATH_MATH_FUNCTIONS
    + (
        "initialize_trigonometry_tables",
        "initialize_math_random_table",
        "next_math_random_value",
        "cosine",
        "sine",
        "square_root",
        "dot_vectors",
        "normalize_vector",
        "normalize_vector_from_source",
        "set_matrix_identity",
    ),
    "allocator": (
        "get_path_nodes",
        "allocate_tracked_memory",
        "free_tracked_memory",
        "push_tracked_allocation",
        "pop_tracked_allocation",
        "get_tracked_allocation_size",
        "initialize_tracked_allocation_depth",
        "set_tracked_allocation_mark",
        "free_tracked_allocations_to_mark",
        "report_errorf",
        "debug_report_stub",
    ),
}
GROUPS["mesh-storage"] = GROUPS["allocator"] + (
    "initialize_object_constructor_thunk",
    "initialize_object",
    "request_object_vertices",
    "request_object_vertex_colours",
    "request_object_vertices_copy",
    "copy_object_vertices",
    "request_object_facequads",
    "request_object_facequad_normals",
    "request_object_texture_groups",
    "request_object_edges",
)
GROUPS["path-nodes"] = (
    GROUPS["mesh-storage"]
    + PATH_MATH_FUNCTIONS
    + (
        "set_matrix_identity",
        "initialize_bod_base",
        "initialize_path_template_record_pair",
        "noop_this_constructor",
        "store_color4f",
        "noop_runtime_ai",
    )
)
RUN_CONFIG = {
    "rmath": (
        23,
        "!corrupt-table",
        "Selected math operations; CalcLengthZ is linked but not exercised",
    ),
    "allocator": (
        20,
        "!corrupt-payload",
        "Tracked allocator on valid LIFO inputs; GetNodes is linked but not exercised",
    ),
    "mesh-storage": (
        21,
        "!corrupt-copy",
        "cRObject construction and mesh allocations; no rendering or path lifecycle",
    ),
    "path-nodes": (
        15,
        "!corrupt-span",
        "GetNodes through CalcLengthZ on a constructed two-sample fixture; no template generator or rendering",
    ),
}
SBEND_FUNCTION = "initialize_sbend_path_template_pair"
GROUPS["sbend"] = tuple(
    dict.fromkeys(
        GROUPS["path-nodes"]
        + GROUPS["rmath"]
        + (
            "initialize_texture_list",
            "get_or_create_texture_ref",
            "copy_c_string",
            "strings_equal_case_insensitive",
            SBEND_FUNCTION,
        )
    )
)
RUN_CONFIG["sbend"] = (
    60,
    "!corrupt-face",
    "S-bend builder on four CPU geometry fixtures including UV wrap; no rendering",
)


def sha(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--group", choices=GROUPS, default="path-math")
    parser.add_argument(
        "--run",
        action="store_true",
        help="Build an integration executable and run positive/negative controls",
    )
    parser.add_argument(
        "--diagnostic-sbend",
        action="store_true",
        help="Allow only S-bend's reference-clean partial body for behavioral diagnostics; no exactness credit",
    )
    parser.add_argument(
        "--runtime-library",
        type=Path,
        required=True,
        help="Existing VC6 MSVCRT.LIB import library",
    )
    parser.add_argument(
        "--out", type=Path, default=REPO_ROOT / "artifacts/match/path-math"
    )
    args = parser.parse_args()
    if args.diagnostic_sbend and args.group != "sbend":
        parser.error("--diagnostic-sbend requires --group sbend")
    if args.run and args.group not in RUN_CONFIG:
        parser.error("--run requires a group with a runtime harness")
    runtime = args.runtime_library.resolve(strict=True)
    out = args.out.resolve()
    out.mkdir(parents=True, exist_ok=True)
    receipt_path = out / "receipt.json"
    receipt_path.unlink(missing_ok=True)

    objects = []
    records = []
    functions = []
    for name in GROUPS[args.group]:
        config = load_scratch_config(DEFAULT_MATCH_ROOT / "scratches" / name)
        if config.compiler != "msvc6.5":
            raise ValueError(f"{name}: expected the canonical VC6 profile")
        status = evaluate_scratch(config)
        diagnostic = (
            args.diagnostic_sbend
            and name == SBEND_FUNCTION
            and status.state == "wip"
            and not status.masked_unresolved
            and not status.masked_mismatches
            and not status.masked_unaudited
        )
        if status.state != "match" and not diagnostic:
            raise ValueError(
                f"{name}: requires an exact, reference-clean scratch: {status}"
            )
        obj_path = compile_scratch(config)
        function = extract_object_function(
            parse_coff_object(obj_path.read_bytes()), config.symbol or config.function
        )
        functions.append(function)
        # Unique filenames make the link map useful without changing the objects.
        copied = out / f"{name}.obj"
        shutil.copyfile(obj_path, copied)
        objects.append(copied)
        records.append(
            {
                "function": name,
                "symbol": function.name,
                "native_address": status.address,
                "native_bytes": status.target_size,
                "object_sha256": sha(copied),
                "source_sha256": sha(config.directory / "scratch.cpp"),
                "code_identity_sha256": status.code_sha256,
                "normalized_exact": status.state == "match",
                "native_match_ratio": status.ratio,
                "native_references_ok": status.masked_ok,
            }
        )

    support = []
    storage_groups = {
        "rmath": ["rmath"],
        "allocator": ["allocator"],
        "mesh-storage": ["allocator"],
        "path-nodes": ["allocator", "path-nodes"],
        "sbend": ["allocator", "path-nodes", "rmath", "texture"],
    }
    support_names = [f"{group}_storage" for group in storage_groups.get(args.group, [])]
    if args.run:
        support_names.append(f"{args.group}_smoke")
    for name in support_names:
        source = DEFAULT_MATCH_ROOT / f"link/{name}.cpp"
        obj = out / f"{name}.obj"
        obj.unlink(missing_ok=True)
        compiled = subprocess.run(
            [
                str(DEFAULT_MATCH_ROOT / "cl.sh"),
                "/c",
                "/O2",
                "/G5",
                "/W3",
                f"/FoZ:{obj}",
                f"Z:{source}",
            ],
            check=False,
            capture_output=True,
            text=True,
            env={**os.environ, "MSVC_VER": "msvc6.5"},
        )
        (out / f"{name}.compile.log").write_text(compiled.stdout + compiled.stderr)
        if compiled.returncode:
            raise RuntimeError(
                f"support compile failed; see {out / (name + '.compile.log')}"
            )
        objects.append(obj)
        support.append(
            {
                "source": str(source.relative_to(REPO_ROOT)),
                "source_sha256": sha(source),
                "object_sha256": sha(obj),
            }
        )

    linker = DEFAULT_MATCH_ROOT / "compilers/msvc6.5/Bin/LINK.EXE"
    runner = os.environ.get("WIBO") or str(DEFAULT_MATCH_ROOT / "bin/wibo")
    if not Path(runner).is_file():
        runner = shutil.which(runner) or shutil.which("wibo")
    if not runner:
        raise FileNotFoundError("Wibo is required, as for the regular matcher")

    dll = out / (f"{args.group}-smoke.exe" if args.run else f"{args.group}.dll")
    map_path = dll.with_suffix(".map")
    dll.unlink(missing_ok=True)
    map_path.unlink(missing_ok=True)
    options = [
        "/nologo",
        *(
            ["/subsystem:console", "/entry:mainCRTStartup"]
            if args.run
            else ["/dll", "/noentry"]
        ),
        "/nodefaultlib",
        "/opt:noref",
        f"/out:Z:{dll}",
        f"/map:Z:{map_path}",
        *(f"Z:{obj}" for obj in objects),
        f"Z:{runtime}",
    ]
    response = out / "link.rsp"
    if any('"' in option or "\n" in option for option in options):
        raise ValueError("linker paths must not contain quotes or newlines")
    response.write_text("\n".join(f'"{option}"' for option in options) + "\n")
    result = subprocess.run(
        [runner, str(linker), f"@Z:{response}"],
        capture_output=True,
        text=True,
        check=False,
    )
    (out / "link.log").write_text(result.stdout + result.stderr)
    if result.returncode or not dll.is_file():
        raise RuntimeError(f"link failed; see {out / 'link.log'}")

    symbols = {
        match[1]: int(match[2], 16)
        for match in re.finditer(
            r"^\s+[0-9A-Fa-f]{4}:[0-9A-Fa-f]{8}\s+(\S+)\s+([0-9A-Fa-f]{8})\b",
            map_path.read_text(),
            re.MULTILINE,
        )
    }
    pe = pefile.PE(str(dll))
    mapped = pe.get_memory_mapped_image()
    image_base = pe.OPTIONAL_HEADER.ImageBase
    data_tables = []
    if args.group in ("path-nodes", "sbend"):
        manifest = load_function_symbol_manifest(DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH)
        native = pefile.PE(str(REPO_ROOT / manifest.primary_target))
        for table, native_address in [
            ("?g_bod_base_vtable@@3PAXA", 0x4974FC),
            ("?g_path_template_record_vtable@@3PAXA", 0x497334),
        ]:
            native_target = struct.unpack(
                "<I",
                native.get_data(native_address - native.OPTIONAL_HEADER.ImageBase, 4),
            )[0]
            if native_target != 0x407B50:
                raise ValueError(f"native callback table changed: {table}")
            address = symbols[table]
            target = struct.unpack_from("<I", mapped, address - image_base)[0]
            if target != symbols["?noop_runtime_ai@@YAXXZ"]:
                raise ValueError(f"wrong recovered callback table entry: {table}")
            data_tables.append(
                {
                    "symbol": table,
                    "native_address": native_address,
                    "native_target": native_target,
                    "linked_address": address,
                    "linked_target": target,
                }
            )
    for record, function in zip(records, functions, strict=True):
        address = symbols[function.name]
        offset = address - image_base
        linked = mapped[offset : offset + len(function.data)]
        masked = {i for r in function.relocation_offsets for i in range(r, r + 4)}
        if len(linked) != len(function.data) or any(
            original != actual
            for i, (original, actual) in enumerate(
                zip(function.data, linked, strict=True)
            )
            if i not in masked
        ):
            raise ValueError(f"link changed non-relocation bytes in {function.name}")
        # Independently verify named REL32 call destinations, including the
        # Cross edge that failed to link under the compatibility declaration.
        obj = parse_coff_object((out / f"{record['function']}.obj").read_bytes())
        symbol = next(s for s in obj.symbols if s.name == function.name)
        by_index = {s.raw_index: s for s in obj.symbols}
        calls = []
        data_references = []
        local_data_references = []
        for relocation in obj.sections[symbol.section_number - 1].relocations:
            relative = relocation.virtual_address - symbol.value
            if not (0 <= relative < len(function.data)):
                continue
            target = by_index[relocation.symbol_index].name
            if relocation.relocation_type == 0x06:
                actual = struct.unpack_from("<I", linked, relative)[0]
                addend = struct.unpack_from("<i", function.data, relative)[0]
                if target in symbols:
                    if actual != (symbols[target] + addend) & 0xFFFFFFFF:
                        raise ValueError(f"wrong linked data address for {target}")
                    data_references.append(
                        {
                            "offset": relative,
                            "symbol": target,
                            "addend": addend,
                            "address": actual,
                        }
                    )
                else:
                    local_data_references.append({"offset": relative, "symbol": target})
                continue
            if relocation.relocation_type != 0x14:
                raise ValueError(
                    f"unsupported function relocation {relocation.relocation_type:#x}"
                )
            if target not in symbols:
                raise ValueError(f"missing linked call target {target}")
            addend = struct.unpack_from("<i", function.data, relative)[0]
            actual = (
                address + relative + 4 + struct.unpack_from("<i", linked, relative)[0]
            )
            if actual != symbols[target] + addend:
                raise ValueError(
                    f"wrong linked destination for {function.name} -> {target}"
                )
            calls.append({"offset": relative, "symbol": target, "address": actual})
        record.update(
            {
                "linked_address": address,
                "object_body_bytes": len(function.data),
                "non_relocation_bytes_preserved": True,
                "verified_rel32_calls": calls,
                "verified_named_data_references": data_references,
                "local_data_references_not_map_verified": local_data_references,
            }
        )
    imports = [
        {
            "dll": entry.dll.decode(),
            "symbols": [
                item.name.decode() if item.name else item.ordinal
                for item in entry.imports
            ],
        }
        for entry in getattr(pe, "DIRECTORY_ENTRY_IMPORT", [])
    ]
    runs = []
    if args.run:
        expected_checks, negative_argument, _ = RUN_CONFIG[args.group]
        for label, extra, expected in [
            ("positive", [], 0),
            ("negative", [negative_argument], 1),
        ]:
            run = subprocess.run(
                [runner, str(dll), *extra],
                capture_output=True,
                text=True,
                timeout=20,
                check=False,
            )
            (out / f"{label}.log").write_text(run.stdout + run.stderr)
            summary = re.search(
                rf"{args.group} checks=(\d+) failures=(\d+)", run.stdout
            )
            if (
                run.returncode != expected
                or not summary
                or int(summary[1]) != expected_checks
                or bool(int(summary[2])) != bool(expected)
            ):
                raise ValueError(
                    f"{label} runtime control failed; see {out / (label + '.log')}"
                )
            runs.append(
                {
                    "label": label,
                    "exit_code": run.returncode,
                    "checks": int(summary[1]),
                    "failures": int(summary[2]),
                    "stdout": run.stdout,
                }
            )
    receipt = {
        "schema": 1,
        "purpose": "Source-object link feasibility; not an executable reconstruction",
        "group": args.group,
        "diagnostic_partial_functions": [
            r["function"] for r in records if not r["normalized_exact"]
        ],
        "support": support,
        "entry_point": pe.OPTIONAL_HEADER.AddressOfEntryPoint,
        "runtime_execution_tested": bool(args.run),
        "runtime_scope": RUN_CONFIG[args.group][2] if args.run else None,
        "runs": runs,
        "public_linked_credit": False,
        "linker_sha256": sha(linker),
        "runtime_library": str(runtime),
        "runtime_library_sha256": sha(runtime),
        "dll_sha256": sha(dll),
        "imports": imports,
        "functions": records,
        "verified_callback_tables": data_tables,
    }
    receipt_path.write_text(json.dumps(receipt, indent=2) + "\n")
    partial_count = sum(not record["normalized_exact"] for record in records)
    if partial_count:
        print(
            f"Linked {len(records) - partial_count} exact functions and {partial_count} diagnostic partial: {receipt_path}"
        )
    else:
        print(f"Linked and verified {len(records)} recovered functions: {receipt_path}")


if __name__ == "__main__":
    main()
