from __future__ import annotations

import argparse
import json
from pathlib import Path
from typing import Sequence

from .archive import extract_archive, parse_archive_index, summarize_archive
from .recon import inspect_path


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

    parser.error(f"Unhandled command: {args.command}")
    return 2
