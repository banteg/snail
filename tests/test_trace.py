from __future__ import annotations

import json
from pathlib import Path

from snail.trace import build_trace_capture_plan, load_runtime_trace, summarize_runtime_trace_file


EXTRACTED_ROOT = Path(__file__).resolve().parents[1] / "artifacts/extracted/SnailMail.dat"


def test_summarize_runtime_trace_file(tmp_path: Path) -> None:
    trace_path = tmp_path / "snailmail-trace.ndjson"
    rows = [
        {
            "ts_ms": 1,
            "pid": 111,
            "tid": 222,
            "event": "module_ready",
            "module": "SnailMail_unwrapped.exe",
            "module_base": "0x400000",
            "module_path": "C:/Games/SnailMail_unwrapped.exe",
        },
        {
            "ts_ms": 2,
            "pid": 111,
            "tid": 222,
            "event": "level_start",
            "seq": 1,
            "mode_before": 7,
            "mode_after": 3,
            "active_level_flag_0": 1,
            "active_level_flag_1": 0,
            "active_level_present": True,
            "selected_track_id": 3,
            "active_level": "0x500000",
            "garbage_scalar": 0.65,
            "salt_scalar": 0.35,
        },
        {
            "ts_ms": 3,
            "pid": 111,
            "tid": 222,
            "event": "path_lookup",
            "seq": 1,
            "path_name": "START",
            "path_name_raw": "Start\x80\x80Stop",
            "path_name_sanitized": "Start",
            "path_name_from_index": "START",
            "path_index": 36,
        },
        {
            "ts_ms": 4,
            "pid": 111,
            "tid": 222,
            "event": "path_lookup",
            "seq": 2,
            "path_name": "START",
            "path_name_from_index": "START",
            "path_index": 36,
        },
        {
            "ts_ms": 5,
            "pid": 111,
            "tid": 222,
            "event": "player_update",
            "seq": 1,
            "player": "0x410000",
            "player_position": {"x": 0.0, "y": 0.49, "z": 118.0},
            "before_position": {"x": 0.0, "y": 0.4, "z": 117.8},
            "velocity": {"x": 0.1, "y": 0.0, "z": 0.8},
            "attachment_active_before": False,
            "attachment_active": True,
            "follow_state": "0x430100",
            "follow_state_summary": {
                "ptr": "0x430100",
                "active": True,
                "template": "0x401000",
                "template_summary": {
                    "ptr": "0x401000",
                    "kind": 36,
                    "sample_count": 12,
                    "width_or_scale": 0.6,
                    "sample_length": 1.25,
                },
                "sample_index": 3,
                "progress": 0.25,
                "offset_y": -0.09,
                "orientation": {"x": 0.0, "y": 0.0, "z": 1.0},
                "output_position": {"x": 0.0, "y": 0.4, "z": 118.0},
            },
            "follow_sample_index": 3,
            "follow_progress": 0.25,
            "cell": {
                "ptr": "0x5ccac8",
                "row": 118,
                "tile_type": 30,
                "floor_height": 0.0,
                "world": {"x": 0.0, "y": 0.0, "z": 118.0},
                "attachment": "0x610000",
                "attachment_kind": 24,
            },
        },
        {
            "ts_ms": 6,
            "pid": 111,
            "tid": 222,
            "event": "attachment_probe",
            "seq": 1,
            "template": "0x401000",
            "template_summary": {
                "ptr": "0x401000",
                "kind": 36,
                "sample_count": 12,
                "width_or_scale": 0.6,
            },
            "position": {"x": 0.0, "y": 0.49, "z": 118.0},
            "velocity": {"x": 0.0, "y": -0.1, "z": 0.8},
            "cell": {
                "ptr": "0x5ccac8",
                "row": 118,
                "tile_type": 30,
                "floor_height": 0.0,
                "world": {"x": 0.0, "y": 0.0, "z": 118.0},
                "attachment": "0x610000",
                "attachment_kind": 24,
            },
        },
        {
            "ts_ms": 7,
            "pid": 111,
            "tid": 222,
            "event": "attachment_begin",
            "seq": 1,
            "follow_state": "0x430100",
            "follow_state_summary": {
                "ptr": "0x430100",
                "active": True,
                "template": "0x401000",
                "template_summary": {"ptr": "0x401000", "kind": 36},
                "sample_index": 0,
                "progress": 0.0,
                "offset_y": -0.09,
                "output_position": {"x": 0.1, "y": 0.4, "z": 118.0},
            },
            "player_position": {"x": 0.1, "y": 0.4, "z": 118.0},
            "cell": {
                "ptr": "0x5ccac8",
                "row": 118,
                "tile_type": 30,
                "floor_height": 0.0,
                "world": {"x": 0.0, "y": 0.0, "z": 118.0},
                "attachment": "0x610000",
                "attachment_kind": 24,
            },
        },
        {
            "ts_ms": 8,
            "pid": 111,
            "tid": 222,
            "event": "attachment_update",
            "seq": 1,
            "follow_state": "0x430100",
            "follow_state_summary": {
                "ptr": "0x430100",
                "active": True,
                "template": "0x401000",
                "template_summary": {
                    "ptr": "0x401000",
                    "kind": 36,
                    "sample_count": 12,
                    "sample_delta": {"x": 0.0, "y": 0.1, "z": 0.6},
                    "sample_length": 1.25,
                },
                "sample_index": 4,
                "progress": 0.5,
                "offset_y": -0.09,
                "orientation": {"x": 0.0, "y": 0.0, "z": 1.0},
                "output_position": {"x": 0.2, "y": 0.5, "z": 118.7},
            },
            "retval": 2,
            "player_position": {"x": 0.2, "y": 0.5, "z": 118.7},
            "velocity": {"x": 0.0, "y": 0.1, "z": 0.7},
            "follow_sample_index": 4,
            "follow_progress": 0.5,
            "cell": {
                "ptr": "0x5ccb04",
                "row": 119,
                "tile_type": 30,
                "floor_height": 0.0,
                "world": {"x": 0.0, "y": 0.0, "z": 119.0},
                "attachment": "0x610000",
                "attachment_kind": 24,
            },
        },
        {
            "ts_ms": 9,
            "pid": 111,
            "tid": 222,
            "event": "attachment_end",
            "seq": 1,
            "follow_state": "0x430100",
            "follow_state_summary": {
                "ptr": "0x430100",
                "active": True,
                "template": "0x401000",
                "template_summary": {"ptr": "0x401000", "kind": 36},
                "sample_index": 9,
                "progress": 0.1,
                "offset_y": -0.09,
                "orientation": {"x": 0.0, "y": 0.0, "z": 1.0},
                "output_position": {"x": 0.3, "y": 0.2, "z": 120.0},
            },
            "player_position": {"x": 0.3, "y": 0.2, "z": 120.0},
            "cell": {
                "ptr": "0x5ccb40",
                "row": 120,
                "tile_type": 1,
                "floor_height": -3.0,
                "world": {"x": None, "y": 0.0, "z": 120.0},
                "attachment": "0x0",
                "attachment_kind": None,
            },
        },
        {
            "ts_ms": 10,
            "pid": 111,
            "tid": 222,
            "event": "attachment_probe",
            "seq": 2,
            "template": "0x401000",
            "template_summary": {"ptr": "0x401000", "kind": 36},
            "position": {"x": 0.0, "y": 0.49, "z": 118.0},
            "velocity": {"x": 0.0, "y": -0.1, "z": 0.8},
            "cell": {
                "ptr": "0x5ccac8",
                "row": 118,
                "tile_type": 30,
                "floor_height": 0.0,
                "world": {"x": 0.0, "y": 0.0, "z": 118.0},
                "attachment": "0x610000",
                "attachment_kind": 24,
            },
        },
        {
            "ts_ms": 11,
            "pid": 111,
            "tid": 222,
            "event": "garbage_spawn",
            "seq": 1,
            "manager": "0x700000",
            "cell": {
                "ptr": "0x5cd000",
                "row": 220,
                "tile_type": 1,
                "floor_height": 0.0,
                "world": {"x": 1.0, "y": 0.0, "z": 220.0},
                "attachment": "0x0",
                "attachment_kind": None,
            },
        },
        {
            "ts_ms": 12,
            "pid": 111,
            "tid": 222,
            "event": "health_pickup",
            "seq": 1,
            "cell": {
                "ptr": "0x5cd020",
                "row": 221,
                "tile_type": 23,
                "floor_height": 0.0,
                "world": {"x": 1.0, "y": 0.0, "z": 221.0},
                "attachment": "0x0",
                "attachment_kind": None,
            },
        },
        {
            "ts_ms": 13,
            "pid": 111,
            "tid": 222,
            "event": "jetpack_pickup",
            "seq": 1,
            "cell": {
                "ptr": "0x5cd040",
                "row": 222,
                "tile_type": 25,
                "floor_height": 0.0,
                "world": {"x": 1.0, "y": 0.0, "z": 222.0},
                "attachment": "0x0",
                "attachment_kind": None,
            },
        },
        {
            "ts_ms": 14,
            "pid": 111,
            "tid": 222,
            "event": "ring_effect",
            "seq": 1,
            "effect_kind": 8,
            "effect_scale": 0.5,
            "cell": {
                "ptr": "0x5cd060",
                "row": 223,
                "tile_type": 17,
                "floor_height": 0.4,
                "world": {"x": 1.0, "y": 0.0, "z": 223.0},
                "attachment": "0x0",
                "attachment_kind": None,
            },
        },
        {
            "ts_ms": 15,
            "pid": 111,
            "tid": 222,
            "event": "garbage_spawn",
            "seq": 2,
            "manager": "0x700000",
            "cell": {
                "ptr": "0x5cd000",
                "row": 220,
                "tile_type": 1,
                "floor_height": 0.0,
                "world": {"x": 1.0, "y": 0.0, "z": 220.0},
                "attachment": "0x0",
                "attachment_kind": None,
            },
        },
        {
            "ts_ms": 16,
            "pid": 111,
            "tid": 222,
            "event": "salt_spawn",
            "seq": 1,
            "slot_manager": "0x710000",
            "slot_result": 3,
            "position": {"x": -1.0, "y": 0.5, "z": 221.0},
        },
        {
            "ts_ms": 17,
            "pid": 111,
            "tid": 222,
            "event": "salt_update",
            "seq": 1,
            "slot": "0x720000",
            "state": 1,
            "position": {"x": -1.1, "y": 0.7, "z": 221.3},
            "velocity": {"x": 0.0, "y": 0.03, "z": 0.0},
        },
        {
            "ts_ms": 18,
            "pid": 111,
            "tid": 222,
            "event": "salt_deactivate",
            "seq": 1,
            "slot": "0x720000",
            "state": 1,
            "position": {"x": -1.0, "y": 0.7, "z": 221.3},
            "velocity": {"x": 0.0, "y": 0.03, "z": 0.0},
        },
        {
            "ts_ms": 19,
            "pid": 111,
            "tid": 222,
            "event": "slug_spawn",
            "seq": 1,
            "sprite_id": 118,
            "cell": {
                "ptr": "0x5cd100",
                "row": 221,
                "tile_type": 18,
                "floor_height": 0.0,
                "world": {"x": -1.0, "y": 0.0, "z": 221.0},
                "attachment": "0x0",
                "attachment_kind": None,
            },
        },
        {
            "ts_ms": 20,
            "pid": 111,
            "tid": 222,
            "event": "floor_sample",
            "seq": 1,
            "template": "0x401000",
            "position": {"x": 0.0, "y": 0.0, "z": 224.0},
            "cell": {
                "ptr": "0x5cd120",
                "row": 224,
                "tile_type": 2,
                "floor_height": 0.25,
                "world": {"x": 0.0, "y": 0.0, "z": 224.0},
                "attachment": "0x0",
                "attachment_kind": None,
            },
        },
    ]
    trace_path.write_text("\n".join(json.dumps(row) for row in rows) + "\n", encoding="utf-8")

    events = load_runtime_trace(trace_path)
    summary = summarize_runtime_trace_file(trace_path, preview_limit=2)

    assert len(events) == 20
    assert summary.total_events == 20
    assert summary.event_counts["path_lookup"] == 2
    assert summary.event_counts["player_update"] == 1
    assert summary.level_modes == {3: 1}
    assert summary.levels[0].mode_before == 7
    assert summary.levels[0].mode_after == 3
    assert summary.levels[0].active_level_present is True
    assert summary.levels[0].selected_track_id == 3
    assert summary.path_lookups_by_name == {"START": 2}
    assert summary.path_lookups_by_index[0].path_index == 36
    assert summary.path_lookups_by_index[0].names == ("START",)
    assert summary.player_updates.count == 1
    assert summary.player_updates.rows == {118: 1}
    assert summary.player_updates.tile_types == {30: 1}
    assert summary.player_updates.positions_preview[0].z == 118.0
    assert events[4].cell is not None
    assert events[4].cell.floor_height == 0.0
    assert events[4].follow_state_summary is not None
    assert events[4].follow_state_summary.template_summary is not None
    assert events[4].follow_state_summary.template_summary.kind == 36
    assert events[4].follow_state_summary.offset_y == -0.09
    assert summary.attachment_probes.count == 2
    assert summary.attachment_probes.rows == {118: 2}
    assert summary.attachment_probes.tile_types == {30: 2}
    assert summary.attachment_probes.attachment_kinds == {24: 2}
    assert summary.attachment_updates.count == 1
    assert summary.attachment_updates.rows == {119: 1}
    assert summary.attachment_ends.count == 1
    assert summary.attachment_ends.rows == {120: 1}
    assert summary.garbage_spawns.rows == {220: 2}
    assert summary.garbage_spawns.positions_preview[0].z == 220.0
    assert summary.health_pickups.rows == {221: 1}
    assert summary.jetpack_pickups.rows == {222: 1}
    assert summary.ring_effects.rows == {223: 1}
    assert summary.salt_spawns.positions_preview[0].y == 0.5
    assert summary.salt_updates.count == 1
    assert summary.salt_updates.positions_preview[0].z == 221.3
    assert summary.salt_deactivations.count == 1
    assert summary.salt_deactivations.positions_preview[0].z == 221.3
    assert summary.slug_spawns.rows == {221: 1}


def test_summarize_runtime_trace_uses_index_name_for_legacy_corrupted_path() -> None:
    trace_path = Path("artifacts/frida/snailmail-trace-20260308-152743-11168.ndjson")
    events = load_runtime_trace(trace_path)
    summary = summarize_runtime_trace_file(trace_path, preview_limit=2)

    assert events
    path_index_summary = next(item for item in summary.path_lookups_by_index if item.path_index == 36)
    assert path_index_summary.names == ("START",)
    assert "START" in summary.path_lookups_by_name
    assert summary.level_modes == {}


def test_build_trace_capture_plan_uses_real_corpus() -> None:
    plan = build_trace_capture_plan(EXTRACTED_ROOT, limit=64)

    assert plan.path_segments
    assert plan.ring_segments
    assert plan.no_fall_segments
    assert plan.jetpack_off_segments
    assert plan.salt_segments
    assert any("WARP.TXT" in hint.path for hint in plan.path_segments)
    assert plan.ring_segments[0].ring_rows == 2
    assert any(hint.path.endswith("SEGMENTS/TUTORIAL 7.TXT") for hint in plan.ring_segments)
    assert plan.no_fall_segments[0].path.endswith("SEGMENTS/TRAMPOLINES.TXT")
    assert plan.no_fall_segments[0].no_fall_rows == 84
    assert plan.jetpack_off_segments[0].path.endswith("SEGMENTS/JETPACKOFF.TXT")
    assert plan.jetpack_off_segments[0].jetpack_off_rows == 1
    assert plan.salt_segments[0].path.endswith("SEGMENTS/TUTORIAL 8.TXT")
    assert plan.salt_segments[0].salt_like_rows >= 7
    assert plan.best_path_levels
    assert plan.best_ring_levels
    assert plan.best_no_fall_levels
    assert plan.best_jetpack_off_levels
    assert plan.best_ring_levels[0].path.endswith("LEVELS/TUTORIAL.TXT")
    assert plan.best_ring_levels[0].ring_row_count == 12
    assert plan.best_ring_levels[0].ring_kinds["PowerUp"] == 9
    assert plan.best_ring_levels[0].ring_kinds["Explode"] == 1
    assert plan.best_no_fall_levels[0].path.endswith("LEVELS/ARCADE047.TXT")
    assert plan.best_no_fall_levels[0].no_fall_row_count == 286
    assert plan.best_jetpack_off_levels[0].path.endswith("LEVELS/ARCADE025.TXT")
    assert plan.best_jetpack_off_levels[0].jetpack_off_row_count == 3
    assert plan.best_garbage_levels[0].garbage == 100
    assert plan.best_garbage_levels[0].path.endswith("LEVELS/ARCADE040.TXT")
    assert plan.best_salt_levels[0].salt == 100
    assert plan.best_salt_levels[0].path.endswith("LEVELS/ARCADE039.TXT")
    assert plan.best_authored_salt_levels
    assert plan.best_authored_salt_levels[0].path.endswith("LEVELS/ARCADE037.TXT")
    assert plan.best_authored_salt_levels[0].salt_like_row_count == 12
    tutorial_hint = next(
        hint for hint in plan.best_authored_salt_levels if hint.path.endswith("LEVELS/TUTORIAL.TXT")
    )
    assert tutorial_hint.salt_like_row_count == 11
    assert tutorial_hint.salt in (None, 0)
    assert plan.best_slug_like_levels
