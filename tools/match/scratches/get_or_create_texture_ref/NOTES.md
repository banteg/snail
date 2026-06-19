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

Focused Wibo result after preserving the new-entry pointer before incrementing
`count`: 82.21%, 85/78 candidate/target instructions, with 4 masked operands OK
and no unresolved or mismatched operands. The accepted source shape uses
`result = &entries[count]; ++count; return result;`, matching the native
allocation return more closely than the previous `result_index = count; count =
result_index + 1; return &entries[result_index];` spelling.

Rejected/no-op variants:

- Rewriting the reuse scan as the IDA-style `while (!match) ... goto allocate`
  structure compiled to the same candidate layout and score, so the structured
  `do` scan remains.
- Moving the found-existing return behind an explicit label did not move VC6's
  emitted found block; it still laid out before the allocation path.
