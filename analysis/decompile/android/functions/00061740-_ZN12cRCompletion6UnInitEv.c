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

  if (*(int *)(this + 0x10) != 0) {
    iVar3 = *(int *)(this + 0x24);
    iVar2 = *(int *)(this + 0x18);
    if (iVar3 != iVar2) {
      bVar1 = iVar3 < iVar2;
      iVar2 = iVar3;
      if (bVar1) {
        do {
          cRSubGoldy::ScoreAdd((cRSubGoldy *)(Game + 0x81364),4,0);
          OFAddParcelDelivered();
          iVar2 = *(int *)(this + 0x24) + 1;
          *(int *)(this + 0x24) = iVar2;
        } while (iVar2 < *(int *)(this + 0x18));
      }
      if (*(int *)(this + 0x1c) != 0) {
        cRSubGoldy::ScoreAdd((cRSubGoldy *)(Game + 0x81364),5,*(int *)(this + 0x44));
        iVar2 = *(int *)(this + 0x24);
      }
    }
    *(int *)(this + 0x24) = iVar2 + 1;
    cRBorderManager::Kill((cRBorderManager *)(Game + 0xd14),*(cRBorder **)this);
    cRBorderManager::Kill((cRBorderManager *)(Game + 0xd14),*(cRBorder **)(this + 4));
    cRBorderManager::Kill((cRBorderManager *)(Game + 0xd14),*(cRBorder **)(this + 8));
    cRBorderManager::Kill((cRBorderManager *)(Game + 0xd14),*(cRBorder **)(this + 0xc));
    if (*(int *)(Game + 0x81630) != *(int *)(this + 0x48)) {
      cRSubGoldy::ScoreAdd
                ((cRSubGoldy *)(Game + 0x81364),5,*(int *)(this + 0x48) - *(int *)(Game + 0x81630));
    }
    if (*(int *)(Game + 0x71900) == 0) {
      SetGameState(1,*(int *)(Game + 0x81630),*(int *)(Game + 0x71904) + 1,*(int *)(Game + 0x85358))
      ;
    }
  }
  *(undefined4 *)(this + 0x10) = 0;
  return;
}
