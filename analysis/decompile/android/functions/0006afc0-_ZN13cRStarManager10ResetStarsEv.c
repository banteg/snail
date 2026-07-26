/*
 * mangled: _ZN13cRStarManager10ResetStarsEv
 * demangled: cRStarManager::ResetStars()
 * address: 0006afc0
 * size: 52
 */

/* cRStarManager::ResetStars() */

void __thiscall cRStarManager::ResetStars(cRStarManager *this)

{
  int iVar1;
  int iVar2;
  int iVar3;

  iVar3 = *(int *)(this + 0x34);
  if (iVar3 < 1) {
    return;
  }
  iVar1 = *(int *)(this + 0x30);
  iVar2 = 0;
  do {
    iVar2 = iVar2 + 1;
    *(undefined4 *)(*(int *)(iVar1 + 0x1c) + 0x88) = 0;
    iVar1 = iVar1 + 0x2c;
  } while (iVar2 != iVar3);
  return;
}
