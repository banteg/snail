/*
 * mangled: _ZN11cRSubTracks4InitEPP15cRSubSegmentRaw
 * demangled: cRSubTracks::Init(cRSubSegmentRaw**)
 * address: 00084c68
 * size: 324
 */

/* cRSubTracks::Init(cRSubSegmentRaw**) */

void __thiscall cRSubTracks::Init(cRSubTracks *this,cRSubSegmentRaw **param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  cRSubSegmentRaw *pcVar5;
  char *pcVar6;
  int iVar7;
  char cVar8;

  iVar4 = 0;
  pcVar6 = *(char **)(*param_1 + 0x28);
  *(undefined4 *)this = 0;
  *(undefined4 *)(this + 0x14f0) = 1000;
  if (*pcVar6 != '\0') {
    do {
      iVar3 = 0;
      do {
        iVar3 = iVar3 + 1;
      } while (pcVar6[iVar3] != '\0');
      *(int *)(this + iVar4 * 0x34 + 8) = iVar3;
      *(int *)param_1[*(int *)this] = iVar3;
      iVar4 = *(int *)this;
      if (*(void **)(this + iVar4 * 0x34 + 0x18) != (void *)0x0) {
        RShellMemoryFree(*(void **)(this + iVar4 * 0x34 + 0x18));
        iVar4 = *(int *)this;
        *(undefined4 *)(this + iVar4 * 0x34 + 0x18) = 0;
      }
      uVar2 = RShellMemoryMalloc(*(int *)(this + iVar4 * 0x34 + 8) << 3,"NOT GIVEN");
      iVar7 = *(int *)this;
      iVar3 = 0;
      pcVar5 = param_1[iVar7];
      *(undefined4 *)(this + iVar4 * 0x34 + 0x18) = uVar2;
      do {
        iVar4 = 0;
        cVar8 = **(char **)(pcVar5 + (iVar3 + 10) * 4);
        do {
          iVar1 = iVar4 * 8;
          iVar4 = iVar4 + 1;
          *(char *)(*(int *)(this + iVar7 * 0x34 + 0x18) + iVar3 + iVar1) = cVar8;
          iVar7 = *(int *)this;
          pcVar5 = param_1[iVar7];
          cVar8 = *(char *)(*(int *)(pcVar5 + (iVar3 + 10) * 4) + iVar4);
        } while (cVar8 != '\0');
        iVar3 = iVar3 + 1;
      } while (iVar3 != 8);
      uVar2 = *(undefined4 *)(pcVar5 + 0x20);
      *(undefined4 *)(this + iVar7 * 0x34 + 0x10) = *(undefined4 *)(pcVar5 + 0x1c);
      iVar4 = *(int *)this;
      *(undefined4 *)(this + iVar7 * 0x34 + 0x14) = uVar2;
      iVar4 = iVar4 + 1;
      *(int *)this = iVar4;
      pcVar6 = *(char **)(param_1[iVar4] + 0x28);
    } while (*pcVar6 != '\0');
    return;
  }
  return;
}
