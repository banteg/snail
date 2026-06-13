# Matched

`kill_slug_hazard` matches exactly. It only acts when `state == 1`, plays the
death voice `play_slug_voice(28 - variant)`, switches the slug to explosion
state `2`, records the toss side from `world_x`, awards slug score kind `1`,
and calls `explode_slug_hazard`.

The branch order matters for the final compare: spelling the toss selector as
`if (world_x > 0.0f) direction = 1; else direction = 2;` produces the native
`jne` layout. The voice variant uses the same float-scale RNG idiom as the
other slug voice helpers.
