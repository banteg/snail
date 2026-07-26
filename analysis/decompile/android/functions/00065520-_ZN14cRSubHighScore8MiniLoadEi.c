/*
 * mangled: _ZN14cRSubHighScore8MiniLoadEi
 * demangled: cRSubHighScore::MiniLoad(int)
 * address: 00065520
 * size: 272
 */

/* cRSubHighScore::MiniLoad(int) */

void __thiscall cRSubHighScore::MiniLoad(cRSubHighScore *this,int param_1)

{
  int iVar1;
  int iVar2;
  cRSubSolutionHeader *pcVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  int local_a8;
  char acStack_a4 [128];
  int local_24;

  iVar2 = DAT_00065634;
  iVar7 = DAT_00065630 + 0x65538;
  local_24 = **(int **)(iVar7 + DAT_00065634);
  MiniFileName(this,acStack_a4,param_1);
  pcVar3 = (cRSubSolutionHeader *)RShellMemoryScratch();
  RShellLoadFile(acStack_a4,pcVar3,&local_a8);
  if (local_a8 == 0) {
    this[param_1 * 0x38 + 0x2c] = (cRSubHighScore)0x0;
  }
  else {
    cRSubSolution::Load((cRSubSolution *)(this + 0x20d60),pcVar3);
    iVar8 = param_1 * 7 + 1;
    iVar1 = param_1 * 0x38;
    *(undefined4 *)(this + iVar8 * 8) = *(undefined4 *)(this + 0x20d60);
    uVar4 = *(undefined4 *)(this + 0x20d6c);
    uVar5 = *(undefined4 *)(this + 0x20d70);
    uVar6 = *(undefined4 *)(this + 0x20d74);
    *(undefined4 *)(this + iVar8 * 8 + 4) = *(undefined4 *)(this + 0x20d68);
    *(undefined4 *)(this + iVar8 * 8 + 8) = uVar4;
    *(undefined4 *)(this + iVar8 * 8 + 0xc) = uVar5;
    *(undefined4 *)(this + iVar8 * 8 + 0x10) = uVar6;
    uVar4 = *(undefined4 *)(this + 0x20d7c);
    *(undefined4 *)(this + iVar8 * 8 + 0x14) = *(undefined4 *)(this + 0x20d78);
    *(undefined4 *)(this + iVar8 * 8 + 0x18) = uVar4;
    strcpy((char *)(this + 0x20db4),(char *)(this + iVar1 + 0x2d));
    this[iVar1 + 0x2c] = (cRSubHighScore)0x1;
    *(undefined4 *)(this + iVar1 + 0x24) = *(undefined4 *)(this + 0x20d64);
  }
  if (local_24 == **(int **)(iVar7 + iVar2)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}
