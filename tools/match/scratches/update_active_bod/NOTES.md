# update_active_bod @ 0x433e80

Exact match: 100.00%, 50/50 instructions.

This helper is the default active-bod updater: once `world_z + 24.0f` falls
behind the embedded player's `interaction_max_z`, the node is removed from
`GameRoot::active_bod_list` and pushed onto its shared free stack.

The exact source shape uses the same typed intrusive-list logic as exact
`recycle_bod_to_free_list` and `refresh_fringe_object_draw_list`.

2026-06-20 ABI cleanup: the runtime record now lives in
`include/active_bod.h` with slot-0 `virtual void update_active_bod()`, list
flags/links at `+0x04/+0x08/+0x0c`, and inherited `world_z` at `+0x38`.
Focused matcher stayed exact at 50/50 instructions with 7 clean masked operands.

2026-07-14 owner closure: root `+0x4326fc` is
`subgame.player.interaction_max_z`, and root `+0x5a8` is the active/free BOD
list owner. Following both through the canonical `GameRoot` graph preserves
the exact 50/50 instructions and all seven operands.
