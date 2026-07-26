/*
 * mangled: _Z11PfmLoadFilePcPvPi
 * demangled: PfmLoadFile(char*, void*, int*)
 * address: 000251a0
 * size: 152
 */

/* PfmLoadFile(char*, void*, int*) */

void * PfmLoadFile(char *param_1,void *param_2,int *param_3)

{
  int iVar1;

  wprintf("PfmLoadFile1 %s",param_1);
  iVar1 = JAVACFindFile(param_1);
  if (iVar1 == 0) {
    wprintf("PfmLoadFile Not found %s",param_1);
    if (param_3 != (int *)0x0) {
      *param_3 = 0;
    }
    param_2 = (void *)0x0;
  }
  else {
    if (param_2 == (void *)0x0) {
      iVar1 = JAVACFileSize(param_1);
      param_2 = (void *)RShellMemoryMalloc(iVar1,param_1);
    }
    iVar1 = JAVACLoadFile(param_1,param_2);
    if (param_3 != (int *)0x0) {
      *param_3 = iVar1;
    }
  }
  return param_2;
}
