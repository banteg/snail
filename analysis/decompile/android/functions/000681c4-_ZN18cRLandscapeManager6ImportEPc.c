/*
 * mangled: _ZN18cRLandscapeManager6ImportEPc
 * demangled: cRLandscapeManager::Import(char*)
 * address: 000681c4
 * size: 1976
 */

/* cRLandscapeManager::Import(char*) */

void __thiscall cRLandscapeManager::Import(cRLandscapeManager *this,char *param_1)

{
  int iVar1;
  float fVar2;
  char *pcVar3;
  byte *pbVar4;
  int iVar5;
  char *pcVar6;
  undefined4 uVar7;
  char *pcVar8;
  char cVar9;
  cRLandscapeManager extraout_r1;
  cRLandscapeManager cVar10;
  byte *pbVar11;
  byte *pbVar12;
  byte bVar13;
  char *pcVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  char *pcVar18;
  uint in_fpscr;
  float fVar19;
  char *local_65c;
  char *local_650;
  char *local_64c;
  char *local_644;
  int local_63c;
  byte *local_638;
  byte local_634 [512];
  char local_434 [4];
  char local_430 [508];
  char acStack_234 [512];
  int local_34;

  iVar15 = DAT_0006827c;
  iVar1 = DAT_00068278;
  iVar16 = DAT_00068274 + 0x681e0;
  local_34 = **(int **)(iVar16 + DAT_00068278);
  sprintf(acStack_234,(char *)(iVar16 + DAT_0006827c),param_1);
  if (0 < *(int *)this) {
    iVar17 = 0;
    do {
      iVar5 = Rstrcmp((char *)(this + iVar17 * 0x1ac + 8),param_1);
      if (iVar5 != 0) goto LAB_0006824c;
      iVar17 = iVar17 + 1;
    } while (iVar17 < *(int *)this);
  }
  pcVar6 = (char *)RShellLoadFile(acStack_234,&local_63c);
  pcVar6[local_63c + -1] = '\0';
  if (pcVar6 == (char *)0x0) {
    RShellError((char *)(iVar16 + DAT_000682b4),acStack_234);
    iVar17 = 0;
  }
  else {
    Rstrcpy((char *)(this + *(int *)this * 0x1ac + 8),param_1);
    local_638 = (byte *)Rstrfind((char *)(iVar16 + DAT_00068280),pcVar6);
    if (local_638 == (byte *)0x0) {
      RShellError((char *)(iVar16 + DAT_000682d0),acStack_234);
      *(undefined4 *)(this + *(int *)this * 0x1ac + 4) = 0;
    }
    else {
      local_638 = (byte *)Rstrfind((char *)(iVar16 + DAT_000682a8),(char *)local_638);
      iVar17 = *(int *)this;
      uVar7 = Rstrint((char **)&local_638);
      *(undefined4 *)(this + iVar17 * 0x1ac + 4) = uVar7;
    }
    pcVar8 = (char *)(iVar16 + DAT_00068284);
    *(int *)(this + *(int *)this * 0x1ac + 4) = *(int *)this;
    local_638 = (byte *)Rstrfind(pcVar8,pcVar6);
    fVar2 = DAT_000682d4;
    if (local_638 == (byte *)0x0) {
      RShellError((char *)(iVar16 + DAT_000682cc),acStack_234);
      tColour::Black();
    }
    else {
      local_638 = (byte *)Rstrfind((char *)(iVar16 + DAT_000682a8),(char *)local_638);
      iVar17 = *(int *)this;
      uVar7 = Rstrint((char **)&local_638);
      fVar19 = (float)VectorSignedToFloat(uVar7,(byte)(in_fpscr >> 0x16) & 3);
      *(float *)(this + iVar17 * 0x1ac + 400) = fVar19 / fVar2;
      iVar17 = *(int *)this;
      uVar7 = Rstrint((char **)&local_638);
      fVar19 = (float)VectorSignedToFloat(uVar7,(byte)(in_fpscr >> 0x16) & 3);
      *(float *)(this + iVar17 * 0x1ac + 0x194) = fVar19 / fVar2;
      iVar17 = *(int *)this;
      uVar7 = Rstrint((char **)&local_638);
      fVar19 = (float)VectorSignedToFloat(uVar7,(byte)(in_fpscr >> 0x16) & 3);
      *(float *)(this + iVar17 * 0x1ac + 0x198) = fVar19 / fVar2;
    }
    local_638 = (byte *)Rstrfind((char *)(iVar16 + DAT_00068288),pcVar6);
    if (local_638 == (byte *)0x0) {
      RShellError((char *)(iVar16 + DAT_000682c8),acStack_234);
    }
    else {
      iVar17 = Rstrfind((char *)(iVar16 + DAT_000682a8),(char *)local_638);
      pcVar8 = (char *)(iVar17 + 1);
      cVar9 = *(char *)(iVar17 + 1);
      if (cVar9 == '.') {
        local_64c = local_430;
        pcVar14 = local_434;
        pcVar18 = local_434 + 1;
      }
      else {
        pcVar3 = (char *)(iVar17 + 2);
        pcVar18 = local_434 + 1;
        do {
          pcVar14 = pcVar18;
          pcVar8 = pcVar3;
          pcVar14[-1] = cVar9;
          cVar9 = *pcVar8;
          pcVar18 = pcVar14 + 1;
          pcVar3 = pcVar8 + 1;
        } while (cVar9 != '.');
        local_64c = pcVar14 + 4;
      }
      local_650 = pcVar14 + 3;
      local_65c = pcVar14 + 2;
      *pcVar14 = '.';
      local_638 = (byte *)(pcVar8 + 4);
      *pcVar18 = pcVar8[1];
      *local_65c = pcVar8[2];
      *local_650 = pcVar8[3];
      *local_64c = '\0';
      sprintf((char *)(this + *(int *)this * 0x1ac + 0x8c),(char *)(iVar16 + iVar15),local_434);
      pcVar8 = (char *)(iVar16 + DAT_0006828c);
      *(undefined4 *)(this + *(int *)this * 0x1ac + 0x88) = 7;
      wprintf(pcVar8,this + *(int *)this * 0x1ac + 0x8c);
    }
    local_638 = (byte *)Rstrfind((char *)(iVar16 + DAT_00068290),pcVar6);
    if (local_638 == (byte *)0x0) {
      this[*(int *)this * 0x1ac + 0x10c] = (cRLandscapeManager)0x0;
      local_638 = (byte *)0x0;
    }
    else {
      iVar17 = Rstrfind((char *)(iVar16 + DAT_000682a8),(char *)local_638);
      pcVar8 = (char *)(iVar17 + 1);
      cVar9 = *(char *)(iVar17 + 1);
      if (cVar9 == '.') {
        local_644 = local_430;
        pcVar14 = local_434;
        pcVar18 = local_434 + 1;
      }
      else {
        pcVar18 = local_434 + 1;
        do {
          pcVar14 = pcVar18;
          pcVar8 = pcVar8 + 1;
          pcVar14[-1] = cVar9;
          cVar9 = *pcVar8;
          pcVar18 = pcVar14 + 1;
        } while (cVar9 != '.');
        local_644 = pcVar14 + 4;
      }
      local_650 = pcVar14 + 3;
      *pcVar14 = '.';
      local_638 = (byte *)(pcVar8 + 4);
      *pcVar18 = pcVar8[1];
      pcVar14[2] = pcVar8[2];
      *local_650 = pcVar8[3];
      *local_644 = '\0';
      sprintf((char *)(this + *(int *)this * 0x1ac + 0x10d),(char *)(iVar16 + iVar15),local_434);
      iVar15 = *(int *)this;
      this[iVar15 * 0x1ac + 0x10c] = (cRLandscapeManager)0x1;
      RShellFindFile((char *)(this + iVar15 * 0x1ac + 0x10d),false);
      wprintf((char *)(iVar16 + DAT_00068294),this + *(int *)this * 0x1ac + 0x10d);
    }
    local_638 = (byte *)Rstrfind((char *)(iVar16 + DAT_00068298),pcVar6);
    if (local_638 == (byte *)0x0) {
      RShellError((char *)(iVar16 + DAT_000682c4),acStack_234);
    }
    else {
      iVar15 = Rstrfind((char *)(iVar16 + DAT_000682a8),(char *)local_638);
      local_638 = (byte *)(iVar15 + 1);
      bVar13 = *(byte *)(iVar15 + 1);
      if (0x20 < bVar13) {
        if (bVar13 == 0x2e) {
          pbVar12 = local_634;
          pbVar11 = local_634 + 1;
        }
        else {
          pbVar4 = (byte *)(iVar15 + 2);
          pbVar11 = local_634 + 1;
          do {
            pbVar12 = pbVar11;
            local_638 = pbVar4;
            pbVar12[-1] = bVar13;
            pbVar11 = pbVar12 + 1;
            bVar13 = *local_638;
            pbVar4 = local_638 + 1;
          } while (bVar13 != 0x2e);
        }
        *pbVar12 = 0x2e;
        *pbVar11 = 0x78;
        pbVar12[2] = 0;
      }
    }
    local_638 = (byte *)Rstrfind((char *)(iVar16 + DAT_0006829c),pcVar6);
    if (local_638 == (byte *)0x0) {
      RShellError((char *)(iVar16 + DAT_000682bc),acStack_234);
    }
    else {
      iVar15 = Rstrfind((char *)(iVar16 + DAT_000682a8),(char *)local_638);
      iVar17 = *(int *)this;
      local_638 = (byte *)(iVar15 + 1);
      uVar7 = Rstrfloat((char **)&local_638);
      *(undefined4 *)(this + iVar17 * 0x1ac + 0x1a0) = uVar7;
    }
    local_638 = (byte *)Rstrfind((char *)(iVar16 + DAT_000682a0),pcVar6);
    if (local_638 == (byte *)0x0) {
      RShellError((char *)(iVar16 + DAT_000682b8),acStack_234);
    }
    else {
      iVar15 = Rstrfind((char *)(iVar16 + DAT_000682a8),(char *)local_638);
      iVar17 = *(int *)this;
      local_638 = (byte *)(iVar15 + 1);
      uVar7 = Rstrfloat((char **)&local_638);
      *(undefined4 *)(this + iVar17 * 0x1ac + 0x1a4) = uVar7;
    }
    local_638 = (byte *)Rstrfind((char *)(iVar16 + DAT_000682a4),pcVar6);
    if (local_638 == (byte *)0x0) {
      RShellError((char *)(iVar16 + DAT_000682c0),acStack_234);
    }
    else {
      iVar15 = Rstrfind((char *)(iVar16 + DAT_000682a8),(char *)local_638);
      iVar17 = *(int *)this;
      local_638 = (byte *)(iVar15 + 1);
      uVar7 = Rstrfloat((char **)&local_638);
      *(undefined4 *)(this + iVar17 * 0x1ac + 0x1a8) = uVar7;
    }
    local_638 = (byte *)Rstrfind((char *)(iVar16 + DAT_000682ac),pcVar6);
    if (local_638 != (byte *)0x0) {
      iVar15 = *(int *)this;
      cVar10 = (cRLandscapeManager)0x1;
    }
    else {
      iVar15 = *(int *)this;
      cVar10 = extraout_r1;
    }
    *(int *)this = iVar15 + 1;
    if (local_638 != (byte *)0x0) {
      this[iVar15 * 0x1ac + 0x1ac] = cVar10;
    }
    else {
      this[iVar15 * 0x1ac + 0x1ac] = (cRLandscapeManager)0x0;
    }
    RShellMemoryFree(pcVar6);
    wprintf((char *)(iVar16 + DAT_000682b0),param_1);
    iVar17 = *(int *)this + -1;
  }
LAB_0006824c:
  if (local_34 == **(int **)(iVar16 + iVar1)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(iVar17);
}
