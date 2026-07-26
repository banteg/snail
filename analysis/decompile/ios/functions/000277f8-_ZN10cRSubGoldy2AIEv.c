/*
 * mangled: _ZN10cRSubGoldy2AIEv
 * demangled: cRSubGoldy::AI()
 * address: 000277f8
 * size: 23436
 */

/* WARNING: Type propagation algorithm not settling */
/* cRSubGoldy::AI() */

void __thiscall cRSubGoldy::AI(cRSubGoldy *this)

{
  cRSubGoldy cVar1;
  char cVar2;
  byte bVar3;
  ushort uVar4;
  int iVar5;
  undefined *puVar6;
  short sVar7;
  undefined2 uVar8;
  cRSubGoldy *pcVar9;
  undefined4 uVar10;
  cRSubGoldy *pcVar11;
  undefined1 *puVar12;
  cRSubGoldy *pcVar13;
  cRSubLoc *pcVar14;
  undefined4 uVar15;
  uint uVar16;
  ushort *puVar17;
  undefined4 uVar18;
  int iVar19;
  int iVar20;
  int iVar21;
  int iVar22;
  int iVar23;
  cRSubGame *this_00;
  cRSubGoldy cVar24;
  int *piVar25;
  tVector *ptVar26;
  cRSubGoldy *pcVar27;
  int iVar28;
  int iVar29;
  bool bVar30;
  bool bVar31;
  uint in_fpscr;
  uint uVar32;
  float fVar33;
  float in_s14;
  float fVar34;
  float fVar35;
  uint uVar36;
  float fVar37;
  uint uVar38;
  uint uVar39;
  float fVar40;
  undefined8 uVar41;
  cRSubGoldy *local_100;
  cRSubGoldy *local_f4;
  tVector *local_ec;
  undefined4 local_80;
  undefined4 uStack_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined1 *local_70;
  float fStack_6c;
  float local_68;
  float fStack_60;
  undefined4 local_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined1 *local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;

  puVar6 = PTR__Game_001b60b8;
  if (*(char *)(*(int *)(this + 0x3f8) + 0x12) != '\0') {
    if (*(int *)(*(int *)PTR__Game_001b60b8 + 0x15c) == 9) {
      return;
    }
    cRDamageGuage::AI((cRDamageGuage *)(this + 0x3b4));
    cRProgressBar::AI();
    if (*(char *)(*(int *)puVar6 + 0x72b8a) == '\0') {
      if (*(int *)(this + 0x3e4) == 1) {
        *(undefined4 *)(*(int *)(this + 0x3f0) + 0x1fc) = 0x3f7fbe77;
        fVar33 = *(float *)(this + 1000);
        *(float *)(this + 1000) = fVar33 + *(float *)(this + 0x3ec);
        if (1.0 < fVar33 + *(float *)(this + 0x3ec)) {
          *(undefined4 *)(this + 1000) = 0;
          *(undefined4 *)(this + 0x3e4) = 2;
        }
      }
      else if (*(int *)(this + 0x3e4) == 2) {
        fVar33 = *(float *)(this + 1000);
        if (fVar33 < 0.5) {
          iVar20 = *(int *)(this + 0x3f0);
          in_s14 = fVar33 * -2.0 + 1.0;
        }
        else {
          iVar20 = 0;
          *(undefined4 *)(*(int *)(this + 0x3f0) + 0x1fc) = 0;
        }
        if (fVar33 < 0.5) {
          *(float *)(iVar20 + 0x1fc) = in_s14;
        }
        fVar33 = *(float *)(this + 1000);
        *(float *)(this + 1000) = fVar33 + *(float *)(this + 0x3ec);
        if (1.0 < fVar33 + *(float *)(this + 0x3ec)) {
          *(undefined4 *)(this + 1000) = 0;
          puVar6 = PTR__gRSound_001b61e0;
          *(undefined4 *)(this + 0x3e4) = 1;
          cRSound::Play((cRSound *)puVar6,0x33);
        }
      }
    }
    cRCompletion::AI((cRCompletion *)(*(int *)(this + 0x3f8) + 0x3052b8));
    return;
  }
  cRBackdrop::SetZoom((cRBackdrop *)(*(int *)PTR__Game_001b60b8 + 0x4d2e0),
                      *(float *)(*(int *)PTR__Game_001b60b8 + 0x82024) / 36000.0);
  if (this[0x374] == (cRSubGoldy)0x0) {
    fVar33 = *(float *)(*(int *)(this + 0x281c) + 0xf0);
    *(float *)(*(int *)(this + 0x281c) + 0xf0) = fVar33 + (0.0 - fVar33) * 0.1;
  }
  else {
    iVar20 = *(int *)(this + 0x380) + 3;
    iVar21 = *(int *)(*(int *)(this + 0x378) + 0x38);
    if (iVar21 <= iVar20) {
      iVar20 = iVar21 + -1;
    }
    fVar33 = *(float *)(*(int *)(this + 0x281c) + 0xf0);
    *(float *)(*(int *)(this + 0x281c) + 0xf0) =
         fVar33 + (*(float *)(iVar20 * 0xa8 + *(int *)(*(int *)(this + 0x378) + 0x4c) + 0xa4) * -3.0
                  - fVar33) * 0.1;
  }
  fVar33 = *(float *)(this + 0x3ff4);
  in_fpscr = in_fpscr & 0xfffffff;
  if (fVar33 != 0.0) {
    fVar34 = fVar33 + *(float *)(this + 0x3ff8);
    *(float *)(this + 0x3ff8) = fVar34;
    fVar33 = (fVar33 + fVar34 * -0.15) * 0.82;
    fVar34 = -fVar34;
    *(float *)(this + 0x3ff0) = fVar34;
    *(float *)(this + 0x3ff4) = fVar33;
    if (fVar33 < 0.0) {
      in_fpscr = in_fpscr | (uint)(fVar33 < -0.001) << 0x1f;
      bVar31 = fVar33 != -0.001 && SUB41(in_fpscr >> 0x1f,0) == NAN(fVar33);
    }
    else {
      in_fpscr = in_fpscr | (uint)(fVar33 < 0.001) << 0x1f;
      if (SUB41(in_fpscr >> 0x1f,0)) {
        bVar31 = true;
      }
      else {
        bVar31 = false;
      }
    }
    if (bVar31) {
      if (fVar34 < 0.0) {
        in_fpscr = in_fpscr & 0xfffffff | (uint)(fVar34 < -0.001) << 0x1f;
        bVar31 = fVar34 != -0.001 && SUB41(in_fpscr >> 0x1f,0) == NAN(fVar34);
      }
      else {
        in_fpscr = in_fpscr & 0xfffffff | (uint)(fVar34 < 0.001) << 0x1f;
        if (SUB41(in_fpscr >> 0x1f,0)) {
          bVar31 = true;
        }
        else {
          bVar31 = false;
        }
      }
      if (bVar31) {
        *(undefined4 *)(this + 0x3ff4) = 0;
        *(undefined4 *)(this + 0x3ff0) = 0;
      }
    }
  }
  pcVar9 = this + 0x4000;
  fVar33 = *(float *)pcVar9;
  in_fpscr = in_fpscr & 0xfffffff;
  uVar36 = in_fpscr | (uint)(fVar33 == 0.0) << 0x1e;
  if (!SUB41(uVar36 >> 0x1e,0)) {
    fVar34 = fVar33 + *(float *)(this + 0x4004);
    *(float *)(this + 0x4004) = fVar34;
    fVar33 = (fVar33 + fVar34 * -0.15) * 0.82;
    fVar34 = -fVar34;
    *(float *)(this + 0x3ffc) = fVar34;
    *(float *)pcVar9 = fVar33;
    if (fVar33 < 0.0) {
      uVar16 = in_fpscr | (uint)(fVar33 < -0.001) << 0x1f | (uint)(fVar33 == -0.001) << 0x1e;
      uVar36 = uVar16 | (uint)NAN(fVar33) << 0x1c;
      bVar3 = (byte)(uVar16 >> 0x18);
      bVar31 = !(bool)(bVar3 >> 6 & 1) && bVar3 >> 7 == ((byte)(uVar36 >> 0x1c) & 1);
    }
    else {
      uVar36 = in_fpscr | (uint)(fVar33 < 0.001) << 0x1f;
      if (SUB41(uVar36 >> 0x1f,0)) {
        bVar31 = true;
      }
      else {
        bVar31 = false;
      }
    }
    if (bVar31) {
      if (fVar34 < 0.0) {
        uVar16 = uVar36 & 0xfffffff | (uint)(fVar34 < -0.001) << 0x1f |
                 (uint)(fVar34 == -0.001) << 0x1e;
        uVar36 = uVar16 | (uint)NAN(fVar34) << 0x1c;
        bVar3 = (byte)(uVar16 >> 0x18);
        bVar31 = !(bool)(bVar3 >> 6 & 1) && bVar3 >> 7 == ((byte)(uVar36 >> 0x1c) & 1);
      }
      else {
        uVar36 = uVar36 & 0xfffffff | (uint)(fVar34 < 0.001) << 0x1f;
        if (SUB41(uVar36 >> 0x1f,0)) {
          bVar31 = true;
        }
        else {
          bVar31 = false;
        }
      }
      if (bVar31) {
        *(undefined4 *)pcVar9 = 0;
        *(undefined4 *)(this + 0x3ffc) = 0;
      }
    }
  }
  *(undefined4 *)(*(int *)(this + 0x281c) + 0xf4) = *(undefined4 *)(this + 0x3ff0);
  *(undefined4 *)(*(int *)(this + 0x281c) + 0xf8) = *(undefined4 *)(this + 0x3ffc);
  iVar20 = *(int *)(this + 0x3f8);
  if (*(int *)(iVar20 + 0x58) == 0) {
    if (*(int *)(this + 0x3fec) < 1) {
      cRBorder::HideInit(*(cRBorder **)(iVar20 + 0x85f0));
    }
    else {
      cRBorder::UnHideInit(*(cRBorder **)(iVar20 + 0x85f0));
    }
    if (*(int *)(this + 0x3fec) < 2) {
      cRBorder::HideInit(*(cRBorder **)(*(int *)(this + 0x3f8) + 0x85f4));
    }
    else {
      cRBorder::UnHideInit(*(cRBorder **)(*(int *)(this + 0x3f8) + 0x85f4));
    }
    if (*(int *)(this + 0x3fec) < 3) {
      cRBorder::HideInit(*(cRBorder **)(*(int *)(this + 0x3f8) + 0x85f8));
    }
    else {
      cRBorder::UnHideInit(*(cRBorder **)(*(int *)(this + 0x3f8) + 0x85f8));
    }
    if (*(int *)(this + 0x3fec) < 4) {
      cRBorder::HideInit(*(cRBorder **)(*(int *)(this + 0x3f8) + 0x85fc));
    }
    else {
      cRBorder::UnHideInit(*(cRBorder **)(*(int *)(this + 0x3f8) + 0x85fc));
    }
    if (*(int *)(this + 0x3fec) < 5) {
      cRBorder::HideInit(*(cRBorder **)(*(int *)(this + 0x3f8) + 0x8600));
    }
    else {
      cRBorder::UnHideInit(*(cRBorder **)(*(int *)(this + 0x3f8) + 0x8600));
    }
    if (*(int *)(this + 0x3fec) < 6) {
      cRBorder::HideInit(*(cRBorder **)(*(int *)(this + 0x3f8) + 0x8604));
    }
    else {
      cRBorder::UnHideInit(*(cRBorder **)(*(int *)(this + 0x3f8) + 0x8604));
    }
    if (*(int *)(this + 0x3fec) < 7) {
      cRBorder::HideInit(*(cRBorder **)(*(int *)(this + 0x3f8) + 0x8608));
    }
    else {
      cRBorder::UnHideInit(*(cRBorder **)(*(int *)(this + 0x3f8) + 0x8608));
    }
    if (*(int *)(this + 0x3fec) < 8) {
      cRBorder::HideInit(*(cRBorder **)(*(int *)(this + 0x3f8) + 0x860c));
    }
    else {
      cRBorder::UnHideInit(*(cRBorder **)(*(int *)(this + 0x3f8) + 0x860c));
    }
    if (*(int *)(this + 0x3fec) < 9) {
      cRBorder::HideInit(*(cRBorder **)(*(int *)(this + 0x3f8) + 0x8610));
    }
    else {
      cRBorder::UnHideInit(*(cRBorder **)(*(int *)(this + 0x3f8) + 0x8610));
    }
  }
  if (*(int *)(this + 0x3fc) == 0 || *(int *)(this + 0x3fc) == 2) {
    return;
  }
  uVar16 = *(uint *)(this + 0x3f8);
  if ((0x14 < *(int *)(&DAT_002e09d8 + uVar16)) && (*(char *)(uVar16 + 0x78) == '\0')) {
    *(undefined1 *)(uVar16 + 0x78) = 1;
    uVar16 = *(uint *)(this + 0x3f8);
  }
  puVar6 = PTR__gConfig_001b60d4;
  if ((&DAT_002e09cc)[uVar16] == '\0') {
LAB_00027de0:
    if (this[0x3b0] != (cRSubGoldy)0x0) {
      uVar16 = (uint)(byte)this[0x430];
    }
    if (this[0x3b0] != (cRSubGoldy)0x0 && uVar16 != 0) {
      *(undefined4 *)(this + 0x25b0) = 0x43a00000;
      *(undefined4 *)(this + 0x25b4) = 0x43a00000;
    }
    else if (this[0x2c0] == (cRSubGoldy)0x0) {
      MouseCalcScale(*(float *)(PTR__gConfig_001b60d4 + *(int *)(this + 0x27e4) * 4 + 0x38));
      iVar20 = *(int *)(this + 0x42c);
      fVar33 = *(float *)(iVar20 + 0x2c);
      uVar36 = uVar36 & 0xfffffff;
      uVar16 = uVar36 | (uint)(fVar33 < 30.0) << 0x1f;
      if (fVar33 != 30.0 && SUB41(uVar16 >> 0x1f,0) == NAN(fVar33)) {
        if ((*(int *)(puVar6 + 8) == 1) &&
           ((uVar16 = uVar36, *(float *)(*(int *)PTR__Game_001b60b8 + 0x3c) == 90.0 ||
            (*(float *)(*(int *)PTR__Game_001b60b8 + 0x3c) == 270.0)))) {
          fVar33 = *(float *)(iVar20 + 0x28) - 320.0;
          *(float *)(this + 0x25b0) = fVar33 + fVar33 + 320.0;
        }
        else {
          *(undefined4 *)(this + 0x25b0) = *(undefined4 *)(iVar20 + 0x28);
        }
      }
      fVar33 = *(float *)(this + 0x25b0);
      uVar36 = uVar16 & 0xfffffff | (uint)(fVar33 < 0.0) << 0x1f;
      if (SUB41(uVar36 >> 0x1f,0)) {
        fVar33 = 0.0;
      }
      else {
        uVar16 = uVar16 & 0xfffffff | (uint)(fVar33 < 639.0) << 0x1f |
                 (uint)(fVar33 == 639.0) << 0x1e;
        uVar36 = uVar16 | (uint)NAN(fVar33) << 0x1c;
        bVar3 = (byte)(uVar16 >> 0x18);
        if (!(bool)(bVar3 >> 6 & 1) && bVar3 >> 7 == ((byte)(uVar36 >> 0x1c) & 1)) {
          fVar33 = 639.0;
        }
      }
      *(float *)(this + 0x25b0) = fVar33;
      *(undefined4 *)(this + 0x25b4) = *(undefined4 *)(iVar20 + 0x28);
      if (*(int *)(this + 0x27e4) == 1) {
        cVar24 = this[0x430];
        *(undefined4 *)(this + 0x25b0) = *(undefined4 *)(iVar20 + 0x28);
      }
      else {
        cVar24 = this[0x430];
      }
      uVar16 = (uint)(byte)cVar24;
    }
    else {
      fVar33 = *(float *)(this + 0x25b0) + *(float *)(this + 0x2834) * -2.0;
      uVar16 = uVar36 & 0xfffffff;
      uVar36 = uVar16 | (uint)(fVar33 < 0.0) << 0x1f;
      *(float *)(this + 0x25b0) = fVar33;
      *(float *)(this + 0x25b4) = fVar33;
      if (SUB41(uVar36 >> 0x1f,0)) {
        fVar33 = 0.0;
      }
      else {
        uVar16 = uVar16 | (uint)(fVar33 < 639.0) << 0x1f | (uint)(fVar33 == 639.0) << 0x1e;
        uVar36 = uVar16 | (uint)NAN(fVar33) << 0x1c;
        bVar3 = (byte)(uVar16 >> 0x18);
        if (!(bool)(bVar3 >> 6 & 1) && bVar3 >> 7 == ((byte)(uVar36 >> 0x1c) & 1)) {
          fVar33 = 639.0;
        }
      }
      uVar16 = (uint)(byte)this[0x430];
      *(float *)(this + 0x25b0) = fVar33;
    }
    if (uVar16 == 0) {
      fVar34 = ((320.0 - *(float *)(this + 0x25b0)) * 8.0) / 640.0;
      uVar16 = uVar36 & 0xfffffff;
      uVar36 = uVar16 | (uint)(fVar34 < -3.7) << 0x1f;
      fVar33 = -3.7;
      if (!SUB41(uVar36 >> 0x1f,0)) {
        uVar16 = uVar16 | (uint)(fVar34 < 3.7) << 0x1f | (uint)(fVar34 == 3.7) << 0x1e;
        uVar36 = uVar16 | (uint)NAN(fVar34) << 0x1c;
        bVar3 = (byte)(uVar16 >> 0x18);
        fVar33 = fVar34;
        if (!(bool)(bVar3 >> 6 & 1) && bVar3 >> 7 == ((byte)(uVar36 >> 0x1c) & 1)) {
          fVar33 = 3.7;
        }
      }
      if (*(int *)(this + 0x108) == 2) goto LAB_00029324;
      fVar33 = *(float *)(this + 0x5c) +
               (fVar33 - *(float *)(this + 0x5c)) * *(float *)(*(int *)(this + 0x3f8) + 0x4c) * 0.2;
      *(float *)(this + 0x5c) = fVar33;
    }
    else {
LAB_00029324:
      fVar33 = *(float *)(this + 0x5c);
    }
    sVar7 = MathType32to16(fVar33,16.0);
    fVar33 = (float)MathType16to32(sVar7,16.0);
    *(float *)(this + 0x5c) = fVar33;
    iVar20 = *(int *)(&DAT_002e09d8 + *(int *)(this + 0x3f8));
    iVar21 = *(int *)(&DAT_002e09c8 + *(int *)(this + 0x3f8));
    uVar8 = MathType32to16(fVar33,16.0);
    *(undefined2 *)(iVar20 * 6 + iVar21 + 0x70) = uVar8;
    iVar20 = *(int *)(this + 0x3f8);
    iVar21 = *(int *)(&DAT_002e09d8 + iVar20);
    if (iVar21 == 0) {
      iVar20 = *(int *)(&DAT_002e09c8 + iVar20);
      uVar8 = MathType32to16(*(float *)(this + 100),32.0);
      *(undefined2 *)(iVar20 + 0x72) = uVar8;
      uVar41 = MathType16to32(*(short *)(*(int *)(&DAT_002e09d8 + *(int *)(this + 0x3f8)) * 6 +
                                         *(int *)(&DAT_002e09c8 + *(int *)(this + 0x3f8)) + 0x72),
                              32.0);
      AI()::GoldyZ = (float)uVar41;
    }
    else {
      iVar20 = *(int *)(&DAT_002e09c8 + iVar20);
      uVar8 = MathType32to16(*(float *)(this + 100) - AI()::GoldyZ,32.0);
      *(undefined2 *)(iVar21 * 6 + iVar20 + 0x72) = uVar8;
      uVar41 = MathType16to32(*(short *)(*(int *)(&DAT_002e09d8 + *(int *)(this + 0x3f8)) * 6 +
                                         *(int *)(&DAT_002e09c8 + *(int *)(this + 0x3f8)) + 0x72),
                              32.0);
      AI()::GoldyZ = (float)uVar41 + AI()::GoldyZ;
    }
    local_ec = (tVector *)((ulonglong)uVar41 >> 0x20);
    pcVar11 = (cRSubGoldy *)uVar41;
    iVar20 = *(int *)(this + 0x3f8);
    if (*(char *)(iVar20 + 0x78) == '\0') {
LAB_00029310:
      iVar21 = *(int *)(this + 0x42c);
      if ((*(uint *)(iVar21 + 0xc) & 0x4000) == 0) goto LAB_00027fb8;
    }
    else {
      iVar21 = *(int *)(this + 0x42c);
      if ((*(uint *)(iVar21 + 4) & 0x4000) != 0) {
        pcVar11 = (cRSubGoldy *)
                  (*(int *)(&DAT_002e09d8 + iVar20) * 6 + *(int *)(&DAT_002e09c8 + iVar20));
        *(ushort *)(pcVar11 + 0x74) = *(ushort *)(pcVar11 + 0x74) | 1;
        iVar21 = *(int *)(this + 0x42c);
        iVar20 = *(int *)(this + 0x3f8);
      }
      if ((*(uint *)(iVar21 + 0xc) & 0x4000) != 0) {
        pcVar11 = (cRSubGoldy *)
                  (*(int *)(&DAT_002e09d8 + iVar20) * 6 + *(int *)(&DAT_002e09c8 + iVar20));
        *(ushort *)(pcVar11 + 0x74) = *(ushort *)(pcVar11 + 0x74) | 2;
        iVar20 = *(int *)(this + 0x3f8);
        goto LAB_00029310;
      }
LAB_00027fb8:
      if ((*(uint *)(iVar21 + 4) & 0x4000) == 0) {
        *(undefined1 *)(iVar20 + 0x78) = 1;
        iVar20 = *(int *)(this + 0x3f8);
      }
    }
    uVar16 = 0;
    if (*(char *)(iVar20 + 0x78) != '\0') {
      pcVar11 = (cRSubGoldy *)
                (*(int *)(&DAT_002e09d8 + iVar20) * 6 + *(int *)(&DAT_002e09c8 + iVar20));
      uVar16 = *(ushort *)(pcVar11 + 0x74) | 4;
      *(short *)(pcVar11 + 0x74) = (short)uVar16;
    }
  }
  else {
    piVar25 = (int *)(&DAT_002e09d0 + uVar16);
    uVar16 = *(uint *)(&DAT_002e09d8 + uVar16);
    if ((*(int *)(*piVar25 + 0x6c) <= (int)uVar16) || (*(int *)(this + 0x108) == 2))
    goto LAB_00027de0;
    uVar10 = MathType16to32(*(short *)(uVar16 * 6 + *piVar25 + 0x70),16.0);
    iVar20 = *(int *)(this + 0x3f8);
    *(undefined4 *)(this + 0x5c) = uVar10;
    pcVar11 = *(cRSubGoldy **)(&DAT_002e09d0 + iVar20);
    if ((*(ushort *)(pcVar11 + *(int *)(&DAT_002e09d8 + iVar20) * 6 + 0x74) & 4) == 0) {
      *(byte *)(iVar20 + 0x78) =
           (byte)*(ushort *)(pcVar11 + *(int *)(&DAT_002e09d8 + iVar20) * 6 + 0x74) & 4;
    }
    else {
      *(undefined1 *)(iVar20 + 0x78) = 1;
    }
    puVar6 = PTR__Game_001b60b8;
    local_ec = *(tVector **)(&DAT_002e09d0 + *(int *)(this + 0x3f8));
    uVar16 = (uint)*(ushort *)
                    (local_ec + *(int *)(&DAT_002e09d8 + *(int *)(this + 0x3f8)) * 6 + 0x74);
    if ((*(ushort *)(local_ec + *(int *)(&DAT_002e09d8 + *(int *)(this + 0x3f8)) * 6 + 0x74) & 8) !=
        0) {
      *(undefined4 *)(*(int *)PTR__Game_001b60b8 + 0x15c) = 0x1a;
      *(undefined4 *)(*(int *)puVar6 + 0x160) = 10;
      *(undefined1 *)(*(int *)puVar6 + 0x2c0) = 1;
      cRFade::StartOn((cRFade *)(*(int *)puVar6 + 0x24));
      return;
    }
  }
  fVar33 = *(float *)(this + 0x5c);
  bVar31 = fVar33 < -4.0;
  if (bVar31) {
    *(undefined4 *)(this + 0x5c) = 0xc0800000;
    pcVar11 = this + 0x400;
    uVar16 = 0;
    fVar33 = -4.0;
  }
  else {
    local_ec = (tVector *)(this + 0x400);
  }
  uVar38 = uVar36 & 0xfffffff | (uint)(fVar33 < 4.0) << 0x1f | (uint)(fVar33 == 4.0) << 0x1e;
  uVar32 = uVar38 | (uint)NAN(fVar33) << 0x1c;
  if (bVar31) {
    *(uint *)pcVar11 = uVar16;
    local_ec = (tVector *)pcVar11;
  }
  bVar3 = (byte)(uVar38 >> 0x18);
  if (!(bool)(bVar3 >> 6 & 1) && bVar3 >> 7 == ((byte)(uVar32 >> 0x1c) & 1)) {
    *(undefined1 **)(this + 0x5c) = &DAT_40800000;
    *(undefined4 *)local_ec = 0;
  }
  if (this[0x78] != (cRSubGoldy)0x0) {
    *(undefined4 *)(this + 0x408) = 0;
    puVar6 = PTR__Game_001b60b8;
    if (*(int *)(*(int *)PTR__Game_001b60b8 + 0x24) == 0) {
      fVar33 = *(float *)(this + 0x80) + *(float *)(this + 0x84);
      uVar36 = uVar36 & 0xfffffff | (uint)(fVar33 < 1.0) << 0x1f | (uint)(fVar33 == 1.0) << 0x1e;
      uVar32 = uVar36 | (uint)NAN(fVar33) << 0x1c;
      *(float *)(this + 0x80) = fVar33;
      bVar3 = (byte)(uVar36 >> 0x18);
      if (!(bool)(bVar3 >> 6 & 1) && bVar3 >> 7 == ((byte)(uVar32 >> 0x1c) & 1)) {
        if (*(int *)(*(int *)puVar6 + 0x24) == 0) {
          cRFade::Start((cRFade *)(*(int *)puVar6 + 0x24),(_func_void *)0x0);
          goto LAB_000280c8;
        }
        goto LAB_000280dc;
      }
    }
    else {
LAB_000280c8:
      fVar33 = *(float *)(this + 0x80);
      uVar36 = uVar32 & 0xfffffff | (uint)(fVar33 < 1.0) << 0x1f | (uint)(fVar33 == 1.0) << 0x1e;
      uVar32 = uVar36 | (uint)NAN(fVar33) << 0x1c;
      bVar3 = (byte)(uVar36 >> 0x18);
      if (!(bool)(bVar3 >> 6 & 1) && bVar3 >> 7 == ((byte)(uVar32 >> 0x1c) & 1)) {
LAB_000280dc:
        puVar6 = PTR__Game_001b60b8;
        if (*(int *)(*(int *)PTR__Game_001b60b8 + 0x24) == 4) {
          if (*(int *)(this + 0x74) == 0) {
            if (*(int *)(*(int *)(this + 0x3f8) + 0x58) == 0) {
              *(int *)(this + 0x3fec) = *(int *)(this + 0x3fec) + -1;
            }
            *(undefined4 *)(*(int *)puVar6 + 0x160) = *(undefined4 *)(*(int *)puVar6 + 0x15c);
            *(undefined4 *)(*(int *)puVar6 + 0x15c) = 0x1c;
          }
          else {
            *(undefined4 *)(&DAT_00303aa8 + *(int *)(this + 0x3f8)) = 2;
            cRSubGame::Complete(*(cRSubGame **)(this + 0x3f8),true);
            if ((&DAT_002e09cd)[*(int *)(this + 0x3f8)] == '\0') {
              *(undefined4 *)(*(int *)puVar6 + 0x160) = *(undefined4 *)(*(int *)puVar6 + 0x15c);
              if ((*(int *)(*(int *)(this + 0x3f8) + 0x58) == 0) &&
                 (*(char *)(*(int *)puVar6 + 0x2c1) == '\0')) {
                *(undefined4 *)(*(int *)puVar6 + 0x15c) = 0x1a;
                *(undefined4 *)(*(int *)puVar6 + 0x160) = 2;
              }
              else {
                *(undefined4 *)(*(int *)PTR__Game_001b60b8 + 0x15c) = 0x1b;
              }
            }
            else {
              *(undefined4 *)(*(int *)puVar6 + 0x160) = *(undefined4 *)(*(int *)puVar6 + 0x15c);
              *(undefined4 *)(*(int *)puVar6 + 0x15c) = 0x1a;
            }
          }
        }
      }
    }
  }
  local_f4 = this + 0x408;
  iVar20 = *(int *)(this + 0x3f8);
  ptVar26 = (tVector *)(this + 0x5c);
  puVar12 = *(undefined1 **)ptVar26;
  fStack_60 = *(float *)(this + 0x60);
  uVar36 = (uint)((float)puVar12 + 4.0);
  if (6 < (int)uVar36) {
    uVar36 = 7;
  }
  uVar16 = (uint)*(float *)(this + 100);
  uVar36 = uVar36 & ~((int)uVar36 >> 0x1f);
  if (0xdaa < (int)uVar16) {
    uVar16 = 0xdab;
  }
  uVar16 = uVar16 & ~((int)uVar16 >> 0x1f);
  iVar21 = uVar36 * 0x44 + uVar16 * 0x220;
  pcVar14 = (cRSubLoc *)((int)&PTR_caseD_6_00013458 + iVar20 + iVar21);
  iVar21 = ((int)((int)pcVar14 -
                 ((*(byte *)(iVar21 + iVar20 + 0x1348a) & 7) * 0x44 + 0x85fd0 +
                 *(int *)PTR__Game_001b60b8)) >> 2) * -0xf0f0f0f;
  if (iVar21 < 0) {
    iVar21 = iVar21 + 7;
  }
  iVar21 = iVar21 >> 3;
  iVar22 = iVar21 * 0xdc + 0x898 + iVar20;
  iVar23 = *(int *)(iVar22 + 0x1e42b0);
  if ((((0 < iVar23) && (iVar23 != *(int *)(this + 0x1d0))) &&
      (iVar23 < *(int *)(iVar20 + 0x98) + 1)) &&
     (*(int *)(this + 0x1d0) = iVar23,
     *(int *)(*(int *)(iVar22 + 0x1e42b0) * 0x2c + iVar20 + 0x90) != 0)) {
    *(undefined4 *)(this + 0x1d4) = 2;
    uVar10 = *(undefined4 *)(*(int *)(iVar22 + 0x1e42b0) * 0x2c + iVar20 + 0x90);
    *(undefined4 *)(this + 0x1d8) = 0;
    *(undefined4 *)(this + 0x1e4) = uVar10;
    *(undefined4 *)(this + 0x1dc) = 0x41f00000;
    *(undefined4 *)(this + 0x1e0) =
         *(undefined4 *)(*(int *)(iVar22 + 0x1e42b0) * 0x2c + iVar20 + 0x94);
    iVar22 = iVar20;
    if (this[0x134] == (cRSubGoldy)0x0) {
      fVar33 = *(float *)(this + 0x5c);
      this[0x134] = (cRSubGoldy)0x1;
      uVar38 = uVar32 & 0xfffffff | (uint)(fVar33 < 0.0) << 0x1f | (uint)(fVar33 == 0.0) << 0x1e;
      uVar32 = uVar38 | (uint)NAN(fVar33) << 0x1c;
      bVar3 = (byte)(uVar38 >> 0x18);
      if ((bool)(bVar3 >> 6 & 1) || bVar3 >> 7 != ((byte)(uVar32 >> 0x1c) & 1)) {
        puVar17 = *(ushort **)(*(int *)(this + 0x2ab8) + 0x104);
        *(ushort **)(this + 0x28fc) = puVar17;
        if ((*puVar17 & 8) == 0) {
          *(undefined4 *)(this + 0x28f4) = 0;
          *(float *)(this + 0x28f8) = ABS(*(float *)(puVar17 + 10));
          uVar10 = *(undefined4 *)(this + 0x2ab8);
        }
        else {
          fVar33 = *(float *)(puVar17 + 10);
          puVar12 = (undefined1 *)0x3f800000;
          *(float *)(this + 0x28f8) = -ABS(fVar33);
          *(float *)(this + 0x28f4) = -ABS(fVar33) + 1.0;
          uVar10 = *(undefined4 *)(this + 0x2ab8);
        }
      }
      else {
        puVar17 = *(ushort **)(*(int *)(this + 0x2b2c) + 0x104);
        *(ushort **)(this + 0x28fc) = puVar17;
        if ((*puVar17 & 8) == 0) {
          *(undefined4 *)(this + 0x28f4) = 0;
          *(float *)(this + 0x28f8) = ABS(*(float *)(puVar17 + 10));
        }
        else {
          fVar33 = *(float *)(puVar17 + 10);
          puVar12 = (undefined1 *)0x3f800000;
          *(float *)(this + 0x28f8) = -ABS(fVar33);
          *(float *)(this + 0x28f4) = -ABS(fVar33) + 1.0;
        }
        uVar10 = *(undefined4 *)(this + 0x2b2c);
      }
      *(undefined4 *)(this + 0x281c) = uVar10;
      *(undefined4 *)(this + 0x292c) = 0;
      *(uint *)(*(int *)(this + 0x2930) + 4) = *(uint *)(*(int *)(this + 0x2930) + 4) | 0x20;
      iVar23 = *(int *)(this + 0x292c);
      iVar22 = *(int *)(this + 0x3f8);
      *(undefined4 *)(this + iVar23 * 4 + 0x2904) = 1;
      *(int *)(this + 0x292c) = iVar23 + 1;
    }
    iVar22 = *(int *)(*(int *)((int)&objc::method_list_t::OFSelectChatRoomDefinitionController.
                                     method8 + iVar21 * 0xdc + iVar20 + 4) * 0x2c + iVar22 + 0x98);
    if (iVar22 != -1) {
      cRVoiceManager::Play((cRVoiceManager *)PTR__gVoiceManager_001b61d8,0xd,2,iVar22);
    }
    puVar6 = PTR__Game_001b60b8;
    cRTipManager::UnInitTips((cRTipManager *)(&DAT_003783b4 + *(int *)PTR__Game_001b60b8));
    cRTipManager::TipNew
              ((cRTipManager *)(&DAT_003783b4 + *(int *)puVar6),(cRTipData *)(this + 0x1d4),true);
  }
  if ((this[0x40d] == (cRSubGoldy)0x0) &&
     ((byte)(*(char *)(uVar36 * 0x44 + uVar16 * 0x220 + iVar20 + 0x13488) - 0x1dU) < 2)) {
    cVar24 = this[0x374];
    if (cVar24 == (cRSubGoldy)0x0) {
      cRPathFollowGoldy::Init((cRPathFollowGoldy *)(this + 0x374),pcVar14,ptVar26,this);
      if (*(int *)(*(int *)(this + 0x378) + 0x2c) != 0x1c) goto LAB_0002841c;
      cRVoiceManager::Play((cRVoiceManager *)PTR__gVoiceManager_001b61d8,0xc,0,-1);
      cVar24 = this[0x374];
    }
  }
  else {
LAB_0002841c:
    cVar24 = this[0x374];
  }
  cVar1 = this[0x2c0];
  if (cVar1 == (cRSubGoldy)0x0) {
    fVar33 = (float)VectorSignedToFloat(*(undefined4 *)(*(int *)(this + 0x3f8) + 0x68),
                                        (byte)(uVar32 >> 0x16) & 3);
    if (*(float *)(this + 100) < fVar33) {
      fVar33 = *(float *)(*(int *)(this + 0x3f8) + 0x4c);
      *(float *)local_f4 = *(float *)local_f4 + fVar33 * fVar33 * 0.004;
    }
    puVar12 = (undefined1 *)0x3f800000;
    fVar33 = *(float *)local_f4;
    uVar16 = uVar32 & 0xfffffff | (uint)(fVar33 < 1.0) << 0x1f | (uint)(fVar33 == 1.0) << 0x1e;
    uVar36 = uVar16 | (uint)NAN(fVar33) << 0x1c;
    bVar3 = (byte)(uVar16 >> 0x18);
    if (!(bool)(bVar3 >> 6 & 1) && bVar3 >> 7 == ((byte)(uVar36 >> 0x1c) & 1)) {
      *(undefined4 *)local_f4 = 0x3f800000;
    }
    if (*(int *)(this + 0x108) == 2) {
      *(undefined4 *)local_f4 = 0;
    }
  }
  else {
    fVar33 = *(float *)local_f4;
    if (fVar33 < 0.0) {
      puVar12 = (undefined1 *)0x3e800000;
      fVar33 = fVar33 + *(float *)(*(int *)(this + 0x3f8) + 0x4c) *
                        *(float *)(*(int *)(this + 0x3f8) + 0x4c) * 0.004 * 0.25;
      *(float *)local_f4 = fVar33;
    }
    uVar16 = uVar32 & 0xfffffff | (uint)(fVar33 < 0.0) << 0x1f | (uint)(fVar33 == 0.0) << 0x1e;
    uVar36 = uVar16 | (uint)NAN(fVar33) << 0x1c;
    bVar3 = (byte)(uVar16 >> 0x18);
    if (!(bool)(bVar3 >> 6 & 1) && bVar3 >> 7 == ((byte)(uVar36 >> 0x1c) & 1)) {
      *(undefined4 *)local_f4 = 0;
    }
  }
  if (cVar24 != (cRSubGoldy)0x0) {
    uVar10 = cRPathFollowGoldy::Traverse
                       ((cRPathFollowGoldy *)(this + 0x374),*(float *)local_f4,ptVar26,local_ec);
    switch(uVar10) {
    case 0:
      if (*(int *)(*(int *)(this + 0x378) + 0x2c) == 0x13) goto switchD_0002af50_caseD_2;
      iVar20 = *(int *)(this + 0x3f8);
      fVar33 = *(float *)(iVar20 + 0x4c) * *(float *)(iVar20 + 0x4c) * 0.004;
      *(float *)local_f4 = *(float *)local_f4 + fVar33 + fVar33;
      break;
    case 1:
    case 3:
      if (this[0x374] == (cRSubGoldy)0x0) goto switchD_0002af50_default;
      goto LAB_00029034;
    case 2:
switchD_0002af50_caseD_2:
      iVar20 = *(int *)(this + 0x3f8);
      break;
    default:
      goto switchD_0002af50_default;
    }
    pcVar11 = this + 0x404;
    fVar33 = *(float *)local_ec;
    fVar40 = *(float *)(this + 0x5c) + fVar33;
    fVar34 = *(float *)(this + 100) + *(float *)local_f4;
    *(float *)(this + 0x5c) = fVar40;
    *(float *)(this + 0x60) = *(float *)(this + 0x60) + *(float *)pcVar11;
    *(float *)(this + 100) = fVar34;
    *(float *)local_f4 = *(float *)local_f4 * (*(float *)(iVar20 + 0x4c) * -0.003 + 1.0);
    fVar35 = *(float *)pcVar11 * (*(float *)(iVar20 + 0x4c) * -0.003 + 1.0);
    *(float *)pcVar11 = fVar35;
    uVar16 = uVar36 & 0xfffffff;
    *(float *)local_ec = fVar33 * (*(float *)(iVar20 + 0x4c) * -0.1 + 1.0);
    fVar37 = *(float *)(iVar20 + 0x4c);
    fVar33 = fVar40;
    if (fVar40 < -4.0) {
      *(undefined4 *)(this + 0x5c) = 0xc0800000;
      fVar33 = -4.0;
    }
    puVar12 = &DAT_40800000;
    uVar36 = uVar16 | (uint)(fVar33 < 4.0) << 0x1f | (uint)(fVar33 == 4.0) << 0x1e;
    uVar38 = uVar36 | (uint)NAN(fVar33) << 0x1c;
    *(float *)pcVar11 = fVar35 + fVar37 * fVar37 * -0.01;
    if (fVar40 < -4.0) {
      *(undefined4 *)local_ec = 0;
    }
    bVar3 = (byte)(uVar36 >> 0x18);
    if (!(bool)(bVar3 >> 6 & 1) && bVar3 >> 7 == ((byte)(uVar38 >> 0x1c) & 1)) {
      *(undefined1 **)(this + 0x5c) = &DAT_40800000;
      *(undefined4 *)local_ec = 0;
    }
    fVar33 = (float)VectorSignedToFloat(*(undefined4 *)(iVar20 + 0x68),(byte)(uVar38 >> 0x16) & 3);
    uVar38 = uVar16 | (uint)(fVar34 < fVar33) << 0x1f;
    uVar36 = uVar38 | (uint)(NAN(fVar34) || NAN(fVar33)) << 0x1c;
    if ((byte)(uVar38 >> 0x1f) == ((byte)(uVar36 >> 0x1c) & 1)) {
      fVar33 = *(float *)(this + 0x25ac);
      uVar16 = uVar16 | (uint)(fVar34 < fVar33) << 0x1f | (uint)(fVar34 == fVar33) << 0x1e;
      uVar36 = uVar16 | (uint)(NAN(fVar34) || NAN(fVar33)) << 0x1c;
      bVar3 = (byte)(uVar16 >> 0x18);
      if (!(bool)(bVar3 >> 6 & 1) && bVar3 >> 7 == ((byte)(uVar36 >> 0x1c) & 1)) {
        *(float *)(this + 0x25ac) = fVar34 + 1.0;
      }
    }
    goto switchD_0002af50_default;
  }
  uVar10 = *(undefined4 *)(this + 0x5c);
  uVar15 = *(undefined4 *)(this + 0x60);
  uVar18 = *(undefined4 *)(this + 100);
  pcVar11 = this + 0x404;
  fVar37 = *(float *)(this + 0x5c) + *(float *)local_ec;
  *(float *)(this + 0x5c) = fVar37;
  uVar36 = uVar36 & 0xfffffff;
  fVar34 = *(float *)(this + 100);
  fVar33 = fVar37;
  if (fVar37 < -4.0) {
    *(undefined4 *)(this + 0x5c) = 0xc0800000;
    fVar33 = -4.0;
  }
  *(float *)(this + 0x60) = *(float *)(this + 0x60) + *(float *)pcVar11;
  fVar35 = *(float *)local_f4;
  if (fVar37 < -4.0) {
    *(undefined4 *)local_ec = 0;
  }
  fVar34 = fVar34 + fVar35;
  uVar38 = uVar36 | (uint)(fVar33 < 4.0) << 0x1f | (uint)(fVar33 == 4.0) << 0x1e;
  uVar16 = uVar38 | (uint)NAN(fVar33) << 0x1c;
  *(float *)(this + 100) = fVar34;
  bVar3 = (byte)(uVar38 >> 0x18);
  if (!(bool)(bVar3 >> 6 & 1) && bVar3 >> 7 == ((byte)(uVar16 >> 0x1c) & 1)) {
    *(undefined1 **)(this + 0x5c) = &DAT_40800000;
    *(undefined4 *)local_ec = 0;
  }
  if (this[0x430] != (cRSubGoldy)0x0) {
    iVar22 = *(int *)(this + 0x3f8);
    goto LAB_000287b0;
  }
  fStack_60 = *(float *)(this + 0x60);
  iVar22 = *(int *)(this + 0x3f8);
  uVar32 = 0xdab;
  uVar38 = (uint)(*(float *)ptVar26 + 4.0);
  if (6 < (int)uVar38) {
    uVar38 = 7;
  }
  uVar39 = (int)*(float *)(this + 100);
  if (0xdaa < (int)*(float *)(this + 100)) {
    uVar39 = uVar32;
  }
  if (*(char *)((uVar38 & ~((int)uVar38 >> 0x1f)) * 0x44 + (uVar39 & ~((int)uVar39 >> 0x1f)) * 0x220
                + iVar22 + 0x13488) == '\x0f') {
LAB_00029288:
    fVar33 = *(float *)(iVar22 + 0x4c) * *(float *)(iVar22 + 0x4c) * 0.004;
    *(float *)local_f4 = *(float *)local_f4 + fVar33 + fVar33;
    fVar33 = (float)VectorSignedToFloat(*(undefined4 *)(iVar22 + 0x68),(byte)(uVar16 >> 0x16) & 3);
    uVar38 = uVar36 | (uint)(fVar34 < fVar33) << 0x1f;
    uVar16 = uVar38 | (uint)(NAN(fVar34) || NAN(fVar33)) << 0x1c;
    if ((byte)(uVar38 >> 0x1f) == ((byte)(uVar16 >> 0x1c) & 1)) {
      fVar33 = *(float *)(this + 0x25ac);
      uVar36 = uVar36 | (uint)(fVar34 < fVar33) << 0x1f | (uint)(fVar34 == fVar33) << 0x1e;
      uVar16 = uVar36 | (uint)(NAN(fVar34) || NAN(fVar33)) << 0x1c;
      bVar3 = (byte)(uVar36 >> 0x18);
      if (!(bool)(bVar3 >> 6 & 1) && bVar3 >> 7 == ((byte)(uVar16 >> 0x1c) & 1)) {
        *(float *)(this + 0x25ac) = fVar34 + 1.0;
      }
    }
  }
  else {
    fStack_60 = *(float *)(this + 0x60);
    uVar38 = (uint)(*(float *)ptVar26 + 4.0);
    if (6 < (int)uVar38) {
      uVar38 = 7;
    }
    uVar39 = (int)*(float *)(this + 100);
    if (0xdaa < (int)*(float *)(this + 100)) {
      uVar39 = uVar32;
    }
    if (*(char *)((uVar38 & ~((int)uVar38 >> 0x1f)) * 0x44 +
                  (uVar39 & ~((int)uVar39 >> 0x1f)) * 0x220 + iVar22 + 0x13488) == '\x10')
    goto LAB_00029288;
    fStack_60 = *(float *)(this + 0x60);
    uVar38 = (uint)(*(float *)ptVar26 + 4.0);
    if (6 < (int)uVar38) {
      uVar38 = 7;
    }
    uVar39 = (int)*(float *)(this + 100);
    if (0xdaa < (int)*(float *)(this + 100)) {
      uVar39 = uVar32;
    }
    if (*(char *)((uVar38 & ~((int)uVar38 >> 0x1f)) * 0x44 +
                  (uVar39 & ~((int)uVar39 >> 0x1f)) * 0x220 + iVar22 + 0x13488) == '\x12')
    goto LAB_00029288;
    fStack_60 = *(float *)(this + 0x60);
    uVar38 = (uint)(*(float *)ptVar26 + 4.0);
    if (6 < (int)uVar38) {
      uVar38 = 7;
    }
    uVar39 = (int)*(float *)(this + 100);
    if (0xdaa < (int)*(float *)(this + 100)) {
      uVar39 = uVar32;
    }
    if (*(char *)((uVar38 & ~((int)uVar38 >> 0x1f)) * 0x44 +
                  (uVar39 & ~((int)uVar39 >> 0x1f)) * 0x220 + iVar22 + 0x13488) == '\x13')
    goto LAB_00029288;
    if (*(int *)(this + 0x3b4) == 2) {
      fStack_60 = *(float *)(this + 0x60);
      uVar38 = (uint)(*(float *)ptVar26 + 4.0);
      if (6 < (int)uVar38) {
        uVar38 = 7;
      }
      uVar39 = (int)*(float *)(this + 100);
      if (0xdaa < (int)*(float *)(this + 100)) {
        uVar39 = uVar32;
      }
      cVar2 = *(char *)((uVar38 & ~((int)uVar38 >> 0x1f)) * 0x44 +
                        (uVar39 & ~((int)uVar39 >> 0x1f)) * 0x220 + iVar22 + 0x13488);
      if (((cVar2 == '\x14' || cVar2 == '\x01') ||
          ((cVar2 == '\x15' || cVar2 == '!') || cVar2 == '\"')) || (cVar2 == '\x1b'))
      goto LAB_00029288;
    }
  }
LAB_000287b0:
  iVar23 = *(int *)(this + 0x25d0);
  if (iVar23 == 1) {
    fVar33 = *(float *)(iVar22 + 0x4c) * *(float *)(iVar22 + 0x4c) * 0.004;
    *(float *)local_f4 = *(float *)local_f4 + fVar33 + fVar33;
  }
  if (this[0x1cc] == (cRSubGoldy)0x0) {
    *(float *)local_f4 = *(float *)local_f4 * (*(float *)(iVar22 + 0x4c) * -0.003 + 1.0);
  }
  cVar24 = this[0x40c];
  *(float *)pcVar11 = *(float *)pcVar11 * (*(float *)(iVar22 + 0x4c) * -0.003 + 1.0);
  *(float *)local_ec = *(float *)local_ec * (*(float *)(iVar22 + 0x4c) * -0.1 + 1.0);
  if (cVar24 != (cRSubGoldy)0x0) {
    fVar33 = *(float *)(iVar22 + 0x4c);
    this[0x40d] = (cRSubGoldy)0x0;
    fVar33 = fVar33 * fVar33 * 0.004;
    *(float *)local_f4 = *(float *)local_f4 + fVar33 + fVar33;
    goto switchD_00029628_caseD_2;
  }
  fStack_60 = *(float *)(this + 0x60);
  cVar24 = this[0x40d];
  uVar36 = (uint)(*(float *)ptVar26 + 4.0);
  if (6 < (int)uVar36) {
    uVar36 = 7;
  }
  uVar38 = (uint)*(float *)(this + 100);
  uVar36 = uVar36 & ~((int)uVar36 >> 0x1f);
  if (0xdaa < (int)uVar38) {
    uVar38 = 0xdab;
  }
  uVar38 = uVar38 & ~((int)uVar38 >> 0x1f);
  if (cVar24 != (cRSubGoldy)0x0) {
    iVar19 = uVar36 * 0x44 + uVar38 * 0x220;
    iVar5 = iVar22 + iVar19;
    iVar19 = iVar19 + iVar22;
    uVar32 = *(byte *)(iVar19 + 0x1348a) & 7;
    iVar29 = uVar32 * 4;
    iVar28 = uVar32 * 0x40;
    uVar32 = ((int)((int)&PTR_caseD_6_00013458 +
                   (iVar5 - (uVar32 * 0x44 + 0x85fd0 + *(int *)PTR__Game_001b60b8))) >> 2) *
             -0xf0f0f0f;
    if ((int)uVar32 < 0) {
      uVar32 = uVar32 + 7;
    }
    if ((((*(uint *)((int)&objc::method_list_t::OFSendChallengeHeaderController +
                    (((int)uVar32 >> 3) * 0x3f - (uVar32 & 0xfffffff8)) * 4 + iVar22 + 0x14) & 0x100
          ) == 0) && (iVar23 == 0)) && (cVar1 == (cRSubGoldy)0x0)) {
      *(float *)local_f4 = *(float *)local_f4 * (*(float *)(iVar22 + 0x4c) * -0.2 + 1.0);
      uVar32 = *(byte *)(iVar19 + 0x1348a) & 7;
      iVar29 = uVar32 << 2;
      iVar28 = uVar32 << 6;
    }
    puVar6 = PTR__Game_001b60b8;
    uVar32 = ((int)&PTR_caseD_6_00013458 +
              (iVar5 - (iVar29 + iVar28 + 0x85fd0 + *(int *)PTR__Game_001b60b8)) >> 2) * -0xf0f0f0f;
    if ((int)uVar32 < 0) {
      uVar32 = uVar32 + 7;
    }
    iVar23 = (((int)uVar32 >> 3) * 0x3f - (uVar32 & 0xfffffff8)) * 4 + iVar22;
    if ((*(uint *)((int)&objc::method_list_t::OFSendChallengeHeaderController + iVar23 + 0x14) &
        0x40) != 0) {
      iVar23 = *(int *)((int)&objc::method_list_t::OFSendChallengeHeaderController + iVar23 + 0xac);
      local_34 = (*(float *)local_ec + 0.0) * 1.05;
      local_30 = (*(float *)pcVar11 + *(float *)(iVar22 + 0x4c) * *(float *)(iVar22 + 0x4c) * -0.01)
                 * 1.05;
      local_2c = (*(float *)local_f4 + 0.0) * 1.05;
      cRPath::Search(*(undefined4 *)(iVar23 + 0x2c),this,*(undefined4 *)ptVar26,
                     *(undefined4 *)(this + 0x60),*(undefined4 *)(this + 100),uVar10,uVar15,uVar18,
                     local_34,local_30,local_2c,iVar23);
      cVar24 = this[0x40d];
    }
    if (cVar24 == (cRSubGoldy)0x0) {
LAB_0002b2a8:
      cVar24 = this[0x374];
    }
    else {
      uVar32 = ((int)((int)&PTR_caseD_6_00013458 +
                     (iVar5 - ((*(byte *)(uVar36 * 0x44 + uVar38 * 0x220 + iVar22 + 0x1348a) & 7) *
                               0x44 + 0x85fd0 + *(int *)puVar6))) >> 2) * -0xf0f0f0f;
      if ((int)uVar32 < 0) {
        uVar32 = uVar32 + 7;
      }
      iVar23 = (((int)uVar32 >> 3) * 0x3f - (uVar32 & 0xfffffff8)) * 4 + *(int *)(this + 0x3f8);
      if ((*(uint *)((int)&objc::method_list_t::OFSendChallengeHeaderController + iVar23 + 0x14) &
          0x80) == 0) goto LAB_0002b2a8;
      fVar33 = *(float *)(*(int *)(this + 0x3f8) + 0x4c);
      iVar23 = *(int *)((int)&objc::method_list_t::OFSendChallengeHeaderController + iVar23 + 0xb0);
      local_40 = (*(float *)local_ec + 0.0) * 1.05;
      local_3c = (*(float *)pcVar11 + fVar33 * fVar33 * -0.01) * 1.05;
      local_38 = (*(float *)local_f4 + 0.0) * 1.05;
      cRPath::Search(*(undefined4 *)(iVar23 + 0x2c),this,*(undefined4 *)ptVar26,
                     *(undefined4 *)(this + 0x60),*(undefined4 *)(this + 100),uVar10,uVar15,uVar18,
                     local_40,local_3c,local_38,iVar23);
      cVar24 = this[0x374];
    }
    if (cVar24 != (cRSubGoldy)0x0) {
      iVar22 = *(int *)(this + 0x3f8);
      goto switchD_00029628_caseD_2;
    }
  }
  fVar33 = *(float *)(this + 0x60);
  uVar10 = 0x3efae148;
  uVar32 = uVar16 & 0xfffffff;
  uVar16 = uVar32 | (uint)(fVar33 < 0.49) << 0x1f;
  if (SUB41(uVar16 >> 0x1f,0)) {
    uVar32 = uVar32 | (uint)(fVar33 < -0.16333334) << 0x1f | (uint)(fVar33 == -0.16333334) << 0x1e;
    uVar16 = uVar32 | (uint)NAN(fVar33) << 0x1c;
    bVar3 = (byte)(uVar32 >> 0x18);
    if ((bool)(bVar3 >> 6 & 1) || bVar3 >> 7 != ((byte)(uVar16 >> 0x1c) & 1)) {
      pcVar27 = (cRSubGoldy *)(uint)*(byte *)(uVar36 * 0x44 + uVar38 * 0x220 + iVar22 + 0x13488);
      uVar32 = 1 - (int)pcVar27;
      if ((cRSubGoldy *)0x1 < pcVar27) {
        uVar32 = 0;
      }
      goto LAB_000295bc;
    }
    iVar23 = uVar36 * 0x44 + uVar38 * 0x220 + iVar22;
    pcVar27 = (cRSubGoldy *)(uint)*(byte *)(iVar23 + 0x13488);
    uVar32 = 1 - (int)pcVar27;
    if ((cRSubGoldy *)0x1 < pcVar27) {
      uVar32 = 0;
    }
    uVar39 = uVar32;
    if (pcVar27 == (cRSubGoldy *)0x1c) {
      uVar39 = uVar32 | 1;
    }
    if (uVar39 != 0) goto LAB_000295bc;
    if (pcVar27 == (cRSubGoldy *)0x23) goto LAB_0002c5a8;
    if (((pcVar27 != (cRSubGoldy *)0xe) && (pcVar27 != (cRSubGoldy *)0x1d)) &&
       (pcVar27 != (cRSubGoldy *)0x16)) {
      pcVar13 = (cRSubGoldy *)tMatrix::RotIdentity((tMatrix *)(this + 0x2c));
      this[0x1cc] = (cRSubGoldy)0x0;
      fVar33 = *(float *)pcVar11;
      if (fVar33 < -0.03) {
        *(float *)(this + 0x3ff4) = (fVar33 - 0.03) * 0.5;
        pcVar27 = this + 0x3ff8;
        *(undefined4 *)pcVar27 = 0;
      }
      uVar16 = uVar16 & 0xfffffff | (uint)(fVar33 == 0.0) << 0x1e | (uint)(0.0 <= fVar33) << 0x1d;
      this[0x40d] = (cRSubGoldy)0x0;
      bVar3 = (byte)(uVar16 >> 0x18);
      bVar31 = (bool)(bVar3 >> 6);
      bVar30 = (bool)(bVar3 >> 5 & 1);
      if (!bVar30 || bVar31) {
        *(undefined4 *)(this + 0x60) = uVar10;
        pcVar27 = (cRSubGoldy *)0x0;
        pcVar13 = pcVar11;
      }
      fVar33 = *(float *)(this + 0x60);
      if (!bVar30 || bVar31) {
        *(cRSubGoldy **)pcVar13 = pcVar27;
      }
      pcVar27 = (cRSubGoldy *)(uint)*(byte *)(iVar23 + 0x13488);
      uVar32 = 1 - (int)pcVar27;
      if ((cRSubGoldy *)0x1 < pcVar27) {
        uVar32 = 0;
      }
      goto LAB_000295bc;
    }
  }
  else {
    pcVar27 = (cRSubGoldy *)(uint)*(byte *)(uVar36 * 0x44 + uVar38 * 0x220 + iVar22 + 0x13488);
    uVar32 = 1 - (int)pcVar27;
    if ((cRSubGoldy *)0x1 < pcVar27) {
      uVar32 = 0;
    }
LAB_000295bc:
    if (pcVar27 == (cRSubGoldy *)0x23) {
      uVar32 = uVar32 | 1;
    }
    if ((uVar32 != 0) &&
       (uVar16 = uVar16 & 0xfffffff | (uint)(fVar33 < 0.49) << 0x1f, SUB41(uVar16 >> 0x1f,0))) {
LAB_0002c5a8:
      uVar32 = uVar16 & 0xfffffff;
      uVar16 = uVar32 | (uint)(*(float *)pcVar11 == 0.0) << 0x1e |
               (uint)(0.0 <= *(float *)pcVar11) << 0x1d;
      bVar3 = (byte)(uVar16 >> 0x18);
      if (!(bool)(bVar3 >> 5 & 1) || (bool)(bVar3 >> 6)) {
        fVar37 = *(float *)(this + 100);
        fVar35 = (float)VectorSignedToFloat((int)fVar37,(byte)(uVar16 >> 0x16) & 3);
        bVar3 = *(byte *)(uVar36 * 0x44 + uVar38 * 0x220 + iVar22 + 0x13489);
        fVar35 = fVar37 - fVar35;
        fVar34 = 1.0;
        if ((bVar3 & 2) != 0) {
          fVar34 = 0.8;
        }
        uVar36 = uVar32 | (uint)(fVar34 < fVar35) << 0x1f | (uint)(fVar34 == fVar35) << 0x1e;
        uVar16 = uVar36 | (uint)(NAN(fVar34) || NAN(fVar35)) << 0x1c;
        fVar34 = 0.2;
        if ((bVar3 & 1) == 0) {
          fVar34 = 0.0;
        }
        bVar3 = (byte)(uVar36 >> 0x18);
        if (((!(bool)(bVar3 >> 6 & 1) && bVar3 >> 7 == ((byte)(uVar16 >> 0x1c) & 1)) &&
            (uVar16 = uVar32 | (uint)(fVar34 < fVar35) << 0x1f, SUB41(uVar16 >> 0x1f,0))) &&
           (this[0x40d] == (cRSubGoldy)0x0)) {
          if (this[0x374] == (cRSubGoldy)0x0) {
            *(undefined4 *)(this + 0x420) = 0;
            *(undefined4 *)(this + 0x41c) = 0;
          }
          else {
            *(undefined4 *)(this + 0x420) = *(undefined4 *)(*(int *)(this + 0x378) + 0x80);
            *(undefined4 *)(this + 0x41c) = *(undefined4 *)(this + 0x390);
          }
          this[0x40d] = (cRSubGoldy)0x1;
          *(float *)(this + 0x414) = fVar37;
          *(undefined4 *)(this + 0x424) = 0;
          this[0x374] = (cRSubGoldy)0x0;
          this[0x43c] = (cRSubGoldy)0x0;
          this[0x43d] = (cRSubGoldy)0x0;
          wprintf("**Death Segment = %s\n",
                  *(undefined4 *)
                   (*(int *)((int)&objc::method_list_t::OFSendChallengeHeaderController.method18 +
                            iVar21 * 0xdc + iVar20 + 8) + 0x10));
          fVar33 = *(float *)(this + 0x60);
        }
      }
    }
  }
  iVar22 = *(int *)(this + 0x3f8);
  if ((((*(uint *)(iVar22 + 100) & 0x400) == 0) || ((*(uint *)PTR__gCheat_001b61dc & 2) != 0)) &&
     (uVar16 = uVar16 & 0xfffffff | (uint)(fVar33 < 0.49) << 0x1f, SUB41(uVar16 >> 0x1f,0))) {
    fVar33 = *(float *)pcVar11;
    *(undefined4 *)pcVar11 = 0;
    *(undefined4 *)(this + 0x60) = 0x3efae148;
    *(float *)(this + 0x3ff4) = fVar33 * 0.5;
    *(undefined4 *)(this + 0x3ff8) = 0;
    this[0x1cc] = (cRSubGoldy)0x0;
    this[0x40d] = (cRSubGoldy)0x0;
    goto switchD_00029628_caseD_2;
  }
  uVar16 = uVar16 & 0xfffffff | (uint)(fVar33 < -7.0) << 0x1f;
  if ((!SUB41(uVar16 >> 0x1f,0)) || (this[0x78] != (cRSubGoldy)0x0)) goto switchD_00029628_caseD_2;
  switch(*(undefined4 *)(iVar22 + 0x58)) {
  case 0:
    if (*(int *)(this + 0x3fec) < 1) {
      SetGameState(0,0,0,0);
      *(undefined4 *)(this + 0x74) = 1;
    }
    else {
      SetGameState(1,*(int *)(this + 0x2cc),*(int *)(iVar22 + 0x5c),*(int *)(this + 0x3fec) + -1);
      *(undefined4 *)(this + 0x74) = 0;
    }
    this[0x78] = (cRSubGoldy)0x1;
    *(undefined4 *)(this + 0x80) = 0;
    iVar22 = *(int *)(this + 0x3f8);
    *(undefined4 *)(this + 0x84) = 0x3c088889;
    break;
  case 1:
  case 4:
    *(undefined4 *)(this + 0x74) = 1;
    goto LAB_0002bb4c;
  case 7:
    *(undefined4 *)(this + 0x74) = 0;
LAB_0002bb4c:
    this[0x78] = (cRSubGoldy)0x1;
    *(undefined4 *)(this + 0x80) = 0;
    *(undefined4 *)(this + 0x84) = 0x3c088889;
  }
switchD_00029628_caseD_2:
  uVar36 = uVar16 & 0xfffffff | (uint)(*(float *)(this + 0x1c4) == 0.0) << 0x1e;
  if (!SUB41(uVar36 >> 0x1e,0)) {
    fVar33 = *(float *)(this + 0x1c4) + *(float *)(this + 0x1c8);
    uVar16 = uVar16 & 0xfffffff | (uint)(fVar33 < 1.0) << 0x1f | (uint)(fVar33 == 1.0) << 0x1e;
    uVar36 = uVar16 | (uint)NAN(fVar33) << 0x1c;
    *(float *)(this + 0x1c4) = fVar33;
    bVar3 = (byte)(uVar16 >> 0x18);
    if (!(bool)(bVar3 >> 6 & 1) && bVar3 >> 7 == ((byte)(uVar36 >> 0x1c) & 1)) {
      *(undefined4 *)(this + 0x1c4) = 0;
    }
  }
  if (this[0x40d] == (cRSubGoldy)0x0) {
    local_70 = *(undefined1 **)ptVar26;
    fStack_60 = *(float *)(this + 0x60);
    local_68 = *(float *)(this + 100);
    uVar16 = (uint)((float)local_70 + 4.0);
    if (6 < (int)uVar16) {
      uVar16 = 7;
    }
    uVar38 = (uint)local_68;
    uVar16 = uVar16 & ~((int)uVar16 >> 0x1f);
    if (0xdaa < (int)uVar38) {
      uVar38 = 0xdab;
    }
    uVar38 = uVar38 & ~((int)uVar38 >> 0x1f);
    bVar3 = *(byte *)(uVar16 * 0x44 + uVar38 * 0x220 + iVar22 + 0x13488);
    if ((bVar3 == 0xf || bVar3 == 1) || (bVar3 == 0xe)) {
      fVar33 = 0.49;
    }
    else {
      bVar31 = 10 < bVar3;
      if (bVar3 != 0xb) {
        bVar31 = 4 < (byte)(bVar3 - 2);
      }
      if (((!bVar31 || (bVar3 == 0xb || (byte)(bVar3 - 2) == 5)) || (bVar3 == 0xc)) ||
         (bVar3 == 0xd)) {
        fVar33 = (float)VectorSignedToFloat((int)local_68,(byte)(uVar36 >> 0x16) & 3);
        fVar33 = (local_68 - fVar33) * 0.4 + 0.49;
      }
      else if ((byte)(bVar3 - 8) < 3) {
        fVar33 = (float)VectorSignedToFloat((int)local_68,(byte)(uVar36 >> 0x16) & 3);
        fVar33 = (local_68 - fVar33) * 0.4 + 0.5 + 0.49;
      }
      else if (bVar3 == 0x16) {
        fVar33 = *(float *)(uVar16 * 0x44 + uVar38 * 0x220 + iVar22 + 0x1346c) + 0.49;
      }
      else {
        fVar33 = -99.51;
      }
    }
    puVar12 = *(undefined1 **)(this + 0x60);
    uVar36 = uVar36 & 0xfffffff;
    uVar16 = uVar36 | (uint)((float)puVar12 < fVar33) << 0x1f;
    if (SUB41(uVar16 >> 0x1f,0)) {
      uVar38 = 0xdab;
      uVar16 = uVar36 | (uint)(*(float *)pcVar11 == 0.0) << 0x1e |
               (uint)(0.0 <= *(float *)pcVar11) << 0x1d;
      bVar3 = (byte)(uVar16 >> 0x18);
      if (!(bool)(bVar3 >> 5 & 1) || (bool)(bVar3 >> 6)) {
        *(float *)(this + 0x60) = fVar33;
      }
      local_70 = *(undefined1 **)ptVar26;
      fStack_6c = *(float *)(this + 0x60);
      local_68 = *(float *)(this + 100);
      uVar32 = (uint)((float)local_70 + 4.0);
      if (6 < (int)uVar32) {
        uVar32 = 7;
      }
      uVar39 = (int)local_68;
      if (0xdaa < (int)local_68) {
        uVar39 = uVar38;
      }
      if (*(char *)((uVar32 & ~((int)uVar32 >> 0x1f)) * 0x44 +
                    (uVar39 & ~((int)uVar39 >> 0x1f)) * 0x220 + iVar22 + 0x13488) == '\b') {
LAB_0002be04:
        fVar33 = *(float *)(this + 100);
        *(float *)pcVar11 = *(float *)(iVar22 + 0x4c) * 0.3;
        fVar34 = *(float *)(this + 0x440) + 1.0;
        uVar36 = uVar36 | (uint)(fVar33 < fVar34) << 0x1f | (uint)(fVar33 == fVar34) << 0x1e;
        uVar16 = uVar36 | (uint)(NAN(fVar33) || NAN(fVar34)) << 0x1c;
        bVar3 = (byte)(uVar36 >> 0x18);
        if (!(bool)(bVar3 >> 6 & 1) && bVar3 >> 7 == ((byte)(uVar16 >> 0x1c) & 1)) {
          cRSound::Play((cRSound *)PTR__gRSound_001b61e0,0x2a);
          puVar12 = *(undefined1 **)(this + 0x60);
          *(undefined4 *)(this + 0x440) = *(undefined4 *)(this + 100);
          goto LAB_00028ff0;
        }
      }
      else {
        local_70 = *(undefined1 **)ptVar26;
        fStack_6c = *(float *)(this + 0x60);
        local_68 = *(float *)(this + 100);
        uVar32 = (uint)((float)local_70 + 4.0);
        if (6 < (int)uVar32) {
          uVar32 = 7;
        }
        uVar39 = (int)local_68;
        if (0xdaa < (int)local_68) {
          uVar39 = uVar38;
        }
        if (*(char *)((uVar32 & ~((int)uVar32 >> 0x1f)) * 0x44 +
                      (uVar39 & ~((int)uVar39 >> 0x1f)) * 0x220 + iVar22 + 0x13488) == '\t')
        goto LAB_0002be04;
        local_70 = *(undefined1 **)ptVar26;
        fStack_6c = *(float *)(this + 0x60);
        local_68 = *(float *)(this + 100);
        uVar32 = (uint)((float)local_70 + 4.0);
        if (6 < (int)uVar32) {
          uVar32 = 7;
        }
        uVar39 = (int)local_68;
        if (0xdaa < (int)local_68) {
          uVar39 = uVar38;
        }
        if (*(char *)((uVar32 & ~((int)uVar32 >> 0x1f)) * 0x44 +
                      (uVar39 & ~((int)uVar39 >> 0x1f)) * 0x220 + iVar22 + 0x13488) == '\n')
        goto LAB_0002be04;
        local_70 = *(undefined1 **)ptVar26;
        fStack_6c = *(float *)(this + 0x60);
        local_68 = *(float *)(this + 100);
        uVar32 = (uint)((float)local_70 + 4.0);
        if (6 < (int)uVar32) {
          uVar32 = 7;
        }
        uVar39 = (int)local_68;
        if (0xdaa < (int)local_68) {
          uVar39 = uVar38;
        }
        if (*(char *)((uVar32 & ~((int)uVar32 >> 0x1f)) * 0x44 +
                      (uVar39 & ~((int)uVar39 >> 0x1f)) * 0x220 + iVar22 + 0x13488) == '\v')
        goto LAB_0002be04;
        local_70 = *(undefined1 **)ptVar26;
        fStack_6c = *(float *)(this + 0x60);
        local_68 = *(float *)(this + 100);
        uVar32 = (uint)((float)local_70 + 4.0);
        if (6 < (int)uVar32) {
          uVar32 = 7;
        }
        uVar39 = (int)local_68;
        if (0xdaa < (int)local_68) {
          uVar39 = uVar38;
        }
        if (*(char *)((uVar32 & ~((int)uVar32 >> 0x1f)) * 0x44 +
                      (uVar39 & ~((int)uVar39 >> 0x1f)) * 0x220 + iVar22 + 0x13488) == '\f')
        goto LAB_0002be04;
        local_70 = *(undefined1 **)ptVar26;
        fStack_6c = *(float *)(this + 0x60);
        local_68 = *(float *)(this + 100);
        uVar32 = (uint)((float)local_70 + 4.0);
        if (6 < (int)uVar32) {
          uVar32 = 7;
        }
        uVar39 = (int)local_68;
        if (0xdaa < (int)local_68) {
          uVar39 = uVar38;
        }
        if (*(char *)((uVar32 & ~((int)uVar32 >> 0x1f)) * 0x44 +
                      (uVar39 & ~((int)uVar39 >> 0x1f)) * 0x220 + iVar22 + 0x13488) == '\r')
        goto LAB_0002be04;
        local_70 = *(undefined1 **)ptVar26;
        fStack_6c = *(float *)(this + 0x60);
        local_68 = *(float *)(this + 100);
        uVar32 = (uint)((float)local_70 + 4.0);
        if (6 < (int)uVar32) {
          uVar32 = 7;
        }
        uVar39 = (int)local_68;
        if (0xdaa < (int)local_68) {
          uVar39 = uVar38;
        }
        if (*(char *)((uVar32 & ~((int)uVar32 >> 0x1f)) * 0x44 +
                      (uVar39 & ~((int)uVar39 >> 0x1f)) * 0x220 + iVar22 + 0x13488) == '\x02') {
LAB_0002ca10:
          fVar34 = 1.0;
          fVar33 = *(float *)(this + 100);
          if (*(float *)(this + 0x1c4) == 0.0) {
            *(undefined4 *)(this + 0x1c4) = *(undefined4 *)(this + 0x1c8);
          }
          *(float *)pcVar11 = *(float *)(iVar22 + 0x4c) * 0.2;
          fVar37 = *(float *)(this + 0x440) + 1.0;
          uVar36 = uVar36 | (uint)(fVar33 < fVar37) << 0x1f | (uint)(fVar33 == fVar37) << 0x1e;
          uVar16 = uVar36 | (uint)(NAN(fVar33) || NAN(fVar37)) << 0x1c;
          bVar3 = (byte)(uVar36 >> 0x18);
          if (!(bool)(bVar3 >> 6 & 1) && bVar3 >> 7 == ((byte)(uVar16 >> 0x1c) & 1)) {
            cRSound::Play((cRSound *)PTR__gRSound_001b61e0,0x2a);
            *(undefined4 *)(this + 0x440) = *(undefined4 *)(this + 100);
          }
          if (this[0x2c0] == (cRSubGoldy)0x0) {
            fVar33 = *(float *)(this + 0x5c);
            uVar36 = uVar16 & 0xfffffff | (uint)(fVar33 < 0.0) << 0x1f |
                     (uint)(fVar33 == 0.0) << 0x1e;
            uVar16 = uVar36 | (uint)NAN(fVar33) << 0x1c;
            bVar3 = (byte)(uVar36 >> 0x18);
            if ((bool)(bVar3 >> 6 & 1) || bVar3 >> 7 != ((byte)(uVar16 >> 0x1c) & 1)) {
              puVar17 = *(ushort **)(*(int *)(this + 0x2ab8) + 0x104);
              *(ushort **)(this + 0x28fc) = puVar17;
              if ((*puVar17 & 8) == 0) {
                *(undefined4 *)(this + 0x28f4) = 0;
                *(float *)(this + 0x28f8) = ABS(*(float *)(puVar17 + 10));
              }
              else {
                fVar33 = *(float *)(puVar17 + 10);
                *(float *)(this + 0x28f8) = -ABS(fVar33);
                *(float *)(this + 0x28f4) = -ABS(fVar33) + fVar34;
              }
              uVar10 = *(undefined4 *)(this + 0x2ab8);
            }
            else {
              puVar17 = *(ushort **)(*(int *)(this + 0x2b2c) + 0x104);
              *(ushort **)(this + 0x28fc) = puVar17;
              if ((*puVar17 & 8) == 0) {
                *(undefined4 *)(this + 0x28f4) = 0;
                *(float *)(this + 0x28f8) = ABS(*(float *)(puVar17 + 10));
              }
              else {
                fVar33 = *(float *)(puVar17 + 10);
                *(float *)(this + 0x28f8) = -ABS(fVar33);
                *(float *)(this + 0x28f4) = -ABS(fVar33) + fVar34;
              }
              uVar10 = *(undefined4 *)(this + 0x2b2c);
            }
            *(undefined4 *)(this + 0x281c) = uVar10;
            *(undefined4 *)(this + 0x292c) = 0;
            puVar12 = *(undefined1 **)(this + 0x60);
            *(uint *)(*(int *)(this + 0x2930) + 4) = *(uint *)(*(int *)(this + 0x2930) + 4) | 0x20;
            iVar20 = *(int *)(this + 0x292c);
            *(undefined4 *)(this + iVar20 * 4 + 0x2904) = 1;
            *(int *)(this + 0x292c) = iVar20 + 1;
            goto LAB_00028ff0;
          }
        }
        else {
          local_70 = *(undefined1 **)ptVar26;
          fStack_6c = *(float *)(this + 0x60);
          local_68 = *(float *)(this + 100);
          uVar32 = (uint)((float)local_70 + 4.0);
          if (6 < (int)uVar32) {
            uVar32 = 7;
          }
          uVar39 = (int)local_68;
          if (0xdaa < (int)local_68) {
            uVar39 = uVar38;
          }
          if (*(char *)((uVar32 & ~((int)uVar32 >> 0x1f)) * 0x44 +
                        (uVar39 & ~((int)uVar39 >> 0x1f)) * 0x220 + iVar22 + 0x13488) == '\x03')
          goto LAB_0002ca10;
          local_70 = *(undefined1 **)ptVar26;
          fStack_6c = *(float *)(this + 0x60);
          local_68 = *(float *)(this + 100);
          uVar32 = (uint)((float)local_70 + 4.0);
          if (6 < (int)uVar32) {
            uVar32 = 7;
          }
          uVar39 = (int)local_68;
          if (0xdaa < (int)local_68) {
            uVar39 = uVar38;
          }
          if (*(char *)((uVar32 & ~((int)uVar32 >> 0x1f)) * 0x44 +
                        (uVar39 & ~((int)uVar39 >> 0x1f)) * 0x220 + iVar22 + 0x13488) == '\x04')
          goto LAB_0002ca10;
          local_70 = *(undefined1 **)ptVar26;
          fStack_6c = *(float *)(this + 0x60);
          local_68 = *(float *)(this + 100);
          uVar32 = (uint)((float)local_70 + 4.0);
          if (6 < (int)uVar32) {
            uVar32 = 7;
          }
          uVar39 = (int)local_68;
          if (0xdaa < (int)local_68) {
            uVar39 = uVar38;
          }
          if (*(char *)((uVar32 & ~((int)uVar32 >> 0x1f)) * 0x44 +
                        (uVar39 & ~((int)uVar39 >> 0x1f)) * 0x220 + iVar22 + 0x13488) == '\x05')
          goto LAB_0002ca10;
          local_70 = *(undefined1 **)ptVar26;
          fStack_6c = *(float *)(this + 0x60);
          local_68 = *(float *)(this + 100);
          uVar32 = (uint)((float)local_70 + 4.0);
          if (6 < (int)uVar32) {
            uVar32 = 7;
          }
          uVar39 = (int)local_68;
          if (0xdaa < (int)local_68) {
            uVar39 = uVar38;
          }
          if (*(char *)((uVar32 & ~((int)uVar32 >> 0x1f)) * 0x44 +
                        (uVar39 & ~((int)uVar39 >> 0x1f)) * 0x220 + iVar22 + 0x13488) == '\x06')
          goto LAB_0002ca10;
          local_70 = *(undefined1 **)ptVar26;
          fStack_6c = *(float *)(this + 0x60);
          local_68 = *(float *)(this + 100);
          uVar32 = (uint)((float)local_70 + 4.0);
          if (6 < (int)uVar32) {
            uVar32 = 7;
          }
          uVar39 = (uint)local_68;
          if (0xdaa < (int)uVar39) {
            uVar39 = uVar38;
          }
          if (*(char *)((uVar32 & ~((int)uVar32 >> 0x1f)) * 0x44 +
                        (uVar39 & ~((int)uVar39 >> 0x1f)) * 0x220 + iVar22 + 0x13488) == '\a')
          goto LAB_0002ca10;
          local_70 = *(undefined1 **)ptVar26;
          fStack_6c = *(float *)(this + 0x60);
          local_68 = *(float *)(this + 100);
          uVar36 = (uint)((float)local_70 + 4.0);
          if (6 < (int)uVar36) {
            uVar36 = 7;
          }
          uVar32 = (int)local_68;
          if (0xdaa < (int)local_68) {
            uVar32 = uVar38;
          }
          if (*(char *)((uVar36 & ~((int)uVar36 >> 0x1f)) * 0x44 +
                        (uVar32 & ~((int)uVar32 >> 0x1f)) * 0x220 + iVar22 + 0x13488) != '\0') {
            local_70 = *(undefined1 **)ptVar26;
            fStack_6c = *(float *)(this + 0x60);
            local_68 = *(float *)(this + 100);
            uVar36 = (uint)((float)local_70 + 4.0);
            if (6 < (int)uVar36) {
              uVar36 = 7;
            }
            uVar38 = (int)local_68;
            if (0xdaa < (int)local_68) {
              uVar38 = 0xdab;
            }
            if (*(char *)((uVar36 & ~((int)uVar36 >> 0x1f)) * 0x44 +
                          (uVar38 & ~((int)uVar38 >> 0x1f)) * 0x220 + iVar22 + 0x13488) != '#') {
              local_70 = *(undefined1 **)ptVar26;
              fStack_6c = *(float *)(this + 0x60);
              local_68 = *(float *)(this + 100);
              uVar36 = (uint)((float)local_70 + 4.0);
              if (6 < (int)uVar36) {
                uVar36 = 7;
              }
              uVar38 = (int)local_68;
              if (0xdaa < (int)local_68) {
                uVar38 = 0xdab;
              }
              if (*(char *)((uVar36 & ~((int)uVar36 >> 0x1f)) * 0x44 +
                            (uVar38 & ~((int)uVar38 >> 0x1f)) * 0x220 + iVar22 + 0x13488) != '\x16')
              {
                puVar12 = *(undefined1 **)(this + 0x60);
                this[0x1cc] = (cRSubGoldy)0x0;
                *(undefined4 *)pcVar11 = 0;
                goto LAB_00028ff0;
              }
            }
          }
        }
      }
      puVar12 = *(undefined1 **)(this + 0x60);
    }
    else {
      *(float *)pcVar11 =
           *(float *)pcVar11 + *(float *)(iVar22 + 0x4c) * *(float *)(iVar22 + 0x4c) * -0.01;
      fStack_6c = fStack_60;
    }
LAB_00028ff0:
    uVar36 = uVar16 & 0xfffffff | (uint)((float)puVar12 < 0.0) << 0x1f;
    if ((SUB41(uVar36 >> 0x1f,0)) &&
       (uVar36 = uVar16 & 0xfffffff | (uint)(*(float *)pcVar11 == 0.0) << 0x1e |
                 (uint)(0.0 <= *(float *)pcVar11) << 0x1d, bVar3 = (byte)(uVar36 >> 0x18),
       !(bool)(bVar3 >> 5 & 1) || (bool)(bVar3 >> 6))) {
      if (this[0x374] == (cRSubGoldy)0x0) {
        *(undefined4 *)(this + 0x420) = 0;
        *(undefined4 *)(this + 0x41c) = 0;
      }
      else {
LAB_00029034:
        *(undefined4 *)(this + 0x420) = *(undefined4 *)(*(int *)(this + 0x378) + 0x80);
        *(undefined4 *)(this + 0x41c) = *(undefined4 *)(this + 0x390);
      }
      this[0x40d] = (cRSubGoldy)0x1;
      *(undefined4 *)(this + 0x414) = *(undefined4 *)(this + 100);
      this[0x374] = (cRSubGoldy)0x0;
      *(undefined4 *)(this + 0x424) = 0;
      this[0x43c] = (cRSubGoldy)0x0;
      this[0x43d] = (cRSubGoldy)0x0;
    }
  }
  else {
    local_70 = *(undefined1 **)ptVar26;
    fStack_6c = *(float *)(this + 0x60);
    local_68 = *(float *)(this + 100);
    fVar33 = *(float *)pcVar11 + *(float *)(iVar22 + 0x4c) * *(float *)(iVar22 + 0x4c) * -0.01;
    *(float *)pcVar11 = fVar33;
    uVar16 = (uint)((float)local_70 + 4.0);
    if (6 < (int)uVar16) {
      uVar16 = 7;
    }
    uVar38 = (uint)local_68;
    uVar16 = uVar16 & ~((int)uVar16 >> 0x1f);
    if (0xdaa < (int)uVar38) {
      uVar38 = 0xdab;
    }
    uVar38 = uVar38 & ~((int)uVar38 >> 0x1f);
    iVar20 = uVar16 * 0x44 + uVar38 * 0x220;
    iVar21 = iVar20 + iVar22;
    puVar12 = local_70;
    if (*(char *)(iVar21 + 0x13488) == '\x16') {
      puVar12 = *(undefined1 **)(iVar21 + 0x1346c);
      fVar34 = *(float *)(this + 0x60);
      uVar32 = uVar36 & 0xfffffff;
      uVar36 = uVar32 | (uint)(fVar34 < (float)puVar12 + 0.49) << 0x1f;
      if (SUB41(uVar36 >> 0x1f,0)) {
        fVar37 = (float)puVar12 - 0.49;
        uVar32 = uVar32 | (uint)(fVar34 < fVar37) << 0x1f | (uint)(fVar34 == fVar37) << 0x1e;
        uVar36 = uVar32 | (uint)(NAN(fVar34) || NAN(fVar37)) << 0x1c;
        bVar3 = (byte)(uVar32 >> 0x18);
        if (!(bool)(bVar3 >> 6 & 1) && bVar3 >> 7 == ((byte)(uVar36 >> 0x1c) & 1)) {
          *(float *)(this + 0x3ff4) = fVar33 * 0.5;
          *(undefined4 *)(this + 0x3ff8) = 0;
          puVar6 = PTR__Game_001b60b8;
          *(float *)pcVar11 = *(float *)(iVar22 + 0x4c) * 0.3;
          iVar23 = *(int *)puVar6;
          cVar2 = *(char *)(iVar21 + 0x13488);
          iVar20 = (int)&PTR_caseD_6_00013458 + iVar22 + iVar20;
          while (cVar2 == '\x16') {
            cVar2 = *(char *)(iVar20 + -0x14);
            iVar20 = iVar20 + -0x44;
          }
          cVar2 = *(char *)(iVar20 + 0x74);
          iVar20 = iVar20 + 0x44;
          while (cVar2 == '\x16') {
            cVar2 = *(char *)(iVar20 + -0x1f0);
            iVar20 = iVar20 + -0x220;
          }
          iVar21 = 0;
          if (*(int *)(&DAT_00377f00 + iVar23) == 0) {
LAB_0002cca8:
            iVar21 = iVar21 * 0x84;
            iVar29 = iVar21 + iVar23;
            *(undefined4 *)(&DAT_00377f00 + iVar29) = 1;
            *(undefined4 *)(&DAT_00377f04 + iVar29) = 0;
            *(float *)(iVar29 + 0x377f08) =
                 *(float *)(*(int *)PTR__Game_001b60b8 + 0x72bc4) * 0.041666668;
            tMatrix::Identity((tMatrix *)(iVar23 + iVar21 + 0x377eb8));
            uVar10 = *(undefined4 *)(iVar20 + 0x6b8);
            uVar15 = *(undefined4 *)(iVar20 + 0x6bc);
            *(undefined4 *)(iVar29 + 0x377ee8) = *(undefined4 *)(iVar20 + 0x6b4);
            *(undefined4 *)(iVar29 + 0x377eec) = uVar10;
            *(undefined4 *)(iVar29 + 0x377ef0) = uVar15;
            uVar32 = *(uint *)(iVar29 + 0x377e90);
            *(float *)(iVar29 + 0x377eec) = *(float *)(iVar29 + 0x377eec) - 0.2;
            iVar20 = *(int *)PTR__Game_001b60b8;
            if ((uVar32 & 0x200) == 0) {
              *(int *)(iVar29 + 0x377e94) = iVar20 + 0x7511c;
              iVar23 = iVar23 + iVar21 + 0x377e8c;
              *(undefined4 *)(iVar29 + 0x377e98) = *(undefined4 *)(iVar20 + 0x75128);
              *(int *)(iVar20 + 0x75128) = iVar23;
              if (*(int *)(iVar29 + 0x377e98) != 0) {
                *(int *)(*(int *)(iVar29 + 0x377e98) + 8) = iVar23;
              }
              *(uint *)(iVar29 + 0x377e90) = uVar32 | 0x200;
            }
            else {
              RShellError("List ADDafter");
            }
          }
          else {
            if (*(int *)(&DAT_00377f84 + iVar23) == 0) {
              iVar21 = 1;
              goto LAB_0002cca8;
            }
            if (*(int *)(&DAT_00378008 + iVar23) == 0) {
              iVar21 = 2;
              goto LAB_0002cca8;
            }
            if (*(int *)(&DAT_0037808c + iVar23) == 0) {
              iVar21 = 3;
              goto LAB_0002cca8;
            }
            if (*(int *)(&DAT_00378110 + iVar23) == 0) {
              iVar21 = 4;
              goto LAB_0002cca8;
            }
            if (*(int *)(&DAT_00378194 + iVar23) == 0) {
              iVar21 = 5;
              goto LAB_0002cca8;
            }
            if (*(int *)(&DAT_00378218 + iVar23) == 0) {
              iVar21 = 6;
              goto LAB_0002cca8;
            }
            if (*(int *)(&DAT_0037829c + iVar23) == 0) {
              iVar21 = 7;
              goto LAB_0002cca8;
            }
          }
          fVar33 = *(float *)(uVar16 * 0x44 + uVar38 * 0x220 + iVar22 + 0x1346c);
          this[0x40d] = (cRSubGoldy)0x0;
          puVar6 = PTR__gRSound_001b61e0;
          puVar12 = (undefined1 *)(fVar33 + 0.49);
          this[0x1cc] = (cRSubGoldy)0x1;
          *(undefined1 **)(this + 0x60) = puVar12;
          cRSound::Play((cRSound *)puVar6,0x29);
        }
      }
    }
  }
switchD_0002af50_default:
  if (*(char *)(*(int *)PTR__Game_001b60b8 + 0x72b8a) == '\0') {
    if (*(int *)(this + 0x3e4) == 1) {
      *(undefined4 *)(*(int *)(this + 0x3f0) + 0x1fc) = 0x3f7fbe77;
      fVar33 = *(float *)(this + 1000) + *(float *)(this + 0x3ec);
      uVar16 = uVar36 & 0xfffffff | (uint)(fVar33 < 1.0) << 0x1f | (uint)(fVar33 == 1.0) << 0x1e;
      uVar36 = uVar16 | (uint)NAN(fVar33) << 0x1c;
      *(float *)(this + 1000) = fVar33;
      bVar3 = (byte)(uVar16 >> 0x18);
      if (!(bool)(bVar3 >> 6 & 1) && bVar3 >> 7 == ((byte)(uVar36 >> 0x1c) & 1)) {
        *(undefined4 *)(this + 1000) = 0;
        *(undefined4 *)(this + 0x3e4) = 2;
      }
    }
    else if (*(int *)(this + 0x3e4) == 2) {
      fVar33 = *(float *)(this + 1000);
      if (fVar33 < 0.5) {
        iVar20 = *(int *)(this + 0x3f0);
        puVar12 = (undefined1 *)(fVar33 * -2.0 + 1.0);
      }
      else {
        iVar20 = 0;
        *(undefined4 *)(*(int *)(this + 0x3f0) + 0x1fc) = 0;
      }
      if (fVar33 < 0.5) {
        *(undefined1 **)(iVar20 + 0x1fc) = puVar12;
      }
      fVar33 = *(float *)(this + 1000) + *(float *)(this + 0x3ec);
      uVar16 = uVar36 & 0xfffffff | (uint)(fVar33 < 1.0) << 0x1f | (uint)(fVar33 == 1.0) << 0x1e;
      uVar36 = uVar16 | (uint)NAN(fVar33) << 0x1c;
      *(float *)(this + 1000) = fVar33;
      bVar3 = (byte)(uVar16 >> 0x18);
      if (!(bool)(bVar3 >> 6 & 1) && bVar3 >> 7 == ((byte)(uVar36 >> 0x1c) & 1)) {
        *(undefined4 *)(this + 1000) = 0;
        puVar6 = PTR__gRSound_001b61e0;
        *(undefined4 *)(this + 0x3e4) = 1;
        cRSound::Play((cRSound *)puVar6,0x33);
      }
    }
  }
  if (this[0x40c] == (cRSubGoldy)0x0) {
    if (this[0x374] == (cRSubGoldy)0x0) {
      uVar10 = 0;
      fVar33 = *(float *)(this + 100);
      local_70 = (undefined1 *)(*(float *)(this + 0x5c) + 0.0);
      iVar20 = *(int *)(this + 0x3f8);
      local_68 = fVar33 + 0.49;
      fStack_6c = *(float *)(this + 0x60) + 0.0;
      uVar16 = (uint)((float)local_70 + 4.0);
      if (6 < (int)uVar16) {
        uVar16 = 7;
      }
      uVar38 = (int)local_68;
      if (0xdaa < (int)local_68) {
        uVar38 = 0xdab;
      }
      local_4c = local_70;
      local_48 = fStack_6c;
      local_44 = local_68;
      if (*(char *)((uVar16 & ~((int)uVar16 >> 0x1f)) * 0x44 +
                    (uVar38 & ~((int)uVar38 >> 0x1f)) * 0x220 + iVar20 + 0x13488) == '\x0e') {
        uVar16 = uVar36 & 0xfffffff;
        uVar36 = uVar16 | (uint)(*(float *)(this + 0x60) < 6.5) << 0x1f;
        if (SUB41(uVar36 >> 0x1f,0)) {
          fVar33 = (float)VectorSignedToFloat((int)local_68,(byte)(uVar36 >> 0x16) & 3);
          *(undefined4 *)local_f4 = 0;
          uVar16 = uVar16 | (uint)(*(float *)(this + 0x3ffc) == 0.0) << 0x1e;
          *(float *)(this + 100) = fVar33 - 0.5;
          if (SUB41(uVar16 >> 0x1e,0)) {
            cRSound::Play((cRSound *)PTR__gRSound_001b61e0,0x30);
            iVar20 = *(int *)(this + 0x3f8);
          }
          fVar33 = *(float *)(this + 0x314) + *(float *)(this + 0x318);
          *(undefined4 *)(this + 0x4004) = 0xbea8f5c3;
          *(undefined4 *)pcVar9 = 0x3a81c2e4;
          uVar16 = uVar16 & 0xfffffff | (uint)(fVar33 < 1.0) << 0x1f | (uint)(fVar33 == 1.0) << 0x1e
          ;
          uVar36 = uVar16 | (uint)NAN(fVar33) << 0x1c;
          *(float *)(this + 0x314) = fVar33;
          bVar3 = (byte)(uVar16 >> 0x18);
          if (((bool)(bVar3 >> 6 & 1) || bVar3 >> 7 != ((byte)(uVar36 >> 0x1c) & 1)) ||
             (*(undefined4 *)(this + 0x314) = uVar10, this[0x40d] != (cRSubGoldy)0x0)) {
            fVar33 = *(float *)(this + 100);
          }
          else {
            if (this[0x374] == (cRSubGoldy)0x0) {
              *(undefined4 *)(this + 0x420) = uVar10;
              *(undefined4 *)(this + 0x41c) = uVar10;
            }
            else {
              *(undefined4 *)(this + 0x420) = *(undefined4 *)(*(int *)(this + 0x378) + 0x80);
              *(undefined4 *)(this + 0x41c) = *(undefined4 *)(this + 0x390);
            }
            fVar33 = *(float *)(this + 100);
            this[0x40d] = (cRSubGoldy)0x1;
            *(float *)(this + 0x414) = fVar33;
            this[0x374] = (cRSubGoldy)0x0;
            *(undefined4 *)(this + 0x424) = 0;
            this[0x43c] = (cRSubGoldy)0x0;
            this[0x43d] = (cRSubGoldy)0x0;
          }
          goto LAB_000298b0;
        }
      }
    }
    else {
      iVar20 = *(int *)(this + 0x3f8);
      fVar33 = *(float *)(this + 100);
    }
    *(undefined4 *)(this + 0x314) = 0;
  }
  else {
    iVar20 = *(int *)(this + 0x3f8);
    fVar33 = *(float *)(this + 100);
    *(undefined4 *)(this + 0x314) = 0;
  }
LAB_000298b0:
  if (*(int *)(this + 0x33c) == 0) {
    local_70 = *(undefined1 **)ptVar26;
    fStack_6c = *(float *)(this + 0x60);
    local_68 = *(float *)(this + 100);
    uVar38 = 0xdab;
    uVar16 = (uint)((float)local_70 + 4.0);
    if (6 < (int)uVar16) {
      uVar16 = 7;
    }
    uVar32 = (int)local_68;
    if (0xdaa < (int)local_68) {
      uVar32 = uVar38;
    }
    if (*(char *)((uVar16 & ~((int)uVar16 >> 0x1f)) * 0x44 +
                  (uVar32 & ~((int)uVar32 >> 0x1f)) * 0x220 + iVar20 + 0x13488) != '\x02') {
      local_70 = *(undefined1 **)ptVar26;
      fStack_6c = *(float *)(this + 0x60);
      local_68 = *(float *)(this + 100);
      uVar16 = (uint)((float)local_70 + 4.0);
      if (6 < (int)uVar16) {
        uVar16 = 7;
      }
      uVar32 = (int)local_68;
      if (0xdaa < (int)local_68) {
        uVar32 = uVar38;
      }
      if (*(char *)((uVar16 & ~((int)uVar16 >> 0x1f)) * 0x44 +
                    (uVar32 & ~((int)uVar32 >> 0x1f)) * 0x220 + iVar20 + 0x13488) != '\x04') {
        local_70 = *(undefined1 **)ptVar26;
        fStack_6c = *(float *)(this + 0x60);
        local_68 = *(float *)(this + 100);
        uVar16 = (uint)((float)local_70 + 4.0);
        if (6 < (int)uVar16) {
          uVar16 = 7;
        }
        uVar32 = (int)local_68;
        if (0xdaa < (int)local_68) {
          uVar32 = uVar38;
        }
        if (*(char *)((uVar16 & ~((int)uVar16 >> 0x1f)) * 0x44 +
                      (uVar32 & ~((int)uVar32 >> 0x1f)) * 0x220 + iVar20 + 0x13488) != '\x05') {
          local_70 = *(undefined1 **)ptVar26;
          fStack_6c = *(float *)(this + 0x60);
          local_68 = *(float *)(this + 100);
          uVar16 = (uint)((float)local_70 + 4.0);
          if (6 < (int)uVar16) {
            uVar16 = 7;
          }
          uVar32 = (int)local_68;
          if (0xdaa < (int)local_68) {
            uVar32 = uVar38;
          }
          if (*(char *)((uVar16 & ~((int)uVar16 >> 0x1f)) * 0x44 +
                        (uVar32 & ~((int)uVar32 >> 0x1f)) * 0x220 + iVar20 + 0x13488) != '\a') {
            local_70 = *(undefined1 **)ptVar26;
            fStack_6c = *(float *)(this + 0x60);
            local_68 = *(float *)(this + 100);
            uVar16 = (uint)((float)local_70 + 4.0);
            if (6 < (int)uVar16) {
              uVar16 = 7;
            }
            uVar32 = (uint)local_68;
            if (0xdaa < (int)uVar32) {
              uVar32 = uVar38;
            }
            if (*(char *)((uVar16 & ~((int)uVar16 >> 0x1f)) * 0x44 +
                          (uVar32 & ~((int)uVar32 >> 0x1f)) * 0x220 + iVar20 + 0x13488) != '\n') {
              local_70 = *(undefined1 **)ptVar26;
              fStack_6c = *(float *)(this + 0x60);
              local_68 = *(float *)(this + 100);
              uVar16 = (uint)((float)local_70 + 4.0);
              if (6 < (int)uVar16) {
                uVar16 = 7;
              }
              uVar32 = (int)local_68;
              if (0xdaa < (int)local_68) {
                uVar32 = uVar38;
              }
              if (*(char *)((uVar16 & ~((int)uVar16 >> 0x1f)) * 0x44 +
                            (uVar32 & ~((int)uVar32 >> 0x1f)) * 0x220 + iVar20 + 0x13488) != '\b') {
                local_70 = *(undefined1 **)ptVar26;
                fStack_6c = *(float *)(this + 0x60);
                local_68 = *(float *)(this + 100);
                uVar16 = (uint)((float)local_70 + 4.0);
                if (6 < (int)uVar16) {
                  uVar16 = 7;
                }
                uVar32 = (int)local_68;
                if (0xdaa < (int)local_68) {
                  uVar32 = uVar38;
                }
                if (*(char *)((uVar16 & ~((int)uVar16 >> 0x1f)) * 0x44 +
                              (uVar32 & ~((int)uVar32 >> 0x1f)) * 0x220 + iVar20 + 0x13488) != '\n')
                {
                  local_70 = *(undefined1 **)ptVar26;
                  fStack_6c = *(float *)(this + 0x60);
                  local_68 = *(float *)(this + 100);
                  uVar16 = (uint)((float)local_70 + 4.0);
                  if (6 < (int)uVar16) {
                    uVar16 = 7;
                  }
                  uVar32 = (int)local_68;
                  if (0xdaa < (int)local_68) {
                    uVar32 = uVar38;
                  }
                  if (*(char *)((uVar16 & ~((int)uVar16 >> 0x1f)) * 0x44 +
                                (uVar32 & ~((int)uVar32 >> 0x1f)) * 0x220 + iVar20 + 0x13488) !=
                      '\v') {
                    local_70 = *(undefined1 **)ptVar26;
                    fStack_6c = *(float *)(this + 0x60);
                    local_68 = *(float *)(this + 100);
                    uVar16 = (uint)((float)local_70 + 4.0);
                    if (6 < (int)uVar16) {
                      uVar16 = 7;
                    }
                    uVar32 = (int)local_68;
                    if (0xdaa < (int)local_68) {
                      uVar32 = uVar38;
                    }
                    if (*(char *)((uVar16 & ~((int)uVar16 >> 0x1f)) * 0x44 +
                                  (uVar32 & ~((int)uVar32 >> 0x1f)) * 0x220 + iVar20 + 0x13488) !=
                        '\r') goto LAB_00029c9c;
                  }
                }
              }
            }
          }
        }
      }
    }
    if ((this[0x40d] == (cRSubGoldy)0x0) &&
       (uVar36 = uVar36 & 0xfffffff | (uint)(*(float *)(this + 0x60) == 0.98) << 0x1e |
                 (uint)(0.98 <= *(float *)(this + 0x60)) << 0x1d, bVar3 = (byte)(uVar36 >> 0x18),
       !(bool)(bVar3 >> 5 & 1) || (bool)(bVar3 >> 6))) {
      local_70 = *(undefined1 **)ptVar26;
      fStack_6c = *(float *)(this + 0x60);
      local_68 = *(float *)(this + 100);
      uVar38 = 0xdab;
      *(float *)(this + 0x348) = *(float *)(iVar20 + 0x4c) * 0.037037037;
      uVar16 = (uint)((float)local_70 + 4.0);
      if (6 < (int)uVar16) {
        uVar16 = 7;
      }
      uVar32 = (int)local_68;
      if (0xdaa < (int)local_68) {
        uVar32 = uVar38;
      }
      if (*(char *)((uVar16 & ~((int)uVar16 >> 0x1f)) * 0x44 +
                    (uVar32 & ~((int)uVar32 >> 0x1f)) * 0x220 + iVar20 + 0x13488) != '\x02') {
        local_70 = *(undefined1 **)ptVar26;
        fStack_6c = *(float *)(this + 0x60);
        local_68 = *(float *)(this + 100);
        uVar16 = (uint)((float)local_70 + 4.0);
        if (6 < (int)uVar16) {
          uVar16 = 7;
        }
        uVar32 = (int)local_68;
        if (0xdaa < (int)local_68) {
          uVar32 = uVar38;
        }
        if (*(char *)((uVar16 & ~((int)uVar16 >> 0x1f)) * 0x44 +
                      (uVar32 & ~((int)uVar32 >> 0x1f)) * 0x220 + iVar20 + 0x13488) != '\x05') {
          local_70 = *(undefined1 **)ptVar26;
          fStack_6c = *(float *)(this + 0x60);
          local_68 = *(float *)(this + 100);
          uVar16 = (uint)((float)local_70 + 4.0);
          if (6 < (int)uVar16) {
            uVar16 = 7;
          }
          uVar32 = (int)local_68;
          if (0xdaa < (int)local_68) {
            uVar32 = uVar38;
          }
          if (*(char *)((uVar16 & ~((int)uVar16 >> 0x1f)) * 0x44 +
                        (uVar32 & ~((int)uVar32 >> 0x1f)) * 0x220 + iVar20 + 0x13488) != '\b') {
            local_70 = *(undefined1 **)ptVar26;
            fStack_6c = *(float *)(this + 0x60);
            local_68 = *(float *)(this + 100);
            uVar16 = (uint)((float)local_70 + 4.0);
            if (6 < (int)uVar16) {
              uVar16 = 7;
            }
            uVar32 = (int)local_68;
            if (0xdaa < (int)local_68) {
              uVar32 = uVar38;
            }
            if (*(char *)((uVar16 & ~((int)uVar16 >> 0x1f)) * 0x44 +
                          (uVar32 & ~((int)uVar32 >> 0x1f)) * 0x220 + iVar20 + 0x13488) != '\v') {
              *(undefined4 *)(this + 0x33c) = 2;
              *(undefined4 *)(this + 0x340) = 0xbf800000;
              goto LAB_00029c9c;
            }
          }
        }
      }
      *(undefined4 *)(this + 0x33c) = 1;
      *(undefined4 *)(this + 0x340) = 0x3f800000;
    }
  }
LAB_00029c9c:
  uVar36 = uVar36 & 0xfffffff;
  if (*(float *)(this + 0x1bc) != 0.0) {
    fVar34 = *(float *)(this + 0x1bc) + *(float *)(this + 0x1c0);
    uVar36 = uVar36 | (uint)(fVar34 < 1.0) << 0x1f;
    *(float *)(this + 0x1bc) = fVar34;
    if (fVar34 != 1.0 && SUB41(uVar36 >> 0x1f,0) == NAN(fVar34)) {
      *(undefined4 *)(this + 0x1bc) = 0;
    }
  }
  fVar34 = (float)VectorSignedToFloat(*(undefined4 *)(iVar20 + 0x70),(byte)(uVar36 >> 0x16) & 3);
  uVar36 = uVar36 & 0xfffffff;
  uVar38 = uVar36 | (uint)(fVar33 < fVar34) << 0x1f;
  uVar16 = uVar38 | (uint)(NAN(fVar33) || NAN(fVar34)) << 0x1c;
  if (((byte)(uVar38 >> 0x1f) == ((byte)(uVar16 >> 0x1c) & 1)) && (this[0x40d] == (cRSubGoldy)0x0))
  {
    if (this[0x430] != (cRSubGoldy)0x0) goto LAB_00029df8;
    if (*(int *)(iVar20 + 0x58) == 4) {
      fVar33 = ((1.0 - (fVar33 - fVar34) / *(float *)local_f4) * 0.016666668) / 60.0;
      *(float *)(this + 0x2d0) = *(float *)(this + 0x2d0) + fVar33;
      fVar33 = fVar33 + *(float *)(this + 0x2e4);
      uVar36 = uVar36 | (uint)(fVar33 < 1.0) << 0x1f;
      uVar16 = uVar36 | (uint)NAN(fVar33) << 0x1c;
      *(float *)(this + 0x2e4) = fVar33;
      if ((byte)(uVar36 >> 0x1f) == ((byte)(uVar16 >> 0x1c) & 1)) {
        fVar33 = fVar33 - 1.0;
        iVar21 = *(int *)(this + 0x2d8);
        iVar22 = iVar21 + 1;
        *(int *)(this + 0x2d8) = iVar22;
        if (0x3b < iVar22) {
          *(int *)(this + 0x2d8) = iVar21 + -0x3b;
        }
        *(float *)(this + 0x2e4) = fVar33;
        if (0x3b < iVar22) {
          *(int *)(this + 0x2d4) = *(int *)(this + 0x2d4) + 1;
        }
      }
      *(int *)(this + 0x2dc) = (int)(fVar33 * 100.0);
      *(int *)(this + 0x2e0) = (int)(fVar33 * 1000.0);
    }
    *(undefined4 *)(this + 0x434) = 0;
    *(undefined4 *)(this + 0x438) = 0x3c888889;
    this[0x43e] = (cRSubGoldy)0x0;
    puVar6 = PTR__gVoiceManager_001b61d8;
    fVar33 = *(float *)(iVar20 + 0x4c) * 0.17;
    fVar34 = *(float *)local_f4;
    uVar36 = uVar16 & 0xfffffff;
    uVar16 = uVar36 | (uint)(fVar34 < fVar33) << 0x1f;
    if (!SUB41(uVar16 >> 0x1f,0)) {
      fVar33 = *(float *)(iVar20 + 0x4c) * 0.5;
      uVar36 = uVar36 | (uint)(fVar34 < fVar33) << 0x1f | (uint)(fVar34 == fVar33) << 0x1e;
      uVar16 = uVar36 | (uint)(NAN(fVar34) || NAN(fVar33)) << 0x1c;
      bVar3 = (byte)(uVar36 >> 0x18);
      if ((bool)(bVar3 >> 6 & 1) || bVar3 >> 7 != ((byte)(uVar16 >> 0x1c) & 1)) {
        fVar33 = fVar34;
      }
    }
    *(float *)local_f4 = fVar33;
    cRVoiceManager::ReSet((cRVoiceManager *)puVar6);
    if (*(int *)(this + 0x25d0) == 1) {
      uVar16 = uVar16 & 0xfffffff | (uint)(*(float *)(this + 0x25c4) < 0.94) << 0x1f;
      if (SUB41(uVar16 >> 0x1f,0)) {
        *(undefined4 *)(this + 0x25c4) = 0x3f70a3d7;
      }
    }
    *(undefined4 *)(this + 0x3f94) = 5;
    cRSound::Play((cRSound *)PTR__gRSound_001b61e0,0);
    this[0x40c] = (cRSubGoldy)0x0;
    if (this[0x430] == (cRSubGoldy)0x0) {
      uVar36 = *(uint *)PTR__Game_001b60b8;
      bVar31 = *(int *)(uVar36 + 100) == 1;
      if (bVar31) {
        uVar36 = (uint)(byte)(&DAT_00353544)[uVar36];
      }
      if (!bVar31 || uVar36 != 0) goto switchD_0002ce0c_caseD_6;
      MacOFSetHighScore();
      puVar6 = PTR__gConfig_001b60d4;
      if (((0x13 < *(int *)(PTR__gConfig_001b60d4 + 0xc)) &&
          (MacOFAddAchievement(0xc), 99 < *(int *)(puVar6 + 0xc))) &&
         (MacOFAddAchievement(0xd), 499 < *(int *)(puVar6 + 0xc))) {
        MacOFAddAchievement(0xe);
      }
      iVar20 = *(int *)PTR__Game_001b60b8;
      iVar21 = *(int *)(iVar20 + 0x72bd0);
      if (iVar21 != 0) {
        if (iVar21 == 1) {
          if ((*(int *)(iVar20 + 0x72bb8) == 0x3c) && (*(int *)(iVar20 + 0x72bb4) == 0x3c)) {
            MacOFAddAchievement(0x1c);
          }
          puVar6 = PTR__Game_001b60b8;
          if ((*(int *)(*(int *)PTR__Game_001b60b8 + 0x72bb8) == 100) &&
             ((*(int *)(*(int *)PTR__Game_001b60b8 + 0x72bb4) != 100 ||
              (MacOFAddAchievement(0x1f), *(int *)(*(int *)puVar6 + 0x72bb8) == 100)))) {
            MacOFAddAchievement(0x1e);
          }
          if (*(int *)(*(int *)PTR__Game_001b60b8 + 0x72bb4) == 100) {
            MacOFAddAchievement(0x1d);
            fVar33 = *(float *)(this + 100);
            iVar20 = *(int *)(this + 0x3f8);
            goto LAB_00029df8;
          }
        }
        else if (iVar21 == 4) {
          if ((*(int *)(iVar20 + 0x72bd4) == 1) &&
             (*(int *)(iVar20 + 0x82294) * 6000 + *(int *)(iVar20 + 0x82298) * 100 +
              *(int *)(iVar20 + 0x8229c) < 0x1004)) {
            MacOFAddAchievement(0x12);
          }
          iVar20 = *(int *)PTR__Game_001b60b8;
          if ((*(int *)(iVar20 + 0x72bd4) == 6) &&
             (*(int *)(iVar20 + 0x82294) * 6000 + *(int *)(iVar20 + 0x82298) * 100 +
              *(int *)(iVar20 + 0x8229c) < 0x14b4)) {
            MacOFAddAchievement(0x13);
          }
          iVar20 = *(int *)PTR__Game_001b60b8;
          if ((*(int *)(iVar20 + 0x72bd4) == 0xb) &&
             (*(int *)(iVar20 + 0x82294) * 6000 + *(int *)(iVar20 + 0x82298) * 100 +
              *(int *)(iVar20 + 0x8229c) < 0x1c20)) {
            MacOFAddAchievement(0x14);
          }
          iVar20 = *(int *)PTR__Game_001b60b8;
          if ((*(int *)(iVar20 + 0x72bd4) == 0x10) &&
             (*(int *)(iVar20 + 0x82294) * 6000 + *(int *)(iVar20 + 0x82298) * 100 +
              *(int *)(iVar20 + 0x8229c) < 0x1e14)) {
            MacOFAddAchievement(0x15);
          }
          iVar20 = *(int *)PTR__Game_001b60b8;
          if ((*(int *)(iVar20 + 0x72bd4) == 0x15) &&
             (*(int *)(iVar20 + 0x82294) * 6000 + *(int *)(iVar20 + 0x82298) * 100 +
              *(int *)(iVar20 + 0x8229c) < 0x29cc)) {
            MacOFAddAchievement(0x16);
          }
          iVar20 = *(int *)PTR__Game_001b60b8;
          if ((*(int *)(iVar20 + 0x72bd4) == 0x1a) &&
             (*(int *)(iVar20 + 0x82294) * 6000 + *(int *)(iVar20 + 0x82298) * 100 +
              *(int *)(iVar20 + 0x8229c) < 0x1bbc)) {
            MacOFAddAchievement(0x17);
          }
          iVar20 = *(int *)PTR__Game_001b60b8;
          if ((*(int *)(iVar20 + 0x72bd4) == 0x1f) &&
             (*(int *)(iVar20 + 0x82294) * 6000 + *(int *)(iVar20 + 0x82298) * 100 +
              *(int *)(iVar20 + 0x8229c) < 7000)) {
            MacOFAddAchievement(0x18);
          }
          iVar20 = *(int *)PTR__Game_001b60b8;
          if ((*(int *)(iVar20 + 0x72bd4) == 0x24) &&
             (*(int *)(iVar20 + 0x82294) * 6000 + *(int *)(iVar20 + 0x82298) * 100 +
              *(int *)(iVar20 + 0x8229c) < 5000)) {
            MacOFAddAchievement(0x19);
          }
          iVar20 = *(int *)PTR__Game_001b60b8;
          if ((*(int *)(iVar20 + 0x72bd4) == 0x29) &&
             (*(int *)(iVar20 + 0x82294) * 6000 + *(int *)(iVar20 + 0x82298) * 100 +
              *(int *)(iVar20 + 0x8229c) < 0x1c84)) {
            MacOFAddAchievement(0x1a);
          }
          iVar20 = *(int *)PTR__Game_001b60b8;
          if ((*(int *)(iVar20 + 0x72bd4) == 0x2e) &&
             (*(int *)(iVar20 + 0x82294) * 6000 + *(int *)(iVar20 + 0x82298) * 100 +
              *(int *)(iVar20 + 0x8229c) < 0x1c20)) {
            MacOFAddAchievement(0x1b);
            fVar33 = *(float *)(this + 100);
            iVar20 = *(int *)(this + 0x3f8);
            goto LAB_00029df8;
          }
        }
        goto switchD_0002ce0c_caseD_6;
      }
      if (*(int *)(&DAT_00364944 + iVar20) == 0) {
        switch(*(undefined4 *)(iVar20 + 0x72bd4)) {
        case 5:
          MacOFAddAchievement(0);
          fVar33 = *(float *)(this + 100);
          iVar20 = *(int *)(this + 0x3f8);
          break;
        default:
          goto switchD_0002ce0c_caseD_6;
        case 10:
          MacOFAddAchievement(1);
          fVar33 = *(float *)(this + 100);
          iVar20 = *(int *)(this + 0x3f8);
          break;
        case 0xf:
          MacOFAddAchievement(2);
          fVar33 = *(float *)(this + 100);
          iVar20 = *(int *)(this + 0x3f8);
          break;
        case 0x14:
          MacOFAddAchievement(3);
          fVar33 = *(float *)(this + 100);
          iVar20 = *(int *)(this + 0x3f8);
          break;
        case 0x19:
          MacOFAddAchievement(4);
          MacOFAddAchievement(5);
          fVar33 = *(float *)(this + 100);
          iVar20 = *(int *)(this + 0x3f8);
          break;
        case 0x1e:
          MacOFAddAchievement(6);
          fVar33 = *(float *)(this + 100);
          iVar20 = *(int *)(this + 0x3f8);
          break;
        case 0x23:
          MacOFAddAchievement(7);
          fVar33 = *(float *)(this + 100);
          iVar20 = *(int *)(this + 0x3f8);
          break;
        case 0x28:
          MacOFAddAchievement(8);
          fVar33 = *(float *)(this + 100);
          iVar20 = *(int *)(this + 0x3f8);
          break;
        case 0x2d:
          MacOFAddAchievement(9);
          fVar33 = *(float *)(this + 100);
          iVar20 = *(int *)(this + 0x3f8);
          break;
        case 0x32:
          MacOFAddAchievement(10);
          MacOFAddAchievement(0xb);
          fVar33 = *(float *)(this + 100);
          iVar20 = *(int *)(this + 0x3f8);
        }
      }
      else {
        if (*(int *)(&DAT_00364944 + iVar20) != 1) goto switchD_0002ce0c_caseD_6;
        if (*(int *)(iVar20 + 0x72bd4) == 5) {
          MacOFAddAchievement(0xf);
          fVar33 = *(float *)(this + 100);
          iVar20 = *(int *)(this + 0x3f8);
        }
        else {
          if (*(int *)(iVar20 + 0x72bd4) != 10) goto switchD_0002ce0c_caseD_6;
          MacOFAddAchievement(0x10);
          MacOFAddAchievement(0x11);
          fVar33 = *(float *)(this + 100);
          iVar20 = *(int *)(this + 0x3f8);
        }
      }
    }
    else {
switchD_0002ce0c_caseD_6:
      iVar20 = *(int *)(this + 0x3f8);
      fVar33 = *(float *)(this + 100);
    }
LAB_00029df8:
    local_100 = this + 0x438;
    pcVar9 = this + 0x434;
    this[0x430] = (cRSubGoldy)0x1;
    fVar34 = (float)VectorSignedToFloat(*(undefined4 *)(iVar20 + 0x70),(byte)(uVar16 >> 0x16) & 3);
    fVar34 = fVar34 + 2.5;
    uVar36 = uVar16 & 0xfffffff | (uint)(fVar33 < fVar34) << 0x1f | (uint)(fVar33 == fVar34) << 0x1e
    ;
    bVar3 = (byte)(uVar36 >> 0x18);
    if (!(bool)(bVar3 >> 6 & 1) && (bool)(bVar3 >> 7) == (NAN(fVar33) || NAN(fVar34))) {
      fVar33 = *(float *)local_f4 +
               *(float *)(iVar20 + 0x4c) * *(float *)(iVar20 + 0x4c) * 0.004 * -2.0;
      uVar36 = uVar16 & 0xfffffff | (uint)(fVar33 < 0.0) << 0x1f;
      *(float *)local_f4 = fVar33;
      if (SUB41(uVar36 >> 0x1f,0)) {
        *(undefined4 *)local_f4 = 0;
      }
    }
    pcVar11 = this + 0x25b8;
    fVar33 = *(float *)pcVar11;
    fVar34 = 2.0;
    *(float *)pcVar11 = fVar33 + *(float *)(this + 0x25bc);
    if (1.0 < fVar33 + *(float *)(this + 0x25bc)) {
      *(undefined4 *)pcVar11 = 0;
    }
    *(float *)pcVar9 = *(float *)pcVar9 + *(float *)local_100;
    *(undefined4 *)(&DAT_00303aa8 + iVar20) = 2;
    fVar33 = *(float *)pcVar9;
    uVar36 = uVar36 & 0xfffffff | (uint)(fVar33 < 2.0) << 0x1f | (uint)(fVar33 == 2.0) << 0x1e;
    uVar16 = uVar36 | (uint)NAN(fVar33) << 0x1c;
    bVar3 = (byte)(uVar36 >> 0x18);
    if ((bool)(bVar3 >> 6 & 1) || bVar3 >> 7 != ((byte)(uVar16 >> 0x1c) & 1)) {
LAB_00029edc:
      uVar36 = uVar16 & 0xfffffff | (uint)(fVar33 < 5.0) << 0x1f | (uint)(fVar33 == 5.0) << 0x1e;
      uVar16 = uVar36 | (uint)NAN(fVar33) << 0x1c;
      bVar3 = (byte)(uVar36 >> 0x18);
      if ((bool)(bVar3 >> 6 & 1) || bVar3 >> 7 != ((byte)(uVar16 >> 0x1c) & 1)) goto LAB_0002a25c;
      this_00 = *(cRSubGame **)(this + 0x3f8);
    }
    else {
      if (this[0x43e] == (cRSubGoldy)0x0) {
        this[0x43e] = (cRSubGoldy)0x1;
        cRVoiceManager::Play((cRVoiceManager *)PTR__gVoiceManager_001b61d8,8,2,-1);
        fVar33 = *(float *)pcVar9;
        uVar36 = uVar16 & 0xfffffff | (uint)(fVar33 < fVar34) << 0x1f |
                 (uint)(fVar33 == fVar34) << 0x1e;
        uVar16 = uVar36 | (uint)(NAN(fVar33) || NAN(fVar34)) << 0x1c;
        bVar3 = (byte)(uVar36 >> 0x18);
        if ((bool)(bVar3 >> 6 & 1) || bVar3 >> 7 != ((byte)(uVar16 >> 0x1c) & 1)) goto LAB_00029edc;
      }
      this_00 = *(cRSubGame **)(this + 0x3f8);
      if (1 < *(uint *)(this_00 + 0x58)) goto LAB_00029edc;
      if ((this_00[0x3052cc] != (cRSubGame)0x0) &&
         ((*(uint *)(*(int *)(this + 0x42c) + 4) & 0x4000) != 0)) {
        *(undefined4 *)pcVar9 = 0x40a33333;
      }
      if (*(int *)(this_00 + 0x3052c8) != 5) {
        fVar33 = *(float *)pcVar9;
        goto LAB_00029edc;
      }
      fVar33 = 5.1;
      *(undefined4 *)pcVar9 = 0x40a33333;
    }
    if ((*(uint *)(this_00 + 0x58) < 2) && (*(int *)(this_00 + 0x3052c8) != 5)) {
      fVar33 = fVar33 - *(float *)local_100;
      uVar36 = uVar16 & 0xfffffff | (uint)(fVar33 < 5.0) << 0x1f | (uint)(fVar33 == 5.0) << 0x1e;
      uVar16 = uVar36 | (uint)NAN(fVar33) << 0x1c;
      *(float *)pcVar9 = fVar33;
      bVar3 = (byte)(uVar36 >> 0x18);
      if ((bool)(bVar3 >> 6 & 1) || bVar3 >> 7 != ((byte)(uVar16 >> 0x1c) & 1)) goto LAB_0002a25c;
    }
    puVar6 = PTR__Game_001b60b8;
    iVar20 = *(int *)(*(int *)PTR__Game_001b60b8 + 0x24);
    if (iVar20 == 0) {
      cRFade::Start((cRFade *)(*(int *)PTR__Game_001b60b8 + 0x24),(_func_void *)0x0);
    }
    else if (iVar20 == 4) {
      if (*(int *)(this_00 + 0x3052c8) != 0) {
        cRCompletion::UnInit((cRCompletion *)(this_00 + 0x3052b8));
        this_00 = *(cRSubGame **)(this + 0x3f8);
      }
      if (*(int *)(this_00 + 0x58) == 0) {
        if (*(int *)(this_00 + 0x5c) ==
            *(int *)(&DAT_00364960 +
                    *(int *)(&DAT_00364944 + *(int *)puVar6) * 0x8e6c + *(int *)puVar6)) {
          cRSubGame::Complete(this_00,true);
          *(undefined4 *)(*(int *)puVar6 + 0x160) = 0x1d;
          *(undefined4 *)(*(int *)puVar6 + 0x15c) = 0x1a;
          *(undefined4 *)(PTR__gConfig_001b60d4 + 0xcc) = 0;
          return;
        }
        cRSubGame::Complete(this_00,false);
        *(undefined4 *)(&DAT_00303aa8 + *(int *)(this + 0x3f8)) = 1;
      }
      else {
        cRSubGame::Complete(this_00,true);
      }
      puVar6 = PTR__Game_001b60b8;
      if (*(int *)(*(int *)(this + 0x3f8) + 0x58) != 7) {
        if ((&DAT_002e09cd)[*(int *)(this + 0x3f8)] != '\0') {
          *(undefined4 *)(*(int *)PTR__Game_001b60b8 + 0x160) =
               *(undefined4 *)(*(int *)PTR__Game_001b60b8 + 0x15c);
          *(undefined4 *)(*(int *)puVar6 + 0x15c) = 0x1a;
          return;
        }
        *(undefined4 *)(*(int *)PTR__Game_001b60b8 + 0x160) =
             *(undefined4 *)(*(int *)PTR__Game_001b60b8 + 0x15c);
        *(undefined4 *)(*(int *)puVar6 + 0x15c) = 0x1b;
        return;
      }
      *(undefined4 *)(*(int *)PTR__Game_001b60b8 + 0x15c) = 0x1a;
      *(undefined4 *)(*(int *)puVar6 + 0x160) = 2;
      return;
    }
  }
  else {
    cVar24 = this[0x40c];
    bVar31 = cVar24 == (cRSubGoldy)0x0;
    if (bVar31) {
      cVar24 = this[0x2c0];
    }
    if (bVar31 && cVar24 == (cRSubGoldy)0x0) {
      fVar33 = *(float *)(iVar20 + 0x4c) * 0.17;
      fVar34 = *(float *)local_f4;
      uVar16 = uVar36 | (uint)(fVar34 < fVar33) << 0x1f;
      if (!SUB41(uVar16 >> 0x1f,0)) {
        fVar33 = *(float *)(iVar20 + 0x4c) * 0.5;
        uVar36 = uVar36 | (uint)(fVar34 < fVar33) << 0x1f | (uint)(fVar34 == fVar33) << 0x1e;
        uVar16 = uVar36 | (uint)(NAN(fVar34) || NAN(fVar33)) << 0x1c;
        bVar3 = (byte)(uVar36 >> 0x18);
        if ((bool)(bVar3 >> 6 & 1) || bVar3 >> 7 != ((byte)(uVar16 >> 0x1c) & 1)) {
          fVar33 = fVar34;
        }
      }
      *(float *)local_f4 = fVar33;
    }
  }
LAB_0002a25c:
  uVar10 = *(undefined4 *)ptVar26;
  uStack_54 = *(undefined4 *)(this + 0x60);
  uStack_50 = *(undefined4 *)(this + 100);
  if (this[0x374] != (cRSubGoldy)0x0) {
    *(undefined4 *)ptVar26 = *(undefined4 *)(this + 0x3a0);
    *(undefined4 *)(this + 0x60) = *(undefined4 *)(this + 0x3a4);
    *(undefined4 *)(this + 100) = *(undefined4 *)(this + 0x3a8);
  }
  local_58 = uVar10;
  cRSubHover::AI((cRSubHover *)(this + 0x25c4));
  puVar6 = PTR__Game_001b60b8;
  if (this[0x430] != (cRSubGoldy)0x0) {
    iVar20 = *(int *)PTR__Game_001b60b8;
    *(undefined4 *)(iVar20 + 0x280) = *(undefined4 *)(iVar20 + 0x100);
    *(undefined4 *)(iVar20 + 0x284) = *(undefined4 *)(iVar20 + 0x104);
    *(undefined4 *)(iVar20 + 0x288) = *(undefined4 *)(iVar20 + 0x108);
    *(undefined4 *)(iVar20 + 0x28c) = *(undefined4 *)(iVar20 + 0x10c);
    *(undefined4 *)(iVar20 + 0x290) = *(undefined4 *)(iVar20 + 0x110);
    *(undefined4 *)(iVar20 + 0x294) = *(undefined4 *)(iVar20 + 0x114);
    *(undefined4 *)(iVar20 + 0x298) = *(undefined4 *)(iVar20 + 0x118);
    *(undefined4 *)(iVar20 + 0x29c) = *(undefined4 *)(iVar20 + 0x11c);
    *(undefined4 *)(iVar20 + 0x2a0) = *(undefined4 *)(iVar20 + 0x120);
    *(undefined4 *)(iVar20 + 0x2a4) = *(undefined4 *)(iVar20 + 0x124);
    *(undefined4 *)(iVar20 + 0x2a8) = *(undefined4 *)(iVar20 + 0x128);
    *(undefined4 *)(iVar20 + 0x2ac) = *(undefined4 *)(iVar20 + 300);
    *(undefined4 *)(iVar20 + 0x2b0) = *(undefined4 *)(iVar20 + 0x130);
    *(undefined4 *)(iVar20 + 0x2b4) = *(undefined4 *)(iVar20 + 0x134);
    *(undefined4 *)(iVar20 + 0x2b8) = *(undefined4 *)(iVar20 + 0x138);
    *(undefined4 *)(iVar20 + 700) = *(undefined4 *)(iVar20 + 0x13c);
    *(float *)(*(int *)puVar6 + 0x2b4) = *(float *)(*(int *)puVar6 + 0x2b4) - 1.0;
  }
  cRDamageGuage::AI((cRDamageGuage *)(this + 0x3b4));
  cRProgressBar::AI();
  fVar33 = *(float *)(this + 0x25d8);
  fVar37 = *(float *)(this + 0x25dc);
  fVar34 = *(float *)(this + 0x25e0);
  pcVar9 = this + 0x27d8;
  *(undefined4 *)pcVar9 = *(undefined4 *)ptVar26;
  *(undefined4 *)(this + 0x27dc) = *(undefined4 *)(this + 0x60);
  *(undefined4 *)(this + 0x27e0) = *(undefined4 *)(this + 100);
  iVar20 = *(int *)(this + 0x3f8);
  *(float *)pcVar9 =
       fVar37 * *(float *)(this + 0x3c) + fVar33 * *(float *)(this + 0x2c) +
       fVar34 * *(float *)(this + 0x4c) + *(float *)pcVar9;
  *(float *)(this + 0x27dc) =
       fVar37 * *(float *)(this + 0x40) + fVar33 * *(float *)(this + 0x30) +
       fVar34 * *(float *)(this + 0x50) + *(float *)(this + 0x27dc);
  *(float *)(this + 0x27e0) =
       fVar37 * *(float *)(this + 0x44) + fVar33 * *(float *)(this + 0x34) +
       fVar34 * *(float *)(this + 0x54) + *(float *)(this + 0x27e0);
  if (0 < *(int *)(this + 0x3cc)) {
    *(int *)(this + 0x3cc) = *(int *)(this + 0x3cc) + -1;
  }
  if (this[0x374] != (cRSubGoldy)0x0) {
    *(undefined4 *)(this + 0x5c) = uVar10;
  }
  fVar33 = *(float *)(iVar20 + 0x4c) * 0.037037037;
  *(float *)(this + 0x348) = fVar33;
  if (*(int *)(this + 0x33c) != 0) {
    fVar33 = fVar33 + *(float *)(this + 0x344);
    uVar36 = uVar16 & 0xfffffff | (uint)(fVar33 < 1.0) << 0x1f | (uint)(fVar33 == 1.0) << 0x1e;
    uVar16 = uVar36 | (uint)NAN(fVar33) << 0x1c;
    *(float *)(this + 0x344) = fVar33;
    bVar3 = (byte)(uVar36 >> 0x18);
    if (!(bool)(bVar3 >> 6 & 1) && bVar3 >> 7 == ((byte)(uVar16 >> 0x1c) & 1)) {
      *(undefined4 *)(this + 0x344) = 0;
      *(undefined4 *)(this + 0x33c) = 0;
    }
  }
  if (*(int *)(this + 0x350) != 0) {
    fVar33 = *(float *)(this + 0x358) + *(float *)(this + 0x35c);
    uVar36 = uVar16 & 0xfffffff | (uint)(fVar33 < 1.0) << 0x1f | (uint)(fVar33 == 1.0) << 0x1e;
    uVar16 = uVar36 | (uint)NAN(fVar33) << 0x1c;
    *(float *)(this + 0x358) = fVar33;
    bVar3 = (byte)(uVar36 >> 0x18);
    if (!(bool)(bVar3 >> 6 & 1) && bVar3 >> 7 == ((byte)(uVar16 >> 0x1c) & 1)) {
      *(undefined4 *)(this + 0x358) = 0;
      *(undefined4 *)(this + 0x350) = 0;
    }
  }
  fVar33 = *(float *)(iVar20 + 0x4c) * 0.022222223;
  fVar34 = *(float *)(this + 0x364);
  uVar16 = uVar16 & 0xfffffff;
  uVar36 = uVar16 | (uint)(fVar34 < 0.0) << 0x1f | (uint)(fVar34 == 0.0) << 0x1e;
  uVar38 = uVar36 | (uint)NAN(fVar34) << 0x1c;
  *(float *)(this + 0x368) = fVar33;
  bVar3 = (byte)(uVar36 >> 0x18);
  if (!(bool)(bVar3 >> 6 & 1) && bVar3 >> 7 == ((byte)(uVar38 >> 0x1c) & 1)) {
    fVar33 = fVar33 + fVar34;
    uVar36 = uVar16 | (uint)(fVar33 < 1.0) << 0x1f | (uint)(fVar33 == 1.0) << 0x1e;
    uVar38 = uVar36 | (uint)NAN(fVar33) << 0x1c;
    *(float *)(this + 0x364) = fVar33;
    bVar3 = (byte)(uVar36 >> 0x18);
    if ((bool)(bVar3 >> 6 & 1) || bVar3 >> 7 != ((byte)(uVar38 >> 0x1c) & 1)) {
      if (*(int *)(this + 0x138) == 1) {
        iVar20 = 0;
        fVar33 = *(float *)(this + 0x144) + *(float *)(this + 0x140);
        fVar34 = *(float *)(this + 0x148) + *(float *)(this + 0x14c);
        *(float *)(this + 0x144) = fVar33;
        uVar36 = uVar16 | (uint)(fVar34 < 6.2831855) << 0x1f | (uint)(fVar34 == 6.2831855) << 0x1e;
        uVar38 = uVar36 | (uint)NAN(fVar34) << 0x1c;
        *(float *)(this + 0x148) = fVar34;
        bVar3 = (byte)(uVar36 >> 0x18);
        pcVar9 = this;
        if (!(bool)(bVar3 >> 6 & 1) && bVar3 >> 7 == ((byte)(uVar38 >> 0x1c) & 1)) {
          fVar34 = fVar34 - 6.2831855;
          *(float *)(this + 0x148) = fVar34;
        }
        while( true ) {
          fVar37 = (float)VectorSignedToFloat(iVar20,(byte)(uVar38 >> 0x16) & 3);
          fVar35 = 7.0;
          iVar20 = iVar20 + 1;
          *(float *)(*(int *)(pcVar9 + 0x150) + 0x50) = fVar33;
          iVar21 = *(int *)(pcVar9 + 0x150);
          fVar34 = fVar34 + (fVar37 / 25.0) * 6.2831855;
          fVar33 = (float)Sin(fVar34);
          *(float *)(iVar21 + 0x48) = fVar33 * fVar35;
          iVar21 = *(int *)(pcVar9 + 0x150);
          fVar33 = (float)Cos(fVar34);
          *(float *)(iVar21 + 0x4c) = fVar33 * fVar35;
          if (iVar20 == 0x19) break;
          fVar33 = *(float *)(this + 0x144);
          fVar34 = *(float *)(this + 0x148);
          pcVar9 = pcVar9 + 4;
        }
        iVar20 = *(int *)(this + 0x3f8);
      }
    }
    else {
      *(undefined4 *)(this + 0x364) = 0;
      if (*(int *)(this + 0x138) == 1) {
        cRSprite::Kill(*(cRSprite **)(this + 0x150));
        iVar20 = 4;
        do {
          iVar21 = iVar20 + 4;
          cRSprite::Kill(*(cRSprite **)(this + iVar20 + 0x150));
          iVar20 = iVar21;
        } while (iVar21 != 100);
        iVar20 = *(int *)(this + 0x3f8);
        *(undefined4 *)(this + 0x138) = 0;
      }
    }
  }
  iVar21 = *(int *)(iVar20 + 0x58);
  bVar31 = iVar21 == 4;
  if (bVar31) {
    iVar21 = *(int *)(&DAT_002a0680 + *(int *)(iVar20 + 0x5c) * 0x38 + iVar20);
  }
  if ((bVar31 && iVar21 == 1) && ((&DAT_002e09cc)[iVar20] == '\0')) {
    iVar21 = *(int *)(this + 0x2ec);
    if (iVar21 == 0) {
LAB_0002c0a0:
      AI()::GhostZ = (float)MathType16to32(*(short *)(&DAT_002c0f7a + iVar20),32.0);
    }
    else {
      if (*(int *)(&DAT_002e09d8 + iVar20) < *(int *)(&DAT_002c0f74 + iVar20)) {
        iVar21 = *(int *)(&DAT_002e09d8 + iVar20) - iVar21;
      }
      else {
        iVar21 = *(int *)(&DAT_002c0f74 + iVar20) - iVar21;
      }
      if (iVar21 + *(int *)(&DAT_002c0f2c + iVar20) == 0) goto LAB_0002c0a0;
      fVar33 = (float)MathType16to32(*(short *)(&DAT_002c0f7a +
                                               (iVar21 + *(int *)(&DAT_002c0f2c + iVar20)) * 6 +
                                               iVar20),32.0);
      AI()::GhostZ = fVar33 + AI()::GhostZ;
    }
    if ((&DAT_002e09cc)[*(int *)(this + 0x3f8)] == '\0') {
      fVar33 = *(float *)(this + 100);
    }
    else {
      fVar33 = *(float *)(this + 100);
      AI()::GhostZ = fVar33;
    }
    fVar34 = AI()::GhostZ;
    fVar33 = fVar33 + 20.0;
    uVar36 = uVar38 & 0xfffffff | (uint)(fVar33 < AI()::GhostZ) << 0x1f |
             (uint)(fVar33 == AI()::GhostZ) << 0x1e;
    uVar38 = uVar36 | (uint)(NAN(fVar33) || NAN(AI()::GhostZ)) << 0x1c;
    *(uint *)(*(int *)(this + 0x8c) + 4) = *(uint *)(*(int *)(this + 0x8c) + 4) | 0x40;
    bVar3 = (byte)(uVar36 >> 0x18);
    if (!(bool)(bVar3 >> 6 & 1) && bVar3 >> 7 == ((byte)(uVar38 >> 0x1c) & 1)) {
      fVar33 = fVar34;
    }
    *(uint *)(*(int *)(this + 0x90) + 4) = *(uint *)(*(int *)(this + 0x90) + 4) | 0x40;
    *(float *)(*(int *)(this + 0x8c) + 0x50) = fVar33;
    *(float *)(*(int *)(this + 0x90) + 0x50) = fVar33;
    iVar20 = *(int *)(this + 0x3f8);
  }
  fVar34 = (float)VectorSignedToFloat(*(undefined4 *)(iVar20 + 0x70),(byte)(uVar38 >> 0x16) & 3);
  fVar33 = fVar34 + 30.0;
  if (*(float *)(this + 100) - 8.0 <= fVar34 + 30.0) {
    fVar33 = *(float *)(this + 100) - 8.0;
  }
  *(float *)(this + 0x27f4) = fVar33;
  if (*(int *)(this + 0x25d0) == 1) {
    if (*(float *)(this + 0x60) < 1.0) {
      pcVar9 = this + 0x404;
      fVar33 = *(float *)pcVar9;
      *(float *)pcVar9 = fVar33 * 0.9;
      *(float *)pcVar9 = fVar33 * 0.9 + *(float *)(iVar20 + 0x4c) * *(float *)(iVar20 + 0x4c) * 0.01
      ;
    }
    this[0x40d] = (cRSubGoldy)0x0;
  }
  else if (this[0x40d] != (cRSubGoldy)0x0) {
    fVar33 = *(float *)(this + 0x424) + *(float *)(this + 0x428);
    *(float *)(this + 0x424) = fVar33;
    if ((fVar33 <= 0.7) || (this[0x43c] != (cRSubGoldy)0x0)) {
LAB_0002a614:
      fVar33 = *(float *)(this + 0x60);
    }
    else {
      cRVoiceManager::Play((cRVoiceManager *)PTR__gVoiceManager_001b61d8,3,0,-1);
      this[0x43c] = (cRSubGoldy)0x1;
      if (this[0x2c0] != (cRSubGoldy)0x0) goto LAB_0002a614;
      fVar33 = *(float *)(this + 0x60);
      if (fVar33 < -6.0) {
        puVar17 = *(ushort **)(*(int *)(this + 0x2ba0) + 0x104);
        *(ushort **)(this + 0x28fc) = puVar17;
        if ((*puVar17 & 8) == 0) {
          *(undefined4 *)(this + 0x28f4) = 0;
          *(float *)(this + 0x28f8) = ABS(*(float *)(puVar17 + 10));
        }
        else {
          fVar34 = *(float *)(puVar17 + 10);
          *(float *)(this + 0x28f8) = -ABS(fVar34);
          *(float *)(this + 0x28f4) = -ABS(fVar34) + 1.0;
        }
        *(undefined4 *)(this + 0x281c) = *(undefined4 *)(this + 0x2ba0);
        *(undefined4 *)(this + 0x292c) = 0;
        *(uint *)(*(int *)(this + 0x2930) + 4) = *(uint *)(*(int *)(this + 0x2930) + 4) | 0x20;
      }
    }
    if ((fVar33 < -7.0) && (this[0x43d] == (cRSubGoldy)0x0)) {
      cRVoiceManager::Play((cRVoiceManager *)PTR__gVoiceManager_001b61d8,1,2,-1);
      this[0x43d] = (cRSubGoldy)0x1;
      this[0x43c] = (cRSubGoldy)0x1;
    }
  }
  if ((0.0 < *(float *)(this + 0x31c)) &&
     (fVar33 = *(float *)(this + 0x31c) + *(float *)(this + 800), *(float *)(this + 0x31c) = fVar33,
     1.0 < fVar33)) {
    cRVoiceManager::Play((cRVoiceManager *)PTR__gVoiceManager_001b61d8,7,2,-1);
    *(undefined4 *)(this + 0x31c) = 0;
  }
  fVar33 = *(float *)(*(int *)(this + 0x3f8) + 0x4c);
  if ((((fVar33 * 0.17 + (fVar33 * -0.17 + fVar33 * 0.5) * 0.1 <= *(float *)local_f4) ||
       (*(float *)local_f4 <= fVar33 * 0.17)) || (this[0x40d] != (cRSubGoldy)0x0)) ||
     (*(int *)(this + 0x108) == 2)) {
    *(undefined4 *)(this + 0x4008) = 0;
  }
  else {
    fVar33 = *(float *)(this + 0x4008);
    *(float *)(this + 0x4008) = fVar33 + *(float *)(this + 0x400c);
    if (1.0 < fVar33 + *(float *)(this + 0x400c)) {
      *(undefined4 *)(this + 0x4008) = 0;
      cRVoiceManager::Play((cRVoiceManager *)PTR__gVoiceManager_001b61d8,6,1,-1);
    }
  }
  Collision(this);
  pcVar9 = this + 0x2900;
  *pcVar9 = (cRSubGoldy)0x0;
  if (*(int *)(this + 0x28f0) != 0) {
    if (*(int *)(this + 0x28f0) == 1) {
      pcVar11 = this + 0x28f4;
      pcVar27 = this + 0x28f8;
      fVar33 = *(float *)pcVar11 +
               (((*(float *)(*(int *)PTR__Game_001b60b8 + 0x72bbc) +
                 *(float *)(*(int *)PTR__Game_001b60b8 + 0x72bbc)) - 0.2) + 1.0) * *(float *)pcVar27
      ;
      *(float *)pcVar11 = fVar33;
      if (1.0 <= fVar33) {
        uVar4 = **(ushort **)(this + 0x28fc);
        if ((uVar4 & 1) == 0) {
          if ((uVar4 & 4) == 0) {
            if ((uVar4 & 2) != 0) {
              *(float *)pcVar11 = 2.0 - fVar33;
              *(float *)pcVar27 = -*(float *)pcVar27;
            }
          }
          else {
            *pcVar9 = (cRSubGoldy)0x1;
            *(undefined4 *)pcVar11 = 0x3f7fbe77;
            *(undefined4 *)pcVar27 = 0;
          }
        }
        else {
          *pcVar9 = (cRSubGoldy)0x1;
          *(float *)pcVar11 = fVar33 - 1.0;
        }
      }
      pcVar11 = this + 0x28f4;
      fVar33 = *(float *)pcVar11;
      if (fVar33 < 0.0) {
        uVar4 = **(ushort **)(this + 0x28fc);
        if ((uVar4 & 2) != 0) {
          *(float *)pcVar11 = -fVar33;
          *(float *)(this + 0x28f8) = -*(float *)(this + 0x28f8);
          *pcVar9 = (cRSubGoldy)0x1;
          uVar4 = **(ushort **)(this + 0x28fc);
        }
        if ((uVar4 & 8) != 0) {
          *(undefined4 *)(this + 0x28f8) = 0;
          *(undefined4 *)pcVar11 = 0;
          *pcVar9 = (cRSubGoldy)0x1;
        }
        fVar33 = *(float *)pcVar11;
        if (0.0 <= fVar33) goto LAB_0002ac64;
        fVar33 = 0.0;
      }
      else {
LAB_0002ac64:
        if (0.9999 < fVar33) {
          fVar33 = 0.9999;
        }
      }
      *(float *)(this + 0x28f4) = fVar33;
    }
    if ((*pcVar9 != (cRSubGoldy)0x0) && (0 < *(int *)(this + 0x292c))) {
      if (*(int *)(this + 0x2904) == -1) {
        *(undefined4 *)(this + 0x28f4) = 0;
        *(undefined4 *)(this + 0x28f8) = 0;
        *(uint *)(*(int *)(this + 0x2930) + 4) = *(uint *)(*(int *)(this + 0x2930) + 4) & 0xffffffdf
        ;
      }
      else {
        *(uint *)(*(int *)(this + 0x2930) + 4) = *(uint *)(*(int *)(this + 0x2930) + 4) | 0x20;
        iVar20 = *(int *)(this + 0x2904) * 0x74 + *(int *)(this + 0x2934);
        iVar21 = *(int *)(*(int *)(iVar20 + 0x24) + 0x104);
        *(int *)(this + 0x28fc) = iVar21;
        *(undefined4 *)(this + 0x28f4) = 0;
        *(undefined4 *)(this + 0x28f8) = *(undefined4 *)(iVar21 + 0x14);
        *(undefined4 *)(*(int *)(this + 0x2930) + 0x24) = *(undefined4 *)(iVar20 + 0x24);
      }
      iVar20 = *(int *)(this + 0x292c);
      *(int *)(this + 0x292c) = iVar20 + -1;
      if (0 < iVar20 + -1) {
        pcVar9 = this + 0x2908;
        iVar20 = 0;
        do {
          iVar20 = iVar20 + 1;
          *(undefined4 *)(pcVar9 + -4) = *(undefined4 *)pcVar9;
          pcVar9 = pcVar9 + 4;
        } while (iVar20 < *(int *)(this + 0x292c));
      }
    }
  }
  this[0x3988] = (cRSubGoldy)0x0;
  if (*(int *)(this + 0x3978) != 0) {
    if (*(int *)(this + 0x3978) == 1) {
      pcVar9 = this + 0x397c;
      pcVar11 = this + 0x3980;
      fVar33 = *(float *)pcVar9 +
               (((*(float *)(*(int *)PTR__Game_001b60b8 + 0x72bbc) +
                 *(float *)(*(int *)PTR__Game_001b60b8 + 0x72bbc)) - 0.2) + 1.0) * *(float *)pcVar11
      ;
      *(float *)pcVar9 = fVar33;
      if (1.0 <= fVar33) {
        uVar4 = **(ushort **)(this + 0x3984);
        if ((uVar4 & 1) == 0) {
          if ((uVar4 & 4) == 0) {
            if ((uVar4 & 2) != 0) {
              *(float *)pcVar9 = 2.0 - fVar33;
              *(float *)pcVar11 = -*(float *)pcVar11;
            }
          }
          else {
            this[0x3988] = (cRSubGoldy)0x1;
            *(undefined4 *)pcVar9 = 0x3f7fbe77;
            *(undefined4 *)pcVar11 = 0;
          }
        }
        else {
          this[0x3988] = (cRSubGoldy)0x1;
          *(float *)pcVar9 = fVar33 - 1.0;
        }
      }
      pcVar9 = this + 0x397c;
      fVar33 = *(float *)pcVar9;
      if (fVar33 < 0.0) {
        uVar4 = **(ushort **)(this + 0x3984);
        if ((uVar4 & 2) != 0) {
          this[0x3988] = (cRSubGoldy)0x1;
          *(float *)pcVar9 = -fVar33;
          *(float *)pcVar11 = -*(float *)pcVar11;
          uVar4 = **(ushort **)(this + 0x3984);
        }
        uVar36 = (uint)uVar4;
        bVar31 = (uVar4 & 8) != 0;
        if (bVar31) {
          uVar36 = 0;
          *(undefined4 *)pcVar9 = 0;
        }
        fVar33 = *(float *)pcVar9;
        if (bVar31) {
          *(uint *)pcVar11 = uVar36;
          this[0x3988] = (cRSubGoldy)0x1;
        }
        if (0.0 <= fVar33) goto LAB_0002ad0c;
        fVar33 = 0.0;
      }
      else {
LAB_0002ad0c:
        if (0.9999 < fVar33) {
          fVar33 = 0.9999;
        }
      }
      *(float *)(this + 0x397c) = fVar33;
    }
    if ((this[0x3988] != (cRSubGoldy)0x0) && (0 < *(int *)(this + 0x39b4))) {
      if (*(int *)(this + 0x398c) == -1) {
        *(undefined4 *)(this + 0x397c) = 0;
        *(undefined4 *)(this + 0x3980) = 0;
        *(uint *)(*(int *)(this + 0x39b8) + 4) = *(uint *)(*(int *)(this + 0x39b8) + 4) & 0xffffffdf
        ;
      }
      else {
        *(uint *)(*(int *)(this + 0x39b8) + 4) = *(uint *)(*(int *)(this + 0x39b8) + 4) | 0x20;
        iVar20 = *(int *)(this + 0x398c) * 0x74 + *(int *)(this + 0x39bc);
        iVar21 = *(int *)(*(int *)(iVar20 + 0x24) + 0x104);
        *(int *)(this + 0x3984) = iVar21;
        *(undefined4 *)(this + 0x397c) = 0;
        *(undefined4 *)(this + 0x3980) = *(undefined4 *)(iVar21 + 0x14);
        *(undefined4 *)(*(int *)(this + 0x39b8) + 0x24) = *(undefined4 *)(iVar20 + 0x24);
      }
      iVar20 = *(int *)(this + 0x39b4);
      *(int *)(this + 0x39b4) = iVar20 + -1;
      if (0 < iVar20 + -1) {
        pcVar9 = this + 0x3990;
        iVar20 = 0;
        do {
          iVar20 = iVar20 + 1;
          *(undefined4 *)(pcVar9 + -4) = *(undefined4 *)pcVar9;
          pcVar9 = pcVar9 + 4;
        } while (iVar20 < *(int *)(this + 0x39b4));
      }
    }
  }
  this[0x2ecc] = (cRSubGoldy)0x0;
  if (*(int *)(this + 0x2ebc) != 0) {
    if (*(int *)(this + 0x2ebc) == 1) {
      pcVar11 = this + 0x2ec0;
      pcVar9 = this + 0x2ec4;
      fVar33 = *(float *)pcVar11 +
               (((*(float *)(*(int *)PTR__Game_001b60b8 + 0x72bbc) +
                 *(float *)(*(int *)PTR__Game_001b60b8 + 0x72bbc)) - 0.2) + 1.0) * *(float *)pcVar9;
      *(float *)pcVar11 = fVar33;
      if (1.0 <= fVar33) {
        uVar4 = **(ushort **)(this + 0x2ec8);
        if ((uVar4 & 1) == 0) {
          if ((uVar4 & 4) == 0) {
            if ((uVar4 & 2) != 0) {
              *(float *)pcVar11 = 2.0 - fVar33;
              *(float *)pcVar9 = -*(float *)pcVar9;
            }
          }
          else {
            this[0x2ecc] = (cRSubGoldy)0x1;
            *(undefined4 *)pcVar11 = 0x3f7fbe77;
            *(undefined4 *)pcVar9 = 0;
          }
        }
        else {
          this[0x2ecc] = (cRSubGoldy)0x1;
          *(float *)pcVar11 = fVar33 - 1.0;
        }
      }
      fVar33 = *(float *)pcVar11;
      if (fVar33 < 0.0) {
        uVar4 = **(ushort **)(this + 0x2ec8);
        if ((uVar4 & 2) != 0) {
          *(float *)pcVar11 = -fVar33;
          *(float *)(this + 0x2ec4) = -*(float *)(this + 0x2ec4);
          this[0x2ecc] = (cRSubGoldy)0x1;
          uVar4 = **(ushort **)(this + 0x2ec8);
        }
        if ((uVar4 & 8) != 0) {
          *(undefined4 *)(this + 0x2ec4) = 0;
          *(undefined4 *)pcVar11 = 0;
          this[0x2ecc] = (cRSubGoldy)0x1;
        }
        fVar33 = *(float *)pcVar11;
        if (fVar33 < 0.0) {
          *(undefined4 *)pcVar11 = 0;
          goto LAB_0002a8b8;
        }
      }
      if (0.9999 < fVar33) {
        fVar33 = 0.9999;
      }
      *(float *)pcVar11 = fVar33;
    }
LAB_0002a8b8:
    if ((this[0x2ecc] != (cRSubGoldy)0x0) && (0 < *(int *)(this + 0x2ef8))) {
      if (*(int *)(this + 0x2ed0) == -1) {
        *(undefined4 *)(this + 0x2ec0) = 0;
        *(undefined4 *)(this + 0x2ec4) = 0;
        *(uint *)(*(int *)(this + 0x2efc) + 4) = *(uint *)(*(int *)(this + 0x2efc) + 4) & 0xffffffdf
        ;
      }
      else {
        *(uint *)(*(int *)(this + 0x2efc) + 4) = *(uint *)(*(int *)(this + 0x2efc) + 4) | 0x20;
        iVar20 = *(int *)(this + 0x2ed0) * 0x74 + *(int *)(this + 0x2f00);
        iVar21 = *(int *)(*(int *)(iVar20 + 0x24) + 0x104);
        *(int *)(this + 0x2ec8) = iVar21;
        *(undefined4 *)(this + 0x2ec0) = 0;
        *(undefined4 *)(this + 0x2ec4) = *(undefined4 *)(iVar21 + 0x14);
        *(undefined4 *)(*(int *)(this + 0x2efc) + 0x24) = *(undefined4 *)(iVar20 + 0x24);
      }
      iVar20 = *(int *)(this + 0x2ef8);
      *(int *)(this + 0x2ef8) = iVar20 + -1;
      if (0 < iVar20 + -1) {
        pcVar9 = this + 0x2ed4;
        iVar20 = 0;
        do {
          iVar20 = iVar20 + 1;
          *(undefined4 *)(pcVar9 + -4) = *(undefined4 *)pcVar9;
          pcVar9 = pcVar9 + 4;
        } while (iVar20 < *(int *)(this + 0x2ef8));
      }
    }
  }
  this[0x3260] = (cRSubGoldy)0x0;
  if (*(int *)(this + 0x3250) != 0) {
    if (*(int *)(this + 0x3250) == 1) {
      fVar33 = *(float *)(this + 0x3254) +
               (((*(float *)(*(int *)PTR__Game_001b60b8 + 0x72bbc) +
                 *(float *)(*(int *)PTR__Game_001b60b8 + 0x72bbc)) - 0.2) + 1.0) *
               *(float *)(this + 0x3258);
      *(float *)(this + 0x3254) = fVar33;
      if (1.0 <= fVar33) {
        uVar4 = **(ushort **)(this + 0x325c);
        if ((uVar4 & 1) == 0) {
          if ((uVar4 & 4) == 0) {
            if ((uVar4 & 2) != 0) {
              *(float *)(this + 0x3254) = 2.0 - fVar33;
              *(float *)(this + 0x3258) = -*(float *)(this + 0x3258);
            }
          }
          else {
            this[0x3260] = (cRSubGoldy)0x1;
            *(undefined4 *)(this + 0x3254) = 0x3f7fbe77;
            *(undefined4 *)(this + 0x3258) = 0;
          }
        }
        else {
          this[0x3260] = (cRSubGoldy)0x1;
          *(float *)(this + 0x3254) = fVar33 - 1.0;
        }
      }
      fVar33 = *(float *)(this + 0x3254);
      if (fVar33 < 0.0) {
        uVar4 = **(ushort **)(this + 0x325c);
        if ((uVar4 & 2) != 0) {
          this[0x3260] = (cRSubGoldy)0x1;
          *(float *)(this + 0x3254) = -fVar33;
          *(float *)(this + 0x3258) = -*(float *)(this + 0x3258);
          uVar4 = **(ushort **)(this + 0x325c);
        }
        uVar36 = (uint)uVar4;
        bVar31 = (uVar4 & 8) != 0;
        if (bVar31) {
          uVar36 = 0;
          *(undefined4 *)(this + 0x3254) = 0;
        }
        fVar33 = *(float *)(this + 0x3254);
        if (bVar31) {
          *(uint *)(this + 0x3258) = uVar36;
          this[0x3260] = (cRSubGoldy)0x1;
        }
        if (fVar33 < 0.0) {
          *(undefined4 *)(this + 0x3254) = 0;
          goto LAB_0002a998;
        }
      }
      if (0.9999 < fVar33) {
        fVar33 = 0.9999;
      }
      *(float *)(this + 0x3254) = fVar33;
    }
LAB_0002a998:
    if ((this[0x3260] != (cRSubGoldy)0x0) && (0 < *(int *)(this + 0x328c))) {
      if (*(int *)(this + 0x3264) == -1) {
        *(undefined4 *)(this + 0x3254) = 0;
        *(undefined4 *)(this + 0x3258) = 0;
        *(uint *)(*(int *)(this + 0x3290) + 4) = *(uint *)(*(int *)(this + 0x3290) + 4) & 0xffffffdf
        ;
      }
      else {
        *(uint *)(*(int *)(this + 0x3290) + 4) = *(uint *)(*(int *)(this + 0x3290) + 4) | 0x20;
        iVar20 = *(int *)(this + 0x3264) * 0x74 + *(int *)(this + 0x3294);
        iVar21 = *(int *)(*(int *)(iVar20 + 0x24) + 0x104);
        *(undefined4 *)(this + 0x3254) = 0;
        *(int *)(this + 0x325c) = iVar21;
        *(undefined4 *)(this + 0x3258) = *(undefined4 *)(iVar21 + 0x14);
        *(undefined4 *)(*(int *)(this + 0x3290) + 0x24) = *(undefined4 *)(iVar20 + 0x24);
      }
      iVar20 = *(int *)(this + 0x328c);
      *(int *)(this + 0x328c) = iVar20 + -1;
      if (0 < iVar20 + -1) {
        pcVar9 = this + 0x3268;
        iVar20 = 0;
        do {
          iVar20 = iVar20 + 1;
          *(undefined4 *)(pcVar9 + -4) = *(undefined4 *)pcVar9;
          pcVar9 = pcVar9 + 4;
        } while (iVar20 < *(int *)(this + 0x328c));
      }
    }
  }
  this[0x35f4] = (cRSubGoldy)0x0;
  if (*(int *)(this + 0x35e4) != 0) {
    if (*(int *)(this + 0x35e4) == 1) {
      pcVar9 = this + 0x35e8;
      pcVar11 = this + 0x35ec;
      fVar33 = *(float *)pcVar9 +
               (((*(float *)(*(int *)PTR__Game_001b60b8 + 0x72bbc) +
                 *(float *)(*(int *)PTR__Game_001b60b8 + 0x72bbc)) - 0.2) + 1.0) * *(float *)pcVar11
      ;
      *(float *)pcVar9 = fVar33;
      if (1.0 <= fVar33) {
        uVar4 = **(ushort **)(this + 0x35f0);
        if ((uVar4 & 1) == 0) {
          if ((uVar4 & 4) == 0) {
            if ((uVar4 & 2) != 0) {
              *(float *)pcVar9 = 2.0 - fVar33;
              *(float *)pcVar11 = -*(float *)pcVar11;
            }
          }
          else {
            this[0x35f4] = (cRSubGoldy)0x1;
            *(undefined4 *)pcVar9 = 0x3f7fbe77;
            *(undefined4 *)pcVar11 = 0;
          }
        }
        else {
          this[0x35f4] = (cRSubGoldy)0x1;
          *(float *)pcVar9 = fVar33 - 1.0;
        }
      }
      pcVar9 = this + 0x35e8;
      fVar33 = *(float *)pcVar9;
      if (fVar33 < 0.0) {
        uVar4 = **(ushort **)(this + 0x35f0);
        if ((uVar4 & 2) != 0) {
          *(float *)pcVar9 = -fVar33;
          *(float *)(this + 0x35ec) = -*(float *)(this + 0x35ec);
          this[0x35f4] = (cRSubGoldy)0x1;
          uVar4 = **(ushort **)(this + 0x35f0);
        }
        if ((uVar4 & 8) != 0) {
          *(undefined4 *)(this + 0x35ec) = 0;
          *(undefined4 *)pcVar9 = 0;
          this[0x35f4] = (cRSubGoldy)0x1;
        }
        fVar33 = *(float *)pcVar9;
        if (0.0 <= fVar33) goto LAB_0002af14;
        fVar33 = 0.0;
      }
      else {
LAB_0002af14:
        if (0.9999 < fVar33) {
          fVar33 = 0.9999;
        }
      }
      *(float *)(this + 0x35e8) = fVar33;
    }
    if ((this[0x35f4] != (cRSubGoldy)0x0) && (0 < *(int *)(this + 0x3620))) {
      if (*(int *)(this + 0x35f8) == -1) {
        *(undefined4 *)(this + 0x35e8) = 0;
        *(undefined4 *)(this + 0x35ec) = 0;
        *(uint *)(*(int *)(this + 0x3624) + 4) = *(uint *)(*(int *)(this + 0x3624) + 4) & 0xffffffdf
        ;
      }
      else {
        *(uint *)(*(int *)(this + 0x3624) + 4) = *(uint *)(*(int *)(this + 0x3624) + 4) | 0x20;
        iVar20 = *(int *)(this + 0x35f8) * 0x74 + *(int *)(this + 0x3628);
        iVar21 = *(int *)(*(int *)(iVar20 + 0x24) + 0x104);
        *(int *)(this + 0x35f0) = iVar21;
        *(undefined4 *)(this + 0x35e8) = 0;
        *(undefined4 *)(this + 0x35ec) = *(undefined4 *)(iVar21 + 0x14);
        *(undefined4 *)(*(int *)(this + 0x3624) + 0x24) = *(undefined4 *)(iVar20 + 0x24);
      }
      iVar20 = *(int *)(this + 0x3620);
      *(int *)(this + 0x3620) = iVar20 + -1;
      if (0 < iVar20 + -1) {
        pcVar9 = this + 0x35fc;
        iVar20 = 0;
        do {
          iVar20 = iVar20 + 1;
          *(undefined4 *)(pcVar9 + -4) = *(undefined4 *)pcVar9;
          pcVar9 = pcVar9 + 4;
        } while (iVar20 < *(int *)(this + 0x3620));
      }
    }
  }
  iVar21 = *(int *)(this + 0x3f8);
  iVar20 = 0;
  piVar25 = (int *)(&DAT_002f04a8 + iVar21);
  do {
    while (*piVar25 == 0) {
      iVar20 = iVar20 + 1;
      piVar25 = piVar25 + 0x20;
      if (iVar20 == 0x32) goto LAB_0002ab8c;
    }
    iVar22 = iVar20 * 0x80;
    iVar20 = iVar20 + 1;
    (**(code **)piVar25[-0xb])(&DAT_002f047c + iVar21 + iVar22);
    piVar25 = piVar25 + 0x20;
  } while (iVar20 != 0x32);
LAB_0002ab8c:
  cRSnail::AIGoldy((cRSnail *)(this + 0x27f8));
  *(undefined4 *)(this + 0x324) = 0;
  switch(*(undefined4 *)(this + 0x2f0)) {
  case 0:
    iVar20 = 1;
    break;
  case 1:
    iVar20 = 2;
    break;
  case 2:
    iVar20 = 4;
    break;
  case 3:
    iVar20 = 8;
    *(undefined4 *)(this + 0x324) = 8;
    *(undefined4 *)(this + 0x25a8) = 0x3de38e39;
    goto LAB_0002b48c;
  case 4:
    iVar20 = 0x10;
    goto LAB_0002b718;
  case 5:
    iVar20 = 0x20;
    goto LAB_0002b758;
  case 6:
    iVar20 = 0x40;
    goto LAB_0002b734;
  case 7:
    iVar20 = 0xc0;
LAB_0002b734:
    *(int *)(this + 0x324) = iVar20;
    *(undefined4 *)(this + 0x25a8) = 0x3e088889;
    goto LAB_0002b48c;
  case 8:
    iVar20 = 0x90;
LAB_0002b718:
    *(int *)(this + 0x324) = iVar20;
    *(undefined4 *)(this + 0x25a8) = 0x3de38e39;
    goto LAB_0002b48c;
  default:
    iVar20 = 0x81;
LAB_0002b758:
    *(int *)(this + 0x324) = iVar20;
    *(undefined4 *)(this + 0x25a8) = 0x3d888889;
    goto LAB_0002b48c;
  }
  *(int *)(this + 0x324) = iVar20;
  *(undefined4 *)(this + 0x25a8) = 0x3d97b425;
LAB_0002b48c:
  if (iVar20 != *(int *)(this + 0x328)) {
    cRSnail::SetWeapon((cRSnail *)(this + 0x27f8),iVar20);
    iVar20 = *(int *)(this + 0x324);
  }
  *(int *)(this + 0x328) = iVar20;
  puVar6 = PTR__Game_001b60b8;
  if (*(int *)(&DAT_00353550 + *(int *)PTR__Game_001b60b8) < 10) {
    *(undefined4 *)(this + 0x25a4) = *(undefined4 *)(this + 0x25a8);
  }
  iVar20 = *(int *)(this + 0x3f8);
  if (((((*(uint *)(iVar20 + 100) & 0x400000) != 0) && (this[0x430] == (cRSubGoldy)0x0)) &&
      (this[0x2c0] == (cRSubGoldy)0x0)) &&
     (*(int *)(this + 0x108) == 4 || *(int *)(this + 0x108) == 0)) {
    pcVar9 = this + 0x25a4;
    if (*(float *)pcVar9 <= 0.0) {
      if (*(char *)(iVar20 + 0x78) != '\0') {
        if ((&DAT_002e09cc)[iVar20] == '\0') {
          if (((*(uint *)(*(int *)(this + 0x42c) + 4) & 0x4000) != 0) &&
             (*(char *)(*(int *)puVar6 + 0x23d) != '\0')) goto LAB_0002cb48;
          if (((*(uint *)(*(int *)(this + 0x42c) + 0xc) & 0x4000) != 0) &&
             (*(char *)(*(int *)PTR__Game_001b60b8 + 0x23d) != '\0')) goto LAB_0002cfd8;
        }
        else {
          uVar4 = *(ushort *)
                   (*(int *)(&DAT_002e09d8 + iVar20) * 6 + *(int *)(&DAT_002e09d0 + iVar20) + 0x74);
          if ((uVar4 & 1) == 0) {
            if ((uVar4 & 2) == 0) goto LAB_0002b558;
LAB_0002cfd8:
            *(undefined4 *)(this + 0x25a4) = *(undefined4 *)(this + 0x25a8);
            PlayShootSfx(this);
            uVar36 = *(uint *)(this + 0x324);
            if (((uVar36 & 1) == 0) && ((uVar36 & 0x68) == 0)) {
              if ((uVar36 & 0x12) != 0) {
                iVar20 = 2;
                goto LAB_0002d4f4;
              }
              if ((uVar36 & 4) != 0) {
                iVar20 = 3;
                goto LAB_0002d4f4;
              }
            }
            else {
              iVar20 = 1;
LAB_0002d4f4:
              iVar21 = 0;
              pcVar9 = this;
              do {
                if (*(int *)(pcVar9 + 0x668) == 0) {
                  cRSubGolb::Create((cRSubGolb *)(this + iVar21 * 0x2c8 + 0x444),this,iVar20,iVar21)
                  ;
                  iVar20 = iVar20 + -1;
                  if (iVar20 == 0) break;
                }
                iVar21 = iVar21 + 1;
                pcVar9 = pcVar9 + 0x2c8;
              } while (iVar21 != 0xc);
            }
            iVar20 = *(int *)(this + 0x3f8);
          }
          else {
LAB_0002cb48:
            PlayShootSfx(this);
            uVar36 = *(uint *)(this + 0x324);
            if (((uVar36 & 1) == 0) && ((uVar36 & 0x68) == 0)) {
              if ((uVar36 & 0x12) != 0) {
                iVar20 = 2;
                goto LAB_0002d5a0;
              }
              if ((uVar36 & 4) != 0) {
                iVar20 = 3;
                goto LAB_0002d5a0;
              }
            }
            else {
              iVar20 = 1;
LAB_0002d5a0:
              iVar21 = 0;
              pcVar9 = this;
              do {
                if (*(int *)(pcVar9 + 0x668) == 0) {
                  cRSubGolb::Create((cRSubGolb *)(this + iVar21 * 0x2c8 + 0x444),this,iVar20,iVar21)
                  ;
                  iVar20 = iVar20 + -1;
                  if (iVar20 == 0) break;
                }
                iVar21 = iVar21 + 1;
                pcVar9 = pcVar9 + 0x2c8;
              } while (iVar21 != 0xc);
            }
            iVar20 = *(int *)(this + 0x3f8);
            *(float *)(this + 0x25a4) = *(float *)(this + 0x25a8) + 0.3;
          }
        }
      }
    }
    else {
      fVar33 = *(float *)pcVar9 + *(float *)(this + 0x25a8);
      *(float *)pcVar9 = fVar33;
      if (1.0 < fVar33) {
        *(undefined4 *)pcVar9 = 0;
      }
    }
  }
LAB_0002b558:
  cRCompletion::AI((cRCompletion *)(iVar20 + 0x3052b8));
  iVar20 = *(int *)(this + 0x3f8);
  if (*(int *)(&DAT_003052c8 + iVar20) != 4) {
    *(int *)(*(int *)(&DAT_002e09c8 + iVar20) + 0x6c) =
         *(int *)(*(int *)(&DAT_002e09c8 + iVar20) + 0x6c) + 1;
    *(int *)(&DAT_002e09d8 + *(int *)(this + 0x3f8)) =
         *(int *)(&DAT_002e09d8 + *(int *)(this + 0x3f8)) + 1;
    iVar20 = *(int *)(this + 0x3f8);
  }
  iVar21 = iVar20 + 0x305000;
  if (*(undefined4 **)(&DAT_002e09d8 + iVar20) == &DAT_00005208) {
    iVar22 = *(int *)(&DAT_00305304 + iVar20);
    if (iVar22 != 0) goto LAB_0002b5c8;
    uVar10 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
    *(undefined4 *)(&DAT_00305308 + iVar20) = uVar10;
    tColour::tColour((tColour *)&local_80,1.0,1.0,1.0,0.03);
    cRBorder::Init(uVar10,&DAT_00400002,"Time\'s Up",0x14,0,0x43480000,local_80,uStack_7c,uStack_78,
                   uStack_74,2,0);
    *(undefined4 *)(&DAT_0030530c + iVar20) = 0;
    *(undefined4 *)(&DAT_00305310 + iVar20) = 0x3bb60b61;
    *(undefined4 *)(&DAT_00305304 + iVar20) = 1;
    iVar21 = *(int *)(this + 0x3f8) + 0x305000;
  }
  iVar22 = *(int *)(iVar21 + 0x304);
LAB_0002b5c8:
  puVar6 = PTR__Game_001b60b8;
  if (iVar22 == 1) {
    fVar33 = *(float *)(iVar21 + 0x30c) + *(float *)(iVar21 + 0x310);
    *(float *)(iVar21 + 0x30c) = fVar33;
    if (1.0 < fVar33) {
      *(undefined4 *)(iVar21 + 0x304) = 2;
    }
  }
  else if (iVar22 == 2) {
    cRBorderManager::Kill((cRBorder *)(*(int *)PTR__Game_001b60b8 + 0xd14));
    iVar20 = *(int *)puVar6;
    bVar31 = *(char *)(iVar20 + 0x82334) != '\0';
    if (bVar31) {
      uVar10 = *(undefined4 *)(*(int *)(iVar20 + 0x82338) + 0x80);
    }
    else {
      uVar10 = 0;
      *(undefined4 *)(&DAT_000823e0 + iVar20) = 0;
      *(undefined4 *)(&DAT_000823dc + iVar20) = 0;
    }
    *(undefined1 *)(iVar20 + 0x82334) = 0;
    (&DAT_000823fc)[iVar20] = 0;
    if (bVar31) {
      *(undefined4 *)(&DAT_000823e0 + iVar20) = uVar10;
      uVar10 = *(undefined4 *)(iVar20 + 0x82350);
    }
    (&DAT_000823fd)[iVar20] = 0;
    *(undefined4 *)(iVar21 + 0x304) = 0;
    if (bVar31) {
      *(undefined4 *)(&DAT_000823dc + iVar20) = uVar10;
    }
    (&DAT_000823cd)[iVar20] = 1;
    *(undefined4 *)(&DAT_000823d4 + iVar20) = *(undefined4 *)(iVar20 + 0x82024);
    *(undefined4 *)(&UNK_000823e4 + iVar20) = 0;
    *(undefined4 *)(iVar20 + 0x82020) = 0xc1000000;
  }
  return;
}
