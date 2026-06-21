# Matched

`kill_slug_hazard` matches exactly. It only acts when `state == 1`, plays the
death voice `play_slug_voice(28 - variant)`, switches the slug to explosion
state `2`, records the toss side from `world_x`, awards slug score kind `1`,
and calls `explode_slug_hazard`.

The branch order matters for the final compare: spelling the toss selector as
`if (world_x > 0.0f) direction = 1; else direction = 2;` produces the native
`jne` layout. The voice variant uses the same float-scale RNG idiom as the
other slug voice helpers.

2026-06-21 owner cleanup: the score award now treats the opaque slug owner as
the subgame base and reaches the shared player at `owner_game+0x3bb764`,
removing the scratch-local `Game` shell. Focused Wibo remains exact at
`100.00%`, `35/35`, with `7` clean masked operands.
