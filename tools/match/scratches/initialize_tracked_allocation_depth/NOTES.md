# initialize_tracked_allocation_depth @ 0x430e30

Clears `g_tracked_allocation_stack.depth` before `initialize_game_data_archive`
and the guarded allocation helpers begin using the shared stack. Allocation,
free, unwind, and bookmark paths independently prove that `0x5108c0` is the
first word of their common owner. The member spelling remains exact at 2/2
instructions with its operand resolved.
