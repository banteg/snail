/*
 * mangled: _ZN7cRSnail15ExtractHotSpotsEv
 * demangled: cRSnail::ExtractHotSpots()
 * address: 00071cfc
 * size: 332
 */

/* cRSnail::ExtractHotSpots() */

void __thiscall cRSnail::ExtractHotSpots(cRSnail *this)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  float *pfVar4;
  int iVar5;
  cRSnail *pcVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  float fVar10;
  float fVar11;

  iVar8 = *(int *)(this + 0x14c0);
  pcVar6 = this + 0x1518;
  iVar7 = 0;
  do {
    *(undefined4 *)pcVar6 = 0;
    *(undefined4 *)(pcVar6 + -4) = 0;
    *(undefined4 *)(pcVar6 + -8) = 0;
    iVar3 = cRTextures::Add((cRTextures *)gTextureList,*(char **)((int)&gSnailHotSpotNames + iVar7),
                            (cTgaHeader *)0x0,0);
    if (*(int *)(iVar8 + 0xc0) < 1) {
LAB_00071db4:
      RShellError("Cannot find HotPoint Texture %s",
                  *(undefined4 *)((int)&gSnailHotSpotNames + iVar7));
    }
    else {
      iVar9 = *(int *)(iVar8 + 200);
      if (iVar3 != *(int *)(iVar9 + 0xc)) {
        iVar5 = 0;
        iVar2 = iVar9;
        do {
          iVar9 = iVar2 + 0x30;
          iVar5 = iVar5 + 1;
          if (*(int *)(iVar8 + 0xc0) <= iVar5) goto LAB_00071db4;
          piVar1 = (int *)(iVar2 + 0x3c);
          iVar2 = iVar9;
        } while (iVar3 != *piVar1);
      }
      pfVar4 = (float *)(*(int *)(iVar8 + 0xa4) + (uint)*(ushort *)(iVar9 + 2) * 0xc);
      fVar10 = *pfVar4;
      fVar11 = pfVar4[1];
      *(float *)pcVar6 = *(float *)pcVar6 + pfVar4[2];
      *(float *)(pcVar6 + -8) = *(float *)(pcVar6 + -8) + fVar10;
      *(float *)(pcVar6 + -4) = *(float *)(pcVar6 + -4) + fVar11;
    }
    iVar7 = iVar7 + 4;
    pcVar6 = pcVar6 + 0xc;
    if (iVar7 == 0x4c) {
      *(float *)(this + 0x15ec) = *(float *)(this + 0x15ec) + 0.3;
      return;
    }
  } while( true );
}
