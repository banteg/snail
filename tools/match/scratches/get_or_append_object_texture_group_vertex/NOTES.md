# get_or_append_object_texture_group_vertex

Relationship-first scratch for the private grouped-vertex append helper at
`0x413bb0`.

Current Wibo result: 45.85%, 126/127 candidate/target instruction shape,
prefix 16/127, masked operands 8 ok, 0 unresolved, 0 mismatch.

Recovered relationships:

- Called only by `build_object_texture_group_buffers`.
- Reads `Object +0x2c` vertex count, `+0x38` vertices, `+0x48` vertex colours,
  and `+0x10` flags.
- `g_object_grouped_vertex_cursor` (`data_5031bc`) is the append cursor and
  return index for the 0x1c-byte temporary grouped-vertex stream.
- `g_object_grouped_vertex_scratch` (`data_5031c4`) points at temporary records:
  position `+0x00..+0x08`, packed diffuse `+0x0c`, UV `+0x10/+0x14`, and source
  vertex index `+0x18`.
- Source V is stored flipped as `1.0f - v`.
- `flags & 0x10000` enables per-vertex colour packing from `Object +0x48`;
  otherwise diffuse is `0xffffffff`.

Corrected assumptions:

- The de-duplication key is flag-dependent. With `flags & 4`, native matches
  on source vertex index plus UV only; without that flag, it matches on full
  position plus UV.

Expected residuals:

- Native keeps the three source-position components in a 0x0c stack local and
  uses a `scratch + 4` cursor in the de-dup loops. The scratch now has the same
  relationship map and clean masks, but VC6 still hoists the scratch pointer
  and emits different loop branch layout around the two compare modes.
