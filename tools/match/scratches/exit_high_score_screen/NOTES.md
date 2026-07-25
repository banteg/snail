# exit_high_score_screen

Leaves the high-score screen and marks the ordinary front-end state as dirty.

The `+0x12e55e0` field reuses the existing `ordinary_rebuild_selector` name
from `update_frontend_state_machine`; both postal and challenge exit paths set
it to `2`.

2026-07-11 cRHighScore ownership: Android preserves this member as
`cRHighScore::Exit()`. The exact Windows 23/23 helper now lives on the shared
root-owned `HighScore` controller.

2026-07-13 canonical root graph: postal/challenge exits now load the typed
`GameRoot*` global while preserving native's deliberate reloads between player
state, rebuild-selector, and redispatch writes. The helper remains exact at
23/23 with all six operands clean.

2026-07-14 return-contract audit: Android's AI tail branches and both Windows
callers establish `cRHighScore::Exit()` as side-effect-only. Removing the
incidental root-pointer return preserves the exact 23/23 body and six clean
operands. The Binary Ninja void prototype remains explicitly deferred after
live analysis restores its stale scalar form.

## 2026-07-25 root-owner replay

Refreshing the typed root view makes IDA agree with the exact source:
`SubgameRuntime::level_mode` chooses the destination
`GamePlayer::frontend_state`, both paths seed
`SubgameRuntime::subgame_rebuild_selector`, and
`GamePlayer::redispatch_requested` schedules the transition. This is an
ownership-only replay; the helper remains exact at 23/23 instructions.

Binary Ninja now explicitly reanalyzes the lifecycle trio after the narrow
high-score sync. Its paired tracked artifact and health canary keep the same
typed root borrows durable without touching the exact matcher.
