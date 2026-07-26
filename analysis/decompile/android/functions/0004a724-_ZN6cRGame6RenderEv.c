/*
 * mangled: _ZN6cRGame6RenderEv
 * demangled: cRGame::Render()
 * address: 0004a724
 * size: 2104
 */

/* cRGame::Render() */

void __thiscall cRGame::Render(cRGame *this)

{
  cRGame *pcVar1;
  float fVar2;
  int iVar3;
  int extraout_r1;
  int iVar4;
  tMatrix *ptVar5;
  int extraout_r1_00;
  cRSprite *this_00;
  cRGame *pcVar6;
  uint uVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  int iVar10;
  int iVar11;
  int *piVar12;
  char *pcVar13;
  char *pcVar14;
  uint uVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  cRBod *pcVar19;
  int iVar20;
  int *piVar21;
  cRObject *pcVar22;
  undefined4 *puVar23;
  undefined4 *puVar24;
  undefined1 uVar25;
  tColourSmall *ptVar26;
  int iVar27;
  bool bVar28;
  float extraout_s0;
  float extraout_s0_00;
  float fVar29;
  float extraout_s0_01;
  float extraout_s0_02;
  float extraout_s0_03;
  float extraout_s0_04;
  float extraout_s1;
  float extraout_s1_00;
  float extraout_s1_01;
  undefined8 uVar30;
  float extraout_s1_02;
  float extraout_s1_03;
  float extraout_s1_04;
  float extraout_s1_05;
  float extraout_s1_06;
  float extraout_s2;
  float extraout_s2_00;
  float fVar31;
  float extraout_s2_01;
  float extraout_s2_02;
  float extraout_s2_03;
  float extraout_s2_04;
  float extraout_s2_05;
  float extraout_s2_06;
  float extraout_s3;
  float extraout_s3_00;
  float fVar32;
  float extraout_s3_01;
  float extraout_s3_02;
  float extraout_s3_03;
  float extraout_s3_04;
  float extraout_s3_05;
  float extraout_s3_06;
  float extraout_s4;
  float extraout_s4_00;
  float fVar33;
  float extraout_s4_01;
  float extraout_s4_02;
  float extraout_s4_03;
  float extraout_s4_04;
  float extraout_s4_05;
  float extraout_s4_06;
  float extraout_s5;
  float extraout_s5_00;
  float fVar34;
  float extraout_s5_01;
  float extraout_s5_02;
  float extraout_s5_03;
  float extraout_s5_04;
  float extraout_s5_05;
  float extraout_s5_06;
  float extraout_s6;
  float extraout_s6_00;
  float fVar35;
  float extraout_s6_01;
  float extraout_s6_02;
  float extraout_s6_03;
  float extraout_s6_04;
  float extraout_s6_05;
  float extraout_s6_06;
  undefined4 uVar36;
  undefined4 extraout_s15;
  undefined4 extraout_s15_00;
  undefined4 extraout_s15_01;
  undefined4 extraout_s15_02;
  undefined4 extraout_s15_03;
  undefined4 extraout_s15_04;
  undefined4 extraout_s15_05;
  float fVar37;
  tColourSmall *local_b8;
  int local_ac;
  tMatrix atStack_88 [48];
  undefined4 local_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  float local_48;
  undefined4 uStack_44;
  float local_40;
  int local_3c [4];

  iVar3 = DAT_0004ace4 + 0x4a748;
  if (*(int *)(this + 0x328) < 1) {
    **(undefined1 **)(iVar3 + DAT_0004acec) = 1;
    G0RenderStart();
    cRBackdrop::Render((cRBackdrop *)(this + 0x4d2e0));
    tMatrix::Identity(atStack_88);
    iVar10 = 0;
    iVar17 = 0;
    pcVar6 = this;
    do {
      *(undefined4 *)((int)local_3c + iVar10) = 0xffffffff;
      iVar10 = iVar10 + 4;
      pcVar1 = pcVar6 + 0x36c;
      pcVar6 = pcVar6 + 0x30;
      if ((*(uint *)pcVar1 & 1) != 0) {
        iVar17 = iVar17 + 1;
      }
    } while (iVar10 != 0xc);
    iVar10 = 0;
    iVar27 = 0;
    *(uint *)(this + 0x39c) = *(uint *)(this + 0x39c) & 0xffffff | 0x2000000;
    pcVar6 = this;
    do {
      if ((*(uint *)(pcVar6 + 0x36c) & 1) != 0) {
        if (iVar10 == 0) {
          local_3c[0] = iVar27;
          iVar10 = 1;
        }
        else if (0 < iVar10) {
          iVar18 = *(int *)(pcVar6 + 0x368);
          iVar11 = 0;
          do {
            if (*(int *)(this + local_3c[iVar11] * 0x30 + 0x368) < iVar18) {
              if (iVar11 < 2) {
                piVar21 = local_3c + 2;
                do {
                  piVar12 = piVar21 + -1;
                  *piVar21 = piVar21[-1];
                  piVar21 = piVar12;
                } while (piVar12 != local_3c + iVar11);
              }
              iVar10 = iVar10 + 1;
              local_3c[iVar11] = iVar27;
              iVar11 = iVar10;
            }
            iVar11 = iVar11 + 1;
          } while (iVar11 < iVar10);
        }
      }
      iVar27 = iVar27 + 1;
      pcVar6 = pcVar6 + 0x30;
    } while (iVar27 != 3);
    iVar10 = **(int **)(iVar3 + DAT_0004acf0);
    *(float *)(this + 0x3bc) =
         (*(float *)(iVar10 + 0x3c) - **(float **)(iVar3 + DAT_0004acf4)) -
         *(float *)(iVar10 + 0x48);
    uVar36 = *(undefined4 *)(iVar10 + 0x4c);
    *(undefined4 *)(this + 0x3c0) = uVar36;
    iVar10 = DAT_0004acfc;
    fVar2 = DAT_0004acd8;
    if (iVar17 != 0) {
      iVar27 = 0;
      pcVar13 = (char *)(iVar3 + DAT_0004acf8);
      local_ac = 0;
      pcVar14 = (char *)(iVar3 + DAT_0004ad00);
      fVar29 = extraout_s0;
      fVar37 = extraout_s1;
      fVar31 = extraout_s2;
      fVar32 = extraout_s3;
      fVar33 = extraout_s4;
      fVar34 = extraout_s5;
      fVar35 = extraout_s6;
      do {
        while( true ) {
          iVar11 = local_3c[local_ac];
          uVar15 = *(uint *)(this + iVar11 * 0x30 + 0x36c);
          if ((uVar15 & 1) != 0) break;
LAB_0004ab24:
          local_ac = local_ac + 1;
          if (iVar17 <= local_ac) goto LAB_0004ab3c;
        }
        if ((uVar15 & 6) != 6) {
          bVar28 = (uVar15 & 0x10) != 0;
          if (bVar28) {
            uVar36 = DAT_0004acdc;
          }
          if (bVar28) {
            *(undefined4 *)(this + iVar11 * 0x30 + 0x37c) = uVar36;
            *(undefined4 *)(this + iVar11 * 0x30 + 0x374) = DAT_0004ace0;
          }
          else {
            uVar36 = *(undefined4 *)(this + iVar11 * 0x30 + 0x37c);
          }
          G0RenderCamera(fVar29,fVar37,fVar31,fVar32,fVar33,
                         *(tMatrix **)(this + iVar11 * 0x30 + 0x370),
                         *(tMatrix **)(this + iVar11 * 0x30 + 0x374),
                         SUB41(*(undefined4 *)(this + iVar11 * 0x30 + 0x378),0),SUB41(uVar36,0),
                         fVar34,fVar35);
          uVar15 = *(uint *)(this + iVar11 * 0x30 + 0x36c);
          fVar29 = extraout_s0_00;
          fVar37 = extraout_s1_00;
          fVar31 = extraout_s2_00;
          fVar32 = extraout_s3_00;
          fVar33 = extraout_s4_00;
          fVar34 = extraout_s5_00;
          fVar35 = extraout_s6_00;
          uVar36 = extraout_s15;
        }
        iVar18 = DAT_0004ad04;
        if ((uVar15 & 2) == 0) {
          pcVar19 = *(cRBod **)(this + 0x35c);
          if (pcVar19 == (cRBod *)0x0) {
            iVar27 = 0;
          }
          else {
            iVar27 = 0;
            iVar4 = DAT_0004ad04;
            do {
              while( true ) {
                if ((*(uint *)(pcVar19 + 4) & 0x10) == 0) {
                  uVar15 = *(uint *)(pcVar19 + 4);
                }
                else {
                  fVar29 = (float)wprintf(pcVar14);
                  uVar15 = *(uint *)(pcVar19 + 4);
                  iVar4 = extraout_r1;
                  fVar37 = extraout_s1_01;
                  fVar31 = extraout_s2_01;
                  fVar32 = extraout_s3_01;
                  fVar33 = extraout_s4_01;
                  fVar34 = extraout_s5_01;
                  fVar35 = extraout_s6_01;
                  uVar36 = extraout_s15_00;
                }
                if (((uVar15 & 0x22) == 0x22) &&
                   (uVar7 = uVar15 & *(uint *)(this + iVar11 * 0x30 + 0x36c),
                   (uVar7 & 0xff000000) != 0)) break;
                pcVar19 = *(cRBod **)(pcVar19 + 0xc);
                if (pcVar19 == (cRBod *)0x0) goto LAB_0004aaf4;
              }
              if ((uVar15 & 0x80) != 0) {
                uVar7 = *(uint *)(iVar3 + iVar18);
                *(cRBod **)(uVar7 + iVar27 * 4) = pcVar19;
                iVar27 = iVar27 + 1;
                iVar4 = iVar3;
              }
              bVar28 = (uVar15 & 0x800) != 0;
              if (bVar28) {
                uVar7 = *(uint *)(pcVar19 + 0x24);
                iVar4 = *(int *)(pcVar19 + 0x6c);
              }
              if (bVar28) {
                uVar36 = *(undefined4 *)(iVar4 + 4);
                uVar7 = *(uint *)(uVar7 + 0x104);
              }
              if (bVar28) {
                *(undefined4 *)(uVar7 + 0x10) = uVar36;
              }
              if ((uVar15 & 0x400) == 0) {
                pcVar22 = *(cRObject **)(pcVar19 + 0x24);
                local_58 = *(undefined4 *)(pcVar19 + 0x10);
                uStack_54 = *(undefined4 *)(pcVar19 + 0x14);
                uStack_50 = *(undefined4 *)(pcVar19 + 0x18);
                local_b8 = *(tColourSmall **)(pcVar19 + 0x1c);
                uVar36 = *(undefined4 *)(pcVar19 + 0x20);
                uVar30 = cRBod::IsAfterSprites(pcVar19);
                uVar25 = (undefined1)uVar36;
                ptVar5 = atStack_88;
              }
              else {
                local_b8 = *(tColourSmall **)(pcVar19 + 0x1c);
                uVar25 = (undefined1)*(undefined4 *)(pcVar19 + 0x20);
                pcVar22 = *(cRObject **)(pcVar19 + 0x24);
                uVar30 = cRBod::IsAfterSprites(pcVar19);
                ptVar5 = (tMatrix *)(pcVar19 + 0x2c);
              }
              fVar29 = (float)G0RenderObject(pcVar22,ptVar5,(float)uVar30,
                                             (float)((ulonglong)uVar30 >> 0x20),local_b8,
                                             (bool)uVar25);
              pcVar19 = *(cRBod **)(pcVar19 + 0xc);
              iVar4 = extraout_r1_00;
              fVar37 = extraout_s1_02;
              fVar31 = extraout_s2_02;
              fVar32 = extraout_s3_02;
              fVar33 = extraout_s4_02;
              fVar34 = extraout_s5_02;
              fVar35 = extraout_s6_02;
              uVar36 = extraout_s15_01;
            } while (pcVar19 != (cRBod *)0x0);
LAB_0004aaf4:
            uVar15 = *(uint *)(this + iVar11 * 0x30 + 0x36c);
          }
        }
        iVar18 = DAT_0004ad0c;
        if ((uVar15 & 4) == 0) {
          iVar20 = *(int *)(*(int *)(iVar3 + iVar10) + (iVar11 + 44000) * 4 + 4);
          G0RenderSprite3DStart();
          fVar29 = DAT_0004ad10;
          iVar4 = DAT_0004ad0c;
          if (iVar20 != 0) {
            puVar24 = *(undefined4 **)(iVar3 + DAT_0004ad08);
            do {
              while (uVar15 = *(uint *)(iVar20 + 4), iVar18 = iVar4,
                    (uVar15 & *(uint *)(this + iVar11 * 0x30 + 0x36c) & 0xff000000) == 0) {
                RShellError(pcVar13);
                iVar20 = *(int *)(iVar20 + 0xc);
                if (iVar20 == 0) goto LAB_0004adc0;
              }
              puVar23 = puVar24;
              if (((uVar15 & 1) != 0) && ((uVar15 & 0x240) == 0x40)) {
                iVar16 = *(int *)(this + iVar11 * 0x30 + 900);
                local_48 = *(float *)(iVar20 + 0x48);
                uStack_44 = *(undefined4 *)(iVar20 + 0x4c);
                local_40 = *(float *)(iVar20 + 0x50);
                tVector::operator*=((tVector *)&local_48,*(undefined4 *)(iVar16 + 0x74),
                                    *(undefined4 *)(iVar16 + 0x78),*(undefined4 *)(iVar16 + 0x7c),
                                    *(undefined4 *)(iVar16 + 0x80),*(undefined4 *)(iVar16 + 0x84),
                                    *(undefined4 *)(iVar16 + 0x88),*(undefined4 *)(iVar16 + 0x8c),
                                    *(undefined4 *)(iVar16 + 0x90),*(undefined4 *)(iVar16 + 0x94),
                                    *(undefined4 *)(iVar16 + 0x98),*(undefined4 *)(iVar16 + 0x9c),
                                    *(undefined4 *)(iVar16 + 0xa0),*(undefined4 *)(iVar16 + 0xa4),
                                    *(undefined4 *)(iVar16 + 0xa8),*(undefined4 *)(iVar16 + 0xac),
                                    *(undefined4 *)(iVar16 + 0xb0));
                local_40 = -local_40;
                local_48 = -local_48;
                fVar37 = (local_40 * fVar2) / fVar29 + *(float *)(iVar20 + 0x94);
                iVar16 = (int)fVar37;
                if (iVar16 < 0x100) {
                  if (iVar16 < 0) goto LAB_0004ad88;
                }
                else {
                  iVar16 = 0xff;
                }
                puVar23 = puVar24 + 6;
                puVar8 = *(undefined4 **)(*(int *)(iVar3 + iVar4) + iVar16 * 4);
                if (puVar8 == (undefined4 *)0x0) {
                  *(undefined4 **)(*(int *)(iVar3 + iVar4) + iVar16 * 4) = puVar24;
                  *puVar24 = 0;
                }
                else {
                  if (fVar37 < (float)puVar8[4]) {
                    do {
                      puVar9 = puVar8;
                      puVar8 = (undefined4 *)*puVar9;
                      if (puVar8 == (undefined4 *)0x0) goto LAB_0004af6c;
                    } while (fVar37 < (float)puVar8[4]);
                    if (puVar9 != (undefined4 *)0x0) {
LAB_0004af6c:
                      *puVar9 = puVar24;
                      *puVar24 = puVar8;
                      goto LAB_0004af74;
                    }
                  }
                  *puVar24 = puVar8;
                  *(undefined4 **)(*(int *)(iVar3 + iVar4) + iVar16 * 4) = puVar24;
                }
LAB_0004af74:
                puVar24[4] = fVar37;
                puVar24[5] = iVar20;
                *(int *)(iVar20 + 0x14) = iVar16;
                puVar24[1] = local_48;
                puVar24[2] = uStack_44;
                puVar24[3] = local_40;
                *(float *)(iVar20 + 0x18) = fVar37;
              }
LAB_0004ad88:
              iVar20 = *(int *)(iVar20 + 0xc);
              puVar24 = puVar23;
            } while (iVar20 != 0);
          }
LAB_0004adc0:
          iVar18 = *(int *)(iVar3 + iVar18);
          iVar4 = iVar18 + -0x400;
          do {
            piVar21 = *(int **)(iVar18 + 0x3fc);
            if (piVar21 != (int *)0x0) {
              do {
                while (this_00 = (cRSprite *)piVar21[5], (*(uint *)(this_00 + 4) & 2) == 0) {
                  G0RenderSprite3D((tVector *)(piVar21 + 1),this_00);
                  piVar21 = (int *)*piVar21;
                  if (piVar21 == (int *)0x0) goto LAB_0004ae38;
                }
                cRSprite::BuildTail(this_00,(tMatrix *)(*(int *)(this + iVar11 * 0x30 + 900) + 0x74)
                                   );
                G0RenderSprite3D((tVector *)(piVar21 + 1),(cRSprite *)piVar21[5]);
                piVar21 = (int *)*piVar21;
              } while (piVar21 != (int *)0x0);
LAB_0004ae38:
              *(undefined4 *)(iVar18 + 0x3fc) = 0;
            }
            iVar18 = iVar18 + -4;
          } while (iVar18 != iVar4);
          G0RenderSprite3DEnd();
          uVar15 = *(uint *)(this + iVar11 * 0x30 + 0x36c);
          fVar29 = extraout_s0_04;
          fVar37 = extraout_s1_06;
          fVar31 = extraout_s2_06;
          fVar32 = extraout_s3_06;
          fVar33 = extraout_s4_06;
          fVar34 = extraout_s5_06;
          fVar35 = extraout_s6_06;
          uVar36 = extraout_s15_05;
        }
        if ((uVar15 & 8) == 0) {
          G0FontRenderStart();
          FontPrintRender(*(int *)(this + iVar11 * 0x30 + 0x36c));
          G0FontRenderEnd();
          uVar15 = *(uint *)(this + iVar11 * 0x30 + 0x36c);
          fVar29 = extraout_s0_03;
          fVar37 = extraout_s1_05;
          fVar31 = extraout_s2_05;
          fVar32 = extraout_s3_05;
          fVar33 = extraout_s4_05;
          fVar34 = extraout_s5_05;
          fVar35 = extraout_s6_05;
          uVar36 = extraout_s15_04;
        }
        if (((uVar15 & 2) != 0) || (iVar27 == 0)) goto LAB_0004ab24;
        G0RenderCamera(fVar29,fVar37,fVar31,fVar32,fVar33,
                       *(tMatrix **)(this + iVar11 * 0x30 + 0x370),
                       *(tMatrix **)(this + iVar11 * 0x30 + 0x374),
                       SUB41(*(undefined4 *)(this + iVar11 * 0x30 + 0x378),0),
                       SUB41(*(undefined4 *)(this + iVar11 * 0x30 + 0x37c),0),fVar34,fVar35);
        iVar11 = *(int *)(iVar3 + DAT_0004ad04) + iVar27 * 4;
        do {
          while( true ) {
            pcVar19 = *(cRBod **)(iVar11 + -4);
            iVar27 = iVar27 + -1;
            if ((*(uint *)(pcVar19 + 4) & 0x400) != 0) break;
            local_58 = *(undefined4 *)(pcVar19 + 0x10);
            uStack_54 = *(undefined4 *)(pcVar19 + 0x14);
            uStack_50 = *(undefined4 *)(pcVar19 + 0x18);
            pcVar22 = *(cRObject **)(pcVar19 + 0x24);
            iVar11 = iVar11 + -4;
            ptVar26 = *(tColourSmall **)(pcVar19 + 0x1c);
            uVar36 = *(undefined4 *)(pcVar19 + 0x20);
            uVar30 = cRBod::IsAfterSprites(pcVar19);
            G0RenderObject(pcVar22,atStack_88,(float)uVar30,(float)((ulonglong)uVar30 >> 0x20),
                           ptVar26,SUB41(uVar36,0));
            fVar29 = extraout_s0_02;
            fVar37 = extraout_s1_04;
            fVar31 = extraout_s2_04;
            fVar32 = extraout_s3_04;
            fVar33 = extraout_s4_04;
            fVar34 = extraout_s5_04;
            fVar35 = extraout_s6_04;
            uVar36 = extraout_s15_03;
            if (iVar27 == 0) goto LAB_0004ac94;
          }
          pcVar22 = *(cRObject **)(pcVar19 + 0x24);
          iVar11 = iVar11 + -4;
          ptVar26 = *(tColourSmall **)(pcVar19 + 0x1c);
          uVar36 = *(undefined4 *)(pcVar19 + 0x20);
          uVar30 = cRBod::IsAfterSprites(pcVar19);
          G0RenderObject(pcVar22,(tMatrix *)(pcVar19 + 0x2c),(float)uVar30,
                         (float)((ulonglong)uVar30 >> 0x20),ptVar26,SUB41(uVar36,0));
          fVar29 = extraout_s0_01;
          fVar37 = extraout_s1_03;
          fVar31 = extraout_s2_03;
          fVar32 = extraout_s3_03;
          fVar33 = extraout_s4_03;
          fVar34 = extraout_s5_03;
          fVar35 = extraout_s6_03;
          uVar36 = extraout_s15_02;
        } while (iVar27 != 0);
LAB_0004ac94:
        local_ac = local_ac + 1;
      } while (local_ac < iVar17);
    }
LAB_0004ab3c:
    G0RenderEnd();
  }
  else {
    wprintf((char *)(iVar3 + DAT_0004ace8));
    *(int *)(this + 0x328) = *(int *)(this + 0x328) + -1;
  }
  return;
}
