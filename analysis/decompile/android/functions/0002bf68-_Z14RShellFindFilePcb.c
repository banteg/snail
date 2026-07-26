/*
 * mangled: _Z14RShellFindFilePcb
 * demangled: RShellFindFile(char*, bool)
 * address: 0002bf68
 * size: 160
 */

/* RShellFindFile(char*, bool) */

void RShellFindFile(char *param_1,bool param_2)

{
  undefined4 uVar1;
  int iVar2;
  char acStack_9c [128];
  int local_1c;

  local_1c = __stack_chk_guard;
  if ((gDat == 0) || (param_2)) {
    RShellConvertFileName(acStack_9c,param_1);
    uVar1 = PfmFindFile(acStack_9c);
  }
  else {
    iVar2 = RShellDatFind(param_1);
    if (iVar2 == 0) {
      RShellWarning("Missing Dat File %s",param_1);
      uVar1 = 0;
    }
    else {
      uVar1 = 1;
    }
  }
  if (local_1c != __stack_chk_guard) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(uVar1);
  }
  return;
}
