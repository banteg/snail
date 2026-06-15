# kill_game_sprites

Exact sprite-manager cleanup traversal at `0x44e3d0`.

The function walks the five active owner buckets from `g_sprite_active_heads`
up to the adjacent `g_sprite_free_head` global. The native loop uses a signed
address comparison against `g_sprite_free_head`, not an array-end expression,
which is why the scratch casts the bucket pointer to `int` for the loop guard.

Recovered relationship: sprite flag `0x800` marks entries that are removed by
the gameplay bulk cleanup path. The next pointer is saved before calling
`kill_sprite`, so the traversal remains valid while the current node is moved
back onto the free list.

Exact match: 100.00%, 23/23 instructions, with three masked operands audited.
