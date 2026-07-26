/*
 * mangled: _ZN15cRSpriteManager8LoadAnimEPcii
 * demangled: cRSpriteManager::LoadAnim(char*, int, int)
 * address: 0003d42c
 * size: 784
 */

/* cRSpriteManager::LoadAnim(char*, int, int) */

void __thiscall
cRSpriteManager::LoadAnim(cRSpriteManager *this,char *param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint *puVar5;
  float fVar6;
  int iVar7;
  uint uVar8;
  char *pcVar9;
  int iVar10;
  int iVar11;
  char *pcVar12;
  uint in_fpscr;
  float fVar13;
  float fVar14;
  undefined4 local_230;
  char local_22c;
  char acStack_22b [511];
  int local_2c;

  iVar2 = DAT_0003d750;
  iVar10 = DAT_0003d74c + 0x3d444;
  local_2c = **(int **)(iVar10 + DAT_0003d750);
  if (199 < param_2) {
    RShellError((char *)(iVar10 + DAT_0003d760),200);
  }
  pcVar9 = &local_22c;
  Rstrcpy(pcVar9,param_1);
  iVar7 = DAT_0003d75c;
  iVar3 = DAT_0003d758;
  if (local_22c == '.') {
    pcVar12 = (char *)((int)&local_230 + 1);
  }
  else {
    do {
      pcVar12 = pcVar9;
      pcVar9 = pcVar12 + 1;
    } while (*pcVar9 != '.');
    pcVar12 = pcVar12 + -2;
  }
  if (((*pcVar12 == '0') && (pcVar12[1] == '0')) && (pcVar12[2] == '0')) {
    iVar1 = param_2 * 0x20;
    iVar11 = 0;
    while (iVar4 = RShellFindFile(&local_22c,false), iVar4 != 0) {
      if (iVar11 == 0) {
        puVar5 = (uint *)cRTextures::Add(*(cRTextures **)(iVar10 + iVar7),&local_22c,
                                         (cTgaHeader *)0x0,param_3);
        uVar8 = *puVar5;
        *(uint **)(*(int *)(iVar10 + iVar3) + iVar1 + 4) = puVar5;
        *puVar5 = uVar8 | 0x2000 | param_3;
      }
      else {
        puVar5 = (uint *)cRTextures::Add(*(cRTextures **)(iVar10 + iVar7),&local_22c,
                                         (cTgaHeader *)0x0,param_3);
        *puVar5 = *puVar5 | param_3;
      }
      iVar11 = iVar11 + 1;
      *pcVar12 = (char)(iVar11 / 100) + '0';
      pcVar12[1] = (char)((iVar11 % 100) / 10) + '0';
      pcVar12[2] = (char)iVar11 + (char)(iVar11 / 10) * -10 + '0';
    }
    iVar4 = *(int *)(iVar10 + iVar3) + iVar1;
    iVar7 = *(int *)(iVar4 + 4);
    *(undefined4 *)(iVar7 + 0x94) = DAT_0003d73c;
    *(int *)(iVar7 + 0x90) = iVar11;
    *pcVar12 = '.';
    pcVar12[1] = 't';
    pcVar12[2] = 'x';
    *pcVar9 = 't';
    pcVar12[4] = '\0';
    iVar7 = RShellFindFile(&local_22c,false);
    if (iVar7 != 0) {
      pcVar9 = (char *)RShellLoadFile(&local_22c,(int *)0x0);
      local_230 = (char *)Rstrfind((char *)(iVar10 + DAT_0003d764),pcVar9);
      if (local_230 != (char *)0x0) {
        fVar6 = (float)Rstrfloat((char **)&local_230);
        fVar13 = (float)VectorSignedToFloat(iVar11,(byte)(in_fpscr >> 0x16) & 3);
        fVar14 = DAT_0003d748;
        if (fVar6 / fVar13 != 0.0) {
          fVar14 = DAT_0003d744 / ((fVar6 / fVar13) * DAT_0003d740);
        }
        *(float *)(*(int *)(iVar4 + 4) + 0x94) = fVar14;
      }
      local_230 = (char *)Rstrfind((char *)(iVar10 + DAT_0003d768),pcVar9);
      if (local_230 != (char *)0x0) {
        puVar5 = *(uint **)(*(int *)(iVar10 + iVar3) + iVar1 + 4);
        *puVar5 = *puVar5 | 0x4000;
      }
      RShellMemoryFree(pcVar9);
    }
  }
  else {
    RShellError((char *)(iVar10 + DAT_0003d754),param_1);
  }
  if (local_2c == **(int **)(iVar10 + iVar2)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}
