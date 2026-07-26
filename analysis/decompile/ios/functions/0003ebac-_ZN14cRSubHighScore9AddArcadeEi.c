/*
 * mangled: _ZN14cRSubHighScore9AddArcadeEi
 * demangled: cRSubHighScore::AddArcade(int)
 * address: 0003ebac
 * size: 316
 */

/* cRSubHighScore::AddArcade(int) */

void __thiscall cRSubHighScore::AddArcade(cRSubHighScore *this,int param_1)

{
  undefined *puVar1;
  int iVar2;
  cRSubHighScore *pcVar3;
  uint uVar4;

  uVar4 = 0;
  *(undefined4 *)(this + 0x12dc) = 0;
  *(int *)(this + 0x12e0) = param_1;
  MacOFAddArcade(*(int *)(this + 0x12a4));
  iVar2 = *(int *)(this + 0x12a4);
  if ((iVar2 <= *(int *)(this + 0x24)) &&
     (uVar4 = (uint)(*(int *)(this + 0x5c) < iVar2), iVar2 <= *(int *)(this + 0x5c))) {
    if (*(int *)(this + 0x94) < iVar2) {
      uVar4 = 2;
    }
    else if (*(int *)(this + 0xcc) < iVar2) {
      uVar4 = 3;
    }
    else if (*(int *)(this + 0x104) < iVar2) {
      uVar4 = 4;
    }
    else if (*(int *)(this + 0x13c) < iVar2) {
      uVar4 = 5;
    }
    else if (*(int *)(this + 0x174) < iVar2) {
      uVar4 = 6;
    }
    else if (*(int *)(this + 0x1ac) < iVar2) {
      uVar4 = 7;
    }
    else if (*(int *)(this + 0x1e4) < iVar2) {
      uVar4 = 8;
    }
    else {
      if (iVar2 <= *(int *)(this + 0x21c)) {
        return;
      }
      uVar4 = 9;
    }
  }
  iVar2 = 10;
  pcVar3 = this;
  do {
    iVar2 = iVar2 + -1;
    _memcpy(pcVar3 + 0x238,pcVar3 + 0x200,0x38);
    pcVar3 = pcVar3 + -0x38;
  } while ((int)uVar4 < iVar2);
  MiniSave(this,uVar4);
  puVar1 = PTR__Game_001b60b8;
  *(undefined4 *)(*(int *)PTR__Game_001b60b8 + 0x15c) = 0x14;
  *(undefined1 *)(*(int *)puVar1 + 0x2c1) = 1;
  *(uint *)(*(int *)puVar1 + 0x2c4) = uVar4;
  *(undefined4 *)(*(int *)puVar1 + 0x2c8) = 0;
  return;
}
