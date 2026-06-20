# replace_object_list_texture_refs

Object-list texture replacement helper at `0x430d90`.

- Walks the `ObjectList` storage (`count`, `capacity`, `objects`) and skips
  entries whose `Object +0x2c` vertex count is zero.
- Rewrites source facequad texture refs at `ObjectFaceQuad +0x0c`.
- Calls `replace_object_group_texture_refs` so already-built grouped render
  tables at `Object +0xd0` stay consistent with the source facequads.

This helper is currently only reached from `select_level_track_texture_set`,
which swaps both banks of level track texture refs.

## 2026-06-20 source-shape pass

Baseline was `51.85%`, `5/53` prefix, with one clean masked operand. Native
keeps a running byte cursor in `eax`, stores the current byte offset in the
second stack local, and only advances that local at the loop bottom. Rewriting
the scratch to use a separate `object_cursor` byte cursor plus
`object_offset = object_cursor` at the bottom raises the match to `69.16%` and
the prefix to `14/53`.

The typed-array walk `&objects[object_index]` regresses to `47.17%`, so this
helper still looks like original byte-cursor source even though
`add_object_to_list` proves the backing storage is an `Object[]`. A direct
`TextureRef**` slot pointer matches the native inner address form but swaps the
outer zero/count registers and drops to `61.68%`; keep the clearer
`ObjectFaceQuad*` spelling until a stronger object-address ownership lead
appears. A `register Object*` hint was codegen-neutral and is not retained.
