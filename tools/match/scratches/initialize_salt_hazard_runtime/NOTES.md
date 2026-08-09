# initialize_salt_hazard_runtime @ 0x408630

Exact constructor wrapper for one authored `Salt` (`cRSalt` cross-port):
constructs the renderable-body prefix, installs the table at `0x497340`, and
returns the receiver. The table entry points directly to
`update_salt_hazard @ 0x441c10`, the preserved `cRSalt::AI()`.

`SaltManager` owns 40 inline 0x98-byte records whose exact 0x17c0 total matches
the native cRSaltManager ledger. The scratch remains exact at 7/7 instructions
with two clean operands.

2026-07-14 renderable inheritance closure: `Salt` now derives from the shared
`RenderableBod` owner that this constructor initializes. This replaces a
field-by-field duplicate of the complete `BodBase + TransformMatrix` prefix;
the inherited `BodNode` remains at offset zero, so intrusive-list ownership is
unchanged. The constructor remains exact at 7/7 with two clean operands.

2026-07-15 analysis-lane owner replay: Binary Ninja and IDA now use `Salt` as
the primary constructor receiver and `SaltManager` element. The first 0x80
bytes resolve as the inherited `RenderableBod body`; `SaltHazardSlot` remains
only a compatibility alias.

## 2026-08-09 shared Object, not Sprite, ownership

The Windows constructor pass at `0x40820c` constructs 40 inline `0x98` actors
and this wrapper installs callback table `0x497340`, whose entry is
`update_salt_hazard`. Startup loads one `salt.x` `cRObject`, borrows it from
every slot, and seeds the containing `cRSubGame*`, alpha `0.9`, blend mode
`12`, and an identity transform. The persistent slot is a renderable BOD, not
a sprite record.

Android and iOS construct the corresponding `0x8c` actors as `cRBodPos` and
share one object per family. Android `cRSalt::Smoke(tVector&)` may allocate a
detached sprite effect, but it never stores that sprite in `cRSalt`; it does
not justify a per-slot `cRSprite*` lane on Windows.
