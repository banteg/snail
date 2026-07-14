from __future__ import annotations

import importlib.util
from pathlib import Path
import sys

import pytest


REPO_ROOT = Path(__file__).resolve().parents[1]


def _load_script(monkeypatch: pytest.MonkeyPatch, relative_path: str, module_name: str):
    path = REPO_ROOT / relative_path
    monkeypatch.syspath_prepend(str(path.parent))
    spec = importlib.util.spec_from_file_location(module_name, path)
    assert spec is not None
    assert spec.loader is not None
    module = importlib.util.module_from_spec(spec)
    sys.modules[module_name] = module
    spec.loader.exec_module(module)
    return module


def test_binja_focused_summary_reports_only_refreshed_exports(
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    module = _load_script(
        monkeypatch,
        "tools/binja/export_manifest_functions.py",
        "test_binja_export_manifest_functions",
    )
    refreshed = [{"address": "0x435180", "name": "merge_track_tile_runs"}]
    index = {
        "selected_count": 3,
        "function_count": 3,
        "exports": [*refreshed, {"address": "0x1"}, {"address": "0x2"}],
    }

    summary = module._command_summary(
        index,
        refreshed=refreshed,
        index_path=REPO_ROOT / "analysis/decompile/binja/index.json",
        focused=True,
    )

    assert summary["selected_count"] == 1
    assert summary["refreshed_count"] == 1
    assert summary["function_count"] == 1
    assert summary["index_function_count"] == 3
    assert summary["exports"] == refreshed


def test_ida_focused_summary_reports_only_refreshed_exports(
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    module = _load_script(
        monkeypatch,
        "tools/ida/export_manifest_functions.py",
        "test_ida_export_manifest_functions",
    )
    refreshed = [{"address": "0x435180", "name": "merge_track_tile_runs"}]
    index = {
        "selected_count": 3,
        "function_count": 3,
        "exported": [*refreshed, {"address": "0x1"}, {"address": "0x2"}],
    }

    summary = module._command_summary(
        index,
        refreshed=refreshed,
        index_path=REPO_ROOT / "analysis/decompile/ida/index.json",
        focused=True,
    )

    assert summary["selected_count"] == 1
    assert summary["refreshed_count"] == 1
    assert summary["function_count"] == 1
    assert summary["index_function_count"] == 3
    assert summary["exported"] == refreshed
