from __future__ import annotations

import json
from pathlib import Path
from typing import Any

import pytest

from snail.cli import main
from snail.match import load_scratch_config, scratch_dependency_sha256
from snail.match_experiments import summarize_experiments


def _result(
    source: str,
    fuzzy_delta: float,
    *,
    prefix_delta: int = 0,
    mismatch_delta: int = 0,
) -> dict[str, Any]:
    return {
        "source_sha256": source,
        "status": {
            "compiler": "msvc6.5",
            "cflags": "/O2",
            "candidate_instructions": 11 if fuzzy_delta > 0 else 10,
            "target_instructions": 10,
        },
        "delta": {
            "fuzzy_weighted_bytes": fuzzy_delta,
            "prefix_instructions": prefix_delta,
            "first_mismatch": {
                "baseline_target_offset": 32,
                "probe_target_offset": 16 if prefix_delta < 0 else 32,
            },
            "references": {
                "ok": -1 if mismatch_delta else 0,
                "unresolved": 0,
                "mismatch": mismatch_delta,
            },
        },
    }


def _sweep(
    spec: str,
    results: list[dict[str, Any]],
    *,
    improves: bool = False,
    exact: bool = False,
) -> dict[str, Any]:
    winner = (
        {
            **results[0],
            "status": {
                **results[0]["status"],
                "state": "match" if exact else "wip",
            },
        }
        if improves
        else None
    )
    return {
        "schema": 1,
        "kind": "mutation-sweep",
        "recorded_at": "2026-07-27T00:00:00+00:00",
        "spec_sha256": spec,
        "evaluated_variants": len(results),
        "best_improves": improves,
        "winner": winner,
        "baseline": {
            "function": "foo",
            "image": "SnailMail_unwrapped.exe",
            "compiler": "msvc6.5",
            "cflags": "/O2",
            "candidate_instructions": 10,
            "target_instructions": 10,
        },
        "results": results,
    }


def _write_jsonl(path: Path, records: list[dict[str, Any]]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(
        "".join(json.dumps(record) + "\n" for record in records),
        encoding="utf-8",
    )


def test_experiment_summary_surfaces_repeats_stalls_and_tradeoffs(
    tmp_path: Path,
) -> None:
    log = tmp_path / "scratches" / "foo" / "experiments.jsonl"
    records: list[dict[str, Any]] = [
        _sweep(
            "spec-a",
            [_result("variant-a", 0), _result("variant-b", -2)],
        ),
        _sweep("spec-a", [_result("variant-a", 0)]),
        _sweep(
            "spec-b",
            [_result("variant-c", 5, prefix_delta=-1, mismatch_delta=1)],
            improves=True,
            exact=True,
        ),
        {
            "baseline": {
                "function": "foo",
                "image": "SnailMail_unwrapped.exe",
            },
            "probe": {"state": "wip"},
            "delta": {"fuzzy_weighted_bytes": 1},
        },
    ]
    _write_jsonl(log, records)

    payload = summarize_experiments(tmp_path)

    assert payload["kind"] == "snail-match-experiment-summary"
    assert payload["summary"] == {
        "files": 1,
        "records": 4,
        "kinds": {"mutation-sweep": 3, "probe": 1},
        "evaluated_variants": 4,
        "unique_variants": 3,
        "repeated_variants": 1,
        "improving_variants": 1,
        "neutral_variants": 2,
        "degrading_variants": 1,
        "tradeoff_variants": 1,
        "improving_sweeps": 1,
        "improving_probes": 1,
        "exact_winners": 1,
        "stalled_scratches": 0,
        "dependency_receipts": {
            "historical": 4,
            "current": 0,
            "stale": 0,
            "invalid": 0,
        },
        "errors": 0,
    }
    row = payload["rows"][0]
    assert row["scratch"] == "scratches/foo"
    assert row["repeated_spec_runs"] == 1
    assert row["no_improvement_streak"] == 0
    assert row["flags"] == [
        "repeated-variants",
        "repeated-specs",
        "metric-tradeoffs",
    ]


def test_experiment_dependency_receipts_distinguish_history_from_drift(
    tmp_path: Path,
    capsys: pytest.CaptureFixture[str],
) -> None:
    scratch = tmp_path / "scratches" / "foo"
    include = tmp_path / "include"
    compiler = tmp_path / "compilers" / "msvc6.5" / "Bin" / "CL.EXE"
    scratch.mkdir(parents=True)
    include.mkdir()
    compiler.parent.mkdir(parents=True)
    (tmp_path / "cl.sh").write_text("launcher\n", encoding="utf-8")
    compiler.write_bytes(b"compiler")
    (scratch / "scratch.conf").write_text(
        "FUNCTION=foo COMPILER=msvc6.5 CFLAGS=/O2\n",
        encoding="utf-8",
    )
    (scratch / "scratch.cpp").write_text(
        '#include "shared.h"\nint foo() { return shared; }\n',
        encoding="utf-8",
    )
    (include / "shared.h").write_text(
        '#include "nested.h"\n',
        encoding="utf-8",
    )
    nested = include / "nested.h"
    nested.write_text("const int shared = 1;\n", encoding="utf-8")

    dependency_sha = scratch_dependency_sha256(
        load_scratch_config(scratch),
        tmp_path,
    )
    record = _sweep("spec-a", [_result("variant-a", 0)])
    record["dependency_sha256"] = dependency_sha
    log = scratch / "experiments.jsonl"
    _write_jsonl(log, [record])

    payload = summarize_experiments(tmp_path)
    assert payload["summary"]["dependency_receipts"] == {
        "historical": 0,
        "current": 1,
        "stale": 0,
        "invalid": 0,
    }
    assert payload["errors"] == []

    nested.write_text("const int shared = 2;\n", encoding="utf-8")
    payload = summarize_experiments(tmp_path)
    assert payload["summary"]["dependency_receipts"] == {
        "historical": 0,
        "current": 0,
        "stale": 1,
        "invalid": 0,
    }
    assert payload["rows"][0]["flags"] == ["stale-dependencies"]
    assert payload["errors"] == []
    assert (
        main(
            [
                "match",
                "experiments",
                "--match-root",
                str(tmp_path),
                "--check",
                "--json",
            ]
        )
        == 0
    )
    capsys.readouterr()

    current_record = _sweep("spec-b", [_result("variant-a", 0)])
    current_record["dependency_sha256"] = scratch_dependency_sha256(
        load_scratch_config(scratch),
        tmp_path,
    )
    _write_jsonl(log, [record, current_record])
    payload = summarize_experiments(tmp_path)
    assert payload["summary"]["dependency_receipts"] == {
        "historical": 0,
        "current": 1,
        "stale": 1,
        "invalid": 0,
    }
    assert payload["summary"]["unique_variants"] == 2
    assert payload["summary"]["repeated_variants"] == 0

    del record["dependency_sha256"]
    del current_record["dependency_sha256"]
    _write_jsonl(log, [record, current_record])
    payload = summarize_experiments(tmp_path)
    assert payload["summary"]["dependency_receipts"] == {
        "historical": 2,
        "current": 0,
        "stale": 0,
        "invalid": 0,
    }
    assert payload["summary"]["unique_variants"] == 1
    assert payload["summary"]["repeated_variants"] == 1
    assert payload["errors"] == []

    record["dependency_sha256"] = "not-a-digest"
    _write_jsonl(log, [record])
    payload = summarize_experiments(tmp_path)
    assert payload["summary"]["dependency_receipts"]["invalid"] == 1
    assert payload["summary"]["errors"] == 1
    assert (
        main(
            [
                "match",
                "experiments",
                "--match-root",
                str(tmp_path),
                "--check",
                "--json",
            ]
        )
        == 1
    )
    capsys.readouterr()


def test_experiment_summary_check_rejects_malformed_logs(
    tmp_path: Path,
    capsys: pytest.CaptureFixture[str],
) -> None:
    log = tmp_path / "scratches" / "stalled" / "experiments.jsonl"
    _write_jsonl(
        log,
        [
            _sweep(
                f"spec-{index}",
                [_result(f"variant-{index}", 0)],
            )
            for index in range(3)
        ],
    )
    with log.open("a", encoding="utf-8") as handle:
        handle.write("{not-json}\n")

    exit_code = main(
        [
            "match",
            "experiments",
            "--match-root",
            str(tmp_path),
            "--sort",
            "no-improvement",
            "--check",
            "--json",
        ]
    )

    assert exit_code == 1
    captured = capsys.readouterr()
    assert captured.err == ""
    payload = json.loads(captured.out)
    assert payload["summary"]["stalled_scratches"] == 1
    assert payload["summary"]["errors"] == 1
    assert payload["rows"][0]["flags"] == ["stalled", "malformed"]
