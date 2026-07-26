/*
 * mangled: _ZN15cRSpriteManager13GetTextureRefEi
 * demangled: cRSpriteManager::GetTextureRef(int)
 * address: 00010938
 * size: 24
 */

/* cRSpriteManager::GetTextureRef(int) */

undefined4 __thiscall cRSpriteManager::GetTextureRef(cRSpriteManager *this,int param_1)

{
  return *(undefined4 *)(*(int *)(&DAT_002ac600 + param_1 * 0x20) + 0x8c);
}
