# register_sprite_texture

Registers one sprite texture id into `g_sprite_texture_table`.

- `TextureRef +0x00` is the shared texture flags word.
- `TextureRef +0x90` is cleared for sprites during registration and later read
  by `allocate_sprite` as sprite frame count.
- `TextureRef +0x94` is the animated-sprite frame-progress step copied by
  `allocate_sprite` when texture flag `0x2000` is set.
- The leading scan to the first `.` is retained by native code, but the scanned
  pointer is not consumed by this function. Treat it as source validation /
  extension probing until another texture loader uses the value directly.
