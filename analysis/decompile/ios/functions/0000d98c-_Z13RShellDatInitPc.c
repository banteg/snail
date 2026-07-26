/*
 * mangled: _Z13RShellDatInitPc
 * demangled: RShellDatInit(char*)
 * address: 0000d98c
 * size: 408
 */

/* RShellDatInit(char*) */

undefined4 RShellDatInit(char *param_1)

{
  char cVar1;
  char *pcVar2;
  byte bVar3;
  char *pcVar4;
  int iVar5;
  int *piVar6;
  size_t sVar7;
  int iVar8;
  char local_114 [128];
  byte abStack_94 [8];
  size_t local_8c;

  _gDat = (int *)0x0;
  cVar1 = *param_1;
  pcVar4 = param_1;
  pcVar2 = local_114;
  while (cVar1 != '\0') {
    if (cVar1 == '/') {
      *pcVar2 = '_';
    }
    else {
      *pcVar2 = cVar1;
      if ((byte)(cVar1 + 0xbfU) < 0x1a) {
        *pcVar2 = cVar1 + ' ';
      }
    }
    pcVar4 = pcVar4 + 1;
    pcVar2 = pcVar2 + 1;
    cVar1 = *pcVar4;
  }
  *pcVar2 = '\0';
  iVar5 = MacFindFile(local_114);
  if (iVar5 == 0) {
    _gDat = (int *)0x0;
  }
  else {
    RShellLoadFileHeader(param_1,abStack_94,0x7c);
    iVar5 = 1;
    bVar3 = 3;
    do {
      abStack_94[iVar5] = abStack_94[iVar5] ^ bVar3 ^ (char)iVar5 * (char)iVar5;
      iVar5 = iVar5 + 1;
      bVar3 = bVar3 + 3;
    } while (iVar5 != 0x7c);
    piVar6 = _malloc(local_8c);
    RShellLoadFileHeader(param_1,piVar6,local_8c);
    if (0 < (int)local_8c) {
      sVar7 = 0;
      bVar3 = 0;
      do {
        *(byte *)(sVar7 + (int)piVar6) =
             *(byte *)(sVar7 + (int)piVar6) ^ bVar3 ^ (char)sVar7 * (char)sVar7;
        sVar7 = sVar7 + 1;
        bVar3 = bVar3 + 3;
      } while (sVar7 != local_8c);
    }
    _gDat = piVar6;
    if (0 < *piVar6) {
      iVar5 = 0;
      do {
        iVar8 = iVar5 + 1;
        _gDat[iVar5 * 3 + 1] = (int)_gDat + _gDat[iVar5 * 3 + 1];
        iVar5 = iVar8;
      } while (iVar8 < *_gDat);
    }
    _gDatFP = _fopen(param_1,"rb");
  }
  return 1;
}
