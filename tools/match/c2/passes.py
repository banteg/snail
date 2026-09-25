"""Print the IL node order of chosen source lines at every late C2 pass (diagnostic).

Hooks each post-allocation pass called by the pass driver (`C2+0x57fc2`)
through the preserving observer and prints, for the selected C2 line labels
(source line minus the function's definition line), the opcode/label sequence
entering each pass, and marks the pass that reordered it. The /G5 list
scheduler is `C2+0x374aa` (see scheduler.md).

    uv run tools/match/c2/passes.py update_subgame 12 15 [--source overlay.cpp] [--out DIR]
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
PASSES = (
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
)


def run(scratch, source, out):
    work = rot.prepare(scratch, source, out.parent / (out.name + "-input"))
    stock = c2.load_profile
    profile = stock()
    hooks = [
        {"site": site, "target": target, "return": False} for site, target in PASSES
    ]
    profile = dict(profile, name=profile["name"] + "-late-passes", hooks=hooks)
    c2.load_profile = lambda: profile
    try:
        _, events = t.trace(work, out)
    finally:
        c2.load_profile = stock
    return events


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("scratch")
    parser.add_argument("first", type=int, help="first C2 line label")
    parser.add_argument("last", type=int, help="last C2 line label")
    parser.add_argument("--source", type=Path)
    parser.add_argument("--out", type=Path)
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
