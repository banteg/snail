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

## 2026-07-25 database ABI closure

The matcher had recovered the authored void `GameRoot` member, but both
database views still treated the native wrapper as an inferred integer-return
fastcall over `void*`. A reversible Binary Ninja prototype preview rewrote the
complete body to `initialize_backdrop(&game->backdrop, 1)` and removed the
incidental tail-call return. IDA independently produces the same owner path
after applying the identical ABI.

The narrow Backdrop replays now persist the function name/prototype and
reanalyze both the wrapper and `game_startup_and_main_loop`; the startup caller
therefore passes `g_game_base` without a `char*` cast. Paired health canaries
guard the member owner and caller edge. Matcher source remains unchanged and
exact at 100.00%, 4/4 instructions, with the call operand clean.
