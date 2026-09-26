"""Run one of Crimson's C2 tracers (`../crimson/scripts/c2/<tracer>.py`) on a Snail scratch.

The tracers observe through `crimson.match_c2`. This runner supplies that module from
[trace.py](trace.py), so they keep Crimson's preserving observer but compile and measure with Snail.
Arguments after the tracer name go to the tracer.

    uv run tools/match/c2/run_tracer.py il_stage_trace <scratch> --out <new-dir> --lines 189-191
    uv run tools/match/c2/run_tracer.py priority_trace <scratch> --out <new-dir> --constant 0 \
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
        "tracer", help="tracer name in ../crimson/scripts/c2, without .py"
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
    tracer = adapter.CRIMSON / "scripts/c2" / f"{args.tracer}.py"
    if not tracer.exists():
        parser.error(f"no such Crimson tracer: {tracer}")
    sys.path.insert(0, str(tracer.parent))
    sys.argv = [str(tracer), *rest]
    runpy.run_path(str(tracer), run_name="__main__")


if __name__ == "__main__":
    main()
