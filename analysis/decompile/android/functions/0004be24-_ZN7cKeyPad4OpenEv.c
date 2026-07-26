/*
 * mangled: _ZN7cKeyPad4OpenEv
 * demangled: cKeyPad::Open()
 * address: 0004be24
 * size: 516
 */

/* cKeyPad::Open() */

void __thiscall cKeyPad::Open(cKeyPad *this)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  char *pcVar5;
  char *pcVar6;
  int iVar7;
  undefined4 uVar8;
  char *pcVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  cRSpriteManager *this_00;
  int iVar13;
  int iVar14;
  uint in_fpscr;
  float fVar15;
  undefined4 uVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  int local_34 [2];

  iVar12 = DAT_0004c038 + 0x4be40;
  iVar11 = 0;
  this_00 = *(cRSpriteManager **)(iVar12 + DAT_0004c03c);
  cRSpriteManager::GetTexture(this_00,0x8b);
  cRSpriteManager::GetTexture(this_00,0x8b);
  pcVar5 = (char *)RShellLoadFile((char *)(iVar12 + DAT_0004c040),local_34);
  iVar7 = DAT_0004c044;
  pcVar5[local_34[0] + -1] = '\0';
  pcVar6 = (char *)Rstrfind((char *)(iVar12 + iVar7),pcVar5);
  pcVar6 = (char *)Rstrscan(pcVar6,':');
  iVar7 = atoi(pcVar6);
  pcVar9 = (char *)(iVar12 + DAT_0004c048);
  *(int *)(this + 8) = iVar7;
  uVar8 = RShellMemoryMalloc(iVar7 * 0x14,pcVar9);
  *(undefined4 *)(this + 4) = uVar8;
  fVar4 = DAT_0004c034;
  fVar3 = DAT_0004c030;
  fVar2 = DAT_0004c02c;
  fVar1 = DAT_0004c028;
  if (0 < *(int *)(this + 8)) {
    iVar7 = 0;
    do {
      iVar7 = iVar7 + 1;
      pcVar6 = (char *)Rstrnewline(pcVar6);
      *(char *)(*(int *)(this + 4) + iVar11 + 0x10) = *pcVar6;
      pcVar6 = (char *)Rstrscan(pcVar6,'-');
      pcVar6 = (char *)Rstrscan(pcVar6,' ');
      iVar13 = *(int *)(this + 4);
      iVar12 = atoi(pcVar6);
      *(int *)(iVar13 + iVar11) = iVar12;
      pcVar6 = (char *)Rstrscan(pcVar6,' ');
      iVar13 = *(int *)(this + 4);
      iVar12 = atoi(pcVar6);
      *(int *)(iVar13 + iVar11 + 4) = iVar12;
      pcVar6 = (char *)Rstrscan(pcVar6,' ');
      iVar13 = *(int *)(this + 4);
      iVar12 = atoi(pcVar6);
      *(int *)(iVar13 + iVar11 + 8) = iVar12;
      pcVar6 = (char *)Rstrscan(pcVar6,' ');
      iVar14 = *(int *)(this + 4);
      iVar12 = atoi(pcVar6);
      iVar13 = *(int *)(this + 4);
      *(float *)(this + 0x14) = fVar1;
      iVar10 = iVar13 + iVar11;
      uVar16 = *(undefined4 *)(iVar10 + 8);
      uVar8 = *(undefined4 *)(iVar10 + 4);
      fVar18 = (float)VectorSignedToFloat(*(undefined4 *)(iVar13 + iVar11),
                                          (byte)(in_fpscr >> 0x16) & 3);
      *(int *)(iVar14 + iVar11 + 0xc) = iVar12;
      fVar19 = (float)VectorSignedToFloat(*(undefined4 *)(iVar10 + 0xc),(byte)(in_fpscr >> 0x16) & 3
                                         );
      fVar17 = (float)VectorSignedToFloat(uVar16,(byte)(in_fpscr >> 0x16) & 3);
      fVar15 = (float)VectorSignedToFloat(uVar8,(byte)(in_fpscr >> 0x16) & 3);
      *(int *)(iVar13 + iVar11) = (int)((fVar18 / fVar2) * fVar3);
      iVar11 = iVar11 + 0x14;
      *(int *)(iVar10 + 8) = (int)((fVar17 / fVar2) * fVar3);
      *(int *)(iVar10 + 4) = (int)(fVar1 + fVar15 * fVar4 * (fVar2 - fVar1));
      *(int *)(iVar10 + 0xc) = (int)(fVar1 + fVar19 * fVar4 * (fVar2 - fVar1));
    } while (iVar7 < *(int *)(this + 8));
  }
  *(undefined4 *)this = 0;
  RShellMemoryFree(pcVar5);
  return;
}
