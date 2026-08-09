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

2026-07-15 analysis-lane owner replay: Binary Ninja and IDA now use
`SubLazer` as the primary constructor receiver and manager element. The live
analysis layout replaces the flattened prefix with the exact inherited
`RenderableBod body`; `SubLazerSlot` remains a compatibility alias only.

## 2026-08-09 shared Object, not Sprite, ownership

The Windows constructor pass at `0x4081f4` constructs 20 inline `0xb0` actors
and this wrapper installs callback table `0x49733c`, whose entry is
`update_sub_lazer_projectile`. Startup then loads one `Objects/Lazer`
`cRObject` and assigns that same borrowed object to every actor while seeding
the containing `cRSubGame*`, alpha `0.7`, and blend mode `9`. The per-slot
owner is therefore `RenderableBod -> cRBod -> cRObject*`; there is no owned
`cRSprite*` field.

Android and iOS independently construct each mobile actor as `cRBodPos` before
installing the SubLazer table. Their `0xa4` stride is `0x0c` smaller than the
Windows actor because the inherited mobile body prefix is smaller, so it
confirms the relationship but must not be used as a Windows offset template.
