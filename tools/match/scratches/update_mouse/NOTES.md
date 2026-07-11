# update_mouse

First scratch for `update_mouse @ 0x44bc50`.

The helper polls the DirectInput mouse device, updates the shared live mouse
coordinates, clips the system cursor against the active client rectangle, and
forwards the current pointer state into slot 0 through
`update_input_controller_pointer_region`.

The `g_mouse_*client*` and `g_mouse_*clip*` globals at `0x4b7770..0x4b778c`
are recovered Win32 client/clip offsets now named in the reference manifest.

## Source-shape notes

- Native reloads `g_game_base + 0x290` for each `is_mouse_captured` query.
  Caching the cursor object in a local made VC6 keep that pointer live in `esi`
  and dropped the focused score to 61.64%, so the scratch keeps the repeated
  member-expression spelling.
- The live-coordinate clamps use the native `< 0.0f` then `> max` shape. The
  equivalent `>= 0.0f` outer test inverted the branch layout and reduced the
  match.
- The DirectInput acquire retry is retained as ordinary source. Native's
  scheduling differs in the first retry block, but the recovered behavior is
  the expected `Acquire` loop while the mouse device reports input lost.

Focused matcher result: 73.68%, 294 candidate instructions versus 295 target
instructions, 5-instruction prefix, and 70 clean masked operands.

The former nine unresolved masked operands were the mouse client/clip offset
globals at `0x4b7770..0x4b778c`; those now resolve cleanly. The remaining
masked mismatch reports `GetClientRect` versus `GetWindowRect` because the
normalized diff aligns the target's second Win32 call with the candidate's
first call after earlier control-flow drift; the candidate object itself
contains distinct `__imp__GetWindowRect@8` and `__imp__GetClientRect@8`
relocations.

2026-06-20 type consolidation: `Rect` now comes from `include/rect.h` here,
`update_mouse_authored_scale`, and `initialize_game_window_and_input`.
Focused rerun preserves the prior result at 73.68%, 294 candidate
instructions versus 295 target instructions, with 70 masked operands OK and
the same Win32 import alignment mismatch.

2026-07-11 root mouse-owner pass: every capture query now reaches the player-
owned cRMouse-compatible prefix through `GameRoot::players[0].mouse_cursor`.
The DirectInput/Win32 helper remains a free platform function, and the focused
result stays 73.68%, 294/295 instructions, prefix 5/295, with the same 70 clean
operands and one import-alignment mismatch.
