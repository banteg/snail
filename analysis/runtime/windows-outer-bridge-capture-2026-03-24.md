# Windows Outer Bridge Capture 2026-03-24

This note records the fresh Windows `cdb` evidence for section 4 of
`analysis/runtime/windows-re-batch-2026-03-24.md` using
`artifacts/snailmail-windbg.log`.

## Artifact Set

- primary log: [`artifacts/snailmail-windbg.log`](../../artifacts/snailmail-windbg.log)
- startup pack:
  [`artifacts/cdb-outer-bridge-startup-pack-2026-03-24.txt`](../../artifacts/cdb-outer-bridge-startup-pack-2026-03-24.txt)
- pause-return pack:
  [`artifacts/cdb-outer-bridge-pause-return-pack-2026-03-24.txt`](../../artifacts/cdb-outer-bridge-pause-return-pack-2026-03-24.txt)
- replay pack:
  [`artifacts/cdb-outer-bridge-time-trial-replay-pack-2026-03-24.txt`](../../artifacts/cdb-outer-bridge-time-trial-replay-pack-2026-03-24.txt)

## Findings

### 1. Ordinary fresh Postal startup does not use the saved-owner bridge

The fresh startup trace begins at
[`snailmail-windbg.log#L114`](../../artifacts/snailmail-windbg.log#L114):

- `initialize_subgame` entered with `state=0`, `mode=0`, `mode_arg=8`,
  `selector=2`, `rec_active=0`, `rec_persist=0`, `app_owner=0xa`,
  `app_saved=0`
- `update_subgame` then advanced through
  [`state=0`](../../artifacts/snailmail-windbg.log#L115),
  [`state=1`](../../artifacts/snailmail-windbg.log#L116),
  [`state=2`](../../artifacts/snailmail-windbg.log#L119),
  [`state=3`](../../artifacts/snailmail-windbg.log#L120), and
  [`state=4`](../../artifacts/snailmail-windbg.log#L121)
- `build_subgame_level` fired once with `mode_arg=7` and `selector=3` at
  [`snailmail-windbg.log#L117`](../../artifacts/snailmail-windbg.log#L117)
- `initialize_subgoldy` spawned the Postal player with `lives=3` at
  [`snailmail-windbg.log#L118`](../../artifacts/snailmail-windbg.log#L118)

No `startup_bridge_to_26` or `startup_bridge_to_27` tag appeared in the
capture. The ordinary fresh-start lane therefore stayed off the
`0x1a/0x1b` saved-owner bridge.

### 2. Ordinary respawn rebuild uses direct owner `0x1c`

The spare-life slug death produced the respawn-side rebuild at
[`snailmail-windbg.log#L123`](../../artifacts/snailmail-windbg.log#L123):

- `initialize_subgame` re-entered from live `state=2` with `selector=0`
- at that entry, `app_owner=0x1c` and `app_saved=0xb`
- one tick later, `update_subgame state=0` restored `app_owner=0xb` while
  preserving `app_saved=0xb` at
  [`snailmail-windbg.log#L124`](../../artifacts/snailmail-windbg.log#L124)
- the rebuild then flowed through
  [`build_subgame_level`](../../artifacts/snailmail-windbg.log#L125),
  [`initialize_subgoldy`](../../artifacts/snailmail-windbg.log#L126), and
  back into gameplay states
  [`2`](../../artifacts/snailmail-windbg.log#L127),
  [`3`](../../artifacts/snailmail-windbg.log#L128), and
  [`4`](../../artifacts/snailmail-windbg.log#L129)

This rules ordinary respawn rebuild into the direct `0x1c` lane rather
than the `0x1a/0x1b` bridge family.

### 3. Transient pause `End Game` uses completion state `2`

The dedicated pause-return pack captured the transient abandon path at
[`snailmail-windbg.log#L159`](../../artifacts/snailmail-windbg.log#L159):

- `update_pause_menu` repeatedly reported `owner=0xb`, `saved=0xb`,
  `persist=0`, `route_sel=2`, `route_kind=0`
- the chosen branch stored the current owner into the completion-screen
  saved slot at
  [`snailmail-windbg.log#L177`](../../artifacts/snailmail-windbg.log#L177)
- it then chose completion state `2` at
  [`snailmail-windbg.log#L178`](../../artifacts/snailmail-windbg.log#L178)
- finally it switched to owner `0x8` at
  [`snailmail-windbg.log#L179`](../../artifacts/snailmail-windbg.log#L179)

The next observed owner was the completion-screen controller itself:

- `update_completion_screen` ran with `owner=0x9`, `saved=0xb`,
  `state_a=2`, `state_b=0` from
  [`snailmail-windbg.log#L180`](../../artifacts/snailmail-windbg.log#L180)
  onward

So transient pause `End Game` does not jump straight back to the shell or
to the replay-backed `0x1a/0x1b` bridge. It enters completion-screen
state `2`, carrying saved return owner `0xb`.

### 4. Route-map Time Trial replay is still transient

The replay pack first captured the route-map Time Trial replay button at
[`snailmail-windbg.log#L277`](../../artifacts/snailmail-windbg.log#L277):

- `initialize_subgame` entered with `mode=4`, `selector=2`,
  `rec_active=0`, `rec_persist=0`, `saved_return=0`, `route_kind=4`
- `build_subgame_level` later ran with `rec_active=1`, `rec_persist=0`,
  `replay_a=1`, `replay_p=0`, and a live replay pointer at
  [`snailmail-windbg.log#L312`](../../artifacts/snailmail-windbg.log#L312)
- `initialize_click_start` kept the same transient replay state at
  [`snailmail-windbg.log#L314`](../../artifacts/snailmail-windbg.log#L314)
- the pause-abandon path stayed transient too:
  [`pause_set_completion_state_2`](../../artifacts/snailmail-windbg.log#L337)
  and
  [`pause_set_owner_8`](../../artifacts/snailmail-windbg.log#L338)
  ran with `persist=0` and `saved_return=0`
- completion then rebuilt subgame directly through
  [`initialize_subgame`](../../artifacts/snailmail-windbg.log#L371),
  [`state=0`](../../artifacts/snailmail-windbg.log#L372), and
  [`state=1`](../../artifacts/snailmail-windbg.log#L373)

No `startup_bridge_to_26` or `startup_bridge_to_27` hit in this lane.
The route-map Time Trial replay button is therefore not the missing live
`0x1a/0x1b` producer.

### 5. High-score replay rows are persistent and use saved-return state `0x12`

The later high-score replay row finally armed the persistent replay
family at
[`snailmail-windbg.log#L431`](../../artifacts/snailmail-windbg.log#L431):

- `initialize_subgame` entered with `mode=1`, `selector=2`,
  `rec_active=1`, `rec_persist=1`, `replay_a=1`, `replay_p=1`,
  `saved_return=0x12`, and a live replay pointer
- `build_subgame_level` preserved that state at
  [`snailmail-windbg.log#L433`](../../artifacts/snailmail-windbg.log#L433)
- `initialize_click_start` still saw `replay_p=1` and
  `saved_return=0x12` at
  [`snailmail-windbg.log#L435`](../../artifacts/snailmail-windbg.log#L435)

The pause `End Game` branch on that replay then took the persistent
completion lane:

- it stored the current owner into the completion-screen slot at
  [`snailmail-windbg.log#L439`](../../artifacts/snailmail-windbg.log#L439)
- it chose completion state `3` at
  [`snailmail-windbg.log#L440`](../../artifacts/snailmail-windbg.log#L440)
- it switched into the completion owner at
  [`snailmail-windbg.log#L441`](../../artifacts/snailmail-windbg.log#L441)
- it immediately consumed the saved-return state through
  [`completion_restore_owner_from_saved_return`](../../artifacts/snailmail-windbg.log#L442)
  with `saved_return=0x12`

The next rebuild still carried the persistent replay context:

- `initialize_subgame` re-entered with `saved=0x12`, `replay_p=1`, and
  the same replay pointer at
  [`snailmail-windbg.log#L443`](../../artifacts/snailmail-windbg.log#L443)
- `build_subgame_level` and `initialize_click_start` preserved that state
  at
  [`snailmail-windbg.log#L445`](../../artifacts/snailmail-windbg.log#L445)
  and
  [`snailmail-windbg.log#L447`](../../artifacts/snailmail-windbg.log#L447)

This closes the persistent high-score replay pause-return lane: high-score
replay rows are real persistent selected-record launches and they restore
through saved-return state `0x12`.

## Narrowed Read

- `game + 0x1270fc8` is now materially narrowed by direct runtime capture:
  fresh Postal startup showed `2 -> 3 -> 1`, while ordinary respawn
  rebuild showed `0`
- the `0x1a/0x1b` saved-owner bridge was not used by:
  - ordinary fresh Postal startup
  - ordinary spare-life respawn rebuild
  - transient pause `End Game`
  - route-map Time Trial replay launch
- persistent high-score replay rows do not stay on the transient abandon
  path:
  - they arm `rec_persist=1`
  - they seed saved-return state `0x12`
  - pause `End Game` consumes that saved-return state through completion
    state `3`
- this narrows the remaining live `0x1a/0x1b` producers to other
  persistent replay or frontend bridge families, not ordinary lifecycle
  flow and not the route-map replay button

## Still Missing

- no live `startup_bridge_to_26` or `startup_bridge_to_27` hit, even on
  the persistent high-score replay row
- no clean completion-screen trace for the later auto-exit path
- the current `main_menu_enter` probe is mis-sited or late enough to read
  garbage, so its captured owner values are not usable evidence

The next best section-4 follow-up is therefore either:

1. a corrected completion-to-main-menu pack for the persistent replay
   auto-exit path, or
2. another persistent frontend replay source, such as the New Game replay
   attract lane, to force the missing explicit `0x1a/0x1b` producer
