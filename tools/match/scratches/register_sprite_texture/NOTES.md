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

Windows startup and landscape-script callers load `g_sprite_manager @
0x790f30` into `ecx` before calling this helper; iOS names the same owner
`cRSpriteManager::Load(char*, int, int)`. Defining the exact body on
`SpriteManager` closes that ABI relationship while preserving all 35
instructions and six operand proofs. The receiver is legitimately unused
because the registered texture-id table remains a separate global on Windows.
