# initialize_tracked_allocation_depth @ 0x430e30

Clears `g_tracked_allocation_depth` before `initialize_game_data_archive` and
the guarded allocation helpers begin using the shared stack. The target global
is independently read and updated by allocation, free, unwind, and mark paths.
