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
  bool bVar4;
  float fVar5;
  int iVar6;
  float *pfVar7;
  int iVar8;
  int iVar9;
  undefined4 uVar10;
  int iVar11;
  int iVar12;
  uint in_fpscr;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float fVar13;
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

  cVar3 = (char)this;
  if (this[0x415] == (cRSubGoldy)0x1) {
    iVar8 = *(int *)(this + 0x400);
    iVar9 = iVar8;
  }
  else if (this[0x414] == (cRSubGoldy)0x1) {
    iVar8 = *(int *)(this + 0x400);
    iVar9 = iVar8;
  }
  else if (this[0x2c0] == (cRSubGoldy)0x1) {
    iVar8 = *(int *)(this + 0x400);
    iVar9 = iVar8;
  }
  else {
    if ((*(uint *)(this + 0x324) & 0x80) == 0) {
      iVar9 = *(int *)(this + 0x400);
      iVar8 = 0;
      do {
        iVar12 = iVar8 * 0x8c + iVar9;
        if (*(int *)(iVar12 + 0x4eec) == 1) {
          if (*(char *)(iVar12 + 0x4f00) != '\0') {
            local_4c = *(float *)(iVar12 + 0x4edc) - *(float *)(this + 0x27e8);
            local_54 = *(float *)(iVar12 + 0x4ed4) - *(float *)(this + 0x27e0);
            local_50 = *(float *)(iVar12 + 0x4ed8) - *(float *)(this + 0x27e4);
            in_fpscr = in_fpscr & 0xfffffff | (uint)(local_4c < 1.0) << 0x1f;
            if (SUB41(in_fpscr >> 0x1f,0)) {
              fVar5 = (float)tVector::Normalize((tVector *)&local_54);
              uVar1 = in_fpscr & 0xfffffff;
              in_fpscr = uVar1 | (uint)(fVar5 < 0.98) << 0x1f;
              if (SUB41(in_fpscr >> 0x1f,0)) {
                in_fpscr = uVar1 | (uint)(*(float *)(this + 0x1bc) == 0.0) << 0x1e;
                if (SUB41(in_fpscr >> 0x1e,0)) {
                  *(undefined4 *)(this + 0x1bc) = *(undefined4 *)(this + 0x1c0);
                }
                *(undefined1 *)(iVar8 * 0x8c + *(int *)(this + 0x400) + 0x4f00) = 0;
                cRDamageGuage::Take(extraout_s0,(bool)(cVar3 + -0x4c));
              }
              iVar9 = *(int *)(this + 0x400);
            }
          }
        }
        iVar8 = iVar8 + 1;
      } while (iVar8 != 0x28);
    }
    else {
      iVar9 = *(int *)(this + 0x400);
    }
    bVar4 = (bool)(cVar3 + -0x4c);
    iVar8 = 0;
    do {
      while( true ) {
        iVar12 = iVar9 + iVar8 * 0xa4;
        if (*(int *)(iVar12 + 0x421c) == 1) break;
LAB_00078654:
        iVar8 = iVar8 + 1;
        if (iVar8 == 0x14) goto LAB_00078704;
      }
      local_58 = *(float *)(iVar12 + 0x420c) - *(float *)(this + 0x27e8);
      local_60 = *(float *)(iVar12 + 0x4204) - *(float *)(this + 0x27e0);
      local_5c = *(float *)(iVar12 + 0x4208) - *(float *)(this + 0x27e4);
      in_fpscr = in_fpscr & 0xfffffff | (uint)(local_58 < 1.0) << 0x1f;
      if (!SUB41(in_fpscr >> 0x1f,0)) goto LAB_00078654;
      fVar5 = (float)tVector::Normalize((tVector *)&local_60);
      in_fpscr = in_fpscr & 0xfffffff | (uint)(fVar5 < 0.49) << 0x1f;
      if (SUB41(in_fpscr >> 0x1f,0)) {
        *(undefined4 *)(*(int *)(this + 0x400) + iVar8 * 0xa4 + 0x421c) = 2;
        cRDamageGuage::Take(extraout_s0_00,bVar4);
        iVar9 = *(int *)(this + 0x400);
      }
      else {
        iVar9 = *(int *)(this + 0x400);
      }
      iVar8 = iVar8 + 1;
    } while (iVar8 != 0x14);
LAB_00078704:
    iVar8 = *(int *)(iVar9 + 0x6500);
    if (iVar8 != 0) {
      do {
        if (*(int *)(iVar8 + 0x78) == 1) {
          local_58 = *(float *)(iVar8 + 100) - *(float *)(this + 0x27e8);
          local_60 = *(float *)(iVar8 + 0x5c) - *(float *)(this + 0x27e0);
          local_5c = *(float *)(iVar8 + 0x60) - *(float *)(this + 0x27e4);
          in_fpscr = in_fpscr & 0xfffffff | (uint)(local_58 < 1.0) << 0x1f;
          if (SUB41(in_fpscr >> 0x1f,0)) {
            fVar5 = (float)tVector::Normalize((tVector *)&local_60);
            uVar1 = in_fpscr & 0xfffffff;
            in_fpscr = uVar1 | (uint)(fVar5 < 0.98) << 0x1f;
            if (SUB41(in_fpscr >> 0x1f,0)) {
              if ((*(uint *)(this + 0x324) & 0x80) == 0) {
                fVar5 = *(float *)(this + 0x410);
                *(float *)(this + 0x408) = *(float *)(this + 0x408) + local_60 * fVar5 * -0.18;
                *(float *)(this + 0x410) = fVar5 + fVar5 * local_58 * -0.1;
              }
              in_fpscr = uVar1 | (uint)(local_60 < 0.0) << 0x1f;
              uVar10 = 2;
              *(undefined4 *)(iVar8 + 0x78) = 2;
              if (!SUB41(in_fpscr >> 0x1f,0)) {
                uVar10 = 1;
              }
              *(undefined4 *)(iVar8 + 0x7c) = uVar10;
              fVar5 = (float)ScoreAdd(this,0,0);
              cRDamageGuage::Take(fVar5,bVar4);
              uVar10 = gRMathRand2();
              VectorSignedToFloat(uVar10,(byte)(in_fpscr >> 0x16) & 3);
              cRSound::Play((int)&gRSound);
            }
          }
        }
        iVar8 = *(int *)(iVar8 + 0x74);
      } while (iVar8 != 0);
      iVar9 = *(int *)(this + 0x400);
    }
    iVar8 = 0;
    iVar12 = iVar9;
    do {
      iVar11 = iVar8 * 0xe0;
      iVar6 = iVar12 + iVar11;
      if (*(int *)(iVar6 + 0x341c) == 1 || *(int *)(iVar6 + 0x341c) == 4) {
        local_58 = *(float *)(iVar6 + 0x340c) - *(float *)(this + 0x27e8);
        local_60 = *(float *)(iVar6 + 0x3404) - *(float *)(this + 0x27e0);
        local_5c = *(float *)(iVar6 + 0x3408) - *(float *)(this + 0x27e4);
        in_fpscr = in_fpscr & 0xfffffff | (uint)(local_58 < 2.0) << 0x1f;
        iVar9 = iVar12;
        if (SUB41(in_fpscr >> 0x1f,0)) {
          fVar5 = (float)tVector::Normalize((tVector *)&local_60);
          in_fpscr = in_fpscr & 0xfffffff | (uint)(fVar5 < 1.5675001) << 0x1f;
          if (SUB41(in_fpscr >> 0x1f,0)) {
            if ((*(uint *)(this + 0x324) & 0x80) == 0) {
              if (this[0x2c0] == (cRSubGoldy)0x0) {
                PfmVibrate();
                fVar13 = *(float *)(*(int *)(this + 0x400) + 0x54);
                this[0x374] = (cRSubGoldy)0x0;
                this[0x2c0] = (cRSubGoldy)0x1;
                *(float *)(this + 0x408) = fVar13 * 0.0;
                *(float *)(this + 0x410) = fVar13 * -0.2;
                *(float *)(this + 0x40c) = fVar13 * 0.2;
                FallingInit(this);
                *(undefined4 *)(this + 0x3f9c) = 10;
                cGLVertexArray::WorldFlatten();
                wprintf("**Slugged Segment = %s\n",
                        *(undefined4 *)
                         (*(int *)(gGroup + (int)*(float *)(*(int *)(this + 0x400) + 0xfb28) * 0xdc
                                            + *(int *)(this + 0x400) + 0xa1908) + 0x10));
                iVar9 = *(int *)(this + 0x400);
                *(undefined1 *)(iVar9 + iVar11 + 0x3475) = 1;
                uVar10 = gRMathRand2();
                VectorSignedToFloat(uVar10,(byte)(in_fpscr >> 0x16) & 3);
                cRSlug::VoicePlay(iVar9 + iVar11 + 0x33a8);
                fVar5 = fVar5 * 0.5;
                *(undefined4 *)(this + 0x3c24) = 0;
                local_64 = *(float *)(this + 0x27e8) + fVar5 * local_58;
                local_6c = *(float *)(this + 0x27e0) + fVar5 * local_60;
                local_68 = *(float *)(this + 0x27e4) + fVar5 * local_5c;
                cRFireWork::Shoot(this + 0x1b8,local_6c,local_68,local_64,
                                  *(undefined4 *)(this + 0x370),0x4e,0x50);
                iVar9 = *(int *)(this + 0x400);
                iVar12 = *(int *)(this + 0x400);
              }
              else {
                *(float *)(this + 0x410) =
                     *(float *)(*(int *)(this + 0x400) + 0x54) *
                     *(float *)(*(int *)(this + 0x400) + 0x54) * -0.004 * 8.0;
                cRDamageGuage::Take(extraout_s0_01,bVar4);
                iVar9 = *(int *)(this + 0x400);
                iVar12 = *(int *)(this + 0x400);
              }
              goto LAB_00078938;
            }
            cRSlug::Kill((cRSlug *)(*(int *)(this + 0x400) + iVar11 + 0x33a8));
          }
          iVar9 = *(int *)(this + 0x400);
          iVar12 = iVar9;
        }
      }
LAB_00078938:
      iVar8 = iVar8 + 1;
    } while (iVar8 != 0x10);
    iVar11 = 0;
    do {
      iVar6 = iVar12 + iVar11 * 0x80;
      iVar8 = iVar9;
      iVar9 = iVar12;
      if (*(int *)(gGroup0 + iVar6 + 0xad0f4) == 1) {
        local_70 = *(float *)(gGroup0 + iVar6 + 0xad0e0) - *(float *)(this + 0x27e8);
        pfVar7 = (float *)(iVar12 + (iVar11 + 0x63ef) * 0x80);
        local_78 = *pfVar7 - *(float *)(this + 0x27e0);
        local_74 = pfVar7[1] - *(float *)(this + 0x27e4);
        iVar8 = iVar12;
        if (local_70 < 1.0) {
          fVar5 = (float)tVector::Normalize((tVector *)&local_78);
          if (fVar5 < 1.73) {
            ScoreAdd(this,3,0);
            cRVoiceManager::Play((int)&gVoiceManager,10,1);
            cRSound::Play((int)&gRSound);
            iVar8 = *(int *)(this + 0x400);
            *(undefined4 *)(gGroup0 + iVar8 + iVar11 * 0x80 + 0xad0f4) = 4;
            iVar12 = *(int *)(this + 0x3fec);
            *(int *)(this + 0x3fec) = iVar12 + 1;
            iVar9 = iVar8;
            if (*(int *)(iVar8 + 0x60) != 0) goto LAB_0007896c;
            sprintf((char *)(*(int *)(iVar8 + 0x8c64) + 0x2c4),"%i/%i",iVar12 + 1,
                    *(undefined4 *)(iVar8 + 0x163c));
          }
          iVar8 = *(int *)(this + 0x400);
          iVar9 = iVar8;
        }
      }
LAB_0007896c:
      iVar11 = iVar11 + 1;
      iVar12 = iVar9;
    } while (iVar11 != 0x32);
  }
  iVar12 = 0;
  do {
    iVar11 = 0;
    do {
      while (iVar6 = iVar11 * 0x68 + iVar9, *(int *)(iVar6 + 0x3094) != 1) {
LAB_00077fc0:
        iVar11 = iVar11 + 1;
        if (iVar11 == 8) goto LAB_0007808c;
      }
      local_84 = *(float *)(iVar6 + 0x3078) - *(float *)(this + 0x27e0);
      local_80 = *(float *)(iVar6 + 0x307c) - *(float *)(this + 0x27e4);
      local_7c = *(float *)(iVar6 + 0x3080) - *(float *)(this + 0x27e8);
      iVar8 = iVar9;
      if ((0.49 <= *(float *)(this + 0x60)) && (local_7c < 1.0)) {
        if (0.0 <= local_80) {
          bVar4 = local_80 < 0.4;
        }
        else if (local_80 <= -0.4) {
          bVar4 = false;
        }
        else {
          bVar4 = true;
        }
        if (bVar4) {
          fVar5 = (float)tVector::Normalize((tVector *)&local_84);
          if (0.98 <= fVar5) {
            iVar8 = *(int *)(this + 0x400);
            iVar9 = iVar8;
            goto LAB_00077fc0;
          }
          cRSound::Play((int)&gRSound);
          iVar8 = *(int *)(this + 0x400);
          *(undefined4 *)(iVar8 + iVar11 * 0x68 + 0x3094) = 2;
          fVar5 = (float)HealthCollect(this,(cRSubHealth *)(iVar8 + iVar11 * 0x68 + 0x3068));
          cRDamageGuage::Take(fVar5,(bool)(cVar3 + -0x4c));
          ScoreAdd(this,6,0);
          iVar8 = *(int *)(this + 0x400);
        }
      }
      iVar11 = iVar11 + 1;
      iVar9 = iVar8;
    } while (iVar11 != 8);
LAB_0007808c:
    iVar12 = iVar12 + 1;
  } while (iVar12 != 8);
  if (*(int *)(iVar9 + 0x2ebc) == 1) {
    local_84 = *(float *)(iVar9 + 0x2ea4) - *(float *)(this + 0x27e0);
    local_80 = *(float *)(iVar9 + 0x2ea8) - *(float *)(this + 0x27e4);
    local_7c = *(float *)(iVar9 + 0x2eac) - *(float *)(this + 0x27e8);
    iVar8 = iVar9;
    if ((0.49 <= *(float *)(this + 0x60)) && (local_7c < 1.0)) {
      if (local_80 < 0.0) {
        bVar4 = -0.4 < local_80;
      }
      else if (0.4 <= local_80) {
        bVar4 = false;
      }
      else {
        bVar4 = true;
      }
      if (bVar4) {
        fVar5 = (float)tVector::Normalize((tVector *)&local_84);
        if (fVar5 < 0.98) {
          *(undefined4 *)(*(int *)(this + 0x400) + 0x2ebc) = 2;
          SpeedUpCollect();
          iVar8 = *(int *)(this + 0x400);
          *(float *)(this + 0x410) = *(float *)(iVar8 + 0x54) * 0.5;
          iVar9 = iVar8;
        }
        else {
          iVar8 = *(int *)(this + 0x400);
          iVar9 = iVar8;
        }
      }
    }
  }
  if (*(int *)(iVar9 + 0x2f1c) == 1) {
    local_84 = *(float *)(iVar9 + 0x2f00) - *(float *)(this + 0x27e0);
    local_80 = *(float *)(iVar9 + 0x2f04) - *(float *)(this + 0x27e4);
    local_7c = *(float *)(iVar9 + 0x2f08) - *(float *)(this + 0x27e8);
    iVar8 = iVar9;
    if ((0.49 <= *(float *)(this + 0x60)) && (local_7c < 1.0)) {
      fVar5 = (float)tVector::Normalize((tVector *)&local_84);
      if (fVar5 < 3.0) {
        *(undefined4 *)(*(int *)(this + 0x400) + 0x2f1c) = 2;
        cRSubHover::On((cRSubHover *)(this + 0x25cc));
        iVar8 = *(int *)(this + 0x400);
      }
      else {
        iVar8 = *(int *)(this + 0x400);
      }
    }
  }
  iVar12 = 0;
  iVar9 = 0;
  if (*(int *)(iVar8 + 0x8968) == 1) goto LAB_00078130;
  do {
    while( true ) {
      do {
        do {
          iVar12 = iVar12 + 1;
          if (iVar12 == 2) {
            return;
          }
          iVar9 = iVar12 * 0x1ac;
          iVar8 = *(int *)(this + 0x400) + iVar9;
        } while (*(int *)(iVar8 + 0x8968) != 1);
LAB_00078130:
        local_88 = *(float *)(iVar8 + 0x8958) - *(float *)(this + 0x27e8);
        local_90 = *(float *)(iVar8 + 0x8950) - *(float *)(this + 0x27e0);
        local_8c = *(float *)(iVar8 + 0x8954) - *(float *)(this + 0x27e4);
      } while ((1.0 <= local_88) ||
              (fVar5 = (float)tVector::Normalize((tVector *)&local_90), 0.98 <= fVar5));
      iVar8 = *(int *)(this + 0x400);
      cVar2 = this[0x438];
      *(undefined4 *)(iVar8 + iVar9 + 0x8968) = 2;
      if (cVar2 == (cRSubGoldy)0x0) {
        iVar9 = *(int *)(iVar8 + iVar9 + 0x8970);
        if (iVar9 == 3 || iVar9 == 7) {
          *(undefined4 *)(this + 0x410) = 0xbdcccccd;
          cRSound::Play((int)&gRSound);
          iVar8 = *(int *)(this + 0x400);
        }
        else {
          *(float *)(this + 0x410) = *(float *)(iVar8 + 0x54) * 0.5;
        }
      }
      iVar9 = *(int *)(iVar12 * 0x1ac + iVar8 + 0x8970);
      if (1 < iVar9 - 4U) break;
      if (*(int *)(this + 0x3fc) < 8) {
        if (((*(uint *)(iVar8 + 0x6c) & 0x10) != 0) && (*(int *)(iVar8 + 0x60) != 3)) {
          *(int *)(this + 0x3fc) = *(int *)(this + 0x3fc) + 1;
        }
        cRVoiceManager::Play((int)&gVoiceManager,5,1);
      }
LAB_00078e0c:
      iVar8 = *(int *)(this + 0x2f0);
      if (iVar8 < 8) {
        *(int *)(this + 0x2f0) = iVar8 + 1;
      }
      else if (iVar8 == 8) {
        *(undefined4 *)(this + 0x2f0) = 7;
      }
      cRSound::Play((int)&gRSound);
      ScoreAdd(this,2,0);
    }
    if (iVar9 == 8) goto LAB_00078e0c;
    if (iVar9 == 1) {
      ScoreAdd(this,2,0);
      cRSound::Play((int)&gRSound);
    }
    else if (iVar9 == 2 || iVar9 == 6) {
      ScoreAdd(this,2,0);
      cRSound::Play((int)&gRSound);
      *(undefined4 *)(this + 0x364) = *(undefined4 *)(this + 0x368);
      cRNuke::Init((cRNuke *)(this + 0x138));
    }
  } while( true );
}
