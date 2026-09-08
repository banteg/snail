#!/usr/bin/env python3
"""Probe texture-call continuation ownership without changing recovered source.

Reduced and independent-input bodies are compiler diagnostics only. Complete
controls retain the operation order on each face; their matcher receipts live
in the S-bend experiment ledger. No diagnostic grants recovery credit.
"""

from __future__ import annotations

import argparse
import json
import os
import shutil
import subprocess
from pathlib import Path

import probe_face_emission_context as p

from snail.match import _manifest_target_sizes


def publication_variants(original, bases):
    variants = {}
    for base_name in ["face_loops", "full_baseline"]:
        variants[base_name] = bases[base_name]
        for kind in ["prefix", "suffix"]:
            for count in range(1, 9):
                source = bases[base_name]
                for texture in ["texture_a", "texture_b"]:
                    at = source.index("g_texture_refs.Add(" + texture)
                    start = source.rindex(
                        "                        if ((column ^ row) & 1)\n", 0, at
                    )
                    uv_start = source.index(
                        "                        facequads[face_offset].uv[0].u", at
                    )
                    end = source.index(
                        "                        facequads[face_offset].uv[3].v = v1;",
                        at,
                    ) + len(
                        "                        facequads[face_offset].uv[3].v = v1;"
                    )
                    uv = source[uv_start:end].splitlines()
                    call = f"facequads[face_offset].texture_ref = g_texture_refs.Add({texture}, 0, 0);\n"
                    inside = uv[:count] if kind == "prefix" else uv[-count:]
                    common = uv[count:] if kind == "prefix" else uv[:-count]
                    if kind == "prefix":
                        arm = call + "\n".join(inside)
                        replace = (
                            "if ((column ^ row) & 1) {\n"
                            + arm
                            + "\n} else {\n"
                            + arm
                            + "\n}\n"
                            + "\n".join(common)
                        )
                    else:
                        # Move final publications into a second repeated parity branch after the original call join.
                        # This preserves order, but tests two branch scopes, unlike prefix duplication.
                        replace = (
                            source[start:uv_start]
                            + "\n".join(common)
                            + "\nif ((column ^ row) & 1) {\n"
                            + "\n".join(inside)
                            + "\n} else {\n"
                            + "\n".join(inside)
                            + "\n}"
                        )
                    source = source[:start] + replace + source[end:]
                variants[f"{base_name}_{kind}_{count}"] = source
    return variants


def helper_variants(original, bases):
    # Variant construction for independent generic inputs specialized at caller.
    variants = {}
    headers = original[: original.index("float Cos")]
    for base_name in ["face_loops", "full_baseline"]:
        for mode in ["texture", "uv", "both", "texture_ref", "both_ref", "struct"]:
            source = bases[base_name]
            if mode == "struct":
                formals = "cRFaceQuad* face, int parity, char* odd_texture, char* even_texture, const ObjectUv* odd_uv, const ObjectUv* even_uv"
                helper = "static __forceinline void emit_parity(" + formals + ") {\n"
                for branch, side in [("if (parity & 1)", "odd"), ("else", "even")]:
                    helper += (
                        branch
                        + " {\nface->texture_ref = g_texture_refs.Add("
                        + side
                        + "_texture, 0, 0);\n"
                    )
                    for i in range(4):
                        helper += f"face->uv[{i}] = {side}_uv[{i}];\n"
                    helper += "}\n"
                helper += "}\n"
            else:
                ref = "&" if mode.endswith("_ref") else ""
                has_tex = mode.startswith(("texture", "both"))
                has_uv = mode.startswith(("uv", "both"))
                formals = "cRFaceQuad* face, int parity, char* " + ref + "odd_texture"
                if has_tex:
                    formals += ", char* " + ref + "even_texture"
                for side in ["odd"] + (["even"] if has_uv else []):
                    formals += ", " + ", ".join(
                        "float " + ref + side + "_" + v
                        for v in ["left", "right", "top", "bottom"]
                    )
                helper = "static __forceinline void emit_parity(" + formals + ") {\n"
                for branch, side in [("if (parity & 1)", "odd"), ("else", "even")]:
                    ts = side if has_tex else "odd"
                    us = side if has_uv else "odd"
                    helper += (
                        branch
                        + " {\nface->texture_ref = g_texture_refs.Add("
                        + ts
                        + "_texture, 0, 0);\n"
                    )
                    for i, (u, v) in enumerate(
                        [
                            ("left", "top"),
                            ("right", "top"),
                            ("right", "bottom"),
                            ("left", "bottom"),
                        ]
                    ):
                        helper += f"face->uv[{i}].u = {us}_{u};\nface->uv[{i}].v = {us}_{v};\n"
                    helper += "}\n"
                helper += "}\n"
            for texture, left, right in [
                ("texture_a", "u0", "u1"),
                ("texture_b", "u1", "u0"),
            ]:
                at = source.index("g_texture_refs.Add(" + texture)
                start = source.rindex(
                    "                        if ((column ^ row) & 1)\n", 0, at
                )
                end = source.index(
                    "                        facequads[face_offset].uv[3].v = v1;", at
                ) + len("                        facequads[face_offset].uv[3].v = v1;")
                if mode == "struct":
                    replace = f"ObjectUv corners[4] = {{{{{left}, v0}}, {{{right}, v0}}, {{{right}, v1}}, {{{left}, v1}}}};\nemit_parity(&facequads[face_offset], column ^ row, {texture}, {texture}, corners, corners);"
                else:
                    actual = "&facequads[face_offset], column ^ row, " + texture
                    if has_tex:
                        actual += ", " + texture
                    actual += f", {left}, {right}, v0, v1"
                    if has_uv:
                        actual += f", {left}, {right}, v0, v1"
                    replace = "emit_parity(" + actual + ");"
                source = source[:start] + replace + source[end:]
            source = source[: len(headers)] + helper + source[len(headers) :]
            variants[base_name + "_" + mode] = source
            if base_name == "face_loops" and mode != "struct":
                standalone = headers + helper.replace(
                    "static __forceinline void emit_parity", "void reduction"
                )
                variants["standalone_" + mode] = standalone

    return variants


def scope_variants(original, bases):
    variants = {}
    for base_name in ["face_loops", "full_baseline"]:
        for side in ["odd", "even"]:
            for count in range(1, 9):
                source = bases[base_name]
                for texture in ["texture_a", "texture_b"]:
                    at = source.index("g_texture_refs.Add(" + texture)
                    start = source.rindex(
                        "                        if ((column ^ row) & 1)\n", 0, at
                    )
                    uv_start = source.index(
                        "                        facequads[face_offset].uv[0].u", at
                    )
                    end = source.index(
                        "                        facequads[face_offset].uv[3].v = v1;",
                        at,
                    ) + len(
                        "                        facequads[face_offset].uv[3].v = v1;"
                    )
                    uv = source[uv_start:end].splitlines()
                    inside = "\n".join(uv[:count])
                    common = "\n".join(uv[count:])
                    call = f"facequads[face_offset].texture_ref = g_texture_refs.Add({texture}, 0, 0);\n"
                    odd = "((column ^ row) & 1)"
                    odd_arm = call + (inside if side == "odd" else "")
                    even_arm = call + (inside if side == "even" else "")
                    predicate = "!" + odd if side == "odd" else odd
                    replace = f"if ({odd}) {{\n{odd_arm}\n}} else {{\n{even_arm}\n}}\nif ({predicate}) {{\n{inside}\n}}\n{common}"
                    source = source[:start] + replace + source[end:]
                variants[f"{base_name}_{side}_staggered_{count}"] = source

    return variants


def build_variants(original):
    bases = p.build_variants(original)
    return {
        **publication_variants(original, bases),
        **helper_variants(original, bases),
        **scope_variants(original, bases),
    }


def cold_continuations(instructions, calls):
    """Recognize the complete native three-instruction alternate argument path.

    Unlike the earlier local parity classifier, this does not require TEST reg,1.
    A repeated condition can become a register test after optimization.
    """
    by_address = {item.address: i for i, item in enumerate(instructions)}
    matches = []
    for branch in instructions:
        if (
            not branch.mnemonic.startswith("j")
            or branch.mnemonic == "jmp"
            or branch.operands[0].type != p.X86_OP_IMM
        ):
            continue
        target = branch.operands[0].imm
        index = by_address.get(target)
        if index is None or target <= branch.address:
            continue
        chunk = instructions[index : index + 3]
        if [item.mnemonic for item in chunk] != ["mov", "push", "jmp"] or chunk[
            -1
        ].operands[0].type != p.X86_OP_IMM:
            continue
        load, push, _ = chunk
        if (
            load.operands[0].type != p.X86_OP_REG
            or push.operands[0].type != p.X86_OP_REG
            or load.operands[0].reg != push.operands[0].reg
        ):
            continue
        destination = chunk[-1].operands[0].imm
        join = by_address.get(destination)
        if (
            join is None
            or join + 1 >= len(instructions)
            or not branch.address < destination < target
        ):
            continue
        receiver, call = instructions[join : join + 2]
        if (
            receiver.mnemonic != "mov"
            or receiver.operands[0].type != p.X86_OP_REG
            or receiver.reg_name(receiver.operands[0].reg) != "ecx"
            or call.address not in calls
        ):
            continue
        matches.append(
            {
                "branch": p.instruction_row(branch),
                "alternate_argument": [p.instruction_row(item) for item in chunk],
                "receiver": p.instruction_row(receiver),
                "call": p.instruction_row(call),
            }
        )
    return matches


def native_scan():
    manifest = p.load_function_symbol_manifest(p.DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH)
    image = p.ROOT / manifest.primary_target
    image_digest = p.digest(image.read_bytes())
    if image_digest != manifest.unwrapped_sha256:
        raise ValueError("native image does not match the pinned manifest")
    sizes = _manifest_target_sizes(manifest, image)
    pe = p.pefile.PE(str(image))
    add = next(
        item.address
        for item in manifest.functions
        if item.name == "get_or_create_texture_ref"
    )
    result = {
        "image_sha256": image_digest,
        "symbol_manifest_sha256": p.digest(
            p.DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH.read_bytes()
        ),
        "interpretation": "Positive structural observations in manifest spans; missing patterns are not semantic absence proof.",
        "manifest_functions": len(manifest.functions),
        "completely_decoded_spans": 0,
        "incomplete_spans": [],
        "spans_with_texture_calls": 0,
        "matches": {},
    }
    for symbol in manifest.functions:
        body = pe.get_data(
            symbol.address - pe.OPTIONAL_HEADER.ImageBase, sizes[symbol.address]
        )
        try:
            instructions = p.decode(body, symbol.address)
        except ValueError:
            result["incomplete_spans"].append(symbol.name)
            continue
        result["completely_decoded_spans"] += 1
        calls = {
            item.address
            for item in instructions
            if item.mnemonic == "call"
            and item.operands[0].type == p.X86_OP_IMM
            and item.operands[0].imm == add
        }
        if not calls:
            continue
        result["spans_with_texture_calls"] += 1
        matches = cold_continuations(instructions, calls)
        if not matches:
            continue
        config = p.load_scratch_config(p.DEFAULT_MATCH_ROOT / "scratches" / symbol.name)
        status = p.evaluate_scratch(config)
        if (
            status.error
            or status.target_size != len(body)
            or status.address != symbol.address
        ):
            raise ValueError(
                f"native positive span disagrees with matcher: {symbol.name}"
            )
        result["matches"][symbol.name] = {
            "address": hex(symbol.address),
            "size": len(body),
            "body_sha256": p.digest(body),
            "instructions": len(instructions),
            "current_match_ratio": status.ratio,
            "references": {
                "ok": status.masked_ok,
                "unresolved": status.masked_unresolved,
                "mismatched": status.masked_mismatches,
                "unaudited": status.masked_unaudited,
            },
            "continuations": matches,
        }
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--out",
        type=Path,
        default=p.ROOT / "artifacts/match/texture-continuation-ownership-20260908",
    )
    args = parser.parse_args()
    output = args.out.resolve()
    output.mkdir(parents=True, exist_ok=True)
    source_path = p.DEFAULT_MATCH_ROOT / "scratches" / p.FUNCTION / "scratch.cpp"
    original = source_path.read_text()
    config = p.load_scratch_config(source_path.parent)
    if config.compiler != "msvc6.5":
        raise ValueError("diagnostic baseline requires canonical VC6")
    runner_name = os.environ.get("WIBO")
    if runner_name is None:
        bundled = p.DEFAULT_MATCH_ROOT / "bin/wibo"
        runner_name = str(bundled) if bundled.is_file() else "wibo"
    runner = shutil.which(runner_name)
    if runner is None:
        raise ValueError(f"cannot find runner: {runner_name}")
    environment = {**os.environ, "MSVC_VER": "msvc6.5", "WIBO": runner}
    flags = ["/O2", "/G5", "/W3"]
    receipt = {
        "schema": 1,
        "classification": "compiler diagnostics; no recovery or runtime credit",
        "source_sha256": p.digest(source_path.read_bytes()),
        "tool_sha256": p.digest(Path(__file__).read_bytes()),
        "face_context_tool_sha256": p.digest(Path(p.__file__).read_bytes()),
        "compiler": "msvc6.5",
        "flags": flags,
        "runner_sha256": p.digest(Path(runner).read_bytes()),
        "build_inputs": {
            str(path.relative_to(p.ROOT)): p.digest(path.read_bytes())
            for path in p._scratch_build_dependencies(config, p.DEFAULT_MATCH_ROOT)
        },
        "native_scan": native_scan(),
        "diagnostics": {},
    }
    for name, source in build_variants(original).items():
        directory = output / name
        directory.mkdir(exist_ok=True)
        (directory / "reduction.cpp").write_text(source)
        process = subprocess.run(
            [
                str(p.DEFAULT_MATCH_ROOT / "cl.sh"),
                "/c",
                *flags,
                "/FAsc",
                "reduction.cpp",
            ],
            cwd=directory,
            env=environment,
            capture_output=True,
            text=True,
            check=False,
        )
        (directory / "compiler.log").write_text(process.stdout + process.stderr)
        if process.returncode:
            raise RuntimeError(f"{name}: {process.stdout}{process.stderr}")
        function = p.extract_object_function(
            p.parse_coff_object((directory / "reduction.obj").read_bytes()),
            p.FUNCTION if "void cRPath::initialize_sbend" in source else "reduction",
        )
        instructions = p.decode(function.data)
        calls = {
            reference.offset - 1
            for reference in function.relocation_references
            if reference.symbol_name.startswith("?Add@cRTextures@@")
        }
        p.write_assembly(directory / "reduction.asm", instructions)
        matches = cold_continuations(instructions, calls)
        receipt["diagnostics"][name] = {
            "complete_source_control": name.startswith("full_baseline"),
            "source_sha256": p.digest(source.encode()),
            "code_sha256": p.object_function_fingerprint(function),
            "size": len(function.data),
            "instructions": len(instructions),
            "texture_call_count": len(calls),
            "cold_continuations": matches,
            "local_patterns": p.patterns(instructions, calls),
        }
        print(
            f"{name}: {len(instructions)} instructions, {len(calls)} calls, {len(matches)} cold continuations",
            flush=True,
        )
    (output / "receipt.json").write_text(json.dumps(receipt, indent=2) + "\n")
    print(f"Diagnostic receipt: {output / 'receipt.json'}")


if __name__ == "__main__":
    main()
