# Outer Bridge Post-Capture Dossier 2026-03-25

This is the active post-capture dossier for the outer bridge replacement batch.

Runtime evidence is locked to the March 24, 2026 Windows captures:
- [windows-re-batch-2026-03-24.md](./windows-re-batch-2026-03-24.md)
- [windows-outer-bridge-capture-2026-03-24.md](./windows-outer-bridge-capture-2026-03-24.md)

Wide Windows capture is suspended on this host due to system hangs on broader probe sets.
Do not widen Frida or CDB for this batch.

## Phase And Boundary

- phase: `replace`
- classification: `static-closable`
- owner boundary: outer subgame or frontend bridge only
- safe-to-code boundary: [zig/src/main.zig](../../zig/src/main.zig)
- scaffold removed in this batch:
  - `OuterBridgeRequest`
  - `OuterBridgeTarget`
  - `preserved_frontend_owner`
  - `post_level_high_score_return_request`

## Locked Runtime Read

These are the non-negotiable bridge facts for this batch:

- ordinary fresh Postal startup is not a saved-owner bridge case
- ordinary respawn rebuild uses direct owner `0x1c`, not `0x1a/0x1b`
- transient pause `End Game` uses completion state `2`
- persistent high-score replay pause `End Game` uses completion state `3`
- persistent high-score replay restores through saved replay return owner `0x12`
- route-map Time Trial replay stays transient
- `29/30` remain the Thanks/credits owner family

## Writer Or Consumer Table

### Active outer owner

- runtime anchors:
  - fresh startup: ordinary flow stays off `0x1a/0x1b`
  - respawn rebuild: direct owner `0x1c`
  - transient abandon: completion state `2`
  - persistent high-score replay abandon: completion state `3`
- bounded writers:
  - `update_subgame`
  - `update_pause_menu`
  - `update_completion_screen`
  - `update_high_score_screen`
  - `update_main_menu`
  - `exit_high_score_screen`
- bounded consumers:
  - `update_subgame`
  - `initialize_subgame`
  - `build_subgame_level`
- current read:
  - ordinary startup and transient replay-backed routes should not be modeled as saved-owner bridge producers

### Saved outer owner

- runtime anchors:
  - transient abandon carries saved owner through completion state `2`
  - respawn rebuild preserves saved owner while current owner goes through `0x1c`
- bounded writers:
  - `update_subgame`
  - `update_pause_menu`
  - `update_high_score_screen`
  - `exit_high_score_screen`
- bounded consumers:
  - `update_completion_screen`
  - `initialize_subgame`
- current read:
  - gameplay-side result or respawn handoff writers are strong enough to port
  - missing explicit producers are now frontend-side and rarer

### Saved replay return owner

- runtime anchors:
  - persistent high-score replay uses `saved_return = 0x12`
  - transient Time Trial replay keeps `saved_return = 0`
- bounded writers:
  - `update_high_score_screen`
  - `update_new_game_menu`
  - `exit_high_score_screen`
- bounded consumers:
  - `initialize_click_start`
  - `update_pause_menu`
  - `update_completion_screen`
- current read:
  - high-score replay rows are the only confirmed persistent replay family
  - `update_high_score_screen` replay-row launch seeds persistent replay plus saved replay return owner `0x12`
  - `update_new_game_menu` replay attract seeds persistent replay plus saved replay return owner `2`
  - `exit_high_score_screen` itself does not write the saved replay return owner; it restores mode-owned exit state `2` for postal and `10` for challenge

### Persistent replay marker

- runtime anchors:
  - high-score replay rows arm `rec_persist = 1`
  - route-map Time Trial replay stays on `rec_persist = 0`
- bounded writers:
  - `update_high_score_screen`
  - `update_new_game_menu`
- bounded consumers:
  - `build_subgame_level`
  - `initialize_click_start`
  - `update_pause_menu`
- current read:
  - persistent replay should remain explicit launch metadata, not reconstructed from source enums

### Completion states `2` and `3`

- writer:
  - `update_pause_menu`
- consumer:
  - `update_completion_screen`
- current read:
  - state `2` is the transient abandon lane
  - state `3` is the persistent saved-return restore lane

### Direct respawn owner `0x1c`

- writer:
  - `update_subgoldy_resurrect`
- consumers:
  - `initialize_subgame`
  - `update_subgame`
- current read:
  - ordinary respawn is not a saved-owner bridge opcode and should not be routed like one in Zig

## Replacement Rules

- keep existing frontend entry helpers as leaf effect endpoints
- move owner selection into one bridge transition function that mutates app bridge state directly
- store the raw continuation selector on `AppState`
- do not invent a generic `0x1a/0x1b` producer
- if a lane is still rare or unresolved, keep a documented raw owner or selector instead of adding a new dispatcher layer

## Static RE Follow-Up After The Patch

After the bridge replacement lands, the next narrow static pass stays inside:
- `update_subgame`
- `initialize_subgame`
- `build_subgame_level`
- `update_pause_menu`
- `update_completion_screen`
- `update_high_score_screen`
- `update_main_menu`
- `exit_high_score_screen`

Goal:
- close the remaining frontend-side saved-owner producers
- close the auto-exit restore path without widening runtime capture

Fresh static narrowing from the bounded frontend set:
- `update_high_score_screen`
  - replay-row clicks seed the selected replay pointer
  - arm the persistent replay byte
  - store saved replay return owner `18`
  - copy replay mode into the launch scratch consumed by subgame startup
- `update_new_game_menu`
  - only the replay-attract cursor families `0`, `1`, and `3` seed a replay launch
  - successful replay-attract launch stores saved replay return owner `2`
  - ordinary menu buttons still go through plain frontend-state `10` launch with no replay scratch
- `exit_high_score_screen`
  - postal browse exits through owner `2`
  - challenge browse exits through owner `10`
- `update_main_menu`
  - `High Scores` enters owner `18`
  - `New Game` enters owner `2`
