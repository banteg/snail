# noop_runtime_callback

Exact match: 100.00%, 1/1 instruction, no masked operands.

## 2026-08-12 authored cRGame::LevelInit owner

This is not a shared anonymous callback. Live Binary Ninja xrefs show no direct
calls and exactly one data reference: the one-entry table at `0x4972d8` that
`construct_game_runtime` installs at `cRGame +0x00`. The Android cRGame
constructor installs its corresponding vtable at the same lifecycle point;
Ghidra labels its first callable slot `LevelInit`. Android and iOS both export
one four-byte `cRGame::LevelInit(int)` body, and the iOS symbol and vtable are
assigned directly to `Game.o`.

All three bodies are empty. ARM returns with the cRGame receiver still in `r0`,
whereas the Windows `ret 4` body never establishes `eax`; the incompatible
residue proves an authored void method rather than a receiver-returning
contract. The explicit integer accounts for the four-byte Windows stack pop
and the mobile `r1` argument. The stable matcher identifier remains
`noop_runtime_callback`, while the source now uses the exact member owner and
the vtable is named `g_game_level_init_callback_table`.
