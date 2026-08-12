# cRDirectX::Init @ 0x405c90

This is the exact Windows `cRDirectX::Init()` body: 13/13 instructions, a full
prefix, and three clean masked operands. The VC6 candidate exports
`?Init@cRDirectX@@QAEXXZ`.

The sole native caller passes `cRGame +0x48e00`. The method clears the cached
mesh count, retains the loaded `XAnimation.txt` bytes, and initializes the
embedded `cRDuplicateVertices` workspace at `+0x5e08`. Together the animation
pointer, 128 fixed `0xbc` cache slots, and duplicate workspace close the
root-owned `cRDirectX` extent at `0x5e10` bytes. Android and iOS preserve the
same authored owner and method.
