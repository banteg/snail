# cRDirectX::ModelAdd @ 0x405cc0

This is the exact Windows `cRDirectX::ModelAdd(char*)` body: 65/65 instructions,
a full prefix, and six clean masked operands. The VC6 candidate exports
`?ModelAdd@cRDirectX@@QAEHPAD@Z`.

The method walks the root-owned 128-slot X-mesh cache using the proven `0xbc`
slot stride and name lane at `+0x3c`. A miss copies the name, attaches a newly
allocated `cRObject` to the selected cRBod-derived slot, invokes
`cRDirectX::Load`, increments the cache count, and returns the selected index.
Both native callers pass `cRGame +0x48e00`; Android and iOS retain the exact
`cRDirectX::ModelAdd(char*)` symbol and homologous cache lifecycle.
