# update_sprite

Exact sprite runtime update at `0x44df30`.

This function ties together the allocator and producer-side `Sprite` layouts:
it respects the global pause byte for `0x800` sprites, consumes the one-frame
skip bit `0x8`, advances progress/lifetime timers, integrates position and
velocity, applies gravity/local-yaw steps, and advances the texture frame state
seeded by `allocate_sprite`.

Recovered sprite relationships:

- `Sprite +0x3c` stores the previous world position copied from `+0x48`.
- `Sprite +0x48/+0x54` are current world position and velocity.
- `Sprite +0x68/+0x6c` are normalized progress and progress step; when progress
  exits `[0, 1]`, the sprite is killed unless flag `0x100` is set.
- `Sprite +0x70/+0x74` are a lifetime accumulator and step; positive lifetime
  step sets flag `0x200`, otherwise it clears that flag.
- `Sprite +0x78` is gravity applied to velocity Y, and `+0x7c/+0x80` are the
  facing angle and per-frame angle step.
- `Sprite +0x9c/+0xa0/+0xa4/+0xa8/+0xac/+0xb0` are the primary texture id,
  frame count, current frame, frame step, frame accumulator, and frame rate.
  Flag `0x2000` enables frame animation; flag `0x4000` makes the frame step
  bounce at either end instead of wrapping to zero.

Exact match: 100.00%, 125/125 instructions, with ten masked operands audited.
