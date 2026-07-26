/*
 * mangled: _Z15RShellPrintTextPcz
 * demangled: RShellPrintText(char*, ...)
 * address: 0002b2b8
 * size: 160
 */

/* RShellPrintText(char*, ...) */

void RShellPrintText(char *param_1,...)

{
  undefined4 in_r1;
  undefined4 in_r2;
  undefined4 in_r3;
  char acStack_102c [4096];
  int local_2c;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;

  local_2c = __stack_chk_guard;
  uStack_c = in_r1;
  uStack_8 = in_r2;
  uStack_4 = in_r3;
  vsprintf(acStack_102c,param_1,&uStack_c);
  wprintf("%s",acStack_102c);
  if (local_2c == __stack_chk_guard) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}
