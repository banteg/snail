# get_track_runtime_cell_at_world_z @ 0x43d480

Exact helper: clamps world z to runtime row `0..3199` and returns the
`TrackAttachmentRuntimeRow` at `game + 0x5ccac8` with stride `0xf4`.

2026-06-16 type pass: return type is now the shared
`TrackAttachmentRuntimeRow*` from `track_attachment_types.h` instead of
`void*`. Focused match remains exact at `23/23`.
