# merge_track_tile_runs

`SubgameRuntime::merge_track_tile_runs` makes a second pass over the populated
runtime track cells. It seeds every cell with the `0x6000` merge-candidate bits,
then scans each row's eight lanes for horizontal slide, floor, and worm-tunnel
runs. Multi-cell runs replace the first cell's object with a wider mesh and
clear render/contact bits on the continuation cells.

The first scratch is intentionally high-level and uses shared `TrackRowCell` and
`TrackAttachmentRuntimeRow` views. The native has heavy cross-jumped control
flow and register reuse across the three run families, so the first retained
version prioritizes the real data model over layout forcing.

Important flag distinction: the first cell's start gate checks low bit `0x40`,
but continuation cells use merge bit `0x4000`. Keeping those separate is required
for the run counts to match the native behavior after the initial `0x6000` seed
pass.

The tempting rewrite around raw `lane_and_flags` pointers regressed the match
and introduced a masked operand mismatch for the row-record base, so the retained
source keeps the typed `TrackRowCell*` walk.
