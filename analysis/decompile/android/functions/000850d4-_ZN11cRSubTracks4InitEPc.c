/*
 * mangled: _ZN11cRSubTracks4InitEPc
 * demangled: cRSubTracks::Init(char*)
 * address: 000850d4
 * size: 4992
 */

/* WARNING: Type propagation algorithm not settling */
/* cRSubTracks::Init(char*) */

void __thiscall cRSubTracks::Init(cRSubTracks *this,char *param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  char *pcVar8;
  cRSubTracks *pcVar9;
  uint uVar10;
  int *piVar11;
  cRSubTracks *pcVar12;
  cRSubTracks cVar13;
  uint uVar14;
  undefined4 *puVar15;
  char *pcVar16;
  int iVar17;
  int iVar18;
  cRSubTracks *pcVar19;
  char *pcVar20;
  void *pvVar21;
  char *pcVar22;
  undefined1 *puVar23;
  undefined4 *puVar24;
  undefined4 *puVar25;
  bool bVar26;
  bool bVar27;
  uint in_fpscr;
  float extraout_s0;
  float extraout_s1;
  float extraout_s2;
  float extraout_s3;
  float fVar28;
  float fVar29;
  undefined8 uVar30;
  cRSubTracks *local_7bc;
  cRSubTracks *local_7b8;
  undefined4 local_7b4;
  undefined4 uStack_7b0;
  undefined4 uStack_7ac;
  undefined4 uStack_7a8;
  undefined2 local_7a4;
  undefined1 local_7a2;
  undefined1 local_5b4 [4];
  undefined4 local_5b0;
  undefined4 uStack_5ac;
  cRSubTracks local_3b4 [512];
  cRSubTracks local_1b4 [256];
  cRSubTracks local_b4 [128];
  int local_34;

  iVar4 = DAT_00085764;
  iVar3 = DAT_0008575c;
  iVar2 = DAT_00085758;
  iVar17 = DAT_00085754 + 0x850f4;
  local_34 = **(int **)(iVar17 + DAT_00085758);
  **(undefined4 **)(iVar17 + DAT_00085760) = param_1;
  sprintf((char *)&local_7b4,(char *)(iVar17 + iVar4));
  pvVar21 = *(void **)(iVar17 + iVar3);
  iVar4 = RShellLoadFile((char *)&local_7b4,pvVar21,(int *)0x0);
  if (iVar4 == 0) {
    RShellError((char *)(iVar17 + DAT_000862b0),&local_7b4);
    puVar15 = (undefined4 *)(iVar17 + DAT_000862b4);
    local_7b4 = *puVar15;
    uStack_7b0 = puVar15[1];
    uStack_7ac = puVar15[2];
    uStack_7a8 = puVar15[3];
    local_7a4 = (undefined2)puVar15[4];
    local_7a2 = (undefined1)((uint)puVar15[4] >> 0x10);
    RShellLoadFile((char *)&local_7b4,pvVar21,(int *)0x0);
  }
  local_7b8 = (cRSubTracks *)Rstrfind((char *)(iVar17 + DAT_00085768),*(char **)(iVar17 + iVar3));
  if (local_7b8 == (cRSubTracks *)0x0) {
    RShellError((char *)(iVar17 + DAT_000862b8),&local_7b4);
  }
  pcVar19 = this + 0x1508;
  uVar30 = Rstrfind((char *)(iVar17 + DAT_0008576c),(char *)local_7b8);
  local_7b8 = (cRSubTracks *)((int)uVar30 + 1);
  cVar13 = *(cRSubTracks *)((int)uVar30 + 1);
  bVar27 = 0x26 < (byte)cVar13;
  bVar26 = cVar13 == (cRSubTracks)0x27;
  if (!bVar26) {
    bVar27 = 0x1e < (byte)cVar13;
  }
  pcVar9 = (cRSubTracks *)((ulonglong)uVar30 >> 0x20);
  if (!bVar27 || (bVar26 || cVar13 == (cRSubTracks)0x1f)) {
    pcVar9 = pcVar19;
  }
  pcVar12 = pcVar19;
  if (bVar27 && (!bVar26 && cVar13 != (cRSubTracks)0x1f)) {
    do {
      local_7b8 = local_7b8 + 1;
      pcVar9 = pcVar12 + 1;
      *pcVar12 = cVar13;
      cVar13 = *local_7b8;
      bVar27 = 0x26 < (byte)cVar13;
      if (cVar13 != (cRSubTracks)0x27) {
        bVar27 = 0x1e < (byte)cVar13;
      }
      pcVar12 = pcVar9;
    } while (bVar27 && (cVar13 != (cRSubTracks)0x27 && cVar13 != (cRSubTracks)0x1f));
  }
  iVar4 = DAT_00085770;
  pcVar22 = *(char **)(iVar17 + iVar3);
  *pcVar9 = (cRSubTracks)0x0;
  *(undefined4 *)(this + 0x1588) = 0;
  iVar4 = Rstrfind((char *)(iVar17 + iVar4),pcVar22);
  if (iVar4 == 0) {
    iVar4 = Rstrfind((char *)(iVar17 + DAT_000862bc),pcVar22);
    if (iVar4 == 0) {
      iVar4 = Rstrfind((char *)(iVar17 + DAT_000862c0),pcVar22);
      if (iVar4 != 0) {
        *(undefined4 *)(this + 0x1588) = 2;
      }
    }
    else {
      *(undefined4 *)(this + 0x1588) = 1;
    }
  }
  else {
    *(undefined4 *)(this + 0x1588) = 0;
  }
  iVar4 = DAT_00085774;
  if (gOFOData[*(int *)(gOFOData + **(int **)(iVar17 + DAT_00085774) + 0x1ebc) * 0x8e6c +
               **(int **)(iVar17 + DAT_00085774) + 0x1ec8] == '\0') {
    local_7b8 = (cRSubTracks *)Rstrfind((char *)(iVar17 + DAT_00086284),param_1);
    if (local_7b8 == (cRSubTracks *)0x0) {
      local_7b8 = (cRSubTracks *)Rstrfind((char *)(iVar17 + DAT_000862ec),param_1);
      if (local_7b8 == (cRSubTracks *)0x0) goto LAB_00085228;
      iVar5 = 0;
    }
    else {
      iVar5 = 1;
    }
    iVar6 = Rstrfind((char *)(iVar17 + DAT_00086288),(char *)local_7b8);
    local_7b8 = (cRSubTracks *)(iVar6 + 1);
    iVar6 = Rstrint((char **)&local_7b8);
    piVar11 = *(int **)(iVar17 + iVar4);
    iVar5 = iVar5 * 0x8e6c;
    strcpy(gOFOData + *piVar11 + iVar6 * 0x2a0 + iVar5 + 0x20e4,(char *)pcVar19);
    local_7b8 = (cRSubTracks *)Rstrfind((char *)(iVar17 + DAT_0008628c),*(char **)(iVar17 + iVar3));
    if (local_7b8 == (cRSubTracks *)0x0) {
      RShellWarning((char *)(iVar17 + DAT_000862cc),param_1);
      Rstrcpy(gOFOData + *piVar11 + (iVar6 + 1) * 0x2a0 + iVar5 + 0x1ec4,
              (char *)(iVar17 + DAT_000862d0));
    }
    else {
      local_7b8 = (cRSubTracks *)Rstrfind((char *)(iVar17 + DAT_00086290),(char *)local_7b8);
      if (local_7b8 == (cRSubTracks *)0x0) {
        RShellWarning((char *)(iVar17 + DAT_000862e0),param_1);
        Rstrcpy(gOFOData + *piVar11 + (iVar6 + 1) * 0x2a0 + iVar5 + 0x1ec4,
                (char *)(iVar17 + DAT_000862e4));
      }
      else {
        local_7b8 = (cRSubTracks *)Rstrnewline((char *)local_7b8);
        iVar18 = Rstrfind((char *)(iVar17 + DAT_00086294),(char *)local_7b8);
        if (iVar18 != 0) {
          pcVar19 = (cRSubTracks *)(gOFOData + *piVar11 + iVar6 * 0x2a0 + iVar5 + 0x2164);
joined_r0x00086118:
          if (local_7b8 < (cRSubTracks *)(iVar18 + -2)) {
            do {
              if ((byte)*local_7b8 < 0x20) {
                pcVar9 = pcVar19 + 1;
                *pcVar19 = (cRSubTracks)0x3e;
                cVar13 = *local_7b8;
                if ((byte)cVar13 < 0x20) goto LAB_00086160;
              }
              else {
                cVar13 = *local_7b8;
                pcVar9 = pcVar19;
              }
              local_7b8 = local_7b8 + 1;
              pcVar19 = pcVar9 + 1;
              *pcVar9 = cVar13;
              if ((cRSubTracks *)(iVar18 + -2) <= local_7b8) break;
            } while( true );
          }
          *pcVar19 = (cRSubTracks)0x0;
          goto LAB_00085228;
        }
        RShellWarning((char *)(iVar17 + DAT_000862f0),param_1);
        Rstrcpy(gOFOData + *piVar11 + (iVar6 + 1) * 0x2a0 + iVar5 + 0x1ec4,
                (char *)(iVar17 + DAT_000862f4));
      }
    }
  }
LAB_00085228:
  pcVar22 = *(char **)(iVar17 + iVar3);
  local_7b8 = (cRSubTracks *)Rstrfind((char *)(iVar17 + DAT_00085778),pcVar22);
  iVar5 = DAT_0008577c;
  if (local_7b8 == (cRSubTracks *)0x0) {
    *(undefined4 *)(this + 0x14f0) = 0;
    this[0x14f4] = (cRSubTracks)0x0;
    local_7b8 = (cRSubTracks *)0x0;
LAB_000852ac:
    local_7b8 = (cRSubTracks *)Rstrfind((char *)(iVar17 + DAT_000857dc),*(char **)(iVar17 + iVar3));
    iVar5 = DAT_00085780;
  }
  else {
    this[0x14f4] = (cRSubTracks)0x1;
    local_7b8 = (cRSubTracks *)Rstrfind((char *)(iVar17 + iVar5),pcVar22);
    if (local_7b8 == (cRSubTracks *)0x0) {
      RShellError((char *)(iVar17 + DAT_000862a8),&local_7b4);
      goto LAB_00085fd8;
    }
    iVar5 = Rstrfind((char *)(iVar17 + DAT_00085780),(char *)local_7b8);
    *(undefined4 *)(this + 0x14f0) = 0;
    local_7b8 = (cRSubTracks *)(iVar5 + 1);
    uVar10 = (uint)*(byte *)(iVar5 + 1);
    uVar14 = (uint)(uVar10 == 0x61 || uVar10 == 0x41);
    if ((uVar10 == 0x61 || uVar10 == 0x41) || (9 < (uVar10 - 0x30 & 0xff))) goto LAB_000852ac;
    do {
      local_7b8 = local_7b8 + 1;
      uVar14 = (uVar10 + uVar14 * 10) - 0x30;
      *(uint *)(this + 0x14f0) = uVar14;
      uVar10 = (uint)(byte)*local_7b8;
    } while ((uVar10 - 0x30 & 0xff) < 10);
    local_7b8 = (cRSubTracks *)Rstrfind((char *)(iVar17 + DAT_000857dc),*(char **)(iVar17 + iVar3));
    iVar5 = DAT_00085780;
  }
  DAT_00085780 = iVar5;
  if (local_7b8 == (cRSubTracks *)0x0) {
    RShellError((char *)(iVar17 + DAT_000857e0),&local_7b4);
    goto LAB_00085fd8;
  }
  iVar6 = Rstrfind((char *)(iVar17 + iVar5),(char *)local_7b8);
  local_7b8 = (cRSubTracks *)(iVar6 + 1);
  cVar13 = *(cRSubTracks *)(iVar6 + 1);
  if (cVar13 == (cRSubTracks)0x2e) {
    pcVar19 = local_3b4;
  }
  else {
    pcVar19 = local_3b4;
    do {
      pcVar19 = pcVar19 + 1;
      local_7b8 = local_7b8 + 1;
      pcVar19[-1] = cVar13;
      cVar13 = *local_7b8;
    } while (cVar13 != (cRSubTracks)0x2e);
  }
  piVar11 = *(int **)(iVar17 + iVar4);
  *pcVar19 = (cRSubTracks)0x2e;
  iVar4 = *piVar11;
  pcVar19[1] = (cRSubTracks)0x74;
  pcVar19[2] = (cRSubTracks)0x78;
  pcVar19[3] = (cRSubTracks)0x74;
  pcVar19[4] = (cRSubTracks)0x0;
  uVar7 = cRLandscapeManager::Import
                    ((cRLandscapeManager *)(gSegmentText + iVar4 + 0x3d8),(char *)local_3b4);
  pcVar22 = *(char **)(iVar17 + iVar3);
  *(undefined4 *)(this + 0x1598) = uVar7;
  local_7b8 = (cRSubTracks *)Rstrfind((char *)(iVar17 + DAT_00085784),pcVar22);
  if (local_7b8 == (cRSubTracks *)0x0) {
    RShellError((char *)(iVar17 + DAT_0008629c),&local_7b4);
    tColour::Set((tColour *)(this + 0x14f8),extraout_s0,extraout_s1,extraout_s2,extraout_s3);
  }
  else {
    iVar4 = Rstrfind((char *)(iVar17 + iVar5),(char *)local_7b8);
    fVar29 = DAT_0008574c;
    local_7b8 = (cRSubTracks *)(iVar4 + 1);
    uVar7 = Rstrint((char **)&local_7b8);
    fVar28 = (float)VectorSignedToFloat(uVar7,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(this + 0x14f8) = fVar28 / fVar29;
    uVar7 = Rstrint((char **)&local_7b8);
    fVar28 = (float)VectorSignedToFloat(uVar7,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(this + 0x14fc) = fVar28 / fVar29;
    uVar7 = Rstrint((char **)&local_7b8);
    fVar28 = (float)VectorSignedToFloat(uVar7,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(this + 0x1500) = fVar28 / fVar29;
  }
  local_7b8 = (cRSubTracks *)Rstrfind((char *)(iVar17 + DAT_00085788),*(char **)(iVar17 + iVar3));
  if (local_7b8 == (cRSubTracks *)0x0) {
    RShellError((char *)(iVar17 + DAT_00086298),&local_7b4);
    *(undefined4 *)(this + 0x15a0) = 0;
  }
  else {
    iVar4 = Rstrfind((char *)(iVar17 + iVar5),(char *)local_7b8);
    local_7b8 = (cRSubTracks *)(iVar4 + 1);
    cVar1 = *(char *)(iVar4 + 1);
    if (cVar1 == '0') {
      *(undefined4 *)(this + 0x15a0) = 0;
    }
    else if (cVar1 == '1') {
      *(undefined4 *)(this + 0x15a0) = 1;
    }
    else if (cVar1 == '2') {
      *(undefined4 *)(this + 0x15a0) = 2;
    }
    else if (cVar1 == '3') {
      *(undefined4 *)(this + 0x15a0) = 3;
    }
    else if (cVar1 == '4') {
      *(undefined4 *)(this + 0x15a0) = 4;
    }
    else if (cVar1 == '5') {
      *(undefined4 *)(this + 0x15a0) = 5;
    }
    else if (cVar1 == '6') {
      *(undefined4 *)(this + 0x15a0) = 6;
    }
    else if (cVar1 == 'r') {
      *(undefined4 *)(this + 0x15a0) = 8;
    }
  }
  pcVar22 = *(char **)(iVar17 + iVar3);
  local_7b8 = (cRSubTracks *)Rstrfind((char *)(iVar17 + DAT_0008578c),pcVar22);
  if (local_7b8 == (cRSubTracks *)0x0) {
    *(undefined4 *)(this + 0x159c) = 0;
    RShellError((char *)(iVar17 + DAT_000862a0),&local_7b4);
    goto LAB_00085fd8;
  }
  pcVar20 = (char *)(iVar17 + iVar5);
  local_7b8 = (cRSubTracks *)Rstrfind(pcVar20,(char *)local_7b8);
  uVar7 = Rstrint((char **)&local_7b8);
  *(undefined4 *)(this + 0x159c) = uVar7;
  local_7b8 = (cRSubTracks *)Rstrfind((char *)(iVar17 + DAT_00085790),pcVar22);
  if (local_7b8 == (cRSubTracks *)0x0) {
    *(undefined4 *)(this + 0x15a4) = 0;
    RShellError((char *)(iVar17 + DAT_000862a4),&local_7b4);
    goto LAB_00085fd8;
  }
  local_7b8 = (cRSubTracks *)Rstrfind(pcVar20,(char *)local_7b8);
  uVar7 = Rstrint((char **)&local_7b8);
  *(undefined4 *)(this + 0x15a4) = uVar7;
  local_7b8 = (cRSubTracks *)Rstrfind((char *)(iVar17 + DAT_00085794),pcVar22);
  if (local_7b8 == (cRSubTracks *)0x0) {
    local_7b8 = (cRSubTracks *)Rstrfind((char *)(iVar17 + DAT_000862c8),pcVar22);
    if (local_7b8 == (cRSubTracks *)0x0) {
      RShellError((char *)(iVar17 + DAT_000862d8),&local_7b4);
      *(undefined4 *)(this + 0x158c) = DAT_000862f8;
    }
    else {
      iVar4 = Rstrfind(pcVar20,(char *)local_7b8);
      local_7b8 = (cRSubTracks *)(iVar4 + 1);
      uVar7 = Rstrfloat((char **)&local_7b8);
      *(undefined4 *)(this + 0x158c) = uVar7;
    }
  }
  else {
    *(undefined4 *)(this + 0x158c) = DAT_00085750;
  }
  local_7b8 = (cRSubTracks *)Rstrfind((char *)(iVar17 + DAT_00085798),*(char **)(iVar17 + iVar3));
  if (local_7b8 == (cRSubTracks *)0x0) {
    pcVar20 = *(char **)(iVar17 + iVar3);
    pcVar22 = (char *)(iVar17 + DAT_000857e4);
    *(undefined4 *)(this + 0x1590) = DAT_0008626c;
    local_7b8 = (cRSubTracks *)Rstrfind(pcVar22,pcVar20);
    if (local_7b8 == (cRSubTracks *)0x0) goto LAB_00085eb8;
LAB_000855b8:
    uVar7 = Rstrfloat((char **)&local_7b8);
    *(undefined4 *)(this + 0x1594) = uVar7;
  }
  else {
    uVar7 = Rstrfloat((char **)&local_7b8);
    pcVar22 = *(char **)(iVar17 + iVar3);
    *(undefined4 *)(this + 0x1590) = uVar7;
    local_7b8 = (cRSubTracks *)Rstrfind((char *)(iVar17 + DAT_000857e4),pcVar22);
    if (local_7b8 != (cRSubTracks *)0x0) goto LAB_000855b8;
LAB_00085eb8:
    *(undefined4 *)(this + 0x1594) = DAT_0008626c;
  }
  iVar4 = DAT_0008579c;
  pcVar22 = *(char **)(iVar17 + iVar3);
  *(undefined4 *)this = 0;
  local_7b8 = (cRSubTracks *)Rstrfind((char *)(iVar17 + iVar4),pcVar22);
  if (local_7b8 == (cRSubTracks *)0x0) {
    RShellError((char *)(iVar17 + DAT_000862ac),&local_7b4);
  }
  else {
    pcVar19 = (cRSubTracks *)Rstrfind((char *)(iVar17 + DAT_000857a0),pcVar22);
    if (pcVar19 == (cRSubTracks *)0x0) {
      RShellError((char *)(iVar17 + DAT_000862c4),&local_7b4);
    }
    else {
      local_7b8 = (cRSubTracks *)Rstrnewline((char *)local_7b8);
      iVar4 = DAT_000857b0;
      if (local_7b8 != (cRSubTracks *)0x0) {
        pcVar22 = (char *)(iVar17 + DAT_000857a4);
        iVar5 = 1 - *(uint *)(this + 0x1588);
        if (1 < *(uint *)(this + 0x1588)) {
          iVar5 = 0;
        }
        puVar15 = (undefined4 *)(iVar17 + DAT_000857a8);
        pcVar20 = (char *)(iVar17 + DAT_000857ac);
        pcVar16 = (char *)(iVar17 + DAT_000857b4);
LAB_00085668:
        if (local_7b8 < pcVar19) {
          do {
            if (iVar5 == 0) {
              cVar13 = *local_7b8;
              if (cVar13 == (cRSubTracks)0x2e) {
                puVar25 = (undefined4 *)local_5b4;
                puVar24 = (undefined4 *)((int)local_5b4 + 1);
              }
              else {
                puVar24 = (undefined4 *)((int)local_5b4 + 1);
                do {
                  puVar25 = puVar24;
                  local_7b8 = local_7b8 + 1;
                  *(cRSubTracks *)((int)puVar25 + -1) = cVar13;
                  cVar13 = *local_7b8;
                  puVar24 = (undefined4 *)((int)puVar25 + 1);
                } while (cVar13 != (cRSubTracks)0x2e);
              }
              *(undefined1 *)puVar25 = 0x2e;
              *(undefined1 *)puVar24 = 0x74;
              *(undefined1 *)((int)puVar25 + 2) = 0x78;
              *(undefined1 *)((int)puVar25 + 3) = 0x74;
              *(undefined1 *)(puVar25 + 1) = 0;
              ImportSegment(this,local_5b4,(cRSubSegment *)(this + *(int *)this * 0x34 + 4));
              local_7bc = local_7b8 + 3;
              cVar13 = local_7b8[3];
              if ((byte)cVar13 < 0x20) {
                pcVar9 = local_1b4;
              }
              else {
                pcVar9 = local_1b4;
                pcVar12 = local_7b8 + 4;
                do {
                  local_7bc = pcVar12;
                  pcVar9 = pcVar9 + 1;
                  pcVar9[-1] = cVar13;
                  cVar13 = *local_7bc;
                  pcVar12 = local_7bc + 1;
                } while (0x1f < (byte)cVar13);
              }
              *pcVar9 = (cRSubTracks)0x0;
            }
            else {
              local_5b4 = (undefined1  [4])*puVar15;
              local_5b0 = puVar15[1];
              uStack_5ac = puVar15[2];
              ImportSegment(this,local_5b4,(cRSubSegment *)(this + *(int *)this * 0x34 + 4));
              local_1b4[0] = (cRSubTracks)0x0;
            }
            local_7bc = (cRSubTracks *)Rstrfind(pcVar20,(char *)local_1b4);
            if (local_7bc == (cRSubTracks *)0x0) {
              iVar6 = *(int *)this;
              *(undefined4 *)(this + iVar6 * 0x34 + 0x20) = DAT_00086270;
              local_7bc = (cRSubTracks *)0x0;
            }
            else {
              local_7bc = (cRSubTracks *)Rstrfind(pcVar22,(char *)local_7bc);
              iVar18 = *(int *)this;
              uVar7 = Rstrint((char **)&local_7bc);
              iVar6 = *(int *)this;
              fVar29 = (float)VectorSignedToFloat(uVar7,(byte)(in_fpscr >> 0x16) & 3);
              *(float *)(this + iVar18 * 0x34 + 0x20) =
                   ((fVar29 + fVar29) * DAT_000857e8) / DAT_000857ec;
            }
            *(undefined4 *)(this + iVar6 * 0x34 + 0x24) = 0;
            local_7bc = (cRSubTracks *)Rstrfind(pcVar16,(char *)local_1b4);
            if (local_7bc == (cRSubTracks *)0x0) goto LAB_00085f50;
            iVar6 = Rstrfind(pcVar22,(char *)local_7bc);
            if (*(char *)(iVar6 + 1) != '\"') {
LAB_00085fcc:
              local_7bc = (cRSubTracks *)(iVar6 + 1);
              RShellError((char *)(iVar17 + DAT_00086280));
              goto LAB_00085fd8;
            }
            local_7bc = (cRSubTracks *)(iVar6 + 2);
            cVar13 = *(cRSubTracks *)(iVar6 + 2);
            pcVar9 = local_7bc;
            while (cVar13 != (cRSubTracks)0x22) {
              pcVar9 = pcVar9 + 1;
              cVar13 = *pcVar9;
            }
            iVar18 = *(int *)this;
            uVar7 = RShellMemoryMalloc((int)(pcVar9 + (8 - (int)local_7bc)),(char *)(iVar17 + iVar4)
                                      );
            iVar6 = *(int *)this;
            *(undefined4 *)(this + iVar18 * 0x34 + 0x24) = uVar7;
            puVar23 = *(undefined1 **)(this + iVar6 * 0x34 + 0x24);
            if (local_7bc < pcVar9) {
              iVar6 = 0;
              pcVar12 = local_7bc;
              do {
                pcVar12 = pcVar12 + 1;
                *(cRSubTracks *)(puVar23 + iVar6) = local_7bc[iVar6];
                iVar6 = iVar6 + 1;
              } while (pcVar12 < pcVar9);
              puVar23 = puVar23 + ((int)pcVar9 - (int)local_7bc);
              local_7bc = pcVar12;
            }
            iVar6 = DAT_000857c4;
            *puVar23 = 0;
            local_7bc = (cRSubTracks *)Rstrfind((char *)(iVar17 + iVar6),(char *)local_1b4);
            *(undefined4 *)(this + *(int *)this * 0x34 + 0x28) = DAT_000857f0;
            if (local_7bc != (cRSubTracks *)0x0) {
              iVar6 = Rstrfind(pcVar22,(char *)local_7bc);
              iVar18 = *(int *)this;
              local_7bc = (cRSubTracks *)(iVar6 + 1);
              uVar7 = Rstrfloat((char **)&local_7bc);
              *(undefined4 *)(this + iVar18 * 0x34 + 0x28) = uVar7;
            }
            local_7bc = (cRSubTracks *)Rstrfind((char *)(iVar17 + DAT_000857b8),(char *)local_1b4);
            *(undefined4 *)(this + *(int *)this * 0x34 + 0x2c) = 0xffffffff;
            if (local_7bc == (cRSubTracks *)0x0) {
LAB_00085f50:
              iVar6 = *(int *)this;
            }
            else {
              iVar6 = Rstrfind(pcVar22,(char *)local_7bc);
              pcVar9 = local_b4;
              for (local_7bc = (cRSubTracks *)(iVar6 + 2); cVar13 = *local_7bc,
                  cVar13 != (cRSubTracks)0x2e; local_7bc = local_7bc + 1) {
                pcVar12 = local_b4;
                if (cVar13 != (cRSubTracks)0x2f) {
                  *pcVar9 = cVar13;
                  pcVar12 = pcVar9 + 1;
                }
                pcVar9 = pcVar12;
              }
              iVar6 = *(int *)this;
              *pcVar9 = (cRSubTracks)0x0;
              uVar7 = cRVoiceManager::FindSample
                                (*(cRVoiceManager **)(iVar17 + DAT_000857cc),(char *)local_b4);
              *(undefined4 *)(this + iVar6 * 0x34 + 0x2c) = uVar7;
              iVar6 = *(int *)this;
              if (*(int *)(this + iVar6 * 0x34 + 0x2c) == -1) {
                RShellError((char *)(iVar17 + DAT_0008627c),local_b4,&local_7b4);
                goto LAB_00085f50;
              }
            }
            pcVar8 = (char *)(iVar17 + DAT_000857bc);
            *(undefined4 *)(this + iVar6 * 0x34 + 0x30) = 0;
            local_7bc = (cRSubTracks *)Rstrfind(pcVar8,(char *)local_1b4);
            if (local_7bc == (cRSubTracks *)0x0) goto LAB_00085ee4;
            iVar6 = Rstrfind(pcVar22,(char *)local_7bc);
            if (*(char *)(iVar6 + 1) != '\"') goto LAB_00085fcc;
            local_7bc = (cRSubTracks *)(iVar6 + 2);
            cVar13 = *(cRSubTracks *)(iVar6 + 2);
            pcVar9 = local_7bc;
            while (cVar13 != (cRSubTracks)0x22) {
              pcVar9 = pcVar9 + 1;
              cVar13 = *pcVar9;
            }
            iVar18 = *(int *)this;
            uVar7 = RShellMemoryMalloc((int)(pcVar9 + (8 - (int)local_7bc)),
                                       (char *)(iVar17 + DAT_000857c0));
            iVar6 = *(int *)this;
            *(undefined4 *)(this + iVar18 * 0x34 + 0x30) = uVar7;
            puVar23 = *(undefined1 **)(this + iVar6 * 0x34 + 0x30);
            if (local_7bc < pcVar9) {
              iVar6 = 0;
              pcVar12 = local_7bc;
              do {
                pcVar12 = pcVar12 + 1;
                *(cRSubTracks *)(puVar23 + iVar6) = local_7bc[iVar6];
                iVar6 = iVar6 + 1;
              } while (pcVar12 < pcVar9);
              puVar23 = puVar23 + ((int)pcVar9 - (int)local_7bc);
              local_7bc = pcVar12;
            }
            iVar6 = DAT_000857c4;
            *puVar23 = 0;
            local_7bc = (cRSubTracks *)Rstrfind((char *)(iVar17 + iVar6),(char *)local_1b4);
            *(undefined4 *)(this + *(int *)this * 0x34 + 0x28) = DAT_000857f0;
            if (local_7bc != (cRSubTracks *)0x0) {
              iVar6 = Rstrfind(pcVar22,(char *)local_7bc);
              iVar18 = *(int *)this;
              local_7bc = (cRSubTracks *)(iVar6 + 1);
              uVar7 = Rstrfloat((char **)&local_7bc);
              *(undefined4 *)(this + iVar18 * 0x34 + 0x28) = uVar7;
            }
            local_7bc = (cRSubTracks *)Rstrfind((char *)(iVar17 + DAT_000857c8),(char *)local_1b4);
            *(undefined4 *)(this + *(int *)this * 0x34 + 0x34) = 0xffffffff;
            if (local_7bc == (cRSubTracks *)0x0) {
LAB_00085ee4:
              iVar6 = *(int *)this + 1;
              *(int *)this = iVar6;
            }
            else {
              iVar6 = Rstrfind(pcVar22,(char *)local_7bc);
              pcVar9 = local_b4;
              for (local_7bc = (cRSubTracks *)(iVar6 + 2); cVar13 = *local_7bc,
                  cVar13 != (cRSubTracks)0x2e; local_7bc = local_7bc + 1) {
                pcVar12 = local_b4;
                if (cVar13 != (cRSubTracks)0x2f) {
                  *pcVar9 = cVar13;
                  pcVar12 = pcVar9 + 1;
                }
                pcVar9 = pcVar12;
              }
              iVar6 = *(int *)this;
              *pcVar9 = (cRSubTracks)0x0;
              uVar7 = cRVoiceManager::FindSample
                                (*(cRVoiceManager **)(iVar17 + DAT_000857cc),(char *)local_b4);
              *(undefined4 *)(this + iVar6 * 0x34 + 0x34) = uVar7;
              if (*(int *)(this + *(int *)this * 0x34 + 0x34) == -1) {
                RShellError((char *)(iVar17 + DAT_00086274),local_b4,&local_7b4);
                goto LAB_00085ee4;
              }
              iVar6 = *(int *)this + 1;
              *(int *)this = iVar6;
            }
            if (100 < iVar6) {
              RShellError((char *)(iVar17 + DAT_00086278),100);
            }
            if (iVar5 == 0) goto LAB_00085f10;
            iVar5 = 0;
            if (pcVar19 <= local_7b8) break;
          } while( true );
        }
        local_7b8 = (cRSubTracks *)
                    Rstrfind((char *)(iVar17 + DAT_000857d0),*(char **)(iVar17 + iVar3));
        if (local_7b8 == (cRSubTracks *)0x0) {
          RShellError((char *)(iVar17 + DAT_000862d4),&local_7b4);
          goto LAB_00085fd8;
        }
        local_7b8 = (cRSubTracks *)Rstrnewline((char *)local_7b8);
        if (local_7b8 != (cRSubTracks *)0x0) {
          cVar13 = *local_7b8;
          if (cVar13 == (cRSubTracks)0x2e) {
            pcVar19 = (cRSubTracks *)local_5b4;
          }
          else {
            pcVar9 = (cRSubTracks *)local_5b4;
            do {
              pcVar19 = pcVar9 + 1;
              local_7b8 = local_7b8 + 1;
              *pcVar9 = cVar13;
              cVar13 = *local_7b8;
              pcVar9 = pcVar19;
            } while (cVar13 != (cRSubTracks)0x2e);
          }
          *pcVar19 = (cRSubTracks)0x2e;
          pcVar19[1] = (cRSubTracks)0x74;
          pcVar19[2] = (cRSubTracks)0x78;
          pcVar19[3] = (cRSubTracks)0x74;
          pcVar19[4] = (cRSubTracks)0x0;
          ImportSegment(this,(char *)local_5b4,(cRSubSegment *)(this + 0x1454));
          local_7b8 = (cRSubTracks *)
                      Rstrfind((char *)(iVar17 + DAT_000857d4),*(char **)(iVar17 + iVar3));
          if (local_7b8 == (cRSubTracks *)0x0) {
            RShellError((char *)(iVar17 + DAT_000862e8),&local_7b4);
            goto LAB_00085fd8;
          }
          local_7b8 = (cRSubTracks *)Rstrnewline((char *)local_7b8);
          if (local_7b8 != (cRSubTracks *)0x0) {
            cVar13 = *local_7b8;
            pcVar19 = (cRSubTracks *)local_5b4;
            while (cVar13 != (cRSubTracks)0x2e) {
              local_7b8 = local_7b8 + 1;
              *pcVar19 = cVar13;
              pcVar19 = pcVar19 + 1;
              cVar13 = *local_7b8;
            }
            *pcVar19 = (cRSubTracks)0x2e;
            pcVar19[1] = (cRSubTracks)0x74;
            pcVar19[2] = (cRSubTracks)0x78;
            pcVar19[3] = (cRSubTracks)0x74;
            pcVar19[4] = (cRSubTracks)0x0;
            ImportSegment(this,local_5b4,(cRSubSegment *)(this + 0x1488));
            ImportSegment(this,(char *)(iVar17 + DAT_000857d8),(cRSubSegment *)(this + 0x14bc));
            goto LAB_00085fd8;
          }
        }
      }
      RShellError((char *)(iVar17 + DAT_000862dc),&local_7b4);
    }
  }
LAB_00085fd8:
  if (local_34 == **(int **)(iVar17 + iVar2)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
LAB_00086160:
  do {
    pcVar12 = local_7b8;
    local_7b8 = pcVar12 + 1;
    cVar13 = *local_7b8;
  } while ((byte)cVar13 < 0x20);
  local_7b8 = pcVar12 + 2;
  pcVar19 = pcVar19 + 2;
  *pcVar9 = cVar13;
  goto joined_r0x00086118;
LAB_00085f10:
  local_7b8 = (cRSubTracks *)Rstrnewline((char *)local_7b8);
  if (local_7b8 == (cRSubTracks *)0x0) {
    RShellError((char *)(iVar17 + DAT_000862dc),param_1);
    goto LAB_00085fd8;
  }
  iVar5 = 1 - *(uint *)(this + 0x1588);
  if (1 < *(uint *)(this + 0x1588)) {
    iVar5 = 0;
  }
  goto LAB_00085668;
}
