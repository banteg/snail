/*
 * mangled: _ZN12cRCompletion6UnInitEv
 * demangled: cRCompletion::UnInit()
 * address: 00061740
 * size: 400
 */

/* cRCompletion::UnInit() */

void __thiscall cRCompletion::UnInit(cRCompletion *this)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int *piVar6;

  iVar2 = DAT_000618d4;
  iVar5 = DAT_000618d0 + 0x6175c;
  if (*(int *)(this + 0x10) != 0) {
    iVar4 = *(int *)(this + 0x24);
    iVar3 = *(int *)(this + 0x18);
    if (iVar4 != iVar3) {
      bVar1 = iVar4 < iVar3;
      iVar3 = iVar4;
      if (bVar1) {
        piVar6 = *(int **)(iVar5 + DAT_000618d4);
        do {
          cRSubGoldy::ScoreAdd((cRSubGoldy *)(*piVar6 + 0x81364),4,0);
          OFAddParcelDelivered();
          iVar3 = *(int *)(this + 0x24) + 1;
          *(int *)(this + 0x24) = iVar3;
        } while (iVar3 < *(int *)(this + 0x18));
      }
      if (*(int *)(this + 0x1c) != 0) {
        cRSubGoldy::ScoreAdd
                  ((cRSubGoldy *)(**(int **)(iVar5 + iVar2) + 0x81364),5,*(int *)(this + 0x44));
        iVar3 = *(int *)(this + 0x24);
      }
    }
    piVar6 = *(int **)(iVar5 + iVar2);
    *(int *)(this + 0x24) = iVar3 + 1;
    cRBorderManager::Kill((cRBorderManager *)(*piVar6 + 0xd14),*(cRBorder **)this);
    cRBorderManager::Kill((cRBorderManager *)(*piVar6 + 0xd14),*(cRBorder **)(this + 4));
    cRBorderManager::Kill((cRBorderManager *)(*piVar6 + 0xd14),*(cRBorder **)(this + 8));
    cRBorderManager::Kill((cRBorderManager *)(*piVar6 + 0xd14),*(cRBorder **)(this + 0xc));
    iVar2 = *piVar6;
    if (*(int *)(iVar2 + 0x81630) != *(int *)(this + 0x48)) {
      cRSubGoldy::ScoreAdd
                ((cRSubGoldy *)(iVar2 + 0x81364),5,*(int *)(this + 0x48) - *(int *)(iVar2 + 0x81630)
                );
      iVar2 = *piVar6;
    }
    if (*(int *)(iVar2 + 0x71900) == 0) {
      SetGameState(1,*(int *)(iVar2 + 0x81630),*(int *)(iVar2 + 0x71904) + 1,
                   *(int *)(iVar2 + 0x85358));
    }
  }
  *(undefined4 *)(this + 0x10) = 0;
  return;
}
