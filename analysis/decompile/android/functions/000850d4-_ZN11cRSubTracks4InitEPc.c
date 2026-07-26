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
  undefined4 uVar3;
  cRSubTracks *pcVar4;
  uint uVar5;
  cRSubTracks *pcVar6;
  cRSubTracks cVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  cRSubTracks *pcVar11;
  undefined1 *puVar12;
  bool bVar13;
  bool bVar14;
  uint in_fpscr;
  float extraout_s0;
  float extraout_s1;
  float extraout_s2;
  float extraout_s3;
  float fVar15;
  undefined8 uVar16;
  cRSubTracks *local_7bc;
  cRSubTracks *local_7b8;
  char local_7b4 [4];
  char acStack_7b0 [4];
  char acStack_7ac [4];
  char acStack_7a8 [4];
  undefined2 local_7a4;
  undefined1 local_7a2;
  cRSubTracks local_5b4 [4];
  char local_5b0 [4];
  char acStack_5ac [504];
  cRSubTracks local_3b4 [512];
  cRSubTracks local_1b4 [256];
  cRSubTracks local_b4 [128];
  int local_34;

  local_34 = __stack_chk_guard;
  gSMLevelFileName = param_1;
  sprintf(local_7b4,"Levels/%s");
  iVar2 = RShellLoadFile(local_7b4,gSMLevel,(int *)0x0);
  if (iVar2 == 0) {
    RShellError("Cannot find %s reverting to default.txt",local_7b4);
    local_7b4[0] = 'L';
    local_7b4[1] = 'e';
    local_7b4[2] = 'v';
    local_7b4[3] = 'e';
    acStack_7b0[0] = 'l';
    acStack_7b0[1] = 's';
    acStack_7b0[2] = '/';
    acStack_7b0[3] = 'D';
    acStack_7ac[0] = 'e';
    acStack_7ac[1] = 'f';
    acStack_7ac[2] = 'a';
    acStack_7ac[3] = 'u';
    acStack_7a8[0] = 'l';
    acStack_7a8[1] = 't';
    acStack_7a8[2] = '.';
    acStack_7a8[3] = 't';
    local_7a4 = 0x7478;
    local_7a2 = 0;
    RShellLoadFile(local_7b4,gSMLevel,(int *)0x0);
  }
  local_7b8 = (cRSubTracks *)Rstrfind("Name:\'",gSMLevel);
  if (local_7b8 == (cRSubTracks *)0x0) {
    RShellError("Cannot find Name:\' in %s",local_7b4);
  }
  pcVar11 = this + 0x1508;
  uVar16 = Rstrfind("\'",(char *)local_7b8);
  local_7b8 = (cRSubTracks *)((int)uVar16 + 1);
  cVar7 = *(cRSubTracks *)((int)uVar16 + 1);
  bVar14 = 0x26 < (byte)cVar7;
  bVar13 = cVar7 == (cRSubTracks)0x27;
  if (!bVar13) {
    bVar14 = 0x1e < (byte)cVar7;
  }
  pcVar4 = (cRSubTracks *)((ulonglong)uVar16 >> 0x20);
  if (!bVar14 || (bVar13 || cVar7 == (cRSubTracks)0x1f)) {
    pcVar4 = pcVar11;
  }
  pcVar6 = pcVar11;
  if (bVar14 && (!bVar13 && cVar7 != (cRSubTracks)0x1f)) {
    do {
      local_7b8 = local_7b8 + 1;
      pcVar4 = pcVar6 + 1;
      *pcVar6 = cVar7;
      cVar7 = *local_7b8;
      bVar14 = 0x26 < (byte)cVar7;
      if (cVar7 != (cRSubTracks)0x27) {
        bVar14 = 0x1e < (byte)cVar7;
      }
      pcVar6 = pcVar4;
    } while (bVar14 && (cVar7 != (cRSubTracks)0x27 && cVar7 != (cRSubTracks)0x1f));
  }
  *pcVar4 = (cRSubTracks)0x0;
  *(undefined4 *)(this + 0x1588) = 0;
  iVar2 = Rstrfind("Mode:Arcade",gSMLevel);
  if (iVar2 == 0) {
    iVar2 = Rstrfind("Mode:Challenge",gSMLevel);
    if (iVar2 == 0) {
      iVar2 = Rstrfind("Mode:Tutourial",gSMLevel);
      if (iVar2 != 0) {
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
  if (gOFOData[*(int *)(gOFOData + Game + 0x1ebc) * 0x8e6c + Game + 0x1ec8] == '\0') {
    local_7b8 = (cRSubTracks *)Rstrfind("ArcadePro",param_1);
    if (local_7b8 == (cRSubTracks *)0x0) {
      local_7b8 = (cRSubTracks *)Rstrfind("Arcade",param_1);
      if (local_7b8 == (cRSubTracks *)0x0) goto LAB_00085228;
      iVar2 = 0;
    }
    else {
      iVar2 = 1;
    }
    iVar9 = Rstrfind("e",(char *)local_7b8);
    local_7b8 = (cRSubTracks *)(iVar9 + 1);
    iVar9 = Rstrint((char **)&local_7b8);
    iVar2 = iVar2 * 0x8e6c;
    strcpy(gOFOData + Game + iVar9 * 0x2a0 + iVar2 + 0x20e4,(char *)pcVar11);
    local_7b8 = (cRSubTracks *)Rstrfind("GalaxyText:",gSMLevel);
    if (local_7b8 == (cRSubTracks *)0x0) {
      RShellWarning("Cannot find GalaxyText: in %s",param_1);
      Rstrcpy(gOFOData + Game + (iVar9 + 1) * 0x2a0 + iVar2 + 0x1ec4,"TEXT MISSING");
    }
    else {
      local_7b8 = (cRSubTracks *)Rstrfind("{",(char *)local_7b8);
      if (local_7b8 == (cRSubTracks *)0x0) {
        RShellWarning("Cannot find { for GalaxyText: in %s",param_1);
        Rstrcpy(gOFOData + Game + (iVar9 + 1) * 0x2a0 + iVar2 + 0x1ec4,"TEXT ERROR { MISSING");
      }
      else {
        local_7b8 = (cRSubTracks *)Rstrnewline((char *)local_7b8);
        iVar10 = Rstrfind("}",(char *)local_7b8);
        if (iVar10 != 0) {
          pcVar11 = (cRSubTracks *)(gOFOData + Game + iVar9 * 0x2a0 + iVar2 + 0x2164);
joined_r0x00086118:
          if (local_7b8 < (cRSubTracks *)(iVar10 + -2)) {
            do {
              if ((byte)*local_7b8 < 0x20) {
                pcVar4 = pcVar11 + 1;
                *pcVar11 = (cRSubTracks)0x3e;
                cVar7 = *local_7b8;
                if ((byte)cVar7 < 0x20) goto LAB_00086160;
              }
              else {
                cVar7 = *local_7b8;
                pcVar4 = pcVar11;
              }
              local_7b8 = local_7b8 + 1;
              pcVar11 = pcVar4 + 1;
              *pcVar4 = cVar7;
              if ((cRSubTracks *)(iVar10 + -2) <= local_7b8) break;
            } while( true );
          }
          *pcVar11 = (cRSubTracks)0x0;
          goto LAB_00085228;
        }
        RShellWarning("Cannot find } for GalaxyText: in %s",param_1);
        Rstrcpy(gOFOData + Game + (iVar9 + 1) * 0x2a0 + iVar2 + 0x1ec4,"TEXT ERROR } MISSING");
      }
    }
  }
LAB_00085228:
  local_7b8 = (cRSubTracks *)Rstrfind("Random:yes",gSMLevel);
  if (local_7b8 == (cRSubTracks *)0x0) {
    *(undefined4 *)(this + 0x14f0) = 0;
    this[0x14f4] = (cRSubTracks)0x0;
    local_7b8 = (cRSubTracks *)0x0;
LAB_000852ac:
    local_7b8 = (cRSubTracks *)Rstrfind("Background:",gSMLevel);
  }
  else {
    this[0x14f4] = (cRSubTracks)0x1;
    local_7b8 = (cRSubTracks *)Rstrfind("Length:",gSMLevel);
    if (local_7b8 == (cRSubTracks *)0x0) {
      RShellError("Cannot Length: in %s",local_7b4);
      goto LAB_00085fd8;
    }
    iVar2 = Rstrfind(":",(char *)local_7b8);
    *(undefined4 *)(this + 0x14f0) = 0;
    local_7b8 = (cRSubTracks *)(iVar2 + 1);
    uVar5 = (uint)*(byte *)(iVar2 + 1);
    uVar8 = (uint)(uVar5 == 0x61 || uVar5 == 0x41);
    if ((uVar5 == 0x61 || uVar5 == 0x41) || (9 < (uVar5 - 0x30 & 0xff))) goto LAB_000852ac;
    do {
      local_7b8 = local_7b8 + 1;
      uVar8 = (uVar5 + uVar8 * 10) - 0x30;
      *(uint *)(this + 0x14f0) = uVar8;
      uVar5 = (uint)(byte)*local_7b8;
    } while ((uVar5 - 0x30 & 0xff) < 10);
    local_7b8 = (cRSubTracks *)Rstrfind("Background:",gSMLevel);
  }
  if (local_7b8 == (cRSubTracks *)0x0) {
    RShellError("No Background: in %s",local_7b4);
    goto LAB_00085fd8;
  }
  iVar2 = Rstrfind(":",(char *)local_7b8);
  local_7b8 = (cRSubTracks *)(iVar2 + 1);
  cVar7 = *(cRSubTracks *)(iVar2 + 1);
  if (cVar7 == (cRSubTracks)0x2e) {
    pcVar11 = local_3b4;
  }
  else {
    pcVar11 = local_3b4;
    do {
      pcVar11 = pcVar11 + 1;
      local_7b8 = local_7b8 + 1;
      pcVar11[-1] = cVar7;
      cVar7 = *local_7b8;
    } while (cVar7 != (cRSubTracks)0x2e);
  }
  *pcVar11 = (cRSubTracks)0x2e;
  pcVar11[1] = (cRSubTracks)0x74;
  pcVar11[2] = (cRSubTracks)0x78;
  pcVar11[3] = (cRSubTracks)0x74;
  pcVar11[4] = (cRSubTracks)0x0;
  uVar3 = cRLandscapeManager::Import
                    ((cRLandscapeManager *)(gSegmentText + Game + 0x3d8),(char *)local_3b4);
  *(undefined4 *)(this + 0x1598) = uVar3;
  local_7b8 = (cRSubTracks *)Rstrfind("Fringe:",gSMLevel);
  if (local_7b8 == (cRSubTracks *)0x0) {
    RShellError("No Fringe: in %s using white",local_7b4);
    tColour::Set((tColour *)(this + 0x14f8),extraout_s0,extraout_s1,extraout_s2,extraout_s3);
  }
  else {
    iVar2 = Rstrfind(":",(char *)local_7b8);
    local_7b8 = (cRSubTracks *)(iVar2 + 1);
    uVar3 = Rstrint((char **)&local_7b8);
    fVar15 = (float)VectorSignedToFloat(uVar3,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(this + 0x14f8) = fVar15 / 255.0;
    uVar3 = Rstrint((char **)&local_7b8);
    fVar15 = (float)VectorSignedToFloat(uVar3,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(this + 0x14fc) = fVar15 / 255.0;
    uVar3 = Rstrint((char **)&local_7b8);
    fVar15 = (float)VectorSignedToFloat(uVar3,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(this + 0x1500) = fVar15 / 255.0;
  }
  local_7b8 = (cRSubTracks *)Rstrfind("Track:",gSMLevel);
  if (local_7b8 == (cRSubTracks *)0x0) {
    RShellError("No Track: in %s using Track0.tga",local_7b4);
    *(undefined4 *)(this + 0x15a0) = 0;
  }
  else {
    iVar2 = Rstrfind(":",(char *)local_7b8);
    local_7b8 = (cRSubTracks *)(iVar2 + 1);
    cVar1 = *(char *)(iVar2 + 1);
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
  local_7b8 = (cRSubTracks *)Rstrfind("Parcels:",gSMLevel);
  if (local_7b8 == (cRSubTracks *)0x0) {
    *(undefined4 *)(this + 0x159c) = 0;
    RShellError("No Parcel: in %s",local_7b4);
    goto LAB_00085fd8;
  }
  local_7b8 = (cRSubTracks *)Rstrfind(":",(char *)local_7b8);
  uVar3 = Rstrint((char **)&local_7b8);
  *(undefined4 *)(this + 0x159c) = uVar3;
  local_7b8 = (cRSubTracks *)Rstrfind("Quota:",gSMLevel);
  if (local_7b8 == (cRSubTracks *)0x0) {
    *(undefined4 *)(this + 0x15a4) = 0;
    RShellError("No Quota: in %s",local_7b4);
    goto LAB_00085fd8;
  }
  local_7b8 = (cRSubTracks *)Rstrfind(":",(char *)local_7b8);
  uVar3 = Rstrint((char **)&local_7b8);
  *(undefined4 *)(this + 0x15a4) = uVar3;
  local_7b8 = (cRSubTracks *)Rstrfind("Speed:select",gSMLevel);
  if (local_7b8 == (cRSubTracks *)0x0) {
    local_7b8 = (cRSubTracks *)Rstrfind("Speed:",gSMLevel);
    if (local_7b8 == (cRSubTracks *)0x0) {
      RShellError("Cannot find Speed: in Segment %s\n",local_7b4);
      *(undefined4 *)(this + 0x158c) = 0x42c80000;
    }
    else {
      iVar2 = Rstrfind(":",(char *)local_7b8);
      local_7b8 = (cRSubTracks *)(iVar2 + 1);
      uVar3 = Rstrfloat((char **)&local_7b8);
      *(undefined4 *)(this + 0x158c) = uVar3;
    }
  }
  else {
    *(undefined4 *)(this + 0x158c) = 0xbf800000;
  }
  local_7b8 = (cRSubTracks *)Rstrfind("Garbage:",gSMLevel);
  if (local_7b8 == (cRSubTracks *)0x0) {
    *(undefined4 *)(this + 0x1590) = 0xbf800000;
    local_7b8 = (cRSubTracks *)Rstrfind("Salt:",gSMLevel);
    if (local_7b8 == (cRSubTracks *)0x0) goto LAB_00085eb8;
LAB_000855b8:
    uVar3 = Rstrfloat((char **)&local_7b8);
    *(undefined4 *)(this + 0x1594) = uVar3;
  }
  else {
    uVar3 = Rstrfloat((char **)&local_7b8);
    *(undefined4 *)(this + 0x1590) = uVar3;
    local_7b8 = (cRSubTracks *)Rstrfind("Salt:",gSMLevel);
    if (local_7b8 != (cRSubTracks *)0x0) goto LAB_000855b8;
LAB_00085eb8:
    *(undefined4 *)(this + 0x1594) = 0xbf800000;
  }
  *(undefined4 *)this = 0;
  local_7b8 = (cRSubTracks *)Rstrfind("Segments Begin:",gSMLevel);
  if (local_7b8 == (cRSubTracks *)0x0) {
    RShellError("Cannot find Segments Begin: in %s",local_7b4);
  }
  else {
    pcVar11 = (cRSubTracks *)Rstrfind("Segments End:",gSMLevel);
    if (pcVar11 == (cRSubTracks *)0x0) {
      RShellError("Cannot find Segments End: in %s",local_7b4);
    }
    else {
      local_7b8 = (cRSubTracks *)Rstrnewline((char *)local_7b8);
      if (local_7b8 != (cRSubTracks *)0x0) {
        iVar2 = 1 - *(uint *)(this + 0x1588);
        if (1 < *(uint *)(this + 0x1588)) {
          iVar2 = 0;
        }
LAB_00085668:
        if (local_7b8 < pcVar11) {
          do {
            if (iVar2 == 0) {
              cVar7 = *local_7b8;
              if (cVar7 == (cRSubTracks)0x2e) {
                pcVar6 = local_5b4;
                pcVar4 = local_5b4 + 1;
              }
              else {
                pcVar4 = local_5b4 + 1;
                do {
                  pcVar6 = pcVar4;
                  local_7b8 = local_7b8 + 1;
                  pcVar6[-1] = cVar7;
                  cVar7 = *local_7b8;
                  pcVar4 = pcVar6 + 1;
                } while (cVar7 != (cRSubTracks)0x2e);
              }
              *pcVar6 = (cRSubTracks)0x2e;
              *pcVar4 = (cRSubTracks)0x74;
              pcVar6[2] = (cRSubTracks)0x78;
              pcVar6[3] = (cRSubTracks)0x74;
              pcVar6[4] = (cRSubTracks)0x0;
              ImportSegment(this,(char *)local_5b4,(cRSubSegment *)(this + *(int *)this * 0x34 + 4))
              ;
              local_7bc = local_7b8 + 3;
              cVar7 = local_7b8[3];
              if ((byte)cVar7 < 0x20) {
                pcVar4 = local_1b4;
              }
              else {
                pcVar4 = local_1b4;
                pcVar6 = local_7b8 + 4;
                do {
                  local_7bc = pcVar6;
                  pcVar4 = pcVar4 + 1;
                  pcVar4[-1] = cVar7;
                  cVar7 = *local_7bc;
                  pcVar6 = local_7bc + 1;
                } while (0x1f < (byte)cVar7);
              }
              *pcVar4 = (cRSubTracks)0x0;
            }
            else {
              local_5b4[0] = 'P';
              local_5b4[1] = 'a';
              local_5b4[2] = 'd';
              local_5b4[3] = 'd';
              local_5b0[0] = 'i';
              local_5b0[1] = 'n';
              local_5b0[2] = 'g';
              local_5b0[3] = '.';
              acStack_5ac[0] = 't';
              acStack_5ac[1] = 'x';
              acStack_5ac[2] = 't';
              acStack_5ac[3] = '\0';
              ImportSegment(this,(char *)local_5b4,(cRSubSegment *)(this + *(int *)this * 0x34 + 4))
              ;
              local_1b4[0] = (cRSubTracks)0x0;
            }
            local_7bc = (cRSubTracks *)Rstrfind("Angle=",(char *)local_1b4);
            if (local_7bc == (cRSubTracks *)0x0) {
              iVar9 = *(int *)this;
              *(undefined4 *)(this + iVar9 * 0x34 + 0x20) = 0;
              local_7bc = (cRSubTracks *)0x0;
            }
            else {
              local_7bc = (cRSubTracks *)Rstrfind("=",(char *)local_7bc);
              iVar10 = *(int *)this;
              uVar3 = Rstrint((char **)&local_7bc);
              iVar9 = *(int *)this;
              fVar15 = (float)VectorSignedToFloat(uVar3,(byte)(in_fpscr >> 0x16) & 3);
              *(float *)(this + iVar10 * 0x34 + 0x20) = ((fVar15 + fVar15) * 3.1415927) / 360.0;
            }
            *(undefined4 *)(this + iVar9 * 0x34 + 0x24) = 0;
            local_7bc = (cRSubTracks *)Rstrfind("Message=",(char *)local_1b4);
            if (local_7bc == (cRSubTracks *)0x0) goto LAB_00085f50;
            iVar9 = Rstrfind("=",(char *)local_7bc);
            if (*(char *)(iVar9 + 1) != '\"') {
LAB_00085fcc:
              local_7bc = (cRSubTracks *)(iVar9 + 1);
              RShellError("Need \" after Message=");
              goto LAB_00085fd8;
            }
            local_7bc = (cRSubTracks *)(iVar9 + 2);
            cVar7 = *(cRSubTracks *)(iVar9 + 2);
            pcVar4 = local_7bc;
            while (cVar7 != (cRSubTracks)0x22) {
              pcVar4 = pcVar4 + 1;
              cVar7 = *pcVar4;
            }
            iVar10 = *(int *)this;
            uVar3 = RShellMemoryMalloc((int)(pcVar4 + (8 - (int)local_7bc)),"Segment Message");
            iVar9 = *(int *)this;
            *(undefined4 *)(this + iVar10 * 0x34 + 0x24) = uVar3;
            puVar12 = *(undefined1 **)(this + iVar9 * 0x34 + 0x24);
            if (local_7bc < pcVar4) {
              iVar9 = 0;
              pcVar6 = local_7bc;
              do {
                pcVar6 = pcVar6 + 1;
                *(cRSubTracks *)(puVar12 + iVar9) = local_7bc[iVar9];
                iVar9 = iVar9 + 1;
              } while (pcVar6 < pcVar4);
              puVar12 = puVar12 + ((int)pcVar4 - (int)local_7bc);
              local_7bc = pcVar6;
            }
            *puVar12 = 0;
            local_7bc = (cRSubTracks *)Rstrfind("Duration=",(char *)local_1b4);
            *(undefined4 *)(this + *(int *)this * 0x34 + 0x28) = 0x40800000;
            if (local_7bc != (cRSubTracks *)0x0) {
              iVar9 = Rstrfind("=",(char *)local_7bc);
              iVar10 = *(int *)this;
              local_7bc = (cRSubTracks *)(iVar9 + 1);
              uVar3 = Rstrfloat((char **)&local_7bc);
              *(undefined4 *)(this + iVar10 * 0x34 + 0x28) = uVar3;
            }
            local_7bc = (cRSubTracks *)Rstrfind("Sample=",(char *)local_1b4);
            *(undefined4 *)(this + *(int *)this * 0x34 + 0x2c) = 0xffffffff;
            if (local_7bc == (cRSubTracks *)0x0) {
LAB_00085f50:
              iVar9 = *(int *)this;
            }
            else {
              iVar9 = Rstrfind("=",(char *)local_7bc);
              pcVar4 = local_b4;
              for (local_7bc = (cRSubTracks *)(iVar9 + 2); cVar7 = *local_7bc,
                  cVar7 != (cRSubTracks)0x2e; local_7bc = local_7bc + 1) {
                pcVar6 = local_b4;
                if (cVar7 != (cRSubTracks)0x2f) {
                  *pcVar4 = cVar7;
                  pcVar6 = pcVar4 + 1;
                }
                pcVar4 = pcVar6;
              }
              iVar9 = *(int *)this;
              *pcVar4 = (cRSubTracks)0x0;
              uVar3 = cRVoiceManager::FindSample((cRVoiceManager *)&gVoiceManager,(char *)local_b4);
              *(undefined4 *)(this + iVar9 * 0x34 + 0x2c) = uVar3;
              iVar9 = *(int *)this;
              if (*(int *)(this + iVar9 * 0x34 + 0x2c) == -1) {
                RShellError("Cannot find sample %s in %s",local_b4,local_7b4);
                goto LAB_00085f50;
              }
            }
            *(undefined4 *)(this + iVar9 * 0x34 + 0x30) = 0;
            local_7bc = (cRSubTracks *)Rstrfind("MessageB=",(char *)local_1b4);
            if (local_7bc == (cRSubTracks *)0x0) goto LAB_00085ee4;
            iVar9 = Rstrfind("=",(char *)local_7bc);
            if (*(char *)(iVar9 + 1) != '\"') goto LAB_00085fcc;
            local_7bc = (cRSubTracks *)(iVar9 + 2);
            cVar7 = *(cRSubTracks *)(iVar9 + 2);
            pcVar4 = local_7bc;
            while (cVar7 != (cRSubTracks)0x22) {
              pcVar4 = pcVar4 + 1;
              cVar7 = *pcVar4;
            }
            iVar10 = *(int *)this;
            uVar3 = RShellMemoryMalloc((int)(pcVar4 + (8 - (int)local_7bc)),"Segment MessageB");
            iVar9 = *(int *)this;
            *(undefined4 *)(this + iVar10 * 0x34 + 0x30) = uVar3;
            puVar12 = *(undefined1 **)(this + iVar9 * 0x34 + 0x30);
            if (local_7bc < pcVar4) {
              iVar9 = 0;
              pcVar6 = local_7bc;
              do {
                pcVar6 = pcVar6 + 1;
                *(cRSubTracks *)(puVar12 + iVar9) = local_7bc[iVar9];
                iVar9 = iVar9 + 1;
              } while (pcVar6 < pcVar4);
              puVar12 = puVar12 + ((int)pcVar4 - (int)local_7bc);
              local_7bc = pcVar6;
            }
            *puVar12 = 0;
            local_7bc = (cRSubTracks *)Rstrfind("Duration=",(char *)local_1b4);
            *(undefined4 *)(this + *(int *)this * 0x34 + 0x28) = 0x40800000;
            if (local_7bc != (cRSubTracks *)0x0) {
              iVar9 = Rstrfind("=",(char *)local_7bc);
              iVar10 = *(int *)this;
              local_7bc = (cRSubTracks *)(iVar9 + 1);
              uVar3 = Rstrfloat((char **)&local_7bc);
              *(undefined4 *)(this + iVar10 * 0x34 + 0x28) = uVar3;
            }
            local_7bc = (cRSubTracks *)Rstrfind("SampleB=",(char *)local_1b4);
            *(undefined4 *)(this + *(int *)this * 0x34 + 0x34) = 0xffffffff;
            if (local_7bc == (cRSubTracks *)0x0) {
LAB_00085ee4:
              iVar9 = *(int *)this + 1;
              *(int *)this = iVar9;
            }
            else {
              iVar9 = Rstrfind("=",(char *)local_7bc);
              pcVar4 = local_b4;
              for (local_7bc = (cRSubTracks *)(iVar9 + 2); cVar7 = *local_7bc,
                  cVar7 != (cRSubTracks)0x2e; local_7bc = local_7bc + 1) {
                pcVar6 = local_b4;
                if (cVar7 != (cRSubTracks)0x2f) {
                  *pcVar4 = cVar7;
                  pcVar6 = pcVar4 + 1;
                }
                pcVar4 = pcVar6;
              }
              iVar9 = *(int *)this;
              *pcVar4 = (cRSubTracks)0x0;
              uVar3 = cRVoiceManager::FindSample((cRVoiceManager *)&gVoiceManager,(char *)local_b4);
              *(undefined4 *)(this + iVar9 * 0x34 + 0x34) = uVar3;
              if (*(int *)(this + *(int *)this * 0x34 + 0x34) == -1) {
                RShellError("Cannot find sampleB %s in %s",local_b4,local_7b4);
                goto LAB_00085ee4;
              }
              iVar9 = *(int *)this + 1;
              *(int *)this = iVar9;
            }
            if (100 < iVar9) {
              RShellError("Too many Segments RSUBGAME_SEGMENTS_MAX=%i",100);
            }
            if (iVar2 == 0) goto LAB_00085f10;
            iVar2 = 0;
            if (pcVar11 <= local_7b8) break;
          } while( true );
        }
        local_7b8 = (cRSubTracks *)Rstrfind("First:",gSMLevel);
        if (local_7b8 == (cRSubTracks *)0x0) {
          RShellError("Cannot find \'First:\' in %s",local_7b4);
          goto LAB_00085fd8;
        }
        local_7b8 = (cRSubTracks *)Rstrnewline((char *)local_7b8);
        if (local_7b8 != (cRSubTracks *)0x0) {
          cVar7 = *local_7b8;
          if (cVar7 == (cRSubTracks)0x2e) {
            pcVar11 = local_5b4;
          }
          else {
            pcVar11 = local_5b4;
            do {
              pcVar11 = pcVar11 + 1;
              local_7b8 = local_7b8 + 1;
              pcVar11[-1] = cVar7;
              cVar7 = *local_7b8;
            } while (cVar7 != (cRSubTracks)0x2e);
          }
          *pcVar11 = (cRSubTracks)0x2e;
          pcVar11[1] = (cRSubTracks)0x74;
          pcVar11[2] = (cRSubTracks)0x78;
          pcVar11[3] = (cRSubTracks)0x74;
          pcVar11[4] = (cRSubTracks)0x0;
          ImportSegment(this,(char *)local_5b4,(cRSubSegment *)(this + 0x1454));
          local_7b8 = (cRSubTracks *)Rstrfind("Last:",gSMLevel);
          if (local_7b8 == (cRSubTracks *)0x0) {
            RShellError("Cannot find \'Last:\' in %s",local_7b4);
            goto LAB_00085fd8;
          }
          local_7b8 = (cRSubTracks *)Rstrnewline((char *)local_7b8);
          if (local_7b8 != (cRSubTracks *)0x0) {
            cVar7 = *local_7b8;
            pcVar11 = local_5b4;
            while (cVar7 != (cRSubTracks)0x2e) {
              local_7b8 = local_7b8 + 1;
              *pcVar11 = cVar7;
              pcVar11 = pcVar11 + 1;
              cVar7 = *local_7b8;
            }
            *pcVar11 = (cRSubTracks)0x2e;
            pcVar11[1] = (cRSubTracks)0x74;
            pcVar11[2] = (cRSubTracks)0x78;
            pcVar11[3] = (cRSubTracks)0x74;
            pcVar11[4] = (cRSubTracks)0x0;
            ImportSegment(this,(char *)local_5b4,(cRSubSegment *)(this + 0x1488));
            ImportSegment(this,"padding.txt",(cRSubSegment *)(this + 0x14bc));
            goto LAB_00085fd8;
          }
        }
      }
      RShellError("Unexpected end of file in %s",local_7b4);
    }
  }
LAB_00085fd8:
  if (local_34 == __stack_chk_guard) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
LAB_00086160:
  do {
    pcVar6 = local_7b8;
    local_7b8 = pcVar6 + 1;
    cVar7 = *local_7b8;
  } while ((byte)cVar7 < 0x20);
  local_7b8 = pcVar6 + 2;
  pcVar11 = pcVar11 + 2;
  *pcVar4 = cVar7;
  goto joined_r0x00086118;
LAB_00085f10:
  local_7b8 = (cRSubTracks *)Rstrnewline((char *)local_7b8);
  if (local_7b8 == (cRSubTracks *)0x0) {
    RShellError("Unexpected end of file in %s",param_1);
    goto LAB_00085fd8;
  }
  iVar2 = 1 - *(uint *)(this + 0x1588);
  if (1 < *(uint *)(this + 0x1588)) {
    iVar2 = 0;
  }
  goto LAB_00085668;
}
