/*
 * mangled: _Z17gRegisterLoadFilePcPvPii
 * demangled: gRegisterLoadFile(char*, void*, int*, int)
 * address: 00031760
 * size: 40
 */

/* gRegisterLoadFile(char*, void*, int*, int) */

void gRegisterLoadFile(char *param_1,void *param_2,int *param_3,int param_4)

{
  int local_c;

  PfmLoadFile(param_1,param_2,&local_c);
  if (param_3 != (int *)0x0) {
    *param_3 = local_c;
  }
  return;
}
