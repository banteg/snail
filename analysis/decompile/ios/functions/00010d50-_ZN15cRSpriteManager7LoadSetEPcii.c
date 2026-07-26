/*
 * mangled: _ZN15cRSpriteManager7LoadSetEPcii
 * demangled: cRSpriteManager::LoadSet(char*, int, int)
 * address: 00010d50
 * size: 880
 */

/* cRSpriteManager::LoadSet(char*, int, int) */

void __thiscall
cRSpriteManager::LoadSet(cRSpriteManager *this,char *param_1,int param_2,int param_3)

{
  char cVar1;
  size_t sVar2;
  char *pcVar3;
  char *pcVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  char *pcVar9;
  int iVar10;
  double dVar11;
  undefined4 local_68;
  char acStack_64 [64];
  int local_24;

  Load(this,param_1,param_2,param_3);
  this[0x2af9c] = SUB41(param_2,0);
  sVar2 = _strlen(param_1);
  local_68 = (uint)(param_1[sVar2 - 1] == 'r');
  if (this[0x2af94] == (cRSpriteManager)0x0) {
    this[0x2af94] = (cRSpriteManager)0x1;
    _sprintf(acStack_64,param_1);
    sVar2 = _strlen(acStack_64);
    acStack_64[sVar2 - 3] = '\0';
    _strcat(acStack_64,"txt");
    pcVar3 = (char *)RShellLoadFile(acStack_64,&local_24);
    pcVar3[local_24 + -1] = '\0';
    cVar1 = *pcVar3;
    pcVar4 = pcVar3;
    while (cVar1 != ':') {
      pcVar4 = pcVar4 + 1;
      cVar1 = *pcVar4;
    }
    iVar5 = _atoi(pcVar4 + 1);
    *(int *)(this + 0x2af98) = iVar5;
    pcVar4 = (char *)Rstrnewline(pcVar4 + 1);
    uVar6 = RShellMemoryMalloc(*(int *)(this + 0x2af98) * 0x58,"Sprite Set");
    *(undefined4 *)(this + 0x2afa0) = uVar6;
    if (0 < *(int *)(this + 0x2af98)) {
      iVar10 = 0;
      iVar5 = 0;
      do {
        pcVar9 = (char *)(iVar5 + *(int *)(this + 0x2afa0));
        _memcpy((void *)(iVar5 + *(int *)(this + 0x2afa0)),"Sprites/",9);
        sVar2 = _strlen(pcVar9);
        cVar1 = *pcVar4;
        pcVar9 = pcVar9 + sVar2;
        while (cVar1 != ' ') {
          *pcVar9 = cVar1;
          pcVar4 = pcVar4 + 1;
          pcVar9 = pcVar9 + 1;
          cVar1 = *pcVar4;
        }
        *pcVar9 = '\0';
        iVar8 = *(int *)(this + 0x2afa0);
        pcVar9 = pcVar4 + 1;
        iVar7 = _atoi(pcVar4 + 1);
        *(int *)(iVar5 + iVar8 + 0x40) = iVar7;
        cVar1 = pcVar4[1];
        while (cVar1 != ' ') {
          pcVar9 = pcVar9 + 1;
          cVar1 = *pcVar9;
        }
        iVar8 = *(int *)(this + 0x2afa0);
        pcVar4 = pcVar9 + 1;
        iVar7 = _atoi(pcVar9 + 1);
        *(int *)(iVar5 + iVar8 + 0x44) = iVar7;
        cVar1 = pcVar9[1];
        while (cVar1 != ' ') {
          pcVar4 = pcVar4 + 1;
          cVar1 = *pcVar4;
        }
        iVar7 = *(int *)(this + 0x2afa0);
        pcVar9 = pcVar4 + 1;
        dVar11 = _atof(pcVar4 + 1);
        *(float *)(iVar5 + iVar7 + 0x48) =
             (float)(double)(((ulonglong)dVar11 & 0xffffffff00000000) +
                            ((ulonglong)dVar11 & 0xffffffff));
        cVar1 = pcVar4[1];
        while (cVar1 != ' ') {
          pcVar9 = pcVar9 + 1;
          cVar1 = *pcVar9;
        }
        pcVar9 = pcVar9 + 1;
        if (local_68 == 0) {
          iVar7 = *(int *)(this + 0x2afa0);
          dVar11 = _atof(pcVar9);
          *(float *)(iVar5 + iVar7 + 0x4c) =
               (float)(double)(((ulonglong)dVar11 & 0xffffffff00000000) +
                              ((ulonglong)dVar11 & 0xffffffff));
        }
        else {
          iVar7 = *(int *)(this + 0x2afa0);
          dVar11 = _atof(pcVar9);
          *(float *)(iVar5 + iVar7 + 0x4c) =
               1.0 - (float)(double)(((ulonglong)dVar11 & 0xffffffff00000000) +
                                    ((ulonglong)dVar11 & 0xffffffff));
        }
        cVar1 = *pcVar9;
        while (cVar1 != ' ') {
          pcVar9 = pcVar9 + 1;
          cVar1 = *pcVar9;
        }
        iVar7 = *(int *)(this + 0x2afa0);
        pcVar4 = pcVar9 + 1;
        dVar11 = _atof(pcVar9 + 1);
        *(float *)(iVar5 + iVar7 + 0x50) =
             (float)(double)(((ulonglong)dVar11 & 0xffffffff00000000) +
                            ((ulonglong)dVar11 & 0xffffffff));
        cVar1 = pcVar9[1];
        while (cVar1 != ' ') {
          pcVar4 = pcVar4 + 1;
          cVar1 = *pcVar4;
        }
        pcVar4 = pcVar4 + 1;
        if (local_68 == 0) {
          iVar7 = *(int *)(this + 0x2afa0);
          dVar11 = _atof(pcVar4);
          *(float *)(iVar5 + iVar7 + 0x54) =
               (float)(double)(((ulonglong)dVar11 & 0xffffffff00000000) +
                              ((ulonglong)dVar11 & 0xffffffff));
        }
        else {
          iVar7 = *(int *)(this + 0x2afa0);
          dVar11 = _atof(pcVar4);
          *(float *)(iVar5 + iVar7 + 0x54) =
               1.0 - (float)(double)(((ulonglong)dVar11 & 0xffffffff00000000) +
                                    ((ulonglong)dVar11 & 0xffffffff));
        }
        pcVar4 = (char *)Rstrnewline(pcVar4);
        iVar10 = iVar10 + 1;
        iVar7 = iVar5 + *(int *)(this + 0x2afa0);
        iVar5 = iVar5 + 0x58;
        wprintf("Sprite Set %s %f %f %f %f\n",iVar7,SUB84((double)*(float *)(iVar7 + 0x48),0),
                (int)((ulonglong)(double)*(float *)(iVar7 + 0x48) >> 0x20),
                (double)*(float *)(iVar7 + 0x4c),(double)*(float *)(iVar7 + 0x50),
                (double)*(float *)(iVar7 + 0x54));
      } while (iVar10 < *(int *)(this + 0x2af98));
    }
    RShellMemoryFree(pcVar3);
  }
  return;
}
