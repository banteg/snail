# Exact - TrackRowCell row index

This accessor pins `TrackRowCell +0x40` as the lane/flags dword. The low
three bits are the lane, and `mark_track_warning_zones` now cross-checks that
the same dword carries the `0x18` warning footprint bits.

Keep the scratch-local class for now. Including `track_attachment.h` makes
`g_game_base` volatile and changes register allocation in this exact function,
even though the recovered field layout is shared.
