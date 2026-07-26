/*
 * mangled: _ZN14cRSubHighScore11AddSurvivalEv
 * demangled: cRSubHighScore::AddSurvival()
 * address: 0003e8a8
 * size: 400
 */

/* cRSubHighScore::AddSurvival() */

void __thiscall cRSubHighScore::AddSurvival(cRSubHighScore *this)

{
  undefined *puVar1;
  int iVar2;
  cRSubHighScore *pcVar3;
  int iVar4;
  int iVar5;

  iVar5 = 1;
  *(undefined4 *)(this + 0x12e0) = 0;
  *(undefined4 *)(this + 0x12e4) = 0;
  *(undefined4 *)(this + 0x12dc) = 1;
  MacOFAddChallenge(*(int *)(this + 0x12a4));
  if ((*(uint *)PTR__gCheat_001b61dc & 2) == 0) {
    MiniSave(this,0x49);
    iVar2 = *(int *)(this + 0x12a4);
    if (*(int *)(this + 0x28c) < iVar2) {
      iVar2 = 0xb;
      iVar5 = 0;
    }
    else if (*(int *)(this + 0x2c4) < iVar2) {
      iVar2 = 0xc;
    }
    else if (*(int *)(this + 0x2fc) < iVar2) {
      iVar2 = 0xd;
      iVar5 = 2;
    }
    else if (*(int *)(this + 0x334) < iVar2) {
      iVar2 = 0xe;
      iVar5 = 3;
    }
    else if (*(int *)(this + 0x36c) < iVar2) {
      iVar2 = 0xf;
      iVar5 = 4;
    }
    else if (*(int *)(this + 0x3a4) < iVar2) {
      iVar2 = 0x10;
      iVar5 = 5;
    }
    else if (*(int *)(this + 0x3dc) < iVar2) {
      iVar2 = 0x11;
      iVar5 = 6;
    }
    else if (*(int *)(this + 0x414) < iVar2) {
      iVar2 = 0x12;
      iVar5 = 7;
    }
    else if (*(int *)(this + 0x44c) < iVar2) {
      iVar2 = 0x13;
      iVar5 = 8;
    }
    else {
      if (iVar2 <= *(int *)(this + 0x484)) {
        return;
      }
      iVar2 = 0x14;
      iVar5 = 9;
    }
    iVar4 = 10;
    pcVar3 = this;
    do {
      iVar4 = iVar4 + -1;
      _memcpy(pcVar3 + 0x4a0,pcVar3 + 0x468,0x38);
      pcVar3 = pcVar3 + -0x38;
    } while (iVar5 < iVar4);
    MiniSave(this,iVar2);
    puVar1 = PTR__Game_001b60b8;
    *(undefined4 *)(*(int *)PTR__Game_001b60b8 + 0x15c) = 0x14;
    *(undefined1 *)(*(int *)puVar1 + 0x2c1) = 1;
    if (iVar5 != -1) {
      *(int *)(*(int *)puVar1 + 0x2c4) = iVar5;
      *(undefined4 *)(*(int *)puVar1 + 0x2c8) = 1;
    }
  }
  return;
}
