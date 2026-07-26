/*
 * mangled: _ZN14cRSubHighScore11AddSurvivalEv
 * demangled: cRSubHighScore::AddSurvival()
 * address: 00065bec
 * size: 264
 */

/* cRSubHighScore::AddSurvival() */

void __thiscall cRSubHighScore::AddSurvival(cRSubHighScore *this)

{
  cRSubHighScore *pcVar1;
  cRSubHighScore *pcVar2;
  int iVar3;
  int iVar4;

  *(undefined4 *)(this + 0x12e4) = 0;
  *(undefined4 *)(this + 0x12dc) = 1;
  *(undefined4 *)(this + 0x12e0) = 0;
  OFAddChallenge(*(int *)(this + 0x12a4));
  if ((gCheat & 2) != 0) {
    return;
  }
  MiniSave(this,0x49);
  iVar3 = 0;
  pcVar2 = this;
  do {
    pcVar1 = pcVar2 + 0x28c;
    pcVar2 = pcVar2 + 0x38;
    if (*(int *)pcVar1 < *(int *)(this + 0x12a4)) {
      if (iVar3 < 10) {
        iVar4 = 10;
        pcVar2 = this;
        do {
          iVar4 = iVar4 + -1;
          *(undefined4 *)(pcVar2 + 0x4a0) = *(undefined4 *)(pcVar2 + 0x468);
          *(undefined4 *)(pcVar2 + 0x4a4) = *(undefined4 *)(pcVar2 + 0x46c);
          *(undefined4 *)(pcVar2 + 0x4a8) = *(undefined4 *)(pcVar2 + 0x470);
          *(undefined4 *)(pcVar2 + 0x4ac) = *(undefined4 *)(pcVar2 + 0x474);
          *(undefined4 *)(pcVar2 + 0x4b0) = *(undefined4 *)(pcVar2 + 0x478);
          *(undefined4 *)(pcVar2 + 0x4b4) = *(undefined4 *)(pcVar2 + 0x47c);
          *(undefined4 *)(pcVar2 + 0x4b8) = *(undefined4 *)(pcVar2 + 0x480);
          *(undefined4 *)(pcVar2 + 0x4bc) = *(undefined4 *)(pcVar2 + 0x484);
          *(undefined4 *)(pcVar2 + 0x4c0) = *(undefined4 *)(pcVar2 + 0x488);
          *(undefined4 *)(pcVar2 + 0x4c4) = *(undefined4 *)(pcVar2 + 0x48c);
          *(undefined4 *)(pcVar2 + 0x4c8) = *(undefined4 *)(pcVar2 + 0x490);
          *(undefined4 *)(pcVar2 + 0x4cc) = *(undefined4 *)(pcVar2 + 0x494);
          *(undefined4 *)(pcVar2 + 0x4d0) = *(undefined4 *)(pcVar2 + 0x498);
          *(undefined4 *)(pcVar2 + 0x4d4) = *(undefined4 *)(pcVar2 + 0x49c);
          pcVar2 = pcVar2 + -0x38;
        } while (iVar4 != iVar3);
      }
      MiniSave(this,iVar3 + 0xb);
      iVar4 = Game;
      *(undefined4 *)(Game + 0x2c8) = 1;
      *(undefined4 *)(iVar4 + 0x15c) = 0x14;
      *(int *)(iVar4 + 0x2c4) = iVar3;
      *(undefined1 *)(iVar4 + 0x2c1) = 1;
      return;
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 != 10);
  return;
}
