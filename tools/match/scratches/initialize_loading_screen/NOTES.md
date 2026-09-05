# cRLoadingBar::Init @ 0x418b50

Verified cross-port owner: `cRLoadingBar::Init()` in `LoadingBar.o`. Windows
startup loads `ECX = 0x503290` before the call and ignores EAX, proving the
global 0x0c-byte `cRLoadingBar` receiver and void contract.

The initializer loads `Sprites/Loading.tga` and `Sprites/LoadingBarOn.tga`,
creates the background and fill vertex resources, writes the 640x480
background quad, enters overlay render state, and resets the three owner
fields. Native calls `Unlock` through the fill resource after locking the
background resource; the scratch preserves that observed call shape.

The retained source is 83.00%, 253/253 instructions, with all 54 masked
references clean. Its whole-function mismatch is the saved-register split:
VC6 assigns `EDI = this` and `EBX = archive_base`, while native assigns the
opposite pair. Bounded receiver, archive-owner, declaration-order, renderer
owner, and calling-convention probes either emitted identical bytes or
regressed. This is a compiler-scheduling residual, not ownership or ABI
uncertainty; the matcher therefore uses the authored `Init` name without
claiming an exact body.

The three linked D3DX 8 texture wrappers have independently verified
`__stdcall` cleanup: `d3dx_create_texture_from_file_in_memory_ex` returns with
`0x3c`, `d3dx_create_texture_from_file_ex` with `0x38`, and
`d3dx_create_texture_from_file` with `0x0c`.

## 2026-08-14 distribution-budget control

The recovered RealArcade-derived executable and canonical initializer both
decode to 263 instructions through the next function boundary. Their sole
non-relocation difference is the first store: loading budget `0x4fe` rather
than canonical `0x4fc`.
The earlier DAT has 601 entries and a runtime font-atlas splitting path; the
canonical DAT has 603 entries and two prebuilt split font textures.

This makes the budget a distribution/content constant and confirms that the
remaining saved-register mismatch is not missing loading-screen behavior. The
older build supplies no alternative source shape worth replaying against the
canonical target.

## 2026-09-05 whole-function source-lifetime probes

Three texture-load lifetime probes test a shared archive pointer, separate result/count scopes per texture, and the load helper result. None improves 83.00%. The returned-byte-pointer variant regresses and is not retained; native continues to consume the archive buffer.

## 2026-09-05 continued source-shape investigation

Two common texture-loading helper forms are neutral at 83.00%. Both preserve error fallback and the native background-lock/bar-unlock behavior. No helper is retained.
