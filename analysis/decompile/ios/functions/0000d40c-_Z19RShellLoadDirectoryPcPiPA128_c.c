/*
 * mangled: _Z19RShellLoadDirectoryPcPiPA128_c
 * demangled: RShellLoadDirectory(char*, int*, char (*) [128])
 * address: 0000d40c
 * size: 148
 */

/* RShellLoadDirectory(char*, int*, char (*) [128]) */

void RShellLoadDirectory(char *param_1,int *param_2,char *param_3)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  char *pcVar4;
  int iVar5;
  int local_14;

  pcVar3 = (char *)RShellLoadFile(param_1,(void *)0x0,&local_14);
  iVar5 = 0;
  pcVar3[local_14 + -1] = '\0';
  *param_2 = 0;
  cVar1 = *pcVar3;
  pcVar4 = pcVar3;
  while (cVar1 != '\0') {
    pcVar2 = param_3 + iVar5 * 0x80;
    while (cVar1 != '\r') {
      *pcVar2 = cVar1;
      pcVar4 = pcVar4 + 1;
      pcVar2 = pcVar2 + 1;
      cVar1 = *pcVar4;
    }
    *pcVar2 = '\0';
    pcVar4 = pcVar4 + 2;
    iVar5 = *param_2 + 1;
    *param_2 = iVar5;
    cVar1 = *pcVar4;
  }
  _free(pcVar3);
  return;
}
