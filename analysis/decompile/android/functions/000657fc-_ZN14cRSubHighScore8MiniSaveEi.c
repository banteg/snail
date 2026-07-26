/*
 * mangled: _ZN14cRSubHighScore8MiniSaveEi
 * demangled: cRSubHighScore::MiniSave(int)
 * address: 000657fc
 * size: 336
 */

/* cRSubHighScore::MiniSave(int) */

void __thiscall cRSubHighScore::MiniSave(cRSubHighScore *this,int param_1)

{
  int iVar1;
  int iVar2;
  uchar *puVar3;
  char *pcVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int iVar7;
  undefined4 uVar8;
  void *pvVar9;
  int iVar10;
  int *piVar11;
  char acStack_ac [128];
  int local_2c;

  iVar2 = DAT_00065954;
  iVar1 = DAT_00065950;
  iVar10 = DAT_0006594c + 0x65814;
  iVar7 = param_1 * 7 + 1;
  piVar11 = *(int **)(iVar10 + DAT_00065954);
  *(undefined4 *)(this + param_1 * 0x38 + 0x28) =
       *(undefined4 *)(*(int *)(iVar10 + DAT_00065950) + 0xc4);
  local_2c = *piVar11;
  *(undefined4 *)(this + iVar7 * 8) = *(undefined4 *)(this + 0x12a0);
  uVar5 = *(undefined4 *)(this + 0x12ac);
  uVar6 = *(undefined4 *)(this + 0x12b0);
  uVar8 = *(undefined4 *)(this + 0x12b4);
  *(undefined4 *)(this + iVar7 * 8 + 4) = *(undefined4 *)(this + 0x12a8);
  *(undefined4 *)(this + iVar7 * 8 + 8) = uVar5;
  *(undefined4 *)(this + iVar7 * 8 + 0xc) = uVar6;
  *(undefined4 *)(this + iVar7 * 8 + 0x10) = uVar8;
  uVar5 = *(undefined4 *)(this + 0x12bc);
  *(undefined4 *)(this + iVar7 * 8 + 0x14) = *(undefined4 *)(this + 0x12b8);
  *(undefined4 *)(this + iVar7 * 8 + 0x18) = uVar5;
  sprintf((char *)(this + param_1 * 0x38 + 0x2d),(char *)(this + 0x12f4));
  this[param_1 * 0x38 + 0x2c] = (cRSubHighScore)0x1;
  *(undefined4 *)(this + param_1 * 0x38 + 0x24) = *(undefined4 *)(this + 0x12a4);
  puVar3 = (uchar *)RShellMemoryScratch();
  iVar7 = cRSubSolution::Save((cRSubSolution *)(this + 0x12a0),puVar3);
  MiniFileName(this,acStack_ac,param_1);
  iVar7 = RShellSaveFile(acStack_ac,puVar3,iVar7);
  if (iVar7 == 0) {
    this[param_1 * 0x38 + 0x2c] = (cRSubHighScore)0x0;
  }
  else {
    this[param_1 * 0x38 + 0x2c] = (cRSubHighScore)0x1;
  }
  pvVar9 = *(void **)(iVar10 + iVar1);
  pcVar4 = (char *)(iVar10 + DAT_00065958);
  *(int *)((int)pvVar9 + 0xc4) = *(int *)((int)pvVar9 + 0xc4) + 1;
  gRegisterSaveFile(pcVar4,pvVar9,0x130);
  SaveMiniData(this);
  if (local_2c != **(int **)(iVar10 + iVar2)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}
