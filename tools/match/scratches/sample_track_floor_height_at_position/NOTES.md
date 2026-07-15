# sample_track_floor_height_at_position

Exact helper: returns the flat/ramp/slope/attachment floor height for the
runtime track cell under the supplied world position.

2026-06-21 subgame-header consolidation: this scratch now uses
`SubgameRuntime` for both the callee and the `get_track_grid_cell_at_world_position`
call surface. Focused Wibo remains exact at `100.00%`, `63/63` instructions,
with `8` clean masked operands.

## 2026-07-14 analysis receiver closure

The live BN prototype now matches that exact source evidence as
`double __thiscall(SubgameRuntime*, Vec3*)` rather than the stale `Game*`
identity. Refreshed BN and IDA output agree on the typed grid lookup,
`TrackRowCell::tile_id`, and the stored `anchor_position.y` special case. The
63/63 matcher remains byte-identical.
