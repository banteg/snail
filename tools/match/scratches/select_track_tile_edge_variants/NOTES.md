# select_track_tile_edge_variants

- Walks the row-major `SubLoc +0x3c` tile-byte view.
- Clears `open_edge_mask`, clears `SUBLOC_FLAG_CORNER_OBJECT`, builds open-edge
  bits from left/right/back/front neighbors, and for edge masks `5`, `6`, `9`,
  and `10` swaps the current cell's BOD object to the matching edge variant.
- The straight-track family branch covers tile ids `1`, `0x14`, `0x15`,
  `0x1b`, `0x21`, and `0x22`; non-ramp non-excluded cells use the alternate
  variant banks.
- 2026-06-20 larger-chunk proof: exact at 100.00%, 220/220 instructions,
  prefix 220/220, with 18 clean masked operands and no unresolved operands.
  The key source shape is keeping byte/dword pointers for the tile flag byte
  and `lane_and_flags` word inside the row-cell tile-byte cursor. That pointer
  view matches the decompiler's byte-pointer walk and stops VC6 from hoisting
  the independent tile-id loads across the flag stores without using volatile
  or artificial dependencies.
- 2026-07-11 predicate-owner pass: the neighbor and ramp calls now resolve
  through the shared `SubLoc` methods proven against Android
  `cRSubLoc::IsEmpty()` and `cRSubLoc::IsRamp()`. The field-first cursor is
  retained for native source shape; the enclosing cell casts express the real
  owner. The function remains exact at 220/220 with all 18 operands clean.
- 2026-07-13 catalog-owner pass: the three four-entry corner banks now resolve
  through `GameRoot::root_bod_catalog`. The explicit authored-id-to-storage
  mapping preserves the physical `0, 1, 3, 2` bank order and keeps the function
  exact at 220/220 with all 18 operands clean.

## 2026-07-14 exact canonical-owner proof

The field-first cursor now comes from
`SubgameRuntime::runtime_cell_tile_views()`, its lane bound derives from the
owned runtime-cell row, and every floor/slide corner selection loads through
the canonical `GameRoot* g_game` plus `root_bod_catalog`. The compiler retains
the intentional field-relative neighbor offsets and authored corner storage
mapping. Focused output remains fully exact at 220/220 instructions with all
18 operands clean.

## 2026-07-14 neighborhood-delta ownership

Binary Ninja's live `TrackRowCell` layout agrees with the shared `SubLoc`:
size `0x54`, `tile_id +0x3c`, `open_edge_mask +0x3d`, and
`lane_and_flags +0x40`. The exact field-first cursor deltas now derive from
`sizeof(SubLoc)`, `sizeof(runtime_cells[0])`, and `offsetof(SubLoc, tile_id)`:
the former `-0x90/+0x18` pair selects adjacent lanes,
`-0x2dc/+0x264` selects adjacent rows, and `-0x3c` recovers the containing
cell/BOD. This removes parallel layout constants while preserving the native
pointer shape, exact 220/220 output, and all 18 clean operands.

## 2026-07-14 open-edge and packed-flag ownership

The exact producer closes `+0x3d` as a four-bit cardinal open-edge mask:
previous/next lane are `0x08/0x04`, and previous/next row are `0x01/0x02`.
`build_track_fringe_objects` consumes the same four corner combinations, while
`update_subgoldy` consumes the row bits as its safe attachment-entry window.
The field is therefore named `open_edge_mask`; the old `tile_flags_3d` label
was needlessly opaque.

The adjacent dword remains one packed owner rather than a C++ bitfield.
This producer proves `SUBLOC_FLAG_CORNER_OBJECT` (`0x8000`), and the broader
producer/consumer pass records the independently owned lane, hazard, cache,
merged-run, AI, and uncached-body masks in `SubLocFlag`.
