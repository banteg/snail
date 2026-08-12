# initialize_global_trivial_object

CRT constructor body at `0x406d20` for the 16-byte global at `0x4df848`. It
passes that owner to the folded three-byte no-op constructor at `0x44db50`.
The next global begins at `0x4df858`, fixing the extent, but no other instruction
addresses the object and the folded constructor is shared by several classes;
the original class therefore remains deliberately generic.
The generic owner call matches the native 2/2 instructions exactly, with both
masked operands resolved.

## 2026-08-12 source-unit closure

This constructor body is the second dynamic initializer in the Windows
`Mac.o` startup run. The immediately preceding initializer at `0x406c10`
constructs `gConfig`; the exact v1.5 iOS `gConfig` STABS record and its static
initializer independently place that anchor in `Mac.o`. This body follows at
`0x406d20`, before the WinMain-style Mac runtime helpers begin at `0x406d30`.

The source-unit recovery does not invent a class for the dead 16-byte global.
Its callee remains the folded no-op constructor shared by `tAxis`,
`tQuaternian`, `tColour`, and `tColourSmall`; only this unique CRT wrapper and
its thunk receive `Mac.o` provenance.
