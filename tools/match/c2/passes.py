"""Print the IL node order of chosen source lines at every late C2 pass (diagnostic).

Hooks each post-allocation pass called by the pass driver (`C2+0x57fc2`)
through the preserving observer and prints, for the selected C2 line labels
(source line minus the function's definition line), the opcode/label sequence
entering each pass, and marks the pass that reordered it. The /G5 list
scheduler is `C2+0x374aa` (see scheduler.md). `--registers` also prints each
node's operands, `[dst<-src]`, with allocated registers by name and other
operands as `k<kind>`, so the pass that first gives a temporary its register
is visible.

    uv run tools/match/c2/passes.py update_subgame 12 15 [--source overlay.cpp] [--out DIR] [--registers]
"""

import argparse
import sys
import tempfile
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import trace as t

import rotation as rot

from snail import match as m

c2 = t.c2

# (call site, target) RVAs in the pass driver; every site passes the function in ecx.
PASSES_BY_COMPILER = {
    "msvc6.3": (
        (0x6859E, 0x319EF),  # local allocator
        (0x685C2, 0x31AE7),  # /G5 memory-operand split
        (0x685D5, 0x31E76),
        (0x685E8, 0x335B0),
        (0x68608, 0x335CD),
        (0x68629, 0x09CF0),
        (0x6863F, 0x3465C),
        (0x68652, 0x34D29),
        (0x68682, 0x3465C),
        (0x68695, 0x39F2D),  # late block mover
        (0x686A8, 0x09E41),
        (0x686AF, 0x09F07),
        (0x686B6, 0x3A3A1),
        (0x686D2, 0x3A418),
        (0x686FF, 0x3AD9B),  # /G5 list scheduler
        (0x6871A, 0x3BDF5),
        (0x6872D, 0x3C273),
        (0x68757, 0x3C627),
        (0x6876A, 0x3C875),
        (0x6878A, 0x3C8CC),
        (0x6879B, 0x3D8BF),
    ),
    "msvc6.5": (
        (0x583C5, 0x336F4),  # local allocator
        (0x583E9, 0x337EC),  # /G5 memory-operand split
        (0x583FC, 0x33B7B),
        (0x5840F, 0x34032),
        (0x5842F, 0x3404F),
        (0x58450, 0x04D75),
        (0x58466, 0x35042),
        (0x58479, 0x3536C),
        (0x584A9, 0x35042),
        (0x584BC, 0x3663C),  # late block mover
        (0x584CF, 0x04DE1),
        (0x584D6, 0x04EA7),
        (0x584DD, 0x36AB0),
        (0x584F9, 0x36B27),
        (0x58526, 0x374AA),  # /G5 list scheduler
        (0x58541, 0x3E113),
        (0x58554, 0x3E591),
        (0x5857E, 0x3E945),
        (0x58591, 0x3EB93),
        (0x585B1, 0x3EBEA),
        (0x585C2, 0x3FBDD),
    ),
}
PASSES = PASSES_BY_COMPILER[m.DEFAULT_SCRATCH_COMPILER]


def run(scratch, source, out):
    work = rot.prepare(scratch, source, out.parent / (out.name + "-input"))
    stock = c2.load_profile
    profile = stock()
    passes = PASSES_BY_COMPILER[profile["compiler"]]
    hooks = [
        {"site": site, "target": target, "return": False} for site, target in passes
    ]
    profile = dict(profile, name=profile["name"] + "-late-passes", hooks=hooks)
    c2.load_profile = lambda *a, **kw: profile
    try:
        result, events = t.trace(work, out, target_only=True)
    finally:
        c2.load_profile = stock
    return t.function_events(events, result["function_ordinal"])


def operands(node, base):
    def name(operand):
        return rot.assigned_register(operand, base) or f"k{operand['kind']}"

    destinations = ",".join(name(operand) for operand in node["dst"])
    sources = ",".join(name(operand) for operand in node["src"])
    return f"[{destinations}<-{sources}]"


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("scratch")
    parser.add_argument("first", type=int, help="first C2 line label")
    parser.add_argument("last", type=int, help="last C2 line label")
    parser.add_argument("--source", type=Path)
    parser.add_argument("--out", type=Path)
    parser.add_argument("--registers", action="store_true", help="print operand registers")
    args = parser.parse_args()
    scratch = Path(args.scratch)
    if not scratch.is_dir():
        scratch = m.DEFAULT_MATCH_ROOT / "scratches" / args.scratch
    out = args.out or Path(tempfile.mkdtemp(prefix="c2pass-")) / "trace"
    events = run(scratch, args.source, out)
    print(f"trace: {out}")
    previous, previous_target = None, None
    for event in events:
        order = [
            f"{node['op']}:{node['line']}"
            + (operands(node, event["c2_base"]) if args.registers else "")
            for node in event["nodes"]
            if args.first <= node["line"] <= args.last
        ]
        _, target = PASSES[event["phase"]]
        changed = previous is not None and order != previous
        mark = f"  <- reordered by C2+{previous_target:#07x}" if changed else ""
        print(f"entering C2+{target:#07x}: {' '.join(order)}{mark}")
        previous, previous_target = order, target


if __name__ == "__main__":
    main()
