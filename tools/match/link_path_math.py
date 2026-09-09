#!/usr/bin/env python3
"""Link and exercise recovered dependency groups (not a game build)."""

import argparse
import fcntl
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
    DEFAULT_REFERENCE_SYMBOL_MANIFEST_PATH,
    CoffRelocation,
    _ScratchIncludeResolver,
    compile_scratch,
    extract_object_function,
    load_default_reference_symbol_manifest,
    load_image,
    load_scratch_config,
    object_function_fingerprint,
    parse_coff_object,
    resolve_function_extent,
    run_match,
    scratch_dependency_sha256,
)
from snail.match_link import (
    load_link_symbols,
    verify_code_sections,
    verify_data_sections,
    verify_relocated_bytes,
)
from snail.match_storage import verify_native_storage
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
    "rtext": (
        "copy_c_string",
        "strings_equal_case_insensitive",
        "skip_to_next_line",
        "append_c_string",
        "parse_next_space_delimited_token",
        "parse_next_int32",
        "parse_next_float32",
    ),
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
GROUPS["transforms"] = GROUPS["rmath"] + (
    "vector_magnitude",
    "multiply_vector_by_matrix",
    "multiply_vector_by_matrix_copy",
    "rotate_vector_by_matrix",
    "initialize_uniform_scale_matrix",
    "initialize_matrix_from_values",
    "set_matrix_rotation_identity",
    "invert_matrix_in_place",
    "rotate_matrix_world_x",
    "rotate_matrix_world_y",
    "rotate_matrix_world_z",
    "set_matrix_z_direction",
    "look_at_point",
    "orthogonalize_matrix",
    "multiply_matrices",
    "multiply_matrix_assign",
    "multiply_matrix",
    "premultiply_matrix_in_place",
)
GROUPS["bod-list"] = (
    "add_bod_to_front",
    "append_bod_to_end",
    "recycle_bod_to_free_list",
    "report_errorf",
    "debug_report_stub",
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
    "rtext": (
        22,
        "!corrupt-token",
        "RShell text helpers through their shared declarations on delimiter-terminated fixtures; no bounded-input or general parser safety claim",
    ),
    "bod-list": (
        21,
        "!corrupt-free-chain",
        "Intrusive active/free lists, duplicate-operation and saved-next guards, independent owners; fixture storage only, no pool allocator or constructors",
    ),
    "transforms": (
        40,
        "!corrupt-table",
        "Math checks plus transform constructors, composition, aliasing, rotation and direction; no rendering",
    ),
    "rmath": (
        23,
        "!corrupt-table",
        "Selected math operations; CalcLengthZ is linked but not exercised",
    ),
    "allocator": (
        24,
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


def support_inputs(source: Path) -> dict[str, str]:
    """Pin support sources, nested includes and the actual VC6 components."""
    resolver = _ScratchIncludeResolver(DEFAULT_MATCH_ROOT)
    paths = {source.resolve(), DEFAULT_MATCH_ROOT / "cl.sh"}
    pending = [source]
    while pending:
        for dependency in resolver.direct_dependencies(pending.pop(), source=False):
            if dependency not in paths:
                paths.add(dependency)
                pending.append(dependency)
    binary = DEFAULT_MATCH_ROOT / "compilers/msvc6.5/Bin"
    paths.add(binary / "CL.EXE")
    paths.update(path for path in binary.iterdir() if path.suffix.lower() == ".dll")
    return {str(path.relative_to(REPO_ROOT)): sha(path) for path in sorted(paths)}


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
    runtime_sha256 = sha(runtime)
    manifest = load_function_symbol_manifest(DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH)
    native_path = REPO_ROOT / manifest.primary_target
    if sha(native_path) != manifest.unwrapped_sha256:
        raise ValueError("native image differs from the matching manifest")
    verification_paths = (
        Path(__file__).resolve(),
        REPO_ROOT / "src/snail/match_link.py",
        REPO_ROOT / "src/snail/match_storage.py",
        REPO_ROOT / "src/snail/match.py",
        REPO_ROOT / "src/snail/symbols.py",
        DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH,
        DEFAULT_REFERENCE_SYMBOL_MANIFEST_PATH,
    )
    verification_inputs = {
        str(path.relative_to(REPO_ROOT)): sha(path) for path in verification_paths
    }
    out = args.out.resolve()
    out.mkdir(parents=True, exist_ok=True)
    output_lock = (out / ".lock").open("a")
    try:
        fcntl.flock(output_lock, fcntl.LOCK_EX | fcntl.LOCK_NB)
    except BlockingIOError as error:
        raise ValueError(f"another integration build is using {out}") from error
    receipt_path = out / "receipt.json"
    receipt_path.unlink(missing_ok=True)

    objects = []
    records = []
    functions = []
    configs = []
    for name in GROUPS[args.group]:
        config = load_scratch_config(DEFAULT_MATCH_ROOT / "scratches" / name)
        configs.append(config)
        dependency_sha256 = scratch_dependency_sha256(config)
        config_sha256 = sha(config.directory / "scratch.conf")
        if config.compiler != "msvc6.5":
            raise ValueError(f"{name}: expected the canonical VC6 profile")
        # Match the immutable per-output copy that will actually be linked.
        # The canonical build cache may be replaced by a parallel match task.
        copied = out / f"{name}.obj"
        copied.write_bytes(compile_scratch(config).read_bytes())
        object_sha256 = sha(copied)
        result = run_match(
            obj_path=copied,
            function_name=config.function,
            image_path=native_path,
            manifest=manifest,
            symbol_name=config.symbol,
            end_va=config.end_va,
        )
        audit = result.masked_operand_audit
        reference_clean = not (
            audit.unresolved_count or audit.mismatch_count or audit.unaudited_count
        )
        exact = result.ratio == 1.0 and reference_clean
        diagnostic = (
            args.diagnostic_sbend
            and name == SBEND_FUNCTION
            and result.ratio < 1.0
            and reference_clean
        )
        if not exact and not diagnostic:
            raise ValueError(
                f"{name}: requires an exact, reference-clean scratch; ratio={result.ratio} audit={audit}"
            )
        function = extract_object_function(
            parse_coff_object(copied.read_bytes()),
            config.symbol or config.function,
            reference_manifest=load_default_reference_symbol_manifest(),
        )
        functions.append(function)
        address, end = resolve_function_extent(manifest, config.function, config.end_va)
        native_bytes = len(
            load_image(native_path, manifest.image_base).function_bytes(address, end)
        )
        objects.append(copied)
        records.append(
            {
                "function": name,
                "symbol": function.name,
                "native_address": address,
                "native_bytes": native_bytes,
                "object_sha256": object_sha256,
                "source_sha256": sha(config.directory / "scratch.cpp"),
                "dependency_sha256": dependency_sha256,
                "config_sha256": config_sha256,
                "code_identity_sha256": object_function_fingerprint(function),
                "normalized_exact": exact,
                "native_match_ratio": result.ratio,
                "native_references_ok": audit.ok_count,
            }
        )

    support = []
    storage_groups = {
        "transforms": ["rmath"],
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
        inputs = support_inputs(source)
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
                "inputs": inputs,
            }
        )

    linker = DEFAULT_MATCH_ROOT / "compilers/msvc6.5/Bin/LINK.EXE"
    linker_sha256 = sha(linker)
    runner = os.environ.get("WIBO") or str(DEFAULT_MATCH_ROOT / "bin/wibo")
    if not Path(runner).is_file():
        runner = shutil.which(runner) or shutil.which("wibo")
    if not runner:
        raise FileNotFoundError("Wibo is required, as for the regular matcher")
    runner_sha256 = sha(Path(runner))

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
        "/debug",
        "/debugtype:coff",
        "/pdb:none",
        "/incremental:no",
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

    dll_sha256, map_sha256 = sha(dll), sha(map_path)
    pe, link_symbols = load_link_symbols(dll, map_path)
    input_objects = {
        path.name: parse_coff_object(path.read_bytes()) for path in objects
    }
    link_symbols.bind_objects(input_objects)
    symbols = {
        name: next(iter(addresses))
        for name, addresses in link_symbols.addresses.items()
        if len(addresses) == 1
    }
    mapped = pe.get_memory_mapped_image().ljust(pe.OPTIONAL_HEADER.SizeOfImage, b"\0")
    image_base = pe.OPTIONAL_HEADER.ImageBase
    data_tables = []
    if args.group in ("path-nodes", "sbend"):
        native = pefile.PE(str(native_path))
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
        link_symbols.section_for_span(address, len(function.data), code=True)
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
        owner = f"{record['function']}.obj"
        obj = input_objects[owner]
        symbol = next(s for s in obj.symbols if s.name == function.name)
        relocations = tuple(
            CoffRelocation(
                r.virtual_address - symbol.value, r.symbol_index, r.relocation_type
            )
            for r in obj.sections[symbol.section_number - 1].relocations
            if symbol.value <= r.virtual_address < symbol.value + len(function.data)
        )
        references = verify_relocated_bytes(
            function.data,
            linked,
            address,
            relocations,
            obj,
            link_symbols,
            owner,
        )
        record.update(
            {
                "linked_address": address,
                "object_body_bytes": len(function.data),
                "non_relocation_bytes_preserved": True,
                "verified_rel32_calls": [r for r in references if r["type"] == "REL32"],
                "verified_named_data_references": [
                    r for r in references if r["type"] == "DIR32"
                ],
                "local_data_references_not_map_verified": [],
            }
        )
    storage = verify_data_sections(
        input_objects,
        mapped,
        image_base,
        link_symbols,
    )
    code_sections = verify_code_sections(
        input_objects, mapped, image_base, link_symbols
    )
    native_storage = verify_native_storage(
        input_objects,
        pefile.PE(str(native_path)),
        json.loads(DEFAULT_REFERENCE_SYMBOL_MANIFEST_PATH.read_text())["symbols"],
        records,
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
    # A receipt must bind one stable build, even when another matching lane is
    # editing shared headers or sources while the integration check runs.
    for config, record in zip(configs, records, strict=True):
        if (
            scratch_dependency_sha256(config) != record["dependency_sha256"]
            or sha(config.directory / "scratch.conf") != record["config_sha256"]
        ):
            raise ValueError(
                f"scratch inputs changed during verification: {config.function}"
            )
        if sha(out / f"{record['function']}.obj") != record["object_sha256"]:
            raise ValueError(
                f"copied object changed during verification: {config.function}"
            )
    for record in support:
        if support_inputs(REPO_ROOT / record["source"]) != record["inputs"]:
            raise ValueError(
                f"support inputs changed during verification: {record['source']}"
            )
        if sha(out / (Path(record["source"]).stem + ".obj")) != record["object_sha256"]:
            raise ValueError(
                f"support object changed during verification: {record['source']}"
            )
    if (
        {str(path.relative_to(REPO_ROOT)): sha(path) for path in verification_paths}
        != verification_inputs
        or sha(native_path) != manifest.unwrapped_sha256
        or sha(runtime) != runtime_sha256
        or sha(linker) != linker_sha256
        or sha(Path(runner)) != runner_sha256
        or sha(dll) != dll_sha256
        or sha(map_path) != map_sha256
    ):
        raise ValueError("verification inputs changed during the build")
    receipt = {
        "schema": 2,
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
        "native_image_sha256": manifest.unwrapped_sha256,
        "runner_sha256": runner_sha256,
        "linker_sha256": linker_sha256,
        "runtime_library": str(runtime),
        "runtime_library_sha256": runtime_sha256,
        "dll_sha256": dll_sha256,
        "map_sha256": map_sha256,
        "imports": imports,
        "functions": records,
        "verified_callback_tables": data_tables,
        "storage": storage,
        "source_code_sections": code_sections,
        "native_storage": native_storage,
        "verification_sources": verification_inputs,
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
