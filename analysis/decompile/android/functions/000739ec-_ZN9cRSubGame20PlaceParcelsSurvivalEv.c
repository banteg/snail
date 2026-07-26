/*
 * mangled: _ZN9cRSubGame20PlaceParcelsSurvivalEv
 * demangled: cRSubGame::PlaceParcelsSurvival()
 * address: 000739ec
 * size: 844
 */

/* cRSubGame::PlaceParcelsSurvival() */

void cRSubGame::PlaceParcelsSurvival(void)

{
  int in_r0;
  int iVar1;
  uint uVar2;
  int iVar3;
  undefined1 *puVar4;
  uint *puVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  int iVar8;
  cRPath *this;
  int iVar9;
  bool bVar10;
  uint in_fpscr;
  float in_s0;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s1;
  float extraout_s2;
  char *pcVar11;
  float fVar12;
  int iVar13;
  uint local_44;
  uint local_40;

  fVar12 = (float)VectorSignedToFloat(*(undefined4 *)(in_r0 + 0x44),(byte)(in_fpscr >> 0x16) & 3);
  iVar3 = 0;
  puVar4 = gGroup0;
  iVar9 = (int)((fVar12 * 50.0) / 100.0 + *(float *)(in_r0 + 0x50) * 50.0) + 1;
  *(int *)(in_r0 + 0x163c) = iVar9;
  *(int *)(in_r0 + 0x1644) = iVar9;
  do {
    *(undefined4 *)(puVar4 + 0x200) = 0;
    puVar4 = puVar4 + 0x20c;
  } while (puVar4 != gParcelGroupSurvival0);
  iVar1 = *(int *)(in_r0 + 0x74);
  if (0 < iVar1) {
    iVar8 = 0;
    puVar5 = (uint *)(gGroup + in_r0 + 0xa1834);
    do {
      if (((*puVar5 & 1) != 0) && (puVar5[0x24] == 0)) {
        *(int *)(gParcelGroupSurvival0 + iVar8 * 4) = iVar3;
        iVar8 = iVar8 + 1;
      }
      iVar3 = iVar3 + 1;
      puVar5 = puVar5 + 0x37;
    } while (iVar3 != iVar1);
    iVar3 = iVar8;
    if (0 < iVar8) {
      iVar3 = iVar9;
    }
    if (0 < iVar3) {
      iVar3 = 0;
      puVar7 = (undefined4 *)(gParcelGroupSurvival0 + iVar8 * 4);
      do {
        pcVar11 = (char *)VectorSignedToFloat(iVar8,(byte)(in_fpscr >> 0x16) & 3);
        iVar3 = iVar3 + 1;
        fVar12 = (float)RAND(in_s0,pcVar11);
        iVar13 = (int)fVar12;
        iVar1 = *(int *)(gParcelGroupSurvival0 + iVar13 * 4);
        iVar9 = iVar1 * 0xdc + in_r0;
        uVar2 = *(uint *)(gGroup + iVar9 + 0xa1834);
        *(uint *)(gGroup + iVar9 + 0xa1834) = uVar2 | 0x11;
        *(float *)(gGroup + iVar9 + 0xa18bc) = *(float *)(gGroup + iVar9 + 0xa18bc) + 1.0;
        if ((uVar2 & 0x20) != 0) {
          *(float *)(gGroup + iVar9 + 0xa18b8) = -*(float *)(gGroup + iVar9 + 0xa18b8);
        }
        if ((uVar2 & 0x4000) != 0) {
          fVar12 = (float)VectorSignedToFloat(iVar1,(byte)(in_fpscr >> 0x16) & 3);
          *(float *)(gGroup + iVar1 * 0xdc + in_r0 + 0xa18c0) =
               *(float *)(gGroup + iVar1 * 0xdc + in_r0 + 0xa18c0) + fVar12 + 0.5;
        }
        iVar8 = iVar8 + -1;
        if (iVar13 < iVar8) {
          puVar6 = (undefined4 *)(gParcelGroupSurvival0 + (iVar13 + 1) * 4);
          do {
            puVar6[-1] = *puVar6;
            puVar6 = puVar6 + 1;
          } while (puVar6 != puVar7);
        }
        iVar1 = *(int *)(in_r0 + 0x163c);
        puVar7 = puVar7 + -1;
        bVar10 = iVar8 == 0;
        iVar9 = iVar8;
        if (0 < iVar8) {
          iVar9 = iVar1 - iVar3;
          bVar10 = iVar1 == iVar3;
        }
        in_s0 = extraout_s0;
      } while (!bVar10 && iVar9 < 0 == (0 < iVar8 && SBORROW4(iVar1,iVar3)));
      goto LAB_00073bdc;
    }
  }
  iVar3 = 0;
LAB_00073bdc:
  *(int *)(in_r0 + 0x163c) = iVar3;
  wprintf("Challenge parcel count %i\n",iVar3);
  iVar3 = *(int *)(in_r0 + 0x74);
  if (iVar3 < 1) {
    return;
  }
  iVar9 = 0;
  puVar5 = (uint *)(gGroup + in_r0 + 0xa1834);
  do {
    while ((*puVar5 & 0x41) != 0x41) {
LAB_00073c28:
      iVar9 = iVar9 + 1;
      puVar5 = puVar5 + 0x37;
      if (iVar3 <= iVar9) {
        return;
      }
    }
    fVar12 = (float)puVar5[0x23];
    iVar3 = cRSubLoc::Yi((cRSubLoc *)puVar5[0x26]);
    this = *(cRPath **)((cRSubLoc *)puVar5[0x26] + 0x2c);
    uVar2 = (int)fVar12 - iVar3 & ~((int)fVar12 - iVar3 >> 0x1f);
    if (*(int *)(this + 0x2c) == 0x39) {
      cRPath::HalfPipePos(extraout_s0_00,extraout_s1,extraout_s2,(tMatrix *)this,
                          *(float **)(uVar2 * 0xa8 + *(int *)(this + 0x4c) + 0xa0));
LAB_00073cf0:
      puVar5[0x21] = local_44;
      iVar3 = *(int *)(in_r0 + 0x74);
      puVar5[0x22] = local_40;
      goto LAB_00073c28;
    }
    if (*(int *)(this + 0x2c) == 0x3a) {
      cRPath::HalfPolePos(extraout_s0_00,extraout_s1,extraout_s2,(tMatrix *)this,
                          *(float **)(uVar2 * 0xa8 + *(int *)(this + 0x4c) + 0xa0));
      goto LAB_00073cf0;
    }
    iVar1 = cRSubLoc::Yi((cRSubLoc *)puVar5[0x26]);
    iVar3 = iVar9 * 0xdc;
    iVar9 = iVar9 + 1;
    puVar5 = puVar5 + 0x37;
    cRPath::GetPos(this,(tVector *)(gGroup + iVar3 + in_r0 + 0xa18b8),uVar2,iVar1,
                   (tVector *)(gGroup + iVar3 + in_r0 + 0xa18b8));
    iVar3 = *(int *)(in_r0 + 0x74);
    if (iVar3 <= iVar9) {
      return;
    }
  } while( true );
}
