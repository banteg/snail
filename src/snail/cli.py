from __future__ import annotations

import argparse
from collections import defaultdict
import difflib
import json
from pathlib import Path
from typing import Sequence

import msgspec

from .archive import extract_archive, parse_archive_index, summarize_archive
from .formats import parse_text_asset
from .match import (
    IDIOM_CASES,
    IDIOM_CASES_BY_NAME,
    compile_idiom_case,
    collect_masked_operand_issues,
    collect_scratch_statuses,
    diff_regions,
    manifest_cluster_totals,
    render_status_markdown,
    render_status_table,
    run_match,
    run_match_dump,
    type_consolidation_findings,
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


def _format_masked_reference_list(references) -> str:
    if not references:
        return "-"
    return ", ".join(
        f"{reference.kind}{reference.operand_index}:{reference.text}"
        for reference in references
    )


def _masked_reference_payload(reference) -> dict:
    return {
        "operand_index": reference.operand_index,
        "kind": reference.kind,
        "source": reference.source,
        "value": reference.value,
        "text": reference.text,
        "key": reference.key,
        "alternate_keys": list(reference.alternate_keys),
        "explained": reference.explained,
    }


def _audit_issue_group_key(issue) -> tuple:
    entry = issue.entry
    target = tuple(
        (ref.text, ref.key, ref.alternate_keys, ref.explained)
        for ref in entry.target_references
    )
    candidate = tuple(
        (ref.text, ref.key, ref.alternate_keys, ref.explained)
        for ref in entry.candidate_references
    )
    return (entry.status, target, candidate)


def _print_masked_audit_issues(issues, *, limit: int | None = None) -> None:
    if not issues:
        print("masked audit issues: none")
        return
    grouped = defaultdict(list)
    for issue in issues:
        grouped[_audit_issue_group_key(issue)].append(issue)
    print(
        "masked audit issues: "
        f"{len(issues)} entries across "
        f"{len({issue.config.function for issue in issues})} scratches, "
        f"{len(grouped)} grouped reference pair(s)"
    )
    printed = 0
    for (_status, _target, _candidate), group in sorted(
        grouped.items(),
        key=lambda item: (-len(item[1]), item[0]),
    ):
        if limit is not None and printed >= limit:
            remaining = len(grouped) - printed
            if remaining > 0:
                print(f"\n... {remaining} group(s) omitted by --limit")
            return
        first = group[0].entry
        print()
        print(f"{first.status} ({len(group)}):")
        print(f"  target: {_format_masked_reference_list(first.target_references)}")
        print(f"  candidate: {_format_masked_reference_list(first.candidate_references)}")
        for issue in group[:5]:
            entry = issue.entry
            print(
                "  "
                f"{issue.config.function} 0x{issue.address:x} "
                f"match {issue.ratio:.2%} "
                f"target +0x{entry.target_offset:x} "
                f"candidate +0x{entry.candidate_offset:x}: "
                f"{entry.instruction}"
            )
        if len(group) > 5:
            print(f"  ... {len(group) - 5} more")
        printed += 1


def _print_masked_operand_audit(audit) -> None:
    if not audit.entries:
        print("masked operands: none")
        return
    print(
        "masked operands: "
        f"{audit.ok_count} ok, "
        f"{audit.unresolved_count} unresolved, "
        f"{audit.mismatch_count} mismatch"
    )
    problem_entries = [entry for entry in audit.entries if entry.status != "ok"]
    if not problem_entries:
        return
    print("masked operand audit:")
    for entry in problem_entries:
        print(
            f"  {entry.status}: target[{entry.target_index}] "
            f"0x{entry.target_address:x} (off +0x{entry.target_offset:x}) "
            f"candidate[{entry.candidate_index}] (off +0x{entry.candidate_offset:x})"
        )
        print(f"    insn: {entry.instruction}")
        print(f"    target: {_format_masked_reference_list(entry.target_references)}")
        print(f"    candidate: {_format_masked_reference_list(entry.candidate_references)}")


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
    match_diff_parser.add_argument(
        "--regions",
        action="store_true",
        help="Print localized mismatch region summaries before the diff/listing.",
    )
    match_diff_parser.add_argument(
        "--region-context",
        type=int,
        default=4,
        help="Instruction context to include around each mismatch region (default: 4).",
    )
    match_diff_parser.add_argument(
        "--max-regions",
        type=int,
        help="Maximum number of mismatch regions to print.",
    )

    match_dump_parser = match_subparsers.add_parser(
        "dump",
        help="Print addressed normalized target/candidate instruction listings.",
    )
    match_dump_parser.add_argument(
        "obj",
        type=Path,
        help="Path to the VC6 COFF object compiled from the candidate scratch.",
    )
    match_dump_parser.add_argument(
        "function",
        help="Curated function name from the symbol manifest.",
    )
    match_dump_parser.add_argument(
        "--symbol",
        help="Override the object symbol to extract (default: match the function name).",
    )
    match_dump_parser.add_argument(
        "--image",
        type=Path,
        help="Path to the original image (default: the manifest primary target).",
    )
    match_dump_parser.add_argument(
        "--manifest",
        type=Path,
        default=DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH,
        help="Path to the tracked gameplay function symbol manifest.",
    )
    match_dump_parser.add_argument(
        "--end",
        type=lambda value: int(value, 0),
        help="Explicit end VA when the next curated function overshoots the extent.",
    )
    match_dump_parser.add_argument(
        "--side",
        choices=("both", "target", "candidate"),
        default="both",
        help="Which listing to print (default: both).",
    )
    match_dump_parser.add_argument(
        "--start-offset",
        type=lambda value: int(value, 0),
        default=0,
        help="Only print instructions at or after this function-relative offset.",
    )
    match_dump_parser.add_argument(
        "--end-offset",
        type=lambda value: int(value, 0),
        help="Only print instructions before this function-relative offset.",
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

    match_audit_parser = match_subparsers.add_parser(
        "audit",
        help="Print grouped masked-operand audit issues across scratches.",
    )
    match_audit_parser.add_argument(
        "--image",
        type=Path,
        help="Path to the original image (default: the manifest primary target).",
    )
    match_audit_parser.add_argument(
        "--manifest",
        type=Path,
        default=DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH,
        help="Path to the tracked gameplay function symbol manifest.",
    )
    match_audit_parser.add_argument(
        "--status",
        choices=("problem", "unresolved", "mismatch", "all"),
        default="problem",
        help="Which audit entries to include (default: problem).",
    )
    match_audit_parser.add_argument(
        "--exact-only",
        action="store_true",
        help="Only report audit issues from scratches with a 100%% normalized match.",
    )
    match_audit_parser.add_argument(
        "--limit",
        type=int,
        help="Maximum grouped reference pairs to print.",
    )
    match_audit_parser.add_argument(
        "--json",
        action="store_true",
        help="Print detailed audit entries as JSON.",
    )

    match_idioms_parser = match_subparsers.add_parser(
        "idioms",
        help="Compile small VC6 source-idiom probes and print normalized asm.",
    )
    match_idioms_parser.add_argument(
        "cases",
        nargs="*",
        help="Specific idiom case names to compile (default: all cases).",
    )
    match_idioms_parser.add_argument(
        "--list",
        action="store_true",
        help="List available idiom cases without compiling.",
    )
    match_idioms_parser.add_argument(
        "--compiler",
        default="msvc6.5",
        help="Compiler bundle to use (default: msvc6.5).",
    )
    match_idioms_parser.add_argument(
        "--cflags",
        default="/O2 /G5 /W3",
        help="Compiler flags to use (default: /O2 /G5 /W3).",
    )

    match_types_parser = match_subparsers.add_parser(
        "types",
        help="Report scratch-local type definitions that are ready or not ready to consolidate.",
    )
    match_types_parser.add_argument(
        "names",
        nargs="*",
        help="Specific type names to report (default: all findings).",
    )
    match_types_parser.add_argument(
        "--threshold",
        type=int,
        default=2,
        help="Minimum scratch-local definition count before reporting a type (default: 2).",
    )
    match_types_parser.add_argument(
        "--paths",
        action="store_true",
        help="Print paths contributing to each type finding.",
    )
    match_types_parser.add_argument(
        "--json",
        action="store_true",
        help="Print findings as JSON.",
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
        totals = manifest_cluster_totals(manifest, image_path, statuses)
        type_findings = type_consolidation_findings()
        print(render_status_table(statuses, totals, type_findings=type_findings))
        if args.write is not None:
            args.write.write_text(
                render_status_markdown(statuses, totals, type_findings=type_findings),
                encoding="utf-8",
            )
        return 0

    if args.command == "match" and args.match_command == "audit":
        manifest = load_function_symbol_manifest(args.manifest)
        image_path = args.image or REPO_ROOT / manifest.primary_target
        if args.status == "all":
            audit_statuses = frozenset(("ok", "unresolved", "mismatch"))
        elif args.status == "problem":
            audit_statuses = frozenset(("unresolved", "mismatch"))
        else:
            audit_statuses = frozenset((args.status,))
        issues = collect_masked_operand_issues(
            manifest,
            image_path,
            statuses=audit_statuses,
            exact_only=args.exact_only,
        )
        if args.json:
            print(
                json.dumps(
                    [
                        {
                            "function": issue.config.function,
                            "scratch": str(issue.config.directory),
                            "address": issue.address,
                            "match": issue.ratio,
                            "status": issue.entry.status,
                            "instruction": issue.entry.instruction,
                            "target_index": issue.entry.target_index,
                            "candidate_index": issue.entry.candidate_index,
                            "target_offset": issue.entry.target_offset,
                            "candidate_offset": issue.entry.candidate_offset,
                            "target_address": issue.entry.target_address,
                            "candidate_address": issue.entry.candidate_address,
                            "target_references": [
                                _masked_reference_payload(ref)
                                for ref in issue.entry.target_references
                            ],
                            "candidate_references": [
                                _masked_reference_payload(ref)
                                for ref in issue.entry.candidate_references
                            ],
                        }
                        for issue in issues
                    ],
                    indent=2,
                    sort_keys=True,
                )
            )
            return 0
        _print_masked_audit_issues(issues, limit=args.limit)
        return 0

    if args.command == "match" and args.match_command == "idioms":
        if args.list:
            for case in IDIOM_CASES:
                print(f"{case.name}: {case.description}")
            return 0
        case_names = args.cases or [case.name for case in IDIOM_CASES]
        unknown = [name for name in case_names if name not in IDIOM_CASES_BY_NAME]
        if unknown:
            parser.error(f"unknown idiom case(s): {', '.join(unknown)}")
        for index, name in enumerate(case_names):
            if index:
                print()
            result = compile_idiom_case(
                IDIOM_CASES_BY_NAME[name],
                compiler=args.compiler,
                cflags=args.cflags,
            )
            print(f"== {result.case.name} ==")
            print(result.case.description)
            print(f"object: {result.object_path}")
            for line in result.instructions:
                print(line)
        return 0

    if args.command == "match" and args.match_command == "types":
        findings = type_consolidation_findings(
            threshold=args.threshold,
            names=set(args.names) if args.names else None,
        )
        if args.json:
            print(
                json.dumps(
                    [
                        {
                            "name": finding.name,
                            "status": finding.status,
                            "scratch_count": finding.scratch_count,
                            "header_count": finding.header_count,
                            "signature_count": finding.signature_count,
                            "recommendation": finding.recommendation,
                            "paths": [str(path) for path in finding.paths],
                        }
                        for finding in findings
                    ],
                    indent=2,
                    sort_keys=True,
                )
            )
            return 0
        if not findings:
            print("no consolidation candidates")
            return 0
        for finding in findings:
            print(
                f"{finding.status:9} {finding.name}: "
                f"{finding.scratch_count} scratch, {finding.header_count} header, "
                f"{finding.signature_count} scratch signature(s) - {finding.recommendation}"
            )
            if args.paths:
                for path in finding.paths:
                    print(f"  {path}")
        return 0

    if args.command == "match" and args.match_command == "dump":
        if args.end_offset is not None and args.end_offset < args.start_offset:
            parser.error("--end-offset must be greater than or equal to --start-offset")
        manifest = load_function_symbol_manifest(args.manifest)
        image_path = args.image or REPO_ROOT / manifest.primary_target
        dump = run_match_dump(
            obj_path=args.obj,
            function_name=args.function,
            image_path=image_path,
            manifest=manifest,
            symbol_name=args.symbol,
            end_va=args.end,
        )

        def selected(lines):
            return [
                line
                for line in lines
                if line.offset >= args.start_offset
                and (args.end_offset is None or line.offset < args.end_offset)
            ]

        def print_listing(title: str, lines) -> None:
            print(f"== {title} ==")
            for line in selected(lines):
                print(f"{line.offset:04x} {line.address:08x}  {line.text}")

        if args.side in ("both", "target"):
            print_listing("target", dump.target_lines)
        if args.side == "both":
            print()
        if args.side in ("both", "candidate"):
            print_listing("candidate", dump.candidate_lines)
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
        print(f"prefix: {result.prefix_instructions}/{len(result.target_lines)} target insns")
        _print_masked_operand_audit(result.masked_operand_audit)
        if result.first_target_mismatch is not None or result.first_candidate_mismatch is not None:
            target = result.first_target_mismatch or "<end>"
            candidate = result.first_candidate_mismatch or "<end>"
            print(f"first mismatch: target[{result.prefix_instructions}] {target}")
            print(f"                candidate[{result.prefix_instructions}] {candidate}")
        if args.regions:
            regions = diff_regions(
                result,
                context=args.region_context,
                max_regions=args.max_regions,
            )
            print("regions:")
            if not regions:
                print("  none")
            for index, region in enumerate(regions, start=1):
                print(
                    f"  {index}. target[{region.target_span}] "
                    f"candidate[{region.candidate_span}] "
                    f"match {region.ratio:.2%}, "
                    f"prefix {region.prefix_instructions}/"
                    f"{region.target_end - region.target_start}, "
                    f"delta {region.instruction_delta:+d}, "
                    f"changed {region.changed_target_instructions}/"
                    f"{region.changed_candidate_instructions}"
                )
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
        return 0 if result.ratio == 1.0 and result.masked_operand_audit.problem_count == 0 else 1

    parser.error(f"Unhandled command: {args.command}")
    return 2
