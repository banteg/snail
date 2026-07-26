/*
 * mangled: _ZN11cRSubTracks13ImportSegmentEPcP12cRSubSegment
 * demangled: cRSubTracks::ImportSegment(char*, cRSubSegment*)
 * address: 00084db4
 * size: 772
 */

/* cRSubTracks::ImportSegment(char*, cRSubSegment*) */

void __thiscall cRSubTracks::ImportSegment(cRSubTracks *this,char *param_1,cRSubSegment *param_2)

{
  undefined4 uVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  float fVar9;

  iVar8 = Game;
  iVar4 = *(int *)(&DAT_0038aacc + Game);
  if (iVar4 < 1) {
    iVar7 = 0;
  }
  else {
    iVar7 = 0;
    do {
      iVar4 = Rstrcmp(param_1,(char *)(iVar8 + iVar7 * 0x90 + 0x38ab10));
      if (iVar4 != 0) {
        iVar4 = *(int *)(&DAT_0038aacc + iVar8);
        break;
      }
      iVar4 = *(int *)(&DAT_0038aacc + iVar8);
      iVar7 = iVar7 + 1;
    } while (iVar7 < iVar4);
  }
  if (iVar7 == iVar4) {
    RShellError("Cannot find segment %s for %s",param_1,gSMLevelFileName);
    return;
  }
  if (*(void **)(param_2 + 0x14) != (void *)0x0) {
    RShellMemoryFree(*(void **)(param_2 + 0x14));
    *(undefined4 *)(param_2 + 0x14) = 0;
  }
  iVar6 = iVar8 + iVar7 * 0x90;
  uVar1 = RShellMemoryMalloc(*(int *)(&DAT_0038ab54 + iVar6) << 3,"TileData[][8]");
  iVar5 = *(int *)(&DAT_0038ab54 + iVar6);
  iVar4 = 0;
  *(undefined4 *)(param_2 + 0x14) = uVar1;
  do {
    if (0 < iVar5) {
      iVar2 = 0;
      do {
        iVar5 = iVar4 + iVar2 * 8;
        iVar2 = iVar2 + 1;
        *(undefined1 *)(*(int *)(param_2 + 0x14) + iVar5) =
             *(undefined1 *)(*(int *)(&DAT_0038ab58 + iVar6) + iVar5);
        iVar5 = *(int *)(&DAT_0038ab54 + iVar6);
      } while (iVar2 < iVar5);
    }
    iVar4 = iVar4 + 1;
  } while (iVar4 != 8);
  *(int *)(param_2 + 4) = iVar5;
  iVar4 = iVar8 + iVar7 * 0x90;
  uVar1 = *(undefined4 *)(&DAT_0038ab50 + iVar4);
  *(int *)(param_2 + 0x10) = iVar4 + 0x38ab10;
  *(undefined4 *)(param_2 + 0x1c) = 0;
  *(undefined4 *)(param_2 + 0xc) = uVar1;
  if (*(void **)(param_2 + 0x18) != (void *)0x0) {
    RShellMemoryFree(*(void **)(param_2 + 0x18));
    iVar5 = *(int *)(param_2 + 4);
    *(undefined4 *)(param_2 + 0x18) = 0;
  }
  iVar4 = RShellMemoryMalloc(iVar5 * 10,"cRSegmentRow");
  iVar8 = iVar8 + iVar7 * 0x90;
  iVar7 = *(int *)(&DAT_0038ab54 + iVar8);
  *(int *)(param_2 + 0x18) = iVar4;
  if (0 < iVar7) {
    iVar7 = 0;
    piVar3 = (int *)(&DAT_0038ab5c + iVar8);
    iVar5 = 0;
    while( true ) {
      iVar2 = *piVar3;
      iVar6 = iVar5 * 0x38;
      iVar5 = iVar5 + 1;
      *(undefined2 *)(iVar4 + iVar7) = *(undefined2 *)(iVar2 + iVar6);
      *(char *)(iVar4 + iVar7 + 3) = (char)*(undefined4 *)(iVar2 + iVar6 + 0x14);
      fVar9 = *(float *)(*piVar3 + iVar6 + 0x18);
      *(char *)(*(int *)(param_2 + 0x18) + iVar7 + 6) = (0.0 < fVar9) * (char)(int)fVar9;
      fVar9 = *(float *)(*piVar3 + iVar6 + 0x1c);
      *(char *)(*(int *)(param_2 + 0x18) + iVar7 + 7) = (0.0 < fVar9) * (char)(int)fVar9;
      fVar9 = *(float *)(*piVar3 + iVar6 + 0x20);
      *(char *)(*(int *)(param_2 + 0x18) + iVar7 + 8) = (0.0 < fVar9) * (char)(int)fVar9;
      *(char *)(*(int *)(param_2 + 0x18) + iVar7 + 2) = (char)*(undefined4 *)(*piVar3 + iVar6 + 4);
      fVar9 = *(float *)(*piVar3 + iVar6 + 0x10);
      *(char *)(*(int *)(param_2 + 0x18) + iVar7 + 5) = (0.0 < fVar9) * (char)(int)fVar9;
      iVar4 = *(int *)(param_2 + 0x18) + iVar7;
      iVar7 = iVar7 + 10;
      *(char *)(iVar4 + 4) = (char)*(undefined4 *)(*piVar3 + iVar6 + 0x30);
      if (*(int *)(&DAT_0038ab54 + iVar8) <= iVar5) break;
      iVar4 = *(int *)(param_2 + 0x18);
    }
  }
  *(undefined4 *)(param_2 + 0x2c) = 0;
  *(undefined4 *)(param_2 + 0x24) = 0;
  *(undefined4 *)(param_2 + 0x20) = 0;
  *(undefined4 *)(param_2 + 0x30) = 0xffffffff;
  *(undefined4 *)(param_2 + 0x28) = 0xffffffff;
  return;
}
