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

Focused Wibo result after correcting the flags width, raw name cursor, and
function end bound: 76.07%, 85/78 candidate/target instructions, with 4 masked
operands OK and no unresolved or mismatched operands. Remaining residual is
control-flow layout for the scan-found return block plus final `count`
increment/register scheduling.
