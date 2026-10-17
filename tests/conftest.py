import json
import os

import pytest

from snail.port_lockstep import layout_offsets
from snail.symbols import REPO_ROOT

# Fields and constants the JavaScript harnesses reach in the port's memory, in the layout the port compiles.
PORT_LAYOUT = (
    ("subgame", "offsetof(cRGame, subgame)"),
    ("backdrop", "offsetof(cRGame, backdrop)"),
    ("level_definition", "offsetof(cRSubGame, level_definition)"),
    ("level_display_name", "offsetof(SubTracks, level_display_name)"),
    ("player", "offsetof(cRSubGame, player)"),
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
    ("total_score", "offsetof(cRSubGoldy, total_score)"),
    ("score_buckets", "offsetof(cRSubGoldy, score_buckets)"),
    ("score_bucket_count", "SUBGOLDY_SCORE_BUCKET_COUNT"),
    ("ring_counter", "offsetof(cRSubGoldy, lives)"),
    ("lives", "offsetof(cRSubGoldy, visible_life_stock)"),
    ("handoff_timer", "offsetof(cRSubGoldy, completion_handoff_timer)"),
)


@pytest.fixture(scope="session")
def port_layout_env() -> dict[str, str]:
    """The environment for a harness that reads `SNAIL_LAYOUT` (tests/port_mobile_runtime.mjs)."""
    return {**os.environ, "SNAIL_LAYOUT": json.dumps(layout_offsets(REPO_ROOT, PORT_LAYOUT, port=True))}
