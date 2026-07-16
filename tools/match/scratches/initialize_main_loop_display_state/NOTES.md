# initialize_main_loop_display_state

Startup display-state reset helper at `0x406d70`. It clears the shared
display-mode/view-sample state, window-deactivation latches, and object
texture transform matrix, then tail-calls the adjacent timing-state initializer
before the loading screen and game runtime bootstrap run.

Follow-up display helper disassembly corrected the initial timer-specific name:
the object at `0x4df9e0` feeds `0x412940` with display-mode dimensions and view
samples, while `game_window_proc` resets its probe count after minimized-window
restore.

Initial scratch result: 64.71%, 11 candidate instructions versus 23 target
instructions, with all 9 masked operands resolved. The apparent residual was a
bad function extent: native ends this helper with `jmp 0x406da0`, followed by
11 alignment nops and a distinct three-store function. A raw executable scan
found only the startup call to `0x406d70` and this tail jump to `0x406da0`, with
no direct call to the aligned helper. Splitting the manifest at `0x406da0`
recovers the private two-function ownership chain without treating padding as
source or spelling a byte-shaped `goto`. With the explicit tail call, VC6 emits
the native 8/8 instructions exactly, with all 7 masked operands resolved.

2026-07-16 process-state closure: the display object is now declared by its
own shared header, and the identity write targets the canonical render-pipeline
UV transform. The startup helper remains exact at 8/8 instructions with all
seven operands clean.
