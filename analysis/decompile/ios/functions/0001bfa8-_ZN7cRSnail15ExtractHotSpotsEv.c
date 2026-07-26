/*
 * mangled: _ZN7cRSnail15ExtractHotSpotsEv
 * demangled: cRSnail::ExtractHotSpots()
 * address: 0001bfa8
 * size: 284
 */

/* cRSnail::ExtractHotSpots() */

void __thiscall cRSnail::ExtractHotSpots(cRSnail *this)

{
  int *piVar1;
  int iVar2;
  undefined *this_00;
  int iVar3;
  int iVar4;
  float *pfVar5;
  cRSnail *pcVar6;
  int iVar7;
  int iVar8;
  int iVar9;

  this_00 = PTR__gTextureList_001b61d0;
  iVar7 = *(int *)(this + 0x14c0);
  pcVar6 = this + 0x1518;
  iVar8 = 0;
  do {
    *(undefined4 *)pcVar6 = 0;
    *(undefined4 *)(pcVar6 + -4) = 0;
    *(undefined4 *)(pcVar6 + -8) = 0;
    iVar3 = cRTextures::Add((cRTextures *)this_00,*(char **)((int)&_gSnailHotSpotNames + iVar8),
                            (cTgaHeader *)0x0,0);
    if (*(int *)(iVar7 + 0xc0) < 1) {
LAB_0001c040:
      RShellError("Cannot find HotPoint Texture %s",
                  *(undefined4 *)((int)&_gSnailHotSpotNames + iVar8));
    }
    else {
      iVar9 = *(int *)(iVar7 + 200);
      if (iVar3 != *(int *)(iVar9 + 0xc)) {
        iVar4 = 0;
        iVar2 = iVar9;
        do {
          iVar9 = iVar2 + 0x30;
          iVar4 = iVar4 + 1;
          if (iVar4 == *(int *)(iVar7 + 0xc0)) goto LAB_0001c040;
          piVar1 = (int *)(iVar2 + 0x3c);
          iVar2 = iVar9;
        } while (iVar3 != *piVar1);
      }
      pfVar5 = (float *)((uint)*(ushort *)(iVar9 + 2) * 0xc + *(int *)(iVar7 + 0xa4));
      *(float *)(pcVar6 + -8) = *(float *)(pcVar6 + -8) + *pfVar5;
      *(float *)(pcVar6 + -4) = *(float *)(pcVar6 + -4) + pfVar5[1];
      *(float *)pcVar6 = *(float *)pcVar6 + pfVar5[2];
    }
    iVar8 = iVar8 + 4;
    pcVar6 = pcVar6 + 0xc;
    if (iVar8 == 0x4c) {
      *(float *)(this + 0x15ec) = *(float *)(this + 0x15ec) + 0.3;
      return;
    }
  } while( true );
}
