/*
 * mangled: _ZN11cRSubTracks13ImportSegmentEPcP12cRSubSegment
 * demangled: cRSubTracks::ImportSegment(char*, cRSubSegment*)
 * address: 00036cd4
 * size: 728
 */

/* cRSubTracks::ImportSegment(char*, cRSubSegment*) */

void __thiscall cRSubTracks::ImportSegment(cRSubTracks *this,char *param_1,cRSubSegment *param_2)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;

  iVar5 = *(int *)PTR__Game_001b60b8;
  iVar2 = *(int *)(&DAT_0035cab0 + iVar5);
  if (iVar2 < 1) {
    iVar6 = 0;
  }
  else {
    iVar6 = 0;
    do {
      iVar2 = Rstrcmp(param_1,(char *)(iVar5 + iVar6 * 0x90 + 0x35caf4));
      if (iVar2 != 0) {
        iVar2 = *(int *)(&DAT_0035cab0 + iVar5);
        break;
      }
      iVar2 = *(int *)(&DAT_0035cab0 + iVar5);
      iVar6 = iVar6 + 1;
    } while (iVar6 < iVar2);
  }
  if (iVar6 == iVar2) {
    RShellError("Cannot find segment %s for %s",param_1,_gSMLevelFileName);
    return;
  }
  if (*(void **)(param_2 + 0x14) != (void *)0x0) {
    RShellMemoryFree(*(void **)(param_2 + 0x14));
    *(undefined4 *)(param_2 + 0x14) = 0;
  }
  iVar2 = iVar6 * 0x90 + iVar5;
  uVar1 = RShellMemoryMalloc(*(int *)(&DAT_0035cb38 + iVar2) << 3,"TileData[][8]");
  *(undefined4 *)(param_2 + 0x14) = uVar1;
  iVar3 = *(int *)(&DAT_0035cb38 + iVar2);
  iVar2 = 0;
  iVar7 = 0;
  do {
    if (iVar3 <= iVar2) {
      do {
        iVar7 = iVar7 + 1;
        if (7 < iVar7) {
          *(int *)(param_2 + 4) = iVar3;
          *(int *)(param_2 + 0x10) = iVar5 + iVar6 * 0x90 + 0x35caf4;
          *(undefined4 *)(param_2 + 0x1c) = 0;
          iVar2 = iVar6 * 0x90 + iVar5;
          *(undefined4 *)(param_2 + 0xc) = *(undefined4 *)(&DAT_0035cb34 + iVar2);
          if (*(void **)(param_2 + 0x18) != (void *)0x0) {
            RShellMemoryFree(*(void **)(param_2 + 0x18));
            *(undefined4 *)(param_2 + 0x18) = 0;
          }
          uVar1 = RShellMemoryMalloc(*(int *)(param_2 + 4) * 10,"cRSegmentRow");
          *(undefined4 *)(param_2 + 0x18) = uVar1;
          if (0 < *(int *)(&DAT_0035cb38 + iVar2)) {
            iVar3 = 0;
            iVar5 = (iVar6 + 1) * 0x90 + iVar5;
            iVar6 = 0;
            do {
              iVar7 = iVar3 * 0x38;
              iVar3 = iVar3 + 1;
              *(undefined2 *)(*(int *)(param_2 + 0x18) + iVar6) =
                   *(undefined2 *)(iVar7 + *(int *)(&DAT_0035cab0 + iVar5));
              *(char *)(*(int *)(param_2 + 0x18) + iVar6 + 3) =
                   (char)*(undefined4 *)(iVar7 + *(int *)(&DAT_0035cab0 + iVar5) + 0x14);
              uVar1 = VectorFloatToUnsigned
                                (*(undefined4 *)(iVar7 + *(int *)(&DAT_0035cab0 + iVar5) + 0x18),3);
              *(char *)(*(int *)(param_2 + 0x18) + iVar6 + 6) = (char)uVar1;
              uVar1 = VectorFloatToUnsigned
                                (*(undefined4 *)(iVar7 + *(int *)(&DAT_0035cab0 + iVar5) + 0x1c),3);
              *(char *)(*(int *)(param_2 + 0x18) + iVar6 + 7) = (char)uVar1;
              uVar1 = VectorFloatToUnsigned
                                (*(undefined4 *)(iVar7 + *(int *)(&DAT_0035cab0 + iVar5) + 0x20),3);
              *(char *)(*(int *)(param_2 + 0x18) + iVar6 + 8) = (char)uVar1;
              *(char *)(*(int *)(param_2 + 0x18) + iVar6 + 2) =
                   (char)*(undefined4 *)(iVar7 + *(int *)(&DAT_0035cab0 + iVar5) + 4);
              uVar1 = VectorFloatToUnsigned
                                (*(undefined4 *)(iVar7 + *(int *)(&DAT_0035cab0 + iVar5) + 0x10),3);
              *(char *)(*(int *)(param_2 + 0x18) + iVar6 + 5) = (char)uVar1;
              iVar4 = *(int *)(param_2 + 0x18) + iVar6;
              iVar6 = iVar6 + 10;
              *(char *)(iVar4 + 4) =
                   (char)*(undefined4 *)(iVar7 + *(int *)(&DAT_0035cab0 + iVar5) + 0x30);
            } while (iVar3 < *(int *)(&DAT_0035cb38 + iVar2));
          }
          *(undefined4 *)(param_2 + 0x20) = 0;
          *(undefined4 *)(param_2 + 0x24) = 0;
          *(undefined4 *)(param_2 + 0x28) = 0xffffffff;
          return;
        }
        iVar2 = 0;
      } while (iVar3 < 1);
    }
    iVar3 = iVar2 * 8 + iVar7;
    iVar4 = iVar6 * 0x90 + iVar5;
    iVar2 = iVar2 + 1;
    *(undefined1 *)(iVar3 + *(int *)(param_2 + 0x14)) =
         *(undefined1 *)(iVar3 + *(int *)(&DAT_0035cb3c + iVar4));
    iVar3 = *(int *)(&DAT_0035cb38 + iVar4);
  } while( true );
}
