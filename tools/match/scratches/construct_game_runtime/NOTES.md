# construct_game_runtime @ 0x407b60

Normalized match: 100.00%, 268/268 instructions under the VC6
`/O2 /G5 /W3 /GX` profile. The complete reference audit has 119 clean operands
and one unresolved exception-handler alias, so this is not proof-grade exact.

The 2026-09-29 tooling audit showed that normalized helper instructions alone
could accept a handler jumping to `operator delete` instead of
`__CxxFrameHandler`. Helper verification now retains nested relocation
identities and encoded bytes. The native EH metadata and handler destination
still need independent content/identity evidence; matching the handler's
instruction shape does not supply that proof.

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

## 2026-10-06 exact: EH handler proven structurally

The source was already 100% normalized and body byte exact; the only open
reference was the `push` of the compiler-generated EH handler thunk
(`$L6760` against `construct_game_runtime_eh_handler` at `0x496a7b`). The
matcher now proves such thunks end to end:

- `0x48bade` is registered as `__CxxFrameHandler` (the trnsctrl.obj body
  identified in `analysis/ownership/library-attribution.json`; all 19 EH
  thunks in the image jump to it).
- The thunk's `mov eax` operand is compared as a VC6 `FuncInfo` record
  (magic `0x19930520`) rather than a float constant: equal max state, IP-map
  and try-block counts, equal unwind states, and every cleanup funclet proven
  equal by the same encoded-body audit as helper aliases. Here that is one
  state (`-1`) whose funclet deletes the allocation through `scalar_delete`.
- The proven thunk and funclet bytes (`0x496a70..0x496a85`, this function's
  `.text$x` chunk) count as covered. Try-block maps are not audited yet and
  never certify.

**100%**, 268/268, body byte exact, 120/120 references; the report now
credits all 1190 owned bytes.
