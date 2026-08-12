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

## 2026-08-12 Mac source-unit closure

This is a normal helper in the Windows Mac startup run, not a fourth CRT
initializer. The initializer table contains `0x406bc0`, `0x406c10`, and
`0x406d10`; the sole edge into this aligned body is instead the tail call from
`initialize_main_loop_display_state`, and all three globals are consumed only
by the immediately following WinMain-style frame loop.

The run begins at the directly sourced `Mac.o` `gConfig` initializer at
`0x406c10` and continues through the window/main-loop block into the separately
recorded Mac constructor-support run. This establishes `Mac.o` provenance for
the timing helper while deliberately making no mobile whole-function mapping:
the iOS app delegate owns a different timer architecture.
