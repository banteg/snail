#!/usr/bin/env python3
"""Compare the partial quaternion constructor with audited original code.

This is a behavioral diagnostic, with no source-matching or linked credit.
The unchanged source and native bodies run in otherwise identical executables.
"""

import argparse
import fcntl
import json
import os
import shutil
import subprocess
from pathlib import Path

from compare_sbend_native import digest, make_oracle, verify_oracle_link
from link_path_math import support_inputs

from snail.match import (
    DEFAULT_MATCH_ROOT,
    DEFAULT_REFERENCE_SYMBOL_MANIFEST_PATH,
    CoffRelocation,
    compile_scratch,
    extract_object_function,
    load_scratch_config,
    object_function_fingerprint,
    parse_coff_object,
    run_match,
    scratch_dependency_sha256,
)
from snail.match_link import load_link_symbols, verify_relocated_bytes
from snail.symbols import (
    DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH,
    REPO_ROOT,
    load_function_symbol_manifest,
)

FUNCTION = "initialize_quaternion_from_matrix"


def checked_run(command, log, **kwargs):
    result = subprocess.run(command, capture_output=True, text=True, check=False, **kwargs)
    log.write_text(result.stdout + result.stderr)
    if result.returncode:
        raise ValueError(f"command failed; see {log}")
    return result


def compare(runtime, out):
    receipt_path = out / "comparison.json"
    receipt_path.unlink(missing_ok=True)
    runner_name = os.environ.get("WIBO") or str(DEFAULT_MATCH_ROOT / "bin/wibo")
    runner = str(Path(shutil.which(runner_name) or runner_name).resolve(strict=True))
    linker = DEFAULT_MATCH_ROOT / "compilers/msvc6.5/Bin/LINK.EXE"
    binary_inputs = {str(path): digest(path.read_bytes())
                     for path in (runtime, linker, Path(runner))}

    manifest = load_function_symbol_manifest(DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH)
    native_path = REPO_ROOT / manifest.primary_target
    if digest(native_path.read_bytes()) != manifest.unwrapped_sha256:
        raise ValueError("native image differs from the matching manifest")
    verification_paths = (
        Path(__file__).resolve(), DEFAULT_MATCH_ROOT / "compare_sbend_native.py",
        DEFAULT_MATCH_ROOT / "link_path_math.py", REPO_ROOT / "src/snail/match_link.py",
        REPO_ROOT / "src/snail/match.py", REPO_ROOT / "src/snail/symbols.py",
        DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH, DEFAULT_REFERENCE_SYMBOL_MANIFEST_PATH,
        native_path,
    )
    verification_inputs = {str(path.relative_to(REPO_ROOT)): digest(path.read_bytes())
                           for path in verification_paths}
    output_inputs = {}
    objects = []
    records = []
    for name in (FUNCTION, "square_root", "debug_report_stub"):
        config = load_scratch_config(DEFAULT_MATCH_ROOT / "scratches" / name)
        dependency_sha256 = scratch_dependency_sha256(config)
        config_sha256 = digest((config.directory / "scratch.conf").read_bytes())
        if config.compiler != "msvc6.5":
            raise ValueError("diagnostic requires the canonical compiler profile")
        obj = out / f"{name}.obj"
        # Gate the same immutable per-output copy that will be linked. Another
        # process may rebuild the shared scratch output after compile_scratch.
        obj.write_bytes(compile_scratch(config).read_bytes())
        output_inputs[str(obj)] = digest(obj.read_bytes())
        match = run_match(
            obj_path=obj, function_name=name, image_path=native_path,
            manifest=manifest, symbol_name=config.symbol, end_va=config.end_va,
        )
        if match.masked_operand_audit.problem_count:
            raise ValueError(f"{name}: requires a clean native reference audit")
        if name != FUNCTION and match.ratio != 1.0:
            raise ValueError(f"{name}: dependency must match exactly")
        function = extract_object_function(
            parse_coff_object(obj.read_bytes()), config.symbol or config.function
        )
        objects.append(obj)
        records.append({
            "function": name,
            "symbol": function.name,
            "source_sha256": digest((config.directory / "scratch.cpp").read_bytes()),
            "dependency_sha256": dependency_sha256,
            "config_sha256": config_sha256,
            "compiler": config.compiler,
            "cflags": config.cflags,
            "object_sha256": digest(obj.read_bytes()),
            "native_match_ratio": match.ratio,
            "native_references_ok": match.masked_operand_audit.ok_count,
            "code_identity_sha256": object_function_fingerprint(function),
        })

    fixture = DEFAULT_MATCH_ROOT / "link/quaternion_smoke.cpp"
    fixture_inputs = support_inputs(fixture)
    fixture_obj = out / "quaternion_smoke.obj"
    fixture_obj.unlink(missing_ok=True)
    checked_run(
        [str(DEFAULT_MATCH_ROOT / "cl.sh"), "/c", "/O2", "/G5", "/W3",
         f"/FoZ:{fixture_obj}", f"Z:{fixture}"],
        out / "fixture.compile.log",
        env={**os.environ, "MSVC_VER": "msvc6.5"},
    )
    objects.append(fixture_obj)
    output_inputs[str(fixture_obj)] = digest(fixture_obj.read_bytes())
    native_obj = out / "native-oracle.obj"
    proof = make_oracle(native_obj, function_name=FUNCTION, source_object=objects[0])
    output_inputs[str(native_obj)] = digest(native_obj.read_bytes())
    traces = {}
    linked_proofs = {}
    runs = []
    for label in ("source", "native"):
        linked_objects = ([native_obj, *objects[1:]] if label == "native" else objects)
        executable = out / f"{label}.exe"
        map_path = executable.with_suffix(".map")
        executable.unlink(missing_ok=True)
        map_path.unlink(missing_ok=True)
        options = [
            "/nologo", "/subsystem:console", "/entry:mainCRTStartup",
            "/nodefaultlib", "/opt:noref", "/debug", "/debugtype:coff",
            "/pdb:none", "/incremental:no", f"/out:Z:{executable}",
            f"/map:Z:{map_path}", *(f"Z:{obj}" for obj in linked_objects),
            f"Z:{runtime}",
        ]
        if any('"' in option or "\n" in option for option in options):
            raise ValueError("linker paths must not contain quotes or newlines")
        response = out / f"{label}.rsp"
        response.write_text("\n".join(f'"{option}"' for option in options) + "\n")
        output_inputs[str(response)] = digest(response.read_bytes())
        checked_run([runner, str(linker), f"@Z:{response}"], out / f"{label}.link.log")
        for path in (executable, map_path):
            output_inputs[str(path)] = digest(path.read_bytes())
        if label == "native":
            proof["native_link_inputs"] = verify_oracle_link(executable, map_path, native_obj, proof)

        pe, symbols = load_link_symbols(executable, map_path)
        parsed = {obj.name: parse_coff_object(obj.read_bytes()) for obj in linked_objects}
        symbols.bind_objects(parsed)
        mapped = pe.get_memory_mapped_image()
        verified = []
        for record, path in zip(records, linked_objects[:len(records)], strict=True):
            if label == "native" and record["function"] == FUNCTION:
                continue  # Original body was independently verified above.
            obj = parsed[path.name]
            function = extract_object_function(obj, record["symbol"])
            symbol = next(s for s in obj.symbols if s.name == function.name)
            relocations = tuple(
                CoffRelocation(r.virtual_address - symbol.value,
                               r.symbol_index, r.relocation_type)
                for r in obj.sections[symbol.section_number - 1].relocations
                if symbol.value <= r.virtual_address < symbol.value + len(function.data)
            )
            address = symbols.resolve(function.name, path.name)
            offset = address - pe.OPTIONAL_HEADER.ImageBase
            references = verify_relocated_bytes(
                function.data, mapped[offset:offset + len(function.data)],
                address, relocations, obj, symbols, path.name,
            )
            verified.append({
                "function": record["function"],
                "object": path.name,
                "linked_address": address,
                "code_bytes": len(function.data),
                "verified_references": references,
                "non_relocation_bytes_preserved": True,
            })
        linked_proofs[label] = verified

        trace = out / f"{label}.bin"
        trace.unlink(missing_ok=True)
        run = checked_run([runner, str(executable), f"Z:{trace}"],
                          out / f"{label}.run.log", timeout=20)
        if "quaternion cases=10 failures=0" not in run.stdout:
            raise ValueError("missing complete quaternion fixture run")
        traces[label] = trace.read_bytes()
        runs.append({"executable": label, "control": "positive",
                     "exit_code": run.returncode, "cases": 10, "failures": 0,
                     "output_sha256": digest(traces[label])})
        negative_trace = out / f"{label}-negative.bin"
        negative_trace.unlink(missing_ok=True)
        negative = subprocess.run(
            [runner, str(executable), f"Z:{negative_trace}", "!difference"],
            capture_output=True, text=True, timeout=20, check=False,
        )
        (out / f"{label}.negative.log").write_text(negative.stdout + negative.stderr)
        if negative.returncode != 1 or "quaternion cases=10 failures=1" not in negative.stdout:
            raise ValueError("fallback w-difference negative control did not fail")
        if negative_trace.read_bytes() == traces[label]:
            raise ValueError("negative control did not alter serialized output")
        runs.append({"executable": label, "control": "fallback-w-difference",
                     "exit_code": negative.returncode, "cases": 10, "failures": 1,
                     "output_sha256": digest(negative_trace.read_bytes())})

    if len(traces["source"]) != 10 * 16 or traces["source"] != traces["native"]:
        raise ValueError("source/native quaternion bytes differ")
    for record in records:
        config = load_scratch_config(DEFAULT_MATCH_ROOT / "scratches" / record["function"])
        if (scratch_dependency_sha256(config) != record["dependency_sha256"]
                or digest((config.directory / "scratch.conf").read_bytes()) != record["config_sha256"]):
            raise ValueError("source compilation inputs changed during diagnostic")
    if support_inputs(fixture) != fixture_inputs:
        raise ValueError("fixture compilation inputs changed during diagnostic")
    if any(digest(Path(path).read_bytes()) != expected
           for path, expected in binary_inputs.items()):
        raise ValueError("linker, runtime import library or runner changed during diagnostic")
    if any(digest((REPO_ROOT / path).read_bytes()) != expected
           for path, expected in verification_inputs.items()):
        raise ValueError("native inputs or verification sources changed during diagnostic")
    if any(digest(Path(path).read_bytes()) != expected
           for path, expected in output_inputs.items()):
        raise ValueError("objects, executables, link maps or response files changed during diagnostic")
    proof.update({
        "purpose": "Original-code behavioral oracle; not reconstructed source",
        "original_code_used": True,
        "public_matching_credit": False,
        "public_linked_credit": False,
        "functions": records,
        "linked_source_functions": linked_proofs,
        "fixture_inputs": fixture_inputs,
        "fixture_cflags": "/c /O2 /G5 /W3",
        "binary_inputs": binary_inputs,
        "verification_inputs": verification_inputs,
        "output_artifacts": output_inputs,
        "cases": 10,
        "runs": runs,
        "source_and_native_negative_controls": "fallback w difference rejected",
        "serialized_quaternion_bytes": len(traces["source"]),
        "serialized_quaternion_sha256": digest(traces["source"]),
        "serialized_quaternion_byte_equal": True,
    })
    receipt_path.write_text(json.dumps(proof, indent=2) + "\n")
    print(f"Source and native quaternion outputs agree for 10 fixtures: {receipt_path}")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--runtime-library", type=Path, required=True)
    parser.add_argument(
        "--out", type=Path, default=REPO_ROOT / "artifacts/match/quaternion-comparison"
    )
    args = parser.parse_args()
    runtime = args.runtime_library.resolve(strict=True)
    out = args.out.resolve()
    out.mkdir(parents=True, exist_ok=True)
    with (out / ".comparison.lock").open("a") as lock:
        try:
            fcntl.flock(lock, fcntl.LOCK_EX | fcntl.LOCK_NB)
        except BlockingIOError as error:
            raise ValueError(f"another comparison owns {out}") from error
        compare(runtime, out)


if __name__ == "__main__":
    main()
