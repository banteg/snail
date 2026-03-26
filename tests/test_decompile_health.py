from __future__ import annotations

import json
from pathlib import Path

from snail.decompile_health import evaluate_decompile_health_checks, load_decompile_health_checks


def test_load_decompile_health_checks_parses_minimal_config(tmp_path: Path) -> None:
    config_path = tmp_path / "health.json"
    config_path.write_text(
        json.dumps(
            {
                "checks": [
                    {
                        "name": "sample",
                        "artifact": "analysis/decompile/binja/functions/foo.c",
                        "required_substrings": ["foo"],
                        "forbidden_substrings": ["bar"],
                        "min_counts": {"foo": 1},
                        "max_counts": {"bar": 0},
                    }
                ]
            }
        ),
        encoding="utf-8",
    )

    checks = load_decompile_health_checks(config_path)

    assert len(checks) == 1
    assert checks[0].name == "sample"
    assert checks[0].required_substrings == ("foo",)
    assert checks[0].forbidden_substrings == ("bar",)
    assert checks[0].min_counts == {"foo": 1}
    assert checks[0].max_counts == {"bar": 0}


def test_evaluate_decompile_health_checks_flags_missing_and_over_limit(tmp_path: Path) -> None:
    artifact = tmp_path / "analysis/decompile/binja/functions/foo.c"
    artifact.parent.mkdir(parents=True, exist_ok=True)
    artifact.write_text("foo foo __offset(\n", encoding="utf-8")
    config_path = tmp_path / "health.json"
    config_path.write_text(
        json.dumps(
            {
                "checks": [
                    {
                        "name": "sample",
                        "artifact": "analysis/decompile/binja/functions/foo.c",
                        "required_substrings": ["foo", "missing"],
                        "forbidden_substrings": ["forbidden"],
                        "min_counts": {"foo": 3},
                        "max_counts": {"__offset(": 0},
                    }
                ]
            }
        ),
        encoding="utf-8",
    )

    summary = evaluate_decompile_health_checks(
        repo_root=tmp_path,
        checks=load_decompile_health_checks(config_path),
    )

    assert summary["passed"] is False
    assert summary["failing_check_count"] == 1
    check = summary["checks"][0]
    assert check["observed_counts"]["foo"] == 2
    assert any("missing required substring: missing" == failure for failure in check["failures"])
    assert any("count below minimum for foo: 2 < 3" == failure for failure in check["failures"])
    assert any("count above maximum for __offset(: 1 > 0" == failure for failure in check["failures"])


def test_evaluate_decompile_health_checks_passes_clean_artifact(tmp_path: Path) -> None:
    artifact = tmp_path / "analysis/decompile/ida/functions/foo.c"
    artifact.parent.mkdir(parents=True, exist_ok=True)
    artifact.write_text("cached_camera_target_world follow_state desired_matrix\n", encoding="utf-8")
    config_path = tmp_path / "health.json"
    config_path.write_text(
        json.dumps(
            {
                "checks": [
                    {
                        "name": "sample",
                        "artifact": "analysis/decompile/ida/functions/foo.c",
                        "required_substrings": [
                            "cached_camera_target_world",
                            "follow_state",
                            "desired_matrix"
                        ],
                        "forbidden_substrings": ["__asm", "__offset("]
                    }
                ]
            }
        ),
        encoding="utf-8",
    )

    summary = evaluate_decompile_health_checks(
        repo_root=tmp_path,
        checks=load_decompile_health_checks(config_path),
    )

    assert summary["passed"] is True
    assert summary["failing_check_count"] == 0
