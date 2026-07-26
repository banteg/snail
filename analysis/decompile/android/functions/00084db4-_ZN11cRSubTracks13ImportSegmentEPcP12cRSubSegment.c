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
  undefined4 uVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  float fVar11;

  iVar8 = DAT_000850bc + 0x84dcc;
  iVar10 = **(int **)(iVar8 + DAT_000850c0);
  iVar5 = *(int *)(&DAT_0038aacc + iVar10);
  if (iVar5 < 1) {
    iVar9 = 0;
  }
  else {
    iVar9 = 0;
    do {
      iVar5 = Rstrcmp(param_1,(char *)(iVar10 + iVar9 * 0x90 + 0x38ab10));
      if (iVar5 != 0) {
        iVar5 = *(int *)(&DAT_0038aacc + iVar10);
        break;
      }
      iVar5 = *(int *)(&DAT_0038aacc + iVar10);
      iVar9 = iVar9 + 1;
    } while (iVar9 < iVar5);
  }
  if (iVar9 == iVar5) {
    RShellError((char *)(iVar8 + DAT_000850d0),param_1,**(undefined4 **)(iVar8 + DAT_000850cc));
    return;
  }
  if (*(void **)(param_2 + 0x14) != (void *)0x0) {
    RShellMemoryFree(*(void **)(param_2 + 0x14));
    *(undefined4 *)(param_2 + 0x14) = 0;
  }
  iVar7 = iVar10 + iVar9 * 0x90;
  uVar1 = RShellMemoryMalloc(*(int *)(&DAT_0038ab54 + iVar7) << 3,(char *)(iVar8 + DAT_000850c4));
  iVar6 = *(int *)(&DAT_0038ab54 + iVar7);
  iVar5 = 0;
  *(undefined4 *)(param_2 + 0x14) = uVar1;
  do {
    if (0 < iVar6) {
      iVar2 = 0;
      do {
        iVar6 = iVar5 + iVar2 * 8;
        iVar2 = iVar2 + 1;
        *(undefined1 *)(*(int *)(param_2 + 0x14) + iVar6) =
             *(undefined1 *)(*(int *)(&DAT_0038ab58 + iVar7) + iVar6);
        iVar6 = *(int *)(&DAT_0038ab54 + iVar7);
      } while (iVar2 < iVar6);
    }
    iVar5 = iVar5 + 1;
  } while (iVar5 != 8);
  *(int *)(param_2 + 4) = iVar6;
  uVar1 = DAT_000850b8;
  iVar5 = iVar10 + iVar9 * 0x90;
  uVar3 = *(undefined4 *)(&DAT_0038ab50 + iVar5);
  *(int *)(param_2 + 0x10) = iVar5 + 0x38ab10;
  *(undefined4 *)(param_2 + 0x1c) = uVar1;
  *(undefined4 *)(param_2 + 0xc) = uVar3;
  if (*(void **)(param_2 + 0x18) != (void *)0x0) {
    RShellMemoryFree(*(void **)(param_2 + 0x18));
    iVar6 = *(int *)(param_2 + 4);
    *(undefined4 *)(param_2 + 0x18) = 0;
  }
  iVar5 = RShellMemoryMalloc(iVar6 * 10,(char *)(iVar8 + DAT_000850c8));
  iVar10 = iVar10 + iVar9 * 0x90;
  iVar8 = *(int *)(&DAT_0038ab54 + iVar10);
  *(int *)(param_2 + 0x18) = iVar5;
  if (0 < iVar8) {
    iVar8 = 0;
    piVar4 = (int *)(&DAT_0038ab5c + iVar10);
    iVar9 = 0;
    while( true ) {
      iVar7 = *piVar4;
      iVar6 = iVar9 * 0x38;
      iVar9 = iVar9 + 1;
      *(undefined2 *)(iVar5 + iVar8) = *(undefined2 *)(iVar7 + iVar6);
      *(char *)(iVar5 + iVar8 + 3) = (char)*(undefined4 *)(iVar7 + iVar6 + 0x14);
      fVar11 = *(float *)(*piVar4 + iVar6 + 0x18);
      *(char *)(*(int *)(param_2 + 0x18) + iVar8 + 6) = (0.0 < fVar11) * (char)(int)fVar11;
      fVar11 = *(float *)(*piVar4 + iVar6 + 0x1c);
      *(char *)(*(int *)(param_2 + 0x18) + iVar8 + 7) = (0.0 < fVar11) * (char)(int)fVar11;
      fVar11 = *(float *)(*piVar4 + iVar6 + 0x20);
      *(char *)(*(int *)(param_2 + 0x18) + iVar8 + 8) = (0.0 < fVar11) * (char)(int)fVar11;
      *(char *)(*(int *)(param_2 + 0x18) + iVar8 + 2) = (char)*(undefined4 *)(*piVar4 + iVar6 + 4);
      fVar11 = *(float *)(*piVar4 + iVar6 + 0x10);
      *(char *)(*(int *)(param_2 + 0x18) + iVar8 + 5) = (0.0 < fVar11) * (char)(int)fVar11;
      iVar5 = *(int *)(param_2 + 0x18) + iVar8;
      iVar8 = iVar8 + 10;
      *(char *)(iVar5 + 4) = (char)*(undefined4 *)(*piVar4 + iVar6 + 0x30);
      if (*(int *)(&DAT_0038ab54 + iVar10) <= iVar9) break;
      iVar5 = *(int *)(param_2 + 0x18);
    }
  }
  uVar1 = DAT_000850b8;
  *(undefined4 *)(param_2 + 0x2c) = 0;
  *(undefined4 *)(param_2 + 0x24) = uVar1;
  *(undefined4 *)(param_2 + 0x20) = 0;
  *(undefined4 *)(param_2 + 0x30) = 0xffffffff;
  *(undefined4 *)(param_2 + 0x28) = 0xffffffff;
  return;
}
