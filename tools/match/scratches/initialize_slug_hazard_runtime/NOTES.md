# initialize_slug_hazard_runtime

`initialize_slug_hazard_runtime` @ 0x408530 is the exact seven-instruction
Windows constructor for one authored `Slug` (`cRSlug` cross-port). It constructs
the inherited `RenderableBod`, installs the table at `0x497324`, and returns the
receiver. The sole table entry is `update_slug_hazard_ai` @ 0x43f930, matching
Android and iOS `cRSlug::AI()` provenance.

`SubgameRuntime` owns eight inline 0xec-byte `Slug` records at `+0x3563a0`.
Their exact 0x760 extent is the native `Size of cRSlug` ledger value.
`SlugHazardRuntime` remains only a compatibility alias for older scratch
vocabulary.
