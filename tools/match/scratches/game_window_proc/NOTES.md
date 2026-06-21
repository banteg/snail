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

Focused matcher result: 94.33%, 141 candidate instructions versus 141 target
instructions, with 37 clean masked operands, 0 unresolved operands, and 2
audited jump-table mismatches. The `message - 2` byte lookup table is now
content-audited as `game_window_proc_low_message_lookup_table`; the two
remaining mismatches are the compiler-emitted jump tables for the `message - 2`
and `message - 0x201` dispatches.

Writing the `WM_KEYDOWN` arm as `if (wparam != 0x1b) return 0;` keeps the
non-ESC return as a standalone block and recovers the missing four instructions.

2026-06-21 close/ESC layout pass: duplicating the `PostQuitMessage(0)` call in
the `WM_CLOSE` and ESC keydown arms, instead of using a shared source label,
matches native's close block before the ESC test and improves focused Wibo from
`91.49%` to `94.33%`. The final `WM_RBUTTONUP` arm still delays `xor eax, eax`
until after the two right-button state stores; staged `LRESULT`, `int`, and
`unsigned char` zero locals were codegen-neutral, so leave that as a scheduler
residual.
