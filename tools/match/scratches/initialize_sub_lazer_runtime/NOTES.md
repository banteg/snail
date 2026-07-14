# initialize_sub_lazer_runtime @ 0x408610

Exact constructor wrapper for one authored `SubLazer` (`cRSubLazer` cross-port):
constructs the renderable-body prefix, installs the table at `0x49733c`, and
returns the receiver. That table points directly to
`update_sub_lazer_projectile @ 0x4417d0`, the preserved `cRSubLazer::AI()`.

`SubLazerManager` owns 20 inline 0xb0-byte records; their exact 0xdc0 total
matches the native cRSubLazerManager size ledger. The scratch remains exact at
7/7 instructions with two clean operands.

2026-07-14 renderable inheritance closure: `SubLazer` now derives from the
shared `RenderableBod` owner initialized here. The hand-written duplicate of
its `BodBase + TransformMatrix` prefix is retired; inherited `BodNode` linkage
still begins at offset zero. The constructor remains exact at 7/7 with both
masked operands clean.
