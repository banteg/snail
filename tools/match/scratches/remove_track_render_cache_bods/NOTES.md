# remove_track_render_cache_bods @ 0x433f20

First typed scratch for clearing the track-render-cache BOD slots.

The helper walks `0x8f` cache rows with five `TrackRenderCacheSlot` entries per
row. The shared `segment_cache.h` layout keeps each slot as a
`BodBase`/`BodNode` overlay with stride `0x3c`, matching the
initializer/build-cache users that address the render object at the
`BodBase::object` lane (`slot + 0x24`).

Semantics: if a cached BOD is live (`list_flags & 0x200`), inline the standard
active-list unlink/free-stack push against the global BOD list at
`g_game_base + 0x5a8`, reporting the same `"List remove"` and
`"List remove NEXTBOD"` diagnostics used by the shared `BodList` remover.

Current match: 52.17%, 57/58 instructions, 7-instruction prefix, four masked
operands clean.

Important shape correction: native keeps `esi` as a cursor to
`BodNode::list_next` (`slot + 0x0c`), not to the slot/BOD base. The scratch uses
`next_ref = &slots[0][0].bod.list_next` to preserve that lane while still
documenting the owning slot as `TrackRenderCacheSlot { BodBase bod; ... }`.

Residuals:

- VC6 folds the `0x200` and `~0x200` flag masks into byte tests/updates
  (`test bh, 0x2`, `and ah, 0xfd`), while native keeps `0x200` in `ebx` and
  `0xfffffdff` in `ebp` for dword `test`/`and` operations.
- Because native keeps those mask registers live, `edi` remains the inner
  five-slot counter and the global list pointer stays in `ecx`; the scratch
  allocates those registers differently.
- The native function is side-effect-only. The old `int` prototype was a
  decompiler artifact from the row-count loop; the sole known caller
  (`remove_subgame_bods`) discards the value, and the native epilogue does not
  materialize a return register. Changing the member and BN/IDA prototypes to
  `void` removes the scratch's trailing `xor eax, eax`.

Rejected probe:

- Walking a `TrackRenderCacheSlot*` directly produced the right semantics but
  started from `slot + 0x00` (`lea esi, [ecx+0x58]`) instead of native's
  `slot + 0x0c` cursor (`lea esi, [ecx+0x64]`) and matched only 43.48%.

2026-06-20 byte-base audit: unlike the damage-gauge byte-base scratch, this
helper benefits from spelling `g_game_base` as a normal external. Focused Wibo
improves from 52.17% to 54.39%, with 56/58 candidate/target instructions and
5 clean masked operands. The change removes one stale volatile reload around
the global BOD-list anchor; the remaining dominant residual is still the native
full-dword mask lifetime (`ebx = 0x200`, `ebp = ~0x200`) versus VC6 folding the
tests/clear into `bh`/`ah`. Signed flag types and explicit assignment for the
final clear were tested and were codegen-neutral, so they are not retained.

2026-06-21 live-bit gate pass: focused Wibo improves to 56.41%, with 59/58
candidate/target instructions and 4 clean masked operands, by spelling the
single-bit live test as `(*flags_ref & live_mask) == live_mask` and making the
masks unsigned. This is equivalent for the `0x200` live bit and avoids the
signed/unsigned warning produced by the first equality probe. Register hints,
computed mask initializers, count-loop rewrites, and unsigned not-zero casts
 were neutral. Hoisting `flags = *flags_ref` before the live test scored higher
numerically but removed the native redundant `"List remove"` diagnostic path
and produced a masked string mismatch, so it is rejected.

2026-07-10 owner closure: the manager is now embedded at
`SubgameRuntime +0x5c`, and each of its `143 x 5` slots owns a full `BodBase`
node plus `cache_row_base`. Binary Ninja now decompiles this loop through
`slots[row][family].bod.bod.{list_flags,list_prev,list_next}` instead of false
slot-local render/vertex fields. The focused score remains 56.41%, 59/58,
prefix 7/58, with all four operands clean; the retained residual is still
register lifetime around the two full-dword masks.

2026-07-11 cRSegmentCache ownership: the exact 0xa7f8 receiver is now the
authored `SegmentCache` rather than a provisional manager wrapper. Focused
matching stays honestly partial at 56.41%, 59/58 instructions, prefix 7/58,
with four clean operands.

## 2026-07-12 active-list owner boundary

The cache grid owns its 143 x 5 embedded `BodBase` records, but it does not own
their active/free linkage. For every live slot this helper borrows the global
`BodList` and invokes its shared inline `remove_bod` operation on the containing
node. That operation unlinks the node and returns it to the list's free stack;
it does not destroy the cache slot or its retained render object.

Using the shared owner method also fixes a semantic error in the previous
hand-expanded scratch. A failed `0x200` ownership check reports `"List remove"`
and leaves the inline removal path immediately; it must not fall through into
the `0x40` iteration check or unlink body. This source shape raises focused
Wibo from 56.41% (59/58) to **70.59%** (61/58), with five clean masked operands.

The remaining residual is honest VC6 loop allocation: candidate keeps a row-end
cursor alongside the active `list_next` cursor and folds `~0x200` into a byte
clear, while native keeps the continuous cursor plus `0x200`/`~0x200` in full
registers. Manual mask locals, flat-loop rewrites, and a second hand expansion
either regress or lose the shared early-exit contract, so none are retained.
