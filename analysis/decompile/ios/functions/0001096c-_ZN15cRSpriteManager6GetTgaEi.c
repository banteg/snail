/*
 * mangled: _ZN15cRSpriteManager6GetTgaEi
 * demangled: cRSpriteManager::GetTga(int)
 * address: 0001096c
 * size: 24
 */

/* cRSpriteManager::GetTga(int) */

undefined4 __thiscall cRSpriteManager::GetTga(cRSpriteManager *this,int param_1)

{
  return *(undefined4 *)(*(int *)(&DAT_002ac600 + param_1 * 0x20) + 0x98);
}
