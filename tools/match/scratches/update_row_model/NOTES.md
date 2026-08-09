# update_row_model @ 0x443070

Recovered owner:

- `this` is primary authored `cRRowModel`, embedded at `cRSubRow +0x04` and
  ending exactly at the outer row's projection payload at
  `+0x90`.
- `transform.position` at `+0x68` is advanced by `Vector3 velocity` at `+0x80`.
  The exact source shape keeps `Vector3* position = &transform.position` for
  the three component stores, then reads `transform.position.z` for the cull
  compare; spelling the stores directly lets VC6 hoist `object` and keep the
  z result live on the x87 stack.
- `object->bounds_max.z` is compared against the embedded player's
  `active_window_min_z` row/world threshold.
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
  `GameRoot -> cRSubGame -> Player` ownership. Matching remains exact at
  60/60 with all six operands clean.
- 2026-08-09: promoted the primary matcher receiver to `cRRowModel::AI()`;
  `RowModel` remains a compatibility typedef. The stable
  `FUNCTION=update_row_model` target remains exact at 60/60 with all six
  operands clean, and the authored VC6 symbol is
  `?AI@cRRowModel@@QAEXXZ`.

Android `_ZN10cRRowModel2AIEv @ 0x6d6c8` and iOS
`_ZN10cRRowModel2AIEv @ 0x3044c` independently preserve the exact owner and
member. Both add three velocity components to the inherited position and
remove the body after the live-row cull threshold. Their compact owner offsets
differ from Windows, so they establish provenance and behavior, not offsets to
transplant into the Windows layout.

## 2026-07-18 live-analysis ownership replay

Both analysis databases carry the exact void member ABI through stable
`RowModel*` analyzer vocabulary. The existing `0x8c`-byte owner is sufficient to
recover all three velocity-to-position additions, the inherited
`Object::bounds_max.z` cull extent, the player's `active_window_min_z` plane,
and the full `GameRoot::active_bod_list` unlink/free-stack transition without
any local-variable override.

Binary Ninja can replay this slice with `--row-model-only`: it checks the
transitive `cRRowModel` header owner, its two proved fields, and the callback
prototype instead of walking the broad path catalog. IDA replays the same
prototype through the canonical path ownership sync. Cross-tool health guards
reject the former `arg1`/raw-offset and `int this` forms while requiring the
nested body, object, player, and active/free-list owners. Do not reopen field
expansion, list-rewrite, or mobile-offset lanes as part of this owner-only
promotion.
