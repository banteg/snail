# update_mouse

Exact scratch for `update_mouse @ 0x44bc50`.

The helper polls the DirectInput mouse device, updates the shared live mouse
coordinates, clips the system cursor against the active client rectangle, and
forwards the current pointer state into slot 0 through
`update_input_controller_pointer_region`.

The ranges at `0x4b7770..0x4b777f` and `0x4b7780..0x4b778f` are recovered as
the captured-client and uncaptured-clip Win32 `RECT` globals.

## Source-shape notes

- Native reloads `g_game_base + 0x290` for each `is_mouse_captured` query.
  Caching the cursor object in a local made VC6 keep that pointer live in `esi`
  and dropped the focused score to 61.64%, so the scratch keeps the repeated
  member-expression spelling.
- The live-coordinate clamps use the native `< 0.0f` then `> max` shape. The
  equivalent `>= 0.0f` outer test inverted the branch layout and reduced the
  match.
- The DirectInput acquire retry is retained as ordinary source: `Acquire`
  repeats while the mouse device reports input lost.

Focused matcher result: 100.00%, 295/295 instructions, full prefix, and 81
clean masked operands.

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

2026-07-13 rectangle ownership pass: `initialize_direct3d_renderer_defaults`
proves the eight adjacent dwords are two complete Win32 rectangles, seeded from
the integer-authored viewport dimensions before the uncaptured rectangle is
expanded with `AdjustWindowRectEx`. `update_mouse` now consumes the shared
`mouse_window_state.h` owners and remains byte-shape neutral at 73.68%, 294/295,
with 70 clean operands and the same one alignment mismatch.

## 2026-07-13 DirectInput and clip-lifetime closure

- The 20-byte state passed to `GetDeviceState` is the SDK `DIMOUSESTATE2`
  layout: three signed motion/wheel dwords followed by eight button bytes. It
  now lives in the shared DirectInput header as `DirectInputMouseState` rather
  than a scratch-local anonymous record.
- Native clears that complete state owner before polling. Replacing five
  field stores with `memset(&state, 0, sizeof(state))` recovers the vtable-load
  schedule and lifts the focused result from 73.68% to 97.97%, while removing
  the spurious Win32 import-alignment mismatch.
- The failed window/client-rectangle path stores the four zero fields in the
  native bottom/left/right/top order. A whole-`Rect` `memset` regressed to
  59.50% by changing saved-register ownership and was rejected.
- The non-fullscreen captured branch falls through the uncaptured rectangle
  construction and takes the captured/null clip path as the alternate edge.
  Spelling that query as `if (!is_mouse_captured())` recovers the native
  borrowed-rectangle lifetime and closes the remaining branch exactly.
- Final focused Wibo is 100.00% (`295/295`, full prefix), with all 81 masked
  operands resolved and equal. No register hints, volatile state, or dummy
  control flow are used.

## 2026-07-16 shared DirectInput state ownership

The poller now borrows the canonical process-owned mouse device, and its
`GetDeviceState` byte count derives from the complete 20-byte SDK state record.
Initialization and teardown use the same shared parent/device lifetime. The
function remains exact at 295/295 instructions with all 81 operands clean.

The authored/live coordinate arrays and cursor-hide latch now come from the
separate canonical two-slot mouse state bank. This keeps DirectInput interface
lifetime distinct from pointer/window state and remains exact at 295/295.

## 2026-07-18 pointer-region ABI closure

The thirteen-parameter pointer-region declaration now lives in the shared
input-controller header instead of this scratch. At the only native callsite,
the instruction immediately after the call reloads the cursor-hide latch into
`al`, proving the callee's incidental `eax` residue is not a return value. The
centralized `void` prototype is byte-shape neutral here: the focused result
remains exact at 295/295 with all 81 masked operands clean.
