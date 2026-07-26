/*
 * mangled: _Z7wprintfPcz
 * demangled: wprintf(char*, ...)
 * address: 0000dc54
 * size: 88
 */

/* wprintf(char*, ...) */

int wprintf(char *param_1,...)

{
  int iVar1;
  undefined4 in_r1;
  undefined4 in_r2;
  undefined4 in_r3;
  char acStack_824 [2048];
  undefined4 *local_24;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;

  local_24 = &uStack_c;
  uStack_c = in_r1;
  uStack_8 = in_r2;
  uStack_4 = in_r3;
  iVar1 = _vsprintf(acStack_824,param_1,local_24);
  _printf(acStack_824);
  return iVar1;
}
