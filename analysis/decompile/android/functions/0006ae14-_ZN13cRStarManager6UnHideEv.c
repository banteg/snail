/*
 * mangled: _ZN13cRStarManager6UnHideEv
 * demangled: cRStarManager::UnHide()
 * address: 0006ae14
 * size: 68
 */

/* cRStarManager::UnHide() */

void __thiscall cRStarManager::UnHide(cRStarManager *this)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;

  if (*(int *)(this + 0x2c) == 0) {
    return;
  }
  iVar4 = *(int *)(this + 0x34);
  if (iVar4 < 1) {
    return;
  }
  iVar2 = *(int *)(this + 0x30);
  iVar3 = 0;
  do {
    piVar1 = (int *)(iVar2 + 0x1c);
    iVar3 = iVar3 + 1;
    iVar2 = iVar2 + 0x2c;
    *(uint *)(*piVar1 + 4) = *(uint *)(*piVar1 + 4) | 0x40;
  } while (iVar3 != iVar4);
  return;
}
