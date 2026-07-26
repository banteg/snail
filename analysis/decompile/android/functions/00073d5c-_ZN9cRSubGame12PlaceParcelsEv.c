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
  float fVar2;
  int iVar3;
  int iVar4;
  float fVar5;
  undefined4 uVar6;
  int iVar7;
  undefined4 uVar8;
  int iVar9;
  int iVar10;
  byte *pbVar11;
  undefined4 uVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  char *pcVar16;
  int *piVar17;
  undefined4 uVar18;
  int iVar19;
  undefined4 *puVar20;
  cRSubGame *pcVar21;
  int iVar22;
  int iVar23;
  int iVar24;
  uint uVar25;
  int iVar26;
  int iVar27;
  cRPath *this_00;
  int iVar28;
  undefined4 *puVar29;
  undefined4 *puVar30;
  int iVar31;
  int iVar32;
  bool bVar33;
  uint in_fpscr;
  float extraout_s0;
  float extraout_s0_00;
  float fVar34;
  float extraout_s0_01;
  float extraout_s0_02;
  float extraout_s0_03;
  float extraout_s1;
  float extraout_s2;
  char *pcVar35;
  float fVar36;
  float fVar37;
  float fVar38;
  int local_23c;
  int local_238;
  int local_224;
  cRSubGame *local_220;
  int local_218;
  int local_204 [112];
  undefined4 local_44;
  undefined4 local_40;

  iVar9 = DAT_000741b0;
  iVar19 = DAT_000741ac;
  iVar13 = *(int *)(this + 0x60);
  iVar7 = DAT_000741a8 + 0x73d7c;
  if (iVar13 == 1) {
    PlaceParcelsSurvival();
  }
  else if (iVar13 == 7 || iVar13 == 0) {
    iVar14 = 0;
    iVar23 = *(int *)(iVar7 + DAT_000741ac);
    iVar3 = *(int *)(iVar7 + DAT_000741b0);
    iVar13 = iVar23;
    do {
      *(undefined4 *)(iVar13 + 0x200) = 0;
      iVar13 = iVar13 + 0x20c;
      *(undefined4 *)(iVar3 + 0x200) = 0;
      fVar2 = DAT_000741cc;
      fVar34 = DAT_000741a0;
      iVar3 = iVar3 + 0x20c;
    } while (iVar13 != iVar23 + 0x106000);
    iVar3 = *(int *)(this + 0xa0);
    iVar13 = iVar14;
    if (iVar3 < 1) {
      local_224 = 0;
      iVar3 = *(int *)(this + 0x163c);
      local_238 = 0;
      local_23c = __divsi3(iVar3 * 0x50,100);
      fVar34 = extraout_s0_00;
    }
    else {
      local_23c = 0;
      local_238 = 0;
      local_224 = 0;
      local_220 = this;
      do {
        uVar6 = DAT_000741a4;
        uVar25 = 0;
        local_218 = 0;
        local_204[local_23c] = 10000;
        iVar14 = *(int *)(local_220 + 0xa8);
        do {
          if (0 < iVar14) {
            iVar28 = 0;
            iVar26 = local_224 * 0x20c;
            iVar10 = *(int *)(local_220 + 0xb8);
            iVar27 = *(int *)(local_220 + 0xbc);
            iVar4 = 0;
            do {
              if (((*(ushort *)(iVar27 + iVar28) & 1) == 0) ||
                 (iVar15 = iVar27 + iVar28, *(byte *)(iVar15 + 2) != uVar25)) {
                if (uVar25 == 0) goto LAB_000740a4;
LAB_00073e9c:
                iVar15 = 0;
                pbVar11 = (byte *)(iVar10 + iVar4 * 8);
                do {
                  while (bVar1 = *pbVar11, pbVar11 = pbVar11 + 1, (uint)bVar1 != uVar25 + 0x30) {
                    iVar15 = iVar15 + 1;
                    if (iVar15 == 8) goto LAB_00073f2c;
                  }
                  fVar36 = (float)VectorSignedToFloat(iVar15,(byte)(in_fpscr >> 0x16) & 3);
                  iVar15 = iVar15 + 1;
                  iVar22 = *(int *)(iVar7 + iVar9);
                  iVar31 = iVar22 + iVar26;
                  *(int *)(iVar31 + 0x208) = local_23c;
                  *(int *)(iVar22 + iVar26 + *(int *)(iVar31 + 0x200) * 0x10) = iVar4;
                  iVar24 = *(int *)(iVar31 + 0x200);
                  *(uint *)(iVar31 + 0x204) = uVar25;
                  *(int *)(iVar31 + 0x200) = iVar24 + 1;
                  iVar22 = iVar22 + iVar26 + iVar24 * 0x10;
                  *(undefined4 *)(iVar22 + 0xc) = uVar6;
                  *(undefined4 *)(iVar22 + 8) = uVar6;
                  *(float *)(iVar22 + 4) = (fVar36 - fVar34) + fVar2;
                } while (iVar15 != 8);
              }
              else {
                if (uVar25 != 0) {
                  iVar31 = *(int *)(iVar7 + iVar9);
                  iVar22 = iVar31 + iVar26;
                  *(int *)(iVar22 + 0x208) = local_23c;
                  *(int *)(iVar31 + iVar26 + *(int *)(iVar22 + 0x200) * 0x10) = iVar4;
                  iVar24 = *(int *)(iVar22 + 0x200);
                  iVar31 = iVar31 + iVar26 + iVar24 * 0x10;
                  *(undefined4 *)(iVar31 + 8) = uVar6;
                  *(undefined4 *)(iVar31 + 4) = uVar6;
                  uVar8 = VectorUnsignedToFloat
                                    ((uint)*(byte *)(iVar15 + 5),(byte)(in_fpscr >> 0x16) & 3);
                  *(int *)(iVar22 + 0x200) = iVar24 + 1;
                  *(uint *)(iVar22 + 0x204) = uVar25;
                  *(undefined4 *)(iVar31 + 0xc) = uVar8;
                  goto LAB_00073e9c;
                }
                iVar32 = iVar13 * 0x20c;
                iVar31 = *(int *)(iVar7 + iVar19);
                iVar13 = iVar13 + 1;
                local_238 = local_238 + 1;
                iVar22 = iVar31 + iVar32;
                *(int *)(iVar22 + 0x208) = local_23c;
                *(int *)(iVar31 + iVar32 + *(int *)(iVar22 + 0x200) * 0x10) = iVar4;
                iVar24 = *(int *)(iVar22 + 0x200);
                iVar31 = iVar31 + iVar32 + iVar24 * 0x10;
                *(undefined4 *)(iVar31 + 8) = uVar6;
                *(undefined4 *)(iVar31 + 4) = uVar6;
                uVar8 = VectorUnsignedToFloat
                                  ((uint)*(byte *)(iVar15 + 5),(byte)(in_fpscr >> 0x16) & 3);
                *(int *)(iVar22 + 0x200) = iVar24 + 1;
                *(undefined4 *)(iVar22 + 0x204) = 0;
                *(undefined4 *)(iVar31 + 0xc) = uVar8;
LAB_000740a4:
                iVar15 = 0;
                pbVar11 = (byte *)(iVar10 + iVar4 * 8);
                do {
                  bVar1 = *pbVar11;
                  pbVar11 = pbVar11 + 1;
                  if (uVar25 + 0x30 == (uint)bVar1) {
                    fVar36 = (float)VectorSignedToFloat(iVar15,(byte)(in_fpscr >> 0x16) & 3);
                    iVar22 = *(int *)(iVar7 + iVar19);
                    local_238 = local_238 + 1;
                    iVar24 = iVar13 * 0x20c;
                    iVar13 = iVar13 + 1;
                    iVar32 = iVar22 + iVar24;
                    *(int *)(iVar32 + 0x208) = local_23c;
                    *(int *)(iVar22 + iVar24 + *(int *)(iVar32 + 0x200) * 0x10) = iVar4;
                    iVar31 = *(int *)(iVar32 + 0x200);
                    *(undefined4 *)(iVar32 + 0x204) = 0;
                    *(int *)(iVar32 + 0x200) = iVar31 + 1;
                    iVar22 = iVar22 + iVar24 + iVar31 * 0x10;
                    *(undefined4 *)(iVar22 + 0xc) = uVar6;
                    *(undefined4 *)(iVar22 + 8) = uVar6;
                    *(float *)(iVar22 + 4) = (fVar36 - fVar34) + fVar2;
                  }
                  iVar15 = iVar15 + 1;
                } while (iVar15 != 8);
              }
LAB_00073f2c:
              iVar4 = iVar4 + 1;
              iVar28 = iVar28 + 10;
            } while (iVar4 != iVar14);
          }
          iVar4 = local_224 * 0x20c + *(int *)(iVar7 + iVar9);
          iVar10 = *(int *)(iVar4 + 0x200);
          if (0 < iVar10) {
            iVar4 = *(int *)(iVar4 + 0x208);
            local_224 = local_224 + 1;
            if (iVar10 < local_204[iVar4]) {
              local_204[iVar4] = iVar10;
            }
            if (local_218 < iVar10) {
              local_218 = iVar10;
            }
          }
          uVar25 = uVar25 + 1;
        } while (uVar25 != 10);
        local_23c = local_23c + 1;
        local_220 = local_220 + 0x34;
      } while (local_23c != iVar3);
      iVar3 = *(int *)(this + 0x163c);
      iVar14 = __divsi3(iVar3 * 0x50,100);
      iVar4 = local_23c * 4;
      iVar10 = 0;
      local_23c = iVar14 - local_218;
      iVar14 = local_238;
      do {
        piVar17 = (int *)((int)local_204 + iVar10);
        iVar10 = iVar10 + 4;
        if (*piVar17 != 10000) {
          iVar14 = iVar14 + *piVar17;
        }
        fVar34 = extraout_s0;
      } while (iVar10 != iVar4);
    }
    if (iVar14 < iVar3) {
      fVar34 = (float)RShellError((char *)(iVar7 + DAT_000741b4),this + 0x15a8);
    }
    pcVar21 = this + 0x15a8;
    if (local_238 < *(int *)(this + 0x163c) - local_23c) {
      fVar34 = (float)RShellError((char *)(iVar7 + DAT_000741b8),pcVar21);
    }
    iVar14 = 0;
    pcVar16 = (char *)(iVar7 + DAT_000741c4);
    while (fVar2 = DAT_000741cc, iVar14 < local_23c && 0 < local_224) {
      pcVar35 = (char *)VectorSignedToFloat(local_224,(byte)(in_fpscr >> 0x16) & 3);
      fVar5 = (float)RAND(fVar34,pcVar35);
      fVar36 = DAT_000741cc;
      fVar2 = DAT_000741c8;
      iVar3 = (int)fVar5 * 0x20c;
      piVar17 = (int *)(*(int *)(iVar7 + iVar9) + iVar3);
      iVar14 = iVar14 + piVar17[0x80];
      fVar34 = extraout_s0_01;
      if (0 < piVar17[0x80]) {
        iVar10 = piVar17[0x82];
        iVar4 = 0;
        do {
          iVar4 = iVar4 + 1;
          iVar26 = *piVar17 + *(int *)(this + iVar10 * 0x34 + 0xa4);
          uVar25 = *(uint *)(this + iVar26 * 0xdc + 0x20dedc);
          if ((uVar25 & 0x10) != 0) {
            fVar34 = (float)RShellError(pcVar16,pcVar21);
            uVar25 = *(uint *)(this + iVar26 * 0xdc + 0x20dedc);
            iVar10 = *(int *)(*(int *)(iVar7 + iVar9) + iVar3 + 0x208);
          }
          fVar37 = (float)VectorSignedToFloat(iVar26,(byte)(in_fpscr >> 0x16) & 3);
          iVar27 = piVar17[2];
          iVar28 = piVar17[3];
          *(int *)(this + iVar26 * 0xdc + 0x20df60) = piVar17[1];
          *(int *)(this + iVar26 * 0xdc + 0x20df64) = iVar27;
          *(int *)(this + iVar26 * 0xdc + 0x20df68) = iVar28;
          bVar33 = (uVar25 & 0x20) != 0;
          *(uint *)(this + iVar26 * 0xdc + 0x20dedc) = uVar25 | 0x11;
          fVar38 = *(float *)(this + iVar26 * 0xdc + 0x20df64) + fVar2;
          piVar17 = piVar17 + 4;
          iVar27 = *(int *)(*(int *)(iVar7 + iVar9) + iVar3 + 0x200);
          *(float *)(this + iVar26 * 0xdc + 0x20df64) = fVar38;
          if (bVar33) {
            fVar38 = -*(float *)(this + iVar26 * 0xdc + 0x20df60);
          }
          *(float *)(this + iVar26 * 0xdc + 0x20df68) =
               *(float *)(this + iVar26 * 0xdc + 0x20df68) + fVar37 + fVar36;
          if (bVar33) {
            *(float *)(this + iVar26 * 0xdc + 0x20df60) = fVar38;
          }
        } while (iVar4 < iVar27);
      }
      iVar10 = 0;
      iVar3 = *(int *)(iVar7 + iVar9);
      iVar4 = *(int *)((int)fVar5 * 0x20c + iVar3 + 0x208);
      do {
        iVar26 = iVar10 * 0x20c + iVar3;
        if (*(int *)(iVar26 + 0x208) == iVar4) {
          local_224 = local_224 + -1;
          iVar27 = iVar10;
          while (iVar27 < local_224) {
            iVar28 = *(int *)(iVar26 + 0x40c);
            if (0 < iVar28) {
              iVar15 = 0;
              puVar20 = (undefined4 *)(iVar27 * 0x20c + *(int *)(iVar7 + iVar9));
              puVar29 = (undefined4 *)((iVar27 + 1) * 0x20c + *(int *)(iVar7 + iVar9));
              do {
                uVar6 = *puVar29;
                uVar8 = puVar29[1];
                uVar12 = puVar29[2];
                uVar18 = puVar29[3];
                iVar15 = iVar15 + 1;
                puVar29 = puVar29 + 4;
                *puVar20 = uVar6;
                puVar20[1] = uVar8;
                puVar20[2] = uVar12;
                puVar20[3] = uVar18;
                puVar20 = puVar20 + 4;
              } while (iVar15 < iVar28);
            }
            *(int *)(iVar26 + 0x200) = iVar28;
            *(undefined4 *)(iVar26 + 0x208) = *(undefined4 *)(iVar26 + 0x414);
            *(undefined4 *)(iVar26 + 0x204) = *(undefined4 *)(iVar26 + 0x410);
            iVar26 = iVar26 + 0x20c;
            iVar27 = iVar27 + 1;
          }
          iVar10 = iVar10 + -1;
        }
        iVar10 = iVar10 + 1;
      } while (iVar10 < local_224);
    }
    puVar20 = (undefined4 *)(iVar13 * 0x20c + iVar23);
    pcVar16 = (char *)(iVar7 + DAT_000741c4);
    while( true ) {
      iVar3 = *(int *)(this + 0x163c);
      bVar33 = iVar13 == 0;
      iVar9 = iVar13;
      if (0 < iVar13) {
        iVar9 = iVar3 - iVar14;
        bVar33 = iVar3 == iVar14;
      }
      if (bVar33 || iVar9 < 0 != (0 < iVar13 && SBORROW4(iVar3,iVar14))) break;
      pcVar35 = (char *)VectorSignedToFloat(iVar13,(byte)(in_fpscr >> 0x16) & 3);
      fVar34 = (float)RAND(fVar34,pcVar35);
      iVar3 = (int)fVar34;
      iVar9 = *(int *)(iVar7 + iVar19) + iVar3 * 0x20c;
      iVar14 = iVar14 + *(int *)(iVar9 + 0x200);
      iVar9 = *(int *)(*(int *)(iVar7 + iVar19) + iVar3 * 0x20c) +
              *(int *)(this + *(int *)(iVar9 + 0x208) * 0x34 + 0xa4);
      fVar34 = extraout_s0_02;
      if ((*(uint *)(this + iVar9 * 0xdc + 0x20dedc) & 0x10) != 0) {
        fVar34 = (float)RShellError(pcVar16,pcVar21);
      }
      fVar5 = (float)VectorSignedToFloat(iVar9,(byte)(in_fpscr >> 0x16) & 3);
      iVar23 = iVar3 * 0x20c + *(int *)(iVar7 + iVar19);
      uVar6 = *(undefined4 *)(iVar23 + 8);
      uVar8 = *(undefined4 *)(iVar23 + 0xc);
      *(undefined4 *)(this + iVar9 * 0xdc + 0x20df60) = *(undefined4 *)(iVar23 + 4);
      *(undefined4 *)(this + iVar9 * 0xdc + 0x20df64) = uVar6;
      *(undefined4 *)(this + iVar9 * 0xdc + 0x20df68) = uVar8;
      fVar36 = DAT_00074880;
      uVar25 = *(uint *)(this + iVar9 * 0xdc + 0x20dedc);
      *(uint *)(this + iVar9 * 0xdc + 0x20dedc) = uVar25 | 0x11;
      *(float *)(this + iVar9 * 0xdc + 0x20df68) =
           *(float *)(this + iVar9 * 0xdc + 0x20df68) + fVar5 + fVar2;
      *(float *)(this + iVar9 * 0xdc + 0x20df64) =
           *(float *)(this + iVar9 * 0xdc + 0x20df64) + fVar36;
      if ((uVar25 & 0x20) != 0) {
        *(float *)(this + iVar9 * 0xdc + 0x20df60) = -*(float *)(this + iVar9 * 0xdc + 0x20df60);
      }
      iVar13 = iVar13 + -1;
      if (iVar3 < iVar13) {
        puVar29 = (undefined4 *)((iVar3 + 1) * 0x20c + *(int *)(iVar7 + iVar19));
        do {
          puVar29[-1] = puVar29[0x82];
          puVar29[-2] = 0;
          puVar29[-3] = puVar29[0x80];
          puVar30 = puVar29 + 0x83;
          puVar29[-0x83] = *puVar29;
          puVar29[-0x82] = puVar29[1];
          puVar29[-0x81] = puVar29[2];
          puVar29[-0x80] = puVar29[3];
          puVar29 = puVar30;
        } while (puVar20 != puVar30);
      }
      puVar20 = puVar20 + -0x83;
    }
    if ((iVar3 != iVar14) &&
       (RShellError((char *)(iVar7 + DAT_00074884),iVar3,pcVar21), *(int *)(this + 0x1644) != 0)) {
      uVar6 = __divsi3(*(int *)(this + 0x163c) * iVar14);
      *(undefined4 *)(this + 0x1644) = uVar6;
    }
    iVar19 = *(int *)(this + 0x74);
    *(int *)(this + 0x163c) = iVar14;
    if (0 < iVar19) {
      iVar9 = 0;
      pcVar21 = this + 0x20dedc;
      do {
        if ((*(uint *)pcVar21 & 0x41) == 0x41) {
          fVar34 = *(float *)(pcVar21 + 0x8c);
          iVar19 = cRSubLoc::Yi(*(cRSubLoc **)(pcVar21 + 0x98));
          this_00 = *(cRPath **)(*(cRSubLoc **)(pcVar21 + 0x98) + 0x2c);
          uVar25 = (int)fVar34 - iVar19 & ~((int)fVar34 - iVar19 >> 0x1f);
          if (*(int *)(this_00 + 0x2c) == 0x39) {
            cRPath::HalfPipePos(extraout_s0_03,extraout_s1,extraout_s2,(tMatrix *)this_00,
                                *(float **)(uVar25 * 0xa8 + *(int *)(this_00 + 0x4c) + 0xa0));
            *(undefined4 *)(pcVar21 + 0x84) = local_44;
            *(undefined4 *)(pcVar21 + 0x88) = local_40;
            iVar19 = *(int *)(this + 0x74);
          }
          else if (*(int *)(this_00 + 0x2c) == 0x3a) {
            cRPath::HalfPolePos(extraout_s0_03,extraout_s1,extraout_s2,(tMatrix *)this_00,
                                *(float **)(uVar25 * 0xa8 + *(int *)(this_00 + 0x4c) + 0xa0));
            *(undefined4 *)(pcVar21 + 0x84) = local_44;
            *(undefined4 *)(pcVar21 + 0x88) = local_40;
            iVar19 = *(int *)(this + 0x74);
          }
          else {
            iVar19 = cRSubLoc::Yi(*(cRSubLoc **)(pcVar21 + 0x98));
            cRPath::GetPos(this_00,(tVector *)(this + iVar9 * 0xdc + 0x20df60),uVar25,iVar19,
                           (tVector *)(this + iVar9 * 0xdc + 0x20df60));
            iVar19 = *(int *)(this + 0x74);
          }
        }
        iVar9 = iVar9 + 1;
        pcVar21 = pcVar21 + 0xdc;
      } while (iVar9 < iVar19);
    }
  }
  return;
}
