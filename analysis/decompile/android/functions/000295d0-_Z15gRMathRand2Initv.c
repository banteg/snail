/*
 * mangled: _Z15gRMathRand2Initv
 * demangled: gRMathRand2Init()
 * address: 000295d0
 * size: 168
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* gRMathRand2Init() */

void gRMathRand2Init(void)

{
  int iVar1;
  long lVar2;

  wprintf("RAND_MAX=%i\n",0x7fffffff);
  iVar1 = RShellFindFile("RandTable.bin",false);
  if (iVar1 == 0) {
    iVar1 = 0;
    do {
      lVar2 = lrand48();
      *(short *)(gRMathRand2Table + iVar1) = (short)lVar2;
      iVar1 = iVar1 + 2;
    } while (iVar1 != 0x3ffe);
    RShellSaveFile("RandTable.bin",gRMathRand2Table,0x3ffe);
  }
  else {
    wprintf("Loading RandTable\n");
    RShellLoadFile("RandTable.bin",gRMathRand2Table,(int *)0x0);
  }
  gRMathRand2Index = 0;
  gRMathRandIndex = 0;
  return;
}
