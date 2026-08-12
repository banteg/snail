# cRBackdrop::SetZoom @ 0x410c30

Exact Windows member: 3/3 instructions with no masked operands.

Android and iOS independently preserve `cRBackdrop::SetZoom(float)`. The sole
Windows caller, `update_subgoldy`, passes a normalized track-row payload ratio
to the root-owned `cRBackdrop` at `GameRoot +0x4ec10`; the method stores it at
backdrop `+0x6c8`.

The stable matcher identity remains `set_backdrop_zoom`, with the authored VC6
decorated symbol selected by `scratch.conf`.
