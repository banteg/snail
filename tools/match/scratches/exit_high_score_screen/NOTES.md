# exit_high_score_screen

Leaves the high-score screen and marks the ordinary front-end state as dirty.

The `+0x12e55e0` field reuses the existing `ordinary_rebuild_selector` name
from `update_frontend_state_machine`; both postal and challenge exit paths set
it to `2`.
