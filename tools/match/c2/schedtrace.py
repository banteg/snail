"""Trace VC6 C2's /G5 list scheduler for one Snail scratch (diagnostic only).

Hooks the scheduler (see scheduler.md) through Crimson's preserving observer.
For every scheduling window it records the input IL order, each node's
dependency edges, latency, height and priority, and for every cycle the ready
list and the node chosen for each issue slot. The script re-derives every pick
from the documented rule and prints any disagreement.

    uv run tools/match/c2/schedtrace.py firework_shoot [--source overlay.cpp] [--line N]

It prints a one-line summary of every window: size, source lines, whether
the scheduler reordered it, and whether our emitted order differs from the
native order of the same instructions. --line N (a physical scratch.cpp line,
repeatable) or --all prints the full trace of the selected windows:

  - the input IL order, with latency, height, priority, memory flags
    (R reads, W writes, B barrier, * critical path) and successor edges
    (raw/war/waw register, load/mwar/store memory, order barrier, /latency,
    brkN breakable by displacement);
  - memory operands with their alias id: @fNNN is a field record, @cNNN a
    bare class that conflicts with every field of its object;
  - per cycle, the U/V pick, the ready list in priority order (#seq@cycle
    when not yet ready) and why each higher node was passed over;
  - our emitted order next to native's order of the same instructions.

The decoded trace is kept in <out>/schedule.json.
"""

import argparse
import difflib
import json
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

# C2.DLL RVAs (image base 0x10700000), pinned by the profile's C2 SHA-256.
FUNCTION_ENTRY_HOOK = rot.FUNCTION_ENTRY_HOOK
FINAL_HOOK = rot.FINAL_HOOK
GRAPH_HOOK = {
    "site": 0x375A2,
    "target": 0x3AF90,
    "return": False,
}  # sched_list_schedule(graph)
CYCLE_HOOK = {
    "site": 0x3B054,
    "target": 0x3B176,
    "return": False,
}  # sched_select_cycle(cycle)
PICK_HOOK = {
    "site": 0x3B252,
    "target": 0x3B53E,
    "return": False,
}  # sched_ready_remove(node)
READY_HEAD = 0x9F278
UNITS = 0x991D8  # per unit: busy cycles (dword) at +0, 12-byte stride
CUR_FUNC_SYM = 0xAC378
REGISTER_SYMBOLS = 0xAC730
REGISTER_SIZE = 0x54

MAX_OPS = 8
OP_RAW = 12
# raw words, base/index registers, symbol id/offset/class, name, alias record
OP_WORDS = OP_RAW + 2 + 3 + 6 + 4
NODE_HEAD = 14
MAX_EDGES = 1024
MAX_READY = 128
FMUL_BLOCK = 0xAC2D8  # cycles before the next fmul may issue
ALIAS_CLASS_COUNT = 0x9D670  # ids at or above it are field records
ALIAS_RECORDS = 0x9D6BC  # field records: (primary class, bit, mask)

RECORDER = r"""
static HANDLE sched_file;
static void sched_write(void *data, unsigned long size)
{
    DWORD written;
    if (!WriteFile(sched_file, data, size, &written, 0) || written != size)
        ExitProcess(75);
}
/* c2_symbol -> id, offset, class, then its front-end name (if any). */
static void sched_symbol(unsigned long *out, unsigned long symbol)
{
    unsigned long fe, j;
    char *name, *dst = (char *)(out + 3);
    for (j = 0; j < 9; ++j) out[j] = 0;
    if (!symbol) return;
    out[0] = *(unsigned long *)(symbol + 0x1c);
    out[1] = *(unsigned long *)(symbol + 0x24);
    out[2] = *(unsigned char *)(symbol + 4);
    fe = *(unsigned long *)symbol;
    if (!fe) return;
    name = *(char **)(fe + 0x18);
    if (!name) return;
    for (j = 0; j < 23 && name[j]; ++j) dst[j] = name[j];
}
static unsigned char *sched_base;
static void sched_operands(unsigned long op)
{
    unsigned long rec[1 + MAX_OPS * OP_WORDS], k, j, kind, at, ref;
    for (j = 0; j < sizeof(rec) / 4; ++j) rec[j] = 0;
    for (k = 0; op && k < MAX_OPS; ++k, op = *(unsigned long *)op) {
        at = 1 + k * OP_WORDS;
        kind = *(unsigned char *)(op + 8);
        for (j = 0; j < (kind == 5 || kind == 6 ? OP_RAW : 7); ++j) rec[at + j] = ((unsigned long *)op)[j];
        if (kind == 5 || kind == 6) {
            ref = *(unsigned long *)(op + 0x28);
            rec[at + OP_RAW] = ref ? *(unsigned long *)(ref + 0x18) : 0;
            ref = *(unsigned long *)(op + 0x2c);
            rec[at + OP_RAW + 1] = ref ? *(unsigned long *)(ref + 0x18) : 0;
        }
        if (kind == 1 || kind == 2 || kind == 3 || kind == 5 || kind == 6)
            sched_symbol(rec + at + OP_RAW + 2, *(unsigned long *)(op + 0x14));
        if (kind == 6) {
            unsigned long count = *(unsigned long *)(sched_base + ALIAS_CLASS_COUNT), id = rec[at + 7];
            unsigned long *record = id >= count
                ? (unsigned long *)(*(unsigned long *)(sched_base + ALIAS_RECORDS) + (id - count) * 12) : 0;
            rec[at + OP_WORDS - 4] = count;
            rec[at + OP_WORDS - 3] = record ? record[0] : id;
            rec[at + OP_WORDS - 2] = record ? record[1] : 0;
            rec[at + OP_WORDS - 1] = record ? record[2] : 0;
        }
    }
    rec[0] = k;
    sched_write(rec, sizeof(rec));
}
static void sched_graph(unsigned long *graph, unsigned char *base)
{
    static unsigned long edges[1 + 3 * MAX_EDGES];
    unsigned long head[4], rec[NODE_HEAD], node, tuple, edge, k, j;
    unsigned long name[16], fe;
    char *text;
    for (j = 0; j < 16; ++j) name[j] = 0;
    fe = *(unsigned long *)(base + CUR_FUNC_SYM);
    text = fe ? *(char **)(fe + 0x18) : 0;
    for (j = 0; text && j < 63 && text[j]; ++j) ((char *)name)[j] = text[j];
    for (k = 0, node = graph[0]; node; node = *(unsigned long *)node) {
        ++k;
        if (node == graph[1]) break;
    }
    head[0] = 1; head[1] = k; head[2] = (unsigned long)base; head[3] = 0;
    sched_write(head, sizeof(head));
    sched_write(name, sizeof(name));
    for (node = graph[0]; node; node = *(unsigned long *)node) {
        unsigned char *n = (unsigned char *)node;
        tuple = *(unsigned long *)(n + 0x1c);
        for (j = 0; j < NODE_HEAD; ++j) rec[j] = 0;
        rec[0] = node; rec[1] = *(unsigned short *)(n + 0x36); rec[2] = tuple;
        rec[3] = *(unsigned short *)(n + 0x20) | (unsigned long)*(unsigned short *)(n + 0x22) << 16;
        rec[4] = *(unsigned short *)(n + 0x24);
        rec[5] = *(unsigned long *)(n + 0x28); rec[6] = *(unsigned long *)(n + 0x2c);
        rec[7] = *(unsigned long *)(n + 0x30); rec[8] = *(unsigned short *)(n + 0x34);
        rec[9] = n[0x38] | (unsigned long)n[0x39] << 8 | (unsigned long)n[0x3a] << 16;
        if (tuple) {
            rec[10] = *(unsigned long *)(tuple + 4);
            rec[11] = *(unsigned char *)(tuple + 8) | (unsigned long)*(unsigned char *)(tuple + 9) << 8
                | (unsigned long)*(unsigned short *)(tuple + 0xa) << 16;
            rec[12] = *(unsigned short *)(tuple + 0x10);
            rec[13] = *(unsigned long *)(tuple + 0x14);
        }
        sched_write(rec, sizeof(rec));
        sched_operands(tuple && (*(unsigned char *)(tuple + 9) & 1) ? *(unsigned long *)(tuple + 0x18) : 0);
        sched_operands(tuple && (*(unsigned char *)(tuple + 9) & 1) ? *(unsigned long *)(tuple + 0x1c) : 0);
        for (k = 0, edge = *(unsigned long *)(n + 0xc); edge && k < MAX_EDGES; edge = *(unsigned long *)edge, ++k) {
            edges[1 + 3 * k] = *(unsigned long *)(edge + 0xc);
            edges[2 + 3 * k] = *(unsigned long *)(edge + 0x10);
            edges[3 + 3 * k] = *(unsigned short *)(edge + 0x14) | (unsigned long)*(unsigned char *)(edge + 0x16) << 16;
        }
        if (edge) ExitProcess(74);
        edges[0] = k;
        sched_write(edges, (1 + 3 * k) * 4);
        if (node == graph[1]) break;
    }
}
static void sched_observe(unsigned long index, unsigned long *registers)
{
    unsigned char *base = (unsigned char *)targets[index] - offsets_copy[index];
    unsigned long rec[4 + 2 * MAX_READY], node, k, u;
    sched_base = base;
    if (index == GRAPH_INDEX) { sched_graph((unsigned long *)registers[6], base); return; }
    if (index == CYCLE_INDEX) {
        rec[0] = 2; rec[1] = registers[6];
        for (u = 0; u < 4; ++u) rec[2 + u] = *(unsigned long *)(base + UNITS + 12 * u);
        rec[6] = *(unsigned long *)(base + FMUL_BLOCK);
        sched_write(rec, 7 * 4);
        return;
    }
    for (k = 0; k < sizeof(rec) / 4; ++k) rec[k] = 0;
    rec[0] = 3; rec[1] = registers[6]; rec[3] = registers[4] & 0xffff;
    for (k = 0, node = *(unsigned long *)(base + READY_HEAD); node && k < MAX_READY; node = *(unsigned long *)(node + 0x10), ++k) {
        rec[4 + 2 * k] = node;
        rec[5 + 2 * k] = *(unsigned long *)(node + 0x30);
    }
    if (node) ExitProcess(73);
    rec[2] = k;
    sched_write(rec, sizeof(rec));
}
"""


def observer(profile, stock_source):
    indices = {"GRAPH_INDEX": 2, "CYCLE_INDEX": 3, "PICK_INDEX": 4}
    defines = {
        **indices,
        "READY_HEAD": READY_HEAD,
        "UNITS": UNITS,
        "FMUL_BLOCK": FMUL_BLOCK,
        "ALIAS_CLASS_COUNT": ALIAS_CLASS_COUNT,
        "ALIAS_RECORDS": ALIAS_RECORDS,
        "CUR_FUNC_SYM": CUR_FUNC_SYM,
        "MAX_OPS": MAX_OPS,
        "OP_RAW": OP_RAW,
        "OP_WORDS": OP_WORDS,
        "NODE_HEAD": NODE_HEAD,
        "MAX_EDGES": MAX_EDGES,
        "MAX_READY": MAX_READY,
    }
    header = "".join(f"#define {k} {v}\n" for k, v in defines.items())
    offsets = ",".join(str(h["target"]) for h in profile["hooks"])
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
    # Long operand chains exceed the stock 16-entry snapshot; truncate instead.
    source = source.replace("if(op) ExitProcess(98);", "")
    source = source.replace(anchors[3], header + RECORDER + anchors[3])
    source = source.replace(
        anchors[0],
        anchors[0]
        + "    if (phase % 100 >= GRAPH_INDEX) { sched_observe(phase % 100, registers); return; }\n",
    )
    source = source.replace(
        anchors[1],
        '    sched_file = CreateFileA("sched.bin", GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);\n'
        "    if (sched_file == INVALID_HANDLE_VALUE) ExitProcess(72);\n" + anchors[1],
    )
    return source.replace(anchors[2], "    CloseHandle(sched_file);\n" + anchors[2])


def run_observer(scratch, out):
    """Preserving run: whole-COFF identity and matcher metrics are checked by the adapter."""
    stock_profile, stock_source = c2.load_profile, c2.observer_source
    profile = stock_profile()
    hooks = [FUNCTION_ENTRY_HOOK, FINAL_HOOK, GRAPH_HOOK, CYCLE_HOOK, PICK_HOOK]
    profile = dict(profile, name=profile["name"] + "-schedule", hooks=hooks)
    c2.load_profile = lambda: profile
    c2.observer_source = lambda p: observer(p, stock_source)
    try:
        result, events = t.trace(scratch, out)
    finally:
        c2.load_profile, c2.observer_source = stock_profile, stock_source
    return result, events, (out / "observed/sched.bin").read_bytes()


# ---------------------------------------------------------------- decoding

# Mnemonics of C2 opcodes 0..0xe0 (enum c2_opcode, X86_ prefix removed).
OPCODE_TEXT = """
p_first mov arpl bound enter esc imul int ret xchg in out pop push call p_jcc jmp
lds lea les lar lsl jcxz loop loopnz loopz lgdt lidt sgdt sidt dec div idiv inc mul
neg not rcl rcr rol ror sar shl shr adc add and cmp or sbb sub test xor cmps ins
lods movs outs scas stos xlat lldt lmsw ltr sldt smsw str verr verw fadd fmul fsub
fsubr fdiv fdivr faddp fmulp fsubp fsubrp fdivp fdivrp fiadd ficom ficomp fidiv
fidivr fild fimul fisub fisubr fist fistp fcom fcomp fcompp fxch fld ffree fst fstp
fbld fldcw fldenv frstor fsave fbstp fstcw fstenv fstsw fnstcw fnstsw fnsave fnstenv
fninit fnclex fndisi fneni f2xm1 fabs fchs fclex fdecstp fdisi feni fincstp finit
p_fldt fldz fldpi fldl2e fldl2t fldlg2 fldln2 fnop fpatan fprem fptan frndint fscale
fsetpm fsqrt ftst fwait fxam fxtract fyl2x fyl2xp1 p_fsttp fld1 aaa aad aam aas cbw
clc cld cli clts cmc cwd daa das hlt p_imul3 into iret lahf leave p_ljcc nop popa
popf pusha pushf sahf p_seg stc std sti wait p_emit rep lock repnz repz p_epop
p_epush p_data p_rpush p_scc lss lfs lgs p_imul2 movzx p_movzxw movsx p_movsxw
p_jmp3216 p_jmp1632 bsf bsr shld shrd bt bts btr btc p_movsr fucom fucomp fucompp
fprem1 fsincos fsin fcos bswap xadd cmpxchg invd wbinvd invlpg cwde cdq
"""
OPCODES = OPCODE_TEXT.split()
IL_NAMES = {
    0x162: "fround",
    0x1AE: "label",
    0x1B4: "prolog_end",
    0x1B5: "epilog",
    0x1BC: "dead_label",
}
REGISTERS = (
    "?", "eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi",
    "ax", "cx", "dx", "bx", "sp", "bp", "si", "di",
    "al", "cl", "dl", "bl", "ah", "ch", "dh", "bh",
)  # fmt: skip
FLAGS_REGISTER = 0x42
FXCH, FMUL, JCC, JCC_113, FROUND = 0x5F, 0x46, 0x0F, 0x113, 0x162
# P5 pairing codes from the /G5 latency table (C2+0xa0dd8, 12 bytes per opcode:
# latency, busy cycles, code). The code's low byte is the unit class.
UV = {
    1,
    0xC,
    0xD,
    0x12,
    0x1E,
    0x21,
    0x2D,
    0x2E,
    0x2F,
    0x30,
    0x32,
    0x34,
    0xA9,
    0xB9,
    0xBA,
}
PU = {0x2C, 0x31}
PV = {JCC, JCC_113}
FP_PAIRABLE = {
    0x45,
    0x46,
    0x47,
    0x48,
    0x49,
    0x4A,
    0x4B,
    0x4C,
    0x4D,
    0x4E,
    0x4F,
    0x50,
    0x5C,
    0x5D,
    0x60,
    0x76,
    0x77,
    0x8D,
    0xD1,
    0xD2,
    0xD3,
}
# Edge kinds (edge +0x10), see scheduler.md.
EDGE_KINDS = (
    (0x1, "raw"),
    (0x2, "war"),
    (0x4, "waw"),
    (0x20, "load"),
    (0x40, "mwar"),
    (0x80, "store"),
    (0x80000, "order"),
)


def read_words(data, at, count):
    return list(struct.unpack_from(f"<{count}I", data, at)), at + count * 4


def cstring(words):
    raw = struct.pack(f"<{len(words)}I", *words)
    return raw.split(b"\0", 1)[0].decode("latin-1")


def signed(value):
    return value - (1 << 32) if value & 0x80000000 else value


def register_index(address, base):
    offset = address - base - REGISTER_SYMBOLS if address else -1
    if offset < 0 or offset % REGISTER_SIZE or offset // REGISTER_SIZE > 0x4A:
        return None
    return offset // REGISTER_SIZE


def decode_operands(data, at, base):
    words, at = read_words(data, at, 1 + MAX_OPS * OP_WORDS)
    operands = []
    for k in range(words[0]):
        w = words[1 + k * OP_WORDS : 1 + (k + 1) * OP_WORDS]
        extra = w[OP_RAW + 2 :]
        operands.append(
            {
                "kind": w[2] & 0xFF,
                "mode": w[1],
                "type": w[2] >> 16,
                "flags10": w[4] & 0xFF,
                "register": register_index(w[6], base),
                "value": signed(w[6]),
                "alias": w[7],
                "disp": signed(w[9]),
                "base": register_index(w[OP_RAW], base),
                "index": register_index(w[OP_RAW + 1], base),
                "alias_classes": w[OP_WORDS - 4],
                "alias_primary": w[OP_WORDS - 3],
                "alias_bit": w[OP_WORDS - 2],
                "alias_mask": w[OP_WORDS - 1],
                "symbol": {
                    "id": extra[0],
                    "offset": signed(extra[1]),
                    "class": extra[2],
                    "name": cstring(extra[3:9]),
                },
            }
        )
    return operands, at


def decode(data):
    """Windows in schedule order: nodes (input order), edges and per-cycle picks."""
    windows, at, window = [], 0, None
    while at < len(data):
        (tag,) = struct.unpack_from("<I", data, at)
        if tag == 1:
            head, at = read_words(data, at, 4)
            name, at = read_words(data, at, 16)
            count, base = head[1], head[2]
            window = {"function": cstring(name), "nodes": [], "cycles": []}
            windows.append(window)
            for _ in range(count):
                w, at = read_words(data, at, NODE_HEAD)
                src, at = decode_operands(data, at, base)
                dst, at = decode_operands(data, at, base)
                (count_edges,) = struct.unpack_from("<I", data, at)
                e, at = read_words(data, at, 1 + 3 * count_edges)
                edges = [
                    {"to": e[1 + 3 * k], "kind": e[2 + 3 * k], "latency": e[3 + 3 * k] & 0xFFFF, "code": (e[3 + 3 * k] >> 16) & 0x1F}
                    for k in range(e[0])
                ]  # fmt: skip
                window["nodes"].append(
                    {
                        "id": w[0], "seq": w[1], "tuple": w[2],
                        "preds": w[3] & 0xFFFF, "succs": w[3] >> 16, "breakable": w[4],
                        "priority": w[5], "dynamic": w[6], "earliest": w[7], "height": w[8],
                        "latency": w[9] & 0xFF, "unit": (w[9] >> 8) & 7,
                        "critical": bool(w[9] & 0x4000), "feeder": bool(w[9] & 0x8000),
                        "reads": bool(w[9] & 0x10000), "writes": bool(w[9] & 0x20000),
                        "barrier": bool(w[9] & 0x80000),
                        "opcode": w[10], "kind": w[11] & 0xFF, "real": bool(w[11] & 0x100),
                        "type": w[11] >> 16, "label": w[12],
                        "src": src, "dst": dst, "edges": edges,
                    }
                )  # fmt: skip
        elif tag == 2:
            w, at = read_words(data, at, 7)
            window["cycles"].append(
                {
                    "cycle": w[1],
                    "busy": [signed(x) for x in w[2:6]],
                    "fmul_block": signed(w[6]),
                    "picks": [],
                }
            )
        elif tag == 3:
            w, at = read_words(data, at, 4 + 2 * MAX_READY)
            ready = [(w[4 + 2 * k], w[5 + 2 * k]) for k in range(w[2])]
            window["cycles"][-1]["picks"].append(
                {"node": w[1], "unit": w[3], "ready": ready}
            )
        else:
            raise ValueError(f"Unknown schedule record {tag} at {at}")
    return windows


# ---------------------------------------------------------------- formatting


def mnemonic(node):
    op = node["opcode"]
    if node["tuple"] == 0:
        return "entry" if node["seq"] == 0 else "exit"
    if op < len(OPCODES):
        return OPCODES[op]
    return IL_NAMES.get(op, f"il{op:#x}")


def register_name(index):
    if index is None:
        return "?"
    if index < len(REGISTERS):
        return REGISTERS[index]
    if 31 <= index <= 38:
        return f"st{index - 31}"
    return "flags" if index == FLAGS_REGISTER else f"r{index}"


def symbol_name(operand):
    sym = operand["symbol"]
    return sym["name"] or f"t{sym['id']}"


def address(operand):
    parts = []
    if operand["kind"] == 6 and operand["mode"] == 0x150 or operand["symbol"]["name"]:
        parts.append(symbol_name(operand))
    if operand["base"] is not None:
        parts.append(register_name(operand["base"]))
    if operand["index"] is not None:
        scale = 1 << (operand["flags10"] & 0xF)
        parts.append(
            register_name(operand["index"]) + (f"*{scale}" if scale > 1 else "")
        )
    text = "+".join(parts)
    if operand["disp"] or not text:
        text += f"{operand['disp']:+#x}" if text else f"{operand['disp']:#x}"
    return f"[{text}]"


def operand_text(operand):
    kind = operand["kind"]
    if kind == 1:
        return register_name(operand["register"])
    if kind == 2:
        return f"[{symbol_name(operand)}]"
    if kind == 3:
        return f"&{symbol_name(operand)}"
    if kind == 5:
        return address(operand)
    if kind == 6:
        # Alias class: a field record (f) is disjoint from other fields of its
        # class; a bare class (c) conflicts with every field of that class.
        alias = operand["alias"]
        if not alias:
            return address(operand)
        tag = "f" if alias >= operand["alias_classes"] else "c"
        return f"{address(operand)}@{tag}{alias:x}"
    if kind in (7, 8):
        return (
            f"{operand['value']:#x}"
            if abs(operand["value"]) > 9
            else str(operand["value"])
        )
    return {9: "fconst", 10: "{regs}", 11: "{mem}"}.get(kind, f"k{kind}")


def hidden(node, operand):
    """Implicit stack-pointer and flags operands that clutter the text."""
    kind, reg = operand["kind"], operand.get("register")
    if kind == 1 and reg == FLAGS_REGISTER:
        return True
    return (
        kind == 1
        and reg == 5
        and mnemonic(node) in ("push", "pop", "call", "p_epush", "p_epop")
    )


def instruction(node):
    text = mnemonic(node)
    if not node["real"]:
        return text
    dst = [operand_text(o) for o in node["dst"] if not hidden(node, o)]
    src = [operand_text(o) for o in node["src"] if not hidden(node, o)]
    if dst and src:
        return f"{text} {', '.join(dst)} <- {', '.join(src)}"
    return f"{text} {', '.join(dst + src)}".rstrip()


def edge_text(edge):
    names = [name for bit, name in EDGE_KINDS if edge["kind"] & bit]
    text = "+".join(names) or f"{edge['kind']:#x}"
    if edge["latency"]:
        text += f"/{edge['latency']}"
    if edge["code"]:
        text += f" brk{edge['code']:#x}"
    return text


# ---------------------------------------------------------------- the P5 rule


def pair_code(node):
    op = node["opcode"]
    if node["tuple"] == 0 or op >= 0x144:
        return 0x300
    if op in UV:
        return 0
    if op in PU:
        return 0x100
    if op in PV:
        return 0x200
    if op in FP_PAIRABLE:
        return 0x102
    if op == FXCH:
        return 0x202
    return 0x300


def fp_typed(node):
    return (node["type"] & 0xF000) == 0x4000


def can_pair(first, second):
    """sched_can_pair_uv (C2+0x3b597): may `second` issue in V beside `first` in U?"""
    if second["tuple"] == 0:
        return False
    if fp_typed(first):
        return pair_code(first) == 0x102 and second["opcode"] == FXCH
    return pair_code(first) in (0, 0x100) and pair_code(second) in (0, 0x200)


class Model:
    """Replays sched_list_schedule (C2+0x3af90) on the recorded graph."""

    def __init__(self, window, previous_tail):
        self.nodes = {n["id"]: n for n in window["nodes"]}
        self.order = window["nodes"]
        self.exit = self.order[-1]["id"]
        self.remaining = {n["id"]: n["preds"] for n in self.order}
        self.breakable = {n["id"]: n["breakable"] for n in self.order}
        self.preds = {n["id"]: [] for n in self.order}
        for n in self.order:
            for e in n["edges"]:
                self.preds[e["to"]].append((n["id"], e))
        self.scheduled = {self.order[0]["id"]}
        for e in self.order[0]["edges"]:
            self.remaining[e["to"]] -= 1
        self.tail = previous_tail or (None, None)

    def ready(self, node_id):
        return (
            node_id not in self.scheduled
            and self.remaining[node_id] == self.breakable[node_id]
        )

    def defer(self, node, cycle, earliest):
        """sched_defer_for_bypassed_pred: wait for a pred rather than break its edge."""
        if not self.remaining[node["id"]]:
            return None
        for pred, e in self.preds[node["id"]]:
            if (
                e["code"] >= 0x10
                and self.ready(pred)
                and earliest.get(pred, 1 << 30) <= cycle + 1
            ):
                return pred
        return None

    def fxch_hold(self, node, cycle, ready, busy):
        """sched_fxch_hold: after an fxch, keep integer work out of the FP slot."""
        last, before = self.tail
        after_fxch = last == FXCH or (last == FROUND and before == FXCH)
        if not after_fxch or not (1 << (node["type"] >> 12)) & 0xE:
            return False
        return any(
            self.nodes[r]["tuple"]
            and fp_typed(self.nodes[r])
            and busy[2] <= 1
            and t <= cycle + 1
            for r, t in ready
        )

    def unit(self, node, picks, busy, fmul_block):
        """sched_pick_unit_p5 (C2+0x3b3e0)."""
        cls = node["unit"]
        if node["opcode"] == FMUL and fmul_block > 0:
            return None, "fmul busy"
        if cls >= 4:
            return (0, None) if all(b <= 0 for b in busy) else (None, "needs all pipes")
        if picks:
            return (cls + 1, None) if can_pair(picks[0], node) else (None, "no V pair")
        if busy[cls] > 0 or busy[cls + 1] > 0:
            return None, "pipe busy"
        return cls, None

    def choose(self, cycle, picks, ready, busy, fmul_block):
        """First ready-list node that passes every check, with the reasons others were passed over."""
        earliest = dict(ready)
        skipped = []
        for node_id, time in ready:
            node = self.nodes[node_id]
            if node_id == self.exit:
                return None, skipped
            unit, why = self.unit(node, picks, busy, fmul_block)
            if unit is None:
                skipped.append((node, why))
                continue
            pred = self.defer(node, cycle, earliest)
            if pred is not None:
                skipped.append((node, f"waits for #{self.nodes[pred]['seq']}"))
                continue
            if self.fxch_hold(node, cycle, ready, busy):
                skipped.append((node, "fxch hold"))
                continue
            if time > cycle + max(0, busy[unit]):
                skipped.append((node, f"ready at c{time}"))
                continue
            return node, skipped
        return None, skipped

    def issue(self, node):
        self.scheduled.add(node["id"])
        if node["tuple"]:
            self.tail = (node["opcode"], self.tail[0])
        for e in node["edges"]:
            self.remaining[e["to"]] -= 1
            if e["code"]:
                self.breakable[e["to"]] -= 1


def replay(window, previous_tail):
    """Annotate each recorded pick with the rule's choice and skip reasons."""
    model = Model(window, previous_tail)
    nodes = model.nodes
    problems = []
    for cycle in window["cycles"]:
        picks = []
        for pick in cycle["picks"]:
            ready = pick["ready"]
            expected = sorted(
                ready, key=lambda r: (-nodes[r[0]]["dynamic"], nodes[r[0]]["seq"])
            )
            if [r[0] for r in expected] != [r[0] for r in ready]:
                problems.append(
                    f"c{cycle['cycle']}: ready list is not in priority order"
                )
            chosen, skipped = model.choose(
                cycle["cycle"], picks, ready, cycle["busy"], cycle["fmul_block"]
            )
            actual = nodes[pick["node"]]
            pick["skipped"] = [(n["seq"], why) for n, why in skipped]
            pick["slot"] = "V" if picks else "U"
            if chosen is not actual:
                problems.append(
                    f"c{cycle['cycle']}: rule picks #{chosen['seq'] if chosen else '-'}, C2 picked #{actual['seq']}"
                )
            picks.append(actual)
            model.issue(actual)
    return problems, model.tail


# ---------------------------------------------------------------- native order


def emitted(window):
    nodes = {n["id"]: n for n in window["nodes"]}
    return [nodes[p["node"]] for c in window["cycles"] for p in c["picks"]]


def native_positions(config, object_path, windows, events):
    """Candidate and native instruction index of every scheduled node, where alignable.

    Tuples keep their identity through the late passes, so the final IL list
    (FINAL_HOOK) orders them as the object does; that list is aligned to the
    candidate instructions by mnemonic, and the candidate to native by the
    structural diff (a moved instruction pairs with identical text nearby).
    """
    manifest = m.load_function_symbol_manifest(m.DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH)
    dump = m.run_match_dump(
        obj_path=object_path,
        function_name=config.function,
        image_path=m.REPO_ROOT / manifest.primary_target,
        manifest=manifest,
        symbol_name=config.symbol,
        end_va=config.end_va,
    )
    target = [m.structural_line(line.text) for line in dump.target_lines]
    candidate = [m.structural_line(line.text) for line in dump.candidate_lines]
    ids = {n["tuple"] for w in windows for n in w["nodes"]}
    finals = [
        e for e in events if e["phase"] == 1 and ids & {n["id"] for n in e["nodes"]}
    ]
    if not finals:
        return dump
    final = [
        n for n in finals[-1]["nodes"] if n["flags"] & 0x100 and n["op"] < len(OPCODES)
    ]
    names = [OPCODES[n["op"]].removeprefix("p_e") for n in final]
    words = [c.split()[0] if c else "" for c in candidate]
    located = {}
    matcher = difflib.SequenceMatcher(a=names, b=words, autojunk=False)
    for tag, i1, i2, j1, j2 in matcher.get_opcodes():
        if tag == "equal" or (tag == "replace" and i2 - i1 == j2 - j1):
            for k in range(i2 - i1):
                located[final[i1 + k]["id"]] = j1 + k
    to_target, claimed = {}, set()
    matcher = difflib.SequenceMatcher(a=target, b=candidate, autojunk=False)
    for tag, i1, i2, j1, j2 in matcher.get_opcodes():
        if tag == "equal":
            for k in range(i2 - i1):
                to_target[j1 + k] = i1 + k
                claimed.add(i1 + k)
    for j, text in enumerate(candidate):
        if j in to_target:
            continue
        near = [i for i, x in enumerate(target) if x == text and i not in claimed]
        if near:
            best = min(near, key=lambda i: abs(i - j))
            if abs(best - j) <= 24:
                to_target[j] = best
                claimed.add(best)
    for w in windows:
        for n in w["nodes"]:
            j = located.get(n["tuple"]) if n["tuple"] else None
            n["candidate_index"] = j
            n["native_index"] = to_target.get(j) if j is not None else None
            n["candidate_text"] = (
                dump.candidate_lines[j].text if j is not None else None
            )
            n["native_text"] = (
                dump.target_lines[n["native_index"]].text
                if n["native_index"] is not None
                else None
            )
    return dump


# ---------------------------------------------------------------- report


def window_lines(window, first_line):
    labels = [n["label"] for n in window["nodes"] if n["real"] and n["label"]]
    if not labels:
        return None
    return first_line + min(labels), first_line + max(labels)


def reordered(window):
    real = [n["seq"] for n in emitted(window) if n["real"]]
    return real != sorted(real)


def report_window(k, window, first_line, verbose):
    nodes = {n["id"]: n for n in window["nodes"]}
    span = window_lines(window, first_line)
    out = emitted(window)
    moved = reordered(window)
    native_known = [n for n in out if n.get("native_index") is not None]
    native_order = [
        n["seq"] for n in sorted(native_known, key=lambda n: n["native_index"])
    ]
    ours_order = [n["seq"] for n in native_known]
    differs = native_order != ours_order
    head = (
        f"window {k}: {len(window['nodes']) - 2} nodes, lines {span[0]}-{span[1]}"
        if span
        else f"window {k}: {len(window['nodes']) - 2} nodes"
    )
    head += (
        f", {len(window['cycles'])} cycles"
        + (", reordered" if moved else "")
        + (", differs from native" if differs else "")
    )
    print(head)
    if not verbose:
        return
    print(
        "  input order (#seq line: instruction | latency height priority | successors)"
    )
    for n in window["nodes"]:
        if n["tuple"] == 0:
            continue
        line = first_line + n["label"] if n["label"] else 0
        flags = "".join(
            c
            for c, on in (
                ("R", n["reads"]),
                ("W", n["writes"]),
                ("B", n["barrier"]),
                ("*", n["critical"]),
            )
            if on
        )
        succ = ", ".join(
            f"#{nodes[e['to']]['seq']} {edge_text(e)}"
            for e in n["edges"]
            if nodes[e["to"]]["tuple"]
        )
        print(
            f"  #{n['seq']:<3} L{line:<4} {instruction(n)[:46]:46} | {n['latency']} h{n['height']:<3} {n['priority']:#07x} {flags:3} | {succ}"
        )
    print(
        "  schedule (cycle slot #seq; ready list in priority order, skipped nodes with the reason)"
    )
    for cycle in window["cycles"]:
        for pick in cycle["picks"]:
            n = nodes[pick["node"]]
            ready = " ".join(
                f"#{nodes[r]['seq']}" + (f"@{t}" if t > cycle["cycle"] else "")
                for r, t in pick["ready"]
                if nodes[r]["tuple"]
            )
            skipped = "; ".join(f"#{s} {why}" for s, why in pick.get("skipped", []))
            print(
                f"  c{cycle['cycle']:<3} {pick.get('slot', '?')} #{n['seq']:<3} {instruction(n)[:40]:40} ready: {ready}"
            )
            if skipped:
                print(f"  {'':9}passed over: {skipped}")
    print("  emitted:", " ".join(f"#{n['seq']}" for n in out if n["real"]))
    if native_known:
        print("  native: ", " ".join(f"#{s}" for s in native_order))
        for n in out:
            if n.get("native_index") is None and n["real"] and n["opcode"] < 0x144:
                print(
                    f"  (#{n['seq']} {n.get('candidate_text') or instruction(n)} has no native counterpart)"
                )


def label_base(source_text, definition):
    """C2 line labels count from the line that closes the parameter list."""
    depth, lines = 0, source_text.splitlines()
    for number in range(definition, len(lines) + 1):
        text = lines[number - 1].split("//", 1)[0]
        depth += text.count("(") - text.count(")")
        if depth <= 0 and "(" in "".join(lines[definition - 1 : number]):
            return number
    return definition


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("scratch", help="scratch name or directory")
    parser.add_argument(
        "--source", type=Path, help="overlay source replacing scratch.cpp"
    )
    parser.add_argument(
        "--line",
        type=int,
        action="append",
        help="physical scratch.cpp line (repeatable)",
    )
    parser.add_argument("--all", action="store_true", help="print every window in full")
    parser.add_argument(
        "--out", type=Path, help="new output directory (default: a temporary one)"
    )
    parser.add_argument(
        "--json", action="store_true", help="print decoded windows as JSON"
    )
    args = parser.parse_args()
    scratch = Path(args.scratch)
    if not scratch.is_dir():
        scratch = m.DEFAULT_MATCH_ROOT / "scratches" / args.scratch
    out = args.out or Path(tempfile.mkdtemp(prefix="c2sched-")) / "trace"
    work = rot.prepare(scratch, args.source, out.parent / (out.name + "-input"))
    result, events, data = run_observer(work, out)
    windows = decode(data)
    config = m.load_scratch_config(work)
    source_text = (work / "scratch.cpp").read_text()
    functions = list(dict.fromkeys(w["function"] for w in windows))
    target = config.symbol or config.function
    windows = [w for w in windows if w["function"] in (target, "_" + target)] or windows
    first_line = label_base(source_text, rot.definition_line(source_text, target))
    tail, problems = None, []
    for k, window in enumerate(windows):
        found, tail = replay(window, tail)
        problems += [f"window {k} {p}" for p in found]
    object_path = m.compile_scratch(config)
    native_positions(config, object_path, windows, events)
    (out / "schedule.json").write_text(json.dumps(windows, indent=1) + "\n")
    if args.json:
        print(json.dumps(windows, indent=1))
        return
    print(f"trace: {out}  functions: {', '.join(functions)}")
    print(f"metrics: {json.dumps(result['metrics'])}")
    for k, window in enumerate(windows):
        if args.line:
            chosen = any(
                first_line + n["label"] in args.line
                for n in window["nodes"]
                if n["real"] and n["label"]
            )
        else:
            chosen = args.all
        report_window(k, window, first_line, chosen)
    print(
        "rule check:",
        "every pick re-derived" if not problems else f"{len(problems)} disagreements",
    )
    for problem in problems[:20]:
        print("  " + problem)


if __name__ == "__main__":
    main()
