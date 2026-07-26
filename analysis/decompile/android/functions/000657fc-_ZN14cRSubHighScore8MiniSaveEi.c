/*
 * mangled: _ZN14cRSubHighScore8MiniSaveEi
 * demangled: cRSubHighScore::MiniSave(int)
 * address: 000657fc
 * size: 336
 */

/* cRSubHighScore::MiniSave(int) */

void __thiscall cRSubHighScore::MiniSave(cRSubHighScore *this,int param_1)

{
  uchar *puVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 uVar5;
  char acStack_ac [128];
  int local_2c;

  iVar4 = param_1 * 7 + 1;
  *(undefined4 *)(this + param_1 * 0x38 + 0x28) = gConfig._196_4_;
  local_2c = __stack_chk_guard;
  *(undefined4 *)(this + iVar4 * 8) = *(undefined4 *)(this + 0x12a0);
  uVar2 = *(undefined4 *)(this + 0x12ac);
  uVar3 = *(undefined4 *)(this + 0x12b0);
  uVar5 = *(undefined4 *)(this + 0x12b4);
  *(undefined4 *)(this + iVar4 * 8 + 4) = *(undefined4 *)(this + 0x12a8);
  *(undefined4 *)(this + iVar4 * 8 + 8) = uVar2;
  *(undefined4 *)(this + iVar4 * 8 + 0xc) = uVar3;
  *(undefined4 *)(this + iVar4 * 8 + 0x10) = uVar5;
  uVar2 = *(undefined4 *)(this + 0x12bc);
  *(undefined4 *)(this + iVar4 * 8 + 0x14) = *(undefined4 *)(this + 0x12b8);
  *(undefined4 *)(this + iVar4 * 8 + 0x18) = uVar2;
  sprintf((char *)(this + param_1 * 0x38 + 0x2d),(char *)(this + 0x12f4));
  this[param_1 * 0x38 + 0x2c] = (cRSubHighScore)0x1;
  *(undefined4 *)(this + param_1 * 0x38 + 0x24) = *(undefined4 *)(this + 0x12a4);
  puVar1 = (uchar *)RShellMemoryScratch();
  iVar4 = cRSubSolution::Save((cRSubSolution *)(this + 0x12a0),puVar1);
  MiniFileName(this,acStack_ac,param_1);
  iVar4 = RShellSaveFile(acStack_ac,puVar1,iVar4);
  if (iVar4 == 0) {
    this[param_1 * 0x38 + 0x2c] = (cRSubHighScore)0x0;
  }
  else {
    this[param_1 * 0x38 + 0x2c] = (cRSubHighScore)0x1;
  }
  gConfig._196_4_ = gConfig._196_4_ + 1;
  gRegisterSaveFile("asm.cfg",gConfig,0x130);
  SaveMiniData(this);
  if (local_2c != __stack_chk_guard) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}
