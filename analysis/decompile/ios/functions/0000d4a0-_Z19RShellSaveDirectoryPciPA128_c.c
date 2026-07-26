/*
 * mangled: _Z19RShellSaveDirectoryPciPA128_c
 * demangled: RShellSaveDirectory(char*, int, char (*) [128])
 * address: 0000d4a0
 * size: 116
 */

/* RShellSaveDirectory(char*, int, char (*) [128]) */

void RShellSaveDirectory(char *param_1,int param_2,char *param_3)

{
  size_t sVar1;
  int iVar2;
  char local_fb8 [4000];

  iVar2 = 0;
  local_fb8[0] = '\0';
  if (0 < param_2) {
    do {
      _strcat(local_fb8,param_3);
      iVar2 = iVar2 + 1;
      _strcat(local_fb8,"\r\n");
      param_3 = param_3 + 0x80;
    } while (iVar2 != param_2);
  }
  sVar1 = _strlen(local_fb8);
  MacSaveFile(param_1,local_fb8,sVar1 + 1);
  return;
}
