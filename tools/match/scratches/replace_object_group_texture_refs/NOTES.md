# replace_object_group_texture_refs

Small grouped-render helper at `0x4145c0`. When an object already owns grouped
render buffers (`flags & 0x80000`), it scans `Object +0xd0` and replaces any
group texture entry matching the old `TextureRef`.

This is only called by `replace_object_list_texture_refs`, after that caller has
also rewritten the source facequad texture refs.
