/*
 * mangled: _ZN13cRStarManager6UnHideEv
 * demangled: cRStarManager::UnHide()
 * address: 00066a54
 * size: 80
 */

/* cRStarManager::UnHide() */

void __thiscall cRStarManager::UnHide(cRStarManager *this)

{
  int iVar1;
  int iVar2;
  int iVar3;

  if (*(int *)(this + 0x2c) == 0) {
    return;
  }
  if (*(int *)(this + 0x34) < 1) {
    return;
  }
  iVar3 = 0;
  iVar1 = 0;
  do {
    iVar3 = iVar3 + 1;
    iVar2 = *(int *)(this + 0x30) + iVar1;
    iVar1 = iVar1 + 0x2c;
    iVar2 = *(int *)(iVar2 + 0x1c);
    *(uint *)(iVar2 + 4) = *(uint *)(iVar2 + 4) | 0x40;
  } while (iVar3 < *(int *)(this + 0x34));
  return;
}
