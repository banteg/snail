# initialize_game_last

Small game-root initializer wrapper at 0x410720. Both BN and IDA decompiles
show it calling initialize_backdrop on the embedded backdrop controller at
this+0x4ec10 with the last-mode flag set to 1.

Exact match: 100.00%, 4/4 instructions, with the initialize_backdrop call
operand resolved.

2026-07-14 root-owner cleanup: the wrapper now calls the already-proven
`GameRoot::backdrop` member directly instead of reconstructing it from
`this + 0x4ec10`. The member spelling remains exact at 4/4 instructions with
the call operand clean.
