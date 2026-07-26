/*
 * mangled: _ZN10cRSubGoldy9CollisionEv
 * demangled: cRSubGoldy::Collision()
 * address: 00077f5c
 * size: 3764
 */

/* cRSubGoldy::Collision() */

void __thiscall cRSubGoldy::Collision(cRSubGoldy *this)

{
  uint uVar1;
  cRSubGoldy cVar2;
  char cVar3;
  float fVar4;
  float fVar5;
  bool bVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  int iVar13;
  int iVar14;
  char *pcVar15;
  int iVar16;
  float *pfVar17;
  int iVar18;
  int iVar19;
  undefined4 uVar20;
  int iVar21;
  int iVar22;
  int iVar23;
  uint in_fpscr;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float fVar24;
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;

  fVar4 = DAT_0007833c;
  fVar12 = DAT_00078338;
  iVar23 = DAT_00078324 + 0x77f7c;
  cVar3 = (char)this;
  if (this[0x415] == (cRSubGoldy)0x1) {
    iVar18 = *(int *)(this + 0x400);
    iVar19 = iVar18;
  }
  else if (this[0x414] == (cRSubGoldy)0x1) {
    iVar18 = *(int *)(this + 0x400);
    iVar19 = iVar18;
  }
  else if (this[0x2c0] == (cRSubGoldy)0x1) {
    iVar18 = *(int *)(this + 0x400);
    iVar19 = iVar18;
  }
  else {
    if ((*(uint *)(this + 0x324) & 0x80) == 0) {
      iVar19 = *(int *)(this + 0x400);
      iVar18 = 0;
      do {
        iVar14 = iVar18 * 0x8c + iVar19;
        if (*(int *)(iVar14 + 0x4eec) == 1) {
          if (*(char *)(iVar14 + 0x4f00) != '\0') {
            local_4c = *(float *)(iVar14 + 0x4edc) - *(float *)(this + 0x27e8);
            local_54 = *(float *)(iVar14 + 0x4ed4) - *(float *)(this + 0x27e0);
            local_50 = *(float *)(iVar14 + 0x4ed8) - *(float *)(this + 0x27e4);
            in_fpscr = in_fpscr & 0xfffffff | (uint)(local_4c < fVar12) << 0x1f;
            if (SUB41(in_fpscr >> 0x1f,0)) {
              fVar9 = (float)tVector::Normalize((tVector *)&local_54);
              uVar1 = in_fpscr & 0xfffffff;
              in_fpscr = uVar1 | (uint)(fVar9 < fVar4) << 0x1f;
              if (SUB41(in_fpscr >> 0x1f,0)) {
                in_fpscr = uVar1 | (uint)(*(float *)(this + 0x1bc) == 0.0) << 0x1e;
                if (SUB41(in_fpscr >> 0x1e,0)) {
                  *(undefined4 *)(this + 0x1bc) = *(undefined4 *)(this + 0x1c0);
                }
                *(undefined1 *)(iVar18 * 0x8c + *(int *)(this + 0x400) + 0x4f00) = 0;
                cRDamageGuage::Take(extraout_s0,(bool)(cVar3 + -0x4c));
              }
              iVar19 = *(int *)(this + 0x400);
            }
          }
        }
        iVar18 = iVar18 + 1;
      } while (iVar18 != 0x28);
    }
    else {
      iVar19 = *(int *)(this + 0x400);
    }
    fVar4 = DAT_00078338;
    fVar12 = DAT_00078334;
    bVar6 = (bool)(cVar3 + -0x4c);
    iVar18 = 0;
    do {
      while( true ) {
        iVar14 = iVar19 + iVar18 * 0xa4;
        if (*(int *)(iVar14 + 0x421c) == 1) break;
LAB_00078654:
        iVar18 = iVar18 + 1;
        if (iVar18 == 0x14) goto LAB_00078704;
      }
      local_58 = *(float *)(iVar14 + 0x420c) - *(float *)(this + 0x27e8);
      local_60 = *(float *)(iVar14 + 0x4204) - *(float *)(this + 0x27e0);
      local_5c = *(float *)(iVar14 + 0x4208) - *(float *)(this + 0x27e4);
      in_fpscr = in_fpscr & 0xfffffff | (uint)(local_58 < fVar4) << 0x1f;
      if (!SUB41(in_fpscr >> 0x1f,0)) goto LAB_00078654;
      fVar9 = (float)tVector::Normalize((tVector *)&local_60);
      in_fpscr = in_fpscr & 0xfffffff | (uint)(fVar9 < fVar12) << 0x1f;
      if (SUB41(in_fpscr >> 0x1f,0)) {
        *(undefined4 *)(*(int *)(this + 0x400) + iVar18 * 0xa4 + 0x421c) = 2;
        cRDamageGuage::Take(extraout_s0_00,bVar6);
        iVar19 = *(int *)(this + 0x400);
      }
      else {
        iVar19 = *(int *)(this + 0x400);
      }
      iVar18 = iVar18 + 1;
    } while (iVar18 != 0x14);
LAB_00078704:
    fVar7 = DAT_00078a30;
    fVar9 = DAT_00078344;
    fVar4 = DAT_0007833c;
    fVar12 = DAT_00078338;
    iVar18 = DAT_0007832c;
    iVar14 = *(int *)(iVar19 + 0x6500);
    if (iVar14 != 0) {
      do {
        if (*(int *)(iVar14 + 0x78) == 1) {
          local_58 = *(float *)(iVar14 + 100) - *(float *)(this + 0x27e8);
          local_60 = *(float *)(iVar14 + 0x5c) - *(float *)(this + 0x27e0);
          local_5c = *(float *)(iVar14 + 0x60) - *(float *)(this + 0x27e4);
          in_fpscr = in_fpscr & 0xfffffff | (uint)(local_58 < fVar12) << 0x1f;
          if (SUB41(in_fpscr >> 0x1f,0)) {
            fVar10 = (float)tVector::Normalize((tVector *)&local_60);
            uVar1 = in_fpscr & 0xfffffff;
            in_fpscr = uVar1 | (uint)(fVar10 < fVar4) << 0x1f;
            if (SUB41(in_fpscr >> 0x1f,0)) {
              if ((*(uint *)(this + 0x324) & 0x80) == 0) {
                fVar10 = *(float *)(this + 0x410);
                *(float *)(this + 0x408) = *(float *)(this + 0x408) + local_60 * fVar10 * fVar9;
                *(float *)(this + 0x410) = fVar10 + fVar10 * local_58 * fVar7;
              }
              in_fpscr = uVar1 | (uint)(local_60 < 0.0) << 0x1f;
              uVar20 = 2;
              *(undefined4 *)(iVar14 + 0x78) = 2;
              if (!SUB41(in_fpscr >> 0x1f,0)) {
                uVar20 = 1;
              }
              *(undefined4 *)(iVar14 + 0x7c) = uVar20;
              fVar10 = (float)ScoreAdd(this,0,0);
              cRDamageGuage::Take(fVar10,bVar6);
              uVar20 = gRMathRand2();
              VectorSignedToFloat(uVar20,(byte)(in_fpscr >> 0x16) & 3);
              cRSound::Play(*(int *)(iVar23 + iVar18));
            }
          }
        }
        iVar14 = *(int *)(iVar14 + 0x74);
      } while (iVar14 != 0);
      iVar19 = *(int *)(this + 0x400);
    }
    fVar5 = DAT_00078a4c;
    fVar8 = DAT_00078a48;
    fVar10 = DAT_00078a44;
    fVar7 = DAT_00078a40;
    fVar9 = DAT_00078a3c;
    fVar4 = DAT_00078a38;
    fVar12 = DAT_00078a34;
    iVar18 = 0;
    pcVar15 = (char *)(iVar23 + DAT_00078a58);
    iVar14 = iVar19;
    do {
      iVar22 = iVar18 * 0xe0;
      iVar21 = iVar14 + iVar22;
      if (*(int *)(iVar21 + 0x341c) == 1 || *(int *)(iVar21 + 0x341c) == 4) {
        local_58 = *(float *)(iVar21 + 0x340c) - *(float *)(this + 0x27e8);
        local_60 = *(float *)(iVar21 + 0x3404) - *(float *)(this + 0x27e0);
        local_5c = *(float *)(iVar21 + 0x3408) - *(float *)(this + 0x27e4);
        in_fpscr = in_fpscr & 0xfffffff | (uint)(local_58 < fVar12) << 0x1f;
        iVar19 = iVar14;
        if (SUB41(in_fpscr >> 0x1f,0)) {
          fVar11 = (float)tVector::Normalize((tVector *)&local_60);
          in_fpscr = in_fpscr & 0xfffffff | (uint)(fVar11 < fVar4) << 0x1f;
          if (SUB41(in_fpscr >> 0x1f,0)) {
            if ((*(uint *)(this + 0x324) & 0x80) == 0) {
              if (this[0x2c0] == (cRSubGoldy)0x0) {
                PfmVibrate();
                fVar24 = *(float *)(*(int *)(this + 0x400) + 0x54);
                this[0x374] = (cRSubGoldy)0x0;
                this[0x2c0] = (cRSubGoldy)0x1;
                *(float *)(this + 0x408) = fVar24 * fVar5;
                *(float *)(this + 0x410) = fVar24 * fVar10;
                *(float *)(this + 0x40c) = fVar24 * fVar8;
                FallingInit(this);
                *(undefined4 *)(this + 0x3f9c) = 10;
                cGLVertexArray::WorldFlatten();
                wprintf(pcVar15,*(undefined4 *)
                                 (*(int *)(gGroup + (int)*(float *)(*(int *)(this + 0x400) + 0xfb28)
                                                    * 0xdc + *(int *)(this + 0x400) + 0xa1908) +
                                 0x10));
                iVar19 = *(int *)(this + 0x400);
                *(undefined1 *)(iVar19 + iVar22 + 0x3475) = 1;
                uVar20 = gRMathRand2();
                VectorSignedToFloat(uVar20,(byte)(in_fpscr >> 0x16) & 3);
                cRSlug::VoicePlay(iVar19 + iVar22 + 0x33a8);
                fVar11 = fVar11 * DAT_00078a6c;
                *(float *)(this + 0x3c24) = fVar5;
                local_64 = *(float *)(this + 0x27e8) + fVar11 * local_58;
                local_6c = *(float *)(this + 0x27e0) + fVar11 * local_60;
                local_68 = *(float *)(this + 0x27e4) + fVar11 * local_5c;
                cRFireWork::Shoot(this + 0x1b8,local_6c,local_68,local_64,
                                  *(undefined4 *)(this + 0x370),0x4e,0x50);
                iVar19 = *(int *)(this + 0x400);
                iVar14 = *(int *)(this + 0x400);
              }
              else {
                *(float *)(this + 0x410) =
                     *(float *)(*(int *)(this + 0x400) + 0x54) *
                     *(float *)(*(int *)(this + 0x400) + 0x54) * fVar9 * fVar7;
                cRDamageGuage::Take(extraout_s0_01,bVar6);
                iVar19 = *(int *)(this + 0x400);
                iVar14 = *(int *)(this + 0x400);
              }
              goto LAB_00078938;
            }
            cRSlug::Kill((cRSlug *)(*(int *)(this + 0x400) + iVar22 + 0x33a8));
          }
          iVar19 = *(int *)(this + 0x400);
          iVar14 = iVar19;
        }
      }
LAB_00078938:
      iVar21 = DAT_00078a64;
      iVar22 = DAT_00078a60;
      fVar24 = DAT_00078a54;
      fVar11 = DAT_00078a50;
      iVar18 = iVar18 + 1;
    } while (iVar18 != 0x10);
    iVar13 = 0;
    pcVar15 = (char *)(iVar23 + DAT_00078a5c);
    do {
      iVar16 = iVar14 + iVar13 * 0x80;
      iVar18 = iVar19;
      iVar19 = iVar14;
      if (*(int *)(gGroup0 + iVar16 + 0xad0f4) == 1) {
        local_70 = *(float *)(gGroup0 + iVar16 + 0xad0e0) - *(float *)(this + 0x27e8);
        pfVar17 = (float *)(iVar14 + (iVar13 + 0x63ef) * 0x80);
        local_78 = *pfVar17 - *(float *)(this + 0x27e0);
        local_74 = pfVar17[1] - *(float *)(this + 0x27e4);
        iVar18 = iVar14;
        if (local_70 < fVar11) {
          fVar12 = (float)tVector::Normalize((tVector *)&local_78);
          if (fVar12 < fVar24) {
            ScoreAdd(this,3,0);
            cRVoiceManager::Play(*(int *)(iVar23 + iVar22),10,1);
            cRSound::Play(*(int *)(iVar23 + iVar21));
            iVar18 = *(int *)(this + 0x400);
            *(undefined4 *)(gGroup0 + iVar18 + iVar13 * 0x80 + 0xad0f4) = 4;
            iVar14 = *(int *)(this + 0x3fec);
            *(int *)(this + 0x3fec) = iVar14 + 1;
            iVar19 = iVar18;
            if (*(int *)(iVar18 + 0x60) != 0) goto LAB_0007896c;
            sprintf((char *)(*(int *)(iVar18 + 0x8c64) + 0x2c4),pcVar15,iVar14 + 1,
                    *(undefined4 *)(iVar18 + 0x163c));
          }
          iVar18 = *(int *)(this + 0x400);
          iVar19 = iVar18;
        }
      }
LAB_0007896c:
      iVar13 = iVar13 + 1;
      iVar14 = iVar19;
    } while (iVar13 != 0x32);
  }
  fVar7 = DAT_0007833c;
  fVar9 = DAT_00078338;
  fVar4 = DAT_00078334;
  fVar12 = DAT_00078330;
  iVar14 = DAT_0007832c;
  iVar22 = 0;
  do {
    fVar10 = DAT_00078318;
    iVar21 = 0;
    do {
      while (iVar13 = iVar21 * 0x68 + iVar19, *(int *)(iVar13 + 0x3094) != 1) {
LAB_00077fc0:
        iVar21 = iVar21 + 1;
        if (iVar21 == 8) goto LAB_0007808c;
      }
      local_84 = *(float *)(iVar13 + 0x3078) - *(float *)(this + 0x27e0);
      local_80 = *(float *)(iVar13 + 0x307c) - *(float *)(this + 0x27e4);
      local_7c = *(float *)(iVar13 + 0x3080) - *(float *)(this + 0x27e8);
      iVar18 = iVar19;
      if ((fVar4 <= *(float *)(this + 0x60)) && (local_7c < fVar9)) {
        if (0.0 <= local_80) {
          bVar6 = local_80 < fVar12;
        }
        else if (local_80 <= fVar10) {
          bVar6 = false;
        }
        else {
          bVar6 = true;
        }
        if (bVar6) {
          fVar8 = (float)tVector::Normalize((tVector *)&local_84);
          if (fVar7 <= fVar8) {
            iVar18 = *(int *)(this + 0x400);
            iVar19 = iVar18;
            goto LAB_00077fc0;
          }
          cRSound::Play(*(int *)(iVar23 + iVar14));
          iVar18 = *(int *)(this + 0x400);
          *(undefined4 *)(iVar18 + iVar21 * 0x68 + 0x3094) = 2;
          fVar8 = (float)HealthCollect(this,(cRSubHealth *)(iVar18 + iVar21 * 0x68 + 0x3068));
          cRDamageGuage::Take(fVar8,(bool)(cVar3 + -0x4c));
          ScoreAdd(this,6,0);
          iVar18 = *(int *)(this + 0x400);
        }
      }
      iVar21 = iVar21 + 1;
      iVar19 = iVar18;
    } while (iVar21 != 8);
LAB_0007808c:
    iVar22 = iVar22 + 1;
  } while (iVar22 != 8);
  if (*(int *)(iVar19 + 0x2ebc) == 1) {
    local_84 = *(float *)(iVar19 + 0x2ea4) - *(float *)(this + 0x27e0);
    local_80 = *(float *)(iVar19 + 0x2ea8) - *(float *)(this + 0x27e4);
    local_7c = *(float *)(iVar19 + 0x2eac) - *(float *)(this + 0x27e8);
    iVar18 = iVar19;
    if ((DAT_00078334 <= *(float *)(this + 0x60)) && (local_7c < DAT_00078338)) {
      if (local_80 < 0.0) {
        bVar6 = DAT_00078a74 < local_80;
      }
      else if (DAT_00078330 <= local_80) {
        bVar6 = false;
      }
      else {
        bVar6 = true;
      }
      if (bVar6) {
        fVar12 = (float)tVector::Normalize((tVector *)&local_84);
        if (fVar12 < DAT_0007833c) {
          *(undefined4 *)(*(int *)(this + 0x400) + 0x2ebc) = 2;
          SpeedUpCollect();
          iVar18 = *(int *)(this + 0x400);
          *(float *)(this + 0x410) = *(float *)(iVar18 + 0x54) * DAT_00078e88;
          iVar19 = iVar18;
        }
        else {
          iVar18 = *(int *)(this + 0x400);
          iVar19 = iVar18;
        }
      }
    }
  }
  if (*(int *)(iVar19 + 0x2f1c) == 1) {
    local_84 = *(float *)(iVar19 + 0x2f00) - *(float *)(this + 0x27e0);
    local_80 = *(float *)(iVar19 + 0x2f04) - *(float *)(this + 0x27e4);
    local_7c = *(float *)(iVar19 + 0x2f08) - *(float *)(this + 0x27e8);
    iVar18 = iVar19;
    if ((DAT_00078334 <= *(float *)(this + 0x60)) && (local_7c < DAT_00078338)) {
      fVar12 = (float)tVector::Normalize((tVector *)&local_84);
      if (fVar12 < DAT_00078a70) {
        *(undefined4 *)(*(int *)(this + 0x400) + 0x2f1c) = 2;
        cRSubHover::On((cRSubHover *)(this + 0x25cc));
        iVar18 = *(int *)(this + 0x400);
      }
      else {
        iVar18 = *(int *)(this + 0x400);
      }
    }
  }
  fVar9 = DAT_0007833c;
  fVar4 = DAT_00078338;
  iVar14 = DAT_0007832c;
  iVar19 = DAT_00078328;
  uVar20 = DAT_00078320;
  fVar12 = DAT_0007831c;
  iVar21 = 0;
  iVar22 = 0;
  if (*(int *)(iVar18 + 0x8968) == 1) goto LAB_00078130;
  do {
    while( true ) {
      do {
        do {
          iVar21 = iVar21 + 1;
          if (iVar21 == 2) {
            return;
          }
          iVar22 = iVar21 * 0x1ac;
          iVar18 = *(int *)(this + 0x400) + iVar22;
        } while (*(int *)(iVar18 + 0x8968) != 1);
LAB_00078130:
        local_88 = *(float *)(iVar18 + 0x8958) - *(float *)(this + 0x27e8);
        local_90 = *(float *)(iVar18 + 0x8950) - *(float *)(this + 0x27e0);
        local_8c = *(float *)(iVar18 + 0x8954) - *(float *)(this + 0x27e4);
      } while ((fVar4 <= local_88) ||
              (fVar7 = (float)tVector::Normalize((tVector *)&local_90), fVar9 <= fVar7));
      iVar18 = *(int *)(this + 0x400);
      cVar2 = this[0x438];
      *(undefined4 *)(iVar18 + iVar22 + 0x8968) = 2;
      if (cVar2 == (cRSubGoldy)0x0) {
        iVar22 = *(int *)(iVar18 + iVar22 + 0x8970);
        if (iVar22 == 3 || iVar22 == 7) {
          *(undefined4 *)(this + 0x410) = uVar20;
          cRSound::Play(*(int *)(iVar23 + iVar14));
          iVar18 = *(int *)(this + 0x400);
        }
        else {
          *(float *)(this + 0x410) = *(float *)(iVar18 + 0x54) * fVar12;
        }
      }
      iVar22 = *(int *)(iVar21 * 0x1ac + iVar18 + 0x8970);
      if (1 < iVar22 - 4U) break;
      if (*(int *)(this + 0x3fc) < 8) {
        if (((*(uint *)(iVar18 + 0x6c) & 0x10) != 0) && (*(int *)(iVar18 + 0x60) != 3)) {
          *(int *)(this + 0x3fc) = *(int *)(this + 0x3fc) + 1;
        }
        cRVoiceManager::Play(*(int *)(iVar23 + iVar19),5,1);
      }
LAB_00078e0c:
      iVar18 = *(int *)(this + 0x2f0);
      if (iVar18 < 8) {
        *(int *)(this + 0x2f0) = iVar18 + 1;
      }
      else if (iVar18 == 8) {
        *(undefined4 *)(this + 0x2f0) = 7;
      }
      cRSound::Play(*(int *)(iVar23 + iVar14));
      ScoreAdd(this,2,0);
    }
    if (iVar22 == 8) goto LAB_00078e0c;
    if (iVar22 == 1) {
      ScoreAdd(this,2,0);
      cRSound::Play(*(int *)(iVar23 + iVar14));
    }
    else if (iVar22 == 2 || iVar22 == 6) {
      ScoreAdd(this,2,0);
      cRSound::Play(*(int *)(iVar23 + iVar14));
      *(undefined4 *)(this + 0x364) = *(undefined4 *)(this + 0x368);
      cRNuke::Init((cRNuke *)(this + 0x138));
    }
  } while( true );
}
