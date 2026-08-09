# initialize_slug_hazard_runtime

`initialize_slug_hazard_runtime` @ 0x408530 is the exact seven-instruction
Windows constructor for one authored `cRSlug`. It constructs
the inherited `RenderableBod`, installs the table at `0x497324`, and returns the
receiver. The sole table entry is `update_slug_hazard_ai` @ 0x43f930, matching
Android and iOS `cRSlug::AI()` provenance.

`cRSubGame` owns eight inline 0xec-byte `cRSlug` records at `+0x3563a0`.
Their exact 0x760 extent is the native `Size of cRSlug` ledger value.
`SlugHazardRuntime` remains only a compatibility alias for older scratch
vocabulary.

## 2026-07-15 analysis-lane owner replay

The matcher uses `cRSlug` as its primary receiver; Binary Ninja and IDA retain
`Slug` as stable analysis vocabulary. The Binary Ninja view replaces the stale anonymous 0x80-byte
prefix with the exact inherited `RenderableBod body`, so list links and world
position resolve through the authored base. The state-two writes at
`+0x9c..+0xab` remain `unknown_9c`; no unobserved ownership was inferred.

## 2026-07-19 lifecycle enum ownership

Both analysis lanes now preserve `SubSlugState` at owner `+0x80` and
`SubSlugDeathTossDirection` at `+0x84`. IDA verifies the exact `0xec` owner,
`0x760` eight-slot pool, and `0xec` state-stride cursor before saving; Binary
Ninja independently replays the exact enum member sets. The constructor stays
exact at 7/7 instructions and does not seed speculative fields.

## 2026-07-25 death-toss lane typing

The former `unknown_9c` span is now four float fields on the concrete `cRSlug`
owner. Windows and Android independently preserve the two adjacent
`(progress, step)` store pairs in the death-toss transition. No reader or
shared hazard base is inferred; the constructor remains exact at 7/7.
