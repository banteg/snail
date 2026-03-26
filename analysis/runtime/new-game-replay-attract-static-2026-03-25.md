# New Game Replay-Attract Static Pass

Date: March 25, 2026

## Scope

Bounded static RE on the remaining New Game replay-attract gap, limited to:

- `update_new_game_menu`
- `initialize_new_game_menu`
- `update_frontend_state_machine`
- `destroy_main_menu`

Goal: narrow the unresolved writer for the menu-local replay-attract step at `data_4df904 + 0x4f2dc + 0x14`, and the maintenance path for the secondary timer lane at `+0x8/+0xc`, without widening runtime capture.

## Confirmed Layout

The New Game menu object still has the same useful partial layout:

- `+0x0`: replay-attract cursor
- `+0x4`: likely hide latch
- `+0x8`: likely post-launch hide-release accumulator
- `+0xc`: unresolved companion reset value for that lane; still a candidate step, but no reader is recovered yet
- `+0x10`: replay-attract launch accumulator
- `+0x14`: likely replay-attract launch addend; producer still unresolved
- `+0x30..+0x44`: widget pointers for Postal / Time Trial / Challenge / Tutorial / Help / Back

## Findings

### 1. `update_frontend_state_machine` only resets the cursor on state `1`

BN and IDA agree:

- state `1`:
  - writes `*(data_4df904 + 0x4f2dc) = 0`
  - calls `initialize_new_game_menu(data_4df904 + 0x4f2dc)`
- state `2`:
  - calls `initialize_new_game_menu(data_4df904 + 0x4f2dc)`
  - immediately falls into `update_new_game_menu(data_4df904 + 0x4f2dc)`

Important negative result:

- neither state `1` nor state `2` seeds `+0x4`, `+0x8/+0xc`, or `+0x10/+0x14`
- ordinary New Game entry only guarantees `cursor = 0`

Implication:

- the missing replay-attract step writer is not part of the ordinary frontend-state handoff into New Game

### 2. `initialize_new_game_menu` does not seed the replay-attract timers

`initialize_new_game_menu` only:

- rebuilds the menu backdrop and shell-font context
- allocates and positions the six widgets
- applies the tutorial/unlock gate by setting `0x8000` on Postal / Time Trial / Challenge when the tutorial flag is still clear

It does **not** write:

- `+0x4`
- `+0x8/+0xc`
- `+0x10/+0x14`

Implication:

- the replay-attract timer producer is not hidden in the menu constructor

### 3. `destroy_main_menu` is pure teardown

`destroy_main_menu` only:

- `kill_all_borders(...)`
- `kill_game_sprites()`

It does not touch the New Game menu-local controller fields.

Implication:

- the replay-attract timer lanes are not being reset in menu teardown either

### 4. `update_new_game_menu` still owns the actual replay-attract launch

The launch side remains as previously narrowed:

- direct buttons use the ordinary owner/state path
- the replay-attract lane is local to `update_new_game_menu`
- cursor values `0/1/3` are the only replay-bank probes
- successful replay-attract launch writes:
  - `app.owner = 10`
  - `app + 0x30c = 1`
  - `app + 0x1066be8 = 1`
  - `app + 0x1066be9 = 1`
  - `app + 0x1066bf0 = 2`
  - `app + 0x74658 = 0/1/4`
- success and `1000`-attempt give-up both reset:
  - `this + 0x8 = 0`
  - `this + 0xc = 1/3600`

### 5. The tracked whole-image decompile does not show any out-of-line timer writers

The stronger March 26 follow-up is negative but useful:

- the tracked full Binary Ninja HLIL snapshot only shows direct global references to this controller family in:
  - `update_frontend_state_machine`
  - `update_completion_screen`
  - `initialize_subgame`
  - `update_subgame`
- among those consumers:
  - `update_frontend_state_machine` only writes `cursor = 0` on ordinary state-`1` entry
  - `update_completion_screen` only tail-calls `update_new_game_menu(...)` in the one New Game return branch
  - `initialize_subgame` only reads the likely hide latch at `data_4df904 + 0x4f2e0`
  - `update_subgame` only reads `data_4df904 + 0x4f2e0` and `data_4df904 + 0x4f2e4`, then clears the hide latch when that suppressor accumulator exceeds `1.0`
- there are no additional tracked absolute references to:
  - `data_4df904 + 0x4f2e8` (`+0xc`)
  - `data_4df904 + 0x4f2ec` (`+0x10`)
  - `data_4df904 + 0x4f2f0` (`+0x14`)

Implication:

- if another producer exists, it is not showing up as a normal out-of-line global-field writer in the current tracked decompile
- the remaining unknown is therefore narrower than “some generic frontend helper”
- the most likely residual possibilities are:
  - mutation hidden behind an indirect/menu-local callback path
  - a build- or data-dependent lane that is dormant in the current Windows image
  - a decompiler-blurred write that only appears through the local `this` pointer inside `update_new_game_menu`

## New Conclusion

The remaining launcher gap is now narrower than before:

- the unresolved writer for `this + 0x14` is **not** in:
  - `update_frontend_state_machine`
  - `initialize_new_game_menu`
  - `destroy_main_menu`
- no additional tracked absolute writer or consumer exists outside the menu/update-subgame family either
- the `+0x8/+0xc` hide-release lane is also **not** initialized in those ordinary entry/exit paths
- `+0x8` is the only member of that lane with a confirmed cross-function consumer outside `update_new_game_menu`
- no tracked out-of-line absolute reader currently explains `+0xc`, `+0x10`, or `+0x14`

So the next static targets are no longer generic menu setup code. They are more likely:

- a local helper reached from inside `update_new_game_menu`
- a build/data-controlled dormant path that the current runtime never seeds
- a decompiler-blurred store on the reused controller object rather than another named frontend controller family

## Porting Implication

Do **not** seed the New Game replay-attract timer on ordinary menu entry in Zig.

The current evidence says that would add a producer the native code does not use in the normal state-machine path.

## Next Static Targets

1. Re-audit the local helper/call path inside `update_new_game_menu` for decompiler-blurred writes to `this + 0x8/+0xc/+0x10/+0x14`.
2. Re-check the small set of New Game return paths (`update_completion_screen`, `update_frontend_state_machine`) for any path-sensitive seed that only appears in the non-default branch bodies.
3. Treat the absent out-of-line writer as a real possibility: the current build may simply leave the random replay-attract lane dormant on ordinary idle New Game entry.
