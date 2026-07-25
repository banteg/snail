#!/usr/bin/env python3
"""Import a native artifact and decompile one unambiguous named function."""

from __future__ import annotations

import argparse
import os
import subprocess
import tempfile
from pathlib import Path


DEFAULT_GHIDRA_DIR = Path("/Applications/ghidra_12.1.2_PUBLIC")
SCRIPT_DIR = Path(__file__).resolve().parent


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("binary", type=Path, help="ELF or PE artifact to import")
    parser.add_argument(
        "symbol_fragment",
        help="unique demangled function-name fragment, such as SetShootFlags",
    )
    parser.add_argument(
        "--ghidra-dir",
        type=Path,
        default=DEFAULT_GHIDRA_DIR,
        help=f"Ghidra installation (default: {DEFAULT_GHIDRA_DIR})",
    )
    parser.add_argument(
        "--analysis-timeout",
        type=int,
        default=180,
        help="whole-program analysis timeout in seconds (default: 180)",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    binary = args.binary.resolve()
    headless = args.ghidra_dir / "support" / "analyzeHeadless"
    if not binary.is_file():
        raise SystemExit(f"missing binary: {binary}")
    if not headless.is_file():
        raise SystemExit(f"missing Ghidra headless launcher: {headless}")

    with tempfile.TemporaryDirectory(prefix="snail-ghidra-") as temporary:
        root = Path(temporary)
        home = root / "home"
        projects = root / "projects"
        home.mkdir()
        projects.mkdir()

        env = os.environ.copy()
        env["HOME"] = str(home)
        java_options = env.get("JAVA_TOOL_OPTIONS", "")
        env["JAVA_TOOL_OPTIONS"] = (
            f"{java_options} -Duser.home={home}".strip()
        )

        command = (
            str(headless),
            str(projects),
            "SnailSymbolProbe",
            "-import",
            str(binary),
            "-analysisTimeoutPerFile",
            str(args.analysis_timeout),
            "-scriptPath",
            str(SCRIPT_DIR),
            "-postScript",
            "DecompileSymbol.java",
            args.symbol_fragment,
            "-deleteProject",
        )
        return subprocess.run(command, env=env, check=False).returncode


if __name__ == "__main__":
    raise SystemExit(main())
