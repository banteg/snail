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
- `+0x8/+0xc`: secondary suppressor accumulator / step
- `+0x10/+0x14`: replay-attract accumulator / step
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

## New Conclusion

The remaining launcher gap is now narrower than before:

- the unresolved writer for `this + 0x14` is **not** in:
  - `update_frontend_state_machine`
  - `initialize_new_game_menu`
  - `destroy_main_menu`
- the `+0x8/+0xc` suppressor lane is also **not** initialized in those ordinary entry/exit paths

So the next static targets are not generic menu setup code. They are more likely:

- a separate startup/bootstrap helper that touches the reused New Game controller object
- a one-shot post-run or post-launch reseed path
- a higher-level frontend helper that runs outside the ordinary `initialize_new_game_menu` / `destroy_main_menu` pair

## Porting Implication

Do **not** seed the New Game replay-attract timer on ordinary menu entry in Zig.

The current evidence says that would add a producer the native code does not use in the normal state-machine path.

## Next Static Targets

1. Recover writers to `data_4df904 + 0x4f2dc + 0x14` outside the four functions above.
2. Recover any writers to `data_4df904 + 0x4f2dc + 0x8/+0xc` other than the success / give-up reset in `update_new_game_menu`.
3. Re-check whether the relevant writer lives in a broader frontend bootstrap/helper family rather than a menu-local controller.
