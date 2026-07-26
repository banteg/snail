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
  cRSubSolutionHeader *pcVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  int local_a8;
  char acStack_a4 [128];
  int local_24;

  local_24 = __stack_chk_guard;
  MiniFileName(this,acStack_a4,param_1);
  pcVar2 = (cRSubSolutionHeader *)RShellMemoryScratch();
  RShellLoadFile(acStack_a4,pcVar2,&local_a8);
  if (local_a8 == 0) {
    this[param_1 * 0x38 + 0x2c] = (cRSubHighScore)0x0;
  }
  else {
    cRSubSolution::Load((cRSubSolution *)(this + 0x20d60),pcVar2);
    iVar6 = param_1 * 7 + 1;
    iVar1 = param_1 * 0x38;
    *(undefined4 *)(this + iVar6 * 8) = *(undefined4 *)(this + 0x20d60);
    uVar3 = *(undefined4 *)(this + 0x20d6c);
    uVar4 = *(undefined4 *)(this + 0x20d70);
    uVar5 = *(undefined4 *)(this + 0x20d74);
    *(undefined4 *)(this + iVar6 * 8 + 4) = *(undefined4 *)(this + 0x20d68);
    *(undefined4 *)(this + iVar6 * 8 + 8) = uVar3;
    *(undefined4 *)(this + iVar6 * 8 + 0xc) = uVar4;
    *(undefined4 *)(this + iVar6 * 8 + 0x10) = uVar5;
    uVar3 = *(undefined4 *)(this + 0x20d7c);
    *(undefined4 *)(this + iVar6 * 8 + 0x14) = *(undefined4 *)(this + 0x20d78);
    *(undefined4 *)(this + iVar6 * 8 + 0x18) = uVar3;
    strcpy((char *)(this + 0x20db4),(char *)(this + iVar1 + 0x2d));
    this[iVar1 + 0x2c] = (cRSubHighScore)0x1;
    *(undefined4 *)(this + iVar1 + 0x24) = *(undefined4 *)(this + 0x20d64);
  }
  if (local_24 == __stack_chk_guard) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}
