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

## 2026-07-27 mobile authored owner

Android and iOS retain this final root-startup lifecycle as
`cRGame::InitLast()` from `Game.o`. Their platform bootstrap functions invoke
it in the same phase as Windows: after the staged asset/texture initialization
and before the loading screen is finished and the opening fade begins.

Android contains the exact `cRBackdrop::Init(backdrop, 1)` operation that is
the complete Windows body, surrounded by mobile-only keypad, online-service,
options, and initialization-flag work. iOS preserves the method and lifecycle
but uses a different mobile backdrop finalization sequence. This evidence
recovers the authored owner and method name without importing either mobile
body into the four-instruction desktop projection.
