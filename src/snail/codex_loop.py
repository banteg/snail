from __future__ import annotations

import argparse
from pathlib import Path
import shlex
import subprocess
import sys
import time
from typing import Sequence

DEFAULT_PROMPT_PATH = Path("LOOP.md")
DEFAULT_CODEX_ARGS = (
    "--dangerously-bypass-approvals-and-sandbox",
    "-m",
    "gpt-5.4",
    "-c",
    'model_reasoning_effort="xhigh"',
)


def split_script_and_codex_args(argv: Sequence[str]) -> tuple[list[str], list[str]]:
    parts = list(argv)
    try:
        separator_index = parts.index("--")
    except ValueError:
        return parts, []
    return parts[:separator_index], parts[separator_index + 1 :]


def positive_int(value: str) -> int:
    parsed = int(value)
    if parsed < 1:
        raise argparse.ArgumentTypeError("iterations must be >= 1")
    return parsed


def nonnegative_float(value: str) -> float:
    parsed = float(value)
    if parsed < 0:
        raise argparse.ArgumentTypeError("delay must be >= 0")
    return parsed


def normalize_codex_args(codex_args: Sequence[str]) -> list[str]:
    if codex_args:
        return list(codex_args)
    return list(DEFAULT_CODEX_ARGS)


def build_codex_command(*, codex_args: Sequence[str], cd_path: Path | None) -> list[str]:
    command = ["codex", "exec", *codex_args]
    if cd_path is not None:
        command.extend(["-C", str(cd_path)])
    command.append("-")
    return command


def run_iterations(
    *,
    iterations: int,
    prompt_path: Path,
    codex_args: Sequence[str],
    cd_path: Path | None,
    continue_on_error: bool,
    delay_seconds: float,
    dry_run: bool,
) -> int:
    command = build_codex_command(codex_args=codex_args, cd_path=cd_path)
    failures: list[tuple[int, int]] = []

    for iteration in range(1, iterations + 1):
        prompt_text = prompt_path.read_text(encoding="utf-8")
        print(f"==> Iteration {iteration}/{iterations}", flush=True)
        print(f"    Prompt: {prompt_path}", flush=True)
        print(f"    Command: {shlex.join(command)}", flush=True)

        if dry_run:
            continue

        completed = subprocess.run(command, input=prompt_text, text=True, check=False)
        if completed.returncode != 0:
            failures.append((iteration, completed.returncode))
            print(
                f"Iteration {iteration} failed with exit code {completed.returncode}.",
                file=sys.stderr,
                flush=True,
            )
            if not continue_on_error:
                break

        if delay_seconds > 0 and iteration < iterations:
            time.sleep(delay_seconds)

    if dry_run:
        return 0
    if not failures:
        return 0

    summary = ", ".join(
        f"iteration {iteration} -> exit {returncode}" for iteration, returncode in failures
    )
    print(f"Failures: {summary}", file=sys.stderr, flush=True)
    return failures[-1][1]


def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
        description="Run `codex exec` against a prompt file for N iterations.",
        epilog=(
            "Default exec args are yolo mode plus `-m gpt-5.4` and "
            "`-c 'model_reasoning_effort=\"xhigh\"'`. "
            "Pass explicit exec args after `--` to override them, for example: "
            "`uv run tools/codex_loop.py --dry-run 5 -- --full-auto -m gpt-5.4`."
        ),
    )
    parser.add_argument("iterations", type=positive_int, help="How many times to run `codex exec`.")
    parser.add_argument(
        "--prompt-file",
        type=Path,
        default=DEFAULT_PROMPT_PATH,
        help="Prompt file to feed to Codex on each iteration (default: LOOP.md).",
    )
    parser.add_argument(
        "--cd",
        type=Path,
        default=Path.cwd(),
        help="Working tree passed to `codex exec -C` (default: current directory).",
    )
    parser.add_argument(
        "--continue-on-error",
        action="store_true",
        help="Keep going even if one iteration exits non-zero.",
    )
    parser.add_argument(
        "--delay-seconds",
        type=nonnegative_float,
        default=0.0,
        help="Optional delay between iterations.",
    )
    parser.add_argument(
        "--dry-run",
        action="store_true",
        help="Print the commands that would be run without executing them.",
    )
    return parser


def main(argv: Sequence[str] | None = None) -> int:
    parser = build_parser()
    script_args, codex_args = split_script_and_codex_args(sys.argv[1:] if argv is None else argv)
    args = parser.parse_args(script_args)

    prompt_path = args.prompt_file.resolve()
    if not prompt_path.is_file():
        parser.error(f"prompt file does not exist: {prompt_path}")

    cd_path = args.cd.resolve() if args.cd is not None else None
    codex_args = normalize_codex_args(codex_args)

    return run_iterations(
        iterations=args.iterations,
        prompt_path=prompt_path,
        codex_args=codex_args,
        cd_path=cd_path,
        continue_on_error=args.continue_on_error,
        delay_seconds=args.delay_seconds,
        dry_run=args.dry_run,
    )


if __name__ == "__main__":
    raise SystemExit(main())
