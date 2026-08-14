from __future__ import annotations

import hashlib
import json
from dataclasses import replace
from pathlib import Path

import pytest

from snail.cli import main
from snail.match import (
    ProbeResult,
    ScratchConfig,
    ScratchStatus,
    evaluate_source_probe,
)


def _config(directory: Path) -> ScratchConfig:
    return ScratchConfig(
        directory=directory,
        function="foo",
        compiler="msvc6.5",
        cflags="/O2",
        end_va=None,
        symbol=None,
    )


def _status(
    config: ScratchConfig,
    ratio: float,
    *,
    prefix: int,
    candidate_instructions: int = 10,
) -> ScratchStatus:
    return ScratchStatus(
        config=config,
        address=0x401000,
        target_size=100,
        ratio=ratio,
        prefix_instructions=prefix,
        target_instructions=10,
        candidate_instructions=candidate_instructions,
        masked_ok=4,
        first_target_mismatch_offset=0x10,
        first_candidate_mismatch_offset=0x10,
    )


def test_source_probe_compares_one_baseline_and_overlay(
    monkeypatch: pytest.MonkeyPatch,
    tmp_path: Path,
) -> None:
    config = _config(tmp_path)
    (tmp_path / "scratch.cpp").write_text(
        "baseline source\n",
        encoding="utf-8",
    )
    calls: list[tuple[str, ScratchConfig]] = []

    def fake_overlay(
        profile: ScratchConfig,
        source_text: str,
        **_kwargs,
    ) -> ScratchStatus:
        if source_text == "baseline source\n":
            calls.append(("baseline", profile))
            return _status(
                replace(profile, directory=Path("/tmp/baseline-shadow")),
                0.5,
                prefix=2,
            )
        assert source_text == "alternate source\n"
        calls.append(("probe", profile))
        return _status(
            replace(profile, directory=Path("/tmp/probe-shadow")),
            0.75,
            prefix=4,
        )

    monkeypatch.setattr(
        "snail.match.evaluate_source_overlay",
        fake_overlay,
    )

    result = evaluate_source_probe(
        config,
        "alternate source\n",
        compiler="msvc6.5pp",
        cflags="/O2 /G5",
        label="same-tu",
    )

    assert [name for name, _profile in calls] == ["baseline", "probe"]
    assert all(profile.compiler == "msvc6.5pp" for _name, profile in calls)
    assert all(profile.cflags == "/O2 /G5" for _name, profile in calls)
    assert result.fuzzy_delta_bytes == 25
    assert result.ratio_delta == 0.25
    assert result.label == "same-tu"
    assert result.source_sha256 == hashlib.sha256(b"alternate source\n").hexdigest()


def test_probe_cli_records_the_complete_result(
    monkeypatch: pytest.MonkeyPatch,
    tmp_path: Path,
    capsys: pytest.CaptureFixture[str],
) -> None:
    scratch = tmp_path / "scratch"
    scratch.mkdir()
    tracked_source = scratch / "scratch.cpp"
    tracked_source.write_text("baseline source\n", encoding="utf-8")
    (scratch / "scratch.conf").write_text(
        "FUNCTION=foo\n",
        encoding="utf-8",
    )
    probe_source = tmp_path / "probe.cpp"
    probe_source.write_text("probe source\n", encoding="utf-8")
    config = _config(scratch)
    result = ProbeResult(
        baseline=_status(config, 0.5, prefix=2),
        probe=_status(
            replace(config, directory=Path("/tmp/shadow")),
            0.75,
            prefix=4,
        ),
        source_sha256="probe-sha",
        label="same-tu",
    )
    monkeypatch.setattr(
        "snail.cli.evaluate_source_probe",
        lambda *args, **kwargs: result,
    )
    monkeypatch.setattr(
        "snail.cli.scratch_dependency_sha256",
        lambda *args, **kwargs: "d" * 64,
    )
    monkeypatch.setattr(
        "snail.cli.scratch_experiment_epoch",
        lambda *args, **kwargs: "e" * 64,
    )

    exit_code = main(
        [
            "match",
            "probe",
            str(scratch),
            "--source",
            str(probe_source),
            "--label",
            "same-tu",
            "--record",
            "--json",
        ]
    )

    assert exit_code == 0
    payload = json.loads(capsys.readouterr().out)
    assert payload["label"] == "same-tu"
    assert payload["delta"]["fuzzy_weighted_bytes"] == 25
    assert payload["recorded_to"] == str(scratch / "experiments.jsonl")
    record = json.loads((scratch / "experiments.jsonl").read_text(encoding="utf-8"))
    assert record["schema"] == 1
    assert record["kind"] == "probe"
    assert record["source_sha256"] == "probe-sha"
    assert record["dependency_sha256"] == "d" * 64
    assert record["baseline_epoch"] == "e" * 64
    assert tracked_source.read_text(encoding="utf-8") == "baseline source\n"
