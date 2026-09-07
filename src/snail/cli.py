from __future__ import annotations

import argparse
import difflib
import json
import sys
from collections import defaultdict
from collections.abc import Sequence
from datetime import UTC, datetime
from pathlib import Path

import msgspec

from . import (
    match_contracts,
    match_experiments,
    match_export,
    match_history,
    match_mutation,
    match_report,
)
from .archive import extract_archive, parse_archive_index, summarize_archive
from .formats import parse_text_asset
from .match import (
    DEFAULT_MATCH_JOBS,
    DEFAULT_MATCH_ROOT,
    IDIOM_CASES,
    IDIOM_CASES_BY_NAME,
    RECOVERY_VALUES,
    RESIDUAL_VALUES,
    TRIAGE_SORTS,
    TRIAGE_STATES,
    collect_masked_operand_issues,
    collect_scratch_statuses,
    collect_triage_rows,
    compile_idiom_case,
    compiler_listing_payload,
    diff_regions,
    evaluate_source_probe,
    generate_compiler_listing,
    lint_extern_declarations,
    load_scratch_config,
    manifest_cluster_totals,
    match_result_payload,
    probe_result_payload,
    render_compiler_listing_result,
    render_probe_result,
    render_status_markdown,
    render_status_table,
    render_triage_summary,
    render_triage_table,
    resolve_scratch_directory,
    run_match,
    run_match_dump,
    run_scratch_match,
    scratch_dependency_sha256,
    scratch_experiment_epoch,
    scratch_experiment_epochs,
    sort_triage_rows,
    triage_row_payload,
    triage_summary_payload,
    type_consolidation_findings,
)
from .mobile import (
    DEFAULT_ANDROID_CORPUS_ROOT,
    DEFAULT_IOS_CORPUS_ROOT,
    DEFAULT_MOBILE_CROSSWALK_PATH,
    corpus_function_path,
    load_json,
    resolve_corpus_symbols,
    windows_decompile_path,
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


def _print_masked_audit_failures(failures) -> None:
    if not failures:
        return
    print()
    print(f"audit failures: {len(failures)} scratch(es) could not be audited")
    for failure in failures:
        print(f"  {failure.config.function} 0x{failure.address:x}: {failure.error}")


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
    for printed, ((_status, _target, _candidate), group) in enumerate(
        sorted(
            grouped.items(),
            key=lambda item: (-len(item[1]), item[0]),
        )
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
            locations = []
            if entry.target_offset is not None:
                locations.append(f"target +0x{entry.target_offset:x}")
            if entry.candidate_offset is not None:
                locations.append(f"candidate +0x{entry.candidate_offset:x}")
            print(
                "  "
                f"{issue.config.function} 0x{issue.address:x} "
                f"match {issue.ratio:.2%} "
                f"{' '.join(locations)}: "
                f"{entry.instruction}"
            )
        if len(group) > 5:
            print(f"  ... {len(group) - 5} more")


def _print_masked_operand_audit(audit) -> None:
    if not audit.entries:
        print("masked operands: none")
        return
    print(
        "masked operands: "
        f"{audit.ok_count} ok, "
        f"{audit.unresolved_count} unresolved, "
        f"{audit.mismatch_count} mismatch, "
        f"{audit.unaudited_count} unaudited"
    )
    problem_entries = [entry for entry in audit.entries if entry.status != "ok"]
    if not problem_entries:
        return
    print("masked operand audit:")
    for entry in problem_entries:
        locations = []
        if entry.target_index is not None:
            locations.append(
                f"target[{entry.target_index}] "
                f"0x{entry.target_address:x} (off +0x{entry.target_offset:x})"
            )
        if entry.candidate_index is not None:
            locations.append(
                f"candidate[{entry.candidate_index}] "
                f"(off +0x{entry.candidate_offset:x})"
            )
        print(f"  {entry.status}: {' '.join(locations)}")
        print(f"    insn: {entry.instruction}")
        print(f"    target: {_format_masked_reference_list(entry.target_references)}")
        print(f"    candidate: {_format_masked_reference_list(entry.candidate_references)}")


def _positive_int(value: str) -> int:
    parsed = int(value)
    if parsed < 1:
        raise argparse.ArgumentTypeError("must be a positive integer")
    return parsed


def _non_negative_int(value: str) -> int:
    parsed = int(value)
    if parsed < 0:
        raise argparse.ArgumentTypeError("must be a non-negative integer")
    return parsed


def _parse_csv(value: str | None) -> set[str] | None:
    if value is None:
        return None
    parsed = {part.strip() for part in value.split(",") if part.strip()}
    return parsed or None


def _display_repo_path(path: Path) -> str:
    try:
        return str(path.relative_to(REPO_ROOT))
    except ValueError:
        return str(path)


def _print_source_section(
    title: str,
    path: Path,
    *,
    paths_only: bool,
    metadata: Sequence[str] = (),
) -> bool:
    print(f"== {title} ==")
    print(f"path: {_display_repo_path(path)}")
    for line in metadata:
        print(line)
    if not path.is_file():
        print("status: unavailable")
        return False
    if not paths_only:
        print()
        print(path.read_text(encoding="utf-8").rstrip())
    return True


def _mobile_backed_pending_rows(manifest, statuses, crosswalk):
    functions_by_name = {
        function.name: function for function in manifest.functions
    }
    entries_by_name = {
        entry["windows_name"]: entry
        for entry in crosswalk.get("entries", ())
    }
    rows = []
    for status in statuses:
        function = functions_by_name.get(status.config.function)
        if (
            function is None
            or not function.is_port_relevant
            or status.state == "match"
            or status.ratio is None
        ):
            continue
        entry = entries_by_name.get(function.name)
        if entry is None or entry.get("status") != "verified":
            continue
        android_bodies = int(entry.get("android_body_count", 0) or 0)
        ios_bodies = int(entry.get("ios_body_count", 0) or 0)
        if android_bodies == 0 and ios_bodies == 0:
            continue
        fuzzy_gap = status.target_size * (1.0 - status.ratio)
        rows.append(
            (
                fuzzy_gap,
                status.ratio,
                status.target_size,
                android_bodies,
                ios_bodies,
                entry.get("confidence") or "-",
                entry.get("source_object") or "-",
                function.name,
            )
        )
    rows.sort(key=lambda row: (-row[0], row[1], row[-1]))
    return rows


def _print_mobile_backed_pending(rows, *, limit: int) -> None:
    print(
        "verified mobile bodies for non-proof Windows targets: "
        f"{len(rows)}"
    )
    print(
        "fuzzy-gap  match    bytes  bodies  confidence  source object       "
        "function"
    )
    for (
        fuzzy_gap,
        ratio,
        target_size,
        android_bodies,
        ios_bodies,
        confidence,
        source_object,
        function,
    ) in rows[:limit]:
        bodies = "/".join(
            part
            for count, part in (
                (android_bodies, f"A{android_bodies}"),
                (ios_bodies, f"I{ios_bodies}"),
            )
            if count
        )
        print(
            f"{fuzzy_gap:9.1f}  {ratio:6.2%}  {target_size:5d}  "
            f"{bodies:6}  {confidence:10}  {source_object:18}  "
            f"{function}"
        )


def _add_scratch_directory_arguments(parser: argparse.ArgumentParser) -> None:
    parser.add_argument(
        "directory",
        help="Scratch directory path, or its basename under --match-root/scratches.",
    )
    parser.add_argument(
        "--match-root",
        type=Path,
        default=DEFAULT_MATCH_ROOT,
        help="Path to the tools/match root.",
    )
    parser.set_defaults(_scratch_directory=True)


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
        help="Path to the candidate screenshot.",
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

    match_mobile_parser = match_subparsers.add_parser(
        "mobile",
        help=(
            "Show one Windows decompile beside verified mobile source bodies, "
            "or rank mobile-backed non-proof targets."
        ),
    )
    match_mobile_parser.add_argument(
        "function",
        nargs="?",
        help=(
            "Curated Windows function name or alias from the symbol manifest; "
            "omit with --pending."
        ),
    )
    match_mobile_parser.add_argument(
        "--pending",
        action="store_true",
        help=(
            "Rank non-proof Windows targets with verified mobile bodies by "
            "their current fuzzy byte gap."
        ),
    )
    match_mobile_parser.add_argument(
        "--limit",
        type=_positive_int,
        default=25,
        help="Maximum pending targets to show (default: 25).",
    )
    match_mobile_parser.add_argument(
        "--port",
        choices=("both", "android", "ios"),
        default="both",
        help="Mobile port to show (default: both).",
    )
    match_mobile_parser.add_argument(
        "--windows-tool",
        choices=("binja", "ida", "none"),
        default="binja",
        help="Windows decompile corpus to show (default: binja).",
    )
    match_mobile_parser.add_argument(
        "--paths-only",
        action="store_true",
        help="Print source paths without dumping decompiler output.",
    )
    match_mobile_parser.add_argument(
        "--candidate-limit",
        type=_positive_int,
        default=5,
        help="Maximum unverified mobile candidates to list (default: 5).",
    )
    match_mobile_parser.add_argument(
        "--manifest",
        type=Path,
        default=DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH,
        help="Path to the tracked gameplay function symbol manifest.",
    )
    match_mobile_parser.add_argument(
        "--crosswalk",
        type=Path,
        default=DEFAULT_MOBILE_CROSSWALK_PATH,
        help="Path to the generated complete mobile crosswalk.",
    )
    match_mobile_parser.add_argument(
        "--android-index",
        type=Path,
        default=DEFAULT_ANDROID_CORPUS_ROOT / "index.json",
        help="Path to the Android decompile corpus index.",
    )
    match_mobile_parser.add_argument(
        "--ios-index",
        type=Path,
        default=DEFAULT_IOS_CORPUS_ROOT / "index.json",
        help="Path to the iOS decompile corpus index.",
    )
    match_mobile_parser.add_argument(
        "--image",
        type=Path,
        help=(
            "Path to the original image used by --pending "
            "(default: the manifest primary target)."
        ),
    )
    match_mobile_parser.add_argument(
        "-j",
        "--jobs",
        type=_positive_int,
        default=DEFAULT_MATCH_JOBS,
        help=(
            "Maximum concurrent scratch jobs needed by --pending "
            f"(default: {DEFAULT_MATCH_JOBS})."
        ),
    )

    match_triage_parser = match_subparsers.add_parser(
        "triage",
        help=(
            "Rank native functions by address-keyed match, experiment, "
            "and mobile evidence."
        ),
    )
    match_triage_parser.add_argument(
        "--image",
        type=Path,
        help="Path to the original image (default: the manifest primary target).",
    )
    match_triage_parser.add_argument(
        "--manifest",
        type=Path,
        default=DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH,
        help="Path to the tracked gameplay function symbol manifest.",
    )
    match_triage_parser.add_argument(
        "--crosswalk",
        type=Path,
        default=DEFAULT_MOBILE_CROSSWALK_PATH,
        help="Path to the generated complete mobile crosswalk.",
    )
    match_triage_parser.add_argument(
        "--match-root",
        type=Path,
        default=DEFAULT_MATCH_ROOT,
        help="Path to the tools/match root.",
    )
    match_triage_parser.add_argument(
        "--scope",
        choices=("port", "all"),
        default="port",
        help="Function ownership scope (default: port).",
    )
    match_triage_parser.add_argument(
        "--state",
        help="Comma-separated states: match,audit,wip,error,missing.",
    )
    match_triage_parser.add_argument(
        "--recovery",
        help=(
            "Comma-separated recovery states: exact, semantic-complete, "
            "incomplete, unspecified,missing."
        ),
    )
    match_triage_parser.add_argument(
        "--residual",
        help="Comma-separated residual kinds: analysis,compiler,references.",
    )
    match_triage_parser.add_argument(
        "--mobile",
        choices=("any", "verified", "without-verified"),
        default="any",
        help="Filter by verified mobile-source evidence (default: any).",
    )
    match_triage_parser.add_argument(
        "--min-bytes",
        type=_non_negative_int,
        default=0,
        help="Minimum native function size (default: 0).",
    )
    match_triage_parser.add_argument(
        "--sort",
        choices=tuple(sorted(TRIAGE_SORTS)),
        default="fuzzy-gap",
        help="Row ordering (default: fuzzy-gap).",
    )
    match_triage_parser.add_argument(
        "--limit",
        type=_positive_int,
        help="Maximum rows to show.",
    )
    match_triage_parser.add_argument(
        "--summary-only",
        action="store_true",
        help="Print aggregate coverage only.",
    )
    match_triage_parser.add_argument(
        "--json",
        action="store_true",
        help="Print machine-readable JSON.",
    )
    match_triage_parser.add_argument(
        "--check",
        action="store_true",
        help="Exit non-zero if any scratch fails to evaluate.",
    )
    match_triage_parser.add_argument(
        "-j",
        "--jobs",
        type=_positive_int,
        default=DEFAULT_MATCH_JOBS,
        help=f"Maximum concurrent scratch jobs (default: {DEFAULT_MATCH_JOBS}).",
    )

    match_scratch_parser = match_subparsers.add_parser(
        "scratch",
        help="Compile and diff one scratch through the canonical matching pipeline.",
    )
    _add_scratch_directory_arguments(match_scratch_parser)
    match_scratch_parser.add_argument(
        "--image",
        type=Path,
        help="Path to the original image (default: the manifest primary target).",
    )
    match_scratch_parser.add_argument(
        "--manifest",
        type=Path,
        default=DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH,
        help="Path to the tracked gameplay function symbol manifest.",
    )
    match_scratch_parser.add_argument(
        "--full",
        action="store_true",
        help="Print both normalized listings side by side instead of only the diff.",
    )
    match_scratch_parser.add_argument(
        "--regions",
        action="store_true",
        help="Print localized mismatch region summaries before the diff/listing.",
    )
    match_scratch_parser.add_argument(
        "--region-context",
        type=int,
        default=4,
        help="Instruction context to include around each mismatch region (default: 4).",
    )
    match_scratch_parser.add_argument(
        "--max-regions",
        type=int,
        help="Maximum number of mismatch regions to print.",
    )

    match_inspect_parser = match_subparsers.add_parser(
        "inspect",
        help="Report structural and stack diagnostics for one scratch.",
    )
    _add_scratch_directory_arguments(match_inspect_parser)
    match_inspect_parser.add_argument(
        "--image",
        type=Path,
        help="Path to the original image (default: the manifest primary target).",
    )
    match_inspect_parser.add_argument(
        "--manifest",
        type=Path,
        default=DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH,
        help="Path to the tracked gameplay function symbol manifest.",
    )
    match_inspect_parser.add_argument(
        "--region-context",
        type=int,
        default=4,
        help="Instruction context around mismatch regions (default: 4).",
    )
    match_inspect_parser.add_argument(
        "--max-regions",
        type=int,
        help="Maximum mismatch regions to report.",
    )
    match_inspect_parser.add_argument(
        "--source-lines",
        action="store_true",
        help=(
            "Generate a proven-equivalent compiler listing and attach candidate "
            "scratch.cpp lines to mismatch regions."
        ),
    )
    match_inspect_parser.add_argument(
        "--json",
        action="store_true",
        help="Print machine-readable diagnostics.",
    )

    match_listing_parser = match_subparsers.add_parser(
        "listing",
        help="Generate a proven-equivalent VC mixed source/assembly listing.",
    )
    _add_scratch_directory_arguments(match_listing_parser)
    match_listing_parser.add_argument(
        "--output",
        type=Path,
        help="Output .cod path (default: the ignored match cache).",
    )
    match_listing_parser.add_argument(
        "--json",
        action="store_true",
        help="Print machine-readable output metadata.",
    )

    match_probe_parser = match_subparsers.add_parser(
        "probe",
        help="Compare a source overlay without editing the scratch.",
    )
    _add_scratch_directory_arguments(match_probe_parser)
    match_probe_source = match_probe_parser.add_mutually_exclusive_group(
        required=True
    )
    match_probe_source.add_argument(
        "--source",
        type=Path,
        help="Temporary replacement source.",
    )
    match_probe_source.add_argument(
        "--stdin",
        action="store_true",
        help="Read temporary replacement source from stdin.",
    )
    match_probe_parser.add_argument(
        "--image",
        type=Path,
        help="Path to the original image (default: the manifest primary target).",
    )
    match_probe_parser.add_argument(
        "--manifest",
        type=Path,
        default=DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH,
        help="Path to the tracked gameplay function symbol manifest.",
    )
    match_probe_parser.add_argument(
        "--compiler",
        help="Compiler profile used for the baseline and probe.",
    )
    match_probe_parser.add_argument(
        "--cflags",
        help="Compiler flags used for the baseline and probe.",
    )
    match_probe_parser.add_argument(
        "--label",
        help="Short experiment label.",
    )
    match_probe_parser.add_argument(
        "--export-dir",
        type=Path,
        help="Fresh directory for baseline, target, and source probe diagnostics.",
    )
    match_probe_parser.add_argument(
        "--record",
        action="store_true",
        help="Append the probe to experiments.jsonl.",
    )
    match_probe_parser.add_argument(
        "--json",
        action="store_true",
        help="Print the result as JSON.",
    )

    match_mutate_parser = match_subparsers.add_parser(
        "mutate",
        help="Compile and rank bounded source mutations without editing the scratch.",
    )
    _add_scratch_directory_arguments(match_mutate_parser)
    match_mutate_parser.add_argument(
        "--spec",
        type=Path,
        required=True,
        help="JSON mutation plan.",
    )
    match_mutate_parser.add_argument(
        "--image",
        type=Path,
        help="Path to the original image (default: the manifest primary target).",
    )
    match_mutate_parser.add_argument(
        "--manifest",
        type=Path,
        default=DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH,
        help="Path to the tracked gameplay function symbol manifest.",
    )
    match_mutate_parser.add_argument(
        "--compiler",
        help="Compiler profile used for the baseline and variants.",
    )
    match_mutate_parser.add_argument(
        "--cflags",
        help="Compiler flags used for the baseline and variants.",
    )
    match_mutate_parser.add_argument(
        "--min-changes",
        type=_positive_int,
        default=1,
        help="Minimum mutation sites changed per variant (default: 1).",
    )
    match_mutate_parser.add_argument(
        "--max-changes",
        type=_positive_int,
        default=1,
        help="Maximum mutation sites changed per variant (default: 1).",
    )
    match_mutate_parser.add_argument(
        "--max-variants",
        type=_positive_int,
        default=256,
        help="Bounded variant budget (default: 256).",
    )
    match_mutate_parser.add_argument(
        "-j",
        "--jobs",
        type=_positive_int,
        default=DEFAULT_MATCH_JOBS,
        help=f"Maximum concurrent variant jobs (default: {DEFAULT_MATCH_JOBS}).",
    )
    match_mutate_parser.add_argument(
        "--stop-on-improvement",
        action="store_true",
        help="Stop scheduling batches after the first improving batch.",
    )
    match_mutate_parser.add_argument(
        "--time-budget",
        type=float,
        help="Soft wall-clock budget in seconds; running batches finish.",
    )
    match_mutate_parser.add_argument(
        "--top",
        type=_positive_int,
        default=20,
        help="Maximum ranked variants to print (default: 20).",
    )
    match_mutate_parser.add_argument(
        "--write-best",
        type=Path,
        help="Write the best source only when it improves the baseline.",
    )
    match_mutate_parser.add_argument(
        "--require-improvement",
        action="store_true",
        help="Exit non-zero when no variant improves the baseline.",
    )
    match_mutate_parser.add_argument(
        "--record",
        action="store_true",
        help="Append the complete sweep to experiments.jsonl.",
    )
    match_mutate_parser.add_argument(
        "--json",
        action="store_true",
        help="Print the ranked result as JSON.",
    )

    match_mutate_parser.add_argument("--hypothesis", help="Reason for this source-shape experiment; saved with --record.")
    match_mutate_parser.add_argument("--export-candidate", help="Exact evaluated label to export, regardless of score.")
    match_mutate_parser.add_argument("--export-dir", type=Path, help="Fresh directory for a diagnostic candidate bundle.")

    contracts_parser = match_subparsers.add_parser("contracts", help="Read-only native return-contract evidence.")
    _add_scratch_directory_arguments(contracts_parser)
    contracts_parser.add_argument("--manifest", type=Path, default=DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH)
    contracts_parser.add_argument("--image", type=Path)
    contracts_parser.add_argument("--mobile-crosswalk", type=Path, default=REPO_ROOT / "analysis/symbols/windows-mobile-gameplay-crosswalk.json")
    contracts_parser.add_argument("--json", action="store_true")

    match_experiments_parser = match_subparsers.add_parser(
        "experiments",
        help="Summarize recorded probes and mutation sweeps.",
    )
    match_experiments_parser.add_argument("--search", help="Search receipt labels, hypotheses and hash-verified recipe edits.")
    match_experiments_parser.add_argument("--details", action="store_true", help="Show individual experiment history with recipe edits.")
    match_experiments_parser.add_argument(
        "--match-root",
        type=Path,
        default=DEFAULT_MATCH_ROOT,
        help="Path to the tools/match root.",
    )
    match_experiments_parser.add_argument(
        "--image",
        type=Path,
        help="Path to the original image (default: the manifest primary target).",
    )
    match_experiments_parser.add_argument(
        "--manifest",
        type=Path,
        default=DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH,
        help="Path to the tracked gameplay function symbol manifest.",
    )
    match_experiments_parser.add_argument(
        "--scratch",
        action="append",
        default=[],
        help=(
            "Scratch name, directory, or experiments.jsonl; "
            "repeat to restrict."
        ),
    )
    match_experiments_parser.add_argument(
        "--sort",
        choices=sorted(match_experiments.EXPERIMENT_SORTS),
        default="variants",
        help="Row ranking (default: variants).",
    )
    match_experiments_parser.add_argument(
        "--limit",
        type=_positive_int,
        help="Maximum rows to display.",
    )
    match_experiments_parser.add_argument(
        "--json",
        action="store_true",
        help="Print the summary as JSON.",
    )
    match_experiments_parser.add_argument(
        "--check",
        action="store_true",
        help="Exit non-zero when any log record is malformed.",
    )
    match_experiments_parser.add_argument(
        "--strict",
        action="store_true",
        help="Also reject current-baseline probe or mutation evaluation errors.",
    )
    match_experiments_parser.add_argument(
        "--check-specs",
        action="store_true",
        help=(
            "Check unreceipted mutation specs against their current scratch; "
            "recorded spec digests are historical."
        ),
    )

    match_experiment_audit_parser = match_subparsers.add_parser(
        "experiment-audit",
        help="Audit reviewed invalid-plan errors in a mutation sweep.",
    )
    _add_scratch_directory_arguments(match_experiment_audit_parser)
    match_experiment_audit_parser.add_argument(
        "--record",
        action="append",
        type=_positive_int,
        required=True,
        help="One-based mutation-sweep record to audit; repeat as needed.",
    )
    match_experiment_audit_parser.add_argument(
        "--reason",
        required=True,
        help="Why the compile failures came from an invalid mutation plan.",
    )
    match_experiment_audit_parser.add_argument(
        "--image",
        type=Path,
        help="Path to the original image (default: the manifest primary target).",
    )
    match_experiment_audit_parser.add_argument(
        "--manifest",
        type=Path,
        default=DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH,
        help="Path to the tracked gameplay function symbol manifest.",
    )
    match_experiment_audit_parser.add_argument(
        "--json",
        action="store_true",
        help="Print appended audit records as JSON.",
    )

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

    match_report_parser = match_subparsers.add_parser("report", help="Validate source-bound evidence and export full-executable decomp.dev progress.")
    match_report_parser.add_argument("--refresh", action="store_true", help="Re-evaluate sources with the local reference image and compilers.")
    match_report_parser.add_argument("--out", type=Path, default=match_report.DEFAULT_REPORT)
    match_report_parser.add_argument("-j", "--jobs", type=_positive_int, default=DEFAULT_MATCH_JOBS)

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
    match_status_parser.add_argument(
        "--check",
        action="store_true",
        help="Exit non-zero if any scratch fails to compile or match.",
    )
    match_status_parser.add_argument(
        "-j",
        "--jobs",
        type=_positive_int,
        default=DEFAULT_MATCH_JOBS,
        help=f"Maximum concurrent scratch jobs (default: {DEFAULT_MATCH_JOBS}).",
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
        choices=("problem", "unresolved", "mismatch", "unaudited", "all"),
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
    match_audit_parser.add_argument(
        "-j",
        "--jobs",
        type=_positive_int,
        default=DEFAULT_MATCH_JOBS,
        help=f"Maximum concurrent scratch jobs (default: {DEFAULT_MATCH_JOBS}).",
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

    match_lint_parser = match_subparsers.add_parser(
        "lint",
        help="Lint shared-address extern declarations across headers and scratches.",
    )
    match_lint_parser.add_argument(
        "--paths",
        action="store_true",
        help="Print declaring files for each finding.",
    )
    match_lint_parser.add_argument(
        "--json",
        action="store_true",
        help="Print findings as JSON.",
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

    if args.command == "match" and args.match_command == "mutate":
        if bool(args.export_candidate) != bool(args.export_dir):
            parser.error("--export-candidate and --export-dir must be supplied together")
        if args.time_budget is not None and args.time_budget <= 0:
            parser.error("--time-budget must be positive")
        if args.min_changes > args.max_changes:
            parser.error("--min-changes cannot exceed --max-changes")

    if getattr(args, "_scratch_directory", False):
        try:
            args.directory = resolve_scratch_directory(args.directory, args.match_root)
        except (OSError, ValueError) as error:
            print(f"scratch resolution failed: {error}", file=sys.stderr)
            return 2

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

    if args.command == "match" and args.match_command == "mobile":
        manifest = load_function_symbol_manifest(args.manifest)
        if args.pending:
            if args.function is not None:
                parser.error("match mobile --pending does not take a function")
            image_path = args.image or REPO_ROOT / manifest.primary_target
            statuses = collect_scratch_statuses(
                manifest,
                image_path,
                jobs=args.jobs,
            )
            crosswalk = load_json(args.crosswalk)
            rows = _mobile_backed_pending_rows(
                manifest,
                statuses,
                crosswalk,
            )
            _print_mobile_backed_pending(rows, limit=args.limit)
            return 0
        if args.function is None:
            parser.error("match mobile requires a function or --pending")
        function = next(
            (
                candidate
                for candidate in manifest.functions
                if args.function == candidate.name
                or args.function in candidate.aliases
            ),
            None,
        )
        if function is None:
            parser.error(f"unknown curated function or alias: {args.function}")

        crosswalk = load_json(args.crosswalk)
        entry = next(
            (
                candidate
                for candidate in crosswalk.get("entries", ())
                if candidate.get("windows_name") == function.name
            ),
            None,
        )
        if entry is None:
            parser.error(
                f"complete mobile crosswalk has no entry for {function.name}; "
                "run tools/sync_mobile_crosswalk.py"
            )

        print(f"function: {function.name} ({function.address_hex})")
        print(f"mapping: {entry['status']}")
        if entry.get("confidence"):
            print(f"confidence: {entry['confidence']}")
        if entry.get("source_object"):
            print(f"source object: {entry['source_object']}")
        if entry.get("source_object_evidence"):
            print(
                "source object evidence: "
                f"{entry['source_object_evidence']}"
            )

        if args.windows_tool != "none":
            print()
            windows_path = windows_decompile_path(
                tool=args.windows_tool,
                address=function.address,
                windows_name=function.name,
            )
            _print_source_section(
                f"windows/{args.windows_tool}",
                windows_path,
                paths_only=args.paths_only,
            )

        port_indexes = {
            "android": args.android_index,
            "ios": args.ios_index,
        }
        ports = (
            ("android", "ios")
            if args.port == "both"
            else (args.port,)
        )
        missing_verified_body = False
        for port in ports:
            print()
            symbol = entry.get(f"{port}_symbol")
            if not symbol:
                print(f"== {port}: no verified mapping ==")
                candidates = entry.get(f"{port}_candidates", ())
                if not candidates:
                    print("unverified candidates: none")
                    continue
                print("unverified candidates:")
                for candidate in candidates[: args.candidate_limit]:
                    print(
                        f"  {candidate['score']:.4f} "
                        f"{candidate['symbol']}"
                    )
                continue

            index_path = port_indexes[port]
            index = load_json(index_path)
            resolved_functions = resolve_corpus_symbols(index, symbol)
            evidence = entry.get(f"{port}_symbol_evidence")
            if not resolved_functions:
                print(f"== {port}: verified mapping unavailable ==")
                print(f"symbol: {symbol}")
                if evidence:
                    print(f"evidence: {evidence}")
                print(f"index: {_display_repo_path(index_path)}")
                missing_verified_body = True
                continue

            for variant, resolved in enumerate(
                resolved_functions,
                start=1,
            ):
                if variant > 1:
                    print()
                title = f"{port}: verified"
                if len(resolved_functions) > 1:
                    title += (
                        f" variant {variant}/{len(resolved_functions)}"
                    )
                mobile_path = corpus_function_path(
                    index_path.parent,
                    resolved,
                )
                metadata = [
                    f"symbol: {resolved['demangled']}",
                    f"mangled: {resolved['mangled']}",
                ]
                if evidence:
                    metadata.append(f"evidence: {evidence}")
                _print_source_section(
                    title,
                    mobile_path,
                    paths_only=args.paths_only,
                    metadata=metadata,
                )

        return 1 if missing_verified_body else 0


    if args.command == "match" and args.match_command == "triage":
        manifest = load_function_symbol_manifest(args.manifest)
        image_path = args.image or REPO_ROOT / manifest.primary_target
        statuses = collect_scratch_statuses(
            manifest,
            image_path,
            args.match_root,
            jobs=args.jobs,
        )
        rows = collect_triage_rows(
            manifest,
            image_path,
            statuses,
            mobile_crosswalk=load_json(args.crosswalk),
            port_relevant_only=args.scope == "port",
            manifest_path=args.manifest,
        )

        states = _parse_csv(args.state)
        if states is not None:
            unknown_states = states - TRIAGE_STATES
            if unknown_states:
                parser.error(
                    "match triage --state has unknown values: "
                    + ", ".join(sorted(unknown_states))
                )
            rows = [row for row in rows if row.state in states]

        recoveries = _parse_csv(args.recovery)
        if recoveries is not None:
            allowed_recoveries = set(RECOVERY_VALUES) | {
                "exact",
                "missing",
                "unspecified",
            }
            unknown_recoveries = recoveries - allowed_recoveries
            if unknown_recoveries:
                parser.error(
                    "match triage --recovery has unknown values: "
                    + ", ".join(sorted(unknown_recoveries))
                )
            rows = [row for row in rows if row.recovery in recoveries]

        residuals = _parse_csv(args.residual)
        if residuals is not None:
            unknown_residuals = residuals - RESIDUAL_VALUES
            if unknown_residuals:
                parser.error(
                    "match triage --residual has unknown values: "
                    + ", ".join(sorted(unknown_residuals))
                )
            rows = [
                row
                for row in rows
                if residuals.intersection(row.residuals)
            ]

        if args.mobile == "verified":
            rows = [row for row in rows if row.mobile.verified]
        elif args.mobile == "without-verified":
            rows = [row for row in rows if not row.mobile.verified]
        rows = [row for row in rows if row.target_size >= args.min_bytes]
        rows = sort_triage_rows(rows, sort_by=args.sort)
        if args.limit is not None:
            rows = rows[: args.limit]

        if args.json:
            print(
                json.dumps(
                    {
                        "scope": args.scope,
                        "sort": args.sort,
                        "summary": triage_summary_payload(rows),
                        "rows": (
                            []
                            if args.summary_only
                            else [triage_row_payload(row) for row in rows]
                        ),
                    },
                    indent=2,
                    sort_keys=True,
                )
            )
        elif args.summary_only:
            print(render_triage_summary(rows))
        else:
            print(render_triage_table(rows, sort_by=args.sort))

        if args.check and any(status.state == "error" for status in statuses):
            return 1
        return 0

    if args.command == "match" and args.match_command == "probe":
        try:
            config = load_scratch_config(args.directory)
            source_text = (
                sys.stdin.read()
                if args.stdin
                else args.source.resolve().read_text(encoding="utf-8")
            )
            manifest = load_function_symbol_manifest(args.manifest)
            image_path = args.image or REPO_ROOT / manifest.primary_target
            result = evaluate_source_probe(
                config,
                source_text,
                match_root=args.match_root,
                image_path=image_path,
                manifest=manifest,
                compiler=args.compiler,
                cflags=args.cflags,
                label=args.label,
            )
            dependency_sha256 = (
                scratch_dependency_sha256(result.baseline.config, args.match_root)
                if args.record or args.export_dir
                else None
            )
            baseline_epoch = (
                scratch_experiment_epoch(
                    result.baseline.config,
                    args.match_root,
                    image_path=image_path,
                    manifest_path=args.manifest,
                )
                if args.record or args.export_dir
                else None
            )
            if args.export_dir is not None:
                match_export.export_probe(
                    result,
                    args.export_dir,
                    source_text=source_text,
                    match_root=args.match_root,
                    image_path=image_path,
                    manifest=manifest,
                    baseline_epoch=baseline_epoch,
                    dependency_sha256=dependency_sha256,
                )
        except Exception as error:  # noqa: BLE001
            print(
                f"probe failed: {str(error).splitlines()[0]}",
                file=sys.stderr,
            )
            return 2

        payload = probe_result_payload(result)
        if args.export_dir is not None:
            payload["diagnostic_export"] = str(args.export_dir)
        recorded_to = None
        if args.record:
            record_path = config.directory / "experiments.jsonl"
            record_payload = {
                "schema": match_experiments.EXPERIMENT_SCHEMA,
                "kind": "probe",
                "recorded_at": datetime.now(UTC).isoformat(),
                "dependency_sha256": dependency_sha256,
                "baseline_epoch": baseline_epoch,
                **payload,
            }
            with record_path.open("a", encoding="utf-8") as handle:
                handle.write(
                    json.dumps(
                        record_payload,
                        separators=(",", ":"),
                        sort_keys=True,
                    )
                    + "\n"
                )
            recorded_to = str(record_path)
            payload["recorded_to"] = recorded_to

        if args.json:
            print(json.dumps(payload, indent=2, sort_keys=True))
        else:
            print(render_probe_result(result))
            if args.export_dir is not None:
                print(f"diagnostic_export={args.export_dir}")
            if recorded_to is not None:
                print(f"recorded={recorded_to}")
        if result.baseline.state == "error" or result.probe.state == "error":
            return 2
        return 0

    if args.command == "match" and args.match_command == "mutate":
        try:
            config = load_scratch_config(args.directory)
            mutation_spec = match_mutation.load_mutation_spec(
                args.spec.resolve()
            )
            manifest = load_function_symbol_manifest(args.manifest)
            image_path = args.image or REPO_ROOT / manifest.primary_target
            source_path = config.directory / "scratch.cpp"
            if (
                args.write_best is not None
                and args.write_best.resolve() == source_path.resolve()
            ):
                raise ValueError(
                    "--write-best cannot overwrite the tracked scratch source"
                )
            source_text = source_path.read_text(encoding="utf-8")
            sweep = match_mutation.evaluate_mutation_sweep(
                config,
                mutation_spec,
                source_text=source_text,
                match_root=args.match_root,
                image_path=image_path,
                manifest=manifest,
                compiler=args.compiler,
                cflags=args.cflags,
                min_changes=args.min_changes,
                max_changes=args.max_changes,
                max_variants=args.max_variants,
                jobs=args.jobs,
                stop_on_improvement=args.stop_on_improvement,
                time_budget=args.time_budget,
            )
            dependency_sha256 = (
                scratch_dependency_sha256(
                    sweep.baseline.config,
                    args.match_root,
                )
                if args.record or args.export_dir
                else None
            )
            baseline_epoch = (
                scratch_experiment_epoch(
                    sweep.baseline.config,
                    args.match_root,
                    image_path=image_path,
                    manifest_path=args.manifest,
                )
                if args.record or args.export_dir
                else None
            )
            if args.export_dir is not None:
                match_export.export_candidate(
                    sweep, args.export_candidate, args.export_dir,
                    source_text=source_text, match_root=args.match_root,
                    image_path=image_path, manifest=manifest, baseline_epoch=baseline_epoch,
                )
        except Exception as error:  # noqa: BLE001
            print(
                f"mutation sweep failed: {str(error).splitlines()[0]}",
                file=sys.stderr,
            )
            return 2

        written_to = None
        if args.write_best is not None and sweep.best_improves:
            assert sweep.best is not None
            args.write_best.parent.mkdir(parents=True, exist_ok=True)
            args.write_best.write_text(
                sweep.best.variant.source_text,
                encoding="utf-8",
            )
            written_to = str(args.write_best)

        recorded_to = None
        if args.record:
            record_path = config.directory / "experiments.jsonl"
            record_payload = {
                "schema": match_experiments.EXPERIMENT_SCHEMA,
                "kind": "mutation-sweep",
                "hypothesis": args.hypothesis,
                "diagnostic_export": str(args.export_dir) if args.export_dir else None,
                "recorded_at": datetime.now(UTC).isoformat(),
                "best_source_written_to": written_to,
                "dependency_sha256": dependency_sha256,
                "baseline_epoch": baseline_epoch,
                **match_mutation.mutation_sweep_payload(sweep),
            }
            with record_path.open("a", encoding="utf-8") as handle:
                handle.write(
                    json.dumps(
                        record_payload,
                        separators=(",", ":"),
                        sort_keys=True,
                    )
                    + "\n"
                )
            recorded_to = str(record_path)

        if args.json:
            payload = match_mutation.mutation_sweep_payload(
                sweep,
                limit=args.top,
            )
            payload["diagnostic_export"] = str(args.export_dir) if args.export_dir else None
            payload["best_source_written_to"] = written_to
            payload["recorded_to"] = recorded_to
            print(json.dumps(payload, indent=2, sort_keys=True))
        else:
            print(
                match_mutation.render_mutation_sweep(
                    sweep,
                    limit=args.top,
                )
            )
            if args.export_dir is not None:
                print(f"diagnostic_export={args.export_dir}")
            if written_to is not None:
                print(f"best_source={written_to}")
            elif args.write_best is not None:
                print("best_source=not-written (no improving variant)")
            if recorded_to is not None:
                print(f"recorded={recorded_to}")

        if sweep.baseline.state == "error" or all(
            evaluation.status.state == "error"
            for evaluation in sweep.evaluations
        ):
            return 2
        if (
            args.write_best is not None or args.require_improvement
        ) and not sweep.best_improves:
            return 1
        return 0

    if args.command == "match" and args.match_command == "experiment-audit":
        try:
            if len(args.record) != len(set(args.record)):
                raise ValueError("--record values must be unique")
            config = load_scratch_config(args.directory)
            path = config.directory / match_experiments.EXPERIMENT_FILE
            current_epoch = scratch_experiment_epoch(
                config,
                args.match_root,
                image_path=args.image,
                manifest_path=args.manifest,
            )
            recorded_at = datetime.now(UTC).isoformat()
            records = [
                match_experiments.build_mutation_error_audit(
                    path,
                    target_record=target_record,
                    current_epoch=current_epoch,
                    reason=args.reason,
                    recorded_at=recorded_at,
                )
                for target_record in args.record
            ]
            with path.open("a", encoding="utf-8") as handle:
                for record in records:
                    handle.write(
                        json.dumps(
                            record,
                            separators=(",", ":"),
                            sort_keys=True,
                        )
                        + "\n"
                    )
        except (OSError, TypeError, ValueError) as error:
            print(
                f"experiment audit failed: {str(error).splitlines()[0]}",
                file=sys.stderr,
            )
            return 2
        if args.json:
            print(json.dumps(records, indent=2, sort_keys=True))
        else:
            targets = ",".join(str(record["target_record"]) for record in records)
            print(
                f"audited={path} records={targets} "
                "classification=invalid-mutation-plan"
            )
        return 0

    if args.command == "match" and args.match_command == "contracts":
        try:
            config = load_scratch_config(args.directory)
            manifest = load_function_symbol_manifest(args.manifest)
            payload = match_contracts.audit_contract(
                config, image_path=args.image or REPO_ROOT / manifest.primary_target,
                manifest=manifest, mobile_crosswalk=json.loads(args.mobile_crosswalk.read_text()),
            )
        except (OSError, ValueError) as error:
            print(f"contract audit failed: {error}", file=sys.stderr)
            return 2
        print(json.dumps(payload, indent=2, sort_keys=True) if args.json else
              match_contracts.render_contract_audit(payload))
        return 0

    if args.command == "match" and args.match_command == "experiments":
        if args.search is not None or args.details:
            if args.check or args.strict or args.check_specs:
                parser.error("history search cannot be combined with summary validation flags")
            try:
                paths = match_experiments.find_experiment_logs(args.match_root, args.scratch)
                payload = match_history.search_history(
                    paths, query=args.search or "",
                    current_epochs=scratch_experiment_epochs(
                        args.match_root, directories=[path.parent for path in paths],
                        image_path=args.image, manifest_path=args.manifest),
                )
                payload["total_rows"] = len(payload["rows"])
                if args.limit is not None:
                    payload["rows"] = payload["rows"][:args.limit]
            except (OSError, ValueError) as error:
                print(f"experiment history failed: {error}", file=sys.stderr)
                return 2
            print(json.dumps(payload, indent=2, sort_keys=True) if args.json else
                  match_history.render_history(payload))
            for error in payload["errors"]:
                print(error, file=sys.stderr)
            return 1 if payload["errors"] else 0
        try:
            experiment_paths = match_experiments.find_experiment_logs(
                args.match_root,
                args.scratch,
            )
            payload = match_experiments.summarize_experiments(
                args.match_root,
                scratches=args.scratch,
                sort_by=args.sort,
                current_epochs=scratch_experiment_epochs(
                    args.match_root,
                    directories=[path.parent for path in experiment_paths],
                    image_path=args.image,
                    manifest_path=args.manifest,
                ),
            )
            mutation_specs = (
                match_experiments.audit_mutation_specs(
                    args.match_root,
                    scratches=args.scratch,
                )
                if args.check_specs
                else None
            )
        except (OSError, ValueError) as error:
            print(
                f"experiment summary failed: "
                f"{str(error).splitlines()[0]}",
                file=sys.stderr,
            )
            return 2

        if args.limit is not None:
            payload["rows"] = payload["rows"][: args.limit]
        payload["selected_rows"] = len(payload["rows"])
        if mutation_specs is not None:
            payload["mutation_specs"] = mutation_specs
        if args.json:
            print(json.dumps(payload, indent=2, sort_keys=True))
        else:
            print(match_experiments.render_experiment_summary(payload))
            for error in payload["errors"]:
                print(str(error), file=sys.stderr)
            for error in payload["strict_errors"]:
                print(str(error), file=sys.stderr)
            if mutation_specs is not None:
                print(
                    "mutation-specs "
                    f"files={mutation_specs['files']} "
                    f"historical={mutation_specs['historical']} "
                    f"active={mutation_specs['active']} "
                    f"runnable={mutation_specs['runnable']} "
                    f"stale={mutation_specs['stale']}"
                )
                for error in mutation_specs["errors"]:
                    print(str(error), file=sys.stderr)
        if (args.check or args.strict) and payload["errors"]:
            return 1
        if args.strict and payload["strict_errors"]:
            return 1
        if mutation_specs is not None and mutation_specs["errors"]:
            return 1
        return 0

    if args.command == "match" and args.match_command == "report":
        try:
            report = match_report.publish(refresh=args.refresh, output=args.out, jobs=args.jobs)
        except (ValueError, KeyError, TypeError, OSError, RuntimeError) as exc:
            print(f"decomp.dev report failed: {exc}", file=sys.stderr)
            return 1
        measures = report["measures"]
        print(
            f"{match_report.VERSION}: {measures['matched_functions']}/{measures['total_functions']} functions; "
            f"{measures['matched_code']}/{measures['total_code']} code bytes matched "
            f"({measures['matched_code_percent']:.2f}%); fuzzy={measures['fuzzy_match_percent']:.2f}%; "
            f"linked={measures['complete_code_percent']:.2f}%; report={args.out}"
        )
        return 0

    if args.command == "match" and args.match_command == "status":
        manifest = load_function_symbol_manifest(args.manifest)
        image_path = args.image or REPO_ROOT / manifest.primary_target
        statuses = collect_scratch_statuses(manifest, image_path, jobs=args.jobs)
        totals = manifest_cluster_totals(manifest, image_path, statuses)
        type_findings = type_consolidation_findings()
        print(
            render_status_table(
                statuses,
                totals,
                type_findings=type_findings,
                manifest=manifest,
                image_path=image_path,
            )
        )
        if args.write is not None:
            args.write.write_text(
                render_status_markdown(
                    statuses,
                    totals,
                    type_findings=type_findings,
                    manifest=manifest,
                    image_path=image_path,
                    manifest_path=args.manifest,
                ),
                encoding="utf-8",
            )
        if args.check:
            errored = [status for status in statuses if status.state == "error"]
            if errored:
                print(
                    f"\nstatus check failed: {len(errored)} scratch(es) errored",
                    file=sys.stderr,
                )
                for status in errored:
                    print(
                        f"  {status.config.function}: {status.error}",
                        file=sys.stderr,
                    )
                return 1
        return 0

    if args.command == "match" and args.match_command == "audit":
        manifest = load_function_symbol_manifest(args.manifest)
        image_path = args.image or REPO_ROOT / manifest.primary_target
        if args.status == "all":
            audit_statuses = frozenset(
                ("ok", "unresolved", "mismatch", "unaudited")
            )
        elif args.status == "problem":
            audit_statuses = frozenset(
                ("unresolved", "mismatch", "unaudited")
            )
        else:
            audit_statuses = frozenset((args.status,))
        report = collect_masked_operand_issues(
            manifest,
            image_path,
            statuses=audit_statuses,
            exact_only=args.exact_only,
            jobs=args.jobs,
        )
        if args.json:
            print(
                json.dumps(
                    {
                        "issues": [
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
                            for issue in report.issues
                        ],
                        "failures": [
                            {
                                "function": failure.config.function,
                                "scratch": str(failure.config.directory),
                                "address": failure.address,
                                "error": failure.error,
                            }
                            for failure in report.failures
                        ],
                    },
                    indent=2,
                    sort_keys=True,
                )
            )
            return 0 if report.clean else 1
        _print_masked_audit_issues(report.issues, limit=args.limit)
        _print_masked_audit_failures(report.failures)
        return 0 if report.clean else 1

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

    if args.command == "match" and args.match_command == "lint":
        findings = lint_extern_declarations()
        if args.json:
            print(
                json.dumps(
                    [
                        {
                            "status": finding.status,
                            "address": finding.address,
                            "name": finding.name,
                            "detail": finding.detail,
                            "paths": [str(path) for path in finding.paths],
                        }
                        for finding in findings
                    ],
                    indent=2,
                    sort_keys=True,
                )
            )
            return 0 if not findings else 1
        if not findings:
            print("extern lint: clean")
            return 0
        print(f"extern lint: {len(findings)} finding(s)")
        for finding in findings:
            print(f"  {finding.status} 0x{finding.address:x} {finding.name}: {finding.detail}")
            if args.paths:
                for path in finding.paths:
                    print(f"    {path}")
        return 1

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
                            "layout_count": finding.signature_count,
                            "recommendation": finding.recommendation,
                            "details": list(finding.details),
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
                f"{finding.signature_count} layout group(s) - {finding.recommendation}"
            )
            for detail in finding.details:
                print(f"  {detail}")
            if args.paths:
                for path in finding.paths:
                    print(f"  {path}")
        return 0

    if args.command == "match" and args.match_command == "listing":
        try:
            config = load_scratch_config(args.directory)
            result = generate_compiler_listing(
                config,
                args.match_root,
                output=args.output,
            )
        except Exception as error:  # noqa: BLE001
            print(
                f"listing failed: {str(error).splitlines()[0]}",
                file=sys.stderr,
            )
            return 2
        if args.json:
            print(json.dumps(compiler_listing_payload(result), indent=2, sort_keys=True))
        else:
            print(render_compiler_listing_result(result))
        return 0

    if args.command == "match" and args.match_command == "inspect":
        try:
            manifest = load_function_symbol_manifest(args.manifest)
            image_path = args.image or REPO_ROOT / manifest.primary_target
            result = run_scratch_match(
                directory=args.directory,
                image_path=image_path,
                manifest=manifest,
                match_root=args.match_root,
            )
            listing = None
            if args.source_lines:
                config = load_scratch_config(args.directory)
                listing = generate_compiler_listing(config, args.match_root)
            payload = match_result_payload(
                result,
                region_context=args.region_context,
                max_regions=args.max_regions,
                listing_spans=listing.spans if listing is not None else None,
            )
        except Exception as error:  # noqa: BLE001
            print(
                f"inspection failed: {str(error).splitlines()[0]}",
                file=sys.stderr,
            )
            return 2
        if args.json:
            print(json.dumps(payload, indent=2, sort_keys=True))
            return 0

        print(
            f"match={result.ratio:.2%} "
            f"insns={len(result.target_lines)}/{len(result.candidate_lines)} "
            f"prefix={result.prefix_instructions}/{len(result.target_lines)}"
        )
        frame = payload["stack_frame"]
        if frame is not None:
            target_frame = frame["target_prologue_allocation_bytes"]
            candidate_frame = frame["candidate_prologue_allocation_bytes"]
            delta = frame["target_minus_candidate_bytes"]
            delta_text = f"{delta:+d}" if delta is not None else "-"
            print(
                "frame: prologue-allocation="
                f"{target_frame if target_frame is not None else '-'}/"
                f"{candidate_frame if candidate_frame is not None else '-'} "
                f"delta={delta_text} "
                f"classification={frame['classification']} diagnostic-only"
            )
        cfg = payload["cfg_alignment"]
        if cfg is not None:
            summary = cfg["summary"]
            print(
                "cfg: "
                f"blocks={summary['target_blocks']}/{summary['candidate_blocks']} "
                f"exact={summary['exact_pairs']} "
                f"ambiguous={summary['exact_ambiguous_pairs']} "
                f"similar={summary['similar_pairs']} anchors={summary['edge_anchor_pairs']} "
                f"unmatched={summary['unmatched_target']}/{summary['unmatched_candidate']} "
                f"edge-conflicts={summary['edge_conflicts']} "
                f"edge-checked={summary['edge_consistent_pairs'] + summary['edge_conflicts']} "
                f"heuristic-edge-conflicts={summary['heuristic_edge_conflicts']}"
            )
            residual_pairs = sorted(
                (
                    pair
                    for pair in cfg["pairs"]
                    if not pair["edge_anchor"] or pair["edge_consistent"] is False
                ),
                key=lambda pair: (
                    pair["edge_consistent"] is not False,
                    pair["kind"] == "exact-ambiguous",
                    pair["match_ratio"],
                    pair["target_block"],
                ),
            )
            for pair in residual_pairs[:12]:
                target_block = pair["target"]
                candidate_block = pair["candidate"]
                print(
                    f"  {pair['kind']} target=b{target_block['index']} "
                    f"0x{target_block['addresses']['start']:08x} "
                    f"candidate=b{candidate_block['index']} "
                    f"+0x{candidate_block['bytes']['start']:x} "
                    f"match={pair['match_ratio']:.1%} "
                    f"anchor={pair['edge_anchor']} edges={pair['edge_consistent']}"
                )
        for index, region in enumerate(payload["regions"], start=1):
            target_region = region["target_instructions"]
            candidate_region = region["candidate_instructions"]
            print(
                f"mismatch {index}: target={target_region['start']}:{target_region['end']} "
                f"candidate={candidate_region['start']}:{candidate_region['end']} "
                f"match={region['match_ratio']:.1%} delta={region['instruction_delta']:+d}"
            )
            candidate_source = region.get("candidate_source")
            if candidate_source is not None:
                source_lines = ",".join(str(line) for line in candidate_source["lines"])
                byte_range = candidate_source["byte_range"]
                print(
                    f"  source={candidate_source['source']}:{source_lines} "
                    f"candidate-bytes=+0x{byte_range['start']:x}:+0x{byte_range['end']:x}"
                )
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

    if args.command == "match" and args.match_command in ("scratch", "diff"):
        manifest = load_function_symbol_manifest(args.manifest)
        image_path = args.image or REPO_ROOT / manifest.primary_target
        if args.match_command == "scratch":
            result = run_scratch_match(
                directory=args.directory,
                image_path=image_path,
                manifest=manifest,
                match_root=args.match_root,
            )
        else:
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
        print(f"encoded body: {'match' if result.body_byte_exact else 'not matched'}")
        if result.unexplained_target_ranges:
            print(f"unexplained target bytes: {sum(b - a for a, b in result.unexplained_target_ranges)}")
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
        return 0 if result.exact else 1

    parser.error(f"Unhandled command: {args.command}")
    return 2
