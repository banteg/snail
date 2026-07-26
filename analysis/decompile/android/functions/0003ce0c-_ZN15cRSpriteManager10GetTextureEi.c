/*
 * mangled: _ZN15cRSpriteManager10GetTextureEi
 * demangled: cRSpriteManager::GetTexture(int)
 * address: 0003ce0c
 * size: 28
 */

/* cRSpriteManager::GetTexture(int) */

undefined4 __thiscall cRSpriteManager::GetTexture(cRSpriteManager *this,int param_1)

{
  return *(undefined4 *)(gSpriteReference + param_1 * 0x20 + 4);
}
