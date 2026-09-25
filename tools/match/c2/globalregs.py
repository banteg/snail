"""Trace VC6 C2's global (priority-based) register allocator for one Snail scratch.

Records every live range the allocator queues (priority, tie key, allowed
registers, preferences), the per-register cost table it builds when it picks a
register, and the register it picks. Live ranges are mapped to source lines
through the IL operands that name the same symbol, and each register is
compared with the register native uses at the structurally aligned
instructions. Diagnostic only; see global-allocation.md.

    uv run tools/match/c2/globalregs.py set_snail_weapon [--source overlay.cpp] [--out DIR]
"""

import argparse
import json
import re
import struct
import sys
import tempfile
from collections import Counter
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import trace as t

import rotation as rot

from snail import match as m

c2 = t.c2

# C2.DLL RVAs (image base 0x10700000), pinned by the profile's C2 SHA-256.
GLOBAL_ENTRY_HOOK = {"site": 0x583B2, "target": 0x2FB58, "return": False}
LOCAL_ENTRY_HOOK = {"site": 0x583C5, "target": 0x336F4, "return": False}
QUEUE_HOOKS = (
    {"site": 0x33607, "target": 0x31D21, "return": False},  # initial priority queue
    {"site": 0x2FED5, "target": 0x31D21, "return": False},  # requeue after a split
    {"site": 0x215BB, "target": 0x31D21, "return": False},  # requeue of split pieces
)
CHOOSE_HOOK = {"site": 0x2FE5F, "target": 0x32F7C, "return": True}
COSTS = 0x9D868  # int[9], per-register cost built by the chooser
RANGES = 0x9D88C  # live-range hash buckets by id & 0x3ff, chained through +0x2c
BIT_TEST = 0x251D
LR_WORDS = 18
SYM_WORDS = 8
MAX_PREFS = 8

RECORDER = r"""
static HANDLE glob_file;
typedef int (__fastcall *glob_bit_test_t)(void *, unsigned long);
static unsigned long glob_current, glob_function;
static void glob_write(void *data, unsigned long size)
{
    DWORD written;
    if (!WriteFile(glob_file, data, size, &written, 0) || written != size)
        ExitProcess(77);
}
static void glob_range(unsigned long kind, unsigned long *lr, unsigned char *base)
{
    unsigned long rec[4 + LR_WORDS + SYM_WORDS + 2 + 2 * MAX_PREFS], q, r, *pref;
    glob_bit_test_t bit_test = (glob_bit_test_t)(base + BIT_TEST);
    unsigned long *sym = (unsigned long *)lr[0];
    for (q = 0; q < sizeof(rec) / 4; ++q) rec[q] = 0;
    rec[0] = kind; rec[1] = glob_function; rec[2] = (unsigned long)lr; rec[3] = (unsigned long)base;
    for (q = 0; q < LR_WORDS; ++q) rec[4 + q] = lr[q];
    for (q = 0; q < SYM_WORDS; ++q) rec[4 + LR_WORDS + q] = sym ? sym[q] : 0;
    if (lr[8])
        for (r = 0; r <= 8; ++r)
            if (bit_test((void *)lr[8], r)) rec[4 + LR_WORDS + SYM_WORDS] |= 1 << r;
    for (pref = (unsigned long *)lr[13], q = 0; pref && q < MAX_PREFS; pref = (unsigned long *)pref[0], ++q) {
        rec[6 + LR_WORDS + SYM_WORDS + 2 * q] = pref[1] ? pref[1] - (unsigned long)base : 0;
        rec[7 + LR_WORDS + SYM_WORDS + 2 * q] = pref[2];
    }
    rec[5 + LR_WORDS + SYM_WORDS] = q;
    glob_write(rec, sizeof(rec));
}
/* Symbol references of every kind-1 operand, with the register if one is bound. */
static void glob_operands(unsigned long tag, unsigned long *function, unsigned char *base)
{
    unsigned long node, op, side, rec[6], bound;
    rec[0] = 5; rec[1] = (unsigned long)function; rec[5] = tag;
    for (node = *(unsigned long *)(*(unsigned long *)function[2] + 0x1c); node; node = *(unsigned long *)node) {
        if (!(*(unsigned char *)(node + 9) & 1)) continue;
        for (side = 0; side < 2; ++side)
            for (op = *(unsigned long *)(node + 0x18 + side * 4); op; op = *(unsigned long *)op) {
                if (*(unsigned char *)(op + 8) != 1) continue;
                bound = *(unsigned long *)(op + 0x18);
                rec[2] = *(unsigned short *)(node + 0x10);
                rec[3] = *(unsigned long *)(op + 0x14);
                rec[4] = bound ? bound - (unsigned long)base : 0;
                glob_write(rec, sizeof(rec));
            }
    }
}
static void glob_observe(unsigned long index, unsigned long phase, unsigned long *registers)
{
    unsigned char *base = (unsigned char *)targets[index] - offsets_copy[index];
    unsigned long rec[13], q;
    if (index == GLOBAL_INDEX || index == LOCAL_INDEX) {
        glob_function = registers[6];
        glob_operands(index == GLOBAL_INDEX ? 0 : 1, (unsigned long *)registers[6], base);
        return;
    }
    if (index == CHOOSE_INDEX && phase >= 100) {
        rec[0] = 3; rec[1] = glob_current; rec[2] = ((unsigned long *)glob_current)[4];
        rec[3] = rec[2] ? rec[2] - (unsigned long)base : 0;
        for (q = 0; q < 9; ++q) rec[4 + q] = ((unsigned long *)(base + COSTS))[q];
        glob_write(rec, sizeof(rec));
        return;
    }
    if (index == CHOOSE_INDEX) {
        unsigned long *set = *(unsigned long **)(registers[3] + 8), *chunk, bit, id, *lr;
        glob_current = registers[6];
        glob_range(2, (unsigned long *)registers[6], base);
        for (chunk = set ? (unsigned long *)set[0] : 0; chunk; chunk = (unsigned long *)chunk[1])
            for (bit = 0; bit < 32; ++bit) {
                if (!(chunk[2] & (1u << bit))) continue;
                id = chunk[0] + bit;
                for (lr = *(unsigned long **)(base + RANGES + (id & 0x3ff) * 4); lr; lr = (unsigned long *)lr[11])
                    if (lr[7] == id) { glob_range(4, lr, base); break; }
            }
        return;
    }
    glob_range(1, (unsigned long *)registers[6], base);
}
"""

# Record kinds: 1 queued, 2 chooser entry, 3 chooser result, 4 neighbour, 5 operand.
REGISTERS = rot.REGISTERS


def observer(profile, stock_source):
    hooks = profile["hooks"]
    [i for i, h in enumerate(hooks) if h["target"] == 0x31D21]
    choose = hooks.index(CHOOSE_HOOK)
    defines = {
        "LR_WORDS": LR_WORDS,
        "SYM_WORDS": SYM_WORDS,
        "MAX_PREFS": MAX_PREFS,
        "BIT_TEST": BIT_TEST,
        "COSTS": COSTS,
        "RANGES": RANGES,
        "CHOOSE_INDEX": choose,
        "GLOBAL_INDEX": hooks.index(GLOBAL_ENTRY_HOOK),
        "LOCAL_INDEX": hooks.index(LOCAL_ENTRY_HOOK),
    }
    offsets = ",".join(str(h["target"]) for h in hooks)
    header = "".join(f"#define {k} {v}\n" for k, v in defines.items())
    header += f"static unsigned long offsets_copy[] = {{{offsets}}};\n"
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
    source = source.replace(anchors[3], header + RECORDER + anchors[3])
    # Every hook is handled here; the stock node snapshots are never written.
    source = source.replace(
        anchors[0],
        anchors[0] + "    { glob_observe(phase % 100, phase, registers); return; }\n",
    )
    source = source.replace(
        anchors[1],
        '    glob_file = CreateFileA("global.bin", GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);\n'
        "    if (glob_file == INVALID_HANDLE_VALUE) ExitProcess(76);\n" + anchors[1],
    )
    return source.replace(anchors[2], "    CloseHandle(glob_file);\n" + anchors[2])


def run_observer(scratch, out):
    stock_profile, stock_source = c2.load_profile, c2.observer_source
    profile = stock_profile()
    hooks = [GLOBAL_ENTRY_HOOK, LOCAL_ENTRY_HOOK, *QUEUE_HOOKS, CHOOSE_HOOK]
    profile = dict(profile, name=profile["name"] + "-global", hooks=hooks)
    c2.load_profile = lambda: profile
    c2.observer_source = lambda p: observer(p, stock_source)
    try:
        # The preserving COFF/metric checks run before the (deliberately empty)
        # stock snapshot stream is decoded, so only that final step may fail.
        t.trace(scratch, out)
    except ValueError as error:
        if "Empty C2 trace" not in str(error):
            raise
    finally:
        c2.load_profile, c2.observer_source = stock_profile, stock_source
    return (out / "observed/global.bin").read_bytes()


RANGE_WORDS = 4 + LR_WORDS + SYM_WORDS + 2 + 2 * MAX_PREFS


def s32(value):
    return value - (1 << 32) if value & 0x80000000 else value


def decode(data):
    rows, at = [], 0
    while at < len(data):
        (kind,) = struct.unpack_from("<I", data, at)
        if kind in (1, 2, 4):
            w = struct.unpack_from(f"<{RANGE_WORDS}I", data, at)
            at += RANGE_WORDS * 4
            lr = w[4 : 4 + LR_WORDS]
            sym = w[4 + LR_WORDS : 4 + LR_WORDS + SYM_WORDS]
            allowed = w[4 + LR_WORDS + SYM_WORDS]
            count = w[5 + LR_WORDS + SYM_WORDS]
            prefs = w[6 + LR_WORDS + SYM_WORDS :]
            rows.append(
                {
                    "kind": {1: "queued", 2: "choose", 4: "neighbour"}[kind],
                    "function": w[1],
                    "range": w[2],
                    "symbol": lr[0],
                    "symbol_class": sym[1] & 0xFF,
                    "symbol_words": list(sym),
                    "id": lr[7],
                    "priority": s32(lr[3]),
                    "tie": lr[16],
                    "benefit": s32(lr[15]),
                    "size": lr[9],
                    "flags": [(lr[1] >> 8) & 0xFF, (lr[1] >> 16) & 0xFF],
                    "allowed": [
                        REGISTERS[r] for r in sorted(REGISTERS) if allowed & (1 << r)
                    ],
                    "preferences": [
                        (rot.register_of(prefs[2 * q]), prefs[2 * q + 1])
                        for q in range(count)
                    ],
                    "words": list(lr),
                }
            )
        elif kind == 5:
            w = struct.unpack_from("<6I", data, at)
            at += 6 * 4
            rows.append(
                {
                    "kind": "operand",
                    "function": w[1],
                    "label": w[2],
                    "symbol": w[3],
                    "register": rot.register_of(w[4]),
                    "stage": "global" if w[5] == 0 else "local",
                }
            )
        elif kind == 3:
            w = struct.unpack_from("<13I", data, at)
            at += 13 * 4
            rows.append(
                {
                    "kind": "chosen",
                    "range": w[1],
                    "register": rot.register_of(w[3]),
                    "costs": {REGISTERS[r]: s32(w[4 + r]) for r in sorted(REGISTERS)},
                }
            )
        else:
            raise ValueError(f"Unknown global record {kind}")
    return rows


REGISTER_TOKEN = re.compile(r"\b(?:e?[abcd]x|[abcd][lh]|e?[sd]i|e?bp)\b")


def widen(token):
    if token in ("si", "di", "bp"):
        return "e" + token
    return rot.widen(token) if not token.startswith("e") else token


def symbol_uses(rows, stage):
    """symbol -> {line labels} and symbol -> Counter(register) at one allocator boundary."""
    lines, registers = {}, {}
    for row in rows:
        if row["kind"] != "operand" or row["stage"] != stage:
            continue
        lines.setdefault(row["symbol"], set()).add(row["label"])
        if row["register"]:
            registers.setdefault(row["symbol"], Counter())[row["register"]] += 1
    return lines, registers


def ranges(rows):
    """Queued live ranges in the order the chooser saw them, with their results."""
    queued, order, result = {}, [], {}
    for row in rows:
        if row["kind"] == "queued":
            queued.setdefault(row["range"], row)
        elif row["kind"] == "choose":
            order.append(dict(row, neighbours=[]))
        elif row["kind"] == "neighbour":
            order[-1]["neighbours"].append(row)
        elif row["kind"] == "chosen":
            result[row["range"]] = row
    chosen = []
    for row in order:
        row = dict(
            row, **{k: v for k, v in result[row["range"]].items() if k != "kind"}
        )
        chosen.append(row)
    seen = {row["range"] for row in chosen}
    rest = [row for key, row in queued.items() if key not in seen]
    return chosen, rest


ORDER = ("eax", "ecx", "edx", "esi", "edi", "ebx", "ebp")


def predict(row):
    """Re-derive the chooser's cost table and pick (C2+0x32f7c, see global-allocation.md)."""
    costs = dict.fromkeys(REGISTERS.values(), 0)
    for other in row["neighbours"]:
        if other["benefit"] <= 0:
            continue
        for register, weight in other["preferences"]:
            if register in other["allowed"]:
                costs[register] += weight
        if len(other["allowed"]) == 1:
            costs[other["allowed"][0]] += 100 * other["benefit"]
    for register, weight in row["preferences"]:
        costs[register] -= weight
    choice = None
    for register in ORDER:
        if register in row["allowed"] and (
            choice is None or costs[register] < costs[choice]
        ):
            choice = register
    return costs, choice


def native_map(config, work, object_path, first_line):
    """(source line, candidate register) -> Counter(native register) over aligned instructions."""
    rows = rot.native_registers(config, work, object_path)
    result = {}
    for ins in rows:
        if ins["target_text"] is None:
            continue
        ours = REGISTER_TOKEN.findall(ins["text"])
        theirs = REGISTER_TOKEN.findall(ins["target_text"])
        if len(ours) != len(theirs):
            continue
        for line in ins["lines"]:
            for a, b in zip(ours, theirs):
                result.setdefault((line, widen(a)), Counter())[widen(b)] += 1
    return result


def describe(symbol, lines_of, first_line, source_lines):
    labels = sorted(label for label in lines_of.get(symbol, ()) if label)
    if not labels:
        return [], ""
    lines = [first_line + label for label in labels]
    text = (
        source_lines[lines[0] - 1].strip() if 0 < lines[0] <= len(source_lines) else ""
    )
    return lines, text


def report(chosen, rest, lines_of, final_regs, natives, first_line, source_lines):
    print(
        f"{'#':>3} {'id':>3} {'cls':>3} {'prio':>5} {'tie':>4} {'allowed':24} {'costs (nonzero)':28}"
        f" {'got':4} {'final':12} {'native':12}  first use"
    )

    def native_of(symbol, register_counts):
        lines, _ = describe(symbol, lines_of, first_line, source_lines)
        found = Counter()
        for line in lines:
            for register in register_counts:
                found.update(natives.get((line, register), Counter()))
        return ",".join(f"{r}:{n}" for r, n in found.most_common(3)) or "-"

    for k, row in enumerate(chosen):
        lines, text = describe(row["symbol"], lines_of, first_line, source_lines)
        costs = " ".join(f"{r}{v:+d}" for r, v in row["costs"].items() if v)
        final = final_regs.get(row["symbol"], Counter())
        print(
            f"{k:3d} {row['id']:3d} {row['symbol_class']:3d} {row['priority']:5d} {row['tie']:4d}"
            f" {','.join(row['allowed']):24} {costs[:28]:28} {row['register'] or '-':4}"
            f" {','.join(final):12} {native_of(row['symbol'], final or [row['register']])[:12]:12}"
            f"  L{lines[0] if lines else '?'} {text[:50]}"
        )
    unassigned = [row for row in rest if row["symbol_class"] != 13]
    if unassigned:
        print(
            "\nqueued but not coloured by the chooser (spilled, or coloured on another path):"
        )
        for row in unassigned:
            lines, text = describe(row["symbol"], lines_of, first_line, source_lines)
            final = final_regs.get(row["symbol"], Counter())
            print(
                f"    id {row['id']:3d} cls {row['symbol_class']} prio {row['priority']:5d} tie {row['tie']:4d}"
                f" final {','.join(final) or 'memory'}  L{lines[0] if lines else '?'} {text[:50]}"
            )


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("scratch", help="scratch name or directory")
    parser.add_argument(
        "--source", type=Path, help="overlay source replacing scratch.cpp"
    )
    parser.add_argument(
        "--out", type=Path, help="new output directory (default: a temporary one)"
    )
    parser.add_argument(
        "--as-msvc65",
        action="store_true",
        help="trace a scratch pinned to another compiler with the msvc6.5 backend (approximation)",
    )
    args = parser.parse_args()
    scratch = Path(args.scratch)
    if not scratch.is_dir():
        scratch = m.DEFAULT_MATCH_ROOT / "scratches" / args.scratch
    out = args.out or Path(tempfile.mkdtemp(prefix="c2glob-")) / "trace"
    work = rot.prepare(scratch, args.source, out.parent / (out.name + "-input"))
    if args.as_msvc65:
        conf = work / "scratch.conf"
        conf.write_text(
            re.sub(r"^COMPILER=.*\n", "", conf.read_text(), flags=re.MULTILINE)
        )
    rows = decode(run_observer(work, out))
    functions = list(
        dict.fromkeys(row["function"] for row in rows if "function" in row)
    )
    if len(functions) != 1:
        raise ValueError(f"Expected one allocating function, saw {len(functions)}")
    lines_of, _ = symbol_uses(rows, "global")
    _, final_regs = symbol_uses(rows, "local")
    config = m.load_scratch_config(work)
    source_text = (work / "scratch.cpp").read_text()
    first_line = rot.definition_line(source_text, config.symbol or config.function)
    object_path = m.compile_scratch(config)
    metrics = t.metrics(config, object_path)
    natives = native_map(config, work, object_path, first_line)
    chosen, rest = ranges(rows)
    for row in chosen:
        costs, choice = predict(row)
        observed = {r: v for r, v in row["costs"].items() if r in costs}
        if choice != row["register"] or any(costs[r] != observed[r] for r in observed):
            raise ValueError(
                f"Chooser rule mismatch for range {row['id']}: {costs} {choice} vs {row}"
            )
    (out / "global.json").write_text(
        json.dumps({"chosen": chosen, "rest": rest}, indent=1) + "\n"
    )
    print(f"trace: {out}  metrics: {json.dumps(metrics)}")
    report(
        chosen,
        rest,
        lines_of,
        final_regs,
        natives,
        first_line,
        source_text.splitlines(),
    )


if __name__ == "__main__":
    main()
