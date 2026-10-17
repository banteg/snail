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
    ("player_z", "offsetof(cRSubGoldy, transform.position.z)"),
    ("player_vy", "offsetof(cRSubGoldy, velocity.y)"),
    ("follow_active", "offsetof(cRSubGoldy, follow_state.active)"),
    ("gauge_fill", "offsetof(cRSubGoldy, damage_gauge.fill)"),
    ("shooting_tier", "offsetof(cRSubGoldy, shooting_tier)"),
)


@pytest.fixture(scope="session")
def port_layout_env() -> dict[str, str]:
    """The environment for a harness that reads `SNAIL_LAYOUT` (tests/port_mobile_runtime.mjs)."""
    return {**os.environ, "SNAIL_LAYOUT": json.dumps(layout_offsets(REPO_ROOT, PORT_LAYOUT, port=True))}
