# request_object_edges @ 0x430570

Exact one-time allocator for the `Object`-owned toon-edge array. A zero
`edge_count` installs the requested count and allocates
`count * sizeof(ObjectToonEdge)` bytes; an existing array is retained.

2026-07-14 void ABI closure: EAX is not a coherent result. The existing-array
path leaves the integer `edge_count` there, while the allocation path leaves
the tracked allocation pointer; the sole `calc_object_edges` caller discards
both. The edge pointer is retained in `Object::edges`, so no ownership is
transferred through the call result. The void member remains exact at 16/16
instructions with both masked operands clean.

2026-07-15 analysis replay: the checked-in Binary Ninja artifact now uses the
canonical `Object*` receiver and names the retained `edge_count`/`edges`
members; the stale generic-pointer result is gone.
