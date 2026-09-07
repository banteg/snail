#!/usr/bin/env python3
"""Link and verify the recovered CalcLengthZ dependency group (not a game build)."""

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
from snail.symbols import REPO_ROOT

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
}


def sha(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--group", choices=GROUPS, default="path-math")
    parser.add_argument(
        "--run",
        action="store_true",
        help="Build the rmath integration executable and run positive/negative controls",
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
    if args.run and args.group != "rmath":
        parser.error("--run requires --group rmath")
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
        if status.state != "match":
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
                "normalized_exact": True,
                "native_references_ok": status.masked_ok,
            }
        )

    support = []
    support_names = ["rmath_storage"] if args.group == "rmath" else []
    if args.run:
        support_names.append("rmath_smoke")
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

    dll = out / ("rmath-smoke.exe" if args.run else f"{args.group}.dll")
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
        for label, extra, expected in [
            ("positive", [], 0),
            ("negative", ["!corrupt-table"], 1),
        ]:
            run = subprocess.run(
                [runner, str(dll), *extra],
                capture_output=True,
                text=True,
                timeout=20,
                check=False,
            )
            (out / f"{label}.log").write_text(run.stdout + run.stderr)
            summary = re.search(r"rmath checks=(\d+) failures=(\d+)", run.stdout)
            if (
                run.returncode != expected
                or not summary
                or int(summary[1]) != 23
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
        "support": support,
        "entry_point": pe.OPTIONAL_HEADER.AddressOfEntryPoint,
        "runtime_execution_tested": bool(args.run),
        "runtime_scope": "Selected math operations; CalcLengthZ is linked but not exercised",
        "runs": runs,
        "public_linked_credit": False,
        "linker_sha256": sha(linker),
        "runtime_library": str(runtime),
        "runtime_library_sha256": sha(runtime),
        "dll_sha256": sha(dll),
        "imports": imports,
        "functions": records,
    }
    receipt_path.write_text(json.dumps(receipt, indent=2) + "\n")
    print(f"Linked and verified {len(records)} recovered functions: {receipt_path}")


if __name__ == "__main__":
    main()
