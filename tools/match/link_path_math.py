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

FUNCTIONS = (
    "calc_path_length_z",
    "cross_vectors",
    "dot_vector",
    "invert_matrix_from_source",
)


def sha(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
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
    runtime = args.runtime_library.resolve(strict=True)
    out = args.out.resolve()
    out.mkdir(parents=True, exist_ok=True)
    receipt_path = out / "receipt.json"
    receipt_path.unlink(missing_ok=True)

    objects = []
    records = []
    functions = []
    for name in FUNCTIONS:
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

    linker = DEFAULT_MATCH_ROOT / "compilers/msvc6.5/Bin/LINK.EXE"
    runner = os.environ.get("WIBO") or str(DEFAULT_MATCH_ROOT / "bin/wibo")
    if not Path(runner).is_file():
        runner = shutil.which(runner) or shutil.which("wibo")
    if not runner:
        raise FileNotFoundError("Wibo is required, as for the regular matcher")

    dll = out / "path-math.dll"
    map_path = out / "path-math.map"
    dll.unlink(missing_ok=True)
    map_path.unlink(missing_ok=True)
    options = [
        "/nologo",
        "/dll",
        "/noentry",
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
        for relocation in obj.sections[symbol.section_number - 1].relocations:
            relative = relocation.virtual_address - symbol.value
            if (
                not (0 <= relative < len(function.data))
                or relocation.relocation_type != 0x14
            ):
                continue
            target = by_index[relocation.symbol_index].name
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
    receipt = {
        "schema": 1,
        "purpose": "CalcLengthZ source-object link feasibility; not an executable reconstruction",
        "entry_point": pe.OPTIONAL_HEADER.AddressOfEntryPoint,
        "runtime_execution_tested": False,
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
