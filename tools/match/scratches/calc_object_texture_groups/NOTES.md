# calc_object_texture_groups @ 0x4303f0

First relationship-first scratch for the object texture-group pass.

Semantics pinned:

- runs two passes over `Object +0x5c` facequad records;
- pass 0 counts texture-group breaks, then calls `request_object_texture_groups`
  with `group_count + 1`;
- pass 1 writes cumulative facequad end indices to `Object +0x6c`;
- `Object +0x54` is facequad count and `Object +0x64/+0x68/+0x6c` are the
  texture-group live count, capacity, and end-index array owned by
  `request_object_texture_groups`;
- facequad `+0x0c` is the texture ref, facequad flag `0x10` forces a group
  split, and object flag `0x400` sets facequad flag `0x02` plus texture flag
  `0x20` on every visited facequad.

This is the missing producer for the cumulative `+0x6c` ends consumed by
`build_object_texture_group_buffers`; do not promote a full `Object` layout
from this alone.
