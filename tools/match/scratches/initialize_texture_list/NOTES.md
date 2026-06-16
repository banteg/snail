# initialize_texture_list

Small texture-list initializer at 0x44e800. Clears the live entry count and
records the caller-provided capacity.

- `TextureRefList +0x00` is `count`, not a head pointer. This is cross-checked
  by `get_or_create_texture_ref`, which compares it against `capacity` and uses
  it as the slot index into the variable-capacity `TextureRef` backing store.
- `TextureRefList +0x04` is `capacity`.

Exact match: 100.00%, 4/4 instructions, no masked operands.
