/*
 * mangled: _ZN10cRSubGoldy9ShowLivesEv
 * demangled: cRSubGoldy::ShowLives()
 * address: 0006ecf8
 * size: 96
 */

/* cRSubGoldy::ShowLives() */

void __thiscall cRSubGoldy::ShowLives(cRSubGoldy *this)

{
  int iVar1;
  int iVar2;

  iVar2 = 0;
  do {
    while (iVar1 = iVar2 + 0x231a, *(int *)(this + 0x3ff4) <= iVar2) {
      iVar2 = iVar2 + 1;
      cRBorder::HideInit(*(cRBorder **)(*(int *)(this + 0x400) + iVar1 * 4));
      if (iVar2 == 9) {
        return;
      }
    }
    iVar2 = iVar2 + 1;
    cRBorder::UnHideInit(*(cRBorder **)(*(int *)(this + 0x400) + iVar1 * 4));
  } while (iVar2 != 9);
  return;
}
