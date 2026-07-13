# merge_track_tile_runs

`SubgameRuntime::merge_track_tile_runs` makes a second pass over the populated
runtime track cells. It seeds every cell with the `0x6000` merge-candidate bits,
then scans each row's eight lanes for horizontal slide, floor, and worm-tunnel
runs. Multi-cell runs replace the first cell's object with a wider mesh and
clear render/contact bits on the continuation cells.

The retained scratch uses the shared `TrackRowCell` and
`TrackAttachmentRuntimeRow` owners, but follows the field-first cursors carried
by the native. Both passes walk `TrackRowCell::lane_and_flags` at a `0x54`-byte
stride. The second pass derives the owning cell at `-0x40`, while its row cursor
starts at `SubRow::attachment_body.list_flags` and advances by the full `0xf4`
row stride.

That row cursor corrected a real ownership bug in the first draft. At
`0x435381`, the native tests `SubRow::flags` at cursor `-0xb4`, clears the
current cell's embedded `BodNode::list_flags`, then clears the row's embedded
`attachment_body.list_flags`. It does not touch `row_model.list_flags`.

Important flag distinction: the first cell's start gate checks low bit `0x40`,
but continuation cells use merge bit `0x4000`. Keeping those separate is required
for the run counts to match the native behavior after the initial `0x6000` seed
pass.

Continuation cleanup is owned by `SubgameRuntime::runtime_cells[row][lane]`, not
by an independently advancing borrowed cell pointer. Recomputing the indexed
field cursor matches the native row/lane address arithmetic and prevents a run
cursor from escaping its eight-cell row.

The `0x0e` wall-run path has another non-obvious ownership detail. Its tile
cursor advances across cells, but the `0x4000` test and `0x0e00`/`0x0100`
updates remain on the first cell's `lane_and_flags`. Advancing a full cell
owner for those flag accesses changes behavior and is not equivalent.

Source-shape progression:

- indexed continuation ownership plus the corrected row actor raised the fuzzy
  match from 21.78% to 32.09%;
- delaying the tile read until both floor/slide helper checks fail recovered the
  native branch shape and raised it to 45.41%;
- the two field-first cursors and fixed wall-run flag owner bring the retained
  version to 54.77% (276 target instructions, 290 candidate instructions, ten
  clean masked operands);
- a `SubgameRuntime* game = this` alias was byte-neutral, and alternate outer
  cell scopes regressed the score, so neither is retained.

The remaining gap is mostly the compiler preserving a parallel cell-base
induction variable and scheduling the three continuation-cleanup stores
differently. No dummy locals, volatile qualifiers, or equivalent-instruction
normalization are used to force those differences.
