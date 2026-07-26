/*
 * mangled: _Z19RShellLoadDirectoryPcPiPA128_c
 * demangled: RShellLoadDirectory(char*, int*, char (*) [128])
 * address: 0002baf8
 * size: 132
 */

/* RShellLoadDirectory(char*, int*, char (*) [128]) */

void RShellLoadDirectory(char *param_1,int *param_2,char *param_3)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  int iVar4;
  char *pcVar5;
  int local_14 [2];

  pcVar3 = (char *)RShellLoadFile(param_1,local_14);
  iVar4 = 0;
  pcVar3[local_14[0] + -1] = '\0';
  *param_2 = 0;
  cVar1 = *pcVar3;
  pcVar5 = pcVar3;
  while (cVar1 != '\0') {
    pcVar2 = param_3 + iVar4 * 0x80;
    while (cVar1 != '\r') {
      *pcVar2 = cVar1;
      pcVar5 = pcVar5 + 1;
      pcVar2 = pcVar2 + 1;
      cVar1 = *pcVar5;
    }
    *pcVar2 = '\0';
    iVar4 = *param_2 + 1;
    *param_2 = iVar4;
    pcVar5 = pcVar5 + 2;
    cVar1 = *pcVar5;
  }
  RShellMemoryFree(pcVar3);
  return;
}
