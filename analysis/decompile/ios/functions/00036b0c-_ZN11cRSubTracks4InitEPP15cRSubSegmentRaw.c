/*
 * mangled: _ZN11cRSubTracks4InitEPP15cRSubSegmentRaw
 * demangled: cRSubTracks::Init(cRSubSegmentRaw**)
 * address: 00036b0c
 * size: 452
 */

/* cRSubTracks::Init(cRSubSegmentRaw**) */

void __thiscall cRSubTracks::Init(cRSubTracks *this,cRSubSegmentRaw **param_1)

{
  int iVar1;
  undefined1 *puVar2;
  char cVar3;
  undefined4 uVar4;
  char *pcVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;

  iVar8 = 0;
  *(undefined4 *)(this + 0x11b8) = 1000;
  *(undefined4 *)this = 0;
  pcVar5 = *(char **)(*param_1 + 0x28);
  cVar3 = *pcVar5;
  while (cVar3 != '\0') {
    iVar6 = 0;
    do {
      iVar6 = iVar6 + 1;
    } while (pcVar5[iVar6] != '\0');
    *(int *)(this + iVar8 * 0x2c + 8) = iVar6;
    *(int *)param_1[*(int *)this] = iVar6;
    iVar8 = *(int *)this;
    if (*(void **)(this + iVar8 * 0x2c + 0x18) != (void *)0x0) {
      RShellMemoryFree(*(void **)(this + iVar8 * 0x2c + 0x18));
      *(undefined4 *)(this + *(int *)this * 0x2c + 0x18) = 0;
      iVar8 = *(int *)this;
    }
    uVar4 = RShellMemoryMalloc(*(int *)(this + iVar8 * 0x2c + 8) << 3,"NOT GIVEN");
    *(undefined4 *)(this + iVar8 * 0x2c + 0x18) = uVar4;
    iVar9 = *(int *)this;
    iVar6 = 0;
    iVar7 = 0;
    iVar8 = 0;
    while( true ) {
      do {
        iVar1 = iVar7 * 8;
        puVar2 = (undefined1 *)(*(int *)(param_1[iVar9] + iVar8 + 0x28) + iVar7);
        iVar7 = iVar7 + 1;
        *(undefined1 *)(iVar1 + iVar6 + *(int *)(this + iVar9 * 0x2c + 0x18)) = *puVar2;
        iVar9 = *(int *)this;
      } while (*(char *)(*(int *)(param_1[iVar9] + iVar8 + 0x28) + iVar7) != '\0');
      iVar6 = iVar6 + 1;
      if (7 < iVar6) break;
      iVar8 = iVar6 * 4;
      iVar7 = 0;
    }
    *(undefined4 *)(this + iVar9 * 0x2c + 0x14) = *(undefined4 *)(param_1[iVar9] + 0x20);
    *(undefined4 *)(this + *(int *)this * 0x2c + 0x10) =
         *(undefined4 *)(param_1[*(int *)this] + 0x1c);
    iVar8 = *(int *)this + 1;
    *(int *)this = iVar8;
    pcVar5 = *(char **)(param_1[iVar8] + 0x28);
    cVar3 = *pcVar5;
  }
  return;
}
