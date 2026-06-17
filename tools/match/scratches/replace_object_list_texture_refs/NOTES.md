# replace_object_list_texture_refs

Object-list texture replacement helper at `0x430d90`.

- Walks the `ObjectList` storage (`count`, `capacity`, `objects`) and skips
  entries whose `Object +0x2c` vertex count is zero.
- Rewrites source facequad texture refs at `ObjectFaceQuad +0x0c`.
- Calls `replace_object_group_texture_refs` so already-built grouped render
  tables at `Object +0xd0` stay consistent with the source facequads.

This helper is currently only reached from `select_level_track_texture_set`,
which swaps both banks of level track texture refs.
