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

## 2026-07-14 sprite texture-table extent

The native error names `RSPRITE_REFERENCE_MAX` and passes 1000 as its value.
That bound also closes the global layout exactly: 1000 pointer slots from
`g_sprite_texture_table` (`0x78ff90`) occupy `0xfa0` bytes and end at the
`g_sprite_manager` base (`0x790f30`). The table declaration and both limit
uses now share `SPRITE_TEXTURE_CAPACITY`.

The registrar remains byte-identical at `35/35` with six clean operands and
normalized hash
`0bd7a4385ac79f034a63c5af4a9b04e5050105a08a97e90ee1269e2eb70063c1`.
The exact allocation/get/set consumers retain hashes
`2b2968a6e83462a879a086cc5416bbffd4c0bed6bd8355921acfaff7a7ecda89`,
`f97d461b2bf8ec70b2b88601d81db1eb3ab97de23a4f1a306127104a45e30285`,
and `49c8696ecafced0fc365f962d9087162719202a2bb9819d0f14d77f6f2d36d68`.

2026-07-18 analysis replay: Binary Ninja and IDA now both retain the exact
`SpriteManager *manager` thiscall receiver for registration and the two texture
accessors. The receiver remains intentionally unused in the Windows body; it
is ownership evidence, not a pretext to move the separately addressed texture
table into the manager layout.
