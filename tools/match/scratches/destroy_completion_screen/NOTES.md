# destroy_completion_screen

Small completion-screen teardown helper at 0x406060. Both BN and IDA decompiles
show it killing the three stored completion widgets, unhiding all global borders,
restoring the previous frontend state at data_4df904+0x1b8, and returning the
unhide result.

Exact match: 100.00%, 25/25 instructions, with all border-manager and
frontend-state operands resolved.
