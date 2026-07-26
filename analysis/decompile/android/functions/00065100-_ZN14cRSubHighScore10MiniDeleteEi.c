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
  bool bVar3;
  char acStack_ac [128];
  int local_2c;

  iVar1 = param_1 * 0x38;
  iVar2 = param_1 * 7 + 1;
  local_2c = __stack_chk_guard;
  MiniFileName(this,acStack_ac,param_1);
  RShellDeleteFile(acStack_ac);
  *(undefined4 *)(this + iVar2 * 8) = 0;
  cRTime::Zero((cRTime *)(this + iVar2 * 8 + 4));
  memcpy(this + iVar1 + 0x2d,&DAT_000934c4,5);
  bVar3 = local_2c == __stack_chk_guard;
  *(undefined4 *)(this + iVar1 + 0x24) = 0;
  this[iVar1 + 0x2c] = (cRSubHighScore)0x0;
  if (bVar3) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}
