/*
 * mangled: _ZN10cRSubGoldy9CollisionEv
 * demangled: cRSubGoldy::Collision()
 * address: 0002613c
 * size: 5576
 */

/* cRSubGoldy::Collision() */

void __thiscall cRSubGoldy::Collision(cRSubGoldy *this)

{
  cRSubGoldy *pcVar1;
  uint uVar2;
  uint uVar3;
  cRSubGoldy cVar4;
  byte bVar5;
  undefined *puVar6;
  undefined *puVar7;
  undefined4 uVar8;
  float fVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  cRSubGoldy *pcVar15;
  cRSound *this_00;
  int iVar16;
  bool bVar17;
  uint in_fpscr;
  float fVar18;
  float fVar19;
  float fVar20;
  undefined4 local_80;
  undefined4 uStack_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
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
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;

  if (this[0x40d] == (cRSubGoldy)0x0) {
    cVar4 = this[0x40c];
    bVar17 = cVar4 == (cRSubGoldy)0x0;
    if (bVar17) {
      cVar4 = this[0x2c0];
    }
    if (bVar17 && cVar4 == (cRSubGoldy)0x0) {
      if ((*(uint *)(this + 0x324) & 0x80) == 0) {
        iVar16 = *(int *)(this + 0x3f8);
        iVar14 = 0;
        iVar12 = iVar16;
        do {
          iVar13 = iVar14 * 0x8c + iVar12;
          if ((*(int *)(&DAT_00004874 + iVar13) == 1) && ((&DAT_00004888)[iVar13] != '\0')) {
            local_34 = *(float *)(&DAT_0000485c + iVar13) - *(float *)(this + 0x27d8);
            local_30 = *(float *)(&DAT_00004860 + iVar13) - *(float *)(this + 0x27dc);
            local_2c = *(float *)(&DAT_00004864 + iVar13) - *(float *)(this + 0x27e0);
            in_fpscr = in_fpscr & 0xfffffff | (uint)(local_2c < 1.0) << 0x1f;
            iVar16 = iVar12;
            if (SUB41(in_fpscr >> 0x1f,0)) {
              fVar9 = (float)tVector::Normalize((tVector *)&local_34);
              uVar2 = in_fpscr & 0xfffffff;
              in_fpscr = uVar2 | (uint)(fVar9 < 0.98) << 0x1f;
              if (SUB41(in_fpscr >> 0x1f,0)) {
                in_fpscr = uVar2 | (uint)(*(float *)(this + 0x1bc) == 0.0) << 0x1e;
                if (SUB41(in_fpscr >> 0x1e,0)) {
                  *(undefined4 *)(this + 0x1bc) = *(undefined4 *)(this + 0x1c0);
                }
                (&DAT_00004888)[iVar14 * 0x8c + *(int *)(this + 0x3f8)] = 0;
                cRDamageGuage::Take((cRDamageGuage *)(this + 0x3b4),0.15,false);
                iVar16 = *(int *)(this + 0x3f8);
                iVar12 = iVar16;
              }
              else {
                iVar16 = *(int *)(this + 0x3f8);
                iVar12 = *(int *)(this + 0x3f8);
              }
            }
          }
          iVar14 = iVar14 + 1;
        } while (iVar14 != 0x28);
      }
      else {
        iVar16 = *(int *)(this + 0x3f8);
        iVar12 = iVar16;
      }
      iVar14 = 0;
      while( true ) {
        iVar10 = iVar14 * 0xa4 + iVar12;
        iVar13 = iVar16;
        iVar16 = iVar12;
        if (*(int *)(iVar10 + 0x3ba4) == 1) {
          local_40 = *(float *)(iVar10 + 0x3b8c) - *(float *)(this + 0x27d8);
          local_3c = *(float *)(iVar10 + 0x3b90) - *(float *)(this + 0x27dc);
          local_38 = *(float *)(iVar10 + 0x3b94) - *(float *)(this + 0x27e0);
          in_fpscr = in_fpscr & 0xfffffff | (uint)(local_38 < 1.0) << 0x1f;
          iVar13 = iVar12;
          if (SUB41(in_fpscr >> 0x1f,0)) {
            fVar9 = (float)tVector::Normalize((tVector *)&local_40);
            in_fpscr = in_fpscr & 0xfffffff | (uint)(fVar9 < 0.49) << 0x1f;
            if (SUB41(in_fpscr >> 0x1f,0)) {
              *(undefined4 *)(iVar14 * 0xa4 + *(int *)(this + 0x3f8) + 0x3ba4) = 2;
              cRDamageGuage::Take((cRDamageGuage *)(this + 0x3b4),0.02,false);
              iVar13 = *(int *)(this + 0x3f8);
              iVar16 = *(int *)(this + 0x3f8);
            }
            else {
              iVar13 = *(int *)(this + 0x3f8);
              iVar16 = *(int *)(this + 0x3f8);
            }
          }
        }
        if (iVar14 == 0x13) break;
        iVar14 = iVar14 + 1;
        iVar12 = iVar16;
      }
      iVar14 = *(int *)(iVar16 + 0x5e88);
      if (iVar14 != 0) {
        do {
          if (*(int *)(iVar14 + 0x78) == 1) {
            local_40 = *(float *)(iVar14 + 0x5c) - *(float *)(this + 0x27d8);
            local_3c = *(float *)(iVar14 + 0x60) - *(float *)(this + 0x27dc);
            local_38 = *(float *)(iVar14 + 100) - *(float *)(this + 0x27e0);
            in_fpscr = in_fpscr & 0xfffffff | (uint)(local_38 < 1.0) << 0x1f;
            if (SUB41(in_fpscr >> 0x1f,0)) {
              fVar9 = (float)tVector::Normalize((tVector *)&local_40);
              uVar2 = in_fpscr & 0xfffffff;
              in_fpscr = uVar2 | (uint)(fVar9 < 0.98) << 0x1f;
              if (SUB41(in_fpscr >> 0x1f,0)) {
                if ((*(uint *)(this + 0x324) & 0x80) == 0) {
                  fVar9 = *(float *)(this + 0x408);
                  *(float *)(this + 0x400) = *(float *)(this + 0x400) + local_40 * fVar9 * -0.18;
                  *(float *)(this + 0x408) = fVar9 + fVar9 * local_38 * -0.1;
                }
                uVar8 = 2;
                *(undefined4 *)(iVar14 + 0x78) = 2;
                in_fpscr = uVar2 | (uint)(local_40 < 0.0) << 0x1f;
                if (!SUB41(in_fpscr >> 0x1f,0)) {
                  uVar8 = 1;
                }
                *(undefined4 *)(iVar14 + 0x7c) = uVar8;
                *(int *)(this + 0x2f8) = *(int *)(this + 0x2f8) + 10;
                iVar12 = *(int *)(this + 0x2cc);
                iVar16 = iVar12 + 10;
                *(int *)(this + 0x2cc) = iVar16;
                if ((iVar12 / 50000 != iVar16 / 50000) && (*(int *)(this + 0x3fec) < 9)) {
                  *(int *)(this + 0x3fec) = *(int *)(this + 0x3fec) + 1;
                  if ((*(int *)(*(int *)PTR__Game_001b60b8 + 0x72bd0) == 0) &&
                     (*(int *)(*(int *)PTR__Game_001b60b8 + 0x24) == 0)) {
                    cRSound::Play((cRSound *)PTR__gRSound_001b61e0,0x2d);
                  }
                }
                cRDamageGuage::Take((cRDamageGuage *)(this + 0x3b4),0.04,false);
                uVar8 = gRMathRand2();
                fVar9 = (float)VectorSignedToFloat(uVar8,(byte)(in_fpscr >> 0x16) & 3);
                cRSound::Play((cRSound *)PTR__gRSound_001b61e0,
                              (int)(fVar9 * 3.0517578e-05 + fVar9 * 3.0517578e-05) + 0x27);
              }
            }
          }
          iVar14 = *(int *)(iVar14 + 0x74);
        } while (iVar14 != 0);
        iVar13 = *(int *)(this + 0x3f8);
        iVar16 = iVar13;
      }
      iVar14 = 0;
      do {
        iVar12 = iVar14 * 0xe0;
        iVar11 = iVar12 + iVar16;
        iVar10 = iVar13;
        iVar13 = iVar16;
        if (*(int *)(iVar11 + 0x2da4) == 4 || *(int *)(iVar11 + 0x2da4) == 1) {
          local_40 = *(float *)((int)&DAT_00002d8c + iVar11) - *(float *)(this + 0x27d8);
          local_3c = *(float *)(tColour::tColour + iVar11) - *(float *)(this + 0x27dc);
          local_38 = *(float *)(tColourSmall::tColourSmall + iVar11) - *(float *)(this + 0x27e0);
          in_fpscr = in_fpscr & 0xfffffff | (uint)(local_38 < 2.0) << 0x1f;
          iVar10 = iVar16;
          if (SUB41(in_fpscr >> 0x1f,0)) {
            fVar9 = (float)tVector::Normalize((tVector *)&local_40);
            in_fpscr = in_fpscr & 0xfffffff | (uint)(fVar9 < 1.5675001) << 0x1f;
            if (SUB41(in_fpscr >> 0x1f,0)) {
              if ((*(uint *)(this + 0x324) & 0x80) == 0) {
                if (this[0x2c0] == (cRSubGoldy)0x0) {
                  MacVibrate();
                  this[0x374] = (cRSubGoldy)0x0;
                  this[0x2c0] = (cRSubGoldy)0x1;
                  fVar18 = *(float *)(*(int *)(this + 0x3f8) + 0x4c);
                  fVar19 = 0.0;
                  this[0x43c] = (cRSubGoldy)0x0;
                  this[0x43d] = (cRSubGoldy)0x0;
                  this[0x40d] = (cRSubGoldy)0x1;
                  *(float *)(this + 0x408) = fVar18 * -0.2;
                  *(float *)(this + 0x404) = fVar18 * 0.2;
                  *(float *)(this + 0x400) = fVar18 * 0.0;
                  *(undefined4 *)(this + 0x420) = 0;
                  *(undefined4 *)(this + 0x41c) = 0;
                  *(undefined4 *)(this + 0x414) = *(undefined4 *)(this + 100);
                  *(undefined4 *)(this + 0x424) = 0;
                  *(undefined4 *)(this + 0x3f94) = 10;
                  cGLVertexArray::WorldFlatten
                            (*(cGLVertexArray **)(*(int *)(*(int *)(this + 0x3f8) + 0xf39c) + 0x10c)
                            );
                  wprintf("**Slugged Segment = %s\n",
                          *(undefined4 *)
                           (*(int *)((int)&objc::method_list_t::OFSendChallengeHeaderController.
                                           method18 +
                                    (int)*(float *)(*(int *)(this + 0x3f8) + 0xf4ac) * 0xdc +
                                    *(int *)(this + 0x3f8) + 8) + 0x10));
                  *(undefined1 *)(iVar12 + *(int *)(this + 0x3f8) + 0x2dfd) = 1;
                  iVar16 = *(int *)(this + 0x3f8);
                  uVar8 = gRMathRand2();
                  puVar6 = PTR__Game_001b60b8;
                  iVar12 = iVar12 + iVar16;
                  if ((*(char *)(iVar12 + 0x2dfc) == '\0') &&
                     (iVar16 = *(int *)PTR__Game_001b60b8, *(char *)(iVar16 + 0x7b14c) == '\0')) {
                    fVar18 = (float)VectorSignedToFloat(uVar8,(byte)(in_fpscr >> 0x16) & 3);
                    *(undefined4 *)(iVar16 + 0x7b150) = *(undefined4 *)((int)&DAT_0007b154 + iVar16)
                    ;
                    *(undefined1 *)(*(int *)puVar6 + 0x7b14c) = 1;
                    *(float *)(iVar12 + 0x2e00) = fVar19;
                    *(undefined1 *)(iVar12 + 0x2dfc) = 1;
                    RShellVoicePlay((int)(fVar18 * 3.0517578e-05 + fVar18 * 3.0517578e-05) + 0x22,
                                    1.0,-1.0,fVar19);
                  }
                  fVar9 = fVar9 * 0.5;
                  *(undefined4 *)(this + 0x3c1c) = 0;
                  local_4c = *(float *)(this + 0x27d8) + fVar9 * local_40;
                  local_48 = *(float *)(this + 0x27dc) + fVar9 * local_3c;
                  local_44 = *(float *)(this + 0x27e0) + fVar9 * local_38;
                  cRFireWork::Shoot(this + 0x1b8,local_4c,local_48,local_44,
                                    *(undefined4 *)(this + 0x370),0x4e,0x50);
                  iVar10 = *(int *)(this + 0x3f8);
                  iVar13 = *(int *)(this + 0x3f8);
                }
                else {
                  *(float *)(this + 0x408) =
                       *(float *)(*(int *)(this + 0x3f8) + 0x4c) *
                       *(float *)(*(int *)(this + 0x3f8) + 0x4c) * -0.004 * 8.0;
                  cRDamageGuage::Take((cRDamageGuage *)(this + 0x3b4),1.0,false);
                  iVar10 = *(int *)(this + 0x3f8);
                  iVar13 = *(int *)(this + 0x3f8);
                }
                goto LAB_00026d8c;
              }
              cRSlug::Kill((cRSlug *)(iVar12 + 0x2d30 + *(int *)(this + 0x3f8)));
            }
            iVar10 = *(int *)(this + 0x3f8);
            iVar13 = iVar10;
          }
        }
LAB_00026d8c:
        iVar14 = iVar14 + 1;
        iVar16 = iVar13;
      } while (iVar14 != 0x10);
      iVar16 = 0;
      do {
        iVar12 = iVar16 * 0x80 + iVar13;
        iVar14 = iVar10;
        iVar10 = iVar13;
        if (*(int *)(&DAT_002f04a8 + iVar12) == 1) {
          local_58 = *(float *)(&DAT_002f048c + iVar12) - *(float *)(this + 0x27d8);
          local_54 = *(float *)(&DAT_002f0490 + iVar12) - *(float *)(this + 0x27dc);
          local_50 = *(float *)(&DAT_002f0494 + iVar12) - *(float *)(this + 0x27e0);
          in_fpscr = in_fpscr & 0xfffffff | (uint)(local_50 < 1.0) << 0x1f;
          iVar14 = iVar13;
          if (SUB41(in_fpscr >> 0x1f,0)) {
            fVar9 = (float)tVector::Normalize((tVector *)&local_58);
            in_fpscr = in_fpscr & 0xfffffff | (uint)(fVar9 < 1.73) << 0x1f;
            if (SUB41(in_fpscr >> 0x1f,0)) {
              *(int *)(this + 0x304) = *(int *)(this + 0x304) + 100;
              iVar12 = *(int *)(this + 0x2cc);
              iVar14 = iVar12 + 100;
              *(int *)(this + 0x2cc) = iVar14;
              if ((iVar12 / 50000 != iVar14 / 50000) && (*(int *)(this + 0x3fec) < 9)) {
                *(int *)(this + 0x3fec) = *(int *)(this + 0x3fec) + 1;
                if ((*(int *)(*(int *)PTR__Game_001b60b8 + 0x72bd0) == 0) &&
                   (*(int *)(*(int *)PTR__Game_001b60b8 + 0x24) == 0)) {
                  cRSound::Play((cRSound *)PTR__gRSound_001b61e0,0x2d);
                }
              }
              cRVoiceManager::Play((cRVoiceManager *)PTR__gVoiceManager_001b61d8,10,1,-1);
              cRSound::Play((cRSound *)PTR__gRSound_001b61e0,0x1b);
              *(undefined4 *)(&DAT_002f04a8 + iVar16 * 0x80 + *(int *)(this + 0x3f8)) = 4;
              iVar12 = *(int *)(this + 0x3fe4);
              iVar14 = *(int *)(this + 0x3f8);
              *(int *)(this + 0x3fe4) = iVar12 + 1;
              iVar10 = iVar14;
              if (*(int *)(iVar14 + 0x58) == 0) {
                _sprintf((char *)(*(int *)(iVar14 + 0x85ec) + 0x2c4),"%i/%i",iVar12 + 1,
                         *(undefined4 *)(section_000012e4.segname + iVar14 + 8));
                iVar14 = *(int *)(this + 0x3f8);
                iVar10 = *(int *)(this + 0x3f8);
              }
            }
            else {
              iVar14 = *(int *)(this + 0x3f8);
              iVar10 = *(int *)(this + 0x3f8);
            }
          }
        }
        iVar16 = iVar16 + 1;
        iVar13 = iVar10;
      } while (iVar16 != 0x32);
      goto LAB_00026420;
    }
  }
  iVar14 = *(int *)(this + 0x3f8);
  iVar10 = iVar14;
LAB_00026420:
  iVar16 = 0;
LAB_00026424:
  iVar12 = 0;
  do {
    iVar11 = iVar12 * 0x68 + iVar10;
    iVar13 = iVar14;
    iVar14 = iVar10;
    if (*(int *)(&DAT_00002a1c + iVar11) == 1) {
      local_64 = *(float *)(&DAT_00002a00 + iVar11) - *(float *)(this + 0x27d8);
      local_60 = *(float *)(&DAT_00002a04 + iVar11) - *(float *)(this + 0x27dc);
      local_5c = *(float *)(&DAT_00002a08 + iVar11) - *(float *)(this + 0x27e0);
      uVar2 = in_fpscr & 0xfffffff;
      uVar3 = uVar2 | (uint)(*(float *)(this + 0x60) < 0.49) << 0x1f;
      in_fpscr = uVar3 | (uint)NAN(*(float *)(this + 0x60)) << 0x1c;
      iVar13 = iVar10;
      if (((byte)(uVar3 >> 0x1f) == ((byte)(in_fpscr >> 0x1c) & 1)) &&
         (in_fpscr = uVar2 | (uint)(local_5c < 1.0) << 0x1f, SUB41(in_fpscr >> 0x1f,0))) {
        if (local_60 < 0.0) {
          uVar2 = uVar2 | (uint)(local_60 < -0.4) << 0x1f | (uint)(local_60 == -0.4) << 0x1e;
          in_fpscr = uVar2 | (uint)NAN(local_60) << 0x1c;
          bVar5 = (byte)(uVar2 >> 0x18);
          bVar17 = !(bool)(bVar5 >> 6 & 1) && bVar5 >> 7 == ((byte)(in_fpscr >> 0x1c) & 1);
        }
        else {
          in_fpscr = uVar2 | (uint)(local_60 < 0.4) << 0x1f;
          if (SUB41(in_fpscr >> 0x1f,0)) {
            bVar17 = true;
          }
          else {
            bVar17 = false;
          }
        }
        if (bVar17) {
          fVar9 = (float)tVector::Normalize((tVector *)&local_64);
          puVar6 = PTR__gRSound_001b61e0;
          in_fpscr = in_fpscr & 0xfffffff | (uint)(fVar9 < 0.98) << 0x1f;
          if (SUB41(in_fpscr >> 0x1f,0)) {
            cRSound::Play((cRSound *)PTR__gRSound_001b61e0,0xe);
            *(undefined4 *)(&DAT_00002a1c + iVar12 * 0x68 + *(int *)(this + 0x3f8)) = 2;
            HealthCollect(this,(cRSubHealth *)
                               (&DAT_000029f0 + *(int *)(this + 0x3f8) + iVar12 * 0x68));
            cRDamageGuage::Take((cRDamageGuage *)(this + 0x3b4),-0.5,false);
            *(int *)(this + 0x310) = *(int *)(this + 0x310) + 0xfa;
            iVar13 = *(int *)(this + 0x2cc);
            iVar14 = iVar13 + 0xfa;
            *(int *)(this + 0x2cc) = iVar14;
            if (iVar13 / 50000 != iVar14 / 50000) {
              if (*(int *)(this + 0x3fec) < 9) {
                *(int *)(this + 0x3fec) = *(int *)(this + 0x3fec) + 1;
                if ((*(int *)(*(int *)PTR__Game_001b60b8 + 0x72bd0) == 0) &&
                   (*(int *)(*(int *)PTR__Game_001b60b8 + 0x24) == 0)) {
                  cRSound::Play((cRSound *)puVar6,0x2d);
                }
              }
              iVar13 = *(int *)(this + 0x3f8);
              iVar14 = *(int *)(this + 0x3f8);
              goto joined_r0x00026434;
            }
          }
          iVar13 = *(int *)(this + 0x3f8);
          iVar14 = *(int *)(this + 0x3f8);
        }
      }
    }
joined_r0x00026434:
    iVar10 = iVar14;
    if (iVar12 == 7) break;
    iVar12 = iVar12 + 1;
  } while( true );
  iVar16 = iVar16 + 1;
  if (iVar16 == 8) goto LAB_000265a4;
  goto LAB_00026424;
LAB_000265a4:
  iVar16 = iVar14 + 0x2000;
  if (*(int *)(&DAT_00002844 + iVar14) == 1) {
    local_64 = *(float *)(&DAT_0000282c + iVar14) - *(float *)(this + 0x27d8);
    local_60 = *(float *)(&DAT_00002830 + iVar14) - *(float *)(this + 0x27dc);
    local_5c = *(float *)(&DAT_00002834 + iVar14) - *(float *)(this + 0x27e0);
    uVar2 = in_fpscr & 0xfffffff;
    uVar3 = uVar2 | (uint)(*(float *)(this + 0x60) < 0.49) << 0x1f;
    in_fpscr = uVar3 | (uint)NAN(*(float *)(this + 0x60)) << 0x1c;
    iVar13 = iVar14;
    if (((byte)(uVar3 >> 0x1f) == ((byte)(in_fpscr >> 0x1c) & 1)) &&
       (in_fpscr = uVar2 | (uint)(local_5c < 1.0) << 0x1f, SUB41(in_fpscr >> 0x1f,0))) {
      if (local_60 < 0.0) {
        uVar2 = uVar2 | (uint)(local_60 < -0.4) << 0x1f | (uint)(local_60 == -0.4) << 0x1e;
        in_fpscr = uVar2 | (uint)NAN(local_60) << 0x1c;
        bVar5 = (byte)(uVar2 >> 0x18);
        bVar17 = !(bool)(bVar5 >> 6 & 1) && bVar5 >> 7 == ((byte)(in_fpscr >> 0x1c) & 1);
      }
      else {
        in_fpscr = uVar2 | (uint)(local_60 < 0.4) << 0x1f;
        if (SUB41(in_fpscr >> 0x1f,0)) {
          bVar17 = true;
        }
        else {
          bVar17 = false;
        }
      }
      if (bVar17) {
        fVar9 = (float)tVector::Normalize((tVector *)&local_64);
        in_fpscr = in_fpscr & 0xfffffff | (uint)(fVar9 < 0.98) << 0x1f;
        if (!SUB41(in_fpscr >> 0x1f,0)) {
          iVar13 = *(int *)(this + 0x3f8);
          iVar16 = iVar13 + 0x2000;
          iVar14 = iVar13;
          goto LAB_000265b4;
        }
        *(undefined4 *)(&DAT_00002844 + *(int *)(this + 0x3f8)) = 2;
        iVar13 = *(int *)(this + 0x3f8);
        *(float *)(this + 0x408) = *(float *)(iVar13 + 0x4c) * 0.5;
      }
    }
    iVar16 = iVar13 + 0x2000;
    iVar14 = iVar13;
  }
LAB_000265b4:
  if (*(int *)(iVar16 + 0x8a4) == 1) {
    local_64 = *(float *)(iVar16 + 0x888) - *(float *)(this + 0x27d8);
    local_60 = *(float *)(iVar16 + 0x88c) - *(float *)(this + 0x27dc);
    local_5c = *(float *)(iVar16 + 0x890) - *(float *)(this + 0x27e0);
    uVar2 = in_fpscr & 0xfffffff;
    uVar3 = uVar2 | (uint)(*(float *)(this + 0x60) < 0.49) << 0x1f;
    in_fpscr = uVar3 | (uint)NAN(*(float *)(this + 0x60)) << 0x1c;
    iVar13 = iVar14;
    if (((byte)(uVar3 >> 0x1f) == ((byte)(in_fpscr >> 0x1c) & 1)) &&
       (in_fpscr = uVar2 | (uint)(local_5c < 1.0) << 0x1f, SUB41(in_fpscr >> 0x1f,0))) {
      fVar9 = (float)tVector::Normalize((tVector *)&local_64);
      in_fpscr = in_fpscr & 0xfffffff | (uint)(fVar9 < 3.0) << 0x1f;
      if ((SUB41(in_fpscr >> 0x1f,0)) &&
         (*(undefined4 *)(&DAT_000028a4 + *(int *)(this + 0x3f8)) = 2, *(int *)(this + 0x25d0) == 0)
         ) {
        *(undefined4 *)(this + 0x25c4) = 0;
        *(undefined4 *)(this + 0x25d0) = 1;
        *(undefined4 *)(this + 0x25e0) = 0;
        *(undefined4 *)(this + 0x25dc) = 0;
        *(undefined4 *)(this + 0x25d8) = 0;
        pcVar15 = this + 0x25e8;
        cRSnail::SetJetPack((cRSnail *)(*(int *)PTR__Game_001b60b8 + 0x847b8),1);
        iVar16 = 0;
        do {
          iVar14 = cRSpriteManager::New((int)PTR__gRSpriteManager_001b61e4,1,0x89,-1);
          *(int *)(pcVar15 + -4) = iVar14;
          *(uint *)(iVar14 + 4) = *(uint *)(iVar14 + 4) | 0x800;
          *(undefined4 *)(*(int *)(pcVar15 + -4) + 0x68) = 0;
          *(undefined4 *)(*(int *)(pcVar15 + -4) + 0x6c) = 0;
          *(undefined4 *)(*(int *)(pcVar15 + -4) + 0x70) = 0;
          *(undefined4 *)(*(int *)(pcVar15 + -4) + 0x74) = 0;
          iVar14 = *(int *)(pcVar15 + -4);
          *(undefined4 *)(iVar14 + 100) = 0;
          *(undefined4 *)(iVar14 + 0x60) = 0;
          iVar14 = *(int *)(pcVar15 + -4);
          *(undefined4 *)(iVar14 + 0x5c) = 0;
          *(undefined4 *)(iVar14 + 0x58) = 0;
          *(undefined4 *)(iVar14 + 0x54) = 0;
          *(undefined4 *)(*(int *)(pcVar15 + -4) + 0x78) = 0;
          iVar14 = *(int *)(pcVar15 + -4);
          tColour::tColour((tColour *)&local_80,1.0,1.0,1.0,0.999);
          *(undefined4 *)(iVar14 + 0x2c) = local_80;
          *(undefined4 *)(iVar14 + 0x30) = uStack_7c;
          *(undefined4 *)(iVar14 + 0x34) = uStack_78;
          *(undefined4 *)(iVar14 + 0x38) = uStack_74;
          *(undefined4 *)(*(int *)(pcVar15 + -4) + 0x28) = 1;
          *(undefined4 *)(pcVar15 + 8) = 0x3e2aaaab;
          *(undefined4 *)pcVar15 = 0;
          *(undefined4 *)(pcVar15 + 4) = 0;
          iVar14 = cRSpriteManager::New((int)PTR__gRSpriteManager_001b61e4,1,0x89,-1);
          *(int *)(pcVar15 + 0xc) = iVar14;
          *(uint *)(iVar14 + 4) = *(uint *)(iVar14 + 4) | 0x800;
          *(undefined4 *)(*(int *)(pcVar15 + 0xc) + 0x68) = 0;
          *(undefined4 *)(*(int *)(pcVar15 + 0xc) + 0x6c) = 0;
          *(undefined4 *)(*(int *)(pcVar15 + 0xc) + 0x70) = 0;
          *(undefined4 *)(*(int *)(pcVar15 + 0xc) + 0x74) = 0;
          iVar14 = *(int *)(pcVar15 + 0xc);
          *(undefined4 *)(iVar14 + 100) = 0;
          *(undefined4 *)(iVar14 + 0x60) = 0;
          iVar14 = *(int *)(pcVar15 + 0xc);
          *(undefined4 *)(iVar14 + 0x5c) = 0;
          *(undefined4 *)(iVar14 + 0x58) = 0;
          *(undefined4 *)(iVar14 + 0x54) = 0;
          *(undefined4 *)(*(int *)(pcVar15 + 0xc) + 0x78) = 0;
          iVar14 = *(int *)(pcVar15 + 0xc);
          tColour::tColour((tColour *)&local_80,1.0,1.0,1.0,0.999);
          *(undefined4 *)(iVar14 + 0x2c) = local_80;
          *(undefined4 *)(iVar14 + 0x30) = uStack_7c;
          *(undefined4 *)(iVar14 + 0x34) = uStack_78;
          *(undefined4 *)(iVar14 + 0x38) = uStack_74;
          iVar16 = iVar16 + 1;
          *(undefined4 *)(*(int *)(pcVar15 + 0xc) + 0x28) = 1;
          *(undefined4 *)(pcVar15 + 0x10) = 0;
          *(undefined4 *)(pcVar15 + 0x14) = 0;
          *(undefined4 *)(pcVar15 + 0x18) = 0x3e2aaaab;
          pcVar15 = pcVar15 + 0x20;
        } while (iVar16 != 0xf);
        iVar13 = *(int *)(this + 0x3f8);
      }
      else {
        iVar13 = *(int *)(this + 0x3f8);
      }
    }
  }
  iVar14 = 0;
  iVar16 = 0;
  if (*(int *)(iVar13 + 0x82f0) == 1) goto LAB_0002660c;
LAB_000265e0:
  do {
    while( true ) {
      do {
        do {
          do {
            iVar14 = iVar14 + 1;
            if (iVar14 == 2) {
              return;
            }
            iVar16 = iVar14 * 0x1ac;
            iVar13 = iVar16 + *(int *)(this + 0x3f8);
          } while (*(int *)(iVar13 + 0x82f0) != 1);
LAB_0002660c:
          local_70 = *(float *)(iVar13 + 0x82d8) - *(float *)(this + 0x27d8);
          local_6c = *(float *)(iVar13 + 0x82dc) - *(float *)(this + 0x27dc);
          local_68 = *(float *)(iVar13 + 0x82e0) - *(float *)(this + 0x27e0);
          in_fpscr = in_fpscr & 0xfffffff | (uint)(local_68 < 1.0) << 0x1f;
        } while (!SUB41(in_fpscr >> 0x1f,0));
        fVar9 = (float)tVector::Normalize((tVector *)&local_70);
        in_fpscr = in_fpscr & 0xfffffff | (uint)(fVar9 < 0.98) << 0x1f;
      } while (!SUB41(in_fpscr >> 0x1f,0));
      *(undefined4 *)(iVar16 + *(int *)(this + 0x3f8) + 0x82f0) = 2;
      puVar6 = PTR__gRSound_001b61e0;
      if (this[0x430] == (cRSubGoldy)0x0) {
        iVar12 = *(int *)(this + 0x3f8);
        iVar16 = *(int *)(iVar16 + iVar12 + 0x82f8);
        if (iVar16 == 7 || iVar16 == 3) {
          *(undefined4 *)(this + 0x408) = 0xbdcccccd;
          cRSound::Play((cRSound *)puVar6,0x2c);
          iVar12 = *(int *)(this + 0x3f8);
        }
        else {
          *(float *)(this + 0x408) = *(float *)(iVar12 + 0x4c) * 0.5;
        }
      }
      else {
        iVar12 = *(int *)(this + 0x3f8);
      }
      iVar16 = *(int *)(iVar14 * 0x1ac + iVar12 + 0x82f8);
      if (iVar16 - 4U < 2) goto LAB_000274b0;
      if (iVar16 == 8) break;
      if (iVar16 == 1) {
        *(int *)(this + 0x300) = *(int *)(this + 0x300) + 100;
        iVar12 = *(int *)(this + 0x2cc);
        iVar16 = iVar12 + 100;
        *(int *)(this + 0x2cc) = iVar16;
        if ((iVar12 / 50000 != iVar16 / 50000) && (*(int *)(this + 0x3fec) < 9)) {
          *(int *)(this + 0x3fec) = *(int *)(this + 0x3fec) + 1;
          if ((*(int *)(*(int *)PTR__Game_001b60b8 + 0x72bd0) == 0) &&
             (*(int *)(*(int *)PTR__Game_001b60b8 + 0x24) == 0)) {
            cRSound::Play((cRSound *)PTR__gRSound_001b61e0,0x2d);
          }
        }
        cRSound::Play((cRSound *)PTR__gRSound_001b61e0,1);
      }
      else if (iVar16 == 6 || iVar16 == 2) {
        *(int *)(this + 0x300) = *(int *)(this + 0x300) + 100;
        iVar12 = *(int *)(this + 0x2cc);
        iVar16 = iVar12 + 100;
        *(int *)(this + 0x2cc) = iVar16;
        if ((iVar12 / 50000 != iVar16 / 50000) && (*(int *)(this + 0x3fec) < 9)) {
          *(int *)(this + 0x3fec) = *(int *)(this + 0x3fec) + 1;
          if ((*(int *)(*(int *)PTR__Game_001b60b8 + 0x72bd0) == 0) &&
             (*(int *)(*(int *)PTR__Game_001b60b8 + 0x24) == 0)) {
            cRSound::Play((cRSound *)PTR__gRSound_001b61e0,0x2d);
          }
        }
        cRSound::Play((cRSound *)PTR__gRSound_001b61e0,0x2b);
        *(undefined4 *)(this + 0x364) = *(undefined4 *)(this + 0x368);
        puVar7 = PTR__gRSpriteManager_001b61e4;
        puVar6 = PTR__Game_001b60b8;
        iVar16 = *(int *)(this + 0x138);
        if (iVar16 == 0) {
          iVar16 = *(int *)(this + 0x13c);
          *(float *)(this + 0x144) = *(float *)(iVar16 + 100) - 5.0;
          fVar9 = *(float *)(*(int *)puVar6 + 0x72bc4);
          *(undefined4 *)(this + 0x148) = 0;
          *(undefined4 *)(this + 0x14c) = 0x3dd67751;
          *(undefined4 *)(this + 0x138) = 1;
          *(float *)(this + 0x140) = fVar9 + fVar9;
          pcVar15 = this;
          while( true ) {
            iVar16 = cRSpriteManager::New((int)puVar7,*(int *)(iVar16 + 0x370),0x77,-1);
            *(int *)(pcVar15 + 0x150) = iVar16;
            *(uint *)(iVar16 + 4) = *(uint *)(iVar16 + 4) | 0x800;
            *(undefined4 *)(*(int *)(pcVar15 + 0x150) + 0x68) = 0;
            *(undefined4 *)(*(int *)(pcVar15 + 0x150) + 0x6c) = 0;
            *(undefined4 *)(*(int *)(pcVar15 + 0x150) + 0x60) = 0x40400000;
            *(undefined4 *)(*(int *)(pcVar15 + 0x150) + 100) = 0x40400000;
            iVar16 = *(int *)(pcVar15 + 0x150);
            *(undefined4 *)(iVar16 + 0x5c) = 0;
            *(undefined4 *)(iVar16 + 0x58) = 0;
            *(undefined4 *)(iVar16 + 0x54) = 0;
            iVar16 = *(int *)(pcVar15 + 0x150);
            *(undefined4 *)(iVar16 + 0x50) = 0;
            *(undefined4 *)(iVar16 + 0x4c) = 0;
            *(undefined4 *)(iVar16 + 0x48) = 0;
            pcVar1 = pcVar15 + 0x150;
            pcVar15 = pcVar15 + 4;
            *(undefined4 *)(*(int *)pcVar1 + 0x78) = 0;
            if (pcVar15 == this + 100) break;
            iVar16 = *(int *)(this + 0x13c);
          }
          iVar16 = *(int *)(this + 0x138);
        }
        if (iVar16 == 1) {
          iVar16 = 0;
          fVar18 = *(float *)(this + 0x144) + *(float *)(this + 0x140);
          fVar9 = *(float *)(this + 0x148) + *(float *)(this + 0x14c);
          *(float *)(this + 0x144) = fVar18;
          uVar2 = in_fpscr & 0xfffffff | (uint)(fVar9 < 6.2831855) << 0x1f |
                  (uint)(fVar9 == 6.2831855) << 0x1e;
          in_fpscr = uVar2 | (uint)NAN(fVar9) << 0x1c;
          *(float *)(this + 0x148) = fVar9;
          bVar5 = (byte)(uVar2 >> 0x18);
          pcVar15 = this;
          if (!(bool)(bVar5 >> 6 & 1) && bVar5 >> 7 == ((byte)(in_fpscr >> 0x1c) & 1)) {
            fVar9 = fVar9 - 6.2831855;
            *(float *)(this + 0x148) = fVar9;
          }
          while( true ) {
            fVar20 = 7.0;
            fVar19 = (float)VectorSignedToFloat(iVar16,(byte)(in_fpscr >> 0x16) & 3);
            *(float *)(*(int *)(pcVar15 + 0x150) + 0x50) = fVar18;
            iVar16 = iVar16 + 1;
            iVar12 = *(int *)(pcVar15 + 0x150);
            fVar9 = fVar9 + (fVar19 / 25.0) * 6.2831855;
            fVar18 = (float)Sin(fVar9);
            *(float *)(iVar12 + 0x48) = fVar18 * fVar20;
            iVar12 = *(int *)(pcVar15 + 0x150);
            fVar9 = (float)Cos(fVar9);
            *(float *)(iVar12 + 0x4c) = fVar9 * fVar20;
            if (iVar16 == 0x19) break;
            fVar18 = *(float *)(this + 0x144);
            fVar9 = *(float *)(this + 0x148);
            pcVar15 = pcVar15 + 4;
          }
        }
      }
    }
    iVar16 = *(int *)(this + 0x2f0);
    if (iVar16 < 8) {
      iVar16 = iVar16 + 1;
      *(int *)(this + 0x2f0) = iVar16;
    }
    else if (iVar16 == 8) {
      iVar16 = 7;
      *(undefined4 *)(this + 0x2f0) = 7;
    }
    this_00 = (cRSound *)PTR__gRSound_001b61e0;
    if (6 < iVar16) {
      iVar16 = 7;
    }
    cRSound::Play((cRSound *)PTR__gRSound_001b61e0,iVar16);
    *(int *)(this + 0x300) = *(int *)(this + 0x300) + 100;
    iVar12 = *(int *)(this + 0x2cc);
    iVar16 = iVar12 + 100;
    *(int *)(this + 0x2cc) = iVar16;
  } while ((iVar12 / 50000 == iVar16 / 50000) || (8 < *(int *)(this + 0x3fec)));
  *(int *)(this + 0x3fec) = *(int *)(this + 0x3fec) + 1;
  goto LAB_0002747c;
LAB_000274b0:
  if (*(int *)(this + 0x3f4) < 8) {
    if (((*(uint *)(iVar12 + 100) & 0x10) != 0) && (*(int *)(iVar12 + 0x58) != 3)) {
      *(int *)(this + 0x3f4) = *(int *)(this + 0x3f4) + 1;
    }
    cRVoiceManager::Play((cRVoiceManager *)PTR__gVoiceManager_001b61d8,5,1,-1);
  }
  iVar16 = *(int *)(this + 0x2f0);
  if (iVar16 < 8) {
    iVar16 = iVar16 + 1;
    *(int *)(this + 0x2f0) = iVar16;
  }
  else if (iVar16 == 8) {
    iVar16 = 7;
    *(undefined4 *)(this + 0x2f0) = 7;
  }
  this_00 = (cRSound *)PTR__gRSound_001b61e0;
  if (6 < iVar16) {
    iVar16 = 7;
  }
  cRSound::Play((cRSound *)PTR__gRSound_001b61e0,iVar16);
  *(int *)(this + 0x300) = *(int *)(this + 0x300) + 100;
  iVar12 = *(int *)(this + 0x2cc);
  iVar16 = iVar12 + 100;
  *(int *)(this + 0x2cc) = iVar16;
  if ((iVar12 / 50000 != iVar16 / 50000) && (*(int *)(this + 0x3fec) < 9)) {
    *(int *)(this + 0x3fec) = *(int *)(this + 0x3fec) + 1;
LAB_0002747c:
    if ((*(int *)(*(int *)PTR__Game_001b60b8 + 0x72bd0) == 0) &&
       (*(int *)(*(int *)PTR__Game_001b60b8 + 0x24) == 0)) {
      cRSound::Play(this_00,0x2d);
    }
  }
  goto LAB_000265e0;
}
