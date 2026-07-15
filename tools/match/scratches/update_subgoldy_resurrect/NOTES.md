# update_subgoldy_resurrect

Exact match.

- Advances the resurrect progress while the global frontend fade is idle, then
  starts a fade-out once progress passes `1.0f`.
- The route branch only runs after progress is past `1.0f` and the fade state
  reaches `4`.
- Non-final deaths return to gameplay state `0x1c`, decrementing visible arcade
  life stock only for level mode `0`.
- Final-loss deaths mark `subgame_rebuild_selector = 2`, call
  `complete_subgame(1)`, then route either through selected-level replay state
  `0x1a`, arcade continue state `0x1a/2`, or fallback state `0x1b`.
- The exact source shape keeps the respawn/final-loss branches explicit so VC6
  can hoist shared `game`/`g_game` loads between condition tests and branches.
- 2026-06-20 shared view, superseded 2026-07-14: the temporary `AppShell`
  slice introduced `app_shell.h` plus `frontend_fade.h` and first named
  `high_score_entry_pending` at root offset `+0x30d`.
- 2026-06-21 owner cleanup: the sparse owner view is now named
  `SubgoldyResurrectGameView` instead of the generic scratch-local `Game`.
  Replacing it with broad `SubgameRuntime*` casts was rejected because it
  changed VC6 hoisting around `resurrect_final_loss` and regressed the scratch
  to `76.51%`; the sparse renamed view keeps the exact `100.00%`, `76/76`
  source shape.
- 2026-07-11 owner closure: all three sparse fields are now independently
  proven members of the real `SubgameRuntime` owner, and `Player::game` is its
  borrowed backlink. Keeping the native succession of `current_game`,
  `persistent_game`, and `route_game` locals avoids the earlier broad-cast
  scheduling regression, so the synthetic `SubgoldyResurrectGameView` can be
  retired while the scratch remains exact at `100.00%`, `76/76`, with `13`
  clean masked operands.
- 2026-07-14 root-owner closure: `app_shell.h` is retired. The frontend state
  lanes are canonical `GameRoot::players[0]` fields: root `+0x1b8/+0x1bc`
  are `GamePlayer::frontend_state/saved_frontend_state`, and root `+0x30d`
  is `GamePlayer::high_score_entry_pending`. The helper remains exact at
  `100.00%`, `76/76`, with all `13` masked operands clean.
