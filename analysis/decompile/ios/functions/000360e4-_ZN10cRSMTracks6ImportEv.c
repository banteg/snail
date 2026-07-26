/*
 * mangled: _ZN10cRSMTracks6ImportEv
 * demangled: cRSMTracks::Import()
 * address: 000360e4
 * size: 2456
 */

/* cRSMTracks::Import() */

void __thiscall cRSMTracks::Import(cRSMTracks *this)

{
  int iVar1;
  undefined *puVar2;
  char *pcVar3;
  int iVar4;
  char *pcVar5;
  char *pcVar6;
  undefined4 uVar7;
  char *pcVar8;
  char *pcVar9;
  char cVar10;
  cRSMTracks *pcVar11;
  cRSMTracks cVar12;
  char *pcVar13;
  cRSMTracks *pcVar14;
  int iVar15;
  int local_4f0;
  int local_4ec;
  char local_4e8 [512];
  char acStack_2e8 [512];
  char local_e8 [128];
  char local_68 [64];
  int local_28;
  char *local_24;

  *(undefined4 *)this = 0;
  iVar4 = RShellFindFile("Data/SegmentsDir.txt",false);
  if (iVar4 == 0) {
    RShellReadDirectory("Segments","*.txt",(int *)this,&_gDirectory);
    RShellSaveDirectory("Data/SegmentsDir.txt",*(int *)this,&_gDirectory);
    iVar4 = *(int *)this;
  }
  else {
    RShellLoadDirectory("Data/SegmentsDir.txt",(int *)this,&_gDirectory);
    iVar4 = *(int *)this;
  }
  if (iVar4 < 0xb4) {
    if (0 < iVar4) {
      local_4f0 = 0;
      pcVar14 = this;
      while( true ) {
        pcVar13 = &_gDirectory + local_4f0 * 0x80;
        _sprintf(acStack_2e8,"Segments/%s",&_gDirectory + local_4f0 * 0x80,&_gSegmentText);
        RShellLoadFile(acStack_2e8,&_gSegmentText,&local_28);
        (&_gSegmentText)[local_28] = 0;
        iVar4 = Rstrfind("ID:",&_gSegmentText);
        if (iVar4 == 0) {
          RShellError("Cannot find ID: in Segment %s\n",pcVar13);
          return;
        }
        cVar10 = *(char *)(iVar4 + 3);
        if ((byte)(cVar10 - 0x30U) < 10) {
          iVar15 = 0;
          do {
            iVar1 = (int)cVar10;
            cVar10 = *(char *)(iVar4 + 4);
            iVar15 = iVar15 * 10 + iVar1 + -0x30;
            iVar4 = iVar4 + 1;
          } while ((byte)(cVar10 - 0x30U) < 10);
        }
        else {
          iVar15 = 0;
        }
        *(int *)(pcVar14 + 0x84) = iVar15;
        _strcpy((char *)(this + local_4f0 * 0x90 + 0x44),pcVar13);
        pcVar5 = (char *)Rstrfind("Name:\'",&_gSegmentText);
        if (pcVar5 == (char *)0x0) break;
        iVar4 = Rstrfind("\'",pcVar5);
        cVar12 = *(cRSMTracks *)(iVar4 + 1);
        if (cVar12 != (cRSMTracks)0x27) {
          pcVar11 = this + local_4f0 * 0x90 + 4;
          do {
            *pcVar11 = cVar12;
            cVar12 = *(cRSMTracks *)(iVar4 + 2);
            iVar4 = iVar4 + 1;
            pcVar11 = pcVar11 + 1;
          } while (cVar12 != (cRSMTracks)0x27);
        }
        pcVar5 = (char *)Rstrfind("Data:",&_gSegmentText);
        if (pcVar5 == (char *)0x0) {
          RShellError("Cannot find Data: in Segment %s\n",pcVar13);
          return;
        }
        pcVar5 = (char *)Rstrnewline(pcVar5);
        if ((pcVar5 == (char *)0x0) || (pcVar5 = (char *)Rstrnewline(pcVar5), pcVar5 == (char *)0x0)
           ) {
LAB_00036460:
          RShellError("Unexpected end of file in Segment %s\n",pcVar13);
          return;
        }
        if (*pcVar5 != '@') {
          RShellError("Data line must start with \'@\' in Segment %s\n",pcVar13);
          return;
        }
        iVar4 = 0;
        pcVar6 = pcVar5;
        while ((pcVar6[1] != '@' || (pcVar6[2] != '@'))) {
          do {
            pcVar6 = (char *)Rstrnewline(pcVar6);
            iVar4 = iVar4 + 1;
          } while (*pcVar6 != '@');
        }
        uVar7 = RShellMemoryMalloc(iVar4 << 3,"Segment tiles");
        *(undefined4 *)(pcVar14 + 0x8c) = uVar7;
        uVar7 = RShellMemoryMalloc(iVar4 * 0x38,"CRSMRow");
        *(undefined4 *)(pcVar14 + 0x88) = 0;
        *(undefined4 *)(pcVar14 + 0x90) = uVar7;
        local_4ec = 0;
        while (((*pcVar5 != '@' || (pcVar5[1] != '@')) || (pcVar5[2] != '@'))) {
          iVar15 = local_4ec * 0x38;
          *(undefined4 *)(iVar15 + *(int *)(pcVar14 + 0x90)) = 0;
          iVar4 = local_4ec * 8;
          *(char *)(*(int *)(pcVar14 + 0x8c) + local_4ec * 8) = pcVar5[1];
          *(char *)(iVar4 + *(int *)(pcVar14 + 0x8c) + 1) = pcVar5[2];
          *(char *)(iVar4 + *(int *)(pcVar14 + 0x8c) + 2) = pcVar5[3];
          *(char *)(iVar4 + *(int *)(pcVar14 + 0x8c) + 3) = pcVar5[4];
          *(char *)(iVar4 + *(int *)(pcVar14 + 0x8c) + 4) = pcVar5[5];
          *(char *)(iVar4 + *(int *)(pcVar14 + 0x8c) + 5) = pcVar5[6];
          *(char *)(iVar4 + *(int *)(pcVar14 + 0x8c) + 6) = pcVar5[7];
          *(char *)(iVar4 + *(int *)(pcVar14 + 0x8c) + 7) = pcVar5[8];
          if (pcVar5[9] != '@') {
            RShellError("Data line must end with \'@\' in Segment %s\n",pcVar13);
            return;
          }
          pcVar6 = pcVar5 + 10;
          *(int *)(pcVar14 + 0x88) = *(int *)(pcVar14 + 0x88) + 1;
          cVar10 = pcVar5[10];
          if (cVar10 == '*') {
            *(uint *)(iVar15 + *(int *)(pcVar14 + 0x90)) =
                 *(uint *)(iVar15 + *(int *)(pcVar14 + 0x90)) | 4;
            cVar10 = pcVar5[10];
          }
          if (cVar10 == '\r') {
            pcVar5 = local_4e8;
          }
          else {
            pcVar9 = local_4e8;
            do {
              pcVar5 = pcVar9 + 1;
              *pcVar9 = cVar10;
              pcVar6 = pcVar6 + 1;
              cVar10 = *pcVar6;
              pcVar9 = pcVar5;
            } while (cVar10 != '\r');
          }
          *pcVar5 = '\0';
          if (local_4e8[0] == '\0') {
            *(undefined4 *)(local_4ec * 0x38 + *(int *)(pcVar14 + 0x90) + 0x34) = 0;
          }
          else {
            local_24 = (char *)Rstrfind("3DModel=",local_4e8);
            if (local_24 != (char *)0x0) {
              iVar4 = Rstrfind("=",local_24);
              puVar2 = PTR__Game_001b60b8;
              cVar10 = *(char *)(iVar4 + 1);
              if (cVar10 == '.') {
                pcVar9 = local_e8;
                pcVar5 = local_e8 + 1;
                local_24 = (char *)(iVar4 + 1);
              }
              else {
                pcVar3 = (char *)(iVar4 + 2);
                pcVar5 = local_e8 + 1;
                do {
                  pcVar9 = pcVar5;
                  pcVar8 = pcVar3;
                  pcVar9[-1] = cVar10;
                  cVar10 = *pcVar8;
                  pcVar5 = pcVar9 + 1;
                  pcVar3 = pcVar8 + 1;
                  local_24 = pcVar8;
                } while (cVar10 != '.');
              }
              *pcVar9 = '.';
              *pcVar5 = 'x';
              pcVar9[2] = '\0';
              iVar4 = local_4ec * 0x38;
              *(uint *)(iVar4 + *(int *)(pcVar14 + 0x90)) =
                   *(uint *)(iVar4 + *(int *)(pcVar14 + 0x90)) | 2;
              iVar15 = *(int *)(pcVar14 + 0x90);
              uVar7 = cRDirectX::ModelAdd((cRDirectX *)(*(int *)puVar2 + 0x47ad0),local_e8);
              *(undefined4 *)(iVar4 + iVar15 + 0x14) = uVar7;
              local_24 = (char *)Rstrfind("(",local_24);
              iVar15 = *(int *)(pcVar14 + 0x90);
              uVar7 = Rstrfloat(&local_24);
              *(undefined4 *)(iVar4 + iVar15 + 0x18) = uVar7;
              iVar15 = *(int *)(pcVar14 + 0x90);
              uVar7 = Rstrfloat(&local_24);
              *(undefined4 *)(iVar4 + iVar15 + 0x1c) = uVar7;
              iVar15 = *(int *)(pcVar14 + 0x90);
              uVar7 = Rstrfloat(&local_24);
              *(undefined4 *)(iVar4 + iVar15 + 0x20) = uVar7;
              local_24 = (char *)Rstrfind("Velocity=",local_4e8);
              if (local_24 != (char *)0x0) {
                iVar15 = Rstrfind("=",local_24);
                local_24 = (char *)(iVar15 + 1);
                *(uint *)(iVar4 + *(int *)(pcVar14 + 0x90)) =
                     *(uint *)(iVar4 + *(int *)(pcVar14 + 0x90)) | 8;
                local_24 = (char *)Rstrfind("(",local_24);
                iVar15 = *(int *)(pcVar14 + 0x90);
                uVar7 = Rstrfloat(&local_24);
                *(undefined4 *)(iVar4 + iVar15 + 0x24) = uVar7;
                iVar15 = *(int *)(pcVar14 + 0x90);
                uVar7 = Rstrfloat(&local_24);
                *(undefined4 *)(iVar4 + iVar15 + 0x28) = uVar7;
                iVar15 = *(int *)(pcVar14 + 0x90);
                uVar7 = Rstrfloat(&local_24);
                *(undefined4 *)(iVar4 + iVar15 + 0x2c) = uVar7;
              }
            }
            local_24 = (char *)Rstrfind("Parcel=",local_4e8);
            if (local_24 != (char *)0x0) {
              iVar4 = local_4ec * 0x38;
              *(uint *)(iVar4 + *(int *)(pcVar14 + 0x90)) =
                   *(uint *)(iVar4 + *(int *)(pcVar14 + 0x90)) | 1;
              iVar15 = Rstrfind("=",local_24);
              local_24 = (char *)(iVar15 + 1);
              iVar15 = *(int *)(pcVar14 + 0x90);
              uVar7 = Rstrint(&local_24);
              *(undefined4 *)(iVar4 + iVar15 + 4) = uVar7;
              iVar15 = Rstrfind("(",local_24);
              local_24 = (char *)(iVar15 + 1);
              iVar15 = *(int *)(pcVar14 + 0x90);
              uVar7 = Rstrfloat(&local_24);
              *(undefined4 *)(iVar4 + iVar15 + 8) = uVar7;
              iVar15 = *(int *)(pcVar14 + 0x90);
              uVar7 = Rstrfloat(&local_24);
              *(undefined4 *)(iVar4 + iVar15 + 0xc) = uVar7;
              iVar15 = *(int *)(pcVar14 + 0x90);
              uVar7 = Rstrfloat(&local_24);
              *(undefined4 *)(iVar4 + iVar15 + 0x10) = uVar7;
            }
            local_24 = (char *)Rstrfind("Path=",local_4e8);
            if (local_24 != (char *)0x0) {
              iVar4 = Rstrfind("=",local_24);
              local_24 = (char *)(iVar4 + 1);
              cVar10 = *(char *)(iVar4 + 1);
              if (cVar10 < ' ') {
                pcVar5 = local_68;
              }
              else {
                pcVar5 = local_68;
                do {
                  pcVar5 = pcVar5 + 1;
                  local_24 = local_24 + 1;
                  pcVar5[-1] = cVar10;
                  cVar10 = *local_24;
                } while ('\x1f' < cVar10);
              }
              *pcVar5 = '\0';
              iVar15 = *(int *)(pcVar14 + 0x90);
              uVar7 = cRPathManager::NameCode
                                ((cRPathManager *)(*(int *)PTR__Game_001b60b8 + 0x353884),local_68);
              iVar4 = local_4ec * 0x38;
              *(undefined4 *)(iVar4 + iVar15 + 0x30) = uVar7;
              iVar15 = *(int *)(pcVar14 + 0x90);
              if (*(int *)(iVar4 + iVar15 + 0x30) == -1) {
                RShellError("Unknown path %s in %s",local_68,pcVar13);
              }
              else {
                *(uint *)(iVar4 + iVar15) = *(uint *)(iVar4 + iVar15) | 8;
              }
            }
            local_24 = (char *)Rstrfind("NoFall",local_4e8);
            if (local_24 != (char *)0x0) {
              *(uint *)(local_4ec * 0x38 + *(int *)(pcVar14 + 0x90)) =
                   *(uint *)(local_4ec * 0x38 + *(int *)(pcVar14 + 0x90)) | 0x100;
            }
            local_24 = (char *)Rstrfind("Ring=None",local_4e8);
            if (local_24 != (char *)0x0) {
              *(uint *)(local_4ec * 0x38 + *(int *)(pcVar14 + 0x90)) =
                   *(uint *)(local_4ec * 0x38 + *(int *)(pcVar14 + 0x90)) | 0x200;
            }
            local_24 = (char *)Rstrfind("Ring=Normal",local_4e8);
            if (local_24 != (char *)0x0) {
              *(uint *)(local_4ec * 0x38 + *(int *)(pcVar14 + 0x90)) =
                   *(uint *)(local_4ec * 0x38 + *(int *)(pcVar14 + 0x90)) | 0x400;
            }
            local_24 = (char *)Rstrfind("Ring=PowerUp",local_4e8);
            if (local_24 != (char *)0x0) {
              *(uint *)(local_4ec * 0x38 + *(int *)(pcVar14 + 0x90)) =
                   *(uint *)(local_4ec * 0x38 + *(int *)(pcVar14 + 0x90)) | 0x2000;
            }
            local_24 = (char *)Rstrfind("Ring=Explode",local_4e8);
            if (local_24 != (char *)0x0) {
              *(uint *)(local_4ec * 0x38 + *(int *)(pcVar14 + 0x90)) =
                   *(uint *)(local_4ec * 0x38 + *(int *)(pcVar14 + 0x90)) | 0x800;
            }
            local_24 = (char *)Rstrfind("Ring=Slow",local_4e8);
            if (local_24 != (char *)0x0) {
              *(uint *)(local_4ec * 0x38 + *(int *)(pcVar14 + 0x90)) =
                   *(uint *)(local_4ec * 0x38 + *(int *)(pcVar14 + 0x90)) | 0x1000;
            }
            local_24 = (char *)Rstrfind("RingSpeed=",local_4e8);
            if (local_24 == (char *)0x0) {
              *(undefined4 *)(local_4ec * 0x38 + *(int *)(pcVar14 + 0x90) + 0x34) = 0;
              local_24 = (char *)0x0;
            }
            else {
              iVar4 = Rstrfind("=",local_24);
              local_24 = (char *)(iVar4 + 1);
              iVar4 = *(int *)(pcVar14 + 0x90);
              uVar7 = Rstrfloat(&local_24);
              *(undefined4 *)(local_4ec * 0x38 + iVar4 + 0x34) = uVar7;
            }
            local_24 = (char *)Rstrfind("JetPack=Off",local_4e8);
            if (local_24 != (char *)0x0) {
              *(uint *)(local_4ec * 0x38 + *(int *)(pcVar14 + 0x90)) =
                   *(uint *)(local_4ec * 0x38 + *(int *)(pcVar14 + 0x90)) | 0x8000;
            }
          }
          pcVar5 = (char *)Rstrnewline(pcVar6);
          local_4ec = local_4ec + 1;
          if (pcVar5 == (char *)0x0) goto LAB_00036460;
        }
        pcVar14 = pcVar14 + 0x90;
        local_4f0 = local_4f0 + 1;
        if (*(int *)this <= local_4f0) {
          return;
        }
      }
      RShellError("Cannot find Name: in Segment %s\n",pcVar13);
    }
  }
  else {
    RShellError("Too many Segments increase RSMTRACK_SEGMENT_MAX");
  }
  return;
}
