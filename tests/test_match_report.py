import json
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


def test_every_chart_measure_reconciles_units_and_categories(monkeypatch):
    monkeypatch.setattr(report, "load_function_symbol_manifest", lambda _: SimpleNamespace(functions=[
        SimpleNamespace(address=1, port_scope="core"),
        SimpleNamespace(address=200, port_scope="replaceable-platform"),
        SimpleNamespace(address=600, port_scope="core"),
    ]))
    monkeypatch.setattr(report, "_load_attribution", lambda: {})
    result = report.build_report([
        row(size=100),
        row(200, 300, ratio=0.5, matched=False),
        row(600, 500, ratio=0, matched=False, candidate=None, source=None),
        row(1200, 100, ratio=0, matched=False, candidate=None, source=None, is_function=False),
    ])
    groups = [(result["measures"], result["units"])] + [
        (category["measures"], [unit for unit in result["units"] if category["id"] in unit["metadata"]["progress_categories"]])
        for category in result["categories"]
    ]
    for measures, units in groups:
        total = sum(int(unit["measures"]["total_code"]) for unit in units)
        matched = sum(int(unit["measures"]["matched_code"]) for unit in units)
        weighted = sum(int(unit["measures"]["total_code"]) * unit["measures"]["fuzzy_match_percent"] for unit in units)
        assert int(measures["total_code"]) == total
        assert int(measures["matched_code"]) == matched
        assert measures["matched_code_percent"] == pytest.approx(100 * matched / total if total else 0)
        assert measures["fuzzy_match_percent"] == pytest.approx(weighted / total if total else 0)
        functions = sum(len(unit["functions"]) for unit in units)
        exact = sum(function["fuzzy_match_percent"] == 100 for unit in units for function in unit["functions"])
        assert measures["total_functions"] == functions
        assert measures["matched_functions"] == exact
        assert measures["matched_functions_percent"] == pytest.approx(100 * exact / functions if functions else 0)
        assert measures["total_units"] == len(units)
        assert measures["complete_units"] == 0
        assert measures["complete_code"] == measures["total_data"] == measures["matched_data"] == measures["complete_data"] == "0"
        assert measures["complete_code_percent"] == measures["matched_data_percent"] == measures["complete_data_percent"] == 0
    assert {c["id"] for c in result["categories"]} == {"game", "libs", "libs.d3dx8", "libs.msvc6-crt", "libs.libpng-1.2.5", "libs.zlib-1.2.1", "other"}


def test_coverage_discount_and_exact_cap_are_applied_before_weighting(monkeypatch):
    monkeypatch.setattr(report, "_load_attribution", lambda: {})
    result = report.build_report([
        row(size=100, ratio=0.25, matched=False),
        row(200, 300, ratio=1.0, matched=False),
    ])
    # The evidence ratio already discounts untested owned bytes. Audit-state
    # 100% instructions remain partial in both function tiles and totals.
    assert result["units"][0]["functions"][0]["fuzzy_match_percent"] == 25
    assert result["units"][1]["functions"][0]["fuzzy_match_percent"] == 99.99
    assert result["measures"]["fuzzy_match_percent"] == pytest.approx((100 * 25 + 300 * 99.99) / 400)
    assert result["measures"]["matched_code"] == "0"


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
    category = result["categories"][0]
    assert (category["id"], category["name"]) == ("game", "Game & Engine")
    m = category["measures"]
    assert m["total_code"] == "900"
    assert m["matched_code"] == "100"
    assert m["fuzzy_match_percent"] == pytest.approx(250 / 900 * 100)
    assert m["total_functions"] == m["total_units"] == 3
    assert m["matched_functions"] == 1
    assert m["complete_code"] == "0"
    assert [u["metadata"]["progress_categories"] for u in result["units"]] == [
        ["game"], ["game"], ["game"], ["other"], ["other"], ["other"],
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
        "schema": report.EVIDENCE_SCHEMA, "version": report.VERSION, "scope": "full-executable-code",
        "inputs": {"source": "pinned"}, "functions": [function],
        "external_inputs": {"image": {"path": "artifacts/bin/target.exe", "sha256": "a" * 64},
                            "compilers": {}, "runner": {"sha256": "b" * 64}},
    }
    evidence["identities"] = report.measurement_identities(evidence["inputs"], evidence["external_inputs"])
    evidence["verification_mode"] = report.VERIFICATION_MODE
    evidence["progress_delta"] = report.progress_delta(None, evidence)
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


def test_ownership_filters_partition_all_code_without_adding_match_credit(monkeypatch):
    monkeypatch.setattr(report, "load_function_symbol_manifest", lambda _: SimpleNamespace(functions=[
        SimpleNamespace(address=1, port_scope="core"),
    ]))
    monkeypatch.setattr(report, "_load_attribution", lambda: {
        200: {"name": "png_known", "component": "libpng-1.2.5"},
        600: {"name": "noop_initializer", "component": "game-init"},
    })
    result = report.build_report([
        row(), row(200, 300, candidate=None, source=None, ratio=0, matched=False),
        row(600, 6, candidate=None, source=None, ratio=0, matched=False),
        row(700, 50, candidate=None, source=None, ratio=0, matched=False),
    ])
    categories = {c["id"]: c["measures"] for c in result["categories"]}
    assert sum(int(categories[c]["total_code"]) for c in ("game", "libs", "other")) == 456
    assert categories["game"]["total_code"] == "106"
    assert categories["libs"]["total_code"] == categories["libs.libpng-1.2.5"]["total_code"] == "300"
    assert categories["libs"]["matched_code"] == "0"
    assert categories["libs"]["fuzzy_match_percent"] == 0
    assert result["measures"]["matched_code"] == "100"
    assert result["units"][1]["functions"][0]["metadata"]["demangled_name"] == "png_known"
    assert result["units"][1]["metadata"]["progress_categories"] == ["libs", "libs.libpng-1.2.5"]


def test_translation_unit_order_invalidates_report_inputs(tmp_path):
    import subprocess

    subprocess.run(["git", "init", "-q", str(tmp_path)], check=True)
    root = tmp_path / "tools/match"
    root.mkdir(parents=True)
    for name in ("a", "b"):
        source = root / "scratches" / name
        source.mkdir(parents=True)
        (source / "scratch.cpp").write_text(f"int {name}() {{ return 0; }}\n")
        (source / "scratch.conf").write_text(f"FUNCTION={name}\n")
    units = root / "translation_units.json"
    first = {
        "schema": 1,
        "units": [{"name": "unit", "source_object": "Unit.o", "members": ["a", "b"]}],
    }
    units.write_text(json.dumps(first))
    before = report.repository_inputs(tmp_path)
    first["units"][0]["members"].reverse()
    units.write_text(json.dumps(first))
    after = report.repository_inputs(tmp_path)
    assert before != after, (
        "Changed compiler source composition/order is invisible to report input pins"
    )
