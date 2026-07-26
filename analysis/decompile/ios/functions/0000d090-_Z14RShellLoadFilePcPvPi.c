/*
 * mangled: _Z14RShellLoadFilePcPvPi
 * demangled: RShellLoadFile(char*, void*, int*)
 * address: 0000d090
 * size: 860
 */

/* RShellLoadFile(char*, void*, int*) */

void * RShellLoadFile(char *param_1,void *param_2,int *param_3)

{
  char *pcVar1;
  void *pvVar2;
  long lVar3;
  int iVar4;
  char *pcVar5;
  int iVar6;
  char cVar7;
  int iVar8;
  int *piVar9;
  char cVar10;
  int iVar11;
  char local_a4 [128];
  int local_24;

  wprintf("FileName %s\n",param_1);
  cRLoadingBar::Signal((cRLoadingBar *)PTR__gLoadingBar_001b60bc);
  if (_gDat != (int *)0x0) {
    if (0 < *_gDat) {
      iVar8 = 0;
      piVar9 = _gDat;
      do {
        pcVar5 = (char *)piVar9[1];
        cVar10 = *pcVar5;
        pcVar1 = param_1;
        if (cVar10 == '\0') {
LAB_0000d200:
          if (*pcVar1 == '\0') {
            if (param_3 != (int *)0x0) {
              *param_3 = _gDat[(iVar8 + 1) * 3];
            }
            if (param_2 == (void *)0xffffffff) {
              return (void *)_gDat[iVar8 * 3 + 2];
            }
            if (param_2 == (void *)0x0) {
              iVar11 = iVar8 + 1;
              pvVar2 = _malloc(_gDat[iVar11 * 3]);
              lVar3 = _ftell(_gDatFP);
              _fseek(_gDatFP,_gDat[iVar8 * 3 + 2] - lVar3,1);
              _fread(pvVar2,1,_gDat[iVar11 * 3],_gDatFP);
              iVar6 = _gDat[iVar8 * 3 + 2];
              iVar8 = _gDat[iVar11 * 3];
              if (iVar6 + iVar8 <= iVar6) {
                return pvVar2;
              }
              iVar11 = 0;
              cVar10 = '\0';
              iVar4 = iVar6;
              do {
                cVar7 = (char)iVar4;
                iVar4 = iVar4 + 1;
                *(byte *)(iVar11 + (int)pvVar2) =
                     *(byte *)(iVar11 + (int)pvVar2) ^ cVar7 * cVar7 ^
                     cVar10 + (char)(iVar6 << 1) + (char)iVar6;
                cVar10 = cVar10 + '\x03';
                iVar11 = iVar11 + 1;
              } while (iVar4 < iVar6 + iVar8);
              return pvVar2;
            }
            lVar3 = _ftell(_gDatFP);
            _fseek(_gDatFP,_gDat[iVar8 * 3 + 2] - lVar3,1);
            _fread(param_2,1,_gDat[(iVar8 + 1) * 3],_gDatFP);
            iVar11 = _gDat[iVar8 * 3 + 2];
            iVar8 = _gDat[(iVar8 + 1) * 3];
            if (iVar11 + iVar8 <= iVar11) {
              return param_2;
            }
            cVar10 = '\0';
            iVar4 = 0;
            iVar6 = iVar11;
            do {
              cVar7 = (char)iVar6;
              iVar6 = iVar6 + 1;
              *(byte *)(iVar4 + (int)param_2) =
                   *(byte *)(iVar4 + (int)param_2) ^ cVar7 * cVar7 ^
                   cVar10 + (char)(iVar11 << 1) + (char)iVar11;
              cVar10 = cVar10 + '\x03';
              iVar4 = iVar4 + 1;
            } while (iVar6 < iVar11 + iVar8);
            return param_2;
          }
        }
        else {
          cVar7 = *param_1;
          while (cVar7 != '\0') {
            if ((byte)(cVar7 + 0x9fU) < 0x1a) {
              cVar7 = cVar7 + -0x20;
            }
            if (cVar10 != cVar7) break;
            cVar10 = pcVar5[1];
            pcVar1 = pcVar1 + 1;
            if (cVar10 == '\0') goto LAB_0000d200;
            pcVar5 = pcVar5 + 1;
            cVar7 = *pcVar1;
          }
        }
        iVar8 = iVar8 + 1;
        piVar9 = piVar9 + 3;
      } while (iVar8 != *_gDat);
    }
    wprintf("FileMissing from gDat %s\n",param_1);
  }
  cVar10 = *param_1;
  pcVar5 = local_a4;
  while (cVar10 != '\0') {
    if (cVar10 == '/') {
      *pcVar5 = '_';
    }
    else {
      *pcVar5 = cVar10;
      if ((byte)(cVar10 + 0xbfU) < 0x1a) {
        *pcVar5 = cVar10 + ' ';
      }
    }
    param_1 = param_1 + 1;
    pcVar5 = pcVar5 + 1;
    cVar10 = *param_1;
  }
  *pcVar5 = '\0';
  pvVar2 = (void *)MacLoadFile(local_a4,param_2,&local_24);
  if (param_3 != (int *)0x0) {
    *param_3 = local_24;
  }
  return pvVar2;
}
