"""Trace where VC6 SP3 creates Search's six swept-addition parameter fields.

Use --source for a whole-Path source overlay, and --out for a new trace directory.
"""

import argparse
import hashlib
import json
import struct
import sys
from pathlib import Path

SCRATCH = Path(__file__).resolve().parent
sys.path.insert(0, str(SCRATCH.parents[1] / "c2"))
import addrorder
import rotation
import trace

# The function driver passes the current function in ECX. Starting here catches
# inline expansion as well as copy propagation, before addrorder's final sort.
PREPARE = {"site": 0x682D3, "target": 0x1994F, "return": False}
# symbol_get_part calls symbol_alloc only when a part record is missing.
ALLOCATE_PART = {"site": 0x3890, "target": 0x1DA6, "return": True}
CREATORS = {
    0x5AC5E: "inline_propagate_address_formals",
    0x4203C: "propagate_copy_into_use",
    0x7409: "find_available_copy_source",
}

# At the allocator CALL in symbol_get_part, EDI is the parent symbol. PUSHAD
# records ESP after PUSHFD. The getter's return address is at stack[7].
RECORDER = r"""
static HANDLE part_file;
static void record_part(unsigned long phase, unsigned long *r)
{
    static unsigned long site;
    unsigned long *parent = (unsigned long *)r[0], *part, *front, *stack;
    unsigned long row[10] = {0}, i;
    const char *name;
    DWORD written;
    if (function_ordinal != SNAPSHOT_ORDINAL || !parent ||
        *((unsigned char *)parent + 4) != 5) return;
    if (phase == 2) {
        stack = (unsigned long *)r[3];
        site = stack[7] - ((unsigned long)targets[2] - 0x1da6) - 5;
        return;
    }
    part = (unsigned long *)r[7];
    front = (unsigned long *)parent[0];
    if (!part || !front || !(name = (const char *)front[6])) return;
    row[0] = r[7]; row[1] = part[7]; row[2] = r[0]; row[3] = site;
    for (i = 0; i < 23 && name[i]; ++i) ((char *)&row[4])[i] = name[i];
    if (!WriteFile(part_file, row, sizeof(row), &written, 0) ||
        written != sizeof(row)) ExitProcess(74);
}
"""


def observer(profile, stock):
    source = stock(profile)
    # Keep the ordinary target-gated snapshots, including each symbol's id,
    # parent, byte offset, and x87 sort key. The allocator uses a side stream.
    edits = {
        addrorder.STOCK_CAPTURE: addrorder.STOCK_CAPTURE + addrorder.SYMBOL_CAPTURE,
        "static void __cdecl observe(": RECORDER + "\nstatic void __cdecl observe(",
        "    if (phase < 12) saved_function": (
            "    if (phase % 100 == 2) { record_part(phase, registers); return; }\n"
            "    if (phase < 12) saved_function"
        ),
        '    trace_file = CreateFileA(': (
            '    part_file = CreateFileA("parts.bin", GENERIC_WRITE, 0, 0, '
            'CREATE_ALWAYS, 0, 0);\n'
            '    if (part_file == INVALID_HANDLE_VALUE) ExitProcess(73);\n'
            '    trace_file = CreateFileA('
        ),
        "    CloseHandle(trace_file);": "    CloseHandle(part_file);\n    CloseHandle(trace_file);",
    }
    for old, new in edits.items():
        if source.count(old) != 1:
            raise ValueError("Unexpected observer template")
        source = source.replace(old, new)
    return source


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--source", type=Path)
    parser.add_argument("--out", type=Path, required=True)
    args = parser.parse_args()
    work = rotation.prepare(SCRATCH, args.source, args.out.with_name(args.out.name + "-input"))
    c2 = trace.c2
    loader, stock = c2.load_profile, c2.observer_source
    profile = loader("msvc6.3")
    address_pass = profile["address_order"]["address_pass"]
    profile = dict(
        profile,
        name=profile["name"] + "-search-operands",
        hooks=[PREPARE, address_pass, ALLOCATE_PART],
    )
    c2.load_profile = lambda: profile
    c2.observer_source = lambda p: observer(p, stock)
    try:
        receipt, events = trace.trace(work, args.out, target_only=True)
    finally:
        c2.load_profile, c2.observer_source = loader, stock

    event = trace.function_event(events, receipt["function_ordinal"], address_pass["target"])
    parts = {}
    data = (args.out / "observed/parts.bin").read_bytes()
    for pointer, ident, parent, site, name in struct.iter_unpack("<4I24s", data):
        key = (pointer, ident, parent)
        name = name.partition(b"\0")[0].decode("ascii").removeprefix("_")
        if key in parts:
            raise ValueError("A parameter part identity was recycled")
        parts[key] = (name, site)

    lanes = {}
    for node in event["nodes"]:
        if node["op"] != 0x16D or node["flags"] >> 16 != 0x4004 or len(node["src"]) != 2:
            continue
        fields = []
        for op in node["src"]:
            words = op["temp_words"]
            if op["kind"] != 2 or words[1] & 0xFF != 5 or words[8] != 4:
                break
            key = (op["raw"][5], words[7], words[2])
            if key not in parts:
                break
            name, site = parts[key]
            slot = addrorder.describe(op)["id"]
            fields.append((name, words[9], slot, site))
        if len(fields) != 2 or {f[0] for f in fields} != {"position", "sweep"}:
            continue
        offset = fields[0][1]
        if fields[1][1] != offset or offset in lanes:
            raise ValueError("Ambiguous swept sum")
        if node["src"][0]["raw"][3] <= node["src"][1]["raw"][3]:
            raise ValueError("Expected two parameter operands sorted by descending cost")
        lanes[offset] = fields
    if set(lanes) != {0, 4, 8}:
        raise ValueError("Expected three paired parameter fields created during the traced compile")
    receipt["parts_sha256"] = hashlib.sha256(data).hexdigest()
    receipt["swept_operands"] = {
        "xyz"[offset // 4]: [
            {"parameter": name, "slot": slot, "creator_rva": site}
            for name, _, slot, site in fields
        ]
        for offset, fields in sorted(lanes.items())
    }
    (args.out / "snail-receipt.json").write_text(json.dumps(receipt, indent=2) + "\n")
    print(receipt["metrics"])
    for offset, fields in sorted(lanes.items()):
        print("xyz"[offset // 4], " > ".join(
            f"{name} #{slot:x} ({CREATORS.get(site, 'other')} at C2+{site:x})"
            for name, _, slot, site in fields
        ))


if __name__ == "__main__":
    main()
