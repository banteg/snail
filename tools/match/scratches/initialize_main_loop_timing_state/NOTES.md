# initialize_main_loop_timing_state

Private startup timing-state initializer at `0x406da0`. It seeds the mean
update-step count, current-frame update-step count, and rendered-frame count to
`1.0f` immediately before the active frame loop begins.

The function begins on a 16-byte boundary after 11 nops. Its only incoming
edge is the terminal `jmp` from `initialize_main_loop_display_state` at
`0x406d90`; the startup loop calls that display helper rather than this function
directly. Keeping the two routines separate recovers the native tail-call
ownership and excludes linker/compiler alignment padding from both extents.
The three assignments compile to the native 4/4 instructions exactly, with all
3 masked operands resolved.
