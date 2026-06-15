# uninit_pause_menu

Small pause-menu teardown helper at 0x440600. Both BN and IDA decompiles show
it killing the three stored pause-menu borders through the global border manager
and then releasing the shared mouse cursor state at data_4df904+0x290.

Exact match: 100.00%, 22/22 instructions, with all border-manager and
mouse-cursor operands resolved.
