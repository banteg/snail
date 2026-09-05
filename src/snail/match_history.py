"""Read-only search of receipts and hash-verified mutation recipe edits."""

from __future__ import annotations

import difflib
import json
from pathlib import Path

from .match_mutation import load_mutation_spec


def search_history(paths: list[Path], *, query: str = "", current_epochs=None) -> dict:
    rows, errors = [], []
    for path in paths:
        specs = {}
        for recipe in sorted(path.parent.glob("*.json")):
            try:
                spec = load_mutation_spec(recipe)
                specs.setdefault(spec.sha256, (recipe, spec))
            except (OSError, ValueError, TypeError):
                continue
        for line_number, line in enumerate(path.read_text().splitlines(), 1):
            if not line.strip():
                continue
            try:
                record = json.loads(line)
                if not isinstance(record, dict):
                    raise TypeError("expected an object")
            except (ValueError, TypeError) as error:
                errors.append(f"{path}:{line_number}: {error}")
                continue
            # Audit annotations are not new experiments.
            if record.get("kind") in {"experiment-audit", "mutation-error-audit"}:
                continue
            recipe, spec = specs.get(record.get("spec_sha256"), (None, None))
            epoch = record.get("baseline_epoch")
            current = (current_epochs or {}).get(path.parent.resolve())
            epoch_state = (
                "unknown"
                if not epoch or not current
                else "current"
                if epoch == current
                else "historical"
            )
            results = record.get("results", [record])
            if not isinstance(results, list) or any(
                not isinstance(r, dict) for r in results
            ):
                errors.append(
                    f"{path}:{line_number}: results must be an array of objects"
                )
                continue
            for result in results:
                edits = []
                evidence = "unavailable"
                choices = result.get("mutations", [])
                if not isinstance(choices, list) or any(
                    not isinstance(c, dict) for c in choices
                ):
                    errors.append(
                        f"{path}:{line_number}: mutations must be an array of objects"
                    )
                    continue
                if spec is not None and choices:
                    evidence = "hash-verified recipe"
                    for choice in choices:
                        site = next(
                            (s for s in spec.sites if s.name == choice.get("site")),
                            None,
                        )
                        index = choice.get("replacement_index")
                        if (
                            site is None
                            or not isinstance(index, int)
                            or not 1 <= index <= len(site.replacements)
                            or site.replacements[index - 1].name
                            != choice.get("replacement")
                        ):
                            evidence = "receipt/recipe choice mismatch"
                            edits = []
                            break
                        replacement = site.replacements[index - 1]
                        edits.append(
                            {
                                "site": site.name,
                                "occurrence": site.occurrence,
                                "find": site.find,
                                "replace": replacement.text,
                                "diff": "\n".join(
                                    difflib.unified_diff(
                                        site.find.splitlines(),
                                        replacement.text.splitlines(),
                                        fromfile="recipe anchor",
                                        tofile="replacement",
                                        lineterm="",
                                    )
                                ),
                            }
                        )
                row = {
                    "scratch": path.parent.name,
                    "path": str(path),
                    "line": line_number,
                    "recorded_at": record.get("recorded_at"),
                    "epoch": epoch_state,
                    "baseline_epoch": epoch,
                    "hypothesis": record.get("hypothesis"),
                    "label": result.get("label", record.get("kind", "probe")),
                    "spec": str(recipe) if recipe else None,
                    "spec_sha256": record.get("spec_sha256"),
                    "edit_evidence": evidence,
                    "edits": edits,
                    "status": result.get("status", record.get("probe")),
                    "delta": result.get("delta"),
                    "tradeoffs": result.get("tradeoffs", []),
                }
                if query.casefold() in json.dumps(row, sort_keys=True).casefold():
                    rows.append(row)
    rows.sort(
        key=lambda r: (r["recorded_at"] or "", r["path"], r["line"]), reverse=True
    )
    return {
        "schema": 1,
        "kind": "experiment-history",
        "rows": rows,
        "errors": errors,
        "caveat": "Recipe edits are hash-verified snippets, not reconstructed historical source. Historical failures do not establish exhaustion.",
    }


def render_history(payload: dict) -> str:
    lines = [payload["caveat"]]
    for row in payload["rows"]:
        lines.append(f"\n{row['path']}:{row['line']} [{row['epoch']}] {row['label']}")
        if row["hypothesis"]:
            lines.append(f"hypothesis: {row['hypothesis']}")
        lines.append(
            f"edits: {row['edit_evidence']} ({row['spec'] or 'recipe unavailable'})"
        )
        lines.append(f"status: {json.dumps(row['status'], sort_keys=True)}")
        if row["tradeoffs"]:
            lines.append(f"tradeoffs: {', '.join(row['tradeoffs'])}")
        lines.extend(edit["diff"] for edit in row["edits"])
    return "\n".join(lines)
