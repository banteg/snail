# initialize_game_window_and_input @ 0x4119d0

Initial recovery for the Win32 window/input startup helper.

- Picks one of the recovered 4:3 resolution presets from
  `RuntimeConfig::display_mode_index`,
  defaulting back to 640x480 when the setting is out of range.
- Registers `"SnailMailWindowClass"` with `game_window_proc`, then creates the
  main window, initializes the renderer, keyboard, controllers, and mouse, and
  sets cull mode.
- The caller passes the current fullscreen-active byte as a second argument to
  `initialize_mouse_input`; that callee only reads the first stack argument, but
  the extra push is part of this caller's native shape.

Focused match result: 79.85% (`287` target instructions, `264` candidate
instructions), with `49` masked operands resolved, `0` unresolved, and `1`
masked mismatch.

2026-06-20 startup/window symbol pass:

- `RuntimeConfig::display_mode_index`, `g_game_window_instance`, `g_main_window_dc`, and
  `g_controller_count_view` are now curated references backed by this function's
  direct consumers.
- The resolution switch table at `0x411d54` is named as
  `initialize_game_window_resolution_jump_table`. The remaining masked mismatch
  is the table's differing case-target layout, not an unknown data owner.

Remaining gaps are mostly code-layout shape rather than unknown behavior:

- MSVC hoists the `0x400` constant into `ebp` for the render-depth test instead
  of emitting the native immediate `and esi, 0x400`.
- The native switch stores the authored width in each case block; this scratch
  still lets the compiler sink that store to the common path.
- The fullscreen fallback and common window-creation block are equivalent, but
  the compiler lays out the out-of-line fullscreen path earlier than native.

2026-06-20 type consolidation: the Win32-style `Rect` view now lives in
`include/rect.h` and is shared with the mouse scratches. Focused rerun keeps
the existing result at 79.85%, 264 candidate instructions versus 287 target
instructions, 49 masked operands OK, and the same jump-table relocation
mismatch.

2026-06-21 branch layout pass: moving the authored-width assignment before the
case-local width/height stores recovers the native per-case stack write shape,
inverting the second fullscreen check restores the native fullscreen/windowed
block layout, and spelling the unused mouse fullscreen argument as a byte-sized
parameter removes the extra zero-extension before the final input call. The
rectangle setup now writes `left`, `right`, `top`, `bottom` to match native
store order. Focused Wibo improves to 87.88%, with 266/287 instructions, a
6/287 prefix, 53 clean masked operands, and the same resolution jump-table
label mismatch. The remaining pinned residuals are the `0x400` constant hoist
into `ebp` and the local cleanup thunk/tail bytes still included in the target
extent.

2026-07-11 Win32 ownership pass:

- `win32_window_state.h` now owns the shared 32-bit handle ABI, `WndClassA`,
  `DevModeA`, and the main/BASS window globals. It distinguishes the WinMain
  instance at `0x4dfad8`, which the BASS window consumes, from this compilation
  unit's independently cached game-window instance at `0x50327c`.
- The latter is therefore named `g_game_window_instance`; the earlier generic
  `g_module_instance` spelling remains a manifest alias.
- COFF places the current resolution table symbol `$L757` at `.text+0x380`
  with exactly five relocations through `+0x390`, proving the `0x14`-byte table
  owner. The pre-header `$L734` spelling remains as an alternate compiler
  alias. Bounded comparison still reports one mismatch because the candidate
  case destinations differ with the known width-store layout; the alias does
  not waive that difference.
- A branch-form depth-selection probe regressed to 85.87% and changed the
  function entry/layout, so the source-truer branchless ternary remains. The
  focused baseline stays 87.88%, 266/287, with 53 clean operands and one honest
  table mismatch.
