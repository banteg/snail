/*
 * mangled: _Z14RShellFindFilePcb
 * demangled: RShellFindFile(char*, bool)
 * address: 0000d518
 * size: 332
 */

/* RShellFindFile(char*, bool) */

undefined4 RShellFindFile(char *param_1,bool param_2)

{
  char cVar1;
  char *pcVar2;
  undefined4 uVar3;
  int *piVar4;
  char cVar5;
  int iVar6;
  char *pcVar7;
  char local_94 [128];

  if ((_gDat == (int *)0x0) || (param_2)) {
    cVar1 = *param_1;
    pcVar2 = local_94;
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
      param_1 = param_1 + 1;
      pcVar2 = pcVar2 + 1;
      cVar1 = *param_1;
    }
    *pcVar2 = '\0';
    uVar3 = MacFindFile(local_94);
  }
  else {
    iVar6 = 0;
    piVar4 = _gDat;
    if (0 < *_gDat) {
      do {
        pcVar2 = (char *)piVar4[1];
        cVar1 = *pcVar2;
        pcVar7 = param_1;
        if (cVar1 == '\0') {
LAB_0000d650:
          if (*pcVar7 == '\0') {
            return 1;
          }
        }
        else {
          cVar5 = *param_1;
          while (cVar5 != '\0') {
            if ((byte)(cVar5 + 0x9fU) < 0x1a) {
              cVar5 = cVar5 + -0x20;
            }
            if (cVar1 != cVar5) break;
            cVar1 = pcVar2[1];
            pcVar7 = pcVar7 + 1;
            if (cVar1 == '\0') goto LAB_0000d650;
            pcVar2 = pcVar2 + 1;
            cVar5 = *pcVar7;
          }
        }
        iVar6 = iVar6 + 1;
        piVar4 = piVar4 + 3;
      } while (iVar6 != *_gDat);
    }
    RShellWarning("Missing Dat File %s",param_1);
    uVar3 = 0;
  }
  return uVar3;
}
