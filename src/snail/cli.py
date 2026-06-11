from __future__ import annotations

import argparse
import difflib
import json
from pathlib import Path
from typing import Sequence

import msgspec

from .archive import extract_archive, parse_archive_index, summarize_archive
from .formats import parse_text_asset
from .match import (
    collect_scratch_statuses,
    render_status_markdown,
    render_status_table,
    run_match,
)
from .recon import inspect_path, sha256_bytes
from .reflexive import decrypt_reflexive_wrapper_config, unwrap_reflexive_executable
from .screenshots import (
    DEFAULT_SCREENSHOT_COMPARE_OUTPUT_DIR,
    compare_screenshots,
    parse_scale_search,
)
from .symbols import (
    DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH,
    REPO_ROOT,
    load_function_symbol_manifest,
    summarize_function_symbol_manifest,
    write_function_symbol_manifest,
)
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

    unwrap_parser = subparsers.add_parser(
        "unwrap",
        help="Decrypt a Reflexive-wrapped executable image and optionally compare it.",
    )
    unwrap_parser.add_argument(
        "--wrapped",
        type=Path,
        default=Path("artifacts/bin/SnailMail.RWG"),
        help="Path to the encrypted wrapped PE image.",
    )
    unwrap_parser.add_argument(
        "--config",
        type=Path,
        default=Path("artifacts/bin/ReflexiveArcade/RAW_002.wdt"),
        help="Path to the encrypted Reflexive wrapper config blob.",
    )
    unwrap_parser.add_argument(
        "--output",
        type=Path,
        default=Path("artifacts/bin/SnailMail_unwrapped.exe"),
        help="Where to write the decrypted PE image.",
    )
    unwrap_parser.add_argument(
        "--compare",
        type=Path,
        help="Optional path to a PE image to compare against the decrypted output.",
    )
    unwrap_parser.add_argument(
        "--write-config",
        type=Path,
        help="Optional path to write the decrypted RAW_002.wdt text.",
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

    symbols_parser = subparsers.add_parser(
        "symbols",
        help="Validate and summarize the tracked gameplay function symbol manifest.",
    )
    symbols_parser.add_argument(
        "--manifest",
        type=Path,
        default=DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH,
        help="Path to the tracked gameplay function symbol manifest.",
    )
    symbols_parser.add_argument(
        "--write",
        type=Path,
        help="Write the normalized manifest JSON to this path in addition to printing a summary.",
    )

    screenshots_parser = subparsers.add_parser(
        "screenshots",
        help="Compare rendered screenshots against reference captures.",
    )
    screenshots_subparsers = screenshots_parser.add_subparsers(dest="screenshots_command", required=True)

    screenshots_compare_parser = screenshots_subparsers.add_parser(
        "compare",
        help="Normalize two screenshots to a common size, write diff artifacts, and print metrics.",
    )
    screenshots_compare_parser.add_argument(
        "render",
        type=Path,
        help="Path to the current port screenshot.",
    )
    screenshots_compare_parser.add_argument(
        "reference",
        type=Path,
        help="Path to the original reference screenshot.",
    )
    screenshots_compare_parser.add_argument(
        "--compare-size",
        default="reference",
        help="Comparison size: reference, render, or WIDTHxHEIGHT (default: reference).",
    )
    screenshots_compare_parser.add_argument(
        "--search-scale",
        help="Optional scale search range in START:STOP:STEP form, for example 0.95:1.05:0.01.",
    )
    screenshots_compare_parser.add_argument(
        "--search-offset",
        type=int,
        default=0,
        help="Optional integer pixel search radius for x/y offsets after normalization.",
    )
    screenshots_compare_parser.add_argument(
        "--output-dir",
        type=Path,
        default=DEFAULT_SCREENSHOT_COMPARE_OUTPUT_DIR,
        help="Directory that will receive the normalized and diff images.",
    )
    screenshots_compare_parser.add_argument(
        "--prefix",
        help="Optional filename prefix for generated artifacts.",
    )
    screenshots_compare_parser.add_argument(
        "--write",
        type=Path,
        help="Write the JSON summary to this path in addition to stdout.",
    )

    match_parser = subparsers.add_parser(
        "match",
        help="Matching-islands workflow: diff scratches against the original image.",
    )
    match_subparsers = match_parser.add_subparsers(dest="match_command", required=True)

    match_diff_parser = match_subparsers.add_parser(
        "diff",
        help="Diff a compiled scratch object's function against the original image.",
    )
    match_diff_parser.add_argument(
        "obj",
        type=Path,
        help="Path to the VC6 COFF object compiled from the candidate scratch.",
    )
    match_diff_parser.add_argument(
        "function",
        help="Curated function name from the symbol manifest.",
    )
    match_diff_parser.add_argument(
        "--symbol",
        help="Override the object symbol to extract (default: match the function name).",
    )
    match_diff_parser.add_argument(
        "--image",
        type=Path,
        help="Path to the original image (default: the manifest primary target).",
    )
    match_diff_parser.add_argument(
        "--manifest",
        type=Path,
        default=DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH,
        help="Path to the tracked gameplay function symbol manifest.",
    )
    match_diff_parser.add_argument(
        "--end",
        type=lambda value: int(value, 0),
        help="Explicit end VA when the next curated function overshoots the extent.",
    )
    match_diff_parser.add_argument(
        "--full",
        action="store_true",
        help="Print both normalized listings side by side instead of only the diff.",
    )

    match_status_parser = match_subparsers.add_parser(
        "status",
        help="Compile all scratches and print a match dashboard.",
    )
    match_status_parser.add_argument(
        "--image",
        type=Path,
        help="Path to the original image (default: the manifest primary target).",
    )
    match_status_parser.add_argument(
        "--manifest",
        type=Path,
        default=DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH,
        help="Path to the tracked gameplay function symbol manifest.",
    )
    match_status_parser.add_argument(
        "--write",
        type=Path,
        help="Write the markdown dashboard to this path in addition to stdout.",
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

    if args.command == "unwrap":
        image = unwrap_reflexive_executable(args.wrapped, args.config)
        args.output.parent.mkdir(parents=True, exist_ok=True)
        args.output.write_bytes(image)

        report: dict[str, object] = {
            "wrapped": str(args.wrapped),
            "config": str(args.config),
            "output": str(args.output),
            "output_sha256": sha256_bytes(image),
            "output_size": len(image),
        }

        config_text = decrypt_reflexive_wrapper_config(args.wrapped, args.config)
        if args.write_config is not None:
            args.write_config.parent.mkdir(parents=True, exist_ok=True)
            args.write_config.write_text(config_text, encoding="utf-8")
            report["config_output"] = str(args.write_config)

        if args.compare is not None:
            compare_bytes = args.compare.read_bytes()
            differing_offsets = [
                index
                for index, (lhs, rhs) in enumerate(zip(image, compare_bytes))
                if lhs != rhs
            ]
            size_mismatch = len(image) != len(compare_bytes)
            report["compare"] = {
                "path": str(args.compare),
                "sha256": sha256_bytes(compare_bytes),
                "size": len(compare_bytes),
                "matches": not size_mismatch and not differing_offsets,
                "diff_count": len(differing_offsets),
                "size_mismatch": size_mismatch,
                "first_differences": differing_offsets[:16],
            }

        print(json.dumps(report, indent=2, sort_keys=True))
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

    if args.command == "symbols":
        manifest = load_function_symbol_manifest(args.manifest)
        if args.write is not None:
            write_function_symbol_manifest(manifest, args.write)
        summary = summarize_function_symbol_manifest(manifest, path=args.manifest)
        if args.write is not None:
            summary["normalized_output"] = str(args.write)
        print(json.dumps(summary, indent=2, sort_keys=True))
        return 0

    if args.command == "screenshots" and args.screenshots_command == "compare":
        summary = compare_screenshots(
            args.render,
            args.reference,
            compare_size_spec=args.compare_size,
            output_dir=args.output_dir,
            scale_search=parse_scale_search(args.search_scale) if args.search_scale else None,
            offset_search=args.search_offset,
            prefix=args.prefix,
        )
        text = json.dumps(summary, indent=2, sort_keys=True)
        if args.write is not None:
            args.write.parent.mkdir(parents=True, exist_ok=True)
            args.write.write_text(text + "\n", encoding="utf-8")
        print(text)
        return 0

    if args.command == "match" and args.match_command == "status":
        manifest = load_function_symbol_manifest(args.manifest)
        image_path = args.image or REPO_ROOT / manifest.primary_target
        statuses = collect_scratch_statuses(manifest, image_path)
        print(render_status_table(statuses))
        if args.write is not None:
            args.write.write_text(render_status_markdown(statuses), encoding="utf-8")
        return 0

    if args.command == "match" and args.match_command == "diff":
        manifest = load_function_symbol_manifest(args.manifest)
        image_path = args.image or REPO_ROOT / manifest.primary_target
        result = run_match(
            obj_path=args.obj,
            function_name=args.function,
            image_path=image_path,
            manifest=manifest,
            symbol_name=args.symbol,
            end_va=args.end,
        )
        print(f"match: {result.ratio:.2%}")
        print(f"target: {len(result.target_lines)} insns, candidate: {len(result.candidate_lines)} insns")
        if args.full:
            width = max((len(line) for line in result.target_lines), default=0)
            matcher = difflib.SequenceMatcher(
                a=result.target_lines, b=result.candidate_lines, autojunk=False
            )
            for tag, a0, a1, b0, b1 in matcher.get_opcodes():
                for offset in range(max(a1 - a0, b1 - b0)):
                    left = result.target_lines[a0 + offset] if a0 + offset < a1 else ""
                    right = result.candidate_lines[b0 + offset] if b0 + offset < b1 else ""
                    marker = " " if tag == "equal" else "|"
                    print(f"{left:<{width}} {marker} {right}")
        else:
            for line in result.diff_lines:
                print(line)
        return 0 if result.ratio == 1.0 else 1

    parser.error(f"Unhandled command: {args.command}")
    return 2
