# clear_display_mode_state

Small `DisplayModeState` method at `0x407910`. Startup calls it before the
active frame loop. Raw display helper disassembly shows this state is the
display-mode/view-sample state used by render setup, not a frame timer: the
method clears the queued view-sample count and current display-mode pointer.
