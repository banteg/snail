"""Run one of Crimson's C2 tracers (`../crimson/scripts/c2/<tool>.py`) on a Snail scratch.

The tracers observe through `crimson.match_c2`. This runner supplies that module from
[trace.py](trace.py), so they keep Crimson's preserving observer but compile and measure with Snail.
Arguments after the tool name go to the tool.

    uv run tools/match/c2/crimson_tool.py il_stage_trace <scratch> --out <new-dir> --lines 189-191
    uv run tools/match/c2/crimson_tool.py priority_trace <scratch> --out <new-dir> --constant 0 \
        --match-root <alternate tools/match root>
"""

import argparse
import runpy
import sys
import trace as adapter
import types
from pathlib import Path

from snail import match as m


def main():
    parser = argparse.ArgumentParser(
        description=__doc__,
        formatter_class=argparse.RawDescriptionHelpFormatter,
        add_help=False,
    )
    parser.add_argument(
        "tool", help="tracer name in ../crimson/scripts/c2, without .py"
    )
    parser.add_argument(
        "--match-root", type=Path, help="compile against another tools/match root"
    )
    args, rest = parser.parse_known_args()
    if args.match_root is not None:
        root = args.match_root.resolve()
        adapter.facade.compile_scratch = lambda config, force=False: m.compile_scratch(
            config, root
        )
    crimson = types.ModuleType("crimson")
    crimson.match_c2 = adapter.c2
    sys.modules["crimson"] = crimson
    sys.modules["crimson.match_c2"] = adapter.c2
    tool = adapter.CRIMSON / "scripts/c2" / f"{args.tool}.py"
    if not tool.exists():
        parser.error(f"no such Crimson tracer: {tool}")
    sys.path.insert(0, str(tool.parent))
    sys.argv = [str(tool), *rest]
    runpy.run_path(str(tool), run_name="__main__")


if __name__ == "__main__":
    main()
