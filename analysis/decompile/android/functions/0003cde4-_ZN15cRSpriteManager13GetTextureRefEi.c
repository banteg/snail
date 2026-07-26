/*
 * mangled: _ZN15cRSpriteManager13GetTextureRefEi
 * demangled: cRSpriteManager::GetTextureRef(int)
 * address: 0003cde4
 * size: 32
 */

/* cRSpriteManager::GetTextureRef(int) */

undefined4 __thiscall cRSpriteManager::GetTextureRef(cRSpriteManager *this,int param_1)

{
  return *(undefined4 *)
          (*(int *)(*(int *)(DAT_0003ce04 + 0x3cdf4 + DAT_0003ce08) + param_1 * 0x20 + 4) + 0x8c);
}
