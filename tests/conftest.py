import itertools
import json
import os
import re
import struct
import subprocess

import pytest

from snail.archive import parse_archive_index, read_archive_entry, write_archive
from snail.port_lockstep import layout_offsets
from snail.symbols import REPO_ROOT

# Fields and constants the JavaScript harnesses reach in the port's memory, in the layout the port compiles.
PORT_LAYOUT = (
    ("subgame", "offsetof(cRGame, subgame)"),
    ("backdrop", "offsetof(cRGame, backdrop)"),
    ("level_definition", "offsetof(cRSubGame, level_definition)"),
    ("level_display_name", "offsetof(SubTracks, level_display_name)"),
    ("player", "offsetof(cRSubGame, player)"),
    ("subgame_state", "offsetof(cRSubGame, subgame_state)"),
    ("subgame_rebuild_selector", "offsetof(cRSubGame, subgame_rebuild_selector)"),
    ("subgame_pause_gate", "offsetof(cRSubGame, subgame_pause_gate)"),
    ("sm_tracks", "offsetof(cRSubGame, sm_tracks)"),
    ("segment_entry", "sizeof(SegmentCatalogEntry)"),
    ("runtime_flags", "offsetof(cRSubGame, runtime_flags)"),
    ("runtime_cells", "offsetof(cRSubGame, runtime_cells)"),
    ("lanes", "SUBGAME_TRACK_LANE_COUNT"),
    ("cell", "sizeof(cRSubLoc)"),
    ("cell_position", "offsetof(cRSubLoc, position)"),
    ("cell_tile", "offsetof(cRSubLoc, tile_id)"),
    ("paths", "offsetof(cRSubGame, paths)"),
    ("path", "sizeof(cRPath)"),
    ("path_kind", "offsetof(cRPath, kind)"),
    ("path_segment_count", "offsetof(cRPath, segment_count)"),
    ("path_width_cells", "offsetof(cRPath, width_cells)"),
    ("runtime_rows", "offsetof(cRSubGame, runtime_rows)"),
    ("runtime_row", "sizeof(cRSubRow)"),
    ("row_flags", "offsetof(cRSubRow, flags)"),
    ("row_primary_cell", "offsetof(cRSubRow, primary_attachment_cell)"),
    ("cell_attachment", "offsetof(cRSubLoc, attachment_template_record)"),
    ("primary_attachment_flag", "SUBROW_FLAG_PRIMARY_ATTACHMENT"),
    ("path_heading", "offsetof(cRPath, installed_heading_delta)"),
    ("path_primary_samples", "offsetof(cRPath, primary_samples)"),
    ("path_secondary_samples", "offsetof(cRPath, secondary_samples)"),
    ("sample", "sizeof(AttachmentSample)"),
    ("sample_center_x", "offsetof(AttachmentSample, center_x)"),
    ("sample_roll", "offsetof(AttachmentSample, rotation_scalar_98)"),
    ("sample_lateral_scale", "offsetof(AttachmentSample, lateral_scale)"),
    ("sample_delta_length", "offsetof(AttachmentSample, delta_length)"),
    ("player_position", "offsetof(cRSubGoldy, transform.position)"),
    ("player_velocity", "offsetof(cRSubGoldy, velocity)"),
    ("player_exit_pending", "offsetof(cRSubGoldy, attachment_exit_pending)"),
    ("player_hover_state", "offsetof(cRSubGoldy, sub_hover.state)"),
    ("player_pitch_cycle", "offsetof(cRSubGoldy, cutscene_pitch_cycle)"),
    ("player_lift", "offsetof(cRSubGoldy, cameraman.attachment_lift_envelope)"),
    ("follow", "offsetof(cRSubGoldy, follow_state)"),
    ("follow_template", "offsetof(cRPathFollowGoldy, template_record)"),
    ("follow_cell", "offsetof(cRPathFollowGoldy, source_cell)"),
    ("follow_index", "offsetof(cRPathFollowGoldy, sample_index)"),
    ("follow_progress", "offsetof(cRPathFollowGoldy, progress)"),
    ("follow_vertical", "offsetof(cRPathFollowGoldy, vertical_offset)"),
    ("follow_roll", "offsetof(cRPathFollowGoldy, orientation_b)"),
    ("allow_falling", "SUBGAME_RUNTIME_FLAG_ALLOW_FALLING"),
    ("hover_active", "SUB_HOVER_STATE_ACTIVE"),
    ("mobile_sbend", "PATH_TEMPLATE_KIND_MOBILE_SBEND"),
    ("trampoline", "SUBLOC_TILE_TRAMPOLINE"),
    ("frontend_state", "offsetof(cRGame, players[0].frontend_state)"),
    ("galaxy_name", "offsetof(cRGame, subgame.galaxy.route_names[0].name)"),
    ("splash_message", "offsetof(cRGame, subgame.splash.message_widget)"),
    ("splash_state", "offsetof(cRGame, subgame.splash.message_state)"),
    ("border_text", "offsetof(cRBorder, text_buffer)"),
    ("rings", "offsetof(cRSubGame, ring_effects.slots)"),
    ("ring", "sizeof(cRSubRing)"),
    ("ring_slots", "SUB_RING_POOL_CAPACITY"),
    ("ring_state", "offsetof(cRSubRing, state)"),
    ("ring_kind", "offsetof(cRSubRing, kind)"),
    ("ring_position", "offsetof(cRSubRing, transform.position)"),
    ("ring_oscillate_x", "offsetof(cRSubRing, oscillate_x)"),
    ("completion", "offsetof(cRSubGame, completion)"),
    ("completion_state", "offsetof(cRCompletion, state)"),
    ("completion_target", "offsetof(cRCompletion, parcel_target_count)"),
    ("completion_display_token", "offsetof(cRCompletion, display_token)"),
    ("replay_update_cursor", "offsetof(cRSubGame, replay_update_cursor)"),
    ("replay_sample_count", "offsetof(cRSubGame, current_high_score_record.replay_sample_count)"),
    ("tips", "offsetof(cRGame, tip_manager.tips)"),
    ("tip", "sizeof(cRTip)"),
    ("tip_slots", "TIP_SLOT_COUNT"),
    ("position", "offsetof(cRSubGoldy, transform.position)"),
    ("camera_target", "offsetof(cRSubGoldy, cached_camera_target_world)"),
    ("row_event", "offsetof(cRSubGoldy, row_event.id)"),
    ("segment_slots", "offsetof(cRSubTracks, segment_slots)"),
    ("segment_slot", "sizeof(SubSegment)"),
    ("segment_message", "offsetof(SubSegment, message_text)"),
    ("total_score", "offsetof(cRSubGoldy, total_score)"),
    ("score_buckets", "offsetof(cRSubGoldy, score_buckets)"),
    ("score_bucket_count", "SUBGOLDY_SCORE_BUCKET_COUNT"),
    ("ring_counter", "offsetof(cRSubGoldy, lives)"),
    ("lives", "offsetof(cRSubGoldy, visible_life_stock)"),
    ("handoff_timer", "offsetof(cRSubGoldy, completion_handoff_timer)"),
    ("completion_row_start", "offsetof(cRSubGame, completion_row_start)"),
    ("runtime_row_scan_end", "offsetof(cRSubGame, runtime_row_scan_end)"),
    ("finish_banner_z", "offsetof(cRSubGame, banners.slots[1].position.z)"),
    ("finish_banner_flags", "offsetof(cRSubGame, banners.slots[1].list_flags)"),
    ("player_z", "offsetof(cRSubGoldy, transform.position.z)"),
    ("active_window_min_z", "offsetof(cRSubGoldy, active_window_min_z)"),
    ("saved_frontend_state", "offsetof(cRGame, players[0].saved_frontend_state)"),
    ("high_score", "offsetof(cRGame, high_score)"),
    ("replay_row_widgets", "offsetof(cRHighScore, replay_row_widgets)"),
    ("widget_flags", "offsetof(FrontendWidget, widget_flags)"),
    ("primary_action_triggered", "FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED"),
    ("postal_records", "offsetof(cRSubGame, sub_high_score.postal_records)"),
    ("record_name", "offsetof(SubSolution, player_name)"),
    ("player_name", "offsetof(cRGame, players[0].player_name)"),
    ("fade_state", "offsetof(cRGame, fade.state)"),
    ("borders", "offsetof(cRGame, border_manager.borders)"),
    ("border_size", "sizeof(BorderRecord)"),
    ("border_count", "BORDER_RECORD_COUNT"),
    ("border_widget_flags", "offsetof(cRBorder, widget_flags)"),
    ("text_buffer", "offsetof(cRBorder, text_buffer)"),
    ("layout_x", "offsetof(cRBorder, layout_x)"),
    ("layout_y", "offsetof(cRBorder, layout_y)"),
    ("layout_width", "offsetof(cRBorder, layout_width)"),
    ("layout_height", "offsetof(cRBorder, layout_height)"),
    ("level_mode_arg", "offsetof(cRSubGame, level_mode_arg)"),
    ("sub_player_z", "offsetof(cRSubGame, player.transform.position.z)"),
    ("sub_total_score", "offsetof(cRSubGame, player.total_score)"),
    ("bonus_score", "offsetof(cRSubGame, completion.bonus_score)"),
    ("sub_high_score", "offsetof(cRSubGame, sub_high_score)"),
    ("hs_postal_records", "offsetof(cRSubHighScore, postal_records)"),
    ("survival_records", "offsetof(cRSubHighScore, survival_records)"),
    ("time_trial_records", "offsetof(cRSubHighScore, time_trial_route_records)"),
    ("solution_size", "sizeof(cRSubSolution)"),
    ("solution_active", "offsetof(cRSubSolution, active)"),
    ("solution_score", "offsetof(cRSubSolution, score)"),
    ("solution_seconds", "offsetof(cRSubSolution, total_seconds)"),
    ("player_vy", "offsetof(cRSubGoldy, velocity.y)"),
    ("follow_active", "offsetof(cRSubGoldy, follow_state.active)"),
    ("gauge_fill", "offsetof(cRSubGoldy, damage_gauge.fill)"),
    ("shooting_tier", "offsetof(cRSubGoldy, shooting_tier)"),
)


@pytest.fixture(scope="session")
def port_layout_env() -> dict[str, str]:
    """The environment for a harness that reads `SNAIL_LAYOUT` (tests/port_mobile_runtime.mjs, port_frontend*.mjs)."""
    return {**os.environ, "SNAIL_LAYOUT": json.dumps(layout_offsets(REPO_ROOT, PORT_LAYOUT, port=True))}


@pytest.fixture
def probe_course(tmp_path):
    """Play a course of the PC Start, the given segment rows and the PC Finish on the headless
    build (Pro 10 in Ultimate, Postal 1 in Original) and return its `--trace`. Ultimate lays the
    four-row Padding before the rows. The snail waits for its start click at z = 4 unless `start`."""
    runs = itertools.count()

    def play(rows, ultimate, start=False):
        directory = tmp_path / f"course{next(runs)}"
        directory.mkdir()
        extras = REPO_ROOT / "artifacts/bin/SnailMailExtras.dat"
        files = {entry.path.upper(): read_archive_entry(extras, entry) for entry in parse_archive_index(extras).entries}
        base = REPO_ROOT / "artifacts/bin/SnailMail.dat"
        base_index = parse_archive_index(base)
        for kind in ("START", "FINISH"):
            files[f"SEGMENTS/PROBE{kind}.TXT"] = read_archive_entry(base, base_index.entry_by_path(f"Segments/{kind}.TXT"))
        files["SEGMENTS/PROBE.TXT"] = (
            "ID:0\r\nName:'Probe'\r\nData:\r\n@@@@@@@@@@\r\n"
            + "".join(f"{row}\r\n" for row in rows) + "@________@\r\n" * 40 + "@@@@@@@@@@\r\n"
        ).encode()
        level = files["LEVELS/ARCADEPRO010.TXT"]
        level = re.sub(
            rb"(Segments Begin:[^\r\n]*\r?\n).*?(Segments End:)",
            lambda match: match[1] + b"Probe.txt\r\n" + match[2],
            level, flags=re.DOTALL,
        )  # fmt: skip
        level = re.sub(rb"(First:[^\r\n]*\s*)Start.txt", rb"\g<1>ProbeStart.txt", level)
        level = re.sub(rb"(Last:[^\r\n]*\s*)Finish.txt", rb"\g<1>ProbeFinish.txt", level)
        files["LEVELS/ARCADEPRO010.TXT"] = level
        if ultimate:
            (directory / "SnailMail.dat").symlink_to(base)
            write_archive(directory / "SnailMailExtras.dat", files)
        else:
            base_files = {entry.path.upper(): read_archive_entry(base, entry) for entry in base_index.entries}
            base_files.update({name: data for name, data in files.items() if "PROBE" in name})
            base_files["LEVELS/ARCADE001.TXT"] = level
            write_archive(directory / "SnailMail.dat", base_files)
        config = bytearray(196)
        struct.pack_into("<ff", config, 0, 1.0, 1.0)
        config[0x60:0x69] = b"Fluctuosa"
        struct.pack_into("<ifi", config, 0x40, 50, 0.5, 50)
        struct.pack_into("<ii", config, 0xA0, 1, 1)
        config[0xC0] = 1
        (directory / "SnailMail.cfg").write_bytes(config)
        (directory / "SnailMailMobile.cfg").write_bytes(config)
        (directory / "SnailMailPro.cfg").write_bytes(struct.pack("<ii", 10, 10))
        keys = directory / "probe.keys"
        menu = f"600 escape\n700 mouse 345 112\n720 click 3\n800 mouse 345 {240 if ultimate else 172}\n820 click 3\n"
        keys.write_text(menu)
        args = ["node", str(REPO_ROOT / "port/shell/run.mjs"), str(REPO_ROOT / "port/zig-out/bin/snail.wasm")]
        args += ["--trace", "--keys", str(keys), *(["--profile", "ultimate"] if ultimate else [])]
        preview = subprocess.run([*args, "--ticks", "900"], cwd=directory, capture_output=True, text=True, check=True)
        button = re.findall(r'widget \d+ at \(([-\d]+), ([-\d]+)\) size ([-\d]+) x ([-\d]+).*"Deliver!"', preview.stderr)
        assert button, preview.stderr
        x, y, width, height = map(int, button[-1])
        menu += f"920 mouse {x + width // 2} {y + height // 2}\n940 click 3\n"
        keys.write_text(menu + ("1100 click 3\n" if start else ""))
        run = subprocess.run(
            [*args, "--ticks", "1400" if start else "1050"], cwd=directory, capture_output=True, text=True, check=True
        )
        assert 'level "Eximius Ferreus"' in run.stderr
        return run.stderr

    return play
