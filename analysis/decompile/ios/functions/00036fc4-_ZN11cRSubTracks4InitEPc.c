/*
 * mangled: _ZN11cRSubTracks4InitEPc
 * demangled: cRSubTracks::Init(char*)
 * address: 00036fc4
 * size: 3896
 */

/* WARNING: Type propagation algorithm not settling */
/* cRSubTracks::Init(char*) */

void __thiscall cRSubTracks::Init(cRSubTracks *this,char *param_1)

{
  undefined *puVar1;
  byte bVar2;
  int iVar3;
  undefined4 uVar4;
  cRSubTracks *pcVar5;
  byte *pbVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  byte *pbVar11;
  byte *pbVar12;
  byte *pbVar13;
  byte *pbVar14;
  cRSubTracks *pcVar15;
  byte *pbVar16;
  bool bVar17;
  bool bVar18;
  uint in_fpscr;
  float fVar19;
  float fVar20;
  undefined8 uVar21;
  char local_7b0 [16];
  undefined2 local_7a0;
  undefined1 local_79e;
  byte local_5b0 [4];
  byte local_5ac [4];
  char acStack_5a8 [504];
  byte local_3b0 [4];
  byte local_3ac [508];
  byte local_1b0 [256];
  byte local_b0 [128];
  byte *local_30;
  byte *local_2c [3];
  cRSubTracks *pcVar6;

  _gSMLevelFileName = param_1;
  _sprintf(local_7b0,"Levels/%s",param_1);
  iVar3 = RShellLoadFile(local_7b0,&_gSMLevel,(int *)0x0);
  if (iVar3 == 0) {
    RShellError("Cannot find %s reverting to default.txt",local_7b0);
    builtin_strncpy(local_7b0,"Levels/Default.t",0x10);
    local_7a0 = 0x7478;
    local_79e = 0;
    RShellLoadFile(local_7b0,&_gSMLevel,(int *)0x0);
  }
  local_2c[0] = (byte *)Rstrfind("Name:\'",&_gSMLevel);
  if (local_2c[0] == (byte *)0x0) {
    RShellError("Cannot find Name:\' in %s",local_7b0);
  }
  uVar21 = Rstrfind("\'",(char *)local_2c[0]);
  iVar10 = (int)uVar21;
  pcVar15 = this + 0x11d0;
  local_2c[0] = (byte *)(iVar10 + 1);
  uVar8 = (uint)*(byte *)(iVar10 + 1);
  iVar9 = (int)(char)*(byte *)(iVar10 + 1);
  bVar18 = SBORROW4(uVar8,0x27);
  iVar3 = uVar8 - 0x27;
  bVar17 = uVar8 == 0x27;
  if (!bVar17) {
    bVar18 = SBORROW4(iVar9,0x1f);
    iVar3 = iVar9 + -0x1f;
  }
  pcVar5 = (cRSubTracks *)((ulonglong)uVar21 >> 0x20);
  if ((bVar17 || iVar9 == 0x1f) || iVar3 < 0 != bVar18) {
    pcVar5 = pcVar15;
  }
  if ((!bVar17 && iVar9 != 0x1f) && iVar3 < 0 == bVar18) {
    pbVar11 = (byte *)(iVar10 + 2);
    pcVar6 = pcVar15;
    do {
      local_2c[0] = pbVar11;
      pcVar5 = pcVar6 + 1;
      *pcVar6 = SUB41(uVar8,0);
      uVar8 = (uint)*local_2c[0];
      iVar10 = (int)(char)*local_2c[0];
      bVar18 = SBORROW4(uVar8,0x27);
      iVar3 = uVar8 - 0x27;
      if (uVar8 != 0x27) {
        bVar18 = SBORROW4(iVar10,0x1f);
        iVar3 = iVar10 + -0x1f;
      }
      pbVar11 = local_2c[0] + 1;
      pcVar6 = pcVar5;
    } while ((uVar8 != 0x27 && iVar10 != 0x1f) && iVar3 < 0 == bVar18);
  }
  *pcVar5 = (cRSubTracks)0x0;
  *(undefined4 *)(this + 0x1250) = 0;
  iVar3 = Rstrfind("Mode:Arcade",&_gSMLevel);
  if (iVar3 == 0) {
    iVar3 = Rstrfind("Mode:Challenge",&_gSMLevel);
    if (iVar3 == 0) {
      iVar3 = Rstrfind("Mode:Tutourial",&_gSMLevel);
      if (iVar3 != 0) {
        *(undefined4 *)(this + 0x1250) = 2;
      }
    }
    else {
      *(undefined4 *)(this + 0x1250) = 1;
    }
  }
  else {
    *(undefined4 *)(this + 0x1250) = 0;
  }
  if ((&DAT_00364950)
      [*(int *)(&DAT_00364944 + *(int *)PTR__Game_001b60b8) * 0x8e6c + *(int *)PTR__Game_001b60b8]
      == '\0') {
    local_2c[0] = (byte *)Rstrfind("ArcadePro",param_1);
    if (local_2c[0] == (byte *)0x0) {
      local_2c[0] = (byte *)Rstrfind("Arcade",param_1);
      iVar3 = 0;
      if (local_2c[0] == (byte *)0x0) {
        local_2c[0] = (byte *)0x0;
        goto LAB_000370e4;
      }
    }
    else {
      iVar3 = 1;
    }
    iVar10 = Rstrfind("e",(char *)local_2c[0]);
    local_2c[0] = (byte *)(iVar10 + 1);
    iVar10 = Rstrint((char **)local_2c);
    puVar1 = PTR__Game_001b60b8;
    iVar3 = iVar3 * 0x8e6c + iVar10 * 0x2a0;
    _strcpy((char *)(iVar3 + 0x364b6c + *(int *)PTR__Game_001b60b8),(char *)pcVar15);
    local_2c[0] = (byte *)Rstrfind("GalaxyText:",&_gSMLevel);
    if (local_2c[0] == (byte *)0x0) {
      RShellWarning("Cannot find GalaxyText: in %s",param_1);
      Rstrcpy((char *)(iVar3 + 0x364bec + *(int *)puVar1),"TEXT MISSING");
    }
    else {
      local_2c[0] = (byte *)Rstrfind("{",(char *)local_2c[0]);
      if (local_2c[0] == (byte *)0x0) {
        RShellWarning("Cannot find { for GalaxyText: in %s",param_1);
        Rstrcpy((char *)(iVar3 + 0x364bec + *(int *)puVar1),"TEXT ERROR { MISSING");
      }
      else {
        local_2c[0] = (byte *)Rstrnewline((char *)local_2c[0]);
        iVar10 = Rstrfind("}",(char *)local_2c[0]);
        if (iVar10 == 0) {
          RShellWarning("Cannot find } for GalaxyText: in %s",param_1);
          Rstrcpy((char *)(iVar3 + 0x364bec + *(int *)puVar1),"TEXT ERROR } MISSING");
        }
        else {
          pbVar11 = (byte *)(iVar3 + 0x364bec + *(int *)puVar1);
          for (; local_2c[0] < (byte *)(iVar10 + -2); local_2c[0] = local_2c[0] + 1) {
            if ((char)*local_2c[0] < ' ') {
              pbVar12 = pbVar11 + 1;
              *pbVar11 = 0x3e;
              bVar2 = *local_2c[0];
              while (pbVar11 = pbVar12, (char)bVar2 < ' ') {
                local_2c[0] = local_2c[0] + 1;
                bVar2 = *local_2c[0];
              }
            }
            *pbVar11 = *local_2c[0];
            pbVar11 = pbVar11 + 1;
          }
          *pbVar11 = 0;
        }
      }
    }
  }
LAB_000370e4:
  local_2c[0] = (byte *)Rstrfind("Random:yes",&_gSMLevel);
  if (local_2c[0] == (byte *)0x0) {
    *(undefined4 *)(this + 0x11b8) = 0;
    this[0x11bc] = (cRSubTracks)0x0;
    local_2c[0] = (byte *)0x0;
  }
  else {
    this[0x11bc] = (cRSubTracks)0x1;
    local_2c[0] = (byte *)Rstrfind("Length:",&_gSMLevel);
    if (local_2c[0] == (byte *)0x0) {
      RShellError("Cannot Length: in %s",local_7b0);
      return;
    }
    iVar3 = Rstrfind(":",(char *)local_2c[0]);
    local_2c[0] = (byte *)(iVar3 + 1);
    *(undefined4 *)(this + 0x11b8) = 0;
    bVar2 = *(byte *)(iVar3 + 1);
    if ((bVar2 != 0x41 && bVar2 != 0x61) && (pbVar11 = local_2c[0], (byte)(bVar2 - 0x30) < 10)) {
      do {
        *(int *)(this + 0x11b8) = *(int *)(this + 0x11b8) * 10 + -0x30 + (int)(char)bVar2;
        local_2c[0] = pbVar11 + 1;
        bVar2 = pbVar11[1];
        pbVar11 = local_2c[0];
      } while ((byte)(bVar2 - 0x30) < 10);
      local_2c[0] = (byte *)Rstrfind("Background:",&_gSMLevel);
      goto joined_r0x00037b90;
    }
  }
  local_2c[0] = (byte *)Rstrfind("Background:",&_gSMLevel);
joined_r0x00037b90:
  if (local_2c[0] == (byte *)0x0) {
    RShellError("No Background: in %s",local_7b0);
    return;
  }
  iVar3 = Rstrfind(":",(char *)local_2c[0]);
  local_2c[0] = (byte *)(iVar3 + 1);
  bVar2 = *(byte *)(iVar3 + 1);
  if (bVar2 == 0x2e) {
    pbVar12 = local_3b0;
    pbVar11 = local_3b0 + 1;
    pbVar16 = local_3ac;
  }
  else {
    pbVar11 = local_3b0 + 1;
    do {
      pbVar12 = pbVar11;
      local_2c[0] = local_2c[0] + 1;
      pbVar12[-1] = bVar2;
      bVar2 = *local_2c[0];
      pbVar11 = pbVar12 + 1;
    } while (bVar2 != 0x2e);
    pbVar16 = pbVar12 + 4;
  }
  *pbVar12 = 0x2e;
  *pbVar11 = 0x74;
  pbVar12[2] = 0x78;
  pbVar12[3] = 0x74;
  *pbVar16 = 0;
  uVar4 = cRLandscapeManager::Import
                    ((cRLandscapeManager *)(&DAT_003593d8 + *(int *)PTR__Game_001b60b8),
                     (char *)local_3b0);
  *(undefined4 *)(this + 0x1260) = uVar4;
  local_2c[0] = (byte *)Rstrfind("Fringe:",&_gSMLevel);
  if (local_2c[0] == (byte *)0x0) {
    RShellError("No Fringe: in %s using white",local_7b0);
    tColour::Set((tColour *)(this + 0x11c0),1.0,1.0,1.0,1.0);
    local_2c[0] = (byte *)Rstrfind("Track:",&_gSMLevel);
  }
  else {
    iVar3 = Rstrfind(":",(char *)local_2c[0]);
    fVar20 = 255.0;
    local_2c[0] = (byte *)(iVar3 + 1);
    uVar4 = Rstrint((char **)local_2c);
    fVar19 = (float)VectorSignedToFloat(uVar4,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(this + 0x11c0) = fVar19 / fVar20;
    uVar4 = Rstrint((char **)local_2c);
    fVar19 = (float)VectorSignedToFloat(uVar4,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(this + 0x11c4) = fVar19 / fVar20;
    uVar4 = Rstrint((char **)local_2c);
    fVar19 = (float)VectorSignedToFloat(uVar4,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(this + 0x11c8) = fVar19 / fVar20;
    local_2c[0] = (byte *)Rstrfind("Track:",&_gSMLevel);
  }
  if (local_2c[0] == (byte *)0x0) {
    local_2c[0] = (byte *)0x0;
    RShellError("No Track: in %s using Track0.tga",local_7b0);
    *(undefined4 *)(this + 0x1268) = 0;
  }
  else {
    iVar3 = Rstrfind(":",(char *)local_2c[0]);
    local_2c[0] = (byte *)(iVar3 + 1);
    iVar3 = (int)*(char *)(iVar3 + 1);
    if (((iVar3 == 0x30) ||
        ((((iVar3 == 0x31 || iVar3 == 0x32) || iVar3 == 0x33) || iVar3 == 0x34) || iVar3 == 0x35))
       || (iVar3 == 0x36)) {
      *(int *)(this + 0x1268) = iVar3 + -0x30;
    }
    else if (iVar3 == 0x72) {
      *(undefined4 *)(this + 0x1268) = 8;
    }
  }
  local_2c[0] = (byte *)Rstrfind("Parcels:",&_gSMLevel);
  if (local_2c[0] == (byte *)0x0) {
    *(undefined4 *)(this + 0x1264) = 0;
    RShellError("No Parcel: in %s",local_7b0);
  }
  else {
    local_2c[0] = (byte *)Rstrfind(":",(char *)local_2c[0]);
    uVar4 = Rstrint((char **)local_2c);
    *(undefined4 *)(this + 0x1264) = uVar4;
    local_2c[0] = (byte *)Rstrfind("Quota:",&_gSMLevel);
    if (local_2c[0] == (byte *)0x0) {
      *(undefined4 *)(this + 0x126c) = 0;
      RShellError("No Quota: in %s",local_7b0);
    }
    else {
      local_2c[0] = (byte *)Rstrfind(":",(char *)local_2c[0]);
      uVar4 = Rstrint((char **)local_2c);
      *(undefined4 *)(this + 0x126c) = uVar4;
      local_2c[0] = (byte *)Rstrfind("Speed:select",&_gSMLevel);
      if (local_2c[0] == (byte *)0x0) {
        local_2c[0] = (byte *)Rstrfind("Speed:",&_gSMLevel);
        if (local_2c[0] == (byte *)0x0) {
          RShellError("Cannot find Speed: in Segment %s\n",local_7b0);
          *(undefined4 *)(this + 0x1254) = 0x42c80000;
        }
        else {
          iVar3 = Rstrfind(":",(char *)local_2c[0]);
          local_2c[0] = (byte *)(iVar3 + 1);
          uVar4 = Rstrfloat((char **)local_2c);
          *(undefined4 *)(this + 0x1254) = uVar4;
        }
      }
      else {
        *(undefined4 *)(this + 0x1254) = 0xbf800000;
      }
      local_2c[0] = (byte *)Rstrfind("Garbage:",&_gSMLevel);
      if (local_2c[0] == (byte *)0x0) {
        *(undefined4 *)(this + 0x1258) = 0xbf800000;
      }
      else {
        uVar4 = Rstrfloat((char **)local_2c);
        *(undefined4 *)(this + 0x1258) = uVar4;
      }
      local_2c[0] = (byte *)Rstrfind("Salt:",&_gSMLevel);
      if (local_2c[0] == (byte *)0x0) {
        *(undefined4 *)(this + 0x125c) = 0xbf800000;
      }
      else {
        uVar4 = Rstrfloat((char **)local_2c);
        *(undefined4 *)(this + 0x125c) = uVar4;
      }
      *(undefined4 *)this = 0;
      local_2c[0] = (byte *)Rstrfind("Segments Begin:",&_gSMLevel);
      if (local_2c[0] == (byte *)0x0) {
        RShellError("Cannot find Segments Begin: in %s",local_7b0);
      }
      else {
        pbVar11 = (byte *)Rstrfind("Segments End:",&_gSMLevel);
        if (pbVar11 == (byte *)0x0) {
          RShellError("Cannot find Segments End: in %s",local_7b0);
        }
        else {
          local_2c[0] = (byte *)Rstrnewline((char *)local_2c[0]);
          if (local_2c[0] != (byte *)0x0) {
            uVar8 = 1 - *(uint *)(this + 0x1250);
            if (1 < *(uint *)(this + 0x1250)) {
              uVar8 = 0;
            }
LAB_00037574:
            if (local_2c[0] < pbVar11) {
              do {
                if (uVar8 == 0) {
                  bVar2 = *local_2c[0];
                  if (bVar2 == 0x2e) {
                    pbVar7 = local_5b0;
                    pbVar12 = local_5b0 + 1;
                    pbVar16 = local_5ac;
                  }
                  else {
                    pbVar16 = local_2c[0];
                    pbVar12 = local_5b0 + 1;
                    do {
                      pbVar7 = pbVar12;
                      pbVar14 = pbVar16 + 1;
                      pbVar7[-1] = bVar2;
                      bVar2 = *pbVar14;
                      pbVar16 = pbVar16 + 1;
                      pbVar12 = pbVar7 + 1;
                    } while (bVar2 != 0x2e);
                    pbVar16 = pbVar7 + 4;
                    local_2c[0] = pbVar14;
                  }
                  *pbVar7 = 0x2e;
                  *pbVar12 = 0x74;
                  pbVar7[2] = 0x78;
                  pbVar7[3] = 0x74;
                  *pbVar16 = 0;
                  ImportSegment(this,(char *)local_5b0,
                                (cRSubSegment *)(this + *(int *)this * 0x2c + 4));
                  bVar2 = local_2c[0][3];
                  if ((char)bVar2 < ' ') {
                    pbVar12 = local_1b0;
                    local_30 = local_2c[0] + 3;
                  }
                  else {
                    pbVar12 = local_1b0;
                    pbVar16 = local_2c[0] + 4;
                    do {
                      pbVar7 = pbVar16;
                      pbVar12 = pbVar12 + 1;
                      pbVar12[-1] = bVar2;
                      bVar2 = *pbVar7;
                      pbVar16 = pbVar7 + 1;
                      local_30 = pbVar7;
                    } while ('\x1f' < (char)bVar2);
                  }
                  *pbVar12 = 0;
                }
                else {
                  local_5b0[0] = 'P';
                  local_5b0[1] = 'a';
                  local_5b0[2] = 'd';
                  local_5b0[3] = 'd';
                  local_5ac[0] = 'i';
                  local_5ac[1] = 'n';
                  local_5ac[2] = 'g';
                  local_5ac[3] = '.';
                  acStack_5a8[0] = 't';
                  acStack_5a8[1] = 'x';
                  acStack_5a8[2] = 't';
                  acStack_5a8[3] = '\0';
                  ImportSegment(this,(char *)local_5b0,
                                (cRSubSegment *)(this + *(int *)this * 0x2c + 4));
                  local_1b0[0] = 0;
                }
                local_30 = (byte *)Rstrfind("Angle=",(char *)local_1b0);
                if (local_30 == (byte *)0x0) {
                  *(undefined4 *)(this + *(int *)this * 0x2c + 0x20) = 0;
                  local_30 = (byte *)0x0;
                }
                else {
                  local_30 = (byte *)Rstrfind("=",(char *)local_30);
                  iVar3 = *(int *)this;
                  uVar4 = Rstrint((char **)&local_30);
                  fVar19 = (float)VectorSignedToFloat(uVar4,(byte)(in_fpscr >> 0x16) & 3);
                  *(float *)(this + iVar3 * 0x2c + 0x20) = ((fVar19 + fVar19) * 3.1415927) / 360.0;
                }
                *(undefined4 *)(this + *(int *)this * 0x2c + 0x24) = 0;
                local_30 = (byte *)Rstrfind("Message=",(char *)local_1b0);
                if (local_30 == (byte *)0x0) {
LAB_00037ba4:
                  iVar3 = *(int *)this + 1;
                  *(int *)this = iVar3;
                }
                else {
                  iVar3 = Rstrfind("=",(char *)local_30);
                  local_30 = (byte *)(iVar3 + 1);
                  if (*(char *)(iVar3 + 1) != '\"') {
                    RShellError("Need \" after Message=");
                    return;
                  }
                  local_30 = (byte *)(iVar3 + 2);
                  bVar2 = *(byte *)(iVar3 + 2);
                  pbVar12 = local_30;
                  while (bVar2 != 0x22) {
                    pbVar12 = pbVar12 + 1;
                    bVar2 = *pbVar12;
                  }
                  iVar3 = *(int *)this;
                  uVar4 = RShellMemoryMalloc((int)(pbVar12 + (8 - (int)local_30)),"Segment Message")
                  ;
                  *(undefined4 *)(this + iVar3 * 0x2c + 0x24) = uVar4;
                  pbVar14 = *(byte **)(this + *(int *)this * 0x2c + 0x24);
                  pbVar16 = pbVar14;
                  pbVar7 = local_30;
                  if (local_30 < pbVar12) {
                    do {
                      pbVar13 = pbVar7 + 1;
                      *pbVar16 = *pbVar7;
                      pbVar16 = pbVar16 + 1;
                      pbVar7 = pbVar13;
                    } while (pbVar13 != pbVar12);
                    pbVar14 = pbVar14 + ((int)pbVar12 - (int)local_30);
                    local_30 = pbVar13;
                  }
                  *pbVar14 = 0;
                  local_30 = (byte *)Rstrfind("Duration=",(char *)local_1b0);
                  *(undefined1 **)(this + *(int *)this * 0x2c + 0x28) = &DAT_40800000;
                  if (local_30 != (byte *)0x0) {
                    iVar3 = Rstrfind("=",(char *)local_30);
                    iVar10 = *(int *)this;
                    local_30 = (byte *)(iVar3 + 1);
                    uVar4 = Rstrfloat((char **)&local_30);
                    *(undefined4 *)(this + iVar10 * 0x2c + 0x28) = uVar4;
                  }
                  local_30 = (byte *)Rstrfind("Sample=",(char *)local_1b0);
                  *(undefined4 *)(this + (*(int *)this + 1) * 0x2c) = 0xffffffff;
                  if (local_30 == (byte *)0x0) goto LAB_00037ba4;
                  iVar3 = Rstrfind("=",(char *)local_30);
                  local_30 = (byte *)(iVar3 + 2);
                  pbVar12 = local_b0;
                  while (bVar2 = *local_30, bVar2 != 0x2e) {
                    if (bVar2 == 0x2f) {
                      local_30 = local_30 + 1;
                      pbVar12 = local_b0;
                    }
                    else {
                      *pbVar12 = bVar2;
                      local_30 = local_30 + 1;
                      pbVar12 = pbVar12 + 1;
                    }
                  }
                  *pbVar12 = 0;
                  iVar3 = *(int *)this;
                  uVar4 = RShellFindSample((char *)local_b0);
                  *(undefined4 *)(this + (iVar3 + 1) * 0x2c) = uVar4;
                  iVar3 = *(int *)this;
                  if (*(int *)(this + (iVar3 + 1) * 0x2c) == -1) {
                    RShellError("Cannot find sample %s in %s",local_b0,local_7b0);
                    iVar3 = *(int *)this;
                  }
                  iVar3 = iVar3 + 1;
                  *(int *)this = iVar3;
                }
                if (100 < iVar3) {
                  RShellError("Too many Segments RSUBGAME_SEGMENTS_MAX=%i",100);
                }
                if (uVar8 != 0) goto code_r0x00037968;
                local_2c[0] = (byte *)Rstrnewline((char *)local_2c[0]);
                if (local_2c[0] == (byte *)0x0) {
                  RShellError("Unexpected end of file in %s",param_1);
                  return;
                }
                uVar8 = (uint)(*(int *)(this + 0x1250) == 0);
                if (pbVar11 <= local_2c[0]) break;
              } while( true );
            }
            local_2c[0] = (byte *)Rstrfind("First:",&_gSMLevel);
            if (local_2c[0] == (byte *)0x0) {
              RShellError("Cannot find \'First:\' in %s",local_7b0);
              return;
            }
            local_2c[0] = (byte *)Rstrnewline((char *)local_2c[0]);
            if (local_2c[0] != (byte *)0x0) {
              bVar2 = *local_2c[0];
              if (bVar2 == 0x2e) {
                pbVar16 = local_5b0;
                pbVar11 = local_5b0 + 1;
                pbVar12 = local_5ac;
              }
              else {
                pbVar11 = local_5b0 + 1;
                do {
                  pbVar16 = pbVar11;
                  local_2c[0] = local_2c[0] + 1;
                  pbVar16[-1] = bVar2;
                  bVar2 = *local_2c[0];
                  pbVar11 = pbVar16 + 1;
                } while (bVar2 != 0x2e);
                pbVar12 = pbVar16 + 4;
              }
              *pbVar16 = 0x2e;
              *pbVar11 = 0x74;
              pbVar16[2] = 0x78;
              pbVar16[3] = 0x74;
              *pbVar12 = 0;
              ImportSegment(this,(char *)local_5b0,(cRSubSegment *)(this + 0x1134));
              local_2c[0] = (byte *)Rstrfind("Last:",&_gSMLevel);
              if (local_2c[0] == (byte *)0x0) {
                RShellError("Cannot find \'Last:\' in %s",local_7b0);
                return;
              }
              local_2c[0] = (byte *)Rstrnewline((char *)local_2c[0]);
              if (local_2c[0] != (byte *)0x0) {
                bVar2 = *local_2c[0];
                if (bVar2 == 0x2e) {
                  pbVar11 = local_5b0 + 1;
                  pbVar12 = local_5ac;
                  pbVar16 = local_5b0;
                }
                else {
                  pbVar11 = local_5b0 + 1;
                  do {
                    pbVar16 = pbVar11;
                    local_2c[0] = local_2c[0] + 1;
                    pbVar16[-1] = bVar2;
                    bVar2 = *local_2c[0];
                    pbVar11 = pbVar16 + 1;
                  } while (bVar2 != 0x2e);
                  pbVar12 = pbVar16 + 4;
                }
                *pbVar16 = 0x2e;
                *pbVar11 = 0x74;
                pbVar16[2] = 0x78;
                pbVar16[3] = 0x74;
                *pbVar12 = 0;
                ImportSegment(this,(char *)local_5b0,(cRSubSegment *)(this + 0x1160));
                ImportSegment(this,"padding.txt",(cRSubSegment *)(this + 0x118c));
                return;
              }
            }
          }
          RShellError("Unexpected end of file in %s",local_7b0);
        }
      }
    }
  }
  return;
code_r0x00037968:
  uVar8 = 0;
  goto LAB_00037574;
}
