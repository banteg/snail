/*
 * mangled: _ZN9cRSubGame20PlaceParcelsSurvivalEv
 * demangled: cRSubGame::PlaceParcelsSurvival()
 * address: 000739ec
 * size: 844
 */

/* cRSubGame::PlaceParcelsSurvival() */

void cRSubGame::PlaceParcelsSurvival(void)

{
  float fVar1;
  int iVar2;
  int in_r0;
  float fVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  uint *puVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  int iVar11;
  cRPath *this;
  int iVar12;
  bool bVar13;
  uint in_fpscr;
  float in_s0;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s1;
  float extraout_s2;
  char *pcVar14;
  float fVar15;
  int iVar16;
  uint local_44;
  uint local_40;

  fVar15 = (float)VectorSignedToFloat(*(undefined4 *)(in_r0 + 0x44),(byte)(in_fpscr >> 0x16) & 3);
  iVar11 = DAT_00073d48 + 0x73a18;
  iVar6 = 0;
  iVar7 = *(int *)(iVar11 + DAT_00073d4c);
  iVar4 = iVar7 + 0x106000;
  iVar12 = (int)((fVar15 * DAT_00073d38) / DAT_00073d3c + DAT_00073d38 * *(float *)(in_r0 + 0x50)) +
           1;
  *(int *)(in_r0 + 0x163c) = iVar12;
  *(int *)(in_r0 + 0x1644) = iVar12;
  do {
    *(undefined4 *)(iVar7 + 0x200) = 0;
    iVar16 = DAT_00073d50;
    iVar7 = iVar7 + 0x20c;
  } while (iVar7 != iVar4);
  iVar4 = *(int *)(in_r0 + 0x74);
  if (0 < iVar4) {
    iVar7 = 0;
    puVar8 = (uint *)(gGroup + in_r0 + 0xa1834);
    do {
      if (((*puVar8 & 1) != 0) && (puVar8[0x24] == 0)) {
        *(int *)(*(int *)(iVar11 + iVar16) + iVar7 * 4) = iVar6;
        iVar7 = iVar7 + 1;
      }
      iVar2 = DAT_00073d50;
      fVar1 = DAT_00073d44;
      fVar15 = DAT_00073d40;
      iVar6 = iVar6 + 1;
      puVar8 = puVar8 + 0x37;
    } while (iVar6 != iVar4);
    iVar4 = iVar7;
    if (0 < iVar7) {
      iVar4 = iVar12;
    }
    if (0 < iVar4) {
      iVar4 = 0;
      puVar10 = (undefined4 *)(*(int *)(iVar11 + DAT_00073d50) + iVar7 * 4);
      do {
        pcVar14 = (char *)VectorSignedToFloat(iVar7,(byte)(in_fpscr >> 0x16) & 3);
        iVar4 = iVar4 + 1;
        fVar3 = (float)RAND(in_s0,pcVar14);
        iVar16 = (int)fVar3;
        iVar12 = *(int *)(*(int *)(iVar11 + iVar2) + iVar16 * 4);
        iVar6 = iVar12 * 0xdc + in_r0;
        uVar5 = *(uint *)(gGroup + iVar6 + 0xa1834);
        *(uint *)(gGroup + iVar6 + 0xa1834) = uVar5 | 0x11;
        *(float *)(gGroup + iVar6 + 0xa18bc) = *(float *)(gGroup + iVar6 + 0xa18bc) + fVar15;
        if ((uVar5 & 0x20) != 0) {
          *(float *)(gGroup + iVar6 + 0xa18b8) = -*(float *)(gGroup + iVar6 + 0xa18b8);
        }
        if ((uVar5 & 0x4000) != 0) {
          fVar3 = (float)VectorSignedToFloat(iVar12,(byte)(in_fpscr >> 0x16) & 3);
          *(float *)(gGroup + iVar12 * 0xdc + in_r0 + 0xa18c0) =
               *(float *)(gGroup + iVar12 * 0xdc + in_r0 + 0xa18c0) + fVar3 + fVar1;
        }
        iVar7 = iVar7 + -1;
        if (iVar16 < iVar7) {
          puVar9 = (undefined4 *)(*(int *)(iVar11 + iVar2) + (iVar16 + 1) * 4);
          do {
            puVar9[-1] = *puVar9;
            puVar9 = puVar9 + 1;
          } while (puVar9 != puVar10);
        }
        iVar12 = *(int *)(in_r0 + 0x163c);
        puVar10 = puVar10 + -1;
        bVar13 = iVar7 == 0;
        iVar6 = iVar7;
        if (0 < iVar7) {
          iVar6 = iVar12 - iVar4;
          bVar13 = iVar12 == iVar4;
        }
        in_s0 = extraout_s0;
      } while (!bVar13 && iVar6 < 0 == (0 < iVar7 && SBORROW4(iVar12,iVar4)));
      goto LAB_00073bdc;
    }
  }
  iVar4 = 0;
LAB_00073bdc:
  iVar6 = DAT_00073d58;
  *(int *)(in_r0 + 0x163c) = iVar4;
  wprintf((char *)(iVar11 + iVar6),iVar4);
  iVar4 = *(int *)(in_r0 + 0x74);
  if (iVar4 < 1) {
    return;
  }
  iVar6 = 0;
  puVar8 = (uint *)(gGroup + in_r0 + 0xa1834);
  do {
    while ((*puVar8 & 0x41) != 0x41) {
LAB_00073c28:
      iVar6 = iVar6 + 1;
      puVar8 = puVar8 + 0x37;
      if (iVar4 <= iVar6) {
        return;
      }
    }
    fVar15 = (float)puVar8[0x23];
    iVar4 = cRSubLoc::Yi((cRSubLoc *)puVar8[0x26]);
    this = *(cRPath **)((cRSubLoc *)puVar8[0x26] + 0x2c);
    uVar5 = (int)fVar15 - iVar4 & ~((int)fVar15 - iVar4 >> 0x1f);
    if (*(int *)(this + 0x2c) == 0x39) {
      cRPath::HalfPipePos(extraout_s0_00,extraout_s1,extraout_s2,(tMatrix *)this,
                          *(float **)(uVar5 * 0xa8 + *(int *)(this + 0x4c) + 0xa0));
LAB_00073cf0:
      puVar8[0x21] = local_44;
      iVar4 = *(int *)(in_r0 + 0x74);
      puVar8[0x22] = local_40;
      goto LAB_00073c28;
    }
    if (*(int *)(this + 0x2c) == 0x3a) {
      cRPath::HalfPolePos(extraout_s0_00,extraout_s1,extraout_s2,(tMatrix *)this,
                          *(float **)(uVar5 * 0xa8 + *(int *)(this + 0x4c) + 0xa0));
      goto LAB_00073cf0;
    }
    iVar7 = cRSubLoc::Yi((cRSubLoc *)puVar8[0x26]);
    iVar4 = iVar6 * 0xdc;
    iVar6 = iVar6 + 1;
    puVar8 = puVar8 + 0x37;
    cRPath::GetPos(this,(tVector *)(gGroup + iVar4 + in_r0 + 0xa18b8),uVar5,iVar7,
                   (tVector *)(gGroup + iVar4 + in_r0 + 0xa18b8));
    iVar4 = *(int *)(in_r0 + 0x74);
    if (iVar4 <= iVar6) {
      return;
    }
  } while( true );
}
