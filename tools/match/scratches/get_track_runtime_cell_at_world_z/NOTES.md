# get_track_runtime_cell_at_world_z @ 0x43d480

Exact helper: clamps world z to runtime row `0..3199` and returns the
`TrackAttachmentRuntimeRow` at `game + 0x5ccac8` with stride `0xf4`.

2026-06-16 type pass: return type is now the shared
`TrackAttachmentRuntimeRow*` from `track_attachment_types.h` instead of
`void*`. Focused match remains exact at `23/23`.

2026-06-16 layout assertion pass: the shared `TrackAttachmentRuntimeRow` now
asserts `sizeof(TrackAttachmentRuntimeRow) == 0xf4`. This exact accessor pins
the row-table stride, and builder/projection/parcel/subgoldy consumers agree
on the same runtime row shape.

2026-06-18 analysis/BN sync: `TrackAttachmentRuntimeRow +0xb0` is now named as a
`BodBase aux_body` in the analysis headers and BN sync script. The
`initialize_track_row_runtime` scratch proves that tail by calling
`initialize_bod_base()` at `this + 0xb0`; the matcher include keeps the same
bytes flattened for now because no scratch consumes the tail through the row
record yet.

2026-06-21 subgame-header consolidation: the accessor is now declared on
`SubgameRuntime` and returns the shared `TrackAttachmentRuntimeRow*` directly.
Focused Wibo remains exact at `100.00%`, `23/23` instructions, with `3` clean
masked operands.
