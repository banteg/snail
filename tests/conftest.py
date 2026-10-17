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
)


@pytest.fixture(scope="session")
def port_layout_env() -> dict[str, str]:
    """The environment for a harness that reads `SNAIL_LAYOUT` (tests/port_mobile_runtime.mjs)."""
    return {**os.environ, "SNAIL_LAYOUT": json.dumps(layout_offsets(REPO_ROOT, PORT_LAYOUT, port=True))}
