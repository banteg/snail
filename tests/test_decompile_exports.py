from __future__ import annotations

import importlib.util
from pathlib import Path
import sys
import types

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


def test_binja_focused_export_retires_stale_same_address_artifacts(
    monkeypatch: pytest.MonkeyPatch,
    tmp_path: Path,
) -> None:
    module = _load_script(
        monkeypatch,
        "tools/binja/export_manifest_functions.py",
        "test_binja_export_manifest_functions_cleanup",
    )
    stale = tmp_path / "00406c10-initialize_default_runtime_config.c"
    keep = tmp_path / "00406c10-initialize_default_runtime_config_thunk.c"
    other = tmp_path / "00406c20-initialize_default_runtime_config.c"
    for path in (stale, keep, other):
        path.write_text("artifact\n", encoding="utf-8")

    removed = module._prune_same_address_artifacts(
        tmp_path,
        address=0x406C10,
        keep_path=keep,
    )

    assert removed == [str(stale)]
    assert not stale.exists()
    assert keep.is_file()
    assert other.is_file()


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


def test_ida_artifact_normalization_strips_trailing_blank_lines(
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    for module_name in (
        "ida_funcs",
        "ida_hexrays",
        "ida_name",
        "ida_pro",
        "idc",
    ):
        monkeypatch.setitem(sys.modules, module_name, types.ModuleType(module_name))
    module = _load_script(
        monkeypatch,
        "tools/ida/export_function_artifact.py",
        "test_ida_export_function_artifact",
    )

    assert module._normalize_pseudocode("line 1  \nline 2\n\n") == "line 1\nline 2"
