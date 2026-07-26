/*
 * mangled: _ZN14cRSubHighScore8MiniSaveEi
 * demangled: cRSubHighScore::MiniSave(int)
 * address: 0003e4a4
 * size: 816
 */

/* cRSubHighScore::MiniSave(int) */

void __thiscall cRSubHighScore::MiniSave(cRSubHighScore *this,int param_1)

{
  undefined *puVar1;
  int *piVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  cRSubHighScore *pcVar7;
  undefined4 uVar8;
  int iVar9;
  char local_a0 [4];
  char acStack_9c [4];
  undefined2 local_98;
  undefined1 local_96;

  iVar4 = param_1 * 0x38;
  *(undefined4 *)(this + iVar4 + 0x28) = *(undefined4 *)(PTR__gConfig_001b60d4 + 0xc4);
  *(undefined4 *)(this + iVar4 + 8) = *(undefined4 *)(this + 0x12a0);
  uVar3 = *(undefined4 *)(this + 0x12ac);
  uVar5 = *(undefined4 *)(this + 0x12b0);
  uVar8 = *(undefined4 *)(this + 0x12b4);
  *(undefined4 *)(this + iVar4 + 0xc) = *(undefined4 *)(this + 0x12a8);
  *(undefined4 *)(this + iVar4 + 0x10) = uVar3;
  *(undefined4 *)(this + iVar4 + 0x14) = uVar5;
  *(undefined4 *)(this + iVar4 + 0x18) = uVar8;
  uVar3 = *(undefined4 *)(this + 0x12bc);
  *(undefined4 *)(this + iVar4 + 0x1c) = *(undefined4 *)(this + 0x12b8);
  *(undefined4 *)(this + iVar4 + 0x20) = uVar3;
  _sprintf((char *)(this + iVar4 + 0x2d),(char *)(this + 0x12f4));
  uVar3 = *(undefined4 *)(this + 0x12a4);
  this[iVar4 + 0x2c] = (cRSubHighScore)0x1;
  *(undefined4 *)(this + iVar4 + 0x24) = uVar3;
  piVar2 = (int *)RShellMemoryScratch();
  *(undefined4 *)(this + 0x12a0) = 1;
  piVar2[0x1d] = *(int *)(this + 0x130c);
  piVar2[0xb] = *(int *)(this + 0x12c8);
  piVar2[0xc] = *(int *)(this + 0x12cc);
  piVar2[0x12] = *(int *)(this + 0x12e8);
  piVar2[0x15] = *(int *)(this + 0x12d4);
  Rstrcpy((char *)(piVar2 + 0x17),(char *)(this + 0x12f4));
  iVar4 = *(int *)(this + 0x12ac);
  iVar6 = *(int *)(this + 0x12b0);
  iVar9 = *(int *)(this + 0x12b4);
  piVar2[2] = *(int *)(this + 0x12a8);
  piVar2[3] = iVar4;
  piVar2[4] = iVar6;
  piVar2[5] = iVar9;
  iVar4 = *(int *)(this + 0x12bc);
  piVar2[6] = *(int *)(this + 0x12b8);
  piVar2[7] = iVar4;
  piVar2[8] = *(int *)(this + 0x12c0);
  piVar2[0x13] = *(int *)(this + 0x12ec);
  piVar2[0x14] = *(int *)(this + 0x12f0);
  piVar2[0x1e] = *(int *)(this + 0x20d50);
  piVar2[0x1f] = *(int *)(this + 0x20d54);
  piVar2[9] = *(int *)(this + 0x12c4);
  piVar2[1] = *(int *)(this + 0x12a4);
  piVar2[10] = *(int *)(this + 0x12a4) * *(int *)(this + 0x12a4) ^ 0xdeadbabe;
  piVar2[0x1c] = *(int *)(this + 0x1308);
  piVar2[0x20] = *(int *)(this + 0x20d58);
  piVar2[0x21] = *(int *)(this + 0x20d5c);
  piVar2[0xe] = *(int *)(this + 0x12d8);
  piVar2[0xf] = *(int *)(this + 0x12dc);
  piVar2[0x10] = *(int *)(this + 0x12e0);
  piVar2[0x11] = *(int *)(this + 0x12e4);
  iVar4 = *(int *)(this + 0x130c);
  if (iVar4 < 1) {
LAB_0003e6d4:
    iVar6 = iVar4 << 2;
  }
  else {
    iVar6 = 0;
    pcVar7 = this + 0x1310;
    do {
      iVar4 = iVar6 * 2;
      iVar6 = iVar6 + 1;
      *(undefined2 *)((int)piVar2 + iVar4 + 0x88) = *(undefined2 *)pcVar7;
      iVar4 = *(int *)(this + 0x130c);
      pcVar7 = pcVar7 + 6;
    } while (iVar6 < iVar4);
    iVar6 = iVar4 * 2;
    if (iVar4 < 1) goto LAB_0003e6d4;
    iVar9 = 0;
    pcVar7 = this + 0x1312;
    do {
      iVar4 = iVar9 * 2;
      iVar9 = iVar9 + 1;
      *(undefined2 *)((int)piVar2 + iVar4 + iVar6 + 0x88) = *(undefined2 *)pcVar7;
      iVar4 = *(int *)(this + 0x130c);
      pcVar7 = pcVar7 + 6;
    } while (iVar9 < iVar4);
    iVar6 = iVar4 * 4;
    if (0 < iVar4) {
      iVar9 = 0;
      pcVar7 = this + 0x1314;
      do {
        *(char *)((int)piVar2 + iVar9 + iVar6 + 0x88) = (char)*(undefined2 *)pcVar7;
        iVar4 = *(int *)(this + 0x130c);
        iVar9 = iVar9 + 1;
        pcVar7 = pcVar7 + 6;
      } while (iVar9 < iVar4);
      goto LAB_0003e6d4;
    }
  }
  iVar6 = iVar4 + 0x88 + iVar6;
  *piVar2 = iVar6;
  if (param_1 - 0x16U < 0x33) {
    _sprintf(local_a0,"TT_%03i.bin");
  }
  else {
    if (param_1 == 0x49) {
      local_a0[0] = 'S';
      local_a0[1] = 'L';
      local_a0[2] = '_';
      local_a0[3] = '0';
      acStack_9c[0] = '0';
      acStack_9c[1] = '0';
      acStack_9c[2] = '.';
      acStack_9c[3] = 'b';
      local_98 = 0x6e69;
      local_96 = 0;
      iVar4 = RShellSaveFile(local_a0,piVar2,iVar6);
      goto joined_r0x0003e7a4;
    }
    _sprintf(local_a0,"HS_%08i.bin",*(undefined4 *)(this + param_1 * 0x38 + 0x28));
  }
  iVar4 = RShellSaveFile(local_a0,piVar2,iVar6);
joined_r0x0003e7a4:
  if (iVar4 == 0) {
    this[param_1 * 0x38 + 0x2c] = (cRSubHighScore)0x0;
  }
  else {
    this[param_1 * 0x38 + 0x2c] = (cRSubHighScore)0x1;
  }
  puVar1 = PTR__gConfig_001b60d4;
  *(int *)(PTR__gConfig_001b60d4 + 0xc4) = *(int *)(PTR__gConfig_001b60d4 + 0xc4) + 1;
  gRegisterSaveFile("ism.cfg",puVar1,0xf0);
  SaveMiniData(this);
  return;
}
