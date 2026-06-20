# initialize_main_loop_display_state

Startup frame-loop reset helper at `0x406d70`. It clears the shared
display-mode/view-sample state, window-deactivation latches, and object
texture transform matrix, then seeds the main-loop timing counters to `1.0f`
before the loading screen and game runtime bootstrap run.

Follow-up display helper disassembly corrected the initial timer-specific name:
the object at `0x4df9e0` feeds `0x412940` with display-mode dimensions and view
samples, while `game_window_proc` resets its probe count after minimized-window
restore.

Initial scratch result: 64.71%, 11 candidate instructions versus 23 target
instructions, with all 9 masked operands resolved. The residual is the native
unconditional jump over 11 alignment nops before the three timing-counter
stores; a source-level `goto` experiment was optimized away by VC6 and left the
same candidate.
