# kill_game_sprites

Exact sprite-manager cleanup traversal at `0x44e3d0`.

The function walks the five active owner buckets from `g_sprite_active_heads`
up to the adjacent `g_sprite_free_head` global. The native loop uses a signed
address comparison against `g_sprite_free_head`, not an array-end expression,
which is why the scratch casts the bucket pointer to `int` for the loop guard.

Recovered relationship: `SPRITE_FLAG_GAMEPLAY_OWNED` marks entries that are
removed by the gameplay bulk cleanup path and whose updates honor the global
gameplay pause byte. The next pointer is saved before calling `kill_sprite`, so
the traversal remains valid while the current node is moved back onto the free
list.

Exact match: 100.00%, 23/23 instructions, with three masked operands audited.

## 2026-07-16 producer-side policy ownership

The exact cleanup consumer and exact paused-update consumer jointly define
`SPRITE_FLAG_GAMEPLAY_OWNED`; the flag is not an emitter-specific magic bit.
All recovered producers now use the shared policy name: jet and ring particle
pools, both SubGoldy ghosts, Golb impact/smoke/trail sprites, slug sprites, ring
star showers, and the track health/jetpack pickups. The substitutions are
byte-identical and make each allocation's pause/bulk-cleanup lifetime explicit.
