# update_row_model @ 0x443070

Recovered owner:

- `this` is the authored `RowModel` (`cRRowModel` on iOS), embedded at
  `SubRow +0x04` and ending exactly at the outer row's projection payload at
  `+0x90`.
- `transform.position` at `+0x68` is advanced by `Vector3 velocity` at `+0x80`.
  The exact source shape keeps `Vector3* position = &transform.position` for
  the three component stores, then reads `transform.position.z` for the cull
  compare; spelling the stores directly lets VC6 hoist `object` and keep the
  z result live on the x87 stack.
- `object->bounds_max.z` is compared against the embedded player's
  `interaction_max_z` row/world threshold.
- When the model has crossed the threshold, the function removes `this` from
  `GameRoot::active_bod_list` and pushes it onto the free list, using the same
  intrusive-list pattern as `update_active_bod` and
  `recycle_bod_to_free_list`.

Status:

- 2026-06-18: 100% match, 60/60 instructions, masked operands clean.
- 2026-07-11: promoted the local class into the shared `SubRow` layout. The
  constructor-installed table at `0x497330` points directly to this helper,
  independently proving the callback relationship. Matching remains exact at
  60/60 instructions with six clean masked operands.
- 2026-07-14: canonicalized the cull plane and active/free list through
  `GameRoot -> SubgameRuntime -> Player` ownership. Matching remains exact at
  60/60 with all six operands clean.

## 2026-07-18 live-analysis ownership replay

Both analysis databases now carry the exact void member ABI,
`update_row_model(RowModel*)`. The existing 0x8c-byte owner is sufficient to
recover all three velocity-to-position additions, the inherited
`Object::bounds_max.z` cull extent, the player's `interaction_max_z` plane,
and the full `GameRoot::active_bod_list` unlink/free-stack transition without
any local-variable override.

Binary Ninja can replay this slice with `--row-model-only`: it checks the
transitive `RowModel` header owner, its two proved fields, and the callback
prototype instead of walking the broad path catalog. IDA replays the same
prototype through the canonical path ownership sync. Cross-tool health guards
reject the former `arg1`/raw-offset and `int this` forms while requiring the
nested body, object, player, and active/free-list owners.
