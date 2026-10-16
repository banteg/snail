"""Trace VC6 C2's per-function inline budget for one Snail scratch (diagnostic only).

Port of Crimson's `scripts/c2/inline_budget_trace.py` to Snail's observer
profiles and translation units. C2's `inline_function_calls` sets the running
total (data 0x9f234) to the caller's own size estimate (`fe_function+0x6d`)
and calls `inline_expand_calls` with budget `clamp(2*size, 1000, 35000)`.
For each collected call site, in IL order, a callee of size `s = fsym+0x6d`
is inlined when `s <= remaining` or `s <= 0x28`, and only while the running
total is at most 35000. A callee with `s > 0x28` spends `s` of the remaining
budget, and every expansion adds `s` to the running total. A refused callee
stays a call (warning C4710 for `__inline`, C4714 for `__forceinline`).

Hooks (msvc6.5 call site -> routine; the msvc6.3 values come from
map_rvas.py with full 24/24 context scores):

- inline_expand_calls, top level: 0x18134 -> 0x181a8 / 0x19986 -> 0x199fa;
- read_function_il(callee), an accepted expansion: 0x187ae -> 0x1ba73 /
  0x1a000 -> 0x1b973;
- warning(callee), a refused callee: 0x18281 -> 0x42bbe / 0x19ad3 -> 0x42b6c.

    uv run tools/match/c2/inline_budget.py initialize_game_assets_and_world \\
        [--source overlay.cpp] [--all] [--function NAME]

It also records C2's alias class count (data 0x9d670) at each scheduling
window; once a function reaches 0x400 classes, later symbols share class 1.

Each row prints the call-site line (physical scratch.cpp line of the frozen
unit), the callee, its size, the remaining budget after the decision and the
running total, in the inliner's visiting order. By default only budget
spenders (size > 0x28) and refusals are listed.
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
import schedtrace as sched

from snail import match as m

c2 = t.c2

HOOKS = {
    "msvc6.5": {
        "top": {"site": 0x18134, "target": 0x181A8, "return": False},
        "accept": {"site": 0x187AE, "target": 0x1BA73, "return": False},
        "refuse": {"site": 0x18281, "target": 0x42BBE, "return": False},
    },
    "msvc6.3": {
        "top": {"site": 0x19986, "target": 0x199FA, "return": False},
        "accept": {"site": 0x1A000, "target": 0x1B973, "return": False},
        "refuse": {"site": 0x19AD3, "target": 0x42B6C, "return": False},
    },
}
INLINE_TOTAL = 0x9F234
WORDS = 24

RECORDER = r"""
static HANDLE inline_file;
static void copy_name(unsigned long *out, const char *text, unsigned long words)
{
    unsigned long j;
    char *dst = (char *)out;
    for (j = 0; j < words; ++j) out[j] = 0;
    for (j = 0; text && j + 1 < words * 4 && text[j]; ++j) dst[j] = text[j];
}
/* Row: 0 kind (1 top, 2 accept, 3 refuse, 4 alias classes), 1 line, 2 callee size, 3 remaining, 4 running total,
   5 budget or depth word, 6..13 callee name, 14..23 function name. */
static int inline_watch(unsigned long phase, unsigned long *registers)
{
    unsigned long rec[WORDS], entry = registers[3] + 4, loop, fsym, fe, tuple, j;
    unsigned char *base;
    DWORD written;
    if (phase < 2) return 0;
    if (phase >= 100) return 1;
    base = (unsigned char *)targets[phase] - hook_rva[phase];
    for (j = 0; j < WORDS; ++j) rec[j] = 0;
    rec[0] = phase - 1;
    rec[4] = *(unsigned long *)(base + INLINE_TOTAL);
    if (phase == 5) {
        rec[4] = *(unsigned long *)(base + ALIAS_CLASS_COUNT);
    } else if (phase == 2) {
        rec[5] = *(unsigned long *)(entry + 4);
    } else {
        loop = entry + 4 + (phase == 4 ? 0xc : 0);
        fsym = phase == 3 ? registers[6] : registers[0];
        tuple = *(unsigned long *)(*(unsigned long *)(loop + 0x14) + 4);
        rec[1] = *(unsigned short *)(tuple + 0x10);
        rec[2] = (unsigned long)(long)*(short *)(fsym + 0x6d);
        rec[3] = *(unsigned long *)(loop + 0x48);
        rec[5] = *(unsigned long *)(loop + 0x34);
        copy_name(rec + 6, *(char **)(fsym + 0x18), 8);
    }
    fe = *(unsigned long *)(base + CUR_FUNC_SYM);
    copy_name(rec + 14, fe ? *(char **)(fe + 0x18) : 0, 10);
    if (!WriteFile(inline_file, rec, sizeof(rec), &written, 0) || written != sizeof(rec)) ExitProcess(71);
    return 1;
}
"""


def observer(profile, stock_source, hooks):
    source = stock_source(profile)
    anchors = (
        "    unsigned long first, node, count = 0, record[742], op, side, j, k, at;\n",
        "    trace_file = CreateFileA(",
        "    CloseHandle(trace_file);",
        "static void __cdecl observe(",
    )
    for anchor in anchors:
        if source.count(anchor) != 1:
            raise ValueError(f"Unexpected observer template near {anchor!r}")
    defines = {
        "WORDS": WORDS,
        "CUR_FUNC_SYM": profile["scheduler"]["current_function_symbol"],
        "INLINE_TOTAL": INLINE_TOTAL,
        "ALIAS_CLASS_COUNT": profile["scheduler"]["alias_class_count"],
    }
    # Long operand chains exceed the stock 16-entry snapshot; truncate instead.
    source = source.replace("if(op) ExitProcess(98);", "")
    header = "".join(f"#define {k} {v}\n" for k, v in defines.items())
    hook_rvas = ",".join(str(h["target"]) for h in hooks)
    header += f"static const unsigned long hook_rva[] = {{{hook_rvas}}};\n"
    source = source.replace(anchors[3], header + RECORDER + anchors[3])
    source = source.replace(
        anchors[0], anchors[0] + "    if (inline_watch(phase, registers)) return;\n"
    )
    source = source.replace(
        anchors[1],
        '    inline_file = CreateFileA("inline.bin", GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);\n'
        "    if (inline_file == INVALID_HANDLE_VALUE) ExitProcess(72);\n" + anchors[1],
    )
    return source.replace(anchors[2], "    CloseHandle(inline_file);\n" + anchors[2])


def run_observer(scratch, out):
    """Preserving run: whole-COFF identity and matcher metrics are checked by the adapter."""
    compiler = m.load_scratch_config(scratch).compiler
    stock_profile, stock_source = c2.load_profile, c2.observer_source
    profile = rot.use_backend(compiler)
    backend = HOOKS[compiler]
    hooks = [
        rot.FUNCTION_ENTRY_HOOK,
        rot.FINAL_HOOK,
        backend["top"],
        backend["accept"],
        backend["refuse"],
        profile["scheduler"]["graph_hook"],
    ]
    profile = dict(profile, name=profile["name"] + "-inline-budget", hooks=hooks)
    c2.load_profile = lambda *_: profile
    c2.observer_source = lambda p: observer(p, stock_source, hooks)
    try:
        result, _events = t.trace(scratch, out)
    finally:
        c2.load_profile, c2.observer_source = stock_profile, stock_source
    return result, (out / "observed/inline.bin").read_bytes()


def text(words):
    return struct.pack(f"<{len(words)}I", *words).split(b"\0", 1)[0].decode("latin-1")


def signed(value):
    return value - (1 << 32) if value & 0x80000000 else value


def decode(data):
    rows = []
    for at in range(0, len(data), WORDS * 4):
        w = struct.unpack_from(f"<{WORDS}I", data, at)
        rows.append(
            {
                "kind": {1: "top", 2: "inline", 3: "refuse", 4: "classes"}[w[0]],
                "line": w[1],
                "size": signed(w[2]),
                "remaining": signed(w[3]),
                "total": signed(w[4]),
                "word": signed(w[5]),
                "callee": text(w[6:14]),
                "function": text(w[14:24]),
            }
        )
    return rows


def main():
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter
    )
    parser.add_argument("scratch", help="scratch name or directory")
    parser.add_argument(
        "--source", type=Path, help="overlay source replacing scratch.cpp"
    )
    parser.add_argument(
        "--out", type=Path, help="new output directory (default: a temporary one)"
    )
    parser.add_argument(
        "--function", help="compiled function to list (default: the scratch's)"
    )
    parser.add_argument(
        "--all",
        action="store_true",
        help="list every expansion, not only budget spenders",
    )
    args = parser.parse_args()
    scratch = Path(args.scratch)
    if not scratch.is_dir():
        scratch = m.DEFAULT_MATCH_ROOT / "scratches" / args.scratch
    out = args.out or Path(tempfile.mkdtemp(prefix="c2inline-")) / "trace"
    work = rot.prepare(scratch, args.source, out.parent / (out.name + "-input"))
    result, data = run_observer(work, out)
    config = m.load_scratch_config(work)
    source_text = (work / "scratch.cpp").read_text()
    target = args.function or config.function
    # Recorded names are decorated and cut at 39 characters.
    rows = [
        r
        for r in decode(data)
        if (stem := r["function"].lstrip("?_").split("@")[0])
        and target.startswith(stem)
    ]
    if not rows:
        names = sorted({r["function"] for r in decode(data)})
        raise SystemExit(f"{target} not traced; functions: {', '.join(names)}")
    first_line = sched.label_base(source_text, rot.definition_line(source_text, target))
    classes = sorted({r["total"] for r in rows if r["kind"] == "classes"})
    rows = [r for r in rows if r["kind"] != "classes"]
    top = next(r for r in rows if r["kind"] == "top")
    inlined = [r for r in rows if r["kind"] == "inline"]
    refused = [r for r in rows if r["kind"] == "refuse"]
    print(f"trace: {out}")
    print(f"metrics: ratio {result['metrics']['ratio']:.4%}")
    print(
        f"{target}: own size {top['total']}, budget {top['word']}, "
        f"{len(inlined)} expansions ({sum(r['size'] for r in inlined)} size), "
        f"final total {rows[-1]['total']}, {len(refused)} refused, "
        f"alias classes {'/'.join(hex(c) for c in classes)} (class 1 from 0x400)"
    )
    for r in rows:
        if r["kind"] == "top":
            continue
        if not args.all and r["kind"] == "inline" and r["size"] <= 0x28:
            continue
        print(
            f"  {r['kind']:6} line {first_line + r['line']:<5} {r['callee']:<40} "
            f"size {r['size']:<5} remaining {r['remaining']:<6} total {r['total']}"
        )


if __name__ == "__main__":
    main()
