"""Run one of Crimson's C2 tracers (`../crimson/scripts/c2/<tracer>.py`) on a Snail scratch.

The tracers observe through `crimson.match_c2`. This runner supplies the vendored
observer ([c2_observer.py](c2_observer.py)) under that name, so they compile and measure with
Snail. Their hook addresses are pinned to Crimson's msvc6.5 backend; on another backend the
observer rejects the hooks before running. Arguments after the tracer name go to the tracer.

    uv run tools/match/c2/run_tracer.py il_stage_trace <scratch> --out <new-dir> --lines 189-191
    uv run tools/match/c2/run_tracer.py priority_trace <scratch> --out <new-dir> --constant 0 \
        --match-root <alternate tools/match root>
"""

import argparse
import runpy
import sys
import types
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import c2_observer

from snail import match as m

CRIMSON = Path(m.__file__).resolve().parents[3] / "crimson"


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
        compile_scratch = m.compile_scratch
        m.compile_scratch = lambda config, *_args, **_kwargs: compile_scratch(config, root)
    crimson = types.ModuleType("crimson")
    crimson.match_c2 = c2_observer
    sys.modules["crimson"] = crimson
    sys.modules["crimson.match_c2"] = c2_observer
    tracer = CRIMSON / "scripts/c2" / f"{args.tracer}.py"
    if not tracer.exists():
        parser.error(f"no such Crimson tracer: {tracer}")
    sys.path.insert(0, str(tracer.parent))
    sys.argv = [str(tracer), *rest]
    runpy.run_path(str(tracer), run_name="__main__")


if __name__ == "__main__":
    main()
