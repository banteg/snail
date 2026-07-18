# `sort_object_faces_by_texture_group` recovery notes

Target: `sort_object_faces_by_texture_group @ 0x419fd0` (`cdecl`).

This scratch recovers the source-level grouping pass used before
`calc_object_texture_groups`: for each base face, later faces with the same
`ObjectFaceQuad::texture_ref` are pulled forward by swapping with the current
insert slot. The native loop advances the base index whenever a matching face
is absorbed into the current group, which is why the decompiler shows `ebp`
increments inside the inner loop as well as at the outer loop tail.

`ObjectFaceQuad` assignment compiles to the expected three 12-dword
`rep movsd` block copies.

2026-07-10 cursor ownership closure:

- The scan cursor begins at `facequads[scan_index]`, while the insertion cursor
  independently begins at `facequads[base_index + 1]`. Although both indices
  have the same initial value, they have different owners and advance under
  different conditions once matching faces are absorbed.
- Modeling both cursors from `scan_index` let VC6 collapse one address
  calculation and assigned the object/base/scan registers incorrectly, leaving
  the old scratch at 41.61% with 74/75 instructions.
- Preserving the distinct insertion anchor reproduces the native object in
  `esi`, base index in `ebp`, scan index in `ebx`, both 0x30-byte cursor walks,
  and the exact swap frame. Focused Wibo is now 100.00%, 75/75 instructions,
  prefix 75/75, with no masked operands.

Rejected probes retained from the earlier allocator audit: C mode, `register`
hints, return-type changes, and guard/compare rewrites did not recover the
missing relationship. No padding or dead work is present in the exact source.

## 2026-07-18 Object-owner ABI replay

The sole callsite in `build_all_objects` passes one object and discards `eax`;
the exact scratch likewise has a natural `void (Object*)` source signature.
The integer return shown by both raw decompilers was only the final
`facequad_count` load. The shared headers and repeatable Binary Ninja/IDA
syncs now preserve the borrowed `Object*` owner and `void` ABI. Matcher source
is unchanged at 100.00%, 75/75 instructions, with no masked operands.
