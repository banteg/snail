/*
 * mangled: _Z15RShellChangeDirPc
 * demangled: RShellChangeDir(char*)
 * address: 0002c138
 * size: 208
 */

/* RShellChangeDir(char*) */

void RShellChangeDir(char *param_1)

{
  int iVar1;
  undefined4 uVar2;
  char local_118;
  char local_117;
  undefined1 local_116;
  undefined1 local_115;
  undefined1 auStack_114 [256];
  int local_14;

  local_14 = __stack_chk_guard;
  if (param_1 != "") {
    if (param_1[1] == ':') {
      local_118 = *param_1;
      local_116 = 0x5c;
      local_115 = 0;
      local_117 = param_1[1];
      chdir(&local_118);
      if ((param_1[2] == '\0') || (param_1 = param_1 + 3, *param_1 == '\0')) goto LAB_0002c188;
    }
    iVar1 = chdir(param_1);
    if (iVar1 != 0) {
      RShellPrintText("ERROR: cannot find directory %s (from %s)\n",param_1,auStack_114);
      uVar2 = 1;
      goto LAB_0002c18c;
    }
  }
LAB_0002c188:
  uVar2 = 0;
LAB_0002c18c:
  if (local_14 != __stack_chk_guard) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(uVar2);
  }
  return;
}
