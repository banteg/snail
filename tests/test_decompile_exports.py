from __future__ import annotations

import importlib.util
import json
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


def test_tracked_export_defaults_to_the_pinned_binja_target(
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    module = _load_script(
        monkeypatch,
        "tools/export_tracked_decompiles.py",
        "test_export_tracked_decompiles_target",
    )
    monkeypatch.setattr(sys, "argv", ["export_tracked_decompiles.py"])

    assert module.parse_args().bn_target == "SnailMail_unwrapped.exe.bndb"


def test_tracked_export_can_reuse_one_lane_index(
    monkeypatch: pytest.MonkeyPatch,
    tmp_path: Path,
) -> None:
    module = _load_script(
        monkeypatch,
        "tools/export_tracked_decompiles.py",
        "test_export_tracked_decompiles_lane_reuse",
    )
    index_path = tmp_path / "index.json"
    expected = {"tool": "binary_ninja", "exports": [{"address": "0x401000"}]}
    index_path.write_text(json.dumps(expected), encoding="utf-8")

    assert module._load_lane_result(index_path, lane="Binary Ninja") == expected


def test_tracked_export_rejects_missing_reused_lane_index(
    monkeypatch: pytest.MonkeyPatch,
    tmp_path: Path,
) -> None:
    module = _load_script(
        monkeypatch,
        "tools/export_tracked_decompiles.py",
        "test_export_tracked_decompiles_missing_lane_index",
    )

    with pytest.raises(RuntimeError, match="cannot skip IDA"):
        module._load_lane_result(tmp_path / "missing.json", lane="IDA")


def test_tracked_export_forwards_focused_selectors_to_ida_sync(
    monkeypatch: pytest.MonkeyPatch,
    tmp_path: Path,
) -> None:
    module = _load_script(
        monkeypatch,
        "tools/export_tracked_decompiles.py",
        "test_export_tracked_decompiles_ida_sync",
    )
    manifest = tmp_path / "functions.json"
    database = tmp_path / "game.i64"

    command = module._build_ida_sync_command(
        manifest_path=manifest,
        ida_bin="idat64",
        ida_db=database,
        selectors=["update_frontend_widget_interaction", "0x402820"],
    )

    assert command == [
        "uv",
        "run",
        "python",
        "tools/ida/sync_symbols.py",
        "--manifest",
        str(manifest),
        "--ida-bin",
        "idat64",
        "--db",
        str(database),
        "--only",
        "update_frontend_widget_interaction",
        "--only",
        "0x402820",
    ]


def test_ida_symbol_sync_filters_manifest_by_name_and_address(
    monkeypatch: pytest.MonkeyPatch,
    tmp_path: Path,
) -> None:
    module = _load_script(
        monkeypatch,
        "tools/ida/sync_symbols.py",
        "test_ida_sync_symbols_focused_manifest",
    )
    manifest = tmp_path / "functions.json"
    manifest.write_text(
        json.dumps(
            {
                "name": "test symbols",
                "functions": [
                    {"address": "0x402820", "name": "update_frontend_widget_interaction"},
                    {"address": "0x4035b0", "name": "border_input_text"},
                    {"address": "0x406da0", "name": "remove_tail_failed"},
                ],
            }
        ),
        encoding="utf-8",
    )

    filtered_path = module._write_filtered_manifest(
        manifest,
        ["update_frontend_widget_interaction", "0x4035b0"],
        tmp_path / "filtered",
    )
    filtered = json.loads(filtered_path.read_text(encoding="utf-8"))

    assert filtered["name"] == "test symbols"
    assert [function["name"] for function in filtered["functions"]] == [
        "update_frontend_widget_interaction",
        "border_input_text",
    ]


def test_ida_symbol_sync_rejects_unknown_focused_selector(
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    module = _load_script(
        monkeypatch,
        "tools/ida/sync_symbols.py",
        "test_ida_sync_symbols_unknown_selector",
    )

    with pytest.raises(RuntimeError, match="missing_function"):
        module._select_manifest_functions(
            {
                "functions": [
                    {"address": "0x402820", "name": "update_frontend_widget_interaction"}
                ]
            },
            ["missing_function"],
        )


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


def test_binja_export_refreshes_dependent_analysis(
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    module = _load_script(
        monkeypatch,
        "tools/binja/export_manifest_functions.py",
        "test_binja_export_manifest_functions_refresh",
    )
    calls = []

    def fake_run_bn_json(*args: str):
        calls.append(args)
        return {"refreshed": True}

    monkeypatch.setattr(module, "_run_bn_json", fake_run_bn_json)

    assert module._refresh_analysis("snail-mail.bndb") == {"refreshed": True}
    assert calls == [("refresh", "--target", "snail-mail.bndb")]


def test_binja_export_rejects_failed_analysis_refresh(
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    module = _load_script(
        monkeypatch,
        "tools/binja/export_manifest_functions.py",
        "test_binja_export_manifest_functions_failed_refresh",
    )
    monkeypatch.setattr(module, "_run_bn_json", lambda *_args: {"refreshed": False})

    with pytest.raises(RuntimeError, match="unexpected `bn refresh"):
        module._refresh_analysis("snail-mail.bndb")


def test_binja_export_reanalyzes_timed_out_functions(
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    module = _load_script(
        monkeypatch,
        "tools/binja/export_manifest_functions.py",
        "test_binja_export_manifest_functions_reanalysis",
    )
    calls = []

    def fake_run_bn_json(*args: str):
        calls.append(args)
        return {
            "result": {
                "reanalyzed": [
                    {
                        "address": "0x43f930",
                        "name": "update_slug_hazard_ai",
                        "verified": True,
                    }
                ],
                "interior_aliases": [],
                "unresolved": [],
                "snapshot_saved": True,
            }
        }

    monkeypatch.setattr(module, "_run_bn_json", fake_run_bn_json)
    function = module.FunctionSymbol(address=0x43F930, name="update_slug_hazard_ai")

    result = module._reanalyze_timed_out_functions("snail-mail.bndb", [function])

    assert result["snapshot_saved"] is True
    assert calls[0][:4] == ("py", "exec", "--target", "snail-mail.bndb")
    assert "NeverSkipFunctionAnalysis" in calls[0][-1]
    assert "get_functions_containing" in calls[0][-1]


def test_binja_export_accepts_decompilable_interior_manifest_target(
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    module = _load_script(
        monkeypatch,
        "tools/binja/export_manifest_functions.py",
        "test_binja_export_manifest_functions_interior_alias",
    )
    monkeypatch.setattr(
        module,
        "_run_bn_json",
        lambda *_args: {
            "result": {
                "reanalyzed": [],
                "interior_aliases": [
                    {
                        "address": "0x406da0",
                        "owner_address": "0x406d70",
                        "owner_name": "initialize_main_loop_display_state",
                    }
                ],
                "unresolved": [],
                "snapshot_saved": False,
            }
        },
    )
    function = module.FunctionSymbol(
        address=0x406DA0,
        name="initialize_main_loop_timing_state",
    )

    result = module._reanalyze_timed_out_functions("snail-mail.bndb", [function])

    assert result["interior_aliases"] == [
        {
            "address": "0x406da0",
            "owner_address": "0x406d70",
            "owner_name": "initialize_main_loop_display_state",
        }
    ]


def test_binja_export_rejects_unresolved_skipped_function(
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    module = _load_script(
        monkeypatch,
        "tools/binja/export_manifest_functions.py",
        "test_binja_export_manifest_functions_unresolved_reanalysis",
    )
    monkeypatch.setattr(
        module,
        "_run_bn_json",
        lambda *_args: {
            "result": {
                "reanalyzed": [],
                "interior_aliases": [],
                "unresolved": [
                    {"address": "0x43f930", "reason": "manual_skip"}
                ],
                "snapshot_saved": False,
            }
        },
    )
    function = module.FunctionSymbol(address=0x43F930, name="update_slug_hazard_ai")

    with pytest.raises(RuntimeError, match="left selected functions without HLIL"):
        module._reanalyze_timed_out_functions("snail-mail.bndb", [function])


def test_ida_symbol_sync_can_split_a_main_function_chunk() -> None:
    source = (REPO_ROOT / "tools/ida/apply_symbol_manifest.py").read_text(
        encoding="utf-8"
    )

    assert "ida_funcs.remove_func_tail(func, address)" in source
    assert "ida_funcs.set_func_end(func.start_ea, address)" in source
    assert "split_main_chunk_verification_failed" in source
    assert "ida_funcs.set_func_end(start, original_end)" in source


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


def test_ida_partial_export_preserves_last_known_good_artifact(
    monkeypatch: pytest.MonkeyPatch,
    tmp_path: Path,
) -> None:
    module = _load_script(
        monkeypatch,
        "tools/ida/export_manifest_functions.py",
        "test_ida_export_manifest_functions_partial_preservation",
    )
    out_dir = tmp_path / "functions"
    out_dir.mkdir()
    fresh = types.SimpleNamespace(
        address=0x401000,
        address_hex="0x401000",
        name="fresh_function",
    )
    failed = types.SimpleNamespace(
        address=0x402000,
        address_hex="0x402000",
        name="failed_function",
    )
    fresh_artifact = out_dir / "00401000-fresh_function.c"
    failed_artifact = out_dir / "00402000-failed_function.c"
    fresh_artifact.write_text("fresh\n", encoding="utf-8")
    failed_artifact.write_text("cached\n", encoding="utf-8")
    refreshed = [
        {
            "selector": fresh.name,
            "address": fresh.address_hex,
            "name": fresh.name,
            "artifact": str(fresh_artifact),
        }
    ]
    existing_index = {
        "exported": [
            {
                "selector": failed.name,
                "address": failed.address_hex,
                "name": failed.name,
                "artifact": str(failed_artifact),
            }
        ]
    }

    merged = module._merge_focused_exports(
        [fresh, failed],
        refreshed,
        out_dir=out_dir,
        existing_index=existing_index,
    )
    expected_paths = {Path(entry["artifact"]) for entry in merged}
    removed = module._prune_stale_artifacts(out_dir, expected_paths)

    assert [entry["address"] for entry in merged] == [
        fresh.address_hex,
        failed.address_hex,
    ]
    assert removed == []
    assert failed_artifact.read_text(encoding="utf-8") == "cached\n"


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


def test_ida_artifact_export_reports_partial_failures_without_process_abort(
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    source = (REPO_ROOT / "tools/ida/export_function_artifact.py").read_text(
        encoding="utf-8"
    )

    assert '"failed": failed' in source
    assert "ida_pro.qexit(0)" in source
    assert "ida_pro.qexit(1 if failed else 0)" not in source
