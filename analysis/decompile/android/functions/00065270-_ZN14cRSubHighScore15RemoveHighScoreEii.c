/*
 * mangled: _ZN14cRSubHighScore15RemoveHighScoreEii
 * demangled: cRSubHighScore::RemoveHighScore(int, int)
 * address: 00065270
 * size: 248
 */

/* cRSubHighScore::RemoveHighScore(int, int) */

void __thiscall cRSubHighScore::RemoveHighScore(cRSubHighScore *this,int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  cRSubHighScore *pcVar5;
  cRSubHighScore *pcVar6;

  if (param_1 == 1) {
    iVar1 = param_2 + 0xb;
  }
  else if (param_1 == 3) {
    iVar1 = param_2 + 0x4a;
  }
  else {
    iVar1 = param_2;
    if (param_1 != 0) {
      iVar1 = 0;
    }
  }
  MiniDelete(this,iVar1);
  if (9 < param_2) {
    return;
  }
  do {
    if (param_1 == 1) {
      pcVar5 = this + (param_2 * 7 + 0x55) * 8;
      pcVar6 = this + (param_2 * 7 + 0x4e) * 8;
LAB_000652e8:
      uVar2 = *(undefined4 *)(pcVar5 + 4);
      uVar3 = *(undefined4 *)(pcVar5 + 8);
      uVar4 = *(undefined4 *)(pcVar5 + 0xc);
      *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
      *(undefined4 *)(pcVar6 + 4) = uVar2;
      *(undefined4 *)(pcVar6 + 8) = uVar3;
      *(undefined4 *)(pcVar6 + 0xc) = uVar4;
      uVar2 = *(undefined4 *)(pcVar5 + 0x14);
      uVar3 = *(undefined4 *)(pcVar5 + 0x18);
      uVar4 = *(undefined4 *)(pcVar5 + 0x1c);
      *(undefined4 *)(pcVar6 + 0x10) = *(undefined4 *)(pcVar5 + 0x10);
      *(undefined4 *)(pcVar6 + 0x14) = uVar2;
      *(undefined4 *)(pcVar6 + 0x18) = uVar3;
      *(undefined4 *)(pcVar6 + 0x1c) = uVar4;
      uVar2 = *(undefined4 *)(pcVar5 + 0x24);
      uVar3 = *(undefined4 *)(pcVar5 + 0x28);
      uVar4 = *(undefined4 *)(pcVar5 + 0x2c);
      *(undefined4 *)(pcVar6 + 0x20) = *(undefined4 *)(pcVar5 + 0x20);
      *(undefined4 *)(pcVar6 + 0x24) = uVar2;
      *(undefined4 *)(pcVar6 + 0x28) = uVar3;
      *(undefined4 *)(pcVar6 + 0x2c) = uVar4;
      uVar2 = *(undefined4 *)(pcVar5 + 0x34);
      *(undefined4 *)(pcVar6 + 0x30) = *(undefined4 *)(pcVar5 + 0x30);
      *(undefined4 *)(pcVar6 + 0x34) = uVar2;
    }
    else {
      if (param_1 == 3) {
        pcVar5 = this + ((param_2 + 0x4b) * 7 + 1) * 8;
        pcVar6 = this + ((param_2 + 0x4a) * 7 + 1) * 8;
        goto LAB_000652e8;
      }
      pcVar6 = this + (param_2 * 7 + 1) * 8;
      if (param_1 == 0) {
        pcVar5 = this + ((param_2 + 1) * 7 + 1) * 8;
        goto LAB_000652e8;
      }
    }
    param_2 = param_2 + 1;
    if (9 < param_2) {
      return;
    }
  } while( true );
}
