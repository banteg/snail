# update_row_model @ 0x443070

Initial shape:

- `this` is a `RenderableBod`-derived row model.
- `transform.position` at `+0x68` is advanced by `Vector3 velocity` at `+0x80`.
  The exact source shape keeps `Vector3* position = &transform.position` for
  the three component stores, then reads `transform.position.z` for the cull
  compare; spelling the stores directly lets VC6 hoist `object` and keep the
  z result live on the x87 stack.
- `object->bounds_max.z` is compared against the row/world z threshold at `g_game_base + 0x4326fc`.
- When the model has crossed the threshold, the function removes `this` from the active BOD list at `g_game_base + 0x5a8` and pushes it onto the free list, using the same intrusive-list pattern as `update_active_bod` and `recycle_bod_to_free_list`.

Status:

- 2026-06-18: 100% match, 60/60 instructions, masked operands clean.
