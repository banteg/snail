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
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  float *pfVar6;
  int iVar7;
  char *pcVar8;
  cRSnail *pcVar9;
  int iVar10;
  int iVar11;
  cRTextures *this_00;
  int iVar12;
  int iVar13;
  int iVar14;
  float fVar15;
  float fVar16;

  iVar4 = DAT_00071e54;
  uVar3 = DAT_00071e48;
  iVar13 = DAT_00071e50 + 0x71d24;
  iVar11 = *(int *)(this + 0x14c0);
  pcVar9 = this + 0x1518;
  iVar12 = *(int *)(iVar13 + DAT_00071e54);
  iVar10 = 0;
  this_00 = *(cRTextures **)(iVar13 + DAT_00071e58);
  pcVar8 = (char *)(iVar13 + DAT_00071e5c);
  do {
    *(undefined4 *)pcVar9 = uVar3;
    *(undefined4 *)(pcVar9 + -4) = uVar3;
    *(undefined4 *)(pcVar9 + -8) = uVar3;
    iVar5 = cRTextures::Add(this_00,*(char **)(iVar12 + iVar10),(cTgaHeader *)0x0,0);
    if (*(int *)(iVar11 + 0xc0) < 1) {
LAB_00071db4:
      RShellError(pcVar8,*(undefined4 *)(*(int *)(iVar13 + iVar4) + iVar10));
    }
    else {
      iVar14 = *(int *)(iVar11 + 200);
      if (iVar5 != *(int *)(iVar14 + 0xc)) {
        iVar7 = 0;
        iVar2 = iVar14;
        do {
          iVar14 = iVar2 + 0x30;
          iVar7 = iVar7 + 1;
          if (*(int *)(iVar11 + 0xc0) <= iVar7) goto LAB_00071db4;
          piVar1 = (int *)(iVar2 + 0x3c);
          iVar2 = iVar14;
        } while (iVar5 != *piVar1);
      }
      pfVar6 = (float *)(*(int *)(iVar11 + 0xa4) + (uint)*(ushort *)(iVar14 + 2) * 0xc);
      fVar15 = *pfVar6;
      fVar16 = pfVar6[1];
      *(float *)pcVar9 = *(float *)pcVar9 + pfVar6[2];
      *(float *)(pcVar9 + -8) = *(float *)(pcVar9 + -8) + fVar15;
      *(float *)(pcVar9 + -4) = *(float *)(pcVar9 + -4) + fVar16;
    }
    iVar10 = iVar10 + 4;
    pcVar9 = pcVar9 + 0xc;
    if (iVar10 == 0x4c) {
      *(float *)(this + 0x15ec) = *(float *)(this + 0x15ec) + DAT_00071e4c;
      return;
    }
  } while( true );
}
