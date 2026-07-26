/*
 * mangled: _Z19RShellSaveDirectoryPciPA128_c
 * demangled: RShellSaveDirectory(char*, int, char (*) [128])
 * address: 0002b84c
 * size: 196
 */

/* RShellSaveDirectory(char*, int, char (*) [128]) */

void RShellSaveDirectory(char *param_1,int param_2,char *param_3)

{
  size_t sVar1;
  int iVar2;
  char local_fcc [4000];
  int local_2c;

  iVar2 = 0;
  local_fcc[0] = '\0';
  local_2c = __stack_chk_guard;
  if (0 < param_2) {
    do {
      strcat(local_fcc,param_3);
      sVar1 = strlen(local_fcc);
      iVar2 = iVar2 + 1;
      param_3 = param_3 + 0x80;
      memcpy(local_fcc + sVar1,&DAT_00091288,3);
    } while (iVar2 < param_2);
  }
  sVar1 = strlen(local_fcc);
  RShellSaveFile(param_1,local_fcc,sVar1 + 1);
  if (local_2c == __stack_chk_guard) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}
