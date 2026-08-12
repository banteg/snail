# cRDuplicateVertices::Clean

`0x419f80` is the authored `cRDuplicateVertices::Clean(int)` method from
`ObjectProc.o`. It scans the owner's 10-byte records and clears later live
flags for duplicate vertex pairs. The retained argument is proven by the
Windows `retn 4`, even though the body does not read it.

- VC6 symbol: `?Clean@cRDuplicateVertices@@QAEXH@Z`
- exact Windows match: 33/33 instructions
- owner callsite: `load_x_animation_clip`
