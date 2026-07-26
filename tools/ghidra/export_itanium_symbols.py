#!/usr/bin/env python3
"""Batch-export every selected Itanium C++ function in one Ghidra run."""

from __future__ import annotations

import argparse
import json
import os
import re
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path

DEFAULT_GHIDRA_DIR = Path("/Applications/ghidra_12.1.2_PUBLIC")
DEFAULT_NM = Path("/usr/bin/nm")
DEFAULT_CXXFILT = Path("/usr/bin/c++filt")
SCRIPT_DIR = Path(__file__).resolve().parent
FAILURE_LOG_LINES = 80
ITANIUM_NESTED_SYMBOL = re.compile(r"^_{1,2}ZN")
TEXT_SYMBOL_TYPES = frozenset(("T", "t", "W", "w"))


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "binary",
        type=Path,
        help="ELF or Mach-O artifact whose nested C++ functions will be exported",
    )
    parser.add_argument(
        "output",
        type=Path,
        help="Corpus root that will receive functions/ and index.json",
    )
    parser.add_argument(
        "--ghidra-dir",
        type=Path,
        default=DEFAULT_GHIDRA_DIR,
        help=f"Ghidra installation (default: {DEFAULT_GHIDRA_DIR})",
    )
    parser.add_argument(
        "--nm",
        type=Path,
        default=DEFAULT_NM,
        help=f"nm executable (default: {DEFAULT_NM})",
    )
    parser.add_argument(
        "--cxxfilt",
        type=Path,
        default=DEFAULT_CXXFILT,
        help=f"c++filt executable (default: {DEFAULT_CXXFILT})",
    )
    parser.add_argument(
        "--analysis-timeout",
        type=int,
        default=300,
        help="whole-program analysis timeout in seconds (default: 300)",
    )
    parser.add_argument(
        "--decompile-timeout",
        type=int,
        default=60,
        help="per-function decompile timeout in seconds (default: 60)",
    )
    parser.add_argument(
        "--contains",
        help="Only export symbols whose mangled or demangled name contains this text",
    )
    parser.add_argument(
        "--limit",
        type=int,
        help="Only export the first N selected symbols (for bounded smoke tests)",
    )
    parser.add_argument(
        "--strict",
        action="store_true",
        help="Exit non-zero instead of installing a corpus with failed functions",
    )
    return parser.parse_args()


def parse_nm_symbols(output: str) -> list[tuple[str, str]]:
    symbols: dict[str, str] = {}
    for line in output.splitlines():
        fields = line.split()
        if not fields:
            continue
        binary_symbol = fields[-1]
        if not ITANIUM_NESTED_SYMBOL.match(binary_symbol):
            continue
        is_text_symbol = (
            len(fields) == 3 and fields[-2] in TEXT_SYMBOL_TYPES
        )
        is_stabs_function = len(fields) >= 6 and fields[-2] == "FUN"
        if not is_text_symbol and not is_stabs_function:
            continue
        mangled = (
            binary_symbol[1:]
            if binary_symbol.startswith("__ZN")
            else binary_symbol
        )
        symbols.setdefault(mangled, binary_symbol)
    return sorted(symbols.items())


def collect_symbols(
    binary: Path,
    *,
    nm: Path = DEFAULT_NM,
    cxxfilt: Path = DEFAULT_CXXFILT,
) -> list[dict[str, str]]:
    nm_result = subprocess.run(
        (str(nm), "-a", str(binary)),
        check=False,
        capture_output=True,
        text=True,
    )
    if nm_result.returncode != 0:
        raise RuntimeError(
            f"nm failed with exit code {nm_result.returncode}: "
            f"{nm_result.stderr.strip()}"
        )
    parsed = parse_nm_symbols(nm_result.stdout)
    if not parsed:
        raise RuntimeError(f"no _ZN symbols found in {binary}")

    mangled_input = "\n".join(mangled for mangled, _ in parsed) + "\n"
    demangle_result = subprocess.run(
        (str(cxxfilt),),
        input=mangled_input,
        check=False,
        capture_output=True,
        text=True,
    )
    if demangle_result.returncode != 0:
        raise RuntimeError(
            f"c++filt failed with exit code {demangle_result.returncode}: "
            f"{demangle_result.stderr.strip()}"
        )
    demangled = demangle_result.stdout.splitlines()
    if len(demangled) != len(parsed):
        raise RuntimeError(
            "c++filt output count does not match the symbol-table input"
        )
    return [
        {
            "mangled": mangled,
            "binarySymbol": binary_symbol,
            "demangled": readable,
        }
        for (mangled, binary_symbol), readable in zip(
            parsed, demangled, strict=True
        )
    ]


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


def install_corpus(staged: Path, output: Path) -> None:
    backup = output.with_name(f".{output.name}.previous")
    if backup.exists():
        raise RuntimeError(f"refusing to overwrite stale backup: {backup}")
    output.parent.mkdir(parents=True, exist_ok=True)
    if output.exists():
        output.rename(backup)
    try:
        staged.rename(output)
    except Exception:
        if backup.exists() and not output.exists():
            backup.rename(output)
        raise
    if backup.exists():
        shutil.rmtree(backup)


def main() -> int:
    args = parse_args()
    binary = args.binary.resolve()
    output = args.output.resolve()
    headless = args.ghidra_dir / "support" / "analyzeHeadless"
    if not binary.is_file():
        raise SystemExit(f"missing binary: {binary}")
    if not headless.is_file():
        raise SystemExit(f"missing Ghidra headless launcher: {headless}")
    if args.limit is not None and args.limit < 1:
        raise SystemExit("--limit must be positive")
    if args.analysis_timeout < 1 or args.decompile_timeout < 1:
        raise SystemExit("timeouts must be positive")

    symbols = collect_symbols(binary, nm=args.nm, cxxfilt=args.cxxfilt)
    if args.contains:
        symbols = [
            symbol
            for symbol in symbols
            if args.contains in symbol["mangled"]
            or args.contains in symbol["demangled"]
        ]
    if args.limit is not None:
        symbols = symbols[: args.limit]
    if not symbols:
        raise SystemExit("no symbols matched the requested filters")

    output.parent.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(
        prefix=f"{output.name}-export-",
        dir=output.parent,
    ) as temporary:
        root = Path(temporary)
        home = root / "home"
        projects = root / "projects"
        staged = root / "corpus"
        manifest = root / "symbols.json"
        home.mkdir()
        projects.mkdir()
        manifest.write_text(
            json.dumps(symbols, indent=2) + "\n",
            encoding="utf-8",
        )

        env = os.environ.copy()
        env["HOME"] = str(home)
        java_options = env.get("JAVA_TOOL_OPTIONS", "")
        env["JAVA_TOOL_OPTIONS"] = (
            f"{java_options} -Duser.home={home}".strip()
        )
        command = (
            str(headless),
            str(projects),
            "SnailMobileExport",
            "-import",
            str(binary),
            "-analysisTimeoutPerFile",
            str(args.analysis_timeout),
            "-scriptPath",
            str(SCRIPT_DIR),
            "-postScript",
            "ExportItaniumSymbols.java",
            str(manifest),
            str(staged),
            str(args.decompile_timeout),
            "-deleteProject",
        )
        completed = subprocess.run(
            command,
            env=env,
            check=False,
            capture_output=True,
            text=True,
        )
        index_path = staged / "index.json"
        if completed.returncode != 0 or not index_path.is_file():
            detail = failure_log_tail(completed.stdout, completed.stderr)
            print("Ghidra batch export failed", file=sys.stderr)
            if completed.returncode != 0:
                print(
                    f"Ghidra launcher exit code: {completed.returncode}",
                    file=sys.stderr,
                )
            if not index_path.is_file():
                print(
                    "Ghidra did not write a corpus index",
                    file=sys.stderr,
                )
            if detail:
                print(detail, file=sys.stderr)
            return completed.returncode or 1

        index = json.loads(index_path.read_text(encoding="utf-8"))
        if index.get("symbol_count") != len(symbols):
            print(
                "Ghidra corpus index has the wrong symbol count",
                file=sys.stderr,
            )
            return 1
        failed = int(index.get("failed_count", 0))
        if args.strict and failed:
            print(
                f"Ghidra batch export left {failed} failed function(s); "
                "the previous corpus was preserved",
                file=sys.stderr,
            )
            return 1

        install_corpus(staged, output)
        print(
            f"exported {index['exported_count']}/{index['symbol_count']} "
            f"symbols to {output}"
        )
        if failed:
            print(f"failed functions recorded in index: {failed}")
        return 0


if __name__ == "__main__":
    raise SystemExit(main())
