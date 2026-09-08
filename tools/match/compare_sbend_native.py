#!/usr/bin/env python3
"""Compare source S-bend output with a relocated original-code oracle.

The oracle object contains original machine code and must never be counted as
recovered source. Only its audited external address operands are relocated.
"""

import argparse
import fcntl
import hashlib
import json
import re
import struct
import subprocess
import sys
import tempfile
from pathlib import Path

import capstone
import pefile

from snail.match import (
    DEFAULT_MATCH_ROOT,
    compile_scratch,
    extract_object_function,
    load_image,
    load_scratch_config,
    parse_coff_object,
    resolve_function_extent,
    run_match,
    scratch_dependency_sha256,
)
from snail.symbols import (
    DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH,
    REPO_ROOT,
    load_function_symbol_manifest,
)

FUNCTION = "initialize_sbend_path_template_pair"


def digest(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def write_object(function_name, body, constants, relocations, external_symbols):
    """Minimal i386 COFF object: one oracle function and copied constants."""
    symbols = [(function_name, 0, 1, 0x20)]
    symbols += [(name, 0, 0, kind) for name, kind in external_symbols.items()]
    rdata = bytearray()
    for name, value in constants.items():
        rdata += b"\0" * (-len(rdata) % 8)
        symbols.append((name, len(rdata), 2, 0))
        rdata += value
    indices = {symbol[0]: i for i, symbol in enumerate(symbols)}
    string_table = bytearray(b"\0" * 4)
    symbol_table = bytearray()
    for name, value, section, kind in symbols:
        encoded = name.encode("ascii")
        if len(encoded) <= 8:
            encoded = encoded.ljust(8, b"\0")
        else:
            offset = len(string_table)
            string_table += encoded + b"\0"
            encoded = struct.pack("<II", 0, offset)
        symbol_table += encoded + struct.pack("<IhHBB", value, section, kind, 2, 0)
    struct.pack_into("<I", string_table, 0, len(string_table))
    raw_relocations = b"".join(
        struct.pack("<IIH", offset, indices[name], kind)
        for offset, name, kind in relocations
    )
    text_offset = 20 + 2 * 40
    data_offset = text_offset + len(body)
    relocation_offset = data_offset + len(rdata)
    symbol_offset = relocation_offset + len(raw_relocations)
    header = struct.pack("<HHIIIHH", 0x14C, 2, 0, symbol_offset, len(symbols), 0, 0)
    text_header = struct.pack(
        "<8sIIIIIIHHI",
        b".text\0\0\0",
        0,
        0,
        len(body),
        text_offset,
        relocation_offset,
        0,
        len(relocations),
        0,
        0x60500020,
    )
    data_header = struct.pack(
        "<8sIIIIIIHHI",
        b".rdata\0\0",
        0,
        0,
        len(rdata),
        data_offset,
        0,
        0,
        0,
        0,
        0x40400040,
    )
    return (
        header
        + text_header
        + data_header
        + body
        + rdata
        + raw_relocations
        + symbol_table
        + string_table
    )


def make_oracle(path, *, function_name=FUNCTION, source_object=None):
    """Extract one clean-audited native body for behavioral diagnostics only."""
    config = load_scratch_config(DEFAULT_MATCH_ROOT / "scratches" / function_name)
    dependency_sha256 = scratch_dependency_sha256(config)
    config_sha256 = digest((config.directory / "scratch.conf").read_bytes())
    source_bytes = (source_object or compile_scratch(config)).read_bytes()
    obj = parse_coff_object(source_bytes)
    function = extract_object_function(obj, config.symbol or config.function)
    refs = {r.offset: r for r in function.relocation_references}
    manifest = load_function_symbol_manifest(DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH)
    image = REPO_ROOT / manifest.primary_target
    image_sha256 = digest(image.read_bytes())
    if image_sha256 != manifest.unwrapped_sha256:
        raise ValueError("native image differs from the matching manifest")
    # Match the exact object bytes used to recover relocation identities. A
    # unique snapshot prevents other scratch compiles from replacing the input
    # between the audit and the native extraction.
    with tempfile.TemporaryDirectory(prefix="native-oracle-source-") as temporary:
        snapshot = Path(temporary) / "source.obj"
        snapshot.write_bytes(source_bytes)
        match = run_match(
            obj_path=snapshot, function_name=function_name, image_path=image,
            manifest=manifest, symbol_name=config.symbol, end_va=config.end_va,
        )
    if match.masked_operand_audit.problem_count:
        raise ValueError("oracle requires a complete clean native reference audit")
    address, end = resolve_function_extent(manifest, function_name, config.end_va)
    original = load_image(image, manifest.image_base).function_bytes(address, end)
    pe = pefile.PE(str(image))
    body = bytearray(original)
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True
    native_insns = {
        i.address - address: i for i in decoder.disasm(original, address)
    }
    source_insns = {i.address: i for i in decoder.disasm(function.data, 0)}
    constants = {}
    externals = {}
    relocations = []
    evidence = []
    for entry in match.masked_operand_audit.entries:
        if (
            entry.status != "ok"
            or len(entry.target_references) != 1
            or len(entry.candidate_references) != 1
        ):
            raise ValueError("oracle only supports one audited operand per instruction")
        native = native_insns[entry.target_offset]
        source = source_insns[entry.candidate_offset]
        target_ref = entry.target_references[0]
        candidate_ref = entry.candidate_references[0]
        native_delta = (
            native.imm_offset if target_ref.kind == "imm" else native.disp_offset
        )
        source_delta = (
            source.imm_offset if candidate_ref.kind == "imm" else source.disp_offset
        )
        native_size = native.imm_size if target_ref.kind == "imm" else native.disp_size
        if native_size != 4:
            raise ValueError("oracle requires four-byte relocations")
        offset = entry.target_offset + native_delta
        source_ref = refs[entry.candidate_offset + source_delta]
        source_addend = struct.unpack_from("<i", function.data, source_ref.offset)[0]
        if source_addend != 0:
            raise ValueError("oracle does not infer nonzero source relocation addends")
        if target_ref.key.startswith("const:"):
            width = native.operands[target_ref.operand_index].size
            if width not in (4, 8):
                raise ValueError("unsupported native constant width")
            value = pe.get_data(target_ref.value - pe.OPTIONAL_HEADER.ImageBase, width)
            name = f"_native_oracle_constant_{target_ref.value:x}_{width}"
            if name in constants and constants[name] != value:
                raise ValueError("inconsistent constant")
            constants[name] = value
            kind = 0x06
        elif target_ref.key.startswith("str:"):
            expected = target_ref.key[4:].encode("utf-8") + b"\0"
            value = pe.get_data(
                target_ref.value - pe.OPTIONAL_HEADER.ImageBase, len(expected)
            )
            if value != expected:
                raise ValueError("audited native string does not match image bytes")
            name = f"_native_oracle_string_{target_ref.value:x}"
            constants[name] = value
            kind = 0x06
        else:
            name = source_ref.symbol_name
            kind = 0x14 if native.mnemonic == "call" else 0x06
            externals[name] = 0x20 if kind == 0x14 else 0
        struct.pack_into("<I", body, offset, 0)
        relocations.append((offset, name, kind))
        evidence.append(
            {
                "offset": offset,
                "symbol": name,
                "kind": kind,
                "original_value": target_ref.value,
                "reference_key": target_ref.key,
            }
        )
    # Independently reject any original-image address left without a relocation.
    slots = {offset for offset, _, _ in relocations}
    base = pe.OPTIONAL_HEADER.ImageBase
    limit = base + pe.OPTIONAL_HEADER.SizeOfImage
    for relative, instruction in native_insns.items():
        for operand in instruction.operands:
            if operand.type == capstone.x86.X86_OP_IMM:
                value = operand.imm
                if instruction.group(
                    capstone.CS_GRP_JUMP
                ) and address <= value < address + len(original):
                    continue
                delta = instruction.imm_offset
            elif (
                operand.type == capstone.x86.X86_OP_MEM
                and not operand.mem.base
                and not operand.mem.index
            ):
                value = operand.mem.disp
                delta = instruction.disp_offset
            else:
                continue
            if base <= value < limit and relative + delta not in slots:
                raise ValueError(
                    f"unrelocated native address at {instruction.address:#x}"
                )
    oracle_bytes = write_object(function.name, body, constants, relocations, externals)
    path.write_bytes(oracle_bytes)
    control = run_match(
        obj_path=path,
        function_name=function_name,
        image_path=image,
        manifest=manifest,
        symbol_name=function.name,
        end_va=config.end_va,
    )
    if control.ratio != 1.0 or control.masked_operand_audit.problem_count:
        raise ValueError("oracle round-trip changed native code or references")
    if (scratch_dependency_sha256(config) != dependency_sha256
            or digest((config.directory / "scratch.conf").read_bytes()) != config_sha256):
        raise ValueError("source compilation inputs changed during oracle extraction")
    if digest(image.read_bytes()) != image_sha256:
        raise ValueError("native image changed during oracle extraction")
    if source_object is not None and source_object.read_bytes() != source_bytes:
        raise ValueError("source object changed during oracle extraction")
    if path.read_bytes() != oracle_bytes:
        raise ValueError("oracle object changed during extraction")
    return {
        "function": function_name,
        "function_symbol": function.name,
        "source_object_sha256": digest(source_bytes),
        "matching_config_sha256": config_sha256,
        # A caller-supplied object's compilation provenance belongs to that
        # caller's preserved build receipt, not the source currently on disk.
        "source_compilation": (
            {
                "dependency_sha256": dependency_sha256,
                "source_sha256": digest((config.directory / "scratch.cpp").read_bytes()),
                "compiler": config.compiler,
                "cflags": config.cflags,
            }
            if source_object is None else None
        ),
        "native_address": address,
        "original_image_sha256": image_sha256,
        "original_body_sha256": digest(original),
        "native_bytes": len(original),
        "oracle_object_sha256": digest(oracle_bytes),
        "relocations": evidence,
        "copied_constants": {name: value.hex() for name, value in constants.items()},
        "round_trip_native_ratio": control.ratio,
    }


def verify_oracle_link(executable, map_path, oracle_object, proof):
    """Verify immutable native instruction, relocation and copied-data snapshots."""
    snapshots = {path: path.read_bytes() for path in (executable, map_path, oracle_object)}
    if digest(snapshots[oracle_object]) != proof["oracle_object_sha256"]:
        raise ValueError("oracle object differs from its extraction receipt")
    symbols = {
        m[1]: int(m[2], 16)
        for m in re.finditer(
            r"^\s+[0-9A-Fa-f]{4}:[0-9A-Fa-f]{8}\s+(\S+)\s+([0-9A-Fa-f]{8})\b",
            snapshots[map_path].decode(),
            re.MULTILINE,
        )
    }
    pe = pefile.PE(data=snapshots[executable])
    mapped = pe.get_memory_mapped_image()
    address = symbols[proof["function_symbol"]]
    function = extract_object_function(
        parse_coff_object(snapshots[oracle_object]), proof["function_symbol"]
    )
    linked_body = mapped[
        address - pe.OPTIONAL_HEADER.ImageBase : address
        - pe.OPTIONAL_HEADER.ImageBase
        + len(function.data)
    ]
    mask = {
        i for r in proof["relocations"] for i in range(r["offset"], r["offset"] + 4)
    }
    if any(
        a != b
        for i, (a, b) in enumerate(zip(function.data, linked_body, strict=True))
        if i not in mask
    ):
        raise ValueError("link changed original non-relocation bytes")
    for ref in proof["relocations"]:
        actual = struct.unpack_from("<I", linked_body, ref["offset"])[0]
        if ref["kind"] == 0x14:
            actual = (address + ref["offset"] + 4 + actual) & 0xFFFFFFFF
        if actual != symbols[ref["symbol"]]:
            raise ValueError("oracle link resolved a wrong address")
    for name, encoded in proof["copied_constants"].items():
        expected = bytes.fromhex(encoded)
        start = symbols[name] - pe.OPTIONAL_HEADER.ImageBase
        if mapped[start : start + len(expected)] != expected:
            raise ValueError("oracle link changed an original constant")
    if any(path.read_bytes() != data for path, data in snapshots.items()):
        raise ValueError("oracle link artifacts changed during verification")
    return {str(path): digest(data) for path, data in snapshots.items()}


def compare(runtime, out):
    source = out / "source"
    receipt_path = out / "comparison.json"
    receipt_path.unlink(missing_ok=True)
    subprocess.run(
        [
            sys.executable,
            str(DEFAULT_MATCH_ROOT / "link_path_math.py"),
            "--group",
            "sbend",
            "--diagnostic-sbend",
            "--run",
            "--out",
            str(source),
            "--runtime-library",
            str(runtime),
        ],
        check=True,
    )
    source_receipt_path = source / "receipt.json"
    source_receipt_bytes = source_receipt_path.read_bytes()
    source_receipt = json.loads(source_receipt_bytes)
    output_inputs = {
        str(source_receipt_path): digest(source_receipt_bytes),
        str(source / "sbend-smoke.exe"): source_receipt["dll_sha256"],
        str(source / "sbend-smoke.map"): source_receipt["map_sha256"],
        str(source / "link.rsp"): digest((source / "link.rsp").read_bytes()),
    }
    for record in source_receipt["functions"]:
        output_inputs[str(source / f"{record['function']}.obj")] = record["object_sha256"]
    for record in source_receipt["support"]:
        object_path = source / (Path(record["source"]).stem + ".obj")
        output_inputs[str(object_path)] = record["object_sha256"]
    if any(digest(Path(path).read_bytes()) != expected
           for path, expected in output_inputs.items()):
        raise ValueError("source artifacts differ from their link receipt")
    native_obj = out / "original-sbend-oracle.obj"
    proof = make_oracle(native_obj, source_object=source / f"{FUNCTION}.obj")
    native_exe = out / "original-sbend-oracle.exe"
    native_map = native_exe.with_suffix(".map")
    native_exe.unlink(missing_ok=True)
    native_map.unlink(missing_ok=True)
    response = (source / "link.rsp").read_text()
    response = response.replace(str(source / f"{FUNCTION}.obj"), str(native_obj))
    response = response.replace(str(source / "sbend-smoke.exe"), str(native_exe))
    response = response.replace(str(source / "sbend-smoke.map"), str(native_map))
    rsp = out / "oracle-link.rsp"
    rsp.write_text(response)
    runner = DEFAULT_MATCH_ROOT / "bin/wibo"
    linker = DEFAULT_MATCH_ROOT / "compilers/msvc6.5/Bin/LINK.EXE"
    linked = subprocess.run(
        [str(runner), str(linker), f"@Z:{rsp}"],
        capture_output=True,
        text=True,
        check=False,
    )
    (out / "oracle-link.log").write_text(linked.stdout + linked.stderr)
    if linked.returncode:
        raise ValueError("oracle link failed; see oracle-link.log")
    output_inputs.update(verify_oracle_link(native_exe, native_map, native_obj, proof))
    output_inputs[str(rsp)] = digest(rsp.read_bytes())
    source_trace = out / "source-geometry.bin"
    native_trace = out / "original-geometry.bin"
    source_trace.unlink(missing_ok=True)
    native_trace.unlink(missing_ok=True)
    source_run = subprocess.run(
        [str(runner), str(source / "sbend-smoke.exe"), "--dump", f"Z:{source_trace}"],
        capture_output=True,
        text=True,
        timeout=20,
        check=False,
    )
    if source_run.returncode or "sbend checks=60 failures=0" not in source_run.stdout:
        raise ValueError("source geometry serialization failed")
    run = subprocess.run(
        [str(runner), str(native_exe), "--dump", f"Z:{native_trace}"],
        capture_output=True,
        text=True,
        timeout=20,
        check=False,
    )
    (out / "oracle-run.log").write_text(run.stdout + run.stderr)
    source_output = (source / "positive.log").read_text()
    pattern = r"sbend case=(\d+) hash=([0-9a-f]{8})"
    native_cases = re.findall(pattern, run.stdout)
    source_cases = re.findall(pattern, source_output)
    if (
        run.returncode
        or "sbend checks=60 failures=0" not in run.stdout
        or len(native_cases) != 4
        or native_cases != source_cases
    ):
        raise ValueError(
            "source/native behavioral comparison failed; inspect both logs"
        )
    source_bytes = source_trace.read_bytes()
    native_bytes = native_trace.read_bytes()
    if not source_bytes or source_bytes != native_bytes:
        raise ValueError("source/native serialized geometry differs")
    if any(digest(Path(path).read_bytes()) != expected
           for path, expected in output_inputs.items()):
        raise ValueError("source or oracle artifacts changed during comparison")
    proof.update(
        {
            "output_artifacts": output_inputs,
            "purpose": "Original-code behavioral oracle; not reconstructed source",
            "original_code_used": True,
            "public_matching_credit": False,
            "public_linked_credit": False,
            "source_receipt": str(source / "receipt.json"),
            "cases": native_cases,
            "checks": 60,
            "failures": 0,
            "serialized_geometry_bytes": len(source_bytes),
            "serialized_geometry_sha256": digest(source_bytes),
            "serialized_geometry_byte_equal": True,
        }
    )
    receipt_path.write_text(json.dumps(proof, indent=2) + "\n")
    print(
        f"Source and original S-bend produce identical serialized geometry ({len(source_bytes)} bytes): {receipt_path}"
    )


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--runtime-library", type=Path, required=True)
    parser.add_argument(
        "--out", type=Path, default=REPO_ROOT / "artifacts/match/sbend-comparison"
    )
    args = parser.parse_args()
    out = args.out.resolve()
    out.mkdir(parents=True, exist_ok=True)
    with (out / ".comparison.lock").open("a") as lock:
        try:
            fcntl.flock(lock, fcntl.LOCK_EX | fcntl.LOCK_NB)
        except BlockingIOError as error:
            raise ValueError(f"another comparison owns {out}") from error
        compare(args.runtime_library.resolve(strict=True), out)


if __name__ == "__main__":
    main()
