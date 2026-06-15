# destroy_help_screen

Small Help-screen teardown helper at 0x4168c0. Both BN and IDA decompiles show
it forwarding to kill_all_borders on the global border manager at
data_4df904+0xb4c.

Exact match: 100.00%, 3/3 instructions, with g_game_base and kill_all_borders
operands resolved.
