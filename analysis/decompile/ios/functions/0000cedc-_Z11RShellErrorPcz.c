/*
 * mangled: _Z11RShellErrorPcz
 * demangled: RShellError(char*, ...)
 * address: 0000cedc
 * size: 104
 */

/* RShellError(char*, ...) */

void RShellError(char *param_1,...)

{
  undefined4 in_r1;
  undefined4 in_r2;
  undefined4 in_r3;
  char acStack_1020 [4096];
  undefined4 *local_20;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;

  local_20 = &uStack_c;
  uStack_c = in_r1;
  uStack_8 = in_r2;
  uStack_4 = in_r3;
  _vsprintf(acStack_1020,param_1,local_20);
  wprintf("***** ERROR ***** ");
  wprintf("%s",acStack_1020);
  wprintf("\n");
  return;
}
