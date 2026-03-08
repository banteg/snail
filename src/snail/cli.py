from __future__ import annotations

import argparse
import json
from pathlib import Path
from typing import Sequence

import msgspec

from .archive import extract_archive, parse_archive_index, summarize_archive
from .formats import parse_text_asset
from .recon import inspect_path
from .trace import build_trace_capture_plan, summarize_runtime_trace_file


def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
        prog="snail",
        description="Inspect the Snail Mail game bundle and reverse-engineering targets.",
    )
    subparsers = parser.add_subparsers(dest="command", required=True)

    inspect_parser = subparsers.add_parser(
        "inspect",
        help="Inspect a file or directory and print a JSON report.",
    )
    inspect_parser.add_argument(
        "path",
        nargs="?",
        default="artifacts/bin",
        help="File or directory to inspect (default: artifacts/bin).",
    )
    inspect_parser.add_argument(
        "--limit",
        type=int,
        default=8,
        help="Maximum offsets to report for each embedded signature.",
    )
    inspect_parser.add_argument(
        "--write",
        type=Path,
        help="Write the JSON report to this path in addition to stdout.",
    )

    archive_parser = subparsers.add_parser(
        "archive",
        help="Inspect or extract the SnailMail.dat archive.",
    )
    archive_subparsers = archive_parser.add_subparsers(dest="archive_command", required=True)

    manifest_parser = archive_subparsers.add_parser(
        "manifest",
        help="Print a JSON manifest for the decoded archive index.",
    )
    manifest_parser.add_argument(
        "path",
        nargs="?",
        default="artifacts/bin/SnailMail.dat",
        help="Path to the SnailMail.dat archive.",
    )
    manifest_parser.add_argument(
        "--limit",
        type=int,
        default=25,
        help="Maximum entries to include in the preview section.",
    )
    manifest_parser.add_argument(
        "--write",
        type=Path,
        help="Write the JSON manifest to this path in addition to stdout.",
    )

    extract_parser = archive_subparsers.add_parser(
        "extract",
        help="Extract and decode archive members to a directory.",
    )
    extract_parser.add_argument(
        "path",
        nargs="?",
        default="artifacts/bin/SnailMail.dat",
        help="Path to the SnailMail.dat archive.",
    )
    extract_parser.add_argument(
        "--output",
        type=Path,
        default=Path("artifacts/extracted/SnailMail.dat"),
        help="Directory that will receive decoded files.",
    )
    extract_parser.add_argument(
        "--prefix",
        help="Only extract entries whose archive path starts with this prefix.",
    )

    format_parser = subparsers.add_parser(
        "format",
        help="Parse Snail Mail text asset formats and print structured JSON.",
    )
    format_parser.add_argument(
        "path",
        help="Path to a decoded OBJECTS, SEGMENTS, or LEVELS text file.",
    )
    format_parser.add_argument(
        "--kind",
        choices=("auto", "object", "segment", "level"),
        default="auto",
        help="Force a format kind instead of auto-detecting from the path and contents.",
    )
    format_parser.add_argument(
        "--write",
        type=Path,
        help="Write the JSON report to this path in addition to stdout.",
    )

    trace_parser = subparsers.add_parser(
        "trace",
        help="Inspect or summarize Snail Mail runtime trace captures.",
    )
    trace_subparsers = trace_parser.add_subparsers(dest="trace_command", required=True)

    trace_summary_parser = trace_subparsers.add_parser(
        "summary",
        help="Summarize a Frida NDJSON runtime trace.",
    )
    trace_summary_parser.add_argument(
        "path",
        help="Path to a newline-delimited JSON trace capture.",
    )
    trace_summary_parser.add_argument(
        "--preview-limit",
        type=int,
        default=8,
        help="Maximum world positions to keep per event bucket preview.",
    )
    trace_summary_parser.add_argument(
        "--write",
        type=Path,
        help="Write the JSON summary to this path in addition to stdout.",
    )

    trace_plan_parser = trace_subparsers.add_parser(
        "plan",
        help="Rank extracted levels and segments for the next Frida runtime capture.",
    )
    trace_plan_parser.add_argument(
        "path",
        nargs="?",
        default="artifacts/extracted/SnailMail.dat",
        help="Path to the extracted Snail Mail asset tree.",
    )
    trace_plan_parser.add_argument(
        "--limit",
        type=int,
        default=8,
        help="Maximum results to keep in each recommendation list.",
    )
    trace_plan_parser.add_argument(
        "--write",
        type=Path,
        help="Write the JSON plan to this path in addition to stdout.",
    )

    return parser


def main(argv: Sequence[str] | None = None) -> int:
    parser = build_parser()
    args = parser.parse_args(argv)

    if args.command == "inspect":
        report = inspect_path(Path(args.path), signature_limit=args.limit)
        text = json.dumps(report, indent=2, sort_keys=True)
        if args.write is not None:
            args.write.parent.mkdir(parents=True, exist_ok=True)
            args.write.write_text(text + "\n", encoding="utf-8")
        print(text)
        return 0

    if args.command == "archive" and args.archive_command == "manifest":
        index = parse_archive_index(Path(args.path))
        manifest = summarize_archive(index, preview_limit=args.limit)
        text = json.dumps(manifest, indent=2, sort_keys=True)
        if args.write is not None:
            args.write.parent.mkdir(parents=True, exist_ok=True)
            args.write.write_text(text + "\n", encoding="utf-8")
        print(text)
        return 0

    if args.command == "archive" and args.archive_command == "extract":
        manifest = extract_archive(
            archive_path=Path(args.path),
            output_dir=args.output,
            prefix=args.prefix,
        )
        print(json.dumps(manifest, indent=2, sort_keys=True))
        return 0

    if args.command == "format":
        parsed = parse_text_asset(Path(args.path), kind=args.kind)
        builtins = msgspec.to_builtins(parsed)
        text = json.dumps(builtins, indent=2, sort_keys=True)
        if args.write is not None:
            args.write.parent.mkdir(parents=True, exist_ok=True)
            args.write.write_text(text + "\n", encoding="utf-8")
        print(text)
        return 0

    if args.command == "trace" and args.trace_command == "summary":
        summary = summarize_runtime_trace_file(Path(args.path), preview_limit=args.preview_limit)
        builtins = msgspec.to_builtins(summary)
        text = json.dumps(builtins, indent=2, sort_keys=True)
        if args.write is not None:
            args.write.parent.mkdir(parents=True, exist_ok=True)
            args.write.write_text(text + "\n", encoding="utf-8")
        print(text)
        return 0

    if args.command == "trace" and args.trace_command == "plan":
        plan = build_trace_capture_plan(Path(args.path), limit=args.limit)
        builtins = msgspec.to_builtins(plan)
        text = json.dumps(builtins, indent=2, sort_keys=True)
        if args.write is not None:
            args.write.parent.mkdir(parents=True, exist_ok=True)
            args.write.write_text(text + "\n", encoding="utf-8")
        print(text)
        return 0

    parser.error(f"Unhandled command: {args.command}")
    return 2
