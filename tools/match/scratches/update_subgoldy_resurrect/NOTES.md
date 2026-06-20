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
  can hoist shared `game`/`g_app` loads between condition tests and branches.
- 2026-06-20 shared view: the local `AppShell`/`FrontendFade` slice was
  replaced with `app_shell.h` plus `frontend_fade.h`. The exact 76-instruction
  match is unchanged, and the final arcade route now names
  `high_score_entry_pending` at app offset `+0x30d`.
