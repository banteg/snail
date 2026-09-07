from copy import deepcopy
from itertools import pairwise
from pathlib import Path
from types import SimpleNamespace

import pytest

from snail import match_report as report


def row(address=1, size=100, **changes):
    return {
        "address": address, "name": f"function_{address}", "size": size,
        "ranges": [[address, address + size]], "is_function": True,
        "candidate": "source", "source": f"src/{address}/scratch.cpp",
        "ratio": 1.0, "matched": True, "linked": False, **changes,
    }


def test_full_scope_weighting_and_no_prebuilt_or_unassigned_credit():
    result = report.build_report([
        row(size=100), row(200, 300, ratio=0.5, matched=False),
        row(600, 500, candidate="archive", source=None),
        row(1200, 100, candidate=None, source=None, ratio=0, matched=False, is_function=False),
    ])
    m = result["measures"]
    assert m["total_code"] == "1000"
    assert m["matched_code"] == "100"
    assert m["fuzzy_match_percent"] == 25
    assert m["matched_code_percent"] == 10
    assert m["total_functions"] == 3
    assert m["matched_functions"] == 1
    assert m["total_units"] == 4
    assert m["complete_code"] == "0"
    assert result["units"][-1]["functions"] == []
    assert result["units"][2]["functions"][0]["fuzzy_match_percent"] == 0
    assert result["categories"][0]["measures"]["total_code"] == "0"


def test_game_category_keeps_platform_and_unrecovered_game_but_excludes_unknown_and_libraries(monkeypatch):
    monkeypatch.setattr(report, "load_function_symbol_manifest", lambda _: SimpleNamespace(functions=[
        SimpleNamespace(address=1, port_scope="core"),
        SimpleNamespace(address=200, port_scope="boundary"),
        SimpleNamespace(address=600, port_scope="replaceable-platform"),
        SimpleNamespace(address=1200, port_scope="third-party"),
    ]))
    result = report.build_report([
        row(size=100), row(200, 300, ratio=0.5, matched=False),
        row(600, 500, candidate=None, source=None, ratio=0, matched=False),
        row(1200, 100), row(1400, 200),
        row(1800, 50, candidate=None, source=None, ratio=0, matched=False, is_function=False),
    ])
    category, = result["categories"]
    assert (category["id"], category["name"]) == ("game", "Game & Engine")
    m = category["measures"]
    assert m["total_code"] == "900"
    assert m["matched_code"] == "100"
    assert m["fuzzy_match_percent"] == pytest.approx(250 / 900 * 100)
    assert m["total_functions"] == m["total_units"] == 3
    assert m["matched_functions"] == 1
    assert m["complete_code"] == "0"
    assert [u["metadata"]["progress_categories"] for u in result["units"]] == [
        ["game"], ["game"], ["game"], [], [], [],
    ]
    assert result["measures"]["total_code"] == "1250"
    assert result["measures"]["matched_code"] == "400"


def test_reference_pending_perfect_ratio_stays_visibly_partial():
    result = report.build_report([row(matched=False)])
    assert result["measures"]["matched_code"] == "0"
    assert result["units"][0]["functions"][0]["fuzzy_match_percent"] == 99.99


@pytest.mark.parametrize("changes", [
    {"ratio": float("nan")}, {"ratio": 1.1}, {"size": -1},
    {"ratio": 0.5}, {"linked": True},
])
def test_invalid_or_unsupported_progress_fails(changes):
    with pytest.raises(ValueError):
        report.build_report([row(**changes)])


def test_duplicate_identity_fails_and_duplicate_names_are_disambiguated():
    with pytest.raises(ValueError, match="duplicate"):
        report.build_report([row(), row()])
    result = report.build_report([row(name="same"), row(200, name="same")])
    assert len({u["name"] for u in result["units"]}) == 2


def test_portable_validation_rejects_stale_source_and_changed_denominator(monkeypatch, tmp_path):
    function = row(candidate=None, source=None, ratio=0, matched=False)
    fields = ("address", "name", "size", "ranges", "is_function")
    monkeypatch.setattr(report, "REPO_ROOT", tmp_path)
    monkeypatch.setattr(report.matchlib, "DEFAULT_MATCH_ROOT", tmp_path / "tools/match")
    monkeypatch.delenv("WIBO", raising=False)
    monkeypatch.setattr(report, "load_function_symbol_manifest", lambda _: SimpleNamespace(
        primary_target="artifacts/bin/target.exe", unwrapped_sha256="a" * 64,
    ))
    monkeypatch.setattr(report, "repository_inputs", lambda: {"source": "pinned"})
    monkeypatch.setattr(report, "inventory", lambda: [{k: function[k] for k in fields}])
    evidence = {
        "schema": 1, "version": report.VERSION, "scope": "full-executable-code",
        "inputs": {"source": "pinned"}, "functions": [function],
        "external_inputs": {"image": {"path": "artifacts/bin/target.exe", "sha256": "a" * 64},
                            "compilers": {}, "runner": {"sha256": "b" * 64}},
    }
    report.validate_evidence(evidence)  # No game executable or compiler in CI.
    changed = deepcopy(evidence)
    changed["functions"][0]["size"] = 99
    with pytest.raises(ValueError, match="denominator"):
        report.validate_evidence(changed)
    changed = deepcopy(evidence)
    changed["inputs"]["source"] = "old"
    with pytest.raises(ValueError, match="stale"):
        report.validate_evidence(changed)


def test_full_inventory_partitions_every_byte_once_and_keeps_curated_entries():
    # Saved native evidence is tracked; no proprietary image is needed here.
    rows = report.inventory()
    ranges = sorted((a, b) for r in rows for a, b in r["ranges"])
    assert all(left[1] <= right[0] for left, right in pairwise(ranges))
    assert sum(b - a for a, b in ranges) == sum(r["size"] for r in rows) == 596823
    assert next(r for r in rows if r["address"] == 0x406DA0)["name"] == "initialize_main_loop_timing_state"
    assert any(not r["is_function"] for r in rows)


def test_added_or_deleted_source_invalidates_input_set(tmp_path: Path):
    import subprocess

    subprocess.run(["git", "init", "-q", str(tmp_path)], check=True)
    source = tmp_path / "tools/match/scratches/example/scratch.cpp"
    source.parent.mkdir(parents=True)
    source.write_text("void example() {}")
    assert source.relative_to(tmp_path).as_posix() in report.repository_inputs(tmp_path)
    subprocess.run(["git", "-C", str(tmp_path), "add", "."], check=True)
    source.unlink()
    with pytest.raises(ValueError, match="missing report input"):
        report.repository_inputs(tmp_path)
