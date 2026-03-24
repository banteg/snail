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

## Narrowed Read

- `game + 0x1270fc8` is now materially narrowed by direct runtime capture:
  fresh Postal startup showed `2 -> 3 -> 1`, while ordinary respawn
  rebuild showed `0`
- the `0x1a/0x1b` saved-owner bridge was not used by:
  - ordinary fresh Postal startup
  - ordinary spare-life respawn rebuild
  - transient pause `End Game`
- this makes the remaining live `0x1a/0x1b` producers look more like
  replay-backed or other persistent launch/return families than ordinary
  lifecycle flow

## Still Missing

- no live `startup_bridge_to_26` or `startup_bridge_to_27` hit
- no final `update_completion_screen` owner-restore hit
- no final `main_menu_enter` hit in the captured window

The next best section-4 follow-up is therefore either:

1. a replay-backed or otherwise persistent launch that can force
   `0x1a/0x1b`, or
2. another pause `End Game` pass where capture remains armed until the
   completion screen actually exits back to the main menu
