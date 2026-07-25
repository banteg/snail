#!/usr/bin/env python3
"""Import a native artifact and decompile one unambiguous named function."""

from __future__ import annotations

import argparse
import os
import subprocess
import sys
import tempfile
from pathlib import Path


DEFAULT_GHIDRA_DIR = Path("/Applications/ghidra_12.1.2_PUBLIC")
SCRIPT_DIR = Path(__file__).resolve().parent
FAILURE_LOG_LINES = 80


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


def failure_log_tail(*streams: str) -> str:
    lines = []
    for stream in streams:
        stream_lines = [line for line in stream.splitlines() if line.strip()]
        error_start = next(
            (
                index
                for index, line in enumerate(stream_lines)
                if "ERROR REPORT SCRIPT ERROR" in line
            ),
            None,
        )
        if error_start is not None:
            script_error = stream_lines[error_start:]
            error_end = next(
                (
                    index
                    for index, line in enumerate(script_error[1:], start=1)
                    if "ANALYZING changes made by post scripts" in line
                ),
                len(script_error),
            )
            return "\n".join(script_error[:error_end])
        lines.extend(stream_lines)
    return "\n".join(lines[-FAILURE_LOG_LINES:])


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
        output_path = root / "decompile.txt"
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
            str(output_path),
            "-deleteProject",
        )
        completed = subprocess.run(
            command,
            env=env,
            check=False,
            capture_output=True,
            text=True,
        )
        if completed.returncode == 0 and output_path.is_file():
            sys.stdout.write(output_path.read_text(encoding="utf-8"))
            return 0

        detail = failure_log_tail(completed.stdout, completed.stderr)
        print("Ghidra symbol probe failed", file=sys.stderr)
        if completed.returncode != 0:
            print(
                f"Ghidra launcher exit code: {completed.returncode}",
                file=sys.stderr,
            )
        if not output_path.is_file():
            print(
                "Ghidra did not write a decompile payload",
                file=sys.stderr,
            )
        if detail:
            print(detail, file=sys.stderr)
        return completed.returncode or 1


if __name__ == "__main__":
    raise SystemExit(main())
