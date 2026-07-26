/*
 * mangled: _ZN13cRStarManager10ResetStarsEv
 * demangled: cRStarManager::ResetStars()
 * address: 0006afc0
 * size: 52
 */

/* cRStarManager::ResetStars() */

void __thiscall cRStarManager::ResetStars(cRStarManager *this)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;

  uVar1 = DAT_0006aff4;
  iVar4 = *(int *)(this + 0x34);
  if (iVar4 < 1) {
    return;
  }
  iVar2 = *(int *)(this + 0x30);
  iVar3 = 0;
  do {
    iVar3 = iVar3 + 1;
    *(undefined4 *)(*(int *)(iVar2 + 0x1c) + 0x88) = uVar1;
    iVar2 = iVar2 + 0x2c;
  } while (iVar3 != iVar4);
  return;
}
