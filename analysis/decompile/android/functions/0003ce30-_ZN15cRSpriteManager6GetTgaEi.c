/*
 * mangled: _ZN15cRSpriteManager6GetTgaEi
 * demangled: cRSpriteManager::GetTga(int)
 * address: 0003ce30
 * size: 32
 */

/* cRSpriteManager::GetTga(int) */

undefined4 __thiscall cRSpriteManager::GetTga(cRSpriteManager *this,int param_1)

{
  return *(undefined4 *)(*(int *)(gSpriteReference + param_1 * 0x20 + 4) + 0x98);
}
