# initialize_track_render_cache_manager @ 0x433060

Initial shape:

- Seeds five render-cache capacity pairs.
- Stores the borrowed enclosing `SubgameRuntime*` at manager `+0x54`; the
  runtime begins at `game+0x74618`.
- Initializes the 143 x 5 cache BOD slots by allocating an `Object` for each
  slot, attaching it through `set_bod_object`, clearing the object geometry
  counters, marking its directly constructed buffers with
  `OBJECT_FLAG_RENDER_BUFFERS_READY`, and allocating per-object
  D3D/index/texture-group resources.
- The fifth slot in each row uses `blend_mode = 5`, matching the skirt/cache
  lane used by `update_track_render_cache_rows`.
- Allocates the five shared GDX cache vertex/index buffers from the recovered
  capacity arrays.

Layout correction:

- The old header had its runtime backlink at `+0x28`. The native
  constructor proves the fixed layout is `unknown_00`, capacity arrays at
  `+0x04/+0x18`, shared vertex/index buffers at `+0x2c/+0x40`, and
  `owner_subgame` at `+0x54`, with cache slots still starting at `+0x58`.
- The slot initialization loop uses a manager-relative cursor view: native
  computes `manager + slot_index * 0x3c`, then accesses the BOD at `+0x58` and
  the attached object pointer at `+0x7c`.

Status:

- 2026-06-18: 91.80%, 122/122 instructions, masked operands clean. Remaining
  residuals were register/scheduling only: capacity seed register choice, a
  commuted slot-index `lea`, and a delayed shared-vertex-buffer store before
  the index-buffer allocation setup.
- 2026-06-18 follow-up: spelling the shared GDX vertex allocation through an
  explicit `vertex_buffer` temporary recovers the native store-before-index
  setup order. Keeping the index element count as a separate temporary gives
  the best current shape: 93.44%, 122/122 instructions, 18 clean masked
  operands. Remaining residuals are the capacity seed register/scheduling
  block, the commuted slot-index `lea`, and the tail byte-count register choice
  (`eax` plus `lea edx,[eax+eax]` versus native `edx` plus `shl edx,1`).
- 2026-06-20 larger near-proof pass: spelling the slot cursor as
  `this + slot_base * 0x3c + i * 0x3c` to mirror the IDA expression
  (`60 * row_base + 60 * i`) is codegen-neutral at 93.44%. VC6 still emits the
  same commuted `lea eax, [edi+edx]`, so the compact `(slot_base + i) * 0x3c`
  source remains retained.
- 2026-06-20 continuation: splitting the shared index-buffer byte count into a
  local and applying `<<= 1` regressed to 92.62%; it produced a shift, but in
  `eax` rather than native `edx` and disturbed the tail region. Naming locals
  for the repeated capacity constants (`560`, `1280`, `160`) was codegen-neutral
  and left the same seed-register residual. Keep the current direct capacity
  stores and `index_buffer_count << 1` tail.
- 2026-06-20 seed-order pass: initializing the first two capacity pairs as
  vertex0/index0/vertex1/index1 recovers the native seed-register schedule
  (`ecx = 560`, `eax = 1280`) and removes the whole first mismatch region.
  The scratch improves from 93.44% to 97.54%, with prefix advancing from
  3/122 to 29/122 and all 18 masked operands still clean. This is plausible
  handwritten C++ even though both decompilers present the duplicate 560 stores
  together.
- Rejected tail/cursor probes in the seed-order pass: a direct
  `2 * *(max_index_count)` expression reached native `edx; shl` arithmetic but
  hoisted the load before the vertex-buffer store and dropped to 95.90%;
  `index_buffer_count *= 2` kept the store order but used `eax` and matched
  96.72%; unsigned count typing was neutral; spelling the cursor as
  `(i + slot_base) * 0x3c` was neutral. Keep the clearer signed count, shift
  expression, and `(slot_base + i)` cursor. Remaining residuals are the
  equivalent slot-index `lea` SIB order and the tail byte-count register/shift
  idiom.
- 2026-06-20 index-count owner pass: keeping the shared index-capacity lane as
  `int* index_buffer_count = (int*)((char*)vertex_buffers - 0x14)` and applying
  the shift through `(*index_buffer_count) << 1` recovers native's `edx; shl`
  byte-count setup without hoisting the load before the vertex-buffer store.
  Focused Wibo improves from 97.54% to 99.18%, with 122/122 instructions and
  all 18 masked operands still clean. A separate `slot_index = i; slot_index +=
  slot_base` spelling is codegen-neutral; the only remaining residual is the
  equivalent slot-index `lea` SIB order.
- 2026-06-21 slot-index SIB retry: broader source spellings for the remaining
  `lea` encoding all stayed at 99.18% with the same `[edx+edi]` versus
  `[edi+edx]` residual. Tested forms included
  `slot_index = slot_base; slot_index += i`, byte-offset locals, split scaled
  terms, volatile reads of either addend, and separate row-base pointers.
Volatile forms regressed by disturbing the prologue; non-volatile forms
compile back to the same SIB base/index choice.

2026-07-10 owner closure: three independent callers establish this manager as
the embedded `SubgameRuntime::segment_cache` at `+0x5c`. The exact
`0xa7f8` manager size ends at subgame `+0xa854`; `owner_subgame +0x54` is a
borrowed backlink, the `143 x 5` BOD grid is manager-owned, and the five shared
vertex/index buffers are tracked allocations owned for the manager lifetime.
The exact initializer remains 99.18%, 122/122, with 18 clean operands.

2026-07-11 renderer-pool closure: cache objects now allocate both retained D3D
wrappers through the one `Direct3DRenderer` owner. Vertex wrappers come from
the renderer prefix; index wrappers come from its `+0x8ca4` embedded factory.
The interior relocation is manifest-resolved through the renderer's proven
`0xbcc0` extent. The 99.18%, 122/122 stream and 18 clean operands are unchanged.

2026-07-11 cRSegmentCache ownership:

- The complete 0xa7f8-byte object at `SubgameRuntime +0x5c` is now named
  `SegmentCache`, matching the constructor's `Size of cRSegmentCache` ledger.
  Its owned 143x5 BOD grid, five vertex/index staging pairs, and borrowed
  enclosing-runtime backlink already account for the full extent. The rename
  is codegen-neutral at 99.18%, 122/122, with 18 clean operands.

## 2026-07-14 root backlink and grid extents

The enclosing-runtime backlink now comes from the canonical root owner as
`&g_game->subgame`; the old `char* g_game_base + 0x74618` expression described
the same address without its ownership. The initializer's family bound, total
slot bound, slot stride, cache-row stride, and shared-buffer count now derive
from `slots` and `shared_vertex_buffers` rather than repeating `5`, `0x2cb`,
`0x3c`, and `75`. Signed casts on the two loop bounds retain the native signed
`jl` comparisons that VC6 emitted for the original integer counters.

The manager-relative `TrackRenderCacheSlotCursor` remains intentional: a
direct pointer to `slots[0][0]` regressed focused matching from 99.18% to
87.70% by folding `+0x58` into the cursor. Native instead keeps the manager
base plus `slot_index * sizeof(TrackRenderCacheSlot)` and applies the field
offsets at each access. The accepted ownership cleanup is byte-identical at
99.18%, 122/122 instructions, prefix 29/122, with all 18 operands clean.

The cursor's inherited `BodBase::object` is now consumed as the canonical
`Object*` handle throughout allocation. The old per-access casts predated that
shared field type and falsely suggested a generic or overlaid payload; each
cache slot retains one ObjectList-owned render object for the manager lifetime.

## 2026-07-14 staging-lane ownership

The compiler-sensitive manager-relative slot cursor now derives its prefix
from `offsetof(SegmentCache, slots)`. Likewise, the shared allocation loop's
backward count lanes derive from `max_vertex_counts`, `max_index_counts`, and
`shared_vertex_buffers`, while the parallel index-buffer lane derives from the
shared-buffer array extent. This preserves native pointer induction without
repeating `+0x58`, `-0x28`, `-0x14`, or `[5]` as unexplained layout facts.

Focused output remains at the honest 99.18%, 122/122 baseline with all 18
operands clean; the sole residual is the equivalent slot-index SIB ordering.

## 2026-07-15 authored void contract

The only Windows call at `0x40ffd6` immediately overwrites the last allocation
pointer with unrelated world-initialization state. Removing the synthetic
return preserves the complete 122/122 instruction stream at 99.18%, with all
18 operands clean and only the equivalent slot-index SIB ordering remaining.
The Binary Ninja and IDA replay lanes now carry the real void initializer ABI.
