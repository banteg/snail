/*
 * mangled: _ZN14cRSubHighScore9AddArcadeEi
 * demangled: cRSubHighScore::AddArcade(int)
 * address: 00065df0
 * size: 220
 */

/* cRSubHighScore::AddArcade(int) */

void __thiscall cRSubHighScore::AddArcade(cRSubHighScore *this,int param_1)

{
  cRSubHighScore *pcVar1;
  cRSubHighScore *pcVar2;
  int iVar3;
  int iVar4;

  *(int *)(this + 0x12e0) = param_1;
  iVar3 = 0;
  *(undefined4 *)(this + 0x12dc) = 0;
  OFAddArcade(*(int *)(this + 0x12a4));
  pcVar2 = this;
  do {
    pcVar1 = pcVar2 + 0x24;
    pcVar2 = pcVar2 + 0x38;
    if (*(int *)pcVar1 < *(int *)(this + 0x12a4)) {
      if (iVar3 < 10) {
        iVar4 = 10;
        pcVar2 = this;
        do {
          iVar4 = iVar4 + -1;
          *(undefined4 *)(pcVar2 + 0x238) = *(undefined4 *)(pcVar2 + 0x200);
          *(undefined4 *)(pcVar2 + 0x23c) = *(undefined4 *)(pcVar2 + 0x204);
          *(undefined4 *)(pcVar2 + 0x240) = *(undefined4 *)(pcVar2 + 0x208);
          *(undefined4 *)(pcVar2 + 0x244) = *(undefined4 *)(pcVar2 + 0x20c);
          *(undefined4 *)(pcVar2 + 0x248) = *(undefined4 *)(pcVar2 + 0x210);
          *(undefined4 *)(pcVar2 + 0x24c) = *(undefined4 *)(pcVar2 + 0x214);
          *(undefined4 *)(pcVar2 + 0x250) = *(undefined4 *)(pcVar2 + 0x218);
          *(undefined4 *)(pcVar2 + 0x254) = *(undefined4 *)(pcVar2 + 0x21c);
          *(undefined4 *)(pcVar2 + 600) = *(undefined4 *)(pcVar2 + 0x220);
          *(undefined4 *)(pcVar2 + 0x25c) = *(undefined4 *)(pcVar2 + 0x224);
          *(undefined4 *)(pcVar2 + 0x260) = *(undefined4 *)(pcVar2 + 0x228);
          *(undefined4 *)(pcVar2 + 0x264) = *(undefined4 *)(pcVar2 + 0x22c);
          *(undefined4 *)(pcVar2 + 0x268) = *(undefined4 *)(pcVar2 + 0x230);
          *(undefined4 *)(pcVar2 + 0x26c) = *(undefined4 *)(pcVar2 + 0x234);
          pcVar2 = pcVar2 + -0x38;
        } while (iVar4 != iVar3);
      }
      MiniSave(this,iVar3);
      iVar4 = Game;
      *(undefined4 *)(Game + 0x2c8) = 0;
      *(int *)(iVar4 + 0x2c4) = iVar3;
      *(undefined4 *)(iVar4 + 0x15c) = 0x14;
      *(undefined1 *)(iVar4 + 0x2c1) = 1;
      return;
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 != 10);
  return;
}
