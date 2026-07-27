# initialize_texture_list

Small texture-list initializer at 0x44e800. Clears the live entry count and
records the caller-provided capacity.

- `TextureRefList +0x00` is `count`, not a head pointer. This is cross-checked
  by `get_or_create_texture_ref`, which compares it against `capacity` and uses
  it as the slot index into the variable-capacity `TextureRef` backing store.
- `TextureRefList +0x04` is `capacity`.

Exact match: 100.00%, 4/4 instructions, no masked operands.

## 2026-07-18 global registry ownership

The sole native caller passes `&g_texture_refs` and capacity 500, then ignores
`eax`. The resulting concrete owner is 0x14058 bytes: the count/capacity prefix
plus 500 inline 0xa4-byte `TextureRef` records. The source-level initializer is
therefore `void TextureRefList::initialize_texture_list(int)`, with the
apparent integer return only the incidental register used for the capacity
store. The void spelling remains exactly 4/4 instructions.

## 2026-07-27 dual-mobile authored owner

Android and iOS independently retain `cRTextures::Init(int)` in `RTexture.o`.
Both write the live count at owner `+0x00` and capacity at `+0x04`; the iOS
body is the exact same two stores as Windows. Android follows those stores by
initializing a hash index in a port-only tail, so that extra state must not be
projected onto the fixed 500-entry Windows owner. The matcher keeps its
descriptive name while `cRTextures_Init` records the recovered authored alias.
