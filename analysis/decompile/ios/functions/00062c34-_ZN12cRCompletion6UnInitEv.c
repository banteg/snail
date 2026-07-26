/*
 * mangled: _ZN12cRCompletion6UnInitEv
 * demangled: cRCompletion::UnInit()
 * address: 00062c34
 * size: 372
 */

/* cRCompletion::UnInit() */

void __thiscall cRCompletion::UnInit(cRCompletion *this)

{
  undefined *puVar1;
  int iVar2;

  puVar1 = PTR__Game_001b60b8;
  if (*(int *)(this + 0x10) != 0) {
    iVar2 = *(int *)(this + 0x24);
    if (iVar2 != *(int *)(this + 0x18)) {
      if (iVar2 < *(int *)(this + 0x18)) {
        do {
          cRSubGoldy::ScoreAdd((cRSubGoldy *)(*(int *)puVar1 + 0x81fc0),4,0);
          MacOFAddParcelDelivered();
          iVar2 = *(int *)(this + 0x24) + 1;
          *(int *)(this + 0x24) = iVar2;
        } while (iVar2 < *(int *)(this + 0x18));
      }
      if (*(int *)(this + 0x1c) != 0) {
        cRSubGoldy::ScoreAdd
                  ((cRSubGoldy *)(*(int *)PTR__Game_001b60b8 + 0x81fc0),5,*(int *)(this + 0x44));
        iVar2 = *(int *)(this + 0x24);
      }
    }
    *(int *)(this + 0x24) = iVar2 + 1;
    puVar1 = PTR__Game_001b60b8;
    cRBorderManager::Kill((cRBorder *)(*(int *)PTR__Game_001b60b8 + 0xd14));
    cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
    cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
    cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
    iVar2 = *(int *)puVar1;
    if (*(int *)(iVar2 + 0x8228c) != *(int *)(this + 0x48)) {
      cRSubGoldy::ScoreAdd
                ((cRSubGoldy *)(iVar2 + 0x81fc0),5,*(int *)(this + 0x48) - *(int *)(iVar2 + 0x8228c)
                );
      iVar2 = *(int *)puVar1;
    }
    if (*(int *)(iVar2 + 0x72bd0) == 0) {
      SetGameState(1,*(int *)(iVar2 + 0x8228c),*(int *)(iVar2 + 0x72bd4) + 1,
                   *(int *)(iVar2 + 0x85fac));
      *(undefined4 *)(this + 0x10) = 0;
      return;
    }
  }
  *(undefined4 *)(this + 0x10) = 0;
  return;
}
