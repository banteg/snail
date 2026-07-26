/*
 * mangled: _ZN10cRSMTracks6ImportEv
 * demangled: cRSMTracks::Import()
 * address: 00083f80
 * size: 2680
 */

/* cRSMTracks::Import() */

void __thiscall cRSMTracks::Import(cRSMTracks *this)

{
  byte *pbVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  char *pcVar5;
  undefined4 uVar6;
  cRDirectX *this_00;
  int iVar7;
  char cVar8;
  byte *pbVar9;
  cRSMTracks cVar10;
  byte bVar11;
  char *__src;
  int iVar12;
  int iVar13;
  byte *pbVar14;
  cRSMTracks *pcVar15;
  int local_528;
  int local_4f4;
  byte *local_4f0;
  char local_4ec [512];
  char acStack_2ec [512];
  byte local_ec [128];
  byte local_6c [64];
  int local_2c;

  *(undefined4 *)this = 0;
  local_2c = __stack_chk_guard;
  iVar2 = RShellFindFile("Data/SegmentsDir.txt",false);
  if (iVar2 == 0) {
    RShellReadDirectory("Segments","*.txt",(int *)this,gDirectory);
    RShellSaveDirectory("Data/SegmentsDir.txt",*(int *)this,gDirectory);
    iVar2 = *(int *)this;
  }
  else {
    RShellLoadDirectory("Data/SegmentsDir.txt",(int *)this,gDirectory);
    iVar2 = *(int *)this;
  }
  if (iVar2 < 0xb4) {
    if (0 < iVar2) {
      local_528 = 0;
      pcVar15 = this;
      while( true ) {
        __src = gDirectory + local_528 * 0x80;
        sprintf(acStack_2ec,"Segments/%s",__src,gSegmentText);
        iVar2 = 0;
        RShellLoadFile(acStack_2ec,gSegmentText,&local_4f4);
        gSegmentText[local_4f4] = 0;
        iVar3 = Rstrfind("ID:",gSegmentText);
        if (iVar3 == 0) {
          RShellError("Cannot find ID: in Segment %s\n",__src);
          goto LAB_00084320;
        }
        bVar11 = *(byte *)(iVar3 + 3);
        while ((bVar11 - 0x30 & 0xff) < 10) {
          pbVar14 = (byte *)(iVar3 + 4);
          iVar2 = (uint)bVar11 + iVar2 * 10 + -0x30;
          iVar3 = iVar3 + 1;
          bVar11 = *pbVar14;
        }
        *(int *)(pcVar15 + 0x84) = iVar2;
        strcpy((char *)(this + local_528 * 0x90 + 0x44),__src);
        pcVar4 = (char *)Rstrfind("Name:\'",gSegmentText);
        if (pcVar4 == (char *)0x0) break;
        iVar2 = Rstrfind("\'",pcVar4);
        cVar10 = *(cRSMTracks *)(iVar2 + 1);
        if (cVar10 != (cRSMTracks)0x27) {
          iVar3 = 0;
          do {
            this[iVar3 + local_528 * 0x90 + 4] = cVar10;
            iVar3 = iVar3 + 1;
            cVar10 = *(cRSMTracks *)(iVar2 + 2);
            iVar2 = iVar2 + 1;
          } while (cVar10 != (cRSMTracks)0x27);
        }
        pcVar4 = (char *)Rstrfind("Data:",gSegmentText);
        if (pcVar4 == (char *)0x0) {
          RShellError("Cannot find Data: in Segment %s\n",__src);
          goto LAB_00084320;
        }
        pcVar4 = (char *)Rstrnewline(pcVar4);
        if ((pcVar4 == (char *)0x0) || (pcVar4 = (char *)Rstrnewline(pcVar4), pcVar4 == (char *)0x0)
           ) {
LAB_00084310:
          RShellError("Unexpected end of file in Segment %s\n",__src);
          goto LAB_00084320;
        }
        if (*pcVar4 != '@') {
          RShellError("Data line must start with \'@\' in Segment %s\n",__src);
          goto LAB_00084320;
        }
        iVar2 = 0;
        pcVar5 = pcVar4;
        while ((pcVar5[1] != '@' || (pcVar5[2] != '@'))) {
          do {
            pcVar5 = (char *)Rstrnewline(pcVar5);
            iVar2 = iVar2 + 1;
          } while (*pcVar5 != '@');
        }
        iVar3 = 0;
        uVar6 = RShellMemoryMalloc(iVar2 * 8,"Segment tiles");
        *(undefined4 *)(pcVar15 + 0x8c) = uVar6;
        uVar6 = RShellMemoryMalloc(iVar2 * 0x38,"CRSMRow");
        *(undefined4 *)(pcVar15 + 0x88) = 0;
        *(undefined4 *)(pcVar15 + 0x90) = uVar6;
        while (((*pcVar4 != '@' || (pcVar4[1] != '@')) || (pcVar4[2] != '@'))) {
          iVar2 = 0;
          *(undefined4 *)(*(int *)(pcVar15 + 0x90) + iVar3 * 0x38) = 0;
          do {
            iVar7 = iVar3 * 8 + iVar2;
            iVar12 = iVar2 + 1;
            iVar2 = iVar2 + 1;
            *(char *)(*(int *)(pcVar15 + 0x8c) + iVar7) = pcVar4[iVar12];
          } while (iVar2 != 8);
          if (pcVar4[9] != '@') {
            RShellError("Data line must end with \'@\' in Segment %s\n",__src);
            goto LAB_00084320;
          }
          pcVar5 = pcVar4 + 10;
          *(int *)(pcVar15 + 0x88) = *(int *)(pcVar15 + 0x88) + 1;
          cVar8 = pcVar4[10];
          if (cVar8 == '*') {
            *(uint *)(*(int *)(pcVar15 + 0x90) + iVar3 * 0x38) =
                 *(uint *)(*(int *)(pcVar15 + 0x90) + iVar3 * 0x38) | 4;
            cVar8 = pcVar4[10];
          }
          if (cVar8 == '\r') {
            pcVar4 = local_4ec;
          }
          else {
            pcVar4 = local_4ec;
            do {
              pcVar4 = pcVar4 + 1;
              pcVar4[-1] = cVar8;
              pcVar5 = pcVar5 + 1;
              cVar8 = *pcVar5;
            } while (cVar8 != '\r');
          }
          *pcVar4 = '\0';
          if (local_4ec[0] == '\0') {
            *(undefined4 *)(*(int *)(pcVar15 + 0x90) + iVar3 * 0x38 + 0x34) = 0;
          }
          else {
            local_4f0 = (byte *)Rstrfind("3DModel=",local_4ec);
            if (local_4f0 != (byte *)0x0) {
              iVar2 = Rstrfind("=",(char *)local_4f0);
              local_4f0 = (byte *)(iVar2 + 1);
              bVar11 = *(byte *)(iVar2 + 1);
              if (bVar11 == 0x2e) {
                pbVar14 = local_ec;
                pbVar9 = local_ec + 1;
              }
              else {
                pbVar1 = (byte *)(iVar2 + 2);
                pbVar9 = local_ec + 1;
                do {
                  pbVar14 = pbVar9;
                  local_4f0 = pbVar1;
                  pbVar14[-1] = bVar11;
                  pbVar9 = pbVar14 + 1;
                  bVar11 = *local_4f0;
                  pbVar1 = local_4f0 + 1;
                } while (bVar11 != 0x2e);
              }
              *pbVar14 = 0x2e;
              *pbVar9 = 0x78;
              pbVar14[2] = 0;
              iVar2 = iVar3 * 0x38;
              iVar12 = *(int *)(pcVar15 + 0x90);
              this_00 = (cRDirectX *)(Game + 0x47ad0);
              *(uint *)(iVar12 + iVar2) = *(uint *)(iVar12 + iVar2) | 2;
              uVar6 = cRDirectX::ModelAdd(this_00,(char *)local_ec);
              *(undefined4 *)(iVar12 + iVar2 + 0x14) = uVar6;
              local_4f0 = (byte *)Rstrfind("(",(char *)local_4f0);
              iVar12 = *(int *)(pcVar15 + 0x90);
              uVar6 = Rstrfloat((char **)&local_4f0);
              iVar7 = *(int *)(pcVar15 + 0x90);
              *(undefined4 *)(iVar12 + iVar2 + 0x18) = uVar6;
              uVar6 = Rstrfloat((char **)&local_4f0);
              iVar12 = *(int *)(pcVar15 + 0x90);
              *(undefined4 *)(iVar7 + iVar2 + 0x1c) = uVar6;
              uVar6 = Rstrfloat((char **)&local_4f0);
              *(undefined4 *)(iVar12 + iVar2 + 0x20) = uVar6;
              local_4f0 = (byte *)Rstrfind("Velocity=",local_4ec);
              if (local_4f0 != (byte *)0x0) {
                iVar12 = Rstrfind("=",(char *)local_4f0);
                *(uint *)(*(int *)(pcVar15 + 0x90) + iVar2) =
                     *(uint *)(*(int *)(pcVar15 + 0x90) + iVar2) | 8;
                local_4f0 = (byte *)(iVar12 + 1);
                local_4f0 = (byte *)Rstrfind("(",(char *)local_4f0);
                iVar12 = *(int *)(pcVar15 + 0x90);
                uVar6 = Rstrfloat((char **)&local_4f0);
                iVar7 = *(int *)(pcVar15 + 0x90);
                *(undefined4 *)(iVar12 + iVar2 + 0x24) = uVar6;
                uVar6 = Rstrfloat((char **)&local_4f0);
                iVar12 = *(int *)(pcVar15 + 0x90);
                *(undefined4 *)(iVar7 + iVar2 + 0x28) = uVar6;
                uVar6 = Rstrfloat((char **)&local_4f0);
                *(undefined4 *)(iVar12 + iVar2 + 0x2c) = uVar6;
              }
            }
            local_4f0 = (byte *)Rstrfind("Parcel=",local_4ec);
            if (local_4f0 != (byte *)0x0) {
              iVar2 = iVar3 * 0x38;
              *(uint *)(*(int *)(pcVar15 + 0x90) + iVar2) =
                   *(uint *)(*(int *)(pcVar15 + 0x90) + iVar2) | 1;
              iVar12 = Rstrfind("=",(char *)local_4f0);
              iVar7 = *(int *)(pcVar15 + 0x90);
              local_4f0 = (byte *)(iVar12 + 1);
              uVar6 = Rstrint((char **)&local_4f0);
              *(undefined4 *)(iVar7 + iVar2 + 4) = uVar6;
              iVar12 = Rstrfind("(",(char *)local_4f0);
              iVar7 = *(int *)(pcVar15 + 0x90);
              local_4f0 = (byte *)(iVar12 + 1);
              uVar6 = Rstrfloat((char **)&local_4f0);
              iVar13 = iVar3 * 7 + 1;
              iVar12 = *(int *)(pcVar15 + 0x90);
              *(undefined4 *)(iVar7 + iVar13 * 8) = uVar6;
              uVar6 = Rstrfloat((char **)&local_4f0);
              iVar7 = *(int *)(pcVar15 + 0x90);
              *(undefined4 *)(iVar12 + iVar13 * 8 + 4) = uVar6;
              uVar6 = Rstrfloat((char **)&local_4f0);
              *(undefined4 *)(iVar7 + iVar2 + 0x10) = uVar6;
            }
            local_4f0 = (byte *)Rstrfind("Path=",local_4ec);
            if (local_4f0 != (byte *)0x0) {
              iVar2 = Rstrfind("=",(char *)local_4f0);
              local_4f0 = (byte *)(iVar2 + 1);
              bVar11 = *(byte *)(iVar2 + 1);
              if (bVar11 < 0x20) {
                pbVar14 = local_6c;
              }
              else {
                pbVar14 = local_6c;
                pbVar9 = (byte *)(iVar2 + 2);
                do {
                  local_4f0 = pbVar9;
                  pbVar14 = pbVar14 + 1;
                  pbVar14[-1] = bVar11;
                  bVar11 = *local_4f0;
                  pbVar9 = local_4f0 + 1;
                } while (0x1f < bVar11);
              }
              *pbVar14 = 0;
              iVar7 = *(int *)(pcVar15 + 0x90);
              uVar6 = cRPathManager::NameCode
                                ((cRPathManager *)(gDirectory + Game + 0x2884),(char *)local_6c);
              iVar12 = *(int *)(pcVar15 + 0x90);
              iVar2 = iVar3 * 0x38;
              *(undefined4 *)(iVar7 + iVar2 + 0x30) = uVar6;
              if (*(int *)(iVar12 + iVar2 + 0x30) == -1) {
                RShellError("Unknown path %s in %s",local_6c,__src);
              }
              else {
                *(uint *)(iVar12 + iVar2) = *(uint *)(iVar12 + iVar2) | 8;
              }
            }
            local_4f0 = (byte *)Rstrfind("NoFall",local_4ec);
            if (local_4f0 != (byte *)0x0) {
              *(uint *)(*(int *)(pcVar15 + 0x90) + iVar3 * 0x38) =
                   *(uint *)(*(int *)(pcVar15 + 0x90) + iVar3 * 0x38) | 0x100;
            }
            local_4f0 = (byte *)Rstrfind("Ring=None",local_4ec);
            if (local_4f0 != (byte *)0x0) {
              *(uint *)(*(int *)(pcVar15 + 0x90) + iVar3 * 0x38) =
                   *(uint *)(*(int *)(pcVar15 + 0x90) + iVar3 * 0x38) | 0x200;
            }
            local_4f0 = (byte *)Rstrfind("Ring=Normal",local_4ec);
            if (local_4f0 != (byte *)0x0) {
              *(uint *)(*(int *)(pcVar15 + 0x90) + iVar3 * 0x38) =
                   *(uint *)(*(int *)(pcVar15 + 0x90) + iVar3 * 0x38) | 0x400;
            }
            local_4f0 = (byte *)Rstrfind("Ring=PowerUp",local_4ec);
            if (local_4f0 != (byte *)0x0) {
              *(uint *)(*(int *)(pcVar15 + 0x90) + iVar3 * 0x38) =
                   *(uint *)(*(int *)(pcVar15 + 0x90) + iVar3 * 0x38) | 0x2000;
            }
            local_4f0 = (byte *)Rstrfind("Ring=Explode",local_4ec);
            if (local_4f0 != (byte *)0x0) {
              *(uint *)(*(int *)(pcVar15 + 0x90) + iVar3 * 0x38) =
                   *(uint *)(*(int *)(pcVar15 + 0x90) + iVar3 * 0x38) | 0x800;
            }
            local_4f0 = (byte *)Rstrfind("Ring=Slow",local_4ec);
            if (local_4f0 != (byte *)0x0) {
              *(uint *)(*(int *)(pcVar15 + 0x90) + iVar3 * 0x38) =
                   *(uint *)(*(int *)(pcVar15 + 0x90) + iVar3 * 0x38) | 0x1000;
            }
            local_4f0 = (byte *)Rstrfind("RingSpeed=",local_4ec);
            if (local_4f0 == (byte *)0x0) {
              *(undefined4 *)(*(int *)(pcVar15 + 0x90) + iVar3 * 0x38 + 0x34) = 0;
              local_4f0 = (byte *)0x0;
            }
            else {
              iVar2 = Rstrfind("=",(char *)local_4f0);
              iVar12 = *(int *)(pcVar15 + 0x90);
              local_4f0 = (byte *)(iVar2 + 1);
              uVar6 = Rstrfloat((char **)&local_4f0);
              *(undefined4 *)(iVar12 + iVar3 * 0x38 + 0x34) = uVar6;
            }
            local_4f0 = (byte *)Rstrfind("JetPack=Off",local_4ec);
            if (local_4f0 != (byte *)0x0) {
              *(uint *)(*(int *)(pcVar15 + 0x90) + iVar3 * 0x38) =
                   *(uint *)(*(int *)(pcVar15 + 0x90) + iVar3 * 0x38) | 0x8000;
            }
          }
          iVar3 = iVar3 + 1;
          pcVar4 = (char *)Rstrnewline(pcVar5);
          if (pcVar4 == (char *)0x0) goto LAB_00084310;
        }
        pcVar15 = pcVar15 + 0x90;
        local_528 = local_528 + 1;
        if (*(int *)this <= local_528) goto LAB_00084320;
      }
      RShellError("Cannot find Name: in Segment %s\n",__src);
    }
  }
  else {
    RShellError("Too many Segments increase RSMTRACK_SEGMENT_MAX");
  }
LAB_00084320:
  if (local_2c != __stack_chk_guard) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}
