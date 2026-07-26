/*
 * mangled: _ZN8cRGalaxy4OpenEi
 * demangled: cRGalaxy::Open(int)
 * address: 0005aea4
 * size: 1168
 */

/* cRGalaxy::Open(int) */

void __thiscall cRGalaxy::Open(cRGalaxy *this,int param_1)

{
  bool bVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  undefined4 uVar8;
  float *pfVar9;
  cRGalaxy *pcVar10;
  void *pvVar11;
  cRGalaxy *pcVar12;
  cRGalaxy *pcVar13;
  int iVar14;
  float *pfVar15;
  cRGalaxy cVar16;
  char *pcVar17;
  char *pcVar18;
  char *pcVar19;
  char *__format;
  float *pfVar20;
  cRGalaxy *pcVar21;
  int iVar22;
  int iVar23;
  int iVar24;
  undefined4 uVar25;
  int local_128;
  int local_124;
  cRGalaxy *local_11c;
  char *local_110;
  cRGalaxy *local_f8;
  char acStack_f4 [128];
  char acStack_74 [64];
  int local_34;

  pfVar9 = DAT_0005b318;
  iVar14 = DAT_0005b314 + 0x5aec0;
  this[8] = (cRGalaxy)0x0;
  *(undefined4 *)this = 0;
  local_34 = **(int **)(iVar14 + (int)pfVar9);
  if (param_1 == 0) {
    pfVar20 = *(float **)(iVar14 + DAT_0005b31c);
  }
  else {
    pfVar20 = pfVar9;
    if (param_1 == 1) {
      pfVar20 = *(float **)(iVar14 + DAT_0005b340);
    }
  }
  pfVar15 = pfVar20 + 1;
  iVar24 = (int)*pfVar20;
  *(int *)(this + 0x14) = iVar24;
  fVar7 = DAT_0005b304;
  fVar6 = DAT_0005b300;
  fVar5 = DAT_0005b2fc;
  fVar4 = DAT_0005b2f8;
  fVar3 = DAT_0005b2f4;
  fVar2 = DAT_0005b2f0;
  if (0 < iVar24) {
    iVar23 = 0;
    pcVar12 = this;
    pfVar20 = pfVar20 + 3;
    do {
      pfVar15 = pfVar20;
      iVar23 = iVar23 + 1;
      *(float *)(pcVar12 + 0x1c) = (fVar2 * pfVar15[-2]) / fVar3;
      *(float *)(pcVar12 + 0x20) = fVar7 + ((fVar4 * pfVar15[-1]) / fVar2 - fVar5) * fVar6;
      pcVar12 = pcVar12 + 8;
      pfVar20 = pfVar15 + 2;
    } while (iVar23 < iVar24);
  }
  iVar24 = iVar24 * 5;
  *(int *)(this + 0x18) = iVar24;
  fVar7 = DAT_0005b304;
  fVar6 = DAT_0005b300;
  fVar5 = DAT_0005b2fc;
  fVar4 = DAT_0005b2f8;
  fVar3 = DAT_0005b2f4;
  fVar2 = DAT_0005b2f0;
  if (-1 < iVar24) {
    iVar23 = 0;
    pcVar12 = this;
    do {
      iVar23 = iVar23 + 1;
      *(float *)(pcVar12 + 0x6c) = (fVar2 * *pfVar15) / fVar3;
      pfVar20 = pfVar15 + 1;
      pfVar15 = pfVar15 + 2;
      *(float *)(pcVar12 + 0x70) = fVar7 + ((fVar4 * *pfVar20) / fVar2 - fVar5) * fVar6;
      pcVar12 = pcVar12 + 8;
    } while (iVar23 <= iVar24);
  }
  *(int *)(this + 0x8e24) = **(int **)(iVar14 + DAT_0005b320) + 0x718a0;
  if (param_1 == 0) {
    pvVar11 = (void *)RShellMemoryScratch();
    local_110 = (char *)RShellLoadFile((char *)(iVar14 + DAT_0005b324),pvVar11,(int *)0x0);
  }
  else if (param_1 == 1) {
    pvVar11 = (void *)RShellMemoryScratch();
    local_110 = (char *)RShellLoadFile((char *)(iVar14 + DAT_0005b33c),pvVar11,(int *)0x0);
  }
  iVar24 = DAT_0005b32c;
  if (0 < *(int *)(this + 0x14)) {
    pcVar12 = this + 0x8880;
    pcVar17 = (char *)(iVar14 + DAT_0005b328);
    local_124 = 0;
    pcVar18 = (char *)(iVar14 + DAT_0005b330);
    pcVar19 = (char *)(iVar14 + DAT_0005b334);
    __format = (char *)(iVar14 + DAT_0005b338);
    local_128 = 0;
    local_11c = this;
    do {
      sprintf(acStack_74,(char *)(iVar14 + iVar24),local_128);
      local_f8 = (cRGalaxy *)Rstrfind(acStack_74,local_110);
      if (local_f8 == (cRGalaxy *)0x0) {
        RShellError((char *)(iVar14 + DAT_0005b348),local_128);
        goto LAB_0005b29c;
      }
      iVar23 = Rstrfind(pcVar17,(char *)local_f8);
      local_f8 = (cRGalaxy *)(iVar23 + 1);
      if (*(char *)(iVar23 + 1) != '\"') {
        RShellError((char *)(iVar14 + DAT_0005b344));
        goto LAB_0005b29c;
      }
      local_f8 = (cRGalaxy *)(iVar23 + 2);
      cVar16 = *(cRGalaxy *)(iVar23 + 2);
      pcVar13 = this + local_128 * 0xa0 + 0x87e4;
      if (cVar16 != (cRGalaxy)0x22) {
        pcVar21 = pcVar13;
        pcVar10 = (cRGalaxy *)(iVar23 + 3);
        do {
          local_f8 = pcVar10;
          pcVar13 = pcVar21 + 1;
          *pcVar21 = cVar16;
          cVar16 = *local_f8;
          pcVar21 = pcVar13;
          pcVar10 = local_f8 + 1;
        } while (cVar16 != (cRGalaxy)0x22);
      }
      *pcVar13 = (cRGalaxy)0x0;
      uVar8 = DAT_0005b308;
      local_f8 = (cRGalaxy *)Rstrfind(pcVar18,(char *)local_f8);
      iVar23 = Rstrfind(pcVar19,(char *)local_f8);
      local_f8 = (cRGalaxy *)(iVar23 + 1);
      iVar23 = Rstrint((char **)&local_f8);
      uVar25 = DAT_0005b30c;
      *(undefined4 *)(pcVar12 + -0x10) = DAT_0005b30c;
      *(undefined4 *)(pcVar12 + -0x18) = uVar25;
      *(undefined4 *)(pcVar12 + -0x14) = uVar25;
      *(undefined4 *)(pcVar12 + -0xc) = DAT_0005b310;
      *(undefined4 *)(pcVar12 + -8) = *(undefined4 *)(local_11c + 0x1c);
      uVar25 = *(undefined4 *)(local_11c + 0x20);
      *(undefined4 *)pcVar12 = uVar8;
      *(undefined4 *)(pcVar12 + -4) = uVar25;
      *(int *)(pcVar12 + -0x1c) = iVar23;
      if (0 < iVar23) {
        pcVar21 = this + local_124 * 8 + 0x6c;
        pcVar13 = this + local_124 * 0x2a0 + 0x204;
        iVar23 = 1;
        do {
          *(undefined4 *)(pcVar13 + 0x2ac) = *(undefined4 *)(pcVar21 + 8);
          iVar22 = iVar23 + local_124;
          *(undefined4 *)(pcVar13 + 0x2b0) = *(undefined4 *)(pcVar21 + 0xc);
          *(int *)(pcVar13 + 0x2a4) = local_128;
          *(undefined4 *)(pcVar13 + 0x2b4) = uVar8;
          sprintf(acStack_f4,__format,iVar22);
          pcVar13 = pcVar13 + 0x2a0;
          pcVar21 = pcVar21 + 8;
          Rstrcpy((char *)(this + iVar22 * 0x2a0 + 0x224),acStack_f4);
          Rstrcpy((char *)(this + iVar22 * 0x2a0 + 0x2a4),acStack_f4);
          bVar1 = iVar23 < *(int *)(pcVar12 + -0x1c);
          iVar23 = iVar23 + 1;
        } while (bVar1);
      }
      pcVar12 = pcVar12 + 0xa0;
      local_128 = local_128 + 1;
      local_124 = local_124 + 5;
      local_11c = local_11c + 8;
    } while (local_128 < *(int *)(this + 0x14));
  }
  this[0x2a4] = (cRGalaxy)0x0;
  *(undefined4 *)(this + 0x210) = *(undefined4 *)(this + 0x6c);
  *(undefined4 *)(this + 0x208) = 0;
  this[0x224] = (cRGalaxy)0x0;
  *(undefined4 *)(this + 0x214) = *(undefined4 *)(this + 0x70);
  *(undefined4 *)(this + 0x218) = DAT_0005b308;
LAB_0005b29c:
  if (local_34 == **(int **)(iVar14 + (int)pfVar9)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}
