# Exact match

`initialize_path_follow_golb` constructs the 0x28-byte path-follow state
embedded at `GolbShot::path_follow`. The state borrows its path template from
the source runtime cell, retains that `TrackRowCell*` for later sampling, and
keeps a backlink to the owning shot. Initial progress is the shot position's
Z displacement from the cell anchor; the vertical offset is relative to the
native `0.49f` path baseline.

Focused output is exact at 100.00%, 16/16 instructions, full prefix, and one
clean operand.

## 2026-07-18 attachment owner replay

The focused Golb replay now explicitly owns both path-follow symbols as well
as the `GolbPathFollowState`, `TrackRowCell`, `Path`, and `GolbShot` boundaries.
This keeps the borrowed attachment links distinct from the embedded state and
gives `calc_path_length_z` and the harder Golb AI a stable owner graph.
