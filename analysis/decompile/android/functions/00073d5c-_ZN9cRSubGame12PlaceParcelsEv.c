/*
 * mangled: _ZN9cRSubGame12PlaceParcelsEv
 * demangled: cRSubGame::PlaceParcels()
 * address: 00073d5c
 * size: 2804
 */

/* cRSubGame::PlaceParcels() */

void __thiscall cRSubGame::PlaceParcels(cRSubGame *this)

{
  byte bVar1;
  undefined1 *puVar2;
  int iVar3;
  float fVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int iVar7;
  byte *pbVar8;
  undefined4 uVar9;
  int iVar10;
  int iVar11;
  int *piVar12;
  undefined4 uVar13;
  undefined4 *puVar14;
  cRSubGame *pcVar15;
  undefined1 *puVar16;
  int iVar17;
  uint uVar18;
  int iVar19;
  int iVar20;
  int iVar21;
  int iVar22;
  cRPath *this_00;
  int iVar23;
  int iVar24;
  undefined4 *puVar25;
  undefined4 *puVar26;
  int iVar27;
  bool bVar28;
  uint in_fpscr;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float extraout_s0_02;
  float extraout_s0_03;
  float extraout_s1;
  float extraout_s2;
  char *pcVar29;
  float fVar30;
  float fVar31;
  float fVar32;
  int local_23c;
  int local_238;
  int local_224;
  cRSubGame *local_220;
  int local_218;
  int local_204 [112];
  undefined4 local_44;
  undefined4 local_40;

  iVar10 = *(int *)(this + 0x60);
  if (iVar10 == 1) {
    PlaceParcelsSurvival();
  }
  else if (iVar10 == 7 || iVar10 == 0) {
    iVar10 = 0;
    puVar16 = gGroup0;
    puVar2 = gGroup;
    do {
      *(undefined4 *)(puVar16 + 0x200) = 0;
      puVar16 = puVar16 + 0x20c;
      *(undefined4 *)(puVar2 + 0x200) = 0;
      puVar2 = puVar2 + 0x20c;
    } while (puVar16 != gParcelGroupSurvival0);
    iVar23 = *(int *)(this + 0xa0);
    iVar22 = iVar10;
    if (iVar23 < 1) {
      local_224 = 0;
      iVar23 = *(int *)(this + 0x163c);
      local_238 = 0;
      local_23c = __divsi3(iVar23 * 0x50,100);
      fVar30 = extraout_s0_00;
    }
    else {
      local_23c = 0;
      local_238 = 0;
      local_224 = 0;
      local_220 = this;
      do {
        uVar18 = 0;
        local_218 = 0;
        local_204[local_23c] = 10000;
        iVar10 = *(int *)(local_220 + 0xa8);
        do {
          if (0 < iVar10) {
            iVar24 = 0;
            iVar19 = local_224 * 0x20c;
            iVar7 = *(int *)(local_220 + 0xb8);
            iVar20 = *(int *)(local_220 + 0xbc);
            iVar3 = 0;
            do {
              if (((*(ushort *)(iVar20 + iVar24) & 1) == 0) ||
                 (iVar11 = iVar20 + iVar24, *(byte *)(iVar11 + 2) != uVar18)) {
                if (uVar18 == 0) goto LAB_000740a4;
LAB_00073e9c:
                iVar11 = 0;
                pbVar8 = (byte *)(iVar7 + iVar3 * 8);
                do {
                  while (bVar1 = *pbVar8, pbVar8 = pbVar8 + 1, (uint)bVar1 != uVar18 + 0x30) {
                    iVar11 = iVar11 + 1;
                    if (iVar11 == 8) goto LAB_00073f2c;
                  }
                  fVar30 = (float)VectorSignedToFloat(iVar11,(byte)(in_fpscr >> 0x16) & 3);
                  iVar11 = iVar11 + 1;
                  *(int *)(gGroup + iVar19 + 0x208) = local_23c;
                  *(int *)(gGroup + iVar19 + *(int *)(gGroup + iVar19 + 0x200) * 0x10) = iVar3;
                  iVar17 = *(int *)(gGroup + iVar19 + 0x200);
                  *(uint *)(gGroup + iVar19 + 0x204) = uVar18;
                  *(int *)(gGroup + iVar19 + 0x200) = iVar17 + 1;
                  iVar17 = iVar19 + iVar17 * 0x10;
                  *(undefined4 *)(gGroup + iVar17 + 0xc) = 0;
                  *(undefined4 *)(gGroup + iVar17 + 8) = 0;
                  *(float *)(gGroup + iVar17 + 4) = (fVar30 - 4.0) + 0.5;
                } while (iVar11 != 8);
              }
              else {
                if (uVar18 != 0) {
                  *(int *)(gGroup + iVar19 + 0x208) = local_23c;
                  *(int *)(gGroup + iVar19 + *(int *)(gGroup + iVar19 + 0x200) * 0x10) = iVar3;
                  iVar17 = *(int *)(gGroup + iVar19 + 0x200);
                  iVar21 = iVar19 + iVar17 * 0x10;
                  *(undefined4 *)(gGroup + iVar21 + 8) = 0;
                  *(undefined4 *)(gGroup + iVar21 + 4) = 0;
                  uVar5 = VectorUnsignedToFloat
                                    ((uint)*(byte *)(iVar11 + 5),(byte)(in_fpscr >> 0x16) & 3);
                  *(int *)(gGroup + iVar19 + 0x200) = iVar17 + 1;
                  *(uint *)(gGroup + iVar19 + 0x204) = uVar18;
                  *(undefined4 *)(gGroup + iVar21 + 0xc) = uVar5;
                  goto LAB_00073e9c;
                }
                iVar27 = iVar22 * 0x20c;
                iVar22 = iVar22 + 1;
                local_238 = local_238 + 1;
                *(int *)(gGroup0 + iVar27 + 0x208) = local_23c;
                *(int *)(gGroup0 + iVar27 + *(int *)(gGroup0 + iVar27 + 0x200) * 0x10) = iVar3;
                iVar17 = *(int *)(gGroup0 + iVar27 + 0x200);
                iVar21 = iVar27 + iVar17 * 0x10;
                *(undefined4 *)(gGroup0 + iVar21 + 8) = 0;
                *(undefined4 *)(gGroup0 + iVar21 + 4) = 0;
                uVar5 = VectorUnsignedToFloat
                                  ((uint)*(byte *)(iVar11 + 5),(byte)(in_fpscr >> 0x16) & 3);
                *(int *)(gGroup0 + iVar27 + 0x200) = iVar17 + 1;
                *(undefined4 *)(gGroup0 + iVar27 + 0x204) = 0;
                *(undefined4 *)(gGroup0 + iVar21 + 0xc) = uVar5;
LAB_000740a4:
                iVar11 = 0;
                pbVar8 = (byte *)(iVar7 + iVar3 * 8);
                do {
                  bVar1 = *pbVar8;
                  pbVar8 = pbVar8 + 1;
                  if (uVar18 + 0x30 == (uint)bVar1) {
                    fVar30 = (float)VectorSignedToFloat(iVar11,(byte)(in_fpscr >> 0x16) & 3);
                    local_238 = local_238 + 1;
                    iVar17 = iVar22 * 0x20c;
                    iVar22 = iVar22 + 1;
                    *(int *)(gGroup0 + iVar17 + 0x208) = local_23c;
                    *(int *)(gGroup0 + iVar17 + *(int *)(gGroup0 + iVar17 + 0x200) * 0x10) = iVar3;
                    iVar21 = *(int *)(gGroup0 + iVar17 + 0x200);
                    *(undefined4 *)(gGroup0 + iVar17 + 0x204) = 0;
                    *(int *)(gGroup0 + iVar17 + 0x200) = iVar21 + 1;
                    iVar17 = iVar17 + iVar21 * 0x10;
                    *(undefined4 *)(gGroup0 + iVar17 + 0xc) = 0;
                    *(undefined4 *)(gGroup0 + iVar17 + 8) = 0;
                    *(float *)(gGroup0 + iVar17 + 4) = (fVar30 - 4.0) + 0.5;
                  }
                  iVar11 = iVar11 + 1;
                } while (iVar11 != 8);
              }
LAB_00073f2c:
              iVar3 = iVar3 + 1;
              iVar24 = iVar24 + 10;
            } while (iVar3 != iVar10);
          }
          iVar3 = local_224 * 0x20c;
          iVar7 = *(int *)(gGroup + iVar3 + 0x200);
          if (0 < iVar7) {
            local_224 = local_224 + 1;
            if (iVar7 < local_204[*(int *)(gGroup + iVar3 + 0x208)]) {
              local_204[*(int *)(gGroup + iVar3 + 0x208)] = iVar7;
            }
            if (local_218 < iVar7) {
              local_218 = iVar7;
            }
          }
          uVar18 = uVar18 + 1;
        } while (uVar18 != 10);
        local_23c = local_23c + 1;
        local_220 = local_220 + 0x34;
      } while (local_23c != iVar23);
      iVar23 = *(int *)(this + 0x163c);
      iVar10 = __divsi3(iVar23 * 0x50,100);
      iVar3 = local_23c * 4;
      iVar7 = 0;
      local_23c = iVar10 - local_218;
      iVar10 = local_238;
      do {
        piVar12 = (int *)((int)local_204 + iVar7);
        iVar7 = iVar7 + 4;
        if (*piVar12 != 10000) {
          iVar10 = iVar10 + *piVar12;
        }
        fVar30 = extraout_s0;
      } while (iVar7 != iVar3);
    }
    if (iVar10 < iVar23) {
      fVar30 = (float)RShellError("Parcel Allocation could fail in %s.  Add more parcel Sets",
                                  this + 0x15a8);
    }
    pcVar15 = this + 0x15a8;
    if (local_238 < *(int *)(this + 0x163c) - local_23c) {
      fVar30 = (float)RShellError("Parcel Allocation could fail in %s. Add more 0 parcels ",pcVar15)
      ;
    }
    iVar10 = 0;
    while (iVar10 < local_23c && 0 < local_224) {
      pcVar29 = (char *)VectorSignedToFloat(local_224,(byte)(in_fpscr >> 0x16) & 3);
      fVar4 = (float)RAND(fVar30,pcVar29);
      iVar23 = (int)fVar4 * 0x20c;
      piVar12 = (int *)(gGroup + iVar23);
      iVar10 = iVar10 + *(int *)(gGroup + iVar23 + 0x200);
      fVar30 = extraout_s0_01;
      if (0 < *(int *)(gGroup + iVar23 + 0x200)) {
        iVar7 = *(int *)(gGroup + iVar23 + 0x208);
        iVar3 = 0;
        do {
          iVar3 = iVar3 + 1;
          iVar19 = *piVar12 + *(int *)(this + iVar7 * 0x34 + 0xa4);
          uVar18 = *(uint *)(this + iVar19 * 0xdc + 0x20dedc);
          if ((uVar18 & 0x10) != 0) {
            fVar30 = (float)RShellError("Duplicate Parcel Request in %s.",pcVar15);
            uVar18 = *(uint *)(this + iVar19 * 0xdc + 0x20dedc);
            iVar7 = *(int *)(gGroup + iVar23 + 0x208);
          }
          fVar31 = (float)VectorSignedToFloat(iVar19,(byte)(in_fpscr >> 0x16) & 3);
          iVar20 = piVar12[2];
          iVar24 = piVar12[3];
          *(int *)(this + iVar19 * 0xdc + 0x20df60) = piVar12[1];
          *(int *)(this + iVar19 * 0xdc + 0x20df64) = iVar20;
          *(int *)(this + iVar19 * 0xdc + 0x20df68) = iVar24;
          bVar28 = (uVar18 & 0x20) != 0;
          *(uint *)(this + iVar19 * 0xdc + 0x20dedc) = uVar18 | 0x11;
          fVar32 = *(float *)(this + iVar19 * 0xdc + 0x20df64) + 1.0;
          piVar12 = piVar12 + 4;
          iVar20 = *(int *)(gGroup + iVar23 + 0x200);
          *(float *)(this + iVar19 * 0xdc + 0x20df64) = fVar32;
          if (bVar28) {
            fVar32 = -*(float *)(this + iVar19 * 0xdc + 0x20df60);
          }
          *(float *)(this + iVar19 * 0xdc + 0x20df68) =
               *(float *)(this + iVar19 * 0xdc + 0x20df68) + fVar31 + 0.5;
          if (bVar28) {
            *(float *)(this + iVar19 * 0xdc + 0x20df60) = fVar32;
          }
        } while (iVar3 < iVar20);
      }
      iVar3 = 0;
      iVar23 = *(int *)(gGroup + (int)fVar4 * 0x20c + 0x208);
      do {
        puVar2 = gGroup + iVar3 * 0x20c;
        if (*(int *)(gGroup + iVar3 * 0x20c + 0x208) == iVar23) {
          local_224 = local_224 + -1;
          iVar7 = iVar3;
          while (iVar7 < local_224) {
            iVar19 = *(int *)(puVar2 + 0x40c);
            if (0 < iVar19) {
              iVar20 = 0;
              puVar14 = (undefined4 *)(gGroup + iVar7 * 0x20c);
              puVar25 = (undefined4 *)(gGroup + (iVar7 + 1) * 0x20c);
              do {
                uVar5 = *puVar25;
                uVar6 = puVar25[1];
                uVar9 = puVar25[2];
                uVar13 = puVar25[3];
                iVar20 = iVar20 + 1;
                puVar25 = puVar25 + 4;
                *puVar14 = uVar5;
                puVar14[1] = uVar6;
                puVar14[2] = uVar9;
                puVar14[3] = uVar13;
                puVar14 = puVar14 + 4;
              } while (iVar20 < iVar19);
            }
            *(int *)(puVar2 + 0x200) = iVar19;
            *(undefined4 *)(puVar2 + 0x208) = *(undefined4 *)(puVar2 + 0x414);
            *(undefined4 *)(puVar2 + 0x204) = *(undefined4 *)(puVar2 + 0x410);
            puVar2 = puVar2 + 0x20c;
            iVar7 = iVar7 + 1;
          }
          iVar3 = iVar3 + -1;
        }
        iVar3 = iVar3 + 1;
      } while (iVar3 < local_224);
    }
    puVar14 = (undefined4 *)(gGroup0 + iVar22 * 0x20c);
    while( true ) {
      iVar3 = *(int *)(this + 0x163c);
      bVar28 = iVar22 == 0;
      iVar23 = iVar22;
      if (0 < iVar22) {
        iVar23 = iVar3 - iVar10;
        bVar28 = iVar3 == iVar10;
      }
      if (bVar28 || iVar23 < 0 != (0 < iVar22 && SBORROW4(iVar3,iVar10))) break;
      pcVar29 = (char *)VectorSignedToFloat(iVar22,(byte)(in_fpscr >> 0x16) & 3);
      fVar30 = (float)RAND(fVar30,pcVar29);
      iVar3 = (int)fVar30;
      iVar23 = iVar3 * 0x20c;
      iVar10 = iVar10 + *(int *)(gGroup0 + iVar23 + 0x200);
      iVar23 = *(int *)(gGroup0 + iVar23) +
               *(int *)(this + *(int *)(gGroup0 + iVar23 + 0x208) * 0x34 + 0xa4);
      fVar30 = extraout_s0_02;
      if ((*(uint *)(this + iVar23 * 0xdc + 0x20dedc) & 0x10) != 0) {
        fVar30 = (float)RShellError("Duplicate Parcel Request in %s.",pcVar15);
      }
      fVar4 = (float)VectorSignedToFloat(iVar23,(byte)(in_fpscr >> 0x16) & 3);
      iVar7 = iVar3 * 0x20c;
      uVar5 = *(undefined4 *)(gGroup0 + iVar7 + 8);
      uVar6 = *(undefined4 *)(gGroup0 + iVar7 + 0xc);
      *(undefined4 *)(this + iVar23 * 0xdc + 0x20df60) = *(undefined4 *)(gGroup0 + iVar7 + 4);
      *(undefined4 *)(this + iVar23 * 0xdc + 0x20df64) = uVar5;
      *(undefined4 *)(this + iVar23 * 0xdc + 0x20df68) = uVar6;
      uVar18 = *(uint *)(this + iVar23 * 0xdc + 0x20dedc);
      *(uint *)(this + iVar23 * 0xdc + 0x20dedc) = uVar18 | 0x11;
      *(float *)(this + iVar23 * 0xdc + 0x20df68) =
           *(float *)(this + iVar23 * 0xdc + 0x20df68) + fVar4 + 0.5;
      *(float *)(this + iVar23 * 0xdc + 0x20df64) =
           *(float *)(this + iVar23 * 0xdc + 0x20df64) + 1.0;
      if ((uVar18 & 0x20) != 0) {
        *(float *)(this + iVar23 * 0xdc + 0x20df60) = -*(float *)(this + iVar23 * 0xdc + 0x20df60);
      }
      iVar22 = iVar22 + -1;
      if (iVar3 < iVar22) {
        puVar25 = (undefined4 *)(gGroup0 + (iVar3 + 1) * 0x20c);
        do {
          puVar25[-1] = puVar25[0x82];
          puVar25[-2] = 0;
          puVar25[-3] = puVar25[0x80];
          puVar26 = puVar25 + 0x83;
          puVar25[-0x83] = *puVar25;
          puVar25[-0x82] = puVar25[1];
          puVar25[-0x81] = puVar25[2];
          puVar25[-0x80] = puVar25[3];
          puVar25 = puVar26;
        } while (puVar14 != puVar26);
      }
      puVar14 = puVar14 + -0x83;
    }
    if ((iVar3 != iVar10) &&
       (RShellError("Did not generate required Parcels(%i) in %s",iVar3,pcVar15),
       *(int *)(this + 0x1644) != 0)) {
      uVar5 = __divsi3(*(int *)(this + 0x163c) * iVar10);
      *(undefined4 *)(this + 0x1644) = uVar5;
    }
    iVar22 = *(int *)(this + 0x74);
    *(int *)(this + 0x163c) = iVar10;
    if (0 < iVar22) {
      iVar10 = 0;
      pcVar15 = this + 0x20dedc;
      do {
        if ((*(uint *)pcVar15 & 0x41) == 0x41) {
          fVar30 = *(float *)(pcVar15 + 0x8c);
          iVar22 = cRSubLoc::Yi(*(cRSubLoc **)(pcVar15 + 0x98));
          this_00 = *(cRPath **)(*(cRSubLoc **)(pcVar15 + 0x98) + 0x2c);
          uVar18 = (int)fVar30 - iVar22 & ~((int)fVar30 - iVar22 >> 0x1f);
          if (*(int *)(this_00 + 0x2c) == 0x39) {
            cRPath::HalfPipePos(extraout_s0_03,extraout_s1,extraout_s2,(tMatrix *)this_00,
                                *(float **)(uVar18 * 0xa8 + *(int *)(this_00 + 0x4c) + 0xa0));
            *(undefined4 *)(pcVar15 + 0x84) = local_44;
            *(undefined4 *)(pcVar15 + 0x88) = local_40;
            iVar22 = *(int *)(this + 0x74);
          }
          else if (*(int *)(this_00 + 0x2c) == 0x3a) {
            cRPath::HalfPolePos(extraout_s0_03,extraout_s1,extraout_s2,(tMatrix *)this_00,
                                *(float **)(uVar18 * 0xa8 + *(int *)(this_00 + 0x4c) + 0xa0));
            *(undefined4 *)(pcVar15 + 0x84) = local_44;
            *(undefined4 *)(pcVar15 + 0x88) = local_40;
            iVar22 = *(int *)(this + 0x74);
          }
          else {
            iVar22 = cRSubLoc::Yi(*(cRSubLoc **)(pcVar15 + 0x98));
            cRPath::GetPos(this_00,(tVector *)(this + iVar10 * 0xdc + 0x20df60),uVar18,iVar22,
                           (tVector *)(this + iVar10 * 0xdc + 0x20df60));
            iVar22 = *(int *)(this + 0x74);
          }
        }
        iVar10 = iVar10 + 1;
        pcVar15 = pcVar15 + 0xdc;
      } while (iVar10 < iVar22);
    }
  }
  return;
}
