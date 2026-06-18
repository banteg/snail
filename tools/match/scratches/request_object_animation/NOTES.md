# request_object_animation @ 0x430a70

First relationship-first scratch for X-mesh object animation ownership.

Semantics pinned:

- caller-provided keyframe records are 0x80 bytes, with object pointer at
  `+0x24` and authored frame number at `+0x7c`;
- every keyframe object's `+0x2c` vertex count must match the target object;
- the target object raises flag `0x200000` and stores an `ObjectAnimation*` at
  `+0xbc`;
- `ObjectAnimation` is 0x14 bytes: flags at `+0x00`, generated frame count
  at `+0x04`, frame pointer array at `+0x08`, playback/progress at `+0x0c`,
  and progress step at `+0x10`;
- each generated `ObjectAnimationFrame` is 8 bytes: vertices at `+0x00` and
  facequad normals at `+0x04`;
- generated frames allocate `vertex_count * 0x0c` vertex arrays and
  `facequad_count * 0x18` facequad-normal arrays, then temporarily install
  them on `Object +0x38/+0x60` before recalculating facequad normals.

This corrects the earlier render-only naming: `ObjectAnimation +0x04` is the
generated frame count, while `+0x0c` is the playback/progress value used by
`refresh_object_vertex_buffer` to select a generated frame.

2026-06-18 object header sync: `request_object_animation` and
`refresh_object_vertex_buffer` both prove `Object +0xbc` is the
`ObjectAnimation*` owner pointer. The generated facequad-normal frame slot is a
`Vector3*` buffer containing two normals per facequad, matching
`calc_object_facequad_normals_simple`. The shared `Object` layout now names
`+0xbc` as `animation` and declares `request_object_animation`; the scratch uses
that shared declaration while keeping the relationship-first loop body for match
shape. Focused Wibo remains `41.24%`, `220/231`, with `13 ok`, `1 unresolved`,
and `1 mismatch` masked operands.
