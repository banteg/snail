/*
 * mangled: _ZN14cRSubHighScore12AddArcadeProEi
 * demangled: cRSubHighScore::AddArcadePro(int)
 * address: 0003ea40
 * size: 360
 */

/* cRSubHighScore::AddArcadePro(int) */

void __thiscall cRSubHighScore::AddArcadePro(cRSubHighScore *this,int param_1)

{
  undefined *puVar1;
  int iVar2;
  int iVar3;
  cRSubHighScore *pcVar4;
  uint uVar5;
  int unaff_r10;

  uVar5 = 0;
  *(undefined4 *)(this + 0x12dc) = 0;
  *(int *)(this + 0x12e0) = param_1;
  MacOFAddArcadePro(*(int *)(this + 0x12a4));
  iVar3 = *(int *)(this + 0x12a4);
  if (*(int *)(this + 0x1054) < iVar3) {
    unaff_r10 = 0x4a;
  }
  else {
    iVar2 = *(int *)(this + 0x108c);
    if (iVar2 < iVar3) {
      unaff_r10 = 0x4b;
    }
    uVar5 = (uint)(iVar2 < iVar3);
    if (iVar3 <= iVar2) {
      if (*(int *)(this + 0x10c4) < iVar3) {
        unaff_r10 = 0x4c;
        uVar5 = 2;
      }
      else if (*(int *)(this + 0x10fc) < iVar3) {
        unaff_r10 = 0x4d;
        uVar5 = 3;
      }
      else if (*(int *)(this + 0x1134) < iVar3) {
        unaff_r10 = 0x4e;
        uVar5 = 4;
      }
      else if (*(int *)(this + 0x116c) < iVar3) {
        unaff_r10 = 0x4f;
        uVar5 = 5;
      }
      else if (*(int *)(this + 0x11a4) < iVar3) {
        unaff_r10 = 0x50;
        uVar5 = 6;
      }
      else if (*(int *)(this + 0x11dc) < iVar3) {
        unaff_r10 = 0x51;
        uVar5 = 7;
      }
      else if (*(int *)(this + 0x1214) < iVar3) {
        unaff_r10 = 0x52;
        uVar5 = 8;
      }
      else {
        if (iVar3 <= *(int *)(this + 0x124c)) {
          return;
        }
        unaff_r10 = 0x53;
        uVar5 = 9;
      }
    }
  }
  pcVar4 = this + 0x1230;
  iVar3 = 10;
  do {
    iVar3 = iVar3 + -1;
    _memcpy(pcVar4 + 0x38,pcVar4,0x38);
    pcVar4 = pcVar4 + -0x38;
  } while ((int)uVar5 < iVar3);
  MiniSave(this,unaff_r10);
  puVar1 = PTR__Game_001b60b8;
  *(undefined4 *)(*(int *)PTR__Game_001b60b8 + 0x15c) = 0x14;
  *(undefined1 *)(*(int *)puVar1 + 0x2c1) = 1;
  *(uint *)(*(int *)puVar1 + 0x2c4) = uVar5;
  *(undefined4 *)(*(int *)puVar1 + 0x2c8) = 3;
  return;
}
