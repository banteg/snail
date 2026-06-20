# clear_frame_timer_state

Small `FrameTimerState` method at `0x407910`. Startup calls it before the
active frame loop, and the adjacent `0x407920` helper clears only the secondary
timestamp lane after a minimized-window restore.
