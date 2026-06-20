# initialize_main_loop_frame_state

Startup frame-loop reset helper at `0x406d70`. It clears the shared frame
timer state, window-deactivation latches, and object texture transform matrix,
then seeds the main-loop timing counters to `1.0f` before the loading screen
and game runtime bootstrap run.

Initial scratch result: 64.71%, 11 candidate instructions versus 23 target
instructions, with all 9 masked operands resolved. The residual is the native
unconditional jump over 11 alignment nops before the three timing-counter
stores; a source-level `goto` experiment was optimized away by VC6 and left the
same candidate.
