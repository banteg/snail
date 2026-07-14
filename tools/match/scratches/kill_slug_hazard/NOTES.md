# Matched

`kill_slug_hazard` matches exactly. It only acts when `state == 1`, plays the
death voice `play_slug_voice(28 - variant)`, switches the slug to explosion
state `2`, records the toss side from `world_x`, awards slug score kind `1`,
and calls `explode_slug_hazard`.

The branch order matters for the final compare: spelling the toss selector as
`if (world_x > 0.0f) direction = 1; else direction = 2;` produces the native
`jne` layout. The voice variant uses the same float-scale RNG idiom as the
other slug voice helpers.

2026-06-21 owner cleanup: the score award began treating the opaque slug owner
as the subgame base and reached the shared player at `owner_game+0x3bb764`,
removing the scratch-local `Game` shell. Focused Wibo remained exact at
`100.00%`, `35/35`, with `7` clean masked operands.

2026-07-11 ownership: the exact body now lives on the primary `Slug` type,
matching Android and iOS `cRSlug::Kill()`. Its call to the now-void explosion
member remains byte-identical, confirming that the incidental EAX value was
never part of the caller contract.

2026-07-13 player-owner closure: the score award now reaches
`owner_game->player` directly. This retires the final fixed-offset Player cast
from the exact slug kill path and makes the lifetime explicit: each inline
`Slug` borrows its enclosing `SubgameRuntime`, which owns the scoring Player.
Focused Wibo remains exact at 35/35 with all seven masked operands clean.

## 2026-07-14 lifecycle roles

Windows and Android agree on the transition from active state one to
death-toss-pending state two and on direction one/two selecting the positive-x
right side or non-positive-x left side. Those roles now come from shared enums
rather than isolated literals. The exact 35-instruction body and all seven
masked operands remain byte-identical.
