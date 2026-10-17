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
    ("subgame_state", "offsetof(cRSubGame, subgame_state)"),
    ("subgame_rebuild_selector", "offsetof(cRSubGame, subgame_rebuild_selector)"),
    ("sm_tracks", "offsetof(cRSubGame, sm_tracks)"),
    ("segment_entry", "sizeof(SegmentCatalogEntry)"),
    ("frontend_state", "offsetof(cRGame, players[0].frontend_state)"),
    ("saved_frontend_state", "offsetof(cRGame, players[0].saved_frontend_state)"),
    ("high_score", "offsetof(cRGame, high_score)"),
    ("replay_row_widgets", "offsetof(cRHighScore, replay_row_widgets)"),
    ("widget_flags", "offsetof(FrontendWidget, widget_flags)"),
    ("primary_action_triggered", "FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED"),
    ("postal_records", "offsetof(cRSubGame, sub_high_score.postal_records)"),
    ("record_name", "offsetof(SubSolution, player_name)"),
)


@pytest.fixture(scope="session")
def port_layout_env() -> dict[str, str]:
    """The environment for a harness that reads `SNAIL_LAYOUT` (tests/port_mobile_runtime.mjs)."""
    return {**os.environ, "SNAIL_LAYOUT": json.dumps(layout_offsets(REPO_ROOT, PORT_LAYOUT, port=True))}
