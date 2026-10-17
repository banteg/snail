import json
import os

import pytest

from snail.port_lockstep import layout_offsets
from snail.symbols import REPO_ROOT

# Fields the JavaScript harnesses reach in the port's memory, in the layout the port compiles.
PORT_LAYOUT = (
    ("subgame", "offsetof(cRGame, subgame)"),
    ("backdrop", "offsetof(cRGame, backdrop)"),
    ("level_definition", "offsetof(cRSubGame, level_definition)"),
    ("level_display_name", "offsetof(SubTracks, level_display_name)"),
    ("player", "offsetof(cRSubGame, player)"),
    ("sm_tracks", "offsetof(cRSubGame, sm_tracks)"),
    ("segment_entry", "sizeof(SegmentCatalogEntry)"),
    ("player_name", "offsetof(cRGame, players[0].player_name)"),
    ("frontend_state", "offsetof(cRGame, players[0].frontend_state)"),
    ("fade_state", "offsetof(cRGame, fade.state)"),
    ("borders", "offsetof(cRGame, border_manager.borders)"),
    ("border_size", "sizeof(BorderRecord)"),
    ("border_count", "BORDER_RECORD_COUNT"),
    ("widget_flags", "offsetof(cRBorder, widget_flags)"),
    ("text_buffer", "offsetof(cRBorder, text_buffer)"),
    ("layout_x", "offsetof(cRBorder, layout_x)"),
    ("layout_y", "offsetof(cRBorder, layout_y)"),
    ("layout_width", "offsetof(cRBorder, layout_width)"),
    ("layout_height", "offsetof(cRBorder, layout_height)"),
    ("level_mode_arg", "offsetof(cRSubGame, level_mode_arg)"),
    ("completion_row_start", "offsetof(cRSubGame, completion_row_start)"),
    ("player_z", "offsetof(cRSubGame, player.transform.position.z)"),
    ("total_score", "offsetof(cRSubGame, player.total_score)"),
    ("bonus_score", "offsetof(cRSubGame, completion.bonus_score)"),
    ("sub_high_score", "offsetof(cRSubGame, sub_high_score)"),
    ("postal_records", "offsetof(cRSubHighScore, postal_records)"),
    ("survival_records", "offsetof(cRSubHighScore, survival_records)"),
    ("time_trial_records", "offsetof(cRSubHighScore, time_trial_route_records)"),
    ("solution_size", "sizeof(cRSubSolution)"),
    ("solution_active", "offsetof(cRSubSolution, active)"),
    ("solution_score", "offsetof(cRSubSolution, score)"),
    ("solution_seconds", "offsetof(cRSubSolution, total_seconds)"),
)


@pytest.fixture(scope="session")
def port_layout_env() -> dict[str, str]:
    """The environment for a harness that reads `SNAIL_LAYOUT` (tests/port_mobile_runtime.mjs, port_frontend.mjs)."""
    return {**os.environ, "SNAIL_LAYOUT": json.dumps(layout_offsets(REPO_ROOT, PORT_LAYOUT, port=True))}
