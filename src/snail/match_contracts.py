"""Conservative, read-only evidence for revisiting x86 return contracts."""

from __future__ import annotations

import re
from collections import Counter
from pathlib import Path

import capstone
from capstone import x86_const as x86

from . import match as matchlib

EAX_PARTS = {x86.X86_REG_EAX, x86.X86_REG_AX, x86.X86_REG_AL, x86.X86_REG_AH}


def decoder():
    engine = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    engine.detail = True
    return engine


def instruction_text(insn) -> str:
    return f"0x{insn.address:x}: {insn.mnemonic} {insn.op_str}".rstrip()


def caller_eax_use(instructions) -> dict:
    """Track the immediately following straight-line path; never assume call ABI."""
    trace = []
    partial_write = False
    for insn in instructions:
        trace.append(instruction_text(insn))
        if insn.group(capstone.CS_GRP_JUMP):
            return {"outcome": "unknown-control-flow", "trace": trace}
        if insn.group(capstone.CS_GRP_CALL):
            return {"outcome": "unknown-call-contract", "trace": trace}
        if insn.group(capstone.CS_GRP_RET):
            return {"outcome": "unknown-forwarded-return", "trace": trace}
        if insn.mnemonic.startswith("cmov") and insn.operands[0].reg in EAX_PARTS:
            return {"outcome": "unknown-conditional-write", "trace": trace}
        reads, writes = map(set, insn.regs_access())
        zeroing = (
            insn.mnemonic in {"xor", "sub"}
            and len(insn.operands) == 2
            and all(
                op.type == x86.X86_OP_REG and op.reg == x86.X86_REG_EAX
                for op in insn.operands
            )
        )
        if not zeroing and reads & EAX_PARTS:
            return {
                "outcome": "read-after-partial-write" if partial_write else "read",
                "trace": trace,
            }
        if x86.X86_REG_EAX in writes:
            return {"outcome": "discarded", "trace": trace}
        if writes & EAX_PARTS:
            partial_write = True
        if insn.group(capstone.CS_GRP_INT) or insn.mnemonic in {"hlt", "ud2"}:
            return {"outcome": "unknown-interruption", "trace": trace}
    return {"outcome": "unknown-range-end", "trace": trace}


def audit_contract(
    config, *, image_path: Path, manifest, mobile_crosswalk=None
) -> dict:
    start, end = matchlib.resolve_function_extent(
        manifest, config.function, config.end_va
    )
    image = matchlib.load_image(image_path, manifest.image_base)
    engine = decoder()
    callers, skipped = [], []
    scanned = 0
    for function in manifest.functions:
        try:
            caller_start, caller_end = matchlib.resolve_function_extent(
                manifest, function.name, None
            )
            data = image.function_bytes(caller_start, caller_end)
            instructions = list(engine.disasm(data, caller_start))
        except (ValueError, OSError) as error:
            skipped.append({"function": function.name, "reason": str(error)})
            continue
        scanned += 1
        decoded_end = (
            instructions[-1].address + instructions[-1].size
            if instructions
            else caller_start
        )
        if decoded_end != caller_start + len(data):
            skipped.append(
                {"function": function.name, "reason": "incomplete linear decode"}
            )
        for index, insn in enumerate(instructions):
            if (
                insn.mnemonic == "call"
                and len(insn.operands) == 1
                and insn.operands[0].type == x86.X86_OP_IMM
                and insn.operands[0].imm == start
            ):
                callers.append(
                    {
                        "caller_range": function.name,
                        "address": insn.address,
                        **caller_eax_use(instructions[index + 1 :]),
                    }
                )
    target = list(engine.disasm(image.function_bytes(start, end), start))
    exits = [
        {
            "address": insn.address,
            "instruction": instruction_text(insn),
            "context": [
                instruction_text(i) for i in target[max(0, index - 8) : index + 1]
            ],
        }
        for index, insn in enumerate(target)
        if insn.group(capstone.CS_GRP_RET)
    ]
    mobile = next(
        (
            entry
            for entry in (mobile_crosswalk or {}).get("entries", [])
            if int(entry["address"], 16) == start
        ),
        None,
    )
    # Unverified fuzzy name candidates are not contract evidence.
    mobile_evidence = mobile if mobile and mobile.get("status") == "verified" else None
    source_text = (config.directory / "scratch.cpp").read_text()
    # A located source excerpt, not a C++ parser or an inferred prototype.
    declaration = re.search(
        r"(?m)^[^\n;{}]*\b"
        + re.escape(config.function)
        + r"\s*\([^;{}]*\)\s*(?:const\s*)?\{",
        source_text,
    )
    source_declaration = (
        {
            "text": declaration.group().removesuffix("{").strip(),
            "line": source_text.count("\n", 0, declaration.start()) + 1,
        }
        if declaration
        else None
    )
    counts = dict(Counter(caller["outcome"] for caller in callers))
    return {
        "schema": 1,
        "kind": "return-contract-audit",
        "function": config.function,
        "address": start,
        "end_address": end,
        "source": str(config.directory / "scratch.cpp"),
        "source_declaration": source_declaration,
        "callers": callers,
        "caller_outcomes": counts,
        "native_return_windows": exits,
        "mobile_evidence": mobile_evidence,
        "review_hint": (
            "All observed direct call sites discard EAX; review whether the source return is supported."
            if callers and counts.get("discarded") == len(callers)
            else "Review return evidence manually; caller observations do not settle the declaration."
        ),
        "coverage": {
            "manifest_functions_scanned": scanned,
            "decode_limitations": skipped,
            "target_decoded_bytes": sum(i.size for i in target),
        },
        "limitations": [
            "Caller names label manifest ranges, not proven function ownership. Direct calls in linearly decoded manifest ranges only; indirect calls and unlisted code are not covered, and embedded data may decode as instructions.",
            "Caller analysis stops at branches, calls, or returns. Partial-register writes do not count as discarding the whole EAX value.",
            "Return windows are nearby instructions, not proven dataflow paths. EAX use alone cannot establish void, ownership, types, or x87/EDX return contracts.",
            "Mobile signatures describe another port; C++ mangled names usually omit return types. No declarations are changed.",
        ],
    }


def render_contract_audit(payload: dict) -> str:
    lines = [
        f"{payload['function']} @ 0x{payload['address']:x}",
        payload["review_hint"],
    ]
    if payload["source_declaration"]:
        lines.append(
            f"Source excerpt at {payload['source']}:{payload['source_declaration']['line']}:\n"
            + payload["source_declaration"]["text"]
        )
    for caller in payload["callers"]:
        lines.append(
            f"\n{caller['caller_range']} range, call @ 0x{caller['address']:x}: {caller['outcome']}"
        )
        lines.extend(f"  {line}" for line in caller["trace"])
    for window in payload["native_return_windows"]:
        lines.append("\nNative return window:")
        lines.extend(f"  {line}" for line in window["context"])
    if payload["mobile_evidence"]:
        import json

        lines.append(
            "\nVerified mobile mapping: "
            + json.dumps(payload["mobile_evidence"], sort_keys=True)
        )
    else:
        lines.append("\nNo verified mobile mapping available.")
    lines.append(
        f"\nCoverage: {payload['coverage']['manifest_functions_scanned']} manifest ranges; "
        f"{len(payload['coverage']['decode_limitations'])} decode limitations"
    )
    lines.extend(payload["limitations"])
    return "\n".join(lines)
