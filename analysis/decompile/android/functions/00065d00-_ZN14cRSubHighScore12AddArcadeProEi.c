/*
 * mangled: _ZN14cRSubHighScore12AddArcadeProEi
 * demangled: cRSubHighScore::AddArcadePro(int)
 * address: 00065d00
 * size: 232
 */

/* cRSubHighScore::AddArcadePro(int) */

void __thiscall cRSubHighScore::AddArcadePro(cRSubHighScore *this,int param_1)

{
  int iVar1;
  cRSubHighScore *pcVar2;
  int iVar3;
  int iVar4;

  iVar3 = DAT_00065de8;
  *(int *)(this + 0x12e0) = param_1;
  iVar4 = 0;
  *(undefined4 *)(this + 0x12dc) = 0;
  OFAddArcadePro(*(int *)(this + 0x12a4));
  pcVar2 = this + 0x1054;
  do {
    iVar1 = *(int *)pcVar2;
    pcVar2 = pcVar2 + 0x38;
    if (iVar1 < *(int *)(this + 0x12a4)) {
      if (iVar4 < 10) {
        iVar1 = 10;
        pcVar2 = this + 0x1230;
        do {
          iVar1 = iVar1 + -1;
          *(undefined4 *)(pcVar2 + 0x38) = *(undefined4 *)pcVar2;
          *(undefined4 *)(pcVar2 + 0x3c) = *(undefined4 *)(pcVar2 + 4);
          *(undefined4 *)(pcVar2 + 0x40) = *(undefined4 *)(pcVar2 + 8);
          *(undefined4 *)(pcVar2 + 0x44) = *(undefined4 *)(pcVar2 + 0xc);
          *(undefined4 *)(pcVar2 + 0x48) = *(undefined4 *)(pcVar2 + 0x10);
          *(undefined4 *)(pcVar2 + 0x4c) = *(undefined4 *)(pcVar2 + 0x14);
          *(undefined4 *)(pcVar2 + 0x50) = *(undefined4 *)(pcVar2 + 0x18);
          *(undefined4 *)(pcVar2 + 0x54) = *(undefined4 *)(pcVar2 + 0x1c);
          *(undefined4 *)(pcVar2 + 0x58) = *(undefined4 *)(pcVar2 + 0x20);
          *(undefined4 *)(pcVar2 + 0x5c) = *(undefined4 *)(pcVar2 + 0x24);
          *(undefined4 *)(pcVar2 + 0x60) = *(undefined4 *)(pcVar2 + 0x28);
          *(undefined4 *)(pcVar2 + 100) = *(undefined4 *)(pcVar2 + 0x2c);
          *(undefined4 *)(pcVar2 + 0x68) = *(undefined4 *)(pcVar2 + 0x30);
          *(undefined4 *)(pcVar2 + 0x6c) = *(undefined4 *)(pcVar2 + 0x34);
          pcVar2 = pcVar2 + -0x38;
        } while (iVar1 != iVar4);
      }
      MiniSave(this,iVar4 + 0x4a);
      iVar3 = **(int **)(iVar3 + 0x65d34 + DAT_00065dec);
      *(undefined4 *)(iVar3 + 0x2c8) = 3;
      *(int *)(iVar3 + 0x2c4) = iVar4;
      *(undefined4 *)(iVar3 + 0x15c) = 0x14;
      *(undefined1 *)(iVar3 + 0x2c1) = 1;
      return;
    }
    iVar4 = iVar4 + 1;
  } while (iVar4 != 10);
  return;
}
