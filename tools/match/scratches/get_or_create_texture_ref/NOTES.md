# get_or_create_texture_ref

Initial scratch for the shared texture-reference list lookup/allocator.

Recovered relationships:

- `TextureRefList +0x00` is `count`; `+0x04` is `capacity`.
- `TextureRefList::entries` starts at `+0x08` and each `TextureRef` is
  `0xa4` bytes.
- `TextureRef::name` is the 0x80-byte path/name at `+0x0c`; the next field is
  `slot_index +0x8c`, not part of the name buffer.
- `flags & 0x800` disables case-insensitive path reuse; native tests this as
  `test ah, 0x8`, so the recovered argument is a full flags word rather than a
  source-level `short`.
- The reuse scan walks a raw `TextureRef::name` cursor by the 0xa4 entry stride
  and returns `&entries[i]`; it is not an entry-pointer loop.
- Newly allocated entries initialize `slot_index`, clear then seed `flags` with
  `0x400`, copy caller `arg3` into `texture_ref +0x98`, set `unknown_a0` to 1,
  then increment `count`.

This scratch exists primarily to correct and consolidate texture-list structure
evidence used by sprite texture registration and runtime sprite allocation.

Focused Wibo result after the structured scan-loop pass: 92.41%, 80/78
candidate/target instructions, with 4 masked operands OK and no unresolved or
mismatched operands. The accepted allocation source still uses
`result = &entries[count]; ++count; return result;`, matching the native
allocation return more closely than the previous `result_index = count; count =
result_index + 1; return &entries[result_index];` spelling.

Rejected/no-op variants:

- Rewriting the reuse scan as the IDA-style `while (!match) ... goto allocate`
  structure compiled to the same candidate layout and score, so the structured
  `do` scan remains.
- Moving the found-existing return behind an explicit label did not move VC6's
  emitted found block; it still laid out before the allocation path.
- 2026-06-21 resource-string family pass: retesting the stronger IDA-style
  allocation gate (`flags || count <= 0` followed by scan and `goto allocate`)
  was still exactly neutral at 82.21%. The retained structured scan is clearer,
  and the remaining residual is confirmed as found-block placement plus the
  allocation tail's count/index scheduling, not missing texture-list semantics.
- 2026-06-21 structured scan-loop pass: spelling the reuse scan as
  `while (i < count)` with a `found_existing` label after the allocation return
  moves VC6's found block after the allocator and improves focused Wibo from
  `82.21%`, `85/78` to `92.41%`, `80/78`. The direct `do` loop, `while
  (!match)` form, and boolean `found` flag either kept the old inline found
  return or regressed. The remaining residual is now only the scan-entry
  `count` test form (`cmp [esi], 0` versus `mov/test eax`) plus one duplicate
  return at the final epilogue.
- 2026-06-21 count-gate ordering pass: changing only the scan gate from
  `count > 0` to `0 < count` makes VC6 emit native's memory compare
  (`cmp dword [esi], 0`) instead of loading `count` into `eax` for a `test`.
  Focused Wibo improves from `92.41%` to `99.36%`, with the full `78/78`
  target instruction prefix matched and the same four clean masked operands.
  Nested-count, `!(count <= 0)`, `count != 0`, and shared-return spellings were
  neutral or regressive. The only remaining residual is the extra candidate
  `ret 0xc` after the target extent at the found-existing epilogue.
