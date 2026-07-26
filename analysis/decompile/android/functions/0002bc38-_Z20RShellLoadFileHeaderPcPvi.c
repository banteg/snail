/*
 * mangled: _Z20RShellLoadFileHeaderPcPvi
 * demangled: RShellLoadFileHeader(char*, void*, int)
 * address: 0002bc38
 * size: 692
 */

/* RShellLoadFileHeader(char*, void*, int) */

void RShellLoadFileHeader(char *param_1,void *param_2,int param_3)

{
  char cVar1;
  char *pcVar2;
  long lVar3;
  FILE *__stream;
  char *pcVar4;
  char cVar5;
  int iVar6;
  int iVar7;
  char acStack_22c [512];
  int local_2c;

  local_2c = __stack_chk_guard;
  cRLoadingBar::Signal((cRLoadingBar *)&gLoadingBar);
  if ((gDat != (int *)0x0) && (0 < *gDat)) {
    iVar6 = 0;
    iVar7 = 0;
    do {
      pcVar2 = *(char **)((int)gDat + iVar6 + 4);
      cVar1 = *pcVar2;
      pcVar4 = param_1;
      if (cVar1 == '\0') {
LAB_0002bd1c:
        if (*pcVar4 == '\0') {
          if (param_2 == (void *)0xffffffff) {
            param_2 = (void *)gDat[iVar7 * 6 + 2];
          }
          else if (param_2 == (void *)0x0) {
            param_2 = (void *)RShellMemoryMalloc(param_3,param_1);
            lVar3 = ftell(gDatFP);
            fseek(gDatFP,gDat[iVar7 * 6 + 2] - lVar3,1);
            fread(param_2,1,param_3,gDatFP);
            RShellUnScrambleDat(gDat[iVar7 * 6 + 2],param_2,param_3);
          }
          else {
            lVar3 = ftell(gDatFP);
            fseek(gDatFP,gDat[iVar7 * 6 + 2] - lVar3,1);
            fread(param_2,1,param_3,gDatFP);
            RShellUnScrambleDat(gDat[iVar7 * 6 + 2],param_2,param_3);
          }
          goto LAB_0002bdf0;
        }
      }
      else {
        cVar5 = *param_1;
        while (cVar5 != '\0') {
          if ((byte)(cVar5 + 0x9fU) < 0x1a) {
            cVar5 = cVar5 + -0x20;
          }
          if (cVar5 != cVar1) {
            if (cVar1 == '\0') goto LAB_0002bd1c;
            break;
          }
          cVar1 = pcVar2[1];
          pcVar4 = pcVar4 + 1;
          if (cVar1 == '\0') goto LAB_0002bd1c;
          pcVar2 = pcVar2 + 1;
          cVar5 = *pcVar4;
        }
      }
      iVar7 = iVar7 + 1;
      iVar6 = iVar6 + 0x18;
    } while (iVar7 < *gDat);
  }
  __stream = fopen(param_1,"rb");
  if (__stream == (FILE *)0x0) {
    getcwd(acStack_22c,0x200);
    RShellPrintText("WARNING:Cannot find file : %s (from %s)\n",param_1,acStack_22c);
    param_2 = (char *)0x0;
  }
  else {
    RShellGetFileSize((__sFILE *)__stream);
    if (0xfffffffd < (int)param_2 - 1U) {
      param_2 = (void *)RShellMemoryMalloc(param_3,param_1);
    }
    fread(param_2,1,param_3,__stream);
    fclose(__stream);
  }
LAB_0002bdf0:
  if (local_2c != __stack_chk_guard) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(param_2);
  }
  return;
}
