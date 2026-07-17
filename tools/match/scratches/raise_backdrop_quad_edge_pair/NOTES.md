# raise_backdrop_quad_edge_pair @ 0x41a170

Raises one or both y components on the four-vertex backdrop quad used by the
`Objects/Univers` lane. The selector controls which side is lifted:

- `< 0`: first configured vertex only
- `0`: both configured vertices
- `> 0`: second configured vertex only

The two configured indices live in small globals at `0x4a3c40` and `0x4a3c44`,
which currently hold `0` and `1`.

Focused match: 100%, 19/19 instructions, with four clean masked operands.

## 2026-07-17 object and index-global ownership

Both databases now record `void __cdecl(int32_t, Object*)`. The two proved
index globals are replayed as `g_backdrop_raise_first_vertex_index` and
`g_backdrop_raise_second_vertex_index`, each `int32_t`, replacing the former
raw bases and incidental pointer return. The exact matcher is unchanged.
