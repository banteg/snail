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
)


@pytest.fixture(scope="session")
def port_layout_env() -> dict[str, str]:
    """The environment for a harness that reads `SNAIL_LAYOUT` (tests/port_mobile_runtime.mjs)."""
    return {**os.environ, "SNAIL_LAYOUT": json.dumps(layout_offsets(REPO_ROOT, PORT_LAYOUT, port=True))}
