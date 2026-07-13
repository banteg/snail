# initialize_global_temp_colour

CRT constructor body `0x42f8b0` passes the 16-byte global at `0x503308` to the
folded `Color4f::noop_this_constructor` at `0x44db50`. No other Windows
instruction addresses its four lanes.

The symbol-preserving iOS v1.9 executable independently names the corresponding
16-byte owner `GTempColour`: `nm -n` places it at `0x2adfac`, immediately before
`gEdgeStore` at `0x2adfbc`. The matching type, extent, engine-object provenance,
and absence of a stronger consumer support the recovered Windows name without
inventing a more specific role.

The source matches the native 2/2 instructions exactly, with both the global
owner and folded constructor operands resolved.
