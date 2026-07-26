/*
 * mangled: _Z8LoadFilePcPvPi
 * demangled: LoadFile(char*, void*, int*)
 * address: 00009790
 * size: 212
 */

/* LoadFile(char*, void*, int*) */

void * LoadFile(char *param_1,void *param_2,int *param_3)

{
  FILE *pFVar1;
  long lVar2;
  size_t sVar3;
  char acStack_21c [512];

  pFVar1 = _fopen(param_1,"rb");
  if (pFVar1 == (FILE *)0x0) {
    _getcwd(acStack_21c,0x200);
    _printf("WARNING:Cannot find file : %s (from %s)\n",param_1,acStack_21c);
    param_2 = (void *)0x0;
  }
  else {
    lVar2 = _ftell(pFVar1);
    _fseek(pFVar1,0,2);
    sVar3 = _ftell(pFVar1);
    _fseek(pFVar1,lVar2,0);
    if (param_2 == (void *)0x0) {
      param_2 = _malloc(sVar3);
    }
    _fread(param_2,1,sVar3,pFVar1);
    _fclose(pFVar1);
    if (param_3 != (int *)0x0) {
      *param_3 = sVar3;
    }
  }
  return param_2;
}
