/*
 * mangled: _ZN15cRSpriteManager10GetTextureEi
 * demangled: cRSpriteManager::GetTexture(int)
 * address: 00010954
 * size: 20
 */

/* cRSpriteManager::GetTexture(int) */

undefined4 __thiscall cRSpriteManager::GetTexture(cRSpriteManager *this,int param_1)

{
  return *(undefined4 *)(&DAT_002ac600 + param_1 * 0x20);
}
