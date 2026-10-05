"""Capture VC6 frontend streams and replay the backend standalone (diagnostic only).

Vendored from Crimson's `crimson_re.match_c2_replay`. The compiler bundle is the
scratch's own; helper programs link against that bundle's KERNEL32.LIB.
"""

import hashlib
import json
import shutil
import subprocess
from pathlib import Path

from snail import match

HERE = Path(__file__).resolve().parent / "observer"
WIBO = match.DEFAULT_MATCH_ROOT / "bin/wibo"
SUFFIXES = ("ex", "in", "sy", "gl")
# Set by the observer for the scratch being traced; defaults to the baseline.
COMPILER = match.DEFAULT_MATCH_ROOT / "compilers" / match.DEFAULT_SCRATCH_COMPILER


def sha(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def windows_path(path: Path) -> str:
    result = "Z:" + str(path.resolve()).replace("/", "\\")
    if len(result.encode("ascii")) >= 240:
        raise ValueError("Use a shorter ASCII output path for this VC6 diagnostic")
    return result


def bundle_file(name: str) -> Path:
    """A compiler-bundle file, whatever its on-disk case."""
    directory, _, leaf = name.rpartition("/")
    folder = COMPILER / directory
    for path in folder.iterdir():
        if path.name.lower() == leaf.lower():
            return path
    raise FileNotFoundError(f"{folder}/{leaf}")


def run(arguments, directory, *, check=True):
    result = subprocess.run(
        [str(argument) for argument in arguments],
        cwd=directory,
        capture_output=True,
        text=True,
        timeout=60,
        check=False,
    )
    if check and result.returncode:
        raise RuntimeError(f"Command failed ({result.returncode}): {arguments}\n{result.stdout}{result.stderr}")
    return result


def normalized_coff(path: Path) -> bytes:
    data = bytearray(path.read_bytes())
    match.parse_coff_object(bytes(data))
    data[4:8] = bytes(4)  # Only the IMAGE_FILE_HEADER timestamp is ignored.
    return bytes(data)


# Kernel32 functions the capture, replay and observer helpers call, with their
# stdcall argument bytes. The decomp.me bundles ship no Lib directory.
KERNEL32_IMPORTS = {
    "CloseHandle": 4,
    "CreateFileA": 28,
    "ExitProcess": 4,
    "GetEnvironmentVariableA": 12,
    "GetProcAddress": 8,
    "LoadLibraryA": 4,
    "ReadFile": 20,
    "VirtualProtect": 16,
    "WriteFile": 20,
}


def alias_object(aliases: dict[str, str]) -> bytes:
    """A COFF object whose weak externals resolve each alias to its target."""
    import struct

    strings = bytearray()
    symbols = bytearray()

    def name_field(name: str) -> bytes:
        raw = name.encode("ascii")
        if len(raw) <= 8:
            return raw.ljust(8, b"\0")
        offset = 4 + len(strings)
        strings.extend(raw + b"\0")
        return struct.pack("<II", 0, offset)

    index = 0
    for alias, target in aliases.items():
        symbols += name_field(target) + struct.pack("<IhHBB", 0, 0, 0, 2, 0)
        symbols += name_field(alias) + struct.pack("<IhHBB", 0, 0, 0, 105, 1)
        symbols += struct.pack("<II10x", index, 3)  # IMAGE_WEAK_EXTERN_SEARCH_ALIAS
        index += 3
    header = struct.pack("<HHIIIHH", 0x14C, 0, 0, 20, index, 0, 0)
    return header + bytes(symbols) + struct.pack("<I", 4 + len(strings)) + bytes(strings)


def import_inputs():
    """Undecorated KERNEL32 import library plus decorated-name aliases."""
    import tempfile

    cache = Path(tempfile.gettempdir()) / "snail-c2-imports" / sha(bundle_file("Bin/LIB.EXE").read_bytes())[:16]
    library, aliases = cache / "kernel32.lib", cache / "aliases.obj"
    if not (library.is_file() and aliases.is_file()):
        cache.mkdir(parents=True, exist_ok=True)
        (cache / "kernel32.def").write_text(
            "LIBRARY KERNEL32.dll\nEXPORTS\n" + "".join(f" {name}\n" for name in KERNEL32_IMPORTS)
        )
        run([WIBO, bundle_file("Bin/LIB.EXE"), "/nologo", "/DEF:kernel32.def", "/MACHINE:IX86",
             "/OUT:kernel32.lib"], cache)
        aliases.write_bytes(alias_object({
            f"{prefix}{name}@{size}": f"{prefix}{name}"
            for name, size in KERNEL32_IMPORTS.items()
            for prefix in ("__imp__", "_")
        }))
    return [library, aliases]


def link(directory, output, object_name, *, dll=False):
    arguments = [
        WIBO,
        bundle_file("Bin/LINK.EXE"),
        "/nologo",
        "/nodefaultlib",
        "/dll" if dll else "/subsystem:console",
        "/entry:DllMain@12" if dll else "/entry:start@0",
        "/out:" + output,
        object_name,
        *(windows_path(path) for path in import_inputs()),
    ]
    run(arguments, directory)


def compile_driver(directory, source_name, object_name):
    run(
        [match.DEFAULT_MATCH_ROOT / "cl.sh", "/c", "/O2", "/Fo" + object_name, source_name],
        directory,
    )


def read_arguments(capture):
    raw = (capture / "arguments.bin").read_bytes()
    if not raw.endswith(b"\0"):
        raise ValueError("Captured backend argv is not NUL terminated")
    arguments = [value.decode("ascii") for value in raw[:-1].split(b"\0")]
    if arguments.count("-il") != 1 or arguments[-1] == "-il":
        raise ValueError("Expected one backend -il prefix argument")
    index = arguments.index("-il") + 1
    original_prefix = arguments[index]
    basename = original_prefix.replace("\\", "/").rsplit("/", 1)[-1]
    if not basename or ":" in basename or basename in (".", ".."):
        raise ValueError("Invalid captured stream basename")
    streams = {suffix: capture / (basename + suffix) for suffix in SUFFIXES}
    if not all(path.is_file() and path.stat().st_size for path in streams.values()):
        raise ValueError("Missing or empty captured backend stream")
    arguments[0] = windows_path(bundle_file("Bin/C2.DLL"))
    arguments[index] = windows_path(capture / basename)
    output_indices = [index for index, argument in enumerate(arguments) if argument.startswith("-Fo")]
    if len(output_indices) != 1:
        raise ValueError("Expected one backend output argument")
    arguments[output_indices[0]] = "-Foreplay.obj"
    return arguments, streams


def build_replay(directory, arguments):
    settings = (
        "static const char *backend_path = " + json.dumps(windows_path(bundle_file("Bin/C2.DLL"))) + ";\n"
        "static const char *pdb_path = " + json.dumps(windows_path(bundle_file("Bin/MSPDB60.DLL"))) + ";\n"
        "static char *arguments[] = {\n" + ",\n".join(json.dumps(argument) for argument in arguments) + "\n};\n"
    )
    (directory / "replay_settings.h").write_text(settings)
    shutil.copyfile(HERE / "replay.c", directory / "replay.c")
    compile_driver(directory, "replay.c", "replay-driver.obj")
    link(directory, "replay.exe", "replay-driver.obj")


def function_metrics(config, object_path):
    manifest = match.load_function_symbol_manifest(match.DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH)
    result = match.run_match(
        obj_path=object_path,
        function_name=config.function,
        end_va=config.end_va,
        symbol_name=config.symbol,
        manifest=manifest,
        image_path=match.REPO_ROOT / manifest.primary_target,
    )
    return {
        "ratio": result.ratio,
        "target_instructions": result.target_instruction_count,
        "candidate_instructions": result.candidate_instruction_count,
        "prefix_instructions": result.instruction_prefix_count,
        "references_ok": result.masked_operand_audit.ok_count,
        "reference_problems": result.masked_operand_audit.problem_count,
        "exact": result.exact,
        "body_byte_exact": result.body_byte_exact,
    }
