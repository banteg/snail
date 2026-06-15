# allocate_sprite

Exact sprite-manager allocator at `0x44e2a0`.

This function consumes the manager free list at `+0x83d78`, links the sprite
into the owner active-head bucket at `+0x83d64 + owner * 4`, reinitializes the
sprite, selects the primary texture record at sprite `+0x1c`, and records the
primary texture id at sprite `+0x9c`.

Recovered sprite relationships:

- `Sprite +0x08` is the owner bucket index.
- `Sprite +0x0c/+0x10` are next/prev links shared by the free list and active
  owner lists.
- `Sprite +0x1c/+0x20/+0x24` are primary/secondary texture-record pointers.
- `Sprite +0x9c` stores the primary texture id used for metadata lookups.
- Texture-record flags at `0x2000/0x4000` propagate into sprite flags, and
  texture metadata at `+0x90/+0x94` populates sprite `+0xa0/+0xb0`.

Exact match: 100.00%, 81/81 instructions, with ten masked operands audited.
