/*
 * mangled: _ZN14cRSubHighScore10MiniDeleteEi
 * demangled: cRSubHighScore::MiniDelete(int)
 * address: 00065100
 * size: 168
 */

/* cRSubHighScore::MiniDelete(int) */

void __thiscall cRSubHighScore::MiniDelete(cRSubHighScore *this,int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  char acStack_ac [128];
  int local_2c;

  iVar2 = DAT_000651a8 + 0x65118;
  piVar4 = *(int **)(iVar2 + DAT_000651ac);
  iVar1 = param_1 * 0x38;
  iVar3 = param_1 * 7 + 1;
  local_2c = *piVar4;
  MiniFileName(this,acStack_ac,param_1);
  RShellDeleteFile(acStack_ac);
  *(undefined4 *)(this + iVar3 * 8) = 0;
  cRTime::Zero((cRTime *)(this + iVar3 * 8 + 4));
  memcpy(this + iVar1 + 0x2d,(void *)(iVar2 + DAT_000651b0),5);
  iVar2 = *piVar4;
  *(undefined4 *)(this + iVar1 + 0x24) = 0;
  this[iVar1 + 0x2c] = (cRSubHighScore)0x0;
  if (local_2c == iVar2) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}
