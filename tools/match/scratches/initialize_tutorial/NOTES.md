# initialize_tutorial @ 0x448da0

Exact authored tutorial initializer.

2026-06-20 type cleanup:

- Recovered the visible `Tutorial` prefix. Binary Ninja and the scratch agree
  on `state` at `+0x00` and the borrowed containing
  subgame pointer at `+0x0c`.
- The initializer stores the root-owned `SubgameRuntime` backlink, sets render
  flags `0x600000`, then clears bit `0x2` through `runtime_flags +0x4c`.
- Focused matcher remains exact at 12/12 instructions with 2 clean masked
  operands.

2026-06-21 subgame-header consolidation: `Tutorial::game` now uses the
shared `SubgameRuntime*` type, and this scratch reads `runtime_flags +0x4c`
through that header instead of a duplicate local `Game` slice.

2026-07-11 cRTutorial boundary: the native size ledger and adjacent
`SubTracks +0xa874` boundary prove the complete 0x1c-byte owner, including the
previously anonymous 0xc-byte tail. `tutorial.h` now owns that extent and maps
the exact 12/12 member to Android/iOS `cRTutorial::Init()`.

2026-07-14 root-owner closure: `Tutorial::game` now receives
`&g_game->subgame` directly. The initializer remains exact at 12/12 with both
operands clean.

## 2026-07-14 game-wide feature owner

The initializer now spells the native `0x600000` write as the composite
tutorial-init OR mask and clears the proved ambient-garbage bit by name. The
composite deliberately retains its unresolved `0x200000` member rather than
inventing a feature label. Focused output remains exact at 12/12 instructions
with both operands clean.

2026-07-18 durable decompiler replay: both tracked decompilers now retain the
complete `Tutorial*` member, borrowed `SubgameRuntime*`, root `subgame`, and
`runtime_flags` owner chain. IDA normalizes only the proven `0x74618` owner
displacement and `0x600000` feature-mask immediate, preventing its auto-symbol
heuristic from turning the mask into `&unk_600000`. Paired health checks pin
the recovered graph; matching remains exact at 12/12 with two clean operands.
