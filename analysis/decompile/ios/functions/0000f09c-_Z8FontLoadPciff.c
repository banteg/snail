/*
 * mangled: _Z8FontLoadPciff
 * demangled: FontLoad(char*, int, float, float)
 * address: 0000f09c
 * size: 904
 */

/* FontLoad(char*, int, float, float) */

void FontLoad(char *param_1,int param_2,float param_3,float param_4)

{
  int iVar1;
  size_t sVar2;
  char *pcVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint in_fpscr;
  undefined4 uVar7;
  longlong lVar8;
  float fVar9;
  double dVar10;
  undefined4 local_230;
  char acStack_22c [512];
  int local_2c [3];

  lVar8 = (ulonglong)(uint)param_4 << 0x20;
  if (_FontCount == 1) {
    RShellError("Too many Fonts RFONT_FONT_MAX in font.h");
  }
  _strcpy(acStack_22c,param_1);
  sVar2 = _strlen(acStack_22c);
  iVar6 = 0;
  acStack_22c[sVar2 - 3] = '\0';
  _strcat(acStack_22c,"txt");
  local_230 = (char *)RShellLoadFile(acStack_22c,local_2c);
  local_230[local_2c[0] + -1] = '\0';
  pcVar3 = (char *)Rstrfind("SetNumber:",local_230);
  pcVar3 = (char *)Rstrscan(pcVar3,':');
  iVar4 = _atoi(pcVar3);
  if (0 < iVar4) {
    do {
      uVar7 = (undefined4)((ulonglong)lVar8 >> 0x20);
      pcVar3 = (char *)Rstrnewline(pcVar3);
      pcVar3 = (char *)Rstrscan(pcVar3,' ');
      iVar1 = _FontCount;
      iVar6 = iVar6 + 1;
      lVar8 = CONCAT44(uVar7,0x3f800000);
      iVar5 = _atoi(pcVar3);
      uVar7 = VectorSignedToFloat(iVar5,(byte)(in_fpscr >> 0x16) & 3);
      *(undefined4 *)(&DAT_0026f01c + (iVar1 * 0x28a + iVar6) * 4) = uVar7;
      pcVar3 = (char *)Rstrscan(pcVar3,' ');
      iVar1 = _FontCount;
      iVar5 = _atoi(pcVar3);
      uVar7 = VectorSignedToFloat(iVar5,(byte)(in_fpscr >> 0x16) & 3);
      *(undefined4 *)(&DAT_0026f21c + iVar1 * 0xa28) = uVar7;
      pcVar3 = (char *)Rstrscan(pcVar3,' ');
      iVar1 = _FontCount;
      dVar10 = _atof(pcVar3);
      *(float *)(&DAT_0026e81c + (iVar1 * 0x28a + iVar6) * 4) =
           (float)(double)(((ulonglong)dVar10 & 0xffffffff00000000) +
                          ((ulonglong)dVar10 & 0xffffffff));
      pcVar3 = (char *)Rstrscan(pcVar3,' ');
      iVar1 = _FontCount;
      dVar10 = _atof(pcVar3);
      *(float *)(&DAT_0026ee1c + (iVar1 * 0x28a + iVar6) * 4) =
           (float)lVar8 -
           (float)(double)(((ulonglong)dVar10 & 0xffffffff00000000) +
                          ((ulonglong)dVar10 & 0xffffffff));
      pcVar3 = (char *)Rstrscan(pcVar3,' ');
      iVar1 = _FontCount;
      dVar10 = _atof(pcVar3);
      *(float *)(&DAT_0026ec1c + (iVar1 * 0x28a + iVar6) * 4) =
           (float)(double)(((ulonglong)dVar10 & 0xffffffff00000000) +
                          ((ulonglong)dVar10 & 0xffffffff));
      pcVar3 = (char *)Rstrscan(pcVar3,' ');
      iVar1 = _FontCount;
      dVar10 = _atof(pcVar3);
      *(float *)(&DAT_0026ea1c + (iVar1 * 0x28a + iVar6) * 4) =
           (float)lVar8 -
           (float)(double)(((ulonglong)dVar10 & 0xffffffff00000000) +
                          ((ulonglong)dVar10 & 0xffffffff));
    } while (iVar6 != iVar4);
  }
  fVar9 = (float)((ulonglong)lVar8 >> 0x20);
  iVar6 = _FontCount * 0xa28;
  *(int *)(&_RFont + iVar6) = iVar4 + 1;
  *(undefined4 *)(&DAT_0026f0f0 + iVar6) = *(undefined4 *)(&DAT_0026f06c + iVar6);
  *(int *)(&DAT_0026f234 + iVar6) = param_2;
  uVar7 = cRTextures::Add((cRTextures *)PTR__gTextureList_001b61d0,param_1,(cTgaHeader *)0x0,0);
  *(undefined4 *)(&DAT_0026e818 + iVar6) = uVar7;
  iVar6 = _FontCount;
  iVar4 = _FontCount * 0xa28;
  **(uint **)(&DAT_0026e818 + iVar4) = **(uint **)(&DAT_0026e818 + iVar4) | 0x20400;
  *(undefined4 *)(&DAT_0026f228 + iVar4) = 0x3f800000;
  *(undefined4 *)(&DAT_0026f22c + iVar4) = 0x3f800000;
  *(float *)(&DAT_0026f230 + iVar4) = fVar9;
  (&DAT_0026f238)[iVar6 * 0x28a] = 0x3fc00000;
  *(float *)(&DAT_0026f21c + iVar4) = *(float *)(&DAT_0026f21c + iVar4) * fVar9 * 0.95;
  RShellMemoryFree(local_230);
  _FontCount = _FontCount + 1;
  return;
}
