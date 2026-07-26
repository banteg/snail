/*
 * mangled: _Z20RShellLoadFileHeaderPcPvi
 * demangled: RShellLoadFileHeader(char*, void*, int)
 * address: 0000d66c
 * size: 780
 */

/* RShellLoadFileHeader(char*, void*, int) */

void * RShellLoadFileHeader(char *param_1,void *param_2,int param_3)

{
  char *pcVar1;
  FILE *pFVar2;
  long lVar3;
  void *pvVar4;
  char *pcVar5;
  char cVar6;
  char cVar7;
  int iVar8;
  int *piVar9;
  int iVar10;
  int iVar11;
  char acStack_220 [512];

  cRLoadingBar::Signal((cRLoadingBar *)PTR__gLoadingBar_001b60bc);
  if ((_gDat != (int *)0x0) && (0 < *_gDat)) {
    iVar8 = 0;
    piVar9 = _gDat;
    do {
      pcVar5 = (char *)piVar9[1];
      cVar7 = *pcVar5;
      pcVar1 = param_1;
      if (cVar7 == '\0') {
LAB_0000d7b0:
        if (*pcVar1 == '\0') {
          if (param_2 == (void *)0xffffffff) {
            return (void *)_gDat[iVar8 * 3 + 2];
          }
          if (param_2 != (void *)0x0) {
            lVar3 = _ftell(_gDatFP);
            _fseek(_gDatFP,_gDat[iVar8 * 3 + 2] - lVar3,1);
            _fread(param_2,1,param_3,_gDatFP);
            iVar8 = _gDat[iVar8 * 3 + 2];
            if (param_3 + iVar8 <= iVar8) {
              return param_2;
            }
            cVar7 = '\0';
            iVar11 = 0;
            iVar10 = iVar8;
            do {
              cVar6 = (char)iVar10;
              iVar10 = iVar10 + 1;
              *(byte *)(iVar11 + (int)param_2) =
                   *(byte *)(iVar11 + (int)param_2) ^ cVar6 * cVar6 ^
                   cVar7 + (char)(iVar8 << 1) + (char)iVar8;
              cVar7 = cVar7 + '\x03';
              iVar11 = iVar11 + 1;
            } while (iVar10 < param_3 + iVar8);
            return param_2;
          }
          pvVar4 = _malloc(param_3);
          lVar3 = _ftell(_gDatFP);
          _fseek(_gDatFP,_gDat[iVar8 * 3 + 2] - lVar3,1);
          _fread(pvVar4,1,param_3,_gDatFP);
          iVar8 = _gDat[iVar8 * 3 + 2];
          if (param_3 + iVar8 <= iVar8) {
            return pvVar4;
          }
          iVar10 = 0;
          cVar7 = '\0';
          iVar11 = iVar8;
          do {
            cVar6 = (char)iVar11;
            iVar11 = iVar11 + 1;
            *(byte *)(iVar10 + (int)pvVar4) =
                 *(byte *)(iVar10 + (int)pvVar4) ^ cVar6 * cVar6 ^
                 cVar7 + (char)(iVar8 << 1) + (char)iVar8;
            cVar7 = cVar7 + '\x03';
            iVar10 = iVar10 + 1;
          } while (iVar11 < param_3 + iVar8);
          return pvVar4;
        }
      }
      else {
        cVar6 = *param_1;
        while (cVar6 != '\0') {
          if ((byte)(cVar6 + 0x9fU) < 0x1a) {
            cVar6 = cVar6 + -0x20;
          }
          if (cVar7 != cVar6) break;
          cVar7 = pcVar5[1];
          pcVar1 = pcVar1 + 1;
          if (cVar7 == '\0') goto LAB_0000d7b0;
          pcVar5 = pcVar5 + 1;
          cVar6 = *pcVar1;
        }
      }
      iVar8 = iVar8 + 1;
      piVar9 = piVar9 + 3;
    } while (iVar8 != *_gDat);
  }
  pFVar2 = _fopen(param_1,"rb");
  if (pFVar2 == (FILE *)0x0) {
    _getcwd(acStack_220,0x200);
    RShellPrintText("WARNING:Cannot find file : %s (from %s)\n",param_1,acStack_220);
    param_2 = (void *)0x0;
  }
  else {
    lVar3 = _ftell(pFVar2);
    _fseek(pFVar2,0,2);
    _ftell(pFVar2);
    _fseek(pFVar2,lVar3,0);
    if (0xfffffffd < (int)param_2 - 1U) {
      param_2 = _malloc(param_3);
    }
    _fread(param_2,1,param_3,pFVar2);
    _fclose(pFVar2);
  }
  return param_2;
}
