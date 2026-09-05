"""Diagnostic bundles for any evaluated mutation, independent of score ranking."""

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
    destination = destination.resolve()
    if destination.exists():
        raise ValueError(f"export destination already exists: {destination}")
    destination.parent.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(
        prefix=".snail-export-", dir=destination.parent
    ) as temp:
        bundle = Path(temp) / "bundle"
        bundle.mkdir()
        (bundle / "candidate.cpp").write_text(selected.variant.source_text)
        (bundle / "source.diff").write_text(
            "\n".join(
                difflib.unified_diff(
                    source_text.splitlines(),
                    selected.variant.source_text.splitlines(),
                    fromfile="baseline.cpp",
                    tofile="candidate.cpp",
                    lineterm="",
                )
            )
            + "\n"
        )
        report = {
            "schema": 1,
            "kind": "mutation-diagnostic",
            "baseline_epoch": baseline_epoch,
            "baseline_source_sha256": hashlib.sha256(source_text.encode()).hexdigest(),
            "spec_sha256": sweep.spec.sha256,
            "evaluation": mutation_evaluation_payload(selected),
            "diagnostic": None,
            "error": selected.status.error,
        }
        if selected.status.error is None:
            shadow = Path(temp) / "scratch"
            shadow.mkdir()
            config = replace(sweep.baseline.config, directory=shadow)
            (shadow / "scratch.cpp").write_text(selected.variant.source_text)
            obj = matchlib.compile_scratch(config, match_root)
            function = matchlib.extract_object_function(
                matchlib.parse_coff_object(obj.read_bytes()),
                config.symbol or config.function,
                reference_manifest=matchlib.load_default_reference_symbol_manifest(),
            )
            digest = matchlib.object_function_fingerprint(function)
            if (
                selected.status.code_sha256 is None
                or digest != selected.status.code_sha256
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
            (bundle / "assembly.diff").write_text("\n".join(result.diff_lines) + "\n")
            for name, lines in (
                ("target", result.target_disassembly),
                ("candidate", result.candidate_disassembly),
            ):
                (bundle / f"{name}.asm").write_text(
                    "\n".join(f"{line.offset:04x}  {line.text}" for line in lines)
                    + "\n"
                )
        (bundle / "report.json").write_text(
            json.dumps(
                report, indent=2, sort_keys=True, default=lambda value: value.hex()
            )
            + "\n"
        )
        # Publish only a complete bundle. The caller must choose a fresh path.
        if destination.exists():
            raise ValueError(f"export destination already exists: {destination}")
        bundle.rename(destination)
    return report
