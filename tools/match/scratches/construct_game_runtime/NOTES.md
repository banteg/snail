# construct_game_runtime @ 0x407b60

Exact match: 100.00%, 268/268 instructions, with all 120 masked operands
clean under the VC6 `/O2 /G5 /W3 /GX` profile.

Live Windows analysis proves the outer entry is a no-argument `int` cdecl
factory/wrapper with one startup caller. It prints the runtime size ledger,
allocates the exact `0x12e6ff4`-byte root with C++ exception cleanup, runs the
embedded construction sequence, publishes `g_game`, and reports allocation
counters. The emitted candidate symbol is
`?construct_game_runtime@@YAHXZ`; this entry is not a cRGame constructor
method.

Android `Game.o` preserves `cRGame::cRGame()` and independently corroborates
the bounded inlined constructor region: the root callback owner, 150 border
records, 128 cached object slots, Backdrop, StarManager, logo banks, embedded
cRSubGame, and TipManager. Platform layouts and the surrounding Windows
wrapper work do not transfer. The crosswalk records this distinction as
`mapping_scope: interior-region`.

The stable matcher identity and outer source name remain
`construct_game_runtime`.
