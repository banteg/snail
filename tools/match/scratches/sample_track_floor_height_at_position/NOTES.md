# sample_track_floor_height_at_position

## 2026-07-26 authored GetY method

Android `cRSubGame::GetY(tVector)` calls `LocFromPos` and preserves the same
flat/ramp/raised-ramp/stored-height ladder with exact `0.4`, `0.5`, and
`-100.0` constants. iOS independently exports the exact demangled method name.
Together they pin this Windows floor sampler as authored `GetY` without
assuming identical port layouts.

Exact helper: returns the flat/ramp/slope/attachment floor height for the
runtime track cell under the supplied world position.

2026-06-21 subgame-header consolidation: this scratch now uses
`cRSubGame` for both the callee and the `get_track_grid_cell_at_world_position`
call surface. Focused Wibo remains exact at `100.00%`, `63/63` instructions,
with `8` clean masked operands.

## 2026-07-14 analysis receiver closure

The live BN prototype now matches that exact source evidence as
`double __thiscall(cRSubGame*, Vec3*)` rather than the stale `Game*`
identity. Refreshed BN and IDA output agree on the typed grid lookup,
`cRSubLoc::tile_id`, and the stored `anchor_position.y` special case. The
63/63 matcher remains byte-identical.

## 2026-07-19 tile identity vocabulary

The exact source now spells the flat, ramp, raised-ramp, backpatch, Wall2, and
trampoline cases through `SubLocTileIdValue`. These are compile-time names over
the same byte values; the helper remains exact at 63/63 with eight clean
operands.
