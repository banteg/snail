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
  size_t sVar3;
  char *pcVar4;
  int iVar5;
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
  char *pcVar6;
  int iVar7;
  char *pcVar8;
  int iVar9;
  int iVar10;
  char *__nptr;
  undefined4 local_78;
  char acStack_74 [64];
  int local_34;

  local_34 = __stack_chk_guard;
  Load(this,param_1,param_2,param_3);
  this[0x2af9c] = SUB41(param_2,0);
  sVar3 = strlen(param_1);
  cVar1 = param_1[sVar3 - 1];
  if (this[0x2af94] == (cRSpriteManager)0x0) {
    this[0x2af94] = (cRSpriteManager)0x1;
    sprintf(acStack_74,param_1);
    sVar3 = strlen(acStack_74);
    acStack_74[sVar3 - 3] = '\0';
    sVar3 = strlen(acStack_74);
    memcpy(acStack_74 + sVar3,"txt",4);
    pcVar4 = (char *)RShellLoadFile(acStack_74,&local_78);
    pcVar4[local_78 + -1] = '\0';
    cVar2 = *pcVar4;
    pcVar6 = pcVar4;
    while (cVar2 != ':') {
      pcVar6 = pcVar6 + 1;
      cVar2 = *pcVar6;
    }
    iVar5 = atoi(pcVar6 + 1);
    *(int *)(this + 0x2af98) = iVar5;
    pcVar6 = (char *)Rstrnewline(pcVar6 + 1);
    iVar5 = RShellMemoryMalloc(*(int *)(this + 0x2af98) * 0x58,"Sprite Set");
    *(int *)(this + 0x2afa0) = iVar5;
    if (0 < *(int *)(this + 0x2af98)) {
      iVar7 = 0;
      iVar10 = 0;
      while( true ) {
        pcVar8 = (char *)(iVar5 + iVar7);
        memcpy(pcVar8,"Sprites/",9);
        sVar3 = strlen(pcVar8);
        cVar2 = *pcVar6;
        pcVar8 = pcVar8 + sVar3;
        while (cVar2 != ' ') {
          *pcVar8 = cVar2;
          pcVar6 = pcVar6 + 1;
          pcVar8 = pcVar8 + 1;
          cVar2 = *pcVar6;
        }
        __nptr = pcVar6 + 1;
        *pcVar8 = '\0';
        iVar9 = *(int *)(this + 0x2afa0);
        iVar5 = atoi(__nptr);
        *(int *)(iVar9 + iVar7 + 0x40) = iVar5;
        cVar2 = pcVar6[1];
        while (cVar2 != ' ') {
          __nptr = __nptr + 1;
          cVar2 = *__nptr;
        }
        pcVar6 = __nptr + 1;
        iVar9 = *(int *)(this + 0x2afa0);
        iVar5 = atoi(pcVar6);
        *(int *)(iVar9 + iVar7 + 0x44) = iVar5;
        cVar2 = __nptr[1];
        while (cVar2 != ' ') {
          pcVar6 = pcVar6 + 1;
          cVar2 = *pcVar6;
        }
        pcVar8 = pcVar6 + 1;
        iVar5 = *(int *)(this + 0x2afa0);
        strtod(pcVar8,(char **)0x0);
        *(float *)(iVar5 + iVar7 + 0x48) = (float)(double)CONCAT44(extraout_r1,extraout_r0);
        cVar2 = pcVar6[1];
        while (cVar2 != ' ') {
          pcVar8 = pcVar8 + 1;
          cVar2 = *pcVar8;
        }
        pcVar8 = pcVar8 + 1;
        if (cVar1 != 'r') {
          iVar5 = *(int *)(this + 0x2afa0);
          strtod(pcVar8,(char **)0x0);
          *(float *)(iVar5 + iVar7 + 0x4c) = (float)(double)CONCAT44(extraout_r1_03,extraout_r0_03);
        }
        else {
          iVar5 = *(int *)(this + 0x2afa0);
          strtod(pcVar8,(char **)0x0);
          *(float *)(iVar5 + iVar7 + 0x4c) =
               1.0 - (float)(double)CONCAT44(extraout_r1_00,extraout_r0_00);
        }
        cVar2 = *pcVar8;
        while (cVar2 != ' ') {
          pcVar8 = pcVar8 + 1;
          cVar2 = *pcVar8;
        }
        pcVar6 = pcVar8 + 1;
        iVar5 = *(int *)(this + 0x2afa0);
        strtod(pcVar6,(char **)0x0);
        *(float *)(iVar5 + iVar7 + 0x50) = (float)(double)CONCAT44(extraout_r1_01,extraout_r0_01);
        cVar2 = pcVar8[1];
        while (cVar2 != ' ') {
          pcVar6 = pcVar6 + 1;
          cVar2 = *pcVar6;
        }
        pcVar6 = pcVar6 + 1;
        if (cVar1 != 'r') {
          iVar5 = *(int *)(this + 0x2afa0);
          strtod(pcVar6,(char **)0x0);
          *(float *)(iVar5 + iVar7 + 0x54) = (float)(double)CONCAT44(extraout_r1_04,extraout_r0_04);
        }
        else {
          iVar5 = *(int *)(this + 0x2afa0);
          strtod(pcVar6,(char **)0x0);
          *(float *)(iVar5 + iVar7 + 0x54) =
               1.0 - (float)(double)CONCAT44(extraout_r1_02,extraout_r0_02);
        }
        iVar10 = iVar10 + 1;
        pcVar6 = (char *)Rstrnewline(pcVar6);
        iVar7 = iVar7 + 0x58;
        if (*(int *)(this + 0x2af98) <= iVar10) break;
        iVar5 = *(int *)(this + 0x2afa0);
      }
    }
    RShellMemoryFree(pcVar4);
  }
  if (local_34 != __stack_chk_guard) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}
