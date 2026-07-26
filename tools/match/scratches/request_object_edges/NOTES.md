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

## 2026-07-24 paired IDA ownership replay

IDA now shares the exact void Object member ABI and renders the one-time
allocation as the Object-owned `ObjectToonEdge* edges` bank. This retires the
raw `_DWORD*` receiver and fake allocation-pointer return. The manifest now
also describes only the bank this helper actually owns; the temporary index
selection workspace belongs to the downstream rendering path. Matching remains
exact at 16/16.

## 2026-07-26 Android owner verification

Android exposes the exact-demangled `cRObject::RequestEdges(int)` method and
the same one-time allocation guard, confirming the Object owner and retained
edge-count lifecycle. Its port additionally allocates an Object-owned edge
index array and uses ten-byte edge records; Windows instead allocates one
36-byte `ObjectToonEdge` bank. Those storage details are intentionally kept
platform-local. The Windows member remains exact at 16/16 with two clean
operands.
