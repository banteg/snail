"""Validate or replay the bounded four-builder source controls from 2026-09-12."""

import argparse
import hashlib
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
RECEIPT = Path(__file__).with_name("four-builder-controls-20260912.json")


def reconstruct(baseline, control):
    lines = baseline.splitlines(keepends=True)
    previous_end = 0
    for edit in control["edits"]:
        start, end = edit["start_line"], edit["end_line"]
        if not previous_end <= start <= end <= len(lines):
            raise ValueError("Invalid or overlapping source edit")
        previous_end = end
    for edit in reversed(control["edits"]):
        lines[edit["start_line"] : edit["end_line"]] = [edit["replacement"]]
    source = "".join(lines)
    if hashlib.sha256(source.encode()).hexdigest() != control["source_sha256"]:
        raise ValueError(f"Source hash mismatch: {control['label']}")
    return source


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--receipt", type=Path, default=RECEIPT)
    parser.add_argument("--function")
    parser.add_argument("--batch")
    parser.add_argument("--label")
    parser.add_argument("--source-out", type=Path)
    parser.add_argument("--replay", action="store_true")
    args = parser.parse_args()
    receipt = json.loads(args.receipt.read_text())
    for name, baseline in receipt["baselines"].items():
        if (
            hashlib.sha256(baseline["source"].encode()).hexdigest()
            != baseline["source_sha256"]
        ):
            raise ValueError(f"Baseline source hash mismatch: {name}")
    selected = []
    for control in receipt["controls"]:
        source = reconstruct(
            receipt["baselines"][control["function"]]["source"], control
        )
        if all(
            getattr(args, key) in (None, control[key])
            for key in ("function", "batch", "label")
        ):
            selected.append((control, source))
    print(
        f"Validated all {len(receipt['controls'])} source reconstructions; selected {len(selected)}"
    )
    if not selected:
        parser.error("No controls selected")
    if args.source_out or args.replay:
        if len(selected) != 1:
            parser.error("Select exactly one control for --source-out or --replay")
        control, source = selected[0]
        if args.source_out:
            args.source_out.write_text(source)
        if args.replay:
            if control["measured"]["error"] is not None:
                parser.error(
                    "This control did not compile; use --source-out to inspect it"
                )
            for filename, expected in receipt["build_inputs"].items():
                if (
                    hashlib.sha256((ROOT / filename).read_bytes()).hexdigest()
                    != expected
                ):
                    raise ValueError(
                        f"Build input changed since measurement: {filename}"
                    )
            from snail import match

            config = match.load_scratch_config(
                ROOT / "tools/match/scratches" / control["function"]
            )
            actual = match.scratch_status_payload(
                match.evaluate_source_overlay(config, source)
            )
            # Whole-object hashes include COFF timestamps. Compare deterministic
            # function code, compiler selection and native matching dimensions.
            keys = (
                "state",
                "body_byte_exact",
                "code_sha256",
                "match_ratio",
                "target_instructions",
                "candidate_instructions",
                "prefix_instructions",
                "references",
                "compiler",
                "cflags",
                "error",
            )
            changes = {
                key: {"expected": control["measured"][key], "actual": actual[key]}
                for key in keys
                if actual[key] != control["measured"][key]
            }
            if changes:
                raise ValueError(json.dumps(changes, indent=2))
            print(
                f"Replay agrees: {control['function']} / {control['batch']} / {control['label']}"
            )


if __name__ == "__main__":
    main()
