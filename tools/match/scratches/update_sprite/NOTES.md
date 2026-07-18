# update_sprite

Exact sprite runtime update at `0x44df30`.

This function ties together the allocator and producer-side `Sprite` layouts:
it respects the global pause byte for `SPRITE_FLAG_GAMEPLAY_OWNED` sprites,
consumes `SPRITE_FLAG_SKIP_INITIAL_PROGRESS` on the first update, advances
progress/lifetime timers, integrates position and velocity, applies
gravity/local-yaw steps, and advances the texture frame state seeded by
`allocate_sprite`.

Recovered sprite relationships:

- `Sprite +0x3c` stores the previous world position copied from `+0x48`.
- `Sprite +0x48/+0x54` are current world position and velocity.
- `Sprite +0x68/+0x6c` are normalized progress and progress step; when progress
  exits `[0, 1]`, the sprite is killed unless
  `SPRITE_FLAG_PRESERVE_AT_PROGRESS_END` is set.
- `Sprite +0x70/+0x74` are a lifetime accumulator and step; positive lifetime
  keeps `SPRITE_FLAG_DELAYED_RENDER` set, otherwise it clears that flag. The
  frame renderer independently excludes sprites carrying this bit.
- `Sprite +0x78` is gravity applied to velocity Y, and `+0x7c/+0x80` are the
  facing angle and per-frame angle step.
- `Sprite +0x9c/+0xa0/+0xa4/+0xa8/+0xac/+0xb0` are the primary texture id,
  frame count, current frame, frame step, frame accumulator, and frame rate.
  `SPRITE_FLAG_ANIMATED` enables frame animation;
  `SPRITE_FLAG_ANIMATION_PING_PONG` makes the frame step bounce at either end
  instead of wrapping to zero.

Exact match: 100.00%, 125/125 instructions, with ten masked operands audited.

## 2026-07-14 analysis ownership synchronization

The proven eleven-bit `SpriteFlag` word now reaches both checked-in concrete
`Sprite` analysis headers and the narrow Binary Ninja replays at owner `+0x04`.
The live owner remains exactly 0xb4 bytes, and this exact matcher remains
byte-identical. Bits without independent lifecycle or renderer evidence remain
unnamed.

## 2026-07-18 lifecycle owner replay

Both analysis databases now carry the exact
`void __thiscall update_sprite(Sprite *sprite)` receiver and the complete
0xb4-byte Sprite owner. Fresh tracked exports render the previous/current
position pair, velocity and gravity integration, lifetime flags, and animated
frame state through named fields in both tools. Cross-tool health checks reject
raw Sprite offsets while the matcher remains the 125/125, ten-operand oracle.
