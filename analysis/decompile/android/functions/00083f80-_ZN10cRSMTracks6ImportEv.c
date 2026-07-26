/*
 * mangled: _ZN10cRSMTracks6ImportEv
 * demangled: cRSMTracks::Import()
 * address: 00083f80
 * size: 2680
 */

/* cRSMTracks::Import() */

void __thiscall cRSMTracks::Import(cRSMTracks *this)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  byte *pbVar6;
  int iVar7;
  int iVar8;
  char *pcVar9;
  undefined4 uVar10;
  int iVar11;
  int iVar12;
  char cVar13;
  int iVar14;
  byte *pbVar15;
  int extraout_r2;
  int extraout_r2_00;
  int extraout_r2_01;
  int extraout_r2_02;
  int extraout_r2_03;
  cRSMTracks cVar16;
  byte bVar17;
  int *piVar18;
  char *pcVar19;
  char *pcVar20;
  char *__src;
  int iVar21;
  byte *pbVar22;
  int extraout_r3;
  int extraout_r3_00;
  int extraout_r3_01;
  int extraout_r3_02;
  int extraout_r3_03;
  char *pcVar23;
  cRSMTracks *pcVar24;
  int iVar25;
  char *pcVar26;
  int iVar27;
  int local_528;
  int local_4f4;
  byte *local_4f0;
  char local_4ec [512];
  char acStack_2ec [512];
  byte local_ec [128];
  byte local_6c [64];
  int local_2c;

  iVar5 = DAT_0008438c;
  iVar25 = DAT_00084388 + 0x83f98;
  piVar18 = *(int **)(iVar25 + DAT_0008438c);
  pcVar23 = (char *)(iVar25 + DAT_00084390);
  *(undefined4 *)this = 0;
  local_2c = *piVar18;
  iVar7 = RShellFindFile(pcVar23,false);
  iVar2 = DAT_00084a70;
  iVar1 = DAT_00084394;
  if (iVar7 == 0) {
    pcVar19 = *(char **)(iVar25 + DAT_00084a70);
    RShellReadDirectory((char *)(iVar25 + DAT_00084a74),(char *)(iVar25 + DAT_00084a78),(int *)this,
                        pcVar19);
    RShellSaveDirectory(pcVar23,*(int *)this,pcVar19);
    iVar7 = *(int *)this;
    iVar1 = iVar2;
    iVar2 = DAT_0008439c;
    iVar3 = DAT_000843a4;
    iVar4 = DAT_000843a8;
  }
  else {
    RShellLoadDirectory(pcVar23,(int *)this,*(char **)(iVar25 + DAT_00084394));
    iVar7 = *(int *)this;
    iVar2 = DAT_0008439c;
    iVar3 = DAT_000843a4;
    iVar4 = DAT_000843a8;
  }
  DAT_0008439c = iVar2;
  DAT_000843a4 = iVar3;
  DAT_000843a8 = iVar4;
  if (iVar7 < 0xb4) {
    if (0 < iVar7) {
      local_528 = 0;
      pcVar23 = (char *)(iVar25 + DAT_00084398);
      pcVar19 = (char *)(iVar25 + DAT_000843a0);
      pcVar20 = (char *)(iVar25 + DAT_000843ac);
      pcVar24 = this;
      while( true ) {
        pcVar26 = *(char **)(iVar25 + iVar3);
        __src = (char *)(*(int *)(iVar25 + iVar1) + local_528 * 0x80);
        sprintf(acStack_2ec,(char *)(iVar25 + iVar2),__src,pcVar26);
        iVar7 = 0;
        RShellLoadFile(acStack_2ec,pcVar26,&local_4f4);
        pcVar26[local_4f4] = '\0';
        iVar8 = Rstrfind((char *)(iVar25 + iVar4),pcVar26);
        if (iVar8 == 0) {
          RShellError((char *)(iVar25 + DAT_00084a94),__src);
          goto LAB_00084320;
        }
        bVar17 = *(byte *)(iVar8 + 3);
        while ((bVar17 - 0x30 & 0xff) < 10) {
          pbVar22 = (byte *)(iVar8 + 4);
          iVar7 = (uint)bVar17 + iVar7 * 10 + -0x30;
          iVar8 = iVar8 + 1;
          bVar17 = *pbVar22;
        }
        *(int *)(pcVar24 + 0x84) = iVar7;
        strcpy((char *)(this + local_528 * 0x90 + 0x44),__src);
        pcVar26 = (char *)Rstrfind((char *)(iVar25 + DAT_000843b0),*(char **)(iVar25 + iVar3));
        if (pcVar26 == (char *)0x0) break;
        iVar7 = Rstrfind((char *)(iVar25 + DAT_000843b4),pcVar26);
        cVar16 = *(cRSMTracks *)(iVar7 + 1);
        if (cVar16 != (cRSMTracks)0x27) {
          iVar8 = 0;
          do {
            this[iVar8 + local_528 * 0x90 + 4] = cVar16;
            iVar8 = iVar8 + 1;
            cVar16 = *(cRSMTracks *)(iVar7 + 2);
            iVar7 = iVar7 + 1;
          } while (cVar16 != (cRSMTracks)0x27);
        }
        pcVar26 = (char *)Rstrfind((char *)(iVar25 + DAT_000843b8),*(char **)(iVar25 + iVar3));
        if (pcVar26 == (char *)0x0) {
          RShellError((char *)(iVar25 + DAT_00084a88),__src);
          goto LAB_00084320;
        }
        pcVar26 = (char *)Rstrnewline(pcVar26);
        if ((pcVar26 == (char *)0x0) ||
           (pcVar26 = (char *)Rstrnewline(pcVar26), pcVar26 == (char *)0x0)) {
LAB_00084310:
          RShellError((char *)(iVar25 + DAT_000843cc),__src);
          goto LAB_00084320;
        }
        if (*pcVar26 != '@') {
          RShellError((char *)(iVar25 + DAT_00084a8c),__src);
          goto LAB_00084320;
        }
        iVar7 = 0;
        pcVar9 = pcVar26;
        while ((iVar8 = DAT_000843bc, pcVar9[1] != '@' || (pcVar9[2] != '@'))) {
          do {
            pcVar9 = (char *)Rstrnewline(pcVar9);
            iVar7 = iVar7 + 1;
          } while (*pcVar9 != '@');
        }
        iVar27 = 0;
        uVar10 = RShellMemoryMalloc(iVar7 * 8,(char *)(iVar25 + DAT_000843c0));
        pcVar9 = (char *)(iVar25 + DAT_000843c4);
        *(undefined4 *)(pcVar24 + 0x8c) = uVar10;
        uVar10 = RShellMemoryMalloc(iVar7 * 0x38,pcVar9);
        iVar7 = DAT_000843c8;
        *(undefined4 *)(pcVar24 + 0x88) = 0;
        *(undefined4 *)(pcVar24 + 0x90) = uVar10;
        while (((*pcVar26 != '@' || (pcVar26[1] != '@')) || (pcVar26[2] != '@'))) {
          iVar14 = 0;
          *(undefined4 *)(*(int *)(pcVar24 + 0x90) + iVar27 * 0x38) = 0;
          do {
            iVar12 = iVar27 * 8 + iVar14;
            iVar11 = iVar14 + 1;
            iVar14 = iVar14 + 1;
            *(char *)(*(int *)(pcVar24 + 0x8c) + iVar12) = pcVar26[iVar11];
          } while (iVar14 != 8);
          if (pcVar26[9] != '@') {
            RShellError((char *)(iVar25 + DAT_00084a80),__src);
            goto LAB_00084320;
          }
          pcVar9 = pcVar26 + 10;
          *(int *)(pcVar24 + 0x88) = *(int *)(pcVar24 + 0x88) + 1;
          cVar13 = pcVar26[10];
          if (cVar13 == '*') {
            *(uint *)(*(int *)(pcVar24 + 0x90) + iVar27 * 0x38) =
                 *(uint *)(*(int *)(pcVar24 + 0x90) + iVar27 * 0x38) | 4;
            cVar13 = pcVar26[10];
          }
          if (cVar13 == '\r') {
            pcVar26 = local_4ec;
          }
          else {
            pcVar26 = local_4ec;
            do {
              pcVar26 = pcVar26 + 1;
              pcVar26[-1] = cVar13;
              pcVar9 = pcVar9 + 1;
              cVar13 = *pcVar9;
            } while (cVar13 != '\r');
          }
          *pcVar26 = '\0';
          if (local_4ec[0] == '\0') {
            *(undefined4 *)(*(int *)(pcVar24 + 0x90) + iVar27 * 0x38 + 0x34) = DAT_00084384;
          }
          else {
            local_4f0 = (byte *)Rstrfind(pcVar23,local_4ec);
            iVar14 = DAT_000843f0;
            if (local_4f0 != (byte *)0x0) {
              iVar11 = Rstrfind((char *)(iVar25 + DAT_000843f0),(char *)local_4f0);
              local_4f0 = (byte *)(iVar11 + 1);
              bVar17 = *(byte *)(iVar11 + 1);
              if (bVar17 == 0x2e) {
                pbVar22 = local_ec;
                pbVar15 = local_ec + 1;
              }
              else {
                pbVar6 = (byte *)(iVar11 + 2);
                pbVar15 = local_ec + 1;
                do {
                  pbVar22 = pbVar15;
                  local_4f0 = pbVar6;
                  pbVar22[-1] = bVar17;
                  pbVar15 = pbVar22 + 1;
                  bVar17 = *local_4f0;
                  pbVar6 = local_4f0 + 1;
                } while (bVar17 != 0x2e);
              }
              *pbVar22 = 0x2e;
              *pbVar15 = 0x78;
              pbVar22[2] = 0;
              iVar11 = iVar27 * 0x38;
              iVar21 = *(int *)(pcVar24 + 0x90);
              iVar12 = **(int **)(iVar25 + DAT_000843d8);
              *(uint *)(iVar21 + iVar11) = *(uint *)(iVar21 + iVar11) | 2;
              uVar10 = cRDirectX::ModelAdd((cRDirectX *)(iVar12 + 0x47ad0),(char *)local_ec);
              pcVar26 = (char *)(iVar25 + DAT_000843d4);
              *(undefined4 *)(iVar21 + iVar11 + 0x14) = uVar10;
              local_4f0 = (byte *)Rstrfind(pcVar26,(char *)local_4f0);
              iVar12 = *(int *)(pcVar24 + 0x90);
              uVar10 = Rstrfloat((char **)&local_4f0);
              iVar21 = *(int *)(pcVar24 + 0x90);
              *(undefined4 *)(iVar12 + iVar11 + 0x18) = uVar10;
              uVar10 = Rstrfloat((char **)&local_4f0);
              iVar12 = *(int *)(pcVar24 + 0x90);
              *(undefined4 *)(iVar21 + iVar11 + 0x1c) = uVar10;
              uVar10 = Rstrfloat((char **)&local_4f0);
              *(undefined4 *)(iVar12 + iVar11 + 0x20) = uVar10;
              local_4f0 = (byte *)Rstrfind((char *)(iVar25 + DAT_000843d0),local_4ec);
              if (local_4f0 != (byte *)0x0) {
                iVar14 = Rstrfind((char *)(iVar25 + iVar14),(char *)local_4f0);
                *(uint *)(*(int *)(pcVar24 + 0x90) + iVar11) =
                     *(uint *)(*(int *)(pcVar24 + 0x90) + iVar11) | 8;
                local_4f0 = (byte *)(iVar14 + 1);
                local_4f0 = (byte *)Rstrfind(pcVar26,(char *)local_4f0);
                iVar14 = *(int *)(pcVar24 + 0x90);
                uVar10 = Rstrfloat((char **)&local_4f0);
                iVar12 = *(int *)(pcVar24 + 0x90);
                *(undefined4 *)(iVar14 + iVar11 + 0x24) = uVar10;
                uVar10 = Rstrfloat((char **)&local_4f0);
                iVar14 = *(int *)(pcVar24 + 0x90);
                *(undefined4 *)(iVar12 + iVar11 + 0x28) = uVar10;
                uVar10 = Rstrfloat((char **)&local_4f0);
                *(undefined4 *)(iVar14 + iVar11 + 0x2c) = uVar10;
              }
            }
            local_4f0 = (byte *)Rstrfind(pcVar19,local_4ec);
            if (local_4f0 != (byte *)0x0) {
              iVar14 = iVar27 * 0x38;
              pcVar26 = (char *)(iVar25 + DAT_000843f0);
              *(uint *)(*(int *)(pcVar24 + 0x90) + iVar14) =
                   *(uint *)(*(int *)(pcVar24 + 0x90) + iVar14) | 1;
              iVar11 = Rstrfind(pcVar26,(char *)local_4f0);
              iVar12 = *(int *)(pcVar24 + 0x90);
              local_4f0 = (byte *)(iVar11 + 1);
              uVar10 = Rstrint((char **)&local_4f0);
              *(undefined4 *)(iVar12 + iVar14 + 4) = uVar10;
              iVar11 = Rstrfind((char *)(iVar25 + DAT_000843d4),(char *)local_4f0);
              iVar12 = *(int *)(pcVar24 + 0x90);
              local_4f0 = (byte *)(iVar11 + 1);
              uVar10 = Rstrfloat((char **)&local_4f0);
              iVar21 = iVar27 * 7 + 1;
              iVar11 = *(int *)(pcVar24 + 0x90);
              *(undefined4 *)(iVar12 + iVar21 * 8) = uVar10;
              uVar10 = Rstrfloat((char **)&local_4f0);
              iVar12 = *(int *)(pcVar24 + 0x90);
              *(undefined4 *)(iVar11 + iVar21 * 8 + 4) = uVar10;
              uVar10 = Rstrfloat((char **)&local_4f0);
              *(undefined4 *)(iVar12 + iVar14 + 0x10) = uVar10;
            }
            local_4f0 = (byte *)Rstrfind(pcVar20,local_4ec);
            if (local_4f0 != (byte *)0x0) {
              iVar14 = Rstrfind((char *)(iVar25 + DAT_000843f0),(char *)local_4f0);
              local_4f0 = (byte *)(iVar14 + 1);
              bVar17 = *(byte *)(iVar14 + 1);
              if (bVar17 < 0x20) {
                pbVar22 = local_6c;
              }
              else {
                pbVar22 = local_6c;
                pbVar15 = (byte *)(iVar14 + 2);
                do {
                  local_4f0 = pbVar15;
                  pbVar22 = pbVar22 + 1;
                  pbVar22[-1] = bVar17;
                  bVar17 = *local_4f0;
                  pbVar15 = local_4f0 + 1;
                } while (0x1f < bVar17);
              }
              *pbVar22 = 0;
              iVar12 = *(int *)(pcVar24 + 0x90);
              uVar10 = cRPathManager::NameCode
                                 ((cRPathManager *)
                                  (gDirectory + **(int **)(iVar25 + DAT_000843d8) + 0x2884),
                                  (char *)local_6c);
              iVar11 = *(int *)(pcVar24 + 0x90);
              iVar14 = iVar27 * 0x38;
              *(undefined4 *)(iVar12 + iVar14 + 0x30) = uVar10;
              if (*(int *)(iVar11 + iVar14 + 0x30) == -1) {
                RShellError((char *)(iVar25 + DAT_00084a84),local_6c,__src);
              }
              else {
                *(uint *)(iVar11 + iVar14) = *(uint *)(iVar11 + iVar14) | 8;
              }
            }
            local_4f0 = (byte *)Rstrfind((char *)(iVar25 + iVar7),local_4ec);
            if (local_4f0 != (byte *)0x0) {
              *(uint *)(*(int *)(pcVar24 + 0x90) + iVar27 * 0x38) =
                   *(uint *)(*(int *)(pcVar24 + 0x90) + iVar27 * 0x38) | 0x100;
            }
            local_4f0 = (byte *)Rstrfind((char *)(iVar25 + iVar8),local_4ec);
            iVar11 = extraout_r2;
            iVar14 = extraout_r3;
            if (local_4f0 != (byte *)0x0) {
              iVar14 = iVar27 * 0x38;
              iVar11 = *(int *)(pcVar24 + 0x90);
            }
            pcVar26 = (char *)(iVar25 + DAT_000843dc);
            if (local_4f0 != (byte *)0x0) {
              *(uint *)(iVar11 + iVar14) = *(uint *)(iVar11 + iVar14) | 0x200;
            }
            local_4f0 = (byte *)Rstrfind(pcVar26,local_4ec);
            iVar11 = extraout_r2_00;
            iVar14 = extraout_r3_00;
            if (local_4f0 != (byte *)0x0) {
              iVar14 = iVar27 * 0x38;
              iVar11 = *(int *)(pcVar24 + 0x90);
            }
            pcVar26 = (char *)(iVar25 + DAT_000843e0);
            if (local_4f0 != (byte *)0x0) {
              *(uint *)(iVar11 + iVar14) = *(uint *)(iVar11 + iVar14) | 0x400;
            }
            local_4f0 = (byte *)Rstrfind(pcVar26,local_4ec);
            iVar11 = extraout_r2_01;
            iVar14 = extraout_r3_01;
            if (local_4f0 != (byte *)0x0) {
              iVar14 = iVar27 * 0x38;
              iVar11 = *(int *)(pcVar24 + 0x90);
            }
            pcVar26 = (char *)(iVar25 + DAT_000843e4);
            if (local_4f0 != (byte *)0x0) {
              *(uint *)(iVar11 + iVar14) = *(uint *)(iVar11 + iVar14) | 0x2000;
            }
            local_4f0 = (byte *)Rstrfind(pcVar26,local_4ec);
            iVar11 = extraout_r2_02;
            iVar14 = extraout_r3_02;
            if (local_4f0 != (byte *)0x0) {
              iVar14 = iVar27 * 0x38;
              iVar11 = *(int *)(pcVar24 + 0x90);
            }
            pcVar26 = (char *)(iVar25 + DAT_000843e8);
            if (local_4f0 != (byte *)0x0) {
              *(uint *)(iVar11 + iVar14) = *(uint *)(iVar11 + iVar14) | 0x800;
            }
            local_4f0 = (byte *)Rstrfind(pcVar26,local_4ec);
            iVar11 = extraout_r2_03;
            iVar14 = extraout_r3_03;
            if (local_4f0 != (byte *)0x0) {
              iVar14 = iVar27 * 0x38;
              iVar11 = *(int *)(pcVar24 + 0x90);
            }
            pcVar26 = (char *)(iVar25 + DAT_000843ec);
            if (local_4f0 != (byte *)0x0) {
              *(uint *)(iVar11 + iVar14) = *(uint *)(iVar11 + iVar14) | 0x1000;
            }
            local_4f0 = (byte *)Rstrfind(pcVar26,local_4ec);
            if (local_4f0 == (byte *)0x0) {
              *(undefined4 *)(*(int *)(pcVar24 + 0x90) + iVar27 * 0x38 + 0x34) = DAT_00084a6c;
              local_4f0 = (byte *)0x0;
            }
            else {
              iVar14 = Rstrfind((char *)(iVar25 + DAT_000843f0),(char *)local_4f0);
              iVar11 = *(int *)(pcVar24 + 0x90);
              local_4f0 = (byte *)(iVar14 + 1);
              uVar10 = Rstrfloat((char **)&local_4f0);
              *(undefined4 *)(iVar11 + iVar27 * 0x38 + 0x34) = uVar10;
            }
            local_4f0 = (byte *)Rstrfind((char *)(iVar25 + DAT_000843f4),local_4ec);
            if (local_4f0 != (byte *)0x0) {
              *(uint *)(*(int *)(pcVar24 + 0x90) + iVar27 * 0x38) =
                   *(uint *)(*(int *)(pcVar24 + 0x90) + iVar27 * 0x38) | 0x8000;
            }
          }
          iVar27 = iVar27 + 1;
          pcVar26 = (char *)Rstrnewline(pcVar9);
          if (pcVar26 == (char *)0x0) goto LAB_00084310;
        }
        pcVar24 = pcVar24 + 0x90;
        local_528 = local_528 + 1;
        if (*(int *)this <= local_528) goto LAB_00084320;
      }
      RShellError((char *)(iVar25 + DAT_00084a90),__src);
    }
  }
  else {
    RShellError((char *)(iVar25 + DAT_00084a7c));
  }
LAB_00084320:
  if (local_2c != **(int **)(iVar25 + iVar5)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}
