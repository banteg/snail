from __future__ import annotations

import json
from pathlib import Path

import pytest

from snail.cli import main
from snail.match import (
    LoadedImage,
    ScratchConfig,
    ScratchStatus,
    TriageExperimentEvidence,
    TriageMobileEvidence,
    TriageRow,
    collect_triage_rows,
    load_scratch_config,
    scratch_status_payload,
)
from snail.symbols import FunctionSymbol, FunctionSymbolManifest


def _manifest() -> FunctionSymbolManifest:
    return FunctionSymbolManifest(
        name="test",
        primary_target="game.exe",
        reference_target="wrapped.exe",
        image_base=0x1000,
        unwrapped_sha256="0" * 64,
        source_database=None,
        functions=(
            FunctionSymbol(0x1000, "foo", aliases=("old_foo",)),
            FunctionSymbol(0x1010, "bar"),
            FunctionSymbol(0x1020, "platform", port_scope="replaceable-platform"),
        ),
    )


def _config(directory: Path, *, function: str = "old_foo") -> ScratchConfig:
    return ScratchConfig(
        directory=directory,
        function=function,
        compiler="msvc6.5",
        cflags="/O2 /G5 /W3",
        end_va=None,
        symbol=None,
        recovery="semantic-complete",
        residuals=("compiler",),
    )


def _status(config: ScratchConfig, *, ratio: float = 0.75) -> ScratchStatus:
    return ScratchStatus(
        config=config,
        address=0x1000,
        target_size=16,
        ratio=ratio,
        prefix_instructions=3,
        target_instructions=8,
        candidate_instructions=8,
        masked_ok=2,
    )


def test_scratch_config_is_strict_and_parses_recovery_metadata(tmp_path: Path) -> None:
    (tmp_path / "scratch.conf").write_text(
        "FUNCTION=foo\n"
        "RECOVERY=semantic-complete\n"
        "RESIDUAL=compiler,references,compiler # reviewed\n",
        encoding="utf-8",
    )

    config = load_scratch_config(tmp_path)

    assert config.recovery == "semantic-complete"
    assert config.residuals == ("compiler", "references")


@pytest.mark.parametrize(
    ("config", "message"),
    [
        ("FUNCTION=foo\nCFLAG=/O2\n", "unknown field 'CFLAG'"),
        ("FUNCTION=foo\ntypo\n", "invalid assignment 'typo'"),
        ("FUNCTION=foo\nRECOVERY=done\n", "invalid RECOVERY='done'"),
        ("FUNCTION=foo\nRESIDUAL=guess\n", "invalid RESIDUAL values guess"),
        ("FUNCTION=foo\nFUNCTION=bar\n", "assigns FUNCTION more than once"),
    ],
)
def test_scratch_config_rejects_invalid_fields(
    tmp_path: Path,
    config: str,
    message: str,
) -> None:
    (tmp_path / "scratch.conf").write_text(config, encoding="utf-8")

    with pytest.raises(ValueError, match=message):
        load_scratch_config(tmp_path)


def test_triage_joins_by_address_and_surfaces_search_and_mobile_evidence(
    monkeypatch: pytest.MonkeyPatch,
    tmp_path: Path,
) -> None:
    scratch = tmp_path / "tools/match/scratches/legacy-name"
    scratch.mkdir(parents=True)
    (scratch / "experiments.jsonl").write_text("{}\n", encoding="utf-8")
    status = _status(_config(scratch))
    image = LoadedImage(
        mapped=b"\x01" * 0x28 + b"\xcc" * 0x18,
        image_base=0x1000,
        size_of_image=0x40,
    )
    experiment_row = {
        "records": 4,
        "mutation_sweeps": 3,
        "probes": 1,
        "evaluated_variants": 20,
        "unique_variants": 18,
        "unique_specs": 3,
        "no_improvement_streak": 3,
        "flags": [],
    }
    monkeypatch.setattr("snail.match.load_image", lambda *_args: image)
    monkeypatch.setattr(
        "snail.match_experiments.summarize_experiment_log",
        lambda *_args, **_kwargs: (experiment_row, []),
    )

    rows = collect_triage_rows(
        _manifest(),
        tmp_path / "game.exe",
        [status],
        mobile_crosswalk={
            "entries": [
                {
                    "windows_name": "foo",
                    "status": "verified",
                    "android_body_count": 1,
                    "ios_body_count": 2,
                    "confidence": "high",
                    "source_object": "Game.o",
                    "source_object_evidence": "unique-ios-class-object",
                }
            ]
        },
    )

    assert [row.function for row in rows] == ["foo", "bar"]
    foo, bar = rows
    assert foo.state == "wip"
    assert foo.recovery == "semantic-complete"
    assert foo.residuals == ("compiler",)
    assert foo.experiments == TriageExperimentEvidence(
        records=4,
        mutation_sweeps=3,
        probes=1,
        evaluated_variants=20,
        unique_variants=18,
        unique_specs=3,
        no_improvement_streak=3,
        flags=(),
    )
    assert foo.mobile == TriageMobileEvidence(
        status="verified",
        android_bodies=1,
        ios_bodies=2,
        confidence="high",
        source_object="Game.o",
        source_object_evidence="unique-ios-class-object",
    )
    assert foo.mobile.verified
    assert bar.state == "missing"
    assert bar.target_size == 16


def test_exact_status_overrides_configured_recovery_and_residuals(
    tmp_path: Path,
) -> None:
    status = _status(_config(tmp_path), ratio=1.0)

    payload = scratch_status_payload(status)

    assert payload["recovery"] == "exact"
    assert payload["residuals"] == []


def test_triage_cli_filters_and_emits_json(
    monkeypatch: pytest.MonkeyPatch,
    tmp_path: Path,
    capsys: pytest.CaptureFixture[str],
) -> None:
    status = _status(_config(tmp_path))
    row = TriageRow(
        function="foo",
        address=0x1000,
        target_size=16,
        state="wip",
        exact_bytes=0,
        fuzzy_weighted_bytes=12,
        candidate_bytes=16,
        scratch_count=1,
        best_status=status,
        experiments=TriageExperimentEvidence(
            records=3,
            unique_variants=10,
            no_improvement_streak=3,
            flags=(),
        ),
        mobile=TriageMobileEvidence(
            status="verified",
            android_bodies=1,
            confidence="high",
        ),
    )
    monkeypatch.setattr(
        "snail.cli.load_function_symbol_manifest", lambda *_args: _manifest()
    )
    monkeypatch.setattr(
        "snail.cli.collect_scratch_statuses", lambda *_args, **_kwargs: [status]
    )
    monkeypatch.setattr(
        "snail.cli.collect_triage_rows", lambda *_args, **_kwargs: [row]
    )
    monkeypatch.setattr("snail.cli.load_json", lambda *_args: {"entries": []})

    exit_code = main(
        [
            "match",
            "triage",
            "--state",
            "wip",
            "--recovery",
            "semantic-complete",
            "--residual",
            "compiler",
            "--mobile",
            "verified",
            "--sort",
            "unexplored",
            "--json",
        ]
    )

    assert exit_code == 0
    payload = json.loads(capsys.readouterr().out)
    assert payload["summary"]["row_count"] == 1
    assert payload["rows"][0]["function"] == "foo"
    assert payload["rows"][0]["recovery"] == "semantic-complete"
    assert payload["rows"][0]["experiments"]["flags"] == []
    assert payload["rows"][0]["mobile"]["verified"] is True
