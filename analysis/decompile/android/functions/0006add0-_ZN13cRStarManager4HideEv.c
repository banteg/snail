/*
 * mangled: _ZN13cRStarManager4HideEv
 * demangled: cRStarManager::Hide()
 * address: 0006add0
 * size: 68
 */

/* cRStarManager::Hide() */

void __thiscall cRStarManager::Hide(cRStarManager *this)

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
    *(uint *)(*piVar1 + 4) = *(uint *)(*piVar1 + 4) & 0xffffffbf;
  } while (iVar3 != iVar4);
  return;
}
