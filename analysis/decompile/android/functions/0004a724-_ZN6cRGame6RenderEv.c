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
  int iVar2;
  undefined **ppuVar3;
  undefined **extraout_r1;
  tMatrix *ptVar4;
  undefined **extraout_r1_00;
  cRSprite *this_00;
  cRGame *pcVar5;
  undefined1 *puVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  int iVar9;
  int iVar10;
  int *piVar11;
  uint uVar12;
  int iVar13;
  int iVar14;
  cRBod *pcVar15;
  int *piVar16;
  undefined4 uVar17;
  cRObject *pcVar18;
  undefined4 *puVar19;
  undefined4 *puVar20;
  undefined1 uVar21;
  tColourSmall *ptVar22;
  int iVar23;
  bool bVar24;
  float extraout_s0;
  float extraout_s0_00;
  float fVar25;
  float extraout_s0_01;
  float extraout_s0_02;
  float extraout_s0_03;
  float extraout_s0_04;
  float extraout_s1;
  float extraout_s1_00;
  float fVar27;
  float extraout_s1_01;
  undefined8 uVar26;
  float extraout_s1_02;
  float extraout_s1_03;
  float extraout_s1_04;
  float extraout_s1_05;
  float extraout_s1_06;
  float extraout_s2;
  float extraout_s2_00;
  float fVar28;
  float extraout_s2_01;
  float extraout_s2_02;
  float extraout_s2_03;
  float extraout_s2_04;
  float extraout_s2_05;
  float extraout_s2_06;
  float extraout_s3;
  float extraout_s3_00;
  float fVar29;
  float extraout_s3_01;
  float extraout_s3_02;
  float extraout_s3_03;
  float extraout_s3_04;
  float extraout_s3_05;
  float extraout_s3_06;
  float extraout_s4;
  float extraout_s4_00;
  float fVar30;
  float extraout_s4_01;
  float extraout_s4_02;
  float extraout_s4_03;
  float extraout_s4_04;
  float extraout_s4_05;
  float extraout_s4_06;
  float extraout_s5;
  float extraout_s5_00;
  float fVar31;
  float extraout_s5_01;
  float extraout_s5_02;
  float extraout_s5_03;
  float extraout_s5_04;
  float extraout_s5_05;
  float extraout_s5_06;
  float extraout_s6;
  float extraout_s6_00;
  float fVar32;
  float extraout_s6_01;
  float extraout_s6_02;
  float extraout_s6_03;
  float extraout_s6_04;
  float extraout_s6_05;
  float extraout_s6_06;
  undefined *puVar33;
  undefined *extraout_s15;
  undefined *extraout_s15_00;
  undefined *extraout_s15_01;
  undefined *extraout_s15_02;
  undefined *extraout_s15_03;
  undefined *extraout_s15_04;
  undefined *extraout_s15_05;
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

  if (*(int *)(this + 0x328) < 1) {
    G0SwapBufferRequest = 1;
    G0RenderStart();
    cRBackdrop::Render((cRBackdrop *)(this + 0x4d2e0));
    tMatrix::Identity(atStack_88);
    iVar9 = 0;
    iVar13 = 0;
    pcVar5 = this;
    do {
      *(undefined4 *)((int)local_3c + iVar9) = 0xffffffff;
      iVar9 = iVar9 + 4;
      pcVar1 = pcVar5 + 0x36c;
      pcVar5 = pcVar5 + 0x30;
      if ((*(uint *)pcVar1 & 1) != 0) {
        iVar13 = iVar13 + 1;
      }
    } while (iVar9 != 0xc);
    iVar2 = 0;
    iVar23 = 0;
    *(uint *)(this + 0x39c) = *(uint *)(this + 0x39c) & 0xffffff | 0x2000000;
    iVar9 = Game;
    pcVar5 = this;
    do {
      if ((*(uint *)(pcVar5 + 0x36c) & 1) != 0) {
        if (iVar2 == 0) {
          local_3c[0] = iVar23;
          iVar2 = 1;
        }
        else if (0 < iVar2) {
          iVar14 = *(int *)(pcVar5 + 0x368);
          iVar10 = 0;
          do {
            if (*(int *)(this + local_3c[iVar10] * 0x30 + 0x368) < iVar14) {
              if (iVar10 < 2) {
                piVar16 = local_3c + 2;
                do {
                  piVar11 = piVar16 + -1;
                  *piVar16 = piVar16[-1];
                  piVar16 = piVar11;
                } while (piVar11 != local_3c + iVar10);
              }
              iVar2 = iVar2 + 1;
              local_3c[iVar10] = iVar23;
              iVar10 = iVar2;
            }
            iVar10 = iVar10 + 1;
          } while (iVar10 < iVar2);
        }
      }
      iVar23 = iVar23 + 1;
      pcVar5 = pcVar5 + 0x30;
    } while (iVar23 != 3);
    *(float *)(this + 0x3bc) =
         (*(float *)(Game + 0x3c) - gAndroidOrientation) - *(float *)(Game + 0x48);
    puVar33 = *(undefined **)(iVar9 + 0x4c);
    *(undefined **)(this + 0x3c0) = puVar33;
    if (iVar13 != 0) {
      iVar9 = 0;
      local_ac = 0;
      fVar25 = extraout_s0;
      fVar27 = extraout_s1;
      fVar28 = extraout_s2;
      fVar29 = extraout_s3;
      fVar30 = extraout_s4;
      fVar31 = extraout_s5;
      fVar32 = extraout_s6;
      do {
        while( true ) {
          iVar2 = local_3c[local_ac];
          uVar12 = *(uint *)(this + iVar2 * 0x30 + 0x36c);
          if ((uVar12 & 1) != 0) break;
LAB_0004ab24:
          local_ac = local_ac + 1;
          if (iVar13 <= local_ac) goto LAB_0004ab3c;
        }
        if ((uVar12 & 6) != 6) {
          bVar24 = (uVar12 & 0x10) != 0;
          if (bVar24) {
            puVar33 = (undefined *)0x3f000000;
          }
          if (bVar24) {
            *(undefined **)(this + iVar2 * 0x30 + 0x37c) = puVar33;
            *(undefined4 *)(this + iVar2 * 0x30 + 0x374) = 0;
          }
          else {
            puVar33 = *(undefined **)(this + iVar2 * 0x30 + 0x37c);
          }
          G0RenderCamera(fVar25,fVar27,fVar28,fVar29,fVar30,
                         *(tMatrix **)(this + iVar2 * 0x30 + 0x370),
                         *(tMatrix **)(this + iVar2 * 0x30 + 0x374),
                         SUB41(*(undefined4 *)(this + iVar2 * 0x30 + 0x378),0),SUB41(puVar33,0),
                         fVar31,fVar32);
          uVar12 = *(uint *)(this + iVar2 * 0x30 + 0x36c);
          fVar25 = extraout_s0_00;
          fVar27 = extraout_s1_00;
          fVar28 = extraout_s2_00;
          fVar29 = extraout_s3_00;
          fVar30 = extraout_s4_00;
          fVar31 = extraout_s5_00;
          fVar32 = extraout_s6_00;
          puVar33 = extraout_s15;
        }
        if ((uVar12 & 2) == 0) {
          pcVar15 = *(cRBod **)(this + 0x35c);
          if (pcVar15 == (cRBod *)0x0) {
            iVar9 = 0;
          }
          else {
            ppuVar3 = (undefined **)0x2d8;
            iVar9 = 0;
            do {
              while( true ) {
                if ((*(uint *)(pcVar15 + 4) & 0x10) == 0) {
                  uVar12 = *(uint *)(pcVar15 + 4);
                }
                else {
                  fVar25 = (float)wprintf("DEBUG RENDER\n");
                  uVar12 = *(uint *)(pcVar15 + 4);
                  ppuVar3 = extraout_r1;
                  fVar27 = extraout_s1_01;
                  fVar28 = extraout_s2_01;
                  fVar29 = extraout_s3_01;
                  fVar30 = extraout_s4_01;
                  fVar31 = extraout_s5_01;
                  fVar32 = extraout_s6_01;
                  puVar33 = extraout_s15_00;
                }
                if (((uVar12 & 0x22) == 0x22) &&
                   (puVar6 = (undefined1 *)(uVar12 & *(uint *)(this + iVar2 * 0x30 + 0x36c)),
                   ((uint)puVar6 & 0xff000000) != 0)) break;
                pcVar15 = *(cRBod **)(pcVar15 + 0xc);
                if (pcVar15 == (cRBod *)0x0) goto LAB_0004aaf4;
              }
              if ((uVar12 & 0x80) != 0) {
                puVar6 = gBodZList;
                *(cRBod **)(gBodZList + iVar9 * 4) = pcVar15;
                iVar9 = iVar9 + 1;
                ppuVar3 = &__DT_PLTGOT;
              }
              bVar24 = (uVar12 & 0x800) != 0;
              if (bVar24) {
                puVar6 = *(undefined1 **)(pcVar15 + 0x24);
                ppuVar3 = *(undefined ***)(pcVar15 + 0x6c);
              }
              if (bVar24) {
                puVar33 = ppuVar3[1];
                puVar6 = *(undefined1 **)(puVar6 + 0x104);
              }
              if (bVar24) {
                *(undefined **)(puVar6 + 0x10) = puVar33;
              }
              if ((uVar12 & 0x400) == 0) {
                pcVar18 = *(cRObject **)(pcVar15 + 0x24);
                local_58 = *(undefined4 *)(pcVar15 + 0x10);
                uStack_54 = *(undefined4 *)(pcVar15 + 0x14);
                uStack_50 = *(undefined4 *)(pcVar15 + 0x18);
                local_b8 = *(tColourSmall **)(pcVar15 + 0x1c);
                uVar17 = *(undefined4 *)(pcVar15 + 0x20);
                uVar26 = cRBod::IsAfterSprites(pcVar15);
                uVar21 = (undefined1)uVar17;
                ptVar4 = atStack_88;
              }
              else {
                local_b8 = *(tColourSmall **)(pcVar15 + 0x1c);
                uVar21 = (undefined1)*(undefined4 *)(pcVar15 + 0x20);
                pcVar18 = *(cRObject **)(pcVar15 + 0x24);
                uVar26 = cRBod::IsAfterSprites(pcVar15);
                ptVar4 = (tMatrix *)(pcVar15 + 0x2c);
              }
              fVar25 = (float)G0RenderObject(pcVar18,ptVar4,(float)uVar26,
                                             (float)((ulonglong)uVar26 >> 0x20),local_b8,
                                             (bool)uVar21);
              pcVar15 = *(cRBod **)(pcVar15 + 0xc);
              ppuVar3 = extraout_r1_00;
              fVar27 = extraout_s1_02;
              fVar28 = extraout_s2_02;
              fVar29 = extraout_s3_02;
              fVar30 = extraout_s4_02;
              fVar31 = extraout_s5_02;
              fVar32 = extraout_s6_02;
              puVar33 = extraout_s15_01;
            } while (pcVar15 != (cRBod *)0x0);
LAB_0004aaf4:
            uVar12 = *(uint *)(this + iVar2 * 0x30 + 0x36c);
          }
        }
        if ((uVar12 & 4) == 0) {
          iVar23 = *(int *)(&DAT_00132054 + (iVar2 + 44000) * 4);
          G0RenderSprite3DStart();
          if (iVar23 != 0) {
            puVar20 = (undefined4 *)ZBuffer;
            do {
              while (uVar12 = *(uint *)(iVar23 + 4),
                    (uVar12 & *(uint *)(this + iVar2 * 0x30 + 0x36c) & 0xff000000) == 0) {
                RShellError("Loose Sprite scene viewport");
                iVar23 = *(int *)(iVar23 + 0xc);
                if (iVar23 == 0) goto LAB_0004adc0;
              }
              puVar19 = puVar20;
              if (((uVar12 & 1) != 0) && ((uVar12 & 0x240) == 0x40)) {
                iVar10 = *(int *)(this + iVar2 * 0x30 + 900);
                local_48 = *(float *)(iVar23 + 0x48);
                uStack_44 = *(undefined4 *)(iVar23 + 0x4c);
                local_40 = *(float *)(iVar23 + 0x50);
                tVector::operator*=((tVector *)&local_48,*(undefined4 *)(iVar10 + 0x74),
                                    *(undefined4 *)(iVar10 + 0x78),*(undefined4 *)(iVar10 + 0x7c),
                                    *(undefined4 *)(iVar10 + 0x80),*(undefined4 *)(iVar10 + 0x84),
                                    *(undefined4 *)(iVar10 + 0x88),*(undefined4 *)(iVar10 + 0x8c),
                                    *(undefined4 *)(iVar10 + 0x90),*(undefined4 *)(iVar10 + 0x94),
                                    *(undefined4 *)(iVar10 + 0x98),*(undefined4 *)(iVar10 + 0x9c),
                                    *(undefined4 *)(iVar10 + 0xa0),*(undefined4 *)(iVar10 + 0xa4),
                                    *(undefined4 *)(iVar10 + 0xa8),*(undefined4 *)(iVar10 + 0xac),
                                    *(undefined4 *)(iVar10 + 0xb0));
                local_40 = -local_40;
                local_48 = -local_48;
                fVar25 = (local_40 * -256.0) / 61.0 + *(float *)(iVar23 + 0x94);
                iVar10 = (int)fVar25;
                if (iVar10 < 0x100) {
                  if (iVar10 < 0) goto LAB_0004ad88;
                }
                else {
                  iVar10 = 0xff;
                }
                puVar19 = puVar20 + 6;
                puVar7 = *(undefined4 **)(ZBufferIndex + iVar10 * 4);
                if (puVar7 == (undefined4 *)0x0) {
                  *(undefined4 **)(ZBufferIndex + iVar10 * 4) = puVar20;
                  *puVar20 = 0;
                }
                else {
                  if (fVar25 < (float)puVar7[4]) {
                    do {
                      puVar8 = puVar7;
                      puVar7 = (undefined4 *)*puVar8;
                      if (puVar7 == (undefined4 *)0x0) goto LAB_0004af6c;
                    } while (fVar25 < (float)puVar7[4]);
                    if (puVar8 != (undefined4 *)0x0) {
LAB_0004af6c:
                      *puVar8 = puVar20;
                      *puVar20 = puVar7;
                      goto LAB_0004af74;
                    }
                  }
                  *puVar20 = puVar7;
                  *(undefined4 **)(ZBufferIndex + iVar10 * 4) = puVar20;
                }
LAB_0004af74:
                puVar20[4] = fVar25;
                puVar20[5] = iVar23;
                *(int *)(iVar23 + 0x14) = iVar10;
                puVar20[1] = local_48;
                puVar20[2] = uStack_44;
                puVar20[3] = local_40;
                *(float *)(iVar23 + 0x18) = fVar25;
              }
LAB_0004ad88:
              iVar23 = *(int *)(iVar23 + 0xc);
              puVar20 = puVar19;
            } while (iVar23 != 0);
          }
LAB_0004adc0:
          puVar6 = ZBufferIndex;
          do {
            piVar16 = *(int **)(puVar6 + 0x3fc);
            if (piVar16 != (int *)0x0) {
              do {
                while (this_00 = (cRSprite *)piVar16[5], (*(uint *)(this_00 + 4) & 2) == 0) {
                  G0RenderSprite3D((tVector *)(piVar16 + 1),this_00);
                  piVar16 = (int *)*piVar16;
                  if (piVar16 == (int *)0x0) goto LAB_0004ae38;
                }
                cRSprite::BuildTail(this_00,(tMatrix *)(*(int *)(this + iVar2 * 0x30 + 900) + 0x74))
                ;
                G0RenderSprite3D((tVector *)(piVar16 + 1),(cRSprite *)piVar16[5]);
                piVar16 = (int *)*piVar16;
              } while (piVar16 != (int *)0x0);
LAB_0004ae38:
              *(undefined4 *)(puVar6 + 0x3fc) = 0;
            }
            puVar6 = puVar6 + -4;
          } while (puVar6 != ZBuffer + 0x59c0);
          G0RenderSprite3DEnd();
          uVar12 = *(uint *)(this + iVar2 * 0x30 + 0x36c);
          fVar25 = extraout_s0_04;
          fVar27 = extraout_s1_06;
          fVar28 = extraout_s2_06;
          fVar29 = extraout_s3_06;
          fVar30 = extraout_s4_06;
          fVar31 = extraout_s5_06;
          fVar32 = extraout_s6_06;
          puVar33 = extraout_s15_05;
        }
        if ((uVar12 & 8) == 0) {
          G0FontRenderStart();
          FontPrintRender(*(int *)(this + iVar2 * 0x30 + 0x36c));
          G0FontRenderEnd();
          uVar12 = *(uint *)(this + iVar2 * 0x30 + 0x36c);
          fVar25 = extraout_s0_03;
          fVar27 = extraout_s1_05;
          fVar28 = extraout_s2_05;
          fVar29 = extraout_s3_05;
          fVar30 = extraout_s4_05;
          fVar31 = extraout_s5_05;
          fVar32 = extraout_s6_05;
          puVar33 = extraout_s15_04;
        }
        if (((uVar12 & 2) != 0) || (iVar9 == 0)) goto LAB_0004ab24;
        G0RenderCamera(fVar25,fVar27,fVar28,fVar29,fVar30,*(tMatrix **)(this + iVar2 * 0x30 + 0x370)
                       ,*(tMatrix **)(this + iVar2 * 0x30 + 0x374),
                       SUB41(*(undefined4 *)(this + iVar2 * 0x30 + 0x378),0),
                       SUB41(*(undefined4 *)(this + iVar2 * 0x30 + 0x37c),0),fVar31,fVar32);
        puVar6 = gBodZList + iVar9 * 4;
        do {
          while( true ) {
            pcVar15 = *(cRBod **)(puVar6 + -4);
            iVar9 = iVar9 + -1;
            if ((*(uint *)(pcVar15 + 4) & 0x400) != 0) break;
            local_58 = *(undefined4 *)(pcVar15 + 0x10);
            uStack_54 = *(undefined4 *)(pcVar15 + 0x14);
            uStack_50 = *(undefined4 *)(pcVar15 + 0x18);
            pcVar18 = *(cRObject **)(pcVar15 + 0x24);
            puVar6 = puVar6 + -4;
            ptVar22 = *(tColourSmall **)(pcVar15 + 0x1c);
            uVar17 = *(undefined4 *)(pcVar15 + 0x20);
            uVar26 = cRBod::IsAfterSprites(pcVar15);
            G0RenderObject(pcVar18,atStack_88,(float)uVar26,(float)((ulonglong)uVar26 >> 0x20),
                           ptVar22,SUB41(uVar17,0));
            fVar25 = extraout_s0_02;
            fVar27 = extraout_s1_04;
            fVar28 = extraout_s2_04;
            fVar29 = extraout_s3_04;
            fVar30 = extraout_s4_04;
            fVar31 = extraout_s5_04;
            fVar32 = extraout_s6_04;
            puVar33 = extraout_s15_03;
            if (iVar9 == 0) goto LAB_0004ac94;
          }
          pcVar18 = *(cRObject **)(pcVar15 + 0x24);
          puVar6 = puVar6 + -4;
          ptVar22 = *(tColourSmall **)(pcVar15 + 0x1c);
          uVar17 = *(undefined4 *)(pcVar15 + 0x20);
          uVar26 = cRBod::IsAfterSprites(pcVar15);
          G0RenderObject(pcVar18,(tMatrix *)(pcVar15 + 0x2c),(float)uVar26,
                         (float)((ulonglong)uVar26 >> 0x20),ptVar22,SUB41(uVar17,0));
          fVar25 = extraout_s0_01;
          fVar27 = extraout_s1_03;
          fVar28 = extraout_s2_03;
          fVar29 = extraout_s3_03;
          fVar30 = extraout_s4_03;
          fVar31 = extraout_s5_03;
          fVar32 = extraout_s6_03;
          puVar33 = extraout_s15_02;
        } while (iVar9 != 0);
LAB_0004ac94:
        local_ac = local_ac + 1;
      } while (local_ac < iVar13);
    }
LAB_0004ab3c:
    G0RenderEnd();
  }
  else {
    wprintf("Render Skip %i");
    *(int *)(this + 0x328) = *(int *)(this + 0x328) + -1;
  }
  return;
}
