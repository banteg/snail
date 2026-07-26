/*
 * mangled: _Z8FontLoadPciff
 * demangled: FontLoad(char*, int, float, float)
 * address: 00032d78
 * size: 912
 */

/* FontLoad(char*, int, float, float) */

void FontLoad(char *param_1,int param_2,float param_3,float param_4)

{
  size_t sVar1;
  char *pcVar2;
  char *pcVar3;
  int iVar4;
  int iVar5;
  undefined4 extraout_r0;
  undefined4 extraout_r0_00;
  undefined4 extraout_r0_01;
  undefined4 extraout_r0_02;
  int iVar6;
  undefined4 extraout_r1;
  undefined4 extraout_r1_00;
  undefined4 extraout_r1_01;
  undefined4 extraout_r1_02;
  float in_r3;
  int iVar7;
  int iVar8;
  uint in_fpscr;
  undefined4 uVar9;
  undefined4 local_238;
  char acStack_234 [512];
  int local_34;

  local_34 = __stack_chk_guard;
  if (FontCount == 1) {
    RShellError("Too many Fonts RFONT_FONT_MAX in font.h",param_3);
  }
  strcpy(acStack_234,param_1);
  sVar1 = strlen(acStack_234);
  iVar7 = 0;
  acStack_234[sVar1 - 3] = '\0';
  sVar1 = strlen(acStack_234);
  memcpy(acStack_234 + sVar1,"txt",4);
  pcVar2 = (char *)RShellLoadFile(acStack_234,&local_238);
  pcVar2[local_238 + -1] = '\0';
  pcVar3 = (char *)Rstrfind("SetNumber:",pcVar2);
  pcVar3 = (char *)Rstrscan(pcVar3,':');
  iVar4 = atoi(pcVar3);
  if (0 < iVar4) {
    do {
      iVar7 = iVar7 + 1;
      pcVar3 = (char *)Rstrnewline(pcVar3);
      pcVar3 = (char *)Rstrscan(pcVar3,' ');
      iVar6 = FontCount * 0x28a;
      iVar5 = atoi(pcVar3);
      uVar9 = VectorSignedToFloat(iVar5,(byte)(in_fpscr >> 0x16) & 3);
      *(undefined4 *)(RFont + (iVar6 + iVar7 + 0x202) * 4) = uVar9;
      pcVar3 = (char *)Rstrscan(pcVar3,' ');
      iVar6 = FontCount;
      iVar5 = atoi(pcVar3);
      uVar9 = VectorSignedToFloat(iVar5,(byte)(in_fpscr >> 0x16) & 3);
      *(undefined4 *)(RFont + iVar6 * 0xa28 + 0xa08) = uVar9;
      pcVar3 = (char *)Rstrscan(pcVar3,' ');
      iVar6 = FontCount * 0x28a;
      strtod(pcVar3,(char **)0x0);
      *(float *)(RFont + (iVar6 + iVar7 + 2) * 4) = (float)(double)CONCAT44(extraout_r1,extraout_r0)
      ;
      pcVar3 = (char *)Rstrscan(pcVar3,' ');
      iVar6 = FontCount * 0x28a;
      strtod(pcVar3,(char **)0x0);
      *(float *)(RFont + (iVar6 + iVar7 + 0x182) * 4) =
           1.0 - (float)(double)CONCAT44(extraout_r1_00,extraout_r0_00);
      pcVar3 = (char *)Rstrscan(pcVar3,' ');
      iVar6 = FontCount * 0x28a;
      strtod(pcVar3,(char **)0x0);
      *(float *)(RFont + (iVar6 + iVar7 + 0x102) * 4) =
           (float)(double)CONCAT44(extraout_r1_01,extraout_r0_01);
      pcVar3 = (char *)Rstrscan(pcVar3,' ');
      iVar6 = FontCount * 0x28a;
      strtod(pcVar3,(char **)0x0);
      *(float *)(RFont + (iVar6 + iVar7 + 0x82) * 4) =
           1.0 - (float)(double)CONCAT44(extraout_r1_02,extraout_r0_02);
    } while (iVar7 < iVar4);
  }
  iVar6 = FontASCIIRemap(' ');
  iVar7 = FontCount;
  iVar5 = FontASCIIRemap('t');
  iVar8 = FontCount * 0xa28;
  *(int *)(RFont + iVar8) = iVar4 + 1;
  *(int *)(RFont + iVar8 + 0xa20) = param_2;
  *(undefined4 *)(RFont + (iVar7 * 0x28a + iVar6 + 0x202) * 4) =
       *(undefined4 *)(RFont + (iVar7 * 0x28a + iVar5 + 0x202) * 4);
  uVar9 = cRTextures::Add((cRTextures *)gTextureList,param_1,(cTgaHeader *)0x0,0);
  iVar4 = FontCount * 0xa28;
  *(undefined4 *)(RFont + iVar4 + 0xa24) = 0x3fc00000;
  *(undefined4 *)(RFont + iVar4 + 0xa18) = 0x3f800000;
  *(undefined4 *)(RFont + iVar4 + 0xa14) = 0x3f800000;
  *(float *)(RFont + iVar4 + 0xa1c) = in_r3;
  *(float *)(RFont + iVar4 + 0xa08) = *(float *)(RFont + iVar4 + 0xa08) * in_r3 * 0.95;
  *(undefined4 *)(RFont + iVar8 + 4) = uVar9;
  **(uint **)(RFont + iVar4 + 4) = **(uint **)(RFont + iVar4 + 4) | 0x20400;
  RShellMemoryFree(pcVar2);
  iVar4 = FontCount;
  FontCount = FontCount + 1;
  if (local_34 != __stack_chk_guard) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(iVar4);
  }
  return;
}
