# update_active_bod @ 0x433e80

Exact match: 100.00%, 50/50 instructions.

This helper is the default active-bod updater: once `world_z + 24.0f` falls
behind the live subgame cull threshold at `g_game_base + 0x4326fc`, the node is
removed from the shared active BOD list and pushed onto the shared free stack at
`g_game_base + 0x5a8`.

The exact source shape uses the same typed intrusive-list logic as exact
`recycle_bod_to_free_list` and `refresh_fringe_object_draw_list`.
