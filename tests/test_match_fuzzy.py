"""Public fuzzy uses the real pinned engine, independently of exact proof."""

import json
from pathlib import Path
from types import SimpleNamespace

import pytest

from snail import match_fuzzy as fuzzy
from snail import match_objdiff as snapshots


@pytest.mark.parametrize(
    "target,candidate,percent",
    [
        ("b801000000c3", "b801000000c3", 100),
        ("b801000000c3", "b802000000c3", 99.5),
        ("8bc1c3", "8bc2c3", 97.5),
        ("83c001c3", "83e801c3", 70),
        ("b801000000c3", "b80100000090c3", 50),
        ("8b0411c3", "8b040ac3", 95),
    ],
)
def test_pinned_objdiff_instruction_controls(tmp_path, target, candidate, percent):
    try:
        cli = fuzzy.binary()
    except ValueError as exc:
        pytest.skip(str(exc))
    for side, code in (("target", target), ("candidate", candidate)):
        (tmp_path / f"{side}.obj").write_bytes(snapshots.coff(bytes.fromhex(code), []))
    assert fuzzy.score_objects(cli, tmp_path) * 100 == pytest.approx(percent)


@pytest.mark.parametrize("score", [float("nan"), -1, 101, True])
def test_invalid_engine_score_is_rejected(tmp_path, monkeypatch, score):
    symbol = {
        "name": snapshots.DISPLAY_SYMBOL,
        "kind": "SYMBOL_FUNCTION",
        "match_percent": score,
    }
    monkeypatch.setattr(
        fuzzy.subprocess,
        "run",
        lambda *a, **k: SimpleNamespace(
            stdout=json.dumps(
                {"left": {"symbols": [symbol]}, "right": {"symbols": [symbol]}}
            )
        ),
    )
    with pytest.raises(ValueError, match="percentage"):
        fuzzy.score_objects(Path("cli"), tmp_path)


def test_missing_candidate_does_not_become_perfect_fuzzy(tmp_path, monkeypatch):
    symbol = {
        "name": snapshots.DISPLAY_SYMBOL,
        "kind": "SYMBOL_FUNCTION",
        "match_percent": 100,
    }
    monkeypatch.setattr(
        fuzzy.subprocess,
        "run",
        lambda *a, **k: SimpleNamespace(
            stdout=json.dumps({"left": {"symbols": [symbol]}, "right": {"symbols": []}})
        ),
    )
    with pytest.raises(ValueError, match="bounded function"):
        fuzzy.score_objects(Path("cli"), tmp_path)


def test_unpinned_binary_is_rejected(tmp_path, monkeypatch):
    cli = tmp_path / "objdiff"
    cli.write_bytes(b"wrong version")
    monkeypatch.setenv("SNAIL_OBJDIFF_CLI", str(cli))
    with pytest.raises(ValueError, match="SHA-256"):
        fuzzy.binary()
