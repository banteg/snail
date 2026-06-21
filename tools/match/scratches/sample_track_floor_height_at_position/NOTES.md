# sample_track_floor_height_at_position

Exact helper: returns the flat/ramp/slope/attachment floor height for the
runtime track cell under the supplied world position.

2026-06-21 subgame-header consolidation: this scratch now uses
`SubgameRuntime` for both the callee and the `get_track_grid_cell_at_world_position`
call surface. Focused Wibo remains exact at `100.00%`, `63/63` instructions,
with `8` clean masked operands.
