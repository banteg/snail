"""Diagnostic bundles for source probes and mutations, independent of scores."""

from __future__ import annotations

import difflib
import hashlib
import json
import tempfile
from dataclasses import asdict, replace
from pathlib import Path

from . import match as matchlib
from .match_mutation import MutationSweep, mutation_evaluation_payload


def export_candidate(
    sweep: MutationSweep,
    label: str,
    destination: Path,
    *,
    source_text: str,
    match_root: Path,
    image_path: Path,
    manifest,
    baseline_epoch: str,
) -> dict:
    selected = next((e for e in sweep.evaluations if e.variant.label == label), None)
    if selected is None:
        raise ValueError(f"candidate label was not evaluated: {label}")
    return _export_diagnostic(
        selected.status,
        destination,
        config=sweep.baseline.config,
        source_text=selected.variant.source_text,
        baseline_source_text=source_text,
        metadata={
            "kind": "mutation-diagnostic",
            "spec_sha256": sweep.spec.sha256,
            "evaluation": mutation_evaluation_payload(selected),
        },
        match_root=match_root,
        image_path=image_path,
        manifest=manifest,
        baseline_epoch=baseline_epoch,
    )


def export_probe(
    result: matchlib.ProbeResult,
    destination: Path,
    *,
    source_text: str,
    match_root: Path,
    image_path: Path,
    manifest,
    baseline_epoch: str,
    dependency_sha256: str,
) -> dict:
    """Export the overlay with its captured baseline source and assembly."""
    if result.baseline_source_text is None:
        raise ValueError("probe result is missing the evaluated baseline source")
    if hashlib.sha256(source_text.encode()).hexdigest() != result.source_sha256:
        raise ValueError("export source does not reproduce evaluated source identity")
    baseline_match = result.baseline_match if result.baseline.error is None else None
    if result.baseline.error is None and baseline_match is None:
        raise ValueError("probe result is missing the evaluated baseline assembly")
    config = result.baseline.config
    return _export_diagnostic(
        result.probe,
        destination,
        config=config,
        source_text=source_text,
        baseline_source_text=result.baseline_source_text,
        metadata={
            "kind": "probe-diagnostic",
            "dependency_sha256": dependency_sha256,
            "evaluation": matchlib.probe_result_payload(result),
            "scratch_config": {
                "function": config.function,
                "compiler": config.compiler,
                "cflags": config.cflags,
                "symbol": config.symbol,
                "end_va": config.end_va,
            },
        },
        match_root=match_root,
        image_path=image_path,
        manifest=manifest,
        baseline_epoch=baseline_epoch,
        baseline_match=baseline_match,
    )


def _export_diagnostic(
    status: matchlib.ScratchStatus,
    destination: Path,
    *,
    config: matchlib.ScratchConfig,
    source_text: str,
    baseline_source_text: str,
    metadata: dict,
    match_root: Path,
    image_path: Path,
    manifest,
    baseline_epoch: str,
    baseline_match: matchlib.MatchResult | None = None,
) -> dict:
    destination = destination.resolve()
    if destination.exists():
        raise ValueError(f"export destination already exists: {destination}")
    destination.parent.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(
        prefix=".snail-export-", dir=destination.parent
    ) as temp:
        bundle = Path(temp) / "bundle"
        bundle.mkdir()
        (bundle / "candidate.cpp").write_text(source_text, encoding="utf-8")
        (bundle / "source.diff").write_text(
            "\n".join(
                difflib.unified_diff(
                    baseline_source_text.splitlines(),
                    source_text.splitlines(),
                    fromfile="baseline.cpp",
                    tofile="candidate.cpp",
                    lineterm="",
                )
            )
            + "\n",
            encoding="utf-8",
        )
        report = {
            "schema": 1,
            **metadata,
            "baseline_epoch": baseline_epoch,
            "baseline_source_sha256": hashlib.sha256(
                baseline_source_text.encode()
            ).hexdigest(),
            "diagnostic": None,
            "error": status.error,
        }
        if baseline_match is not None:
            _write_assembly(bundle / "baseline.asm", baseline_match.candidate_disassembly)
        if status.error is None:
            shadow = Path(temp) / "scratch"
            shadow.mkdir()
            config = replace(config, directory=shadow)
            (shadow / "scratch.cpp").write_text(source_text, encoding="utf-8")
            obj = matchlib.compile_scratch(config, match_root)
            function = matchlib.extract_object_function(
                matchlib.parse_coff_object(obj.read_bytes()),
                config.symbol or config.function,
                reference_manifest=matchlib.load_default_reference_symbol_manifest(),
            )
            digest = matchlib.object_function_fingerprint(function)
            if (
                status.code_sha256 is None
                or digest != status.code_sha256
            ):
                raise ValueError(
                    "export recompilation does not reproduce evaluated code identity"
                )
            result = matchlib.run_match(
                obj_path=obj,
                function_name=config.function,
                image_path=image_path,
                manifest=manifest,
                symbol_name=config.symbol,
                end_va=config.end_va,
            )
            report["diagnostic"] = matchlib.match_result_payload(result)
            report["code_sha256"] = digest
            report["reference_audit"] = asdict(result.masked_operand_audit)
            (bundle / "assembly.diff").write_text(
                "\n".join(result.diff_lines) + "\n", encoding="utf-8"
            )
            if baseline_match is not None:
                (bundle / "baseline.diff").write_text(
                    "\n".join(difflib.unified_diff(
                        baseline_match.candidate_lines,
                        result.candidate_lines,
                        fromfile="baseline",
                        tofile="candidate",
                        lineterm="",
                    )) + "\n",
                    encoding="utf-8",
                )
            for name, lines in (
                ("target", result.target_disassembly),
                ("candidate", result.candidate_disassembly),
            ):
                _write_assembly(bundle / f"{name}.asm", lines)
        (bundle / "report.json").write_text(
            json.dumps(
                report, indent=2, sort_keys=True, default=lambda value: value.hex()
            )
            + "\n",
            encoding="utf-8",
        )
        # Publish only a complete bundle. The caller must choose a fresh path.
        if destination.exists():
            raise ValueError(f"export destination already exists: {destination}")
        bundle.rename(destination)
    return report


def _write_assembly(path: Path, lines: tuple[matchlib.DisassemblyLine, ...]) -> None:
    path.write_text(
        "\n".join(f"{line.offset:04x}  {line.text}" for line in lines) + "\n",
        encoding="utf-8",
    )
