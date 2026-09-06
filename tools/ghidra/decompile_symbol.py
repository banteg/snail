#!/usr/bin/env python3
"""Import a native artifact and decompile one selected function."""

from __future__ import annotations

import argparse
import os
import subprocess
import sys
from pathlib import Path

from project import (
    DEFAULT_GHIDRA_DIR,
    DEFAULT_PROJECT_ROOT,
    Project,
    ProjectLockError,
    ProjectMetadataError,
    locked_persistent_project,
    prepare_project,
    record_initialized_project,
    temporary_fresh_project,
)

SCRIPT_DIR = Path(__file__).resolve().parent
FAILURE_LOG_LINES = 80


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "binary",
        type=Path,
        help="ELF, Mach-O, or PE artifact to import",
    )
    parser.add_argument(
        "selector",
        help=(
            "unique function-name fragment, such as SetShootFlags, or an "
            "exact hexadecimal entry address, such as 0x5f620"
        ),
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
    parser.add_argument(
        "--project-root",
        type=Path,
        default=DEFAULT_PROJECT_ROOT,
        help=(
            "Persistent per-binary Ghidra project root "
            f"(default: {DEFAULT_PROJECT_ROOT})"
        ),
    )
    parser.add_argument(
        "--fresh",
        action="store_true",
        help="Use and delete a temporary clean-room project instead of the persistent project",
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


def run_probe(
    *,
    project: Project,
    headless: Path,
    binary: Path,
    selector: str,
    analysis_timeout: int,
) -> int:
    output_path = project.root / "decompile.txt"
    if output_path.exists():
        output_path.unlink()
    env = os.environ.copy()
    env["HOME"] = str(project.home)
    java_options = env.get("JAVA_TOOL_OPTIONS", "")
    env["JAVA_TOOL_OPTIONS"] = f"{java_options} -Duser.home={project.home}".strip()
    command = (
        *project.command_prefix(headless, binary),
        "-analysisTimeoutPerFile",
        str(analysis_timeout),
        "-scriptPath",
        str(SCRIPT_DIR),
        "-postScript",
        "DecompileSymbol.java",
        selector,
        str(output_path),
        *project.command_suffix(),
    )
    completed = subprocess.run(
        command,
        env=env,
        check=False,
        capture_output=True,
        text=True,
    )
    if completed.returncode == 0 and project.project_file.is_file():
        record_initialized_project(project)
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


def main() -> int:
    args = parse_args()
    binary = args.binary.resolve()
    headless = args.ghidra_dir / "support" / "analyzeHeadless"
    if not binary.is_file():
        raise SystemExit(f"missing binary: {binary}")
    if not headless.is_file():
        raise SystemExit(f"missing Ghidra headless launcher: {headless}")
    try:
        if args.fresh:
            with temporary_fresh_project(
                binary,
                args.ghidra_dir,
                prefix="snail-ghidra-",
            ) as project:
                return run_probe(
                    project=project,
                    headless=headless,
                    binary=binary,
                    selector=args.selector,
                    analysis_timeout=args.analysis_timeout,
                )

        with locked_persistent_project(
            binary,
            args.ghidra_dir,
            args.project_root,
        ) as project:
            prepare_project(project)
            print(
                f"using persistent Ghidra project: {project.root}",
                file=sys.stderr,
            )
            return run_probe(
                project=project,
                headless=headless,
                binary=binary,
                selector=args.selector,
                analysis_timeout=args.analysis_timeout,
            )
    except (ProjectLockError, ProjectMetadataError) as error:
        raise SystemExit(str(error)) from error


if __name__ == "__main__":
    raise SystemExit(main())
