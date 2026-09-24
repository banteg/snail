"""Trace VC6 C2's eax/ecx/edx rotation cursor for one Snail scratch (diagnostic only).

Hooks the only call to C2's local register selector (see register-rotation.md)
through Crimson's preserving observer, records the selector's inputs and result
for every temporary it colours, re-derives each choice from the documented
rule, marks allocations whose instruction later disappears, and maps each one
to its source line and to the native register implied by the structural diff.
The summary lists where the implied native cursor stops agreeing with ours.

    uv run tools/match/c2/rotation.py update_subgame [--source overlay.cpp] [--out DIR]
"""

import argparse
import difflib
import json
import re
import struct
import sys
import tempfile
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import trace as t

from snail import match as m

c2 = t.c2

# C2.DLL RVAs (image base 0x10700000), pinned by the profile's C2 SHA-256.
FUNCTION_ENTRY_HOOK = {"site": 0x581EE, "target": 0x130CB, "return": False}
SELECTOR_HOOK = {"site": 0x385B4, "target": 0x3C97C, "return": True}
FINAL_HOOK = {
    "site": 0x585B1,
    "target": 0x3EBEA,
    "return": False,
}  # late pass, esi = function
REGISTER_DESCRIPTORS = 0xAC730  # 0x54-byte descriptor per register number
DESCRIPTOR_SIZE = 0x54
ORDER_LIST = 0xADFF4  # 1,2,3,7,8,4,6,0: eax ecx edx esi edi ebx ebp
CURSOR = 0x9D710  # pointer into ORDER_LIST, reset per function at +0x3375e
HOLDERS = 0x9D6EC  # [reg] -> operand currently occupying the register
CONFLICTS = 0x9D6C8  # [reg] -> bit set of temporaries that must avoid it
ROTATE_ENABLED = 0xAC0B4
BIT_TEST = 0x251D

REGISTERS = {
    1: "eax",
    2: "ecx",
    3: "edx",
    4: "ebx",
    5: "esp",
    6: "ebp",
    7: "esi",
    8: "edi",
}
ORDER = (1, 2, 3, 7, 8, 4, 6)
ROTATING = (1, 2, 3)
ENTRY_WORDS, RETURN_WORDS = 14, 5

RECORDER = r"""
static HANDLE rotation_file;
static void rotation_write(void *data, unsigned long size)
{
    DWORD written;
    if (!WriteFile(rotation_file, data, size, &written, 0) || written != size)
        ExitProcess(79);
}
typedef int (__fastcall *rotation_bit_test_t)(void *, unsigned long);
/* Selector inputs (entry) and result (return); see rotation.py for layout. */
static void rotation_observe(unsigned long phase, unsigned long *registers)
{
    unsigned char *base = (unsigned char *)targets[ROTATION_HOOK] - SELECTOR_TARGET;
    unsigned long values[ENTRY_WORDS], r;
    unsigned long *node = (unsigned long *)registers[5];
    unsigned long *operand = (unsigned long *)registers[6];
    unsigned long *temp;
    rotation_bit_test_t bit_test = (rotation_bit_test_t)(base + BIT_TEST);
    unsigned long cursor = (*(unsigned long *)(base + CURSOR) - (unsigned long)(base + ORDER_LIST)) / 4;
    if (phase >= 100) {
        values[0] = 2; values[1] = registers[7] - (unsigned long)base; values[2] = cursor;
        values[3] = ((unsigned long *)operand_saved)[11]; values[4] = operand_saved;
        rotation_write(values, RETURN_WORDS * 4);
        return;
    }
    temp = (unsigned long *)operand[6];
    operand_saved = (unsigned long)temp;
    values[0] = 1; values[1] = saved_function; values[2] = (unsigned long)node;
    values[3] = *(unsigned long *)(node + 1); values[4] = *(unsigned short *)(node + 4);
    values[5] = (unsigned long)temp; values[6] = temp[7]; values[7] = temp[11];
    values[8] = 0; values[9] = 0; values[10] = cursor;
    values[11] = *(unsigned long *)(base + ROTATE_ENABLED);
    values[12] = (unsigned long)operand; values[13] = (unsigned long)base;
    for (r = 1; r <= 8; ++r) {
        if (*(unsigned long *)(base + HOLDERS + r * 4)) values[8] |= 1 << r;
        if (bit_test(*(void **)(base + CONFLICTS + r * 4), temp[7])) values[9] |= 1 << r;
    }
    rotation_write(values, ENTRY_WORDS * 4);
}
"""


def observer(profile, stock_source):
    hook = len(profile["hooks"]) - 1
    defines = {
        "ROTATION_HOOK": hook,
        "SELECTOR_TARGET": SELECTOR_HOOK["target"],
        "ENTRY_WORDS": ENTRY_WORDS,
        "RETURN_WORDS": RETURN_WORDS,
        "BIT_TEST": BIT_TEST,
        "CURSOR": CURSOR,
        "ORDER_LIST": ORDER_LIST,
        "HOLDERS": HOLDERS,
        "CONFLICTS": CONFLICTS,
        "ROTATE_ENABLED": ROTATE_ENABLED,
    }
    header = "".join(f"#define {k} {v}\n" for k, v in defines.items())
    source = stock_source(profile)
    anchors = (
        "static HANDLE trace_file;",
        "    unsigned long first, node, count = 0, record[742], op, side, j, k, at;\n",
        "    trace_file = CreateFileA(",
        "    CloseHandle(trace_file);",
        "static void __cdecl observe(",
    )
    for anchor in anchors:
        if source.count(anchor) != 1:
            raise ValueError(f"Unexpected Crimson observer template near {anchor!r}")
    # The recorder uses the generated targets/offsets arrays, so place it
    # before observe() but after the generated profile declarations.
    source = source.replace(
        "static void __cdecl observe(",
        header
        + "static unsigned long operand_saved;\n"
        + RECORDER
        + "static void __cdecl observe(",
    )
    source = source.replace(
        anchors[1],
        anchors[1]
        + "    if (phase % 100 == ROTATION_HOOK) { rotation_observe(phase, registers); return; }\n",
    )
    source = source.replace(
        anchors[2],
        '    rotation_file = CreateFileA("rotation.bin", GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);\n'
        "    if (rotation_file == INVALID_HANDLE_VALUE) ExitProcess(78);\n"
        + anchors[2],
    )
    return source.replace(anchors[3], "    CloseHandle(rotation_file);\n" + anchors[3])


def run_observer(scratch, out):
    """Preserving run: whole-COFF identity and matcher metrics are checked by the adapter."""
    stock_profile, stock_source = c2.load_profile, c2.observer_source
    profile = stock_profile()
    hooks = [FUNCTION_ENTRY_HOOK, FINAL_HOOK, SELECTOR_HOOK]
    profile = dict(profile, name=profile["name"] + "-rotation", hooks=hooks)
    c2.load_profile = lambda: profile
    c2.observer_source = lambda p: observer(p, stock_source)
    try:
        result, events = t.trace(scratch, out)
    finally:
        c2.load_profile, c2.observer_source = stock_profile, stock_source
    return result, events, (out / "observed/rotation.bin").read_bytes()


def decode(data):
    rows, at, pending = [], 0, None
    while at < len(data):
        (kind,) = struct.unpack_from("<I", data, at)
        if kind == 1:
            if pending is not None:
                raise ValueError("Selector entry without return")
            w = struct.unpack_from(f"<{ENTRY_WORDS}I", data, at)
            at += ENTRY_WORDS * 4
            base = w[13]
            pending = {
                "function": w[1],
                "node": w[2],
                "opcode": w[3] & 0xFFFF,
                "label": w[4],
                "temp": w[5],
                "temp_id": w[6],
                "preference_in": register_of(w[7] - base if w[7] else 0),
                "busy": mask(w[8]),
                "excluded": mask(w[9]),
                "cursor_in": w[10],
                "rotation_enabled": bool(w[11]),
                "operand": w[12],
                "_base": base,
            }
        elif kind == 2:
            w = struct.unpack_from(f"<{RETURN_WORDS}I", data, at)
            at += RETURN_WORDS * 4
            if pending is None or w[4] != pending["temp"]:
                raise ValueError("Selector return without entry")
            base = pending.pop("_base")
            pending["register"] = register_of(w[1]) or "none"
            pending["cursor_out"] = w[2]
            pending["preference_out"] = register_of(w[3] - base if w[3] else 0)
            rows.append(pending)
            pending = None
        else:
            raise ValueError(f"Unknown rotation record {kind}")
    if pending is not None:
        raise ValueError("Truncated rotation trace")
    return rows


def register_of(rva):
    """Register named by a C2-relative register descriptor address."""
    offset = rva - REGISTER_DESCRIPTORS
    if not rva or offset < 0 or offset % DESCRIPTOR_SIZE:
        return None
    return REGISTERS.get(offset // DESCRIPTOR_SIZE)


def mask(bits):
    return [REGISTERS[r] for r in sorted(REGISTERS) if bits & (1 << r)]


def predict(row):
    """Re-derive the selector's first three paths (documented in register-rotation.md)."""
    free = [
        r
        for r in ORDER
        if REGISTERS[r] not in row["busy"] and REGISTERS[r] not in row["excluded"]
    ]
    names = [REGISTERS[r] for r in free]
    preference = row["preference_out"]
    if preference and preference in names:
        return "preference", preference, row["cursor_in"]
    if row["rotation_enabled"]:
        start = row["cursor_in"] if row["cursor_in"] < 3 else 0
        for step in range(3):
            slot = (start + step) % 3
            if REGISTERS[ROTATING[slot]] in names:
                return "rotation", REGISTERS[ROTATING[slot]], (slot + 1) % 3
    if names:
        return "first-free", names[0], row["cursor_in"]
    return "spill", None, row["cursor_in"]


def assigned_register(operand, base):
    if operand["kind"] != 1:
        return None
    return register_of(operand["raw"][6] - base)


def attach_final(rows, events):
    """Mark whether each coloured temporary still appears in C2's final node list."""
    final = {}
    for event in events:
        if event["phase"] == 1:  # FINAL_HOOK entry, one per function
            final[event["function_address"]] = event
    for row in rows:
        event = final.get(row["function"])
        if event is None:
            row["final"] = "unobserved"
            continue
        node = next((n for n in event["nodes"] if n["id"] == row["node"]), None)
        # Arena addresses are recycled, so a different opcode/line is a new node.
        if node is None or (node["op"] & 0xFFFF, node["line"]) != (
            row["opcode"],
            row["label"],
        ):
            row["final"] = "removed"
            continue
        registers = {
            assigned_register(op, event["c2_base"])
            for side in ("src", "dst")
            for op in node[side]
        }
        row["final"] = "kept" if row["register"] in registers else "folded"


def definition_line(source_text, symbol):
    """Line of the function definition; C2 line labels are relative to it."""
    name = symbol
    if symbol.startswith("?"):
        parts = symbol[1:].split("@@")[0].split("@")
        name = "::".join(reversed(parts))
    pattern = re.compile(r"^\S.*\b" + re.escape(name) + r"\s*\(")
    lines = [
        i for i, text in enumerate(source_text.splitlines(), 1) if pattern.match(text)
    ]
    if not lines:
        raise ValueError(f"Cannot find the definition of {name}")
    return lines[-1]


SCRATCH_TOKEN = re.compile(r"\b(?:e?[abcd]x|[abcd][lh])\b")
WIDE = {"a": "eax", "b": "ebx", "c": "ecx", "d": "edx"}


def widen(token):
    return (
        token if token.startswith("e") else WIDE[token[0]] if token != "bx" else "ebx"
    )


def native_registers(config, work, object_path):
    """Candidate instruction -> (source lines, native register renaming) via the structural diff."""
    manifest = m.load_function_symbol_manifest(m.DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH)
    dump = m.run_match_dump(
        obj_path=object_path,
        function_name=config.function,
        image_path=m.REPO_ROOT / manifest.primary_target,
        manifest=manifest,
        symbol_name=config.symbol,
        end_va=config.end_va,
    )
    listing = m.generate_compiler_listing(config, output=work / "listing.cod")
    lines_at = {}
    for span in listing.spans:
        for offset in span.instruction_offsets:
            lines_at[offset] = span.source_lines
    target = [m.structural_line(line.text) for line in dump.target_lines]
    candidate = [m.structural_line(line.text) for line in dump.candidate_lines]
    aligned = {}
    matcher = difflib.SequenceMatcher(a=target, b=candidate, autojunk=False)
    for tag, i1, i2, j1, j2 in matcher.get_opcodes():
        if tag == "equal":
            for k in range(i2 - i1):
                aligned[j1 + k] = i1 + k
    rows = []
    for j, line in enumerate(dump.candidate_lines):
        i = aligned.get(j)
        rows.append(
            {
                "index": j,
                "offset": line.offset,
                "text": line.text,
                "lines": lines_at.get(line.offset, ()),
                "target_index": i,
                "target_text": dump.target_lines[i].text if i is not None else None,
            }
        )
    return rows


def destination(text):
    """First operand register of a normalized instruction, if it is a register."""
    parts = text.split(None, 1)
    if len(parts) < 2:
        return None
    first = parts[1].split(",")[0].strip()
    return widen(first) if SCRATCH_TOKEN.fullmatch(first) else None


def renamed(candidate_text, target_text, register):
    ours = SCRATCH_TOKEN.findall(candidate_text)
    theirs = SCRATCH_TOKEN.findall(target_text)
    for a, b in zip(ours, theirs):
        if widen(a) == register:
            return widen(b)
    return None


def link(rows, instructions, first_line):
    """Pair each allocation with the first unclaimed candidate write of its register on its line."""
    claimed = set()
    for row in rows:
        row["line"] = first_line + row["label"]
        row["instruction"] = row["native"] = None
        for ins in instructions:
            if ins["index"] in claimed or row["line"] not in ins["lines"]:
                continue
            if destination(ins["text"]) != row["register"]:
                continue
            claimed.add(ins["index"])
            row["instruction"] = ins["index"]
            row["candidate_text"] = ins["text"]
            if ins["target_text"] is not None:
                row["native"] = renamed(
                    ins["text"], ins["target_text"], row["register"]
                )
            break


def implied_cursors(row):
    """Rotation cursors that would make the selector return the native register."""
    if row["native"] is None:
        return None
    hits = []
    for cursor in range(3):
        _path, register, _ = predict(dict(row, cursor_in=cursor))
        if register == row["native"]:
            hits.append(cursor)
    return hits


def offsets(rows):
    """Native-minus-candidate cursor offset wherever the native register pins it."""
    for row in rows:
        implied = row["implied"]
        determinate = row["path"] == "rotation" and implied and len(implied) == 1
        row["offset"] = (implied[0] - row["cursor_in"]) % 3 if determinate else None


def shifts(rows):
    """Windows of allocations across which the implied offset changes."""
    previous = None
    for k, row in enumerate(rows):
        if row["offset"] is None:
            continue
        if previous is None:
            if row["offset"]:
                yield None, k, 0, row["offset"]
        elif rows[previous]["offset"] != row["offset"]:
            yield previous, k, rows[previous]["offset"], row["offset"]
        previous = k


def report(rows, source_lines):
    def text(row):
        line = row["line"]
        return (
            source_lines[line - 1].strip()[:56] if 0 < line <= len(source_lines) else ""
        )

    print(
        f"{'#':>4} {'line':>5} {'op':>4} {'cur':>3} {'path':10} {'reg':4} {'final':8}"
        f" {'native':6} {'n-cur':5} {'off':>3}  source"
    )
    for k, row in enumerate(rows):
        implied = ",".join(map(str, row["implied"])) if row["implied"] else "-"
        offset = "-" if row["offset"] is None else f"+{row['offset']}"
        mark = " <<" if row["native"] and row["native"] != row["register"] else ""
        print(
            f"{k:4d} {row['line']:5d} {row['opcode']:4d} {row['cursor_in']:3d}"
            f" {row['path']:10} {row['register']:4} {row['final']:8}"
            f" {row['native'] or '-':6} {implied:5} {offset:>3}  {text(row)}{mark}"
        )
    found = list(shifts(rows))
    print("\nrotation shifts (native cursor minus candidate cursor, mod 3):")
    if not found:
        print("  none: every pinned allocation agrees with native")
    for before, after, old, new in found:
        start = 0 if before is None else before + 1
        print(
            f"  +{old} -> +{new} between #{start - 1 if before is not None else '-'} and #{after}:"
        )
        for row in rows[start : after + 1]:
            print(
                f"    #{rows.index(row)} line {row['line']} {row['path']} {row['register']}"
                f" ({row['final']}): {text(row)}"
            )


def prepare(scratch, source, work):
    """Freeze scratch.conf with the canonical or overlay source in a new directory."""
    work.mkdir(parents=True)
    (work / "scratch.conf").write_bytes((scratch / "scratch.conf").read_bytes())
    (work / "scratch.cpp").write_bytes((source or scratch / "scratch.cpp").read_bytes())
    return work


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("scratch", help="scratch name or directory")
    parser.add_argument(
        "--source", type=Path, help="overlay source replacing scratch.cpp"
    )
    parser.add_argument(
        "--out", type=Path, help="new output directory (default: a temporary one)"
    )
    parser.add_argument("--json", action="store_true", help="print rows as JSON")
    args = parser.parse_args()
    scratch = Path(args.scratch)
    if not scratch.is_dir():
        scratch = m.DEFAULT_MATCH_ROOT / "scratches" / args.scratch
    out = args.out or Path(tempfile.mkdtemp(prefix="c2rot-")) / "trace"
    work = prepare(scratch, args.source, out.parent / (out.name + "-input"))
    result, events, data = run_observer(work, out)
    rows = decode(data)
    functions = list(dict.fromkeys(row["function"] for row in rows))
    if not functions:
        print(f"trace: {out}  no temporary reached the rotation selector")
        return
    if len(functions) != 1:
        raise ValueError(f"Expected one allocating function, saw {len(functions)}")
    for row in rows:
        row["path"], predicted, cursor = predict(row)
        # The spill heuristics after the first-free scan are not modelled.
        if row["path"] != "spill" and (predicted, cursor) != (
            row["register"],
            row["cursor_out"],
        ):
            raise ValueError(f"Selector rule mismatch: {row}")
    attach_final(rows, events)
    config = m.load_scratch_config(work)
    source_text = (work / "scratch.cpp").read_text()
    first_line = definition_line(source_text, config.symbol or config.function)
    object_path = m.compile_scratch(config)
    instructions = native_registers(config, work, object_path)
    link(rows, instructions, first_line)
    for row in rows:
        row["implied"] = implied_cursors(row)
    offsets(rows)
    (out / "rotation.json").write_text(json.dumps(rows, indent=1) + "\n")
    if args.json:
        print(json.dumps(rows, indent=1))
    else:
        print(f"trace: {out}  metrics: {json.dumps(result['metrics'])}")
        report(rows, source_text.splitlines())


if __name__ == "__main__":
    main()
