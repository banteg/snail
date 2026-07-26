/*
 * mangled: _Z13RShellDatInitPc
 * demangled: RShellDatInit(char*)
 * address: 0002c018
 * size: 268
 */

/* RShellDatInit(char*) */

undefined4 RShellDatInit(char *param_1)

{
  int iVar1;
  int *piVar2;
  char *pcVar3;
  int iVar4;
  char acStack_114 [8];
  int local_10c;

  gDat = (int *)0x0;
  iVar1 = RShellFindFile(param_1,false);
  if (iVar1 == 0) {
    gDat = (int *)0x0;
  }
  else {
    RShellLoadFileHeader(param_1,acStack_114,0xf4);
    RShellUnScrambleDat(0,acStack_114,0xf4);
    piVar2 = (int *)RShellMemoryMalloc(local_10c,"Dat File Header");
    RShellLoadFileHeader(param_1,piVar2,local_10c);
    RShellUnScrambleDat(0,(char *)piVar2,local_10c);
    gDat = piVar2;
    cRHash::Init((cRHash *)gDatHash,*piVar2,DatHashGetString);
    iVar1 = 0;
    if (0 < *gDat) {
      do {
        iVar4 = iVar1 + 1;
        pcVar3 = (char *)((int)gDat + gDat[iVar1 * 6 + 1]);
        gDat[iVar1 * 6 + 1] = (int)pcVar3;
        cRHash::Add((cRHash *)gDatHash,pcVar3,iVar1);
        iVar1 = iVar4;
      } while (iVar4 < *gDat);
    }
  }
  return 1;
}
