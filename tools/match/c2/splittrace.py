"""Trace VC6 C2's /G5 memory-operand split register picks for one scratch (diagnostic only).

msvc6.3 only. The split pass (`C2+0x31ae7`, see register-rotation.md) runs after
the local allocator. For a node whose opcode has the split flag
(`[0x107a049c + 4*op] & 0x400`) it asks the chooser `C2+0x32fbc` for a scratch
register. The chooser keeps its own cursor `C2+0xac2dc` into the order list
{eax, ecx, edx, esi, edi, ebx, ebp}:

- the pass walks each block backwards and resets the cursor to
  `[C2+0xac2e0] - 1` at every block, so the block's first pick starts at the
  first order entry;
- a pick tries the entries after the cursor, wrapping at `[C2+0xac2e0]`, and
  takes the first one whose descriptor flag `0x10` (byte `+0x35`) is set and
  that is not in the live set; the cursor moves to it;
- if it comes back to the cursor, a second lap tries the entries from the
  first up to the cursor without the flag test;
- if that fails too, it takes the first order entry outside the live set and
  moves the cursor there.

The byte-register site only accepts eax, ecx, edx and ebx.

The script hooks both call sites, re-derives every pick in the unit from this
rule, and prints the picks of the traced function with their source line,
cursor in/out, the live and flagged registers, and the register returned.

    uv run tools/match/c2/splittrace.py populate_runtime_track_cells_from_segments [--source overlay.cpp]
"""

import argparse
import struct
import sys
import tempfile
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import trace as t

import rotation as rot

from snail import match as m

c2 = t.c2

CHOOSER = 0x32FBC
SITES = (0x31D72, 0x31E48)  # any register; byte register (edx = 1)
CURSOR, COUNT = 0xAC2DC, 0xAC2E0
ENTRY_WORDS, RETURN_WORDS = 9, 3

RECORDER = r"""
static HANDLE split_file;
typedef int (__fastcall *split_bit_test_t)(void *, unsigned long);
static void split_write(void *data, unsigned long size)
{
    DWORD written;
    if (!WriteFile(split_file, data, size, &written, 0) || written != size) ExitProcess(79);
}
static void split_observe(unsigned long phase, unsigned long *registers)
{
    unsigned char *base = (unsigned char *)targets[phase % 100] - CHOOSER_TARGET;
    split_bit_test_t bit_test = (split_bit_test_t)(base + BIT_TEST);
    unsigned long values[ENTRY_WORDS], r;
    if (phase >= 100) {
        values[0] = 2; values[1] = registers[7]; values[2] = *(unsigned long *)(base + SPLIT_CURSOR);
        split_write(values, RETURN_WORDS * 4);
        return;
    }
    values[0] = 1; values[1] = phase % 100;
    /* ebp holds the node at the any-register site only. */
    values[2] = phase % 100 == FIRST_SPLIT_HOOK ? registers[2] : 0;
    values[3] = values[2] ? *(unsigned long *)(values[2] + 4) : 0;
    values[4] = values[2] ? *(unsigned short *)(values[2] + 0x10) : 0;
    values[5] = *(unsigned long *)(base + SPLIT_CURSOR);
    values[6] = *(unsigned long *)(base + SPLIT_COUNT);
    values[7] = 0; values[8] = 0;
    for (r = 1; r <= 8; ++r) {
        if (bit_test((void *)registers[6], r)) values[7] |= 1 << r;
        if (*(unsigned char *)(base + REGISTER_DESCRIPTORS + r * 0x54 + 5) & 0x10) values[8] |= 1 << r;
    }
    split_write(values, ENTRY_WORDS * 4);
}
"""


def observer(profile, stock_source, first_hook):
    defines = {
        "CHOOSER_TARGET": CHOOSER,
        "SPLIT_CURSOR": CURSOR,
        "SPLIT_COUNT": COUNT,
        "REGISTER_DESCRIPTORS": rot.REGISTER_DESCRIPTORS,
        "BIT_TEST": rot.BIT_TEST,
        "ENTRY_WORDS": ENTRY_WORDS,
        "RETURN_WORDS": RETURN_WORDS,
        "FIRST_SPLIT_HOOK": first_hook,
    }
    header = "".join(f"#define {k} {v}\n" for k, v in defines.items())
    source = stock_source(profile)
    anchors = (
        "    unsigned long first, node, count = 0, record[742], op, side, j, k, at;\n",
        "    trace_file = CreateFileA(",
        "    CloseHandle(trace_file);",
        "static void __cdecl observe(",
    )
    for anchor in anchors:
        if source.count(anchor) != 1:
            raise ValueError(f"Unexpected Crimson observer template near {anchor!r}")
    source = source.replace("if(op) ExitProcess(98);", "")
    source = source.replace(anchors[3], header + RECORDER + anchors[3])
    source = source.replace(
        anchors[0],
        anchors[0]
        + "    if (phase % 100 >= FIRST_SPLIT_HOOK) { split_observe(phase, registers); return; }\n"
        + "    if (phase == 0) { unsigned long marker = 3; split_write(&marker, 4); }\n",
    )
    source = source.replace(
        anchors[1],
        '    split_file = CreateFileA("split.bin", GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);\n'
        "    if (split_file == INVALID_HANDLE_VALUE) ExitProcess(78);\n" + anchors[1],
    )
    return source.replace(anchors[2], "    CloseHandle(split_file);\n" + anchors[2])


def run_observer(scratch, out):
    stock_profile, stock_source = c2.load_profile, c2.observer_source
    profile = rot.use_backend(m.load_scratch_config(scratch).compiler)
    if profile["compiler"] != "msvc6.3":
        raise ValueError("splittrace.py knows only the msvc6.3 split pass addresses")
    hooks = [rot.FUNCTION_ENTRY_HOOK] + [
        {"site": site, "target": CHOOSER, "return": True} for site in SITES
    ]
    profile = dict(profile, name=profile["name"] + "-split", hooks=hooks)
    c2.load_profile = lambda: profile
    c2.observer_source = lambda p: observer(p, stock_source, 1)
    try:
        result, _events = t.trace(scratch, out)
    finally:
        c2.load_profile, c2.observer_source = stock_profile, stock_source
    return result, (out / "observed/split.bin").read_bytes()


def names(bits):
    return [rot.REGISTERS[r] for r in sorted(rot.REGISTERS) if bits & (1 << r)]


def decode(data):
    rows, at, ordinal, pending = [], 0, -1, None
    while at < len(data):
        (kind,) = struct.unpack_from("<I", data, at)
        if kind == 3:
            at += 4
            ordinal += 1
        elif kind == 1:
            w = struct.unpack_from(f"<{ENTRY_WORDS}I", data, at)
            at += ENTRY_WORDS * 4
            pending = {
                "ordinal": ordinal,
                "site": "byte" if w[1] == 2 else "any",
                "node": w[2],
                "opcode": w[3] & 0xFFFF,
                "label": w[4],
                "cursor_in": w[5],
                "count": w[6],
                "live": names(w[7]),
                "flagged": names(w[8]),
            }
        elif kind == 2:
            w = struct.unpack_from(f"<{RETURN_WORDS}I", data, at)
            at += RETURN_WORDS * 4
            pending["register"] = rot.REGISTERS.get(w[1], "none")
            pending["cursor_out"] = w[2]
            rows.append(pending)
            pending = None
        else:
            raise ValueError(f"Unknown split record {kind}")
    return rows


ORDER = (1, 2, 3, 7, 8, 4, 6, 0)


def predict(row):
    """Re-derive a pick from the chooser rule above: (register, cursor out)."""
    cursor, count = row["cursor_in"], row["count"]

    def fits(index, flag_test):
        register = ORDER[index]
        if not register or (row["site"] == "byte" and register > 4):
            return False
        name = rot.REGISTERS[register]
        return (not flag_test or name in row["flagged"]) and name not in row["live"]

    index = cursor + 1 if cursor + 1 < count else 0
    while index != cursor:
        if fits(index, True):
            return rot.REGISTERS[ORDER[index]], index
        index = index + 1 if index + 1 < count else 0
    index = 0
    while index != cursor:
        if fits(index, False):
            return rot.REGISTERS[ORDER[index]], index
        index = index + 1 if index + 1 < count else 0
    for index, register in enumerate(ORDER):
        if register and fits(index, False):
            return rot.REGISTERS[register], index
    return "none", cursor


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("scratch", help="scratch name or directory")
    parser.add_argument("--source", type=Path, help="overlay source replacing scratch.cpp")
    parser.add_argument("--out", type=Path, help="new output directory (default: a temporary one)")
    args = parser.parse_args()
    scratch = Path(args.scratch)
    if not scratch.is_dir():
        scratch = m.DEFAULT_MATCH_ROOT / "scratches" / args.scratch
    out = args.out or Path(tempfile.mkdtemp(prefix="c2split-")) / "trace"
    work = rot.prepare(scratch, args.source, out.parent / (out.name + "-input"))
    result, data = run_observer(work, out)
    every = decode(data)
    for row in every:
        if predict(row) != (row["register"], row["cursor_out"]):
            raise ValueError(f"Split chooser rule mismatch: {row}")
    rows = [row for row in every if row["ordinal"] == result["function_ordinal"]]
    config = m.load_scratch_config(work)
    source_lines = (work / "scratch.cpp").read_text().splitlines()
    first_line = rot.definition_line("\n".join(source_lines), config.symbol or config.function)
    print(f"trace: {out}  metrics: {result['metrics']}")
    print(f"rule check: all {len(every)} picks in the unit re-derived")
    print(f"{'#':>4} {'line':>5} {'op':>4} {'site':4} {'cur':>3} {'out':>3} {'reg':4} {'live':24} flagged  source")
    for k, row in enumerate(rows):
        line = first_line + row["label"]
        text = source_lines[line - 1].strip()[:50] if 0 < line <= len(source_lines) else ""
        print(
            f"{k:4d} {line:5d} {row['opcode']:4d} {row['site']:4} {row['cursor_in']:3d}"
            f" {row['cursor_out']:3d} {row['register']:4} {','.join(row['live']):24}"
            f" {','.join(row['flagged'])}  {text}"
        )


if __name__ == "__main__":
    main()
