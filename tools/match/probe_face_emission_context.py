#!/usr/bin/env python3
"""Diagnose VC6 face-emission context; reductions are not recovered game code.

Generated sources deliberately omit or change geometry in some cases. This
tool never awards matching credit or modifies the canonical scratch.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import os
import re
import shutil
import subprocess
from pathlib import Path

import pefile
from capstone import CS_ARCH_X86, CS_MODE_32, Cs
from capstone.x86 import X86_OP_IMM, X86_OP_MEM, X86_OP_REG

from snail.match import (
    DEFAULT_MATCH_ROOT,
    _scratch_build_dependencies,
    evaluate_scratch,
    extract_object_function,
    load_scratch_config,
    object_function_fingerprint,
    parse_coff_object,
)
from snail.symbols import (
    DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH,
    REPO_ROOT,
    load_function_symbol_manifest,
)

ROOT = REPO_ROOT
FUNCTION = "initialize_sbend_path_template_pair"
NATIVE_CONTROLS = (
    FUNCTION,
    "initialize_sweep_path_template_pair",
    "initialize_slalom_path_template_pair",
    "initialize_turnunder_path_template_pair",
    "build_track_fringe_mesh",
    "build_track_fringe_supertramp_mesh",
)


def digest(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def build_variants(original: str) -> dict[str, str]:
    headers = original[: original.index("float Cos")]
    start = original.index("    for (row = 0; row < path->segment_count; ++row)")
    end = original.index("\nvoid cRPath::initialize_sbend", start)
    face_loop = original[start:end].rstrip()
    assert face_loop.endswith("}")
    face_loop = face_loop[:-1].rstrip()
    decls = """    cRFaceQuad* facequads = path->strip_mesh->facequads;
        int row;
        int column;
        int face_index;
    """
    base = (
        headers
        + "void reduction(Path* path, char* texture_a, char* texture_b)\n{\n"
        + decls
        + face_loop
        + "\n}\n"
    )

    variants = {"face_loops": base}
    branch = base.replace("facequads[face_offset].", "face->")
    branch = branch.replace(
        "if (face_index == 0) {",
        "if (face_index == 0) {\n                        cRFaceQuad* face = &facequads[face_offset];",
    )
    branch = branch.replace(
        "                    } else {",
        "                    } else {\n                        cRFaceQuad* face = &facequads[face_offset];",
    )
    variants["branch_pointer"] = branch
    variants["branch_offset"] = (
        base.replace(
            "                    int face_offset =\n                        2 * column + 2 * row * path->width_cells + face_index;\n",
            "",
        )
        .replace(
            "if (face_index == 0) {",
            "if (face_index == 0) {\n                        int face_offset = 2 * column + 2 * row * path->width_cells + face_index;",
        )
        .replace(
            "                    } else {",
            "                    } else {\n                        int face_offset = 2 * column + 2 * row * path->width_cells + face_index;",
        )
    )
    # Separate the winding iteration from the row/column loops, retaining the same
    # expressions and field stores. Diagnostic signature only; no matching credit.
    inner_start = base.index("                for (face_index = 0;")
    inner_end = base.index("\n                ++column;", inner_start)
    inner = base[inner_start:inner_end]
    assert inner.endswith("                }")
    inner = inner[inner.index("\n") + 1 : inner.rindex("                }")]
    variants["single_face"] = (
        headers
        + "void reduction(Path* path, cRFaceQuad* facequads, int row, int column, int face_index, char* texture_a, char* texture_b, float u0, float u1, float v0, float v1)\n{\n"
        + inner
        + "}\n"
    )

    signature_start = original.index("void cRPath::initialize_sbend_path_template_pair")
    body_start = original.index("{", signature_start)
    signature = original[signature_start : body_start + 1]
    helpers = original[:signature_start]
    variants["full_baseline"] = original
    variants["member_faces"] = (
        headers + signature + "\n    Path* path = this;\n" + decls + face_loop + "\n}\n"
    )
    variants["member_faces_finalize"] = (
        variants["member_faces"].rsplit("}", 1)[0] + "    CalcLengthZ();\n}\n"
    )
    variants["member_mesh"] = (
        helpers + signature + "\n    build_strip_mesh(this, texture_a, texture_b);\n}\n"
    )
    variants["member_mesh_finalize"] = (
        helpers
        + signature
        + "\n    build_strip_mesh(this, texture_a, texture_b);\n    CalcLengthZ();\n}\n"
    )
    variants["member_delta_mesh_finalize"] = (
        helpers
        + signature
        + "\n    compute_path_deltas(this);\n    build_strip_mesh(this, texture_a, texture_b);\n    CalcLengthZ();\n}\n"
    )
    vertex_start = original.index("    if (path->segment_count >= 0)")
    vertex_end = original.index("    for (row = 0;", vertex_start)
    variants["full_without_vertex_loop"] = (
        original[:vertex_start] + original[vertex_end:]
    )
    variants["full_without_deltas"] = original.replace(
        "    compute_path_deltas(this);\n", ""
    )

    def publish_helper(source):
        helper = """static __forceinline void publish_strip_texture_uv(cRFaceQuad* face, char* texture, float left_u, float right_u, float top_v, float bottom_v)
    {
        face->texture_ref = g_texture_refs.Add(texture, 0, 0);
        face->uv[0].u = left_u;
        face->uv[0].v = top_v;
        face->uv[1].u = right_u;
        face->uv[1].v = top_v;
        face->uv[2].u = right_u;
        face->uv[2].v = bottom_v;
        face->uv[3].u = left_u;
        face->uv[3].v = bottom_v;
    }

    """
        for texture, left, right in [
            ("texture_a", "u0", "u1"),
            ("texture_b", "u1", "u0"),
        ]:
            anchor = "                        if ((column ^ row) & 1)\n"
            at = source.index("g_texture_refs.Add(" + texture)
            begin = source.rindex(anchor, 0, at)
            end = source.index(
                "                        facequads[face_offset].uv[3].v = v1;", at
            ) + len("                        facequads[face_offset].uv[3].v = v1;")
            call = f"publish_strip_texture_uv(&facequads[face_offset], {texture}, {left}, {right}, v0, v1);"
            replacement = (
                anchor
                + "                            "
                + call
                + "\n                        else\n                            "
                + call
            )
            source = source[:begin] + replacement + source[end:]
        return source[: len(headers)] + helper + source[len(headers) :]

    variants["face_loops_publish_helper"] = publish_helper(base)
    variants["full_publish_helper"] = publish_helper(original)
    # Inline an operation with distinct checkerboard inputs, specialized to each
    # side's texture at the caller. This tests optimization timing in the reduction.
    generic = base.replace(
        "void reduction(Path* path, char* texture_a, char* texture_b)",
        "static __forceinline void generic_faces(Path* path, char* texture_a, char* front_even, char* texture_b, char* back_even)",
    )
    generic = generic.replace(
        "else\n                            facequads[face_offset].texture_ref =\n                                g_texture_refs.Add(texture_a, 0, 0);",
        "else\n                            facequads[face_offset].texture_ref =\n                                g_texture_refs.Add(front_even, 0, 0);",
    )
    generic = generic.replace(
        "else\n                            facequads[face_offset].texture_ref =\n                                g_texture_refs.Add(texture_b, 0, 0);",
        "else\n                            facequads[face_offset].texture_ref =\n                                g_texture_refs.Add(back_even, 0, 0);",
    )
    variants["face_loops_four_inputs"] = (
        generic
        + "\nvoid reduction(Path* path, char* a, char* b) { generic_faces(path, a, a, b, b); }\n"
    )

    mesh_only = variants["member_mesh"]
    vertex_source = original[vertex_start:vertex_end]
    for name, replacement in {
        "one_vertex_x_store": "    vertices[0].x = path->primary_samples[0].transform.position.x;\n",
        "one_vertex_vector_copy": "    vertices[0] = path->primary_samples[0].transform.position;\n",
        "vertex_x_stores_only": vertex_source.replace(
            "*vertex = generated_position;", "vertex->x = generated_position.x;"
        ),
        "vertex_plain_position": """    for (row = 0; row < path->segment_count; ++row) {
            for (column = 0; column <= path->width_cells; ++column) {
                vertices[column + row * (path->width_cells + 1)] = path->primary_samples[row].transform.position;
            }
        }

    """,
        "vertex_plain_x": """    for (row = 0; row < path->segment_count; ++row) {
            for (column = 0; column <= path->width_cells; ++column) {
                vertices[column + row * (path->width_cells + 1)].x = path->primary_samples[row].transform.position.x;
            }
        }

    """,
    }.items():
        variants["mesh_" + name] = mesh_only.replace(vertex_source, replacement)
    variants["mesh_allocations_only"] = mesh_only.replace(vertex_source, "")

    # Straight duplicate UV publication, distinct from calling a UV helper. Keep
    # both parity paths in the diagnostic source to observe common-tail placement.
    for original_name in ["face_loops", "member_mesh", "full_baseline"]:
        duplicate = variants[original_name]
        for texture in ["texture_a", "texture_b"]:
            anchor = "                        if ((column ^ row) & 1)\n"
            at = duplicate.index("g_texture_refs.Add(" + texture)
            begin = duplicate.rindex(anchor, 0, at)
            uv_start = duplicate.index(
                "                        facequads[face_offset].uv[0].u", at
            )
            end = duplicate.index(
                "                        facequads[face_offset].uv[3].v = v1;", at
            ) + len("                        facequads[face_offset].uv[3].v = v1;")
            uv = duplicate[uv_start:end]
            call = f"                        facequads[face_offset].texture_ref = g_texture_refs.Add({texture}, 0, 0);\n"
            replacement = (
                "                        if ((column ^ row) & 1) {\n"
                + call
                + uv
                + "\n                        } else {\n"
                + call
                + uv
                + "\n                        }"
            )
            duplicate = duplicate[:begin] + replacement + duplicate[end:]
        variants[original_name + "_duplicate_parity_uv"] = duplicate

    for name in ["face_loops", "member_mesh", "full_baseline"]:
        variants[name + "_global_opt_off"] = variants[name]
        variants[name + "_size_preference"] = variants[name]

    for base_name in ["face_loops", "full_baseline"]:
        for shape in [
            "independent",
            "else_if",
            "switch_zero",
            "switch_one",
            "switch_both",
        ]:
            altered = variants[base_name]
            for texture in ["texture_a", "texture_b"]:
                at = altered.index("g_texture_refs.Add(" + texture)
                begin = altered.rindex(
                    "                        if ((column ^ row) & 1)\n", 0, at
                )
                end = altered.index(
                    "                        facequads[face_offset].uv[0].u", at
                )
                call = f"facequads[face_offset].texture_ref = g_texture_refs.Add({texture}, 0, 0);"
                odd = "((column ^ row) & 1)"
                if shape == "independent":
                    replacement = f"if ({odd}) {{ {call} }}\nif (!{odd}) {{ {call} }}\n"
                elif shape == "else_if":
                    replacement = (
                        f"if ({odd}) {{ {call} }} else if (!{odd}) {{ {call} }}\n"
                    )
                elif shape == "switch_zero":
                    replacement = f"switch ({odd}) {{ case 0: {call} break; default: {call} break; }}\n"
                elif shape == "switch_one":
                    replacement = f"switch ({odd}) {{ case 1: {call} break; default: {call} break; }}\n"
                else:
                    replacement = f"switch ({odd}) {{ case 0: {call} break; case 1: {call} break; }}\n"
                altered = altered[:begin] + replacement + altered[end:]
            variants[base_name + "_parity_" + shape] = altered

    variants.update(vertex_factor_variants(mesh_only, vertex_source))
    return variants


def vertex_factor_variants(mesh_only: str, vertex_source: str) -> dict[str, str]:
    """Separate terminal-row context from vector temporaries in diagnostics.

    These sources store only X and some omit the terminal row. They deliberately
    do not implement the mesh builder and must never receive matching credit.
    """
    x_only = vertex_source.replace(
        "*vertex = generated_position;", "vertex->x = generated_position.x;"
    )
    scalar = x_only.replace(
        "Vector3 lateral_offset =\n                            sample->transform.basis_right * lateral;",
        "float lateral_offset = sample->transform.basis_right.x * (float)lateral;",
    ).replace(
        "Vector3 generated_position =\n                            sample->transform.position + lateral_offset;",
        "float generated_position = sample->transform.position.x + lateral_offset;",
    )

    def scalar_terminal(match):
        expression = match[1].replace(
            ".transform.position + Vector3(0.0f, 0.0f, 1.0f)",
            ".transform.position.x + 0.0f",
        ).replace(".transform.basis_right * lateral", ".transform.basis_right.x * (float)lateral")
        return "float generated_position = " + expression + ";"

    scalar = re.sub(r"Vector3 generated_position = (.*?);", scalar_terminal,
                    scalar, flags=re.DOTALL).replace(
        "vertex->x = generated_position.x;", "vertex->x = generated_position;"
    )

    def typed_samples(source):
        return source.replace(
            "(PathTemplateSample*)((char*)path->primary_samples + sample_offset)",
            "&path->primary_samples[row]",
        ).replace(
            "((PathTemplateSample*)((char*)path->primary_samples\n                                + sample_offset))[-1]",
            "path->primary_samples[row - 1]",
        ).replace("        int sample_offset = 0;\n", "").replace(
            "            sample_offset += sizeof(PathTemplateSample);\n", ""
        )

    variants = {
        "x_original": x_only,
        "x_scalar": scalar,
        "x_typed_samples": typed_samples(x_only),
        "x_scalar_typed_samples": typed_samples(scalar),
        "x_float_lateral": x_only.replace("double lateral =", "float lateral ="),
    }
    for name, source in [("x_original", x_only), ("x_scalar", scalar)]:
        at = source.index("                    if (row != path->segment_count) {")
        middle = source.index("                    } else {", at)
        end = source.index("                    ++column;", middle)
        ordinary = source[
            at + len("                    if (row != path->segment_count) {\n"):middle
        ]
        nonterminal = source[:at] + ordinary + source[end:]
        variants[name + "_nonterminal_only"] = nonterminal.replace(
            "path->segment_count >= 0", "path->segment_count > 0"
        ).replace("row <= path->segment_count", "row < path->segment_count")
        # Keep the extra iteration but remove the terminal expression/branch.
        # This deliberately reads a different sample; it is a compiler control.
        variants[name + "_extra_row_no_terminal_branch"] = nonterminal
        # Keep the terminal branch text but constrain its loop to ordinary rows.
        variants[name + "_nonterminal_bound"] = source.replace(
            "path->segment_count >= 0", "path->segment_count > 0"
        ).replace("row <= path->segment_count", "row < path->segment_count")
    return {
        "vertex_factor_" + name: mesh_only.replace(vertex_source, body)
        for name, body in variants.items()
    }


def instruction_row(instruction):
    return {
        "address": hex(instruction.address),
        "mnemonic": instruction.mnemonic,
        "operands": instruction.op_str,
    }


def stride_lea(instruction) -> bool:
    if instruction.mnemonic != "lea" or len(instruction.operands) != 2:
        return False
    operand = instruction.operands[1]
    return (
        operand.type == X86_OP_MEM
        and operand.mem.base != 0
        and operand.mem.base == operand.mem.index
        and operand.mem.scale == 2
    )


def patterns(instructions, texture_calls):
    """Report local structural observations, not inferred source equivalence."""
    by_address = {instruction.address: i for i, instruction in enumerate(instructions)}
    first_call = min(texture_calls, default=None)
    winding = []
    for i, instruction in enumerate(instructions):
        if first_call is None or instruction.address >= first_call:
            break
        if instruction.mnemonic != "test" or len(instruction.operands) != 2:
            continue
        left, right = instruction.operands
        if left.type != X86_OP_REG or right.type != X86_OP_REG or left.reg != right.reg:
            continue
        between = []
        for jump in instructions[i + 1 : i + 5]:
            if jump.mnemonic.startswith("j") and jump.mnemonic != "jmp":
                if any(item.mnemonic == "lea" for item in between):
                    branch_target = jump.operands[0].imm
                    target_index = by_address.get(branch_target)
                    following = instructions[
                        by_address[jump.address] + 1 : by_address[jump.address] + 9
                    ]
                    target_prefix = (
                        instructions[target_index : target_index + 8]
                        if target_index is not None
                        else []
                    )
                    winding.append(
                        {
                            "test": instruction_row(instruction),
                            "branch": instruction_row(jump),
                            "pretest_prefix": [
                                instruction_row(item)
                                for item in instructions[max(0, i - 8) : i]
                            ],
                            "stride_in_pretest_prefix": any(
                                stride_lea(item)
                                for item in instructions[max(0, i - 8) : i]
                            ),
                            "stride_between_test_and_branch": any(
                                stride_lea(item) for item in between
                            ),
                            "stride_in_fallthrough_prefix": any(
                                stride_lea(item) for item in following
                            ),
                            "stride_in_taken_prefix": any(
                                stride_lea(item) for item in target_prefix
                            ),
                        }
                    )
                break
            if jump.mnemonic not in {"lea", "mov"}:
                break
            between.append(jump)

    calls = []
    for address in sorted(texture_calls):
        index = by_address[address]
        tests = [
            i
            for i in range(max(0, index - 16), index)
            if instructions[i].mnemonic == "test"
            and len(instructions[i].operands) == 2
            and instructions[i].operands[1].type == X86_OP_IMM
            and instructions[i].operands[1].imm == 1
        ]
        branch = None
        if tests:
            branch = next(
                (
                    item
                    for item in instructions[tests[-1] + 1 : index]
                    if item.mnemonic.startswith("j") and item.mnemonic != "jmp"
                ),
                None,
            )
        destination = branch.operands[0].imm if branch is not None else None
        destination_index = by_address.get(destination)
        prefix = (
            instructions[destination_index : destination_index + 3]
            if destination_index is not None
            else []
        )
        cold_continuation = (
            destination is not None
            and destination > address
            and len(prefix) == 3
            and [item.mnemonic for item in prefix] == ["mov", "push", "jmp"]
            and prefix[-1].operands[0].type == X86_OP_IMM
            and prefix[-1].operands[0].imm == address - 5
            and instructions[index - 1].mnemonic == "mov"
            and instructions[index - 1].size == 5
        )
        calls.append(
            {
                "call": instruction_row(instructions[index]),
                "nearby_parity_test": instruction_row(instructions[tests[-1]])
                if tests
                else None,
                "branch": instruction_row(branch) if branch is not None else None,
                "branch_target_after_call": destination > address
                if destination is not None
                else None,
                "cold_argument_continuation": cold_continuation,
                "target_prefix": [instruction_row(item) for item in prefix],
            }
        )
    return {
        "interpretation": "Local instruction observations; absence means no recognized pattern, not proof of absence.",
        "winding_candidates": winding,
        "texture_calls": calls,
    }


def decode(data, address=0):
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    instructions = list(decoder.disasm(data, address))
    if sum(item.size for item in instructions) != len(data):
        raise ValueError("incomplete diagnostic disassembly")
    return instructions


def write_assembly(path, instructions):
    path.write_text(
        "\n".join(
            f"{item.address:08x} {item.mnemonic:8} {item.op_str}"
            for item in instructions
        )
        + "\n"
    )


def native_controls(output):
    manifest = load_function_symbol_manifest(DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH)
    image = ROOT / manifest.primary_target
    image_digest = digest(image.read_bytes())
    if image_digest != manifest.unwrapped_sha256:
        raise ValueError("native image does not match the pinned manifest")
    pe = pefile.PE(str(image))
    add_address = next(
        item.address
        for item in manifest.functions
        if item.name == "get_or_create_texture_ref"
    )
    controls = {}
    for name in NATIVE_CONTROLS:
        status = evaluate_scratch(
            load_scratch_config(DEFAULT_MATCH_ROOT / "scratches" / name)
        )
        if status.error or status.address is None or status.target_size is None:
            raise ValueError(f"cannot evaluate native control: {name}")
        body = pe.get_data(
            status.address - pe.OPTIONAL_HEADER.ImageBase, status.target_size
        )
        instructions = decode(body, status.address)
        calls = {
            item.address
            for item in instructions
            if item.mnemonic == "call"
            and item.operands[0].type == X86_OP_IMM
            and item.operands[0].imm == add_address
        }
        write_assembly(output / f"native-{name}.asm", instructions)
        controls[name] = {
            "address": hex(status.address),
            "size": len(body),
            "body_sha256": digest(body),
            "instructions": len(instructions),
            "current_match_ratio": status.ratio,
            "references": {
                "ok": status.masked_ok,
                "unresolved": status.masked_unresolved,
                "mismatched": status.masked_mismatches,
                "unaudited": status.masked_unaudited,
            },
            "patterns": patterns(instructions, calls),
        }
    return image_digest, controls


def main():
    from probe_texture_continuations import cold_continuations

    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--variant-prefix", default="",
        help="Run only diagnostic names starting with this prefix",
    )
    parser.add_argument(
        "--out",
        type=Path,
        default=ROOT / "artifacts/match/face-emission-context-20260908",
    )
    args = parser.parse_args()
    output = args.out.resolve()
    output.mkdir(parents=True, exist_ok=True)
    source_path = DEFAULT_MATCH_ROOT / "scratches" / FUNCTION / "scratch.cpp"
    original = source_path.read_text()
    image_digest, controls = native_controls(output)
    runner_name = os.environ.get("WIBO")
    if runner_name is None:
        bundled = DEFAULT_MATCH_ROOT / "bin/wibo"
        runner_name = str(bundled) if bundled.is_file() else "wibo"
    runner = shutil.which(runner_name)
    if runner is None:
        raise ValueError(f"cannot find runner: {runner_name}")
    environment = {**os.environ, "MSVC_VER": "msvc6.5", "WIBO": runner}
    config = load_scratch_config(source_path.parent)
    if config.compiler != "msvc6.5":
        raise ValueError("diagnostic baseline requires the canonical VC6 profile")
    receipt = {
        "schema": 1,
        "classification": "compiler diagnostics; reductions carry no source-matching or runtime credit",
        "source_sha256": digest(source_path.read_bytes()),
        "image_sha256": image_digest,
        "compiler": "msvc6.5",
        "runner_sha256": digest(Path(runner).read_bytes()),
        "tool_sha256": digest(Path(__file__).read_bytes()),
        "continuation_recognizer_sha256": digest(
            Path(__file__).with_name("probe_texture_continuations.py").read_bytes()
        ),
        "build_inputs": {
            str(path.relative_to(ROOT)): digest(path.read_bytes())
            for path in _scratch_build_dependencies(config, DEFAULT_MATCH_ROOT)
        },
        "native_controls": controls,
        "reductions": {},
    }
    variants = {
        name: source for name, source in build_variants(original).items()
        if name.startswith(args.variant_prefix)
    }
    if not variants:
        raise ValueError(f"no diagnostic names start with {args.variant_prefix!r}")
    for name, source in variants.items():
        directory = output / name
        directory.mkdir(exist_ok=True)
        (directory / "reduction.cpp").write_text(source)
        extra_flags = (
            ["/Og-"]
            if name.endswith("_global_opt_off")
            else ["/Os"]
            if name.endswith("_size_preference")
            else []
        )
        flags = ["/O2", *extra_flags, "/G5", "/W3"]
        process = subprocess.run(
            [str(DEFAULT_MATCH_ROOT / "cl.sh"), "/c", *flags, "/FAsc", "reduction.cpp"],
            cwd=directory,
            text=True,
            capture_output=True,
            env=environment,
            check=False,
        )
        (directory / "compiler.log").write_text(process.stdout + process.stderr)
        if process.returncode:
            raise RuntimeError(f"{name}: {process.stdout}{process.stderr}")
        function_name = (
            FUNCTION if "void cRPath::initialize_sbend" in source else "reduction"
        )
        function = extract_object_function(
            parse_coff_object((directory / "reduction.obj").read_bytes()),
            function_name,
        )
        instructions = decode(function.data)
        calls = {
            reference.offset - 1
            for reference in function.relocation_references
            if reference.symbol_name.startswith("?Add@cRTextures@@")
        }
        write_assembly(directory / "reduction.asm", instructions)
        receipt["reductions"][name] = {
            "flags": flags,
            "source_sha256": digest(source.encode()),
            "instructions": len(instructions),
            "size": len(function.data),
            "code_sha256": object_function_fingerprint(function),
            "patterns": patterns(instructions, calls),
            "strict_call_continuations": cold_continuations(instructions, calls),
        }
        print(f"{name}: {len(instructions)} instructions, {len(calls)} texture calls")
    if digest(source_path.read_bytes()) != receipt["source_sha256"] or any(
        digest((ROOT / name).read_bytes()) != expected
        for name, expected in receipt["build_inputs"].items()
    ):
        raise ValueError("diagnostic source inputs changed during compilation")
    (output / "receipt.json").write_text(json.dumps(receipt, indent=2) + "\n")
    print(f"Diagnostic receipt: {output / 'receipt.json'}")


if __name__ == "__main__":
    main()
