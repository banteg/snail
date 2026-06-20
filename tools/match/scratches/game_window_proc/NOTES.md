# game_window_proc

First scratch for `game_window_proc @ 0x4074b0`.

The function is the main Win32 window procedure. It handles:

- left/right mouse button latches and live state;
- mouse wheel deltas through `g_mouse_wheel_delta[0]`;
- minimize/restore activation bookkeeping for the audio backend and fullscreen
  restoration path;
- ESC/close quit posting;
- default forwarding through `DefWindowProcA`.

The decompile and BN disassembly agree that `WM_MOUSEMOVE` (`0x200`) and
`WM_MOUSEWHEEL` (`0x20a`) share the signed high-word `wparam` path. Normal
mouse movement therefore returns zero without changing the wheel latch.

## Current match notes

Focused matcher result: 89.21%, 137 candidate instructions versus 141 target
instructions, with 37 clean masked operands, 0 unresolved operands, and 2
audited jump-table mismatches. The `message - 2` byte lookup table is now
content-audited as `game_window_proc_low_message_lookup_table`; the two
remaining mismatches are the compiler-emitted jump tables for the `message - 2`
and `message - 0x201` dispatches.

The main remaining source-shape difference is the shared close/ESC quit body:
native lays out the `PostQuitMessage(0)` block before the `WM_KEYDOWN` ESC
test, while this source compiles to the same behavior with the ESC test first.
