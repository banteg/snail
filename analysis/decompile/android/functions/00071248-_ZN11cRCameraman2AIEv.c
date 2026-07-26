/*
 * mangled: _ZN11cRCameraman2AIEv
 * demangled: cRCameraman::AI()
 * address: 00071248
 * size: 1624
 */

/* cRCameraman::AI() */

void cRCameraman::AI(void)

{
  tMatrix *in_r0;
  int iVar1;
  int iVar2;
  tMatrix *this;
  uint in_fpscr;
  float in_s0;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float extraout_s0_02;
  float in_s1;
  float in_s2;
  float in_s3;
  float in_s4;
  float in_s5;
  float in_s6;
  float in_s7;
  float in_s8;
  float in_s9;
  float in_s10;
  float in_s11;
  float in_s12;
  float fVar3;
  float fVar4;
  float in_s13;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  tMatrix atStack_a8 [64];
  undefined4 local_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 local_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 local_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;

  fVar5 = *(float *)(*(int *)(in_r0 + 0xc0) + 0x27e0);
  in_r0[0xcc] = (tMatrix)0x0;
  this = in_r0 + 0x40;
  tMatrix::tMatrix((tMatrix *)&local_68,in_s0,in_s1,in_s2,in_s3,in_s4,in_s5,in_s6,in_s7,in_s8,in_s9,
                   in_s10,in_s11,in_s12,in_s13,-0.5,fVar5 / 2.5);
  *(undefined4 *)this = local_68;
  *(undefined4 *)(in_r0 + 0x44) = uStack_64;
  *(undefined4 *)(in_r0 + 0x48) = uStack_60;
  *(undefined4 *)(in_r0 + 0x4c) = uStack_5c;
  *(undefined4 *)(in_r0 + 0x50) = local_58;
  *(undefined4 *)(in_r0 + 0x54) = uStack_54;
  *(undefined4 *)(in_r0 + 0x58) = uStack_50;
  *(undefined4 *)(in_r0 + 0x5c) = uStack_4c;
  *(undefined4 *)(in_r0 + 0x60) = local_48;
  *(undefined4 *)(in_r0 + 100) = uStack_44;
  *(undefined4 *)(in_r0 + 0x68) = uStack_40;
  *(undefined4 *)(in_r0 + 0x6c) = uStack_3c;
  *(undefined4 *)(in_r0 + 0x70) = local_38;
  *(undefined4 *)(in_r0 + 0x74) = uStack_34;
  *(undefined4 *)(in_r0 + 0x78) = uStack_30;
  *(undefined4 *)(in_r0 + 0x7c) = uStack_2c;
  fVar5 = (float)tMatrix::Orthoganalize(this);
  fVar8 = (float)VectorSignedToFloat(*(undefined4 *)(*(int *)(in_r0 + 0xc4) + 0x70),
                                     (byte)(in_fpscr >> 0x16) & 3);
  iVar2 = *(int *)(in_r0 + 0xc0);
  if (fVar8 <= *(float *)(iVar2 + 0x27e8)) {
    *(float *)(in_r0 + 0x74) = *(float *)(in_r0 + 0x74) + *(float *)(iVar2 + 0x27e4) * 0.35;
  }
  else {
    fVar8 = (*(float *)(iVar2 + 0x27e8) / fVar8) * 1.4 - 0.4;
    if (fVar8 < 0.0) {
      fVar8 = 0.0;
    }
    else if (1.0 < fVar8) {
      fVar8 = 1.0;
    }
    fVar6 = *(float *)(in_r0 + 0x74) + (1.0 - fVar8) * *(float *)(iVar2 + 0x27e4) * 1.15;
    *(float *)(in_r0 + 0x74) = fVar6;
    *(float *)(in_r0 + 0x74) = fVar6 + fVar8 * 0.35 * *(float *)(iVar2 + 0x27e4);
    fVar5 = (float)tMatrix::RotLocalX(this,fVar5);
    iVar2 = *(int *)(in_r0 + 0xc0);
  }
  if (*(char *)(iVar2 + 0x374) == '\0') {
LAB_000713c0:
    fVar8 = 0.0;
    if (*(float *)(iVar2 + 0x2c4) <= 0.0) {
      fVar8 = *(float *)(in_r0 + 0xd0) * 0.98;
    }
    *(float *)(in_r0 + 0xd0) = fVar8;
  }
  else {
    iVar1 = *(int *)(*(int *)(iVar2 + 0x378) + 0x2c);
    if (((((iVar1 == 0x14 || iVar1 == 9) || (iVar1 == 10)) || (iVar1 == 0xb)) ||
        ((iVar1 == 0x3b || (iVar1 == 0x3d)))) || (iVar1 == 0x2c)) {
      fVar5 = (float)Cos(fVar5);
      iVar2 = *(int *)(in_r0 + 0xc0);
      fVar8 = (fVar5 * -0.5 + 0.5) * 0.35;
      *(float *)(in_r0 + 0xd0) = fVar8;
      fVar6 = *(float *)(iVar2 + 0x2c4);
      fVar5 = extraout_s0_00;
      goto joined_r0x0007175c;
    }
    if (iVar1 != 0x12) goto LAB_000713c0;
    fVar8 = (*(float *)(iVar2 + 100) - *(float *)(*(int *)(iVar2 + 0x37c) + 0x18)) /
            *(float *)(*(int *)(iVar2 + 0x378) + 0x40);
    if (fVar8 < 0.0) {
      fVar8 = 0.0;
    }
    else if (1.0 < fVar8) {
      fVar8 = 1.0;
    }
    fVar8 = fVar8 * 0.55;
    *(float *)(in_r0 + 0xd0) = fVar8;
  }
  fVar6 = *(float *)(iVar2 + 0x2c4);
joined_r0x0007175c:
  if (0.0 < fVar6) {
    fVar5 = (float)Cos(fVar5);
    iVar2 = *(int *)(in_r0 + 0xc0);
    fVar8 = fVar8 + (fVar5 * -0.5 + 0.5) * 0.24;
    *(float *)(in_r0 + 0xd0) = fVar8;
    fVar5 = extraout_s0_01;
  }
  fVar6 = *(float *)(in_r0 + 0xd4) + (fVar8 - *(float *)(in_r0 + 0xd4)) * 0.1;
  *(float *)(in_r0 + 0xd4) = fVar6;
  fVar8 = *(float *)(iVar2 + 0x27e0);
  fVar3 = *(float *)(iVar2 + 0x27e4);
  fVar7 = *(float *)(iVar2 + 0x27e8) + 0.4 + *(float *)(in_r0 + 0x78);
  *(float *)(in_r0 + 0x78) = fVar7;
  fVar4 = fVar7 - *(float *)(in_r0 + 0xb8);
  *(float *)(in_r0 + 0x74) = *(float *)(in_r0 + 0x74) + fVar6 * fVar3;
  if (3.0 < fVar4) {
    fVar7 = fVar7 - 3.0;
  }
  *(float *)(in_r0 + 0x70) = *(float *)(in_r0 + 0x70) + fVar8 / 3.0;
  if (3.0 < fVar4) {
    *(float *)(in_r0 + 0xb8) = fVar7;
  }
  else if (fVar4 < 1.7) {
    *(float *)(in_r0 + 0xb8) = fVar7 - 1.7;
  }
  fVar5 = (float)tMatrix::RotLocalX(this,fVar5);
  fVar5 = (float)Cos(fVar5);
  fVar5 = (fVar5 * -0.5 + 0.5) * *(float *)(*(int *)(in_r0 + 0xc0) + 0x340);
  *(float *)(*(int *)(in_r0 + 0xc0) + 0x34c) = (fVar5 + fVar5) * 3.1415927;
  fVar5 = (float)Cos(extraout_s0);
  fVar5 = (float)tMatrix::RotLocalZ(this,fVar5);
  iVar2 = *(int *)(in_r0 + 0xc0);
  if (*(char *)(iVar2 + 0x374) != '\0') {
    fVar5 = (float)tMatrix::Identity(atStack_a8);
    tMatrix::RotLocalZ(atStack_a8,fVar5);
    fVar5 = (float)tMatrix::operator*=(this,atStack_a8);
    fVar5 = (float)tMatrix::RotLocalZ(this,fVar5);
    iVar2 = *(int *)(in_r0 + 0xc0);
  }
  if (*(char *)(iVar2 + 0x415) != '\0') {
    fVar5 = (float)tMatrix::RotLocalZ(this,fVar5);
  }
  fVar5 = (float)tMatrix::RotLocalZ(this,fVar5);
  if ((*(char *)(*(int *)(in_r0 + 0xc0) + 0x374) == '\0') ||
     (*(int *)(*(int *)(*(int *)(in_r0 + 0xc0) + 0x378) + 0x2c) != 0x1c)) {
    fVar8 = 120.0;
  }
  else {
    fVar5 = (float)Cos(fVar5);
    fVar8 = (fVar5 * -0.5 + 0.5) * 50.0 + 120.0;
    fVar5 = (float)cRBackdrop::SetZoom((cRBackdrop *)(Game + 0x4d2e0),extraout_s0_02);
  }
  *(float *)(in_r0 + 200) = *(float *)(in_r0 + 200) + (fVar8 - *(float *)(in_r0 + 200)) * 0.3;
  tMatrix::LinearInterpolate(in_r0,in_r0 + 0x80,this,fVar5);
  *(undefined4 *)(in_r0 + 0x80) = *(undefined4 *)this;
  *(undefined4 *)(in_r0 + 0x84) = *(undefined4 *)(in_r0 + 0x44);
  *(undefined4 *)(in_r0 + 0x88) = *(undefined4 *)(in_r0 + 0x48);
  *(undefined4 *)(in_r0 + 0x8c) = *(undefined4 *)(in_r0 + 0x4c);
  *(undefined4 *)(in_r0 + 0x90) = *(undefined4 *)(in_r0 + 0x50);
  *(undefined4 *)(in_r0 + 0x94) = *(undefined4 *)(in_r0 + 0x54);
  *(undefined4 *)(in_r0 + 0x98) = *(undefined4 *)(in_r0 + 0x58);
  *(undefined4 *)(in_r0 + 0x9c) = *(undefined4 *)(in_r0 + 0x5c);
  *(undefined4 *)(in_r0 + 0xa0) = *(undefined4 *)(in_r0 + 0x60);
  *(undefined4 *)(in_r0 + 0xa4) = *(undefined4 *)(in_r0 + 100);
  *(undefined4 *)(in_r0 + 0xa8) = *(undefined4 *)(in_r0 + 0x68);
  *(undefined4 *)(in_r0 + 0xac) = *(undefined4 *)(in_r0 + 0x6c);
  *(undefined4 *)(in_r0 + 0xb0) = *(undefined4 *)(in_r0 + 0x70);
  *(undefined4 *)(in_r0 + 0xb4) = *(undefined4 *)(in_r0 + 0x74);
  *(undefined4 *)(in_r0 + 0xb8) = *(undefined4 *)(in_r0 + 0x78);
  *(undefined4 *)(in_r0 + 0xbc) = *(undefined4 *)(in_r0 + 0x7c);
  return;
}
