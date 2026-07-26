/*
 * mangled: _ZN15cRSpriteManager7LoadSetEPcii
 * demangled: cRSpriteManager::LoadSet(char*, int, int)
 * address: 0003d99c
 * size: 960
 */

/* cRSpriteManager::LoadSet(char*, int, int) */

void __thiscall
cRSpriteManager::LoadSet(cRSpriteManager *this,char *param_1,int param_2,int param_3)

{
  char cVar1;
  char cVar2;
  float fVar3;
  int iVar4;
  size_t sVar5;
  char *pcVar6;
  int iVar7;
  undefined4 extraout_r0;
  undefined4 extraout_r0_00;
  undefined4 extraout_r0_01;
  undefined4 extraout_r0_02;
  undefined4 extraout_r0_03;
  undefined4 extraout_r0_04;
  undefined4 extraout_r1;
  undefined4 extraout_r1_00;
  undefined4 extraout_r1_01;
  undefined4 extraout_r1_02;
  undefined4 extraout_r1_03;
  undefined4 extraout_r1_04;
  void *__src;
  char *pcVar8;
  int iVar9;
  int iVar10;
  char *pcVar11;
  int iVar12;
  int iVar13;
  char *__nptr;
  undefined4 local_78;
  char acStack_74 [64];
  int local_34;

  iVar4 = DAT_0003dd64;
  iVar10 = DAT_0003dd60 + 0x3d9b8;
  local_34 = **(int **)(iVar10 + DAT_0003dd64);
  Load(this,param_1,param_2,param_3);
  this[0x2af9c] = SUB41(param_2,0);
  sVar5 = strlen(param_1);
  cVar1 = param_1[sVar5 - 1];
  if (this[0x2af94] == (cRSpriteManager)0x0) {
    this[0x2af94] = (cRSpriteManager)0x1;
    sprintf(acStack_74,param_1);
    sVar5 = strlen(acStack_74);
    acStack_74[sVar5 - 3] = '\0';
    sVar5 = strlen(acStack_74);
    memcpy(acStack_74 + sVar5,(void *)(iVar10 + DAT_0003dd68),4);
    pcVar6 = (char *)RShellLoadFile(acStack_74,&local_78);
    pcVar6[local_78 + -1] = '\0';
    cVar2 = *pcVar6;
    pcVar8 = pcVar6;
    while (cVar2 != ':') {
      pcVar8 = pcVar8 + 1;
      cVar2 = *pcVar8;
    }
    iVar7 = atoi(pcVar8 + 1);
    *(int *)(this + 0x2af98) = iVar7;
    pcVar8 = (char *)Rstrnewline(pcVar8 + 1);
    iVar7 = RShellMemoryMalloc(*(int *)(this + 0x2af98) * 0x58,(char *)(iVar10 + DAT_0003dd6c));
    *(int *)(this + 0x2afa0) = iVar7;
    fVar3 = DAT_0003dd5c;
    if (0 < *(int *)(this + 0x2af98)) {
      iVar9 = 0;
      iVar13 = 0;
      __src = (void *)(iVar10 + DAT_0003dd70);
      while( true ) {
        pcVar11 = (char *)(iVar7 + iVar9);
        memcpy(pcVar11,__src,9);
        sVar5 = strlen(pcVar11);
        cVar2 = *pcVar8;
        pcVar11 = pcVar11 + sVar5;
        while (cVar2 != ' ') {
          *pcVar11 = cVar2;
          pcVar8 = pcVar8 + 1;
          pcVar11 = pcVar11 + 1;
          cVar2 = *pcVar8;
        }
        __nptr = pcVar8 + 1;
        *pcVar11 = '\0';
        iVar12 = *(int *)(this + 0x2afa0);
        iVar7 = atoi(__nptr);
        *(int *)(iVar12 + iVar9 + 0x40) = iVar7;
        cVar2 = pcVar8[1];
        while (cVar2 != ' ') {
          __nptr = __nptr + 1;
          cVar2 = *__nptr;
        }
        pcVar8 = __nptr + 1;
        iVar12 = *(int *)(this + 0x2afa0);
        iVar7 = atoi(pcVar8);
        *(int *)(iVar12 + iVar9 + 0x44) = iVar7;
        cVar2 = __nptr[1];
        while (cVar2 != ' ') {
          pcVar8 = pcVar8 + 1;
          cVar2 = *pcVar8;
        }
        pcVar11 = pcVar8 + 1;
        iVar7 = *(int *)(this + 0x2afa0);
        strtod(pcVar11,(char **)0x0);
        *(float *)(iVar7 + iVar9 + 0x48) = (float)(double)CONCAT44(extraout_r1,extraout_r0);
        cVar2 = pcVar8[1];
        while (cVar2 != ' ') {
          pcVar11 = pcVar11 + 1;
          cVar2 = *pcVar11;
        }
        pcVar11 = pcVar11 + 1;
        if (cVar1 != 'r') {
          iVar7 = *(int *)(this + 0x2afa0);
          strtod(pcVar11,(char **)0x0);
          *(float *)(iVar7 + iVar9 + 0x4c) = (float)(double)CONCAT44(extraout_r1_03,extraout_r0_03);
        }
        else {
          iVar7 = *(int *)(this + 0x2afa0);
          strtod(pcVar11,(char **)0x0);
          *(float *)(iVar7 + iVar9 + 0x4c) =
               fVar3 - (float)(double)CONCAT44(extraout_r1_00,extraout_r0_00);
        }
        cVar2 = *pcVar11;
        while (cVar2 != ' ') {
          pcVar11 = pcVar11 + 1;
          cVar2 = *pcVar11;
        }
        pcVar8 = pcVar11 + 1;
        iVar7 = *(int *)(this + 0x2afa0);
        strtod(pcVar8,(char **)0x0);
        *(float *)(iVar7 + iVar9 + 0x50) = (float)(double)CONCAT44(extraout_r1_01,extraout_r0_01);
        cVar2 = pcVar11[1];
        while (cVar2 != ' ') {
          pcVar8 = pcVar8 + 1;
          cVar2 = *pcVar8;
        }
        pcVar8 = pcVar8 + 1;
        if (cVar1 != 'r') {
          iVar7 = *(int *)(this + 0x2afa0);
          strtod(pcVar8,(char **)0x0);
          *(float *)(iVar7 + iVar9 + 0x54) = (float)(double)CONCAT44(extraout_r1_04,extraout_r0_04);
        }
        else {
          iVar7 = *(int *)(this + 0x2afa0);
          strtod(pcVar8,(char **)0x0);
          *(float *)(iVar7 + iVar9 + 0x54) =
               fVar3 - (float)(double)CONCAT44(extraout_r1_02,extraout_r0_02);
        }
        iVar13 = iVar13 + 1;
        pcVar8 = (char *)Rstrnewline(pcVar8);
        iVar9 = iVar9 + 0x58;
        if (*(int *)(this + 0x2af98) <= iVar13) break;
        iVar7 = *(int *)(this + 0x2afa0);
      }
    }
    RShellMemoryFree(pcVar6);
  }
  if (local_34 != **(int **)(iVar10 + iVar4)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}
