/*
 * mangled: _ZN13cRStarManager6UnInitEv
 * demangled: cRStarManager::UnInit()
 * address: 0006b400
 * size: 84
 */

/* cRStarManager::UnInit() */

void __thiscall cRStarManager::UnInit(cRStarManager *this)

{
  int iVar1;
  int iVar2;
  int iVar3;

  if (0 < *(int *)(this + 0x34)) {
    iVar2 = 0;
    iVar3 = 0;
    do {
      iVar3 = iVar3 + 1;
      iVar1 = *(int *)(this + 0x30) + iVar2;
      *(undefined4 *)(*(int *)(this + 0x30) + iVar2) = 0;
      iVar2 = iVar2 + 0x2c;
      cRSprite::Kill(*(cRSprite **)(iVar1 + 0x1c));
    } while (iVar3 < *(int *)(this + 0x34));
  }
  *(undefined4 *)(this + 0x2c) = 0;
  return;
}
