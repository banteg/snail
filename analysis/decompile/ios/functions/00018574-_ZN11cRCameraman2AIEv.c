/*
 * mangled: _ZN11cRCameraman2AIEv
 * demangled: cRCameraman::AI()
 * address: 00018574
 * size: 1620
 */

/* cRCameraman::AI() */

void __thiscall cRCameraman::AI(cRCameraman *this)

{
  int iVar1;
  int iVar2;
  int iVar3;
  tMatrix *this_00;
  uint in_fpscr;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  tMatrix atStack_a4 [64];
  undefined4 local_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 local_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 local_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 local_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;

  this[0xcc] = (cRCameraman)0x0;
  fVar6 = 1.0;
  tMatrix::tMatrix((tMatrix *)&local_64,1.0,0.0,0.0,0.0,0.0,0.946001,0.324162,0.0,0.0,-0.324162,
                   0.946001,0.0,*(float *)(&DAT_000027d8 + *(int *)(this + 0xc0)) / 2.5,1.8,-0.5,1.0
                  );
  this_00 = (tMatrix *)(this + 0x40);
  *(undefined4 *)(this + 0x40) = local_64;
  *(undefined4 *)(this + 0x44) = uStack_60;
  *(undefined4 *)(this + 0x48) = uStack_5c;
  *(undefined4 *)(this + 0x4c) = uStack_58;
  *(undefined4 *)(this + 0x50) = local_54;
  *(undefined4 *)(this + 0x54) = uStack_50;
  *(undefined4 *)(this + 0x58) = uStack_4c;
  *(undefined4 *)(this + 0x5c) = uStack_48;
  *(undefined4 *)(this + 0x60) = local_44;
  *(undefined4 *)(this + 100) = uStack_40;
  *(undefined4 *)(this + 0x68) = uStack_3c;
  *(undefined4 *)(this + 0x6c) = uStack_38;
  *(undefined4 *)(this + 0x70) = local_34;
  *(undefined4 *)(this + 0x74) = uStack_30;
  *(undefined4 *)(this + 0x78) = uStack_2c;
  *(undefined4 *)(this + 0x7c) = uStack_28;
  tMatrix::Orthoganalize((tMatrix *)(this + 0x40));
  iVar1 = *(int *)(this + 0xc0);
  fVar5 = (float)VectorSignedToFloat(*(undefined4 *)(*(int *)(this + 0xc4) + 0x68),
                                     (byte)(in_fpscr >> 0x16) & 3);
  if (fVar5 <= *(float *)(&DAT_000027e0 + iVar1)) {
    *(float *)(this + 0x74) = *(float *)(this + 0x74) + *(float *)(&DAT_000027dc + iVar1) * 0.35;
  }
  else {
    fVar5 = (*(float *)(&DAT_000027e0 + iVar1) / fVar5) * 1.4 - 0.4;
    if (fVar5 < 0.0) {
      fVar4 = 0.87249994;
      fVar5 = 0.0;
    }
    else {
      if (fVar6 < fVar5) {
        fVar5 = fVar6;
      }
      fVar6 = fVar6 - fVar5;
      fVar4 = fVar6 * 0.87249994;
      fVar5 = fVar5 * 0.35;
    }
    fVar6 = *(float *)(this + 0x74) + fVar6 * *(float *)(&DAT_000027dc + iVar1) * 1.15;
    *(float *)(this + 0x74) = fVar6;
    *(float *)(this + 0x74) = fVar6 + fVar5 * *(float *)(&DAT_000027dc + iVar1);
    tMatrix::RotLocalX(this_00,fVar4);
    iVar1 = *(int *)(this + 0xc0);
  }
  if (*(char *)(iVar1 + 0x374) == '\0') {
LAB_00018a8c:
    if (0.0 < *(float *)(iVar1 + 0x2c4)) {
      fVar6 = 0.0;
      *(undefined4 *)(this + 0xd0) = 0;
      goto LAB_00018764;
    }
    fVar6 = *(float *)(this + 0xd0) * 0.98;
  }
  else {
    iVar2 = *(int *)(iVar1 + 0x378);
    iVar3 = *(int *)(iVar2 + 0x2c);
    if (((iVar3 == 9 || iVar3 == 0x14) ||
        (((iVar3 == 10 || iVar3 == 0xb) || iVar3 == 0x3b) || iVar3 == 0x3d)) || (iVar3 == 0x2c)) {
      fVar6 = (*(float *)(iVar1 + 100) - *(float *)(*(int *)(iVar1 + 0x37c) + 0x18)) /
              *(float *)(iVar2 + 0x40);
      if (fVar6 < 0.0) {
        fVar6 = 0.0;
      }
      else {
        if (1.0 < fVar6) {
          fVar6 = 1.0;
        }
        fVar6 = fVar6 * 6.2831855;
      }
      fVar6 = (float)Cos(fVar6);
      iVar1 = *(int *)(this + 0xc0);
      fVar6 = (fVar6 * -0.5 + 0.5) * 0.35;
      *(float *)(this + 0xd0) = fVar6;
      goto LAB_00018764;
    }
    if (iVar3 != 0x12) goto LAB_00018a8c;
    fVar6 = (*(float *)(iVar1 + 100) - *(float *)(*(int *)(iVar1 + 0x37c) + 0x18)) /
            *(float *)(iVar2 + 0x40);
    if (0.0 <= fVar6) {
      if (1.0 < fVar6) {
        fVar6 = 1.0;
      }
      fVar6 = fVar6 * 0.55;
      *(float *)(this + 0xd0) = fVar6;
      goto LAB_00018764;
    }
    fVar6 = 0.0;
  }
  *(float *)(this + 0xd0) = fVar6;
LAB_00018764:
  if (0.0 < *(float *)(iVar1 + 0x2c4)) {
    fVar5 = (float)Cos(*(float *)(iVar1 + 0x2c4) * 1.5 * 3.1415927 + 1.5707964);
    iVar1 = *(int *)(this + 0xc0);
    fVar6 = fVar6 + (fVar5 * -0.5 + 0.5) * 0.24;
    *(float *)(this + 0xd0) = fVar6;
  }
  fVar6 = *(float *)(this + 0xd4) + (fVar6 - *(float *)(this + 0xd4)) * 0.1;
  *(float *)(this + 0xd4) = fVar6;
  fVar5 = 3.0;
  *(float *)(this + 0x74) = *(float *)(this + 0x74) + fVar6 * *(float *)(&DAT_000027dc + iVar1);
  fVar6 = *(float *)(&DAT_000027e0 + iVar1);
  *(float *)(this + 0x70) = *(float *)(this + 0x70) + *(float *)(&DAT_000027d8 + iVar1) / 3.0;
  fVar6 = *(float *)(this + 0x78) + fVar6 + 0.4;
  *(float *)(this + 0x78) = fVar6;
  if ((3.0 < fVar6 - *(float *)(this + 0xb8)) ||
     (fVar5 = 1.7, fVar6 - *(float *)(this + 0xb8) < 1.7)) {
    *(float *)(this + 0xb8) = fVar6 - fVar5;
  }
  fVar5 = ((*(float *)(&DAT_000027dc + iVar1) - 0.49) * -5.0 - 2.0) * 0.01745;
  fVar6 = -1.2214999;
  if ((-1.2214999 <= fVar5) && (fVar6 = fVar5, 1.2214999 < fVar5)) {
    fVar6 = 1.2214999;
  }
  tMatrix::RotLocalX(this_00,fVar6);
  fVar7 = 3.1415927;
  fVar5 = 0.5;
  fVar8 = -0.5;
  fVar6 = (float)Cos(*(float *)(*(int *)(this + 0xc0) + 0x344) * 3.1415927);
  fVar6 = (fVar5 + fVar6 * fVar8) * *(float *)(*(int *)(this + 0xc0) + 0x340);
  *(float *)(*(int *)(this + 0xc0) + 0x34c) = (fVar6 + fVar6) * fVar7;
  fVar4 = *(float *)(&DAT_000027d8 + *(int *)(this + 0xc0)) * -8.0 * 0.01745 * 0.17;
  fVar6 = (float)Cos(*(float *)(*(int *)(this + 0xc0) + 0x344) * fVar7);
  fVar6 = (fVar5 + fVar6 * fVar8) * *(float *)(*(int *)(this + 0xc0) + 0x340);
  tMatrix::RotLocalZ(this_00,fVar4 + (fVar6 + fVar6) * fVar7);
  iVar1 = *(int *)(this + 0xc0);
  if (*(char *)(iVar1 + 0x374) != '\0') {
    tMatrix::Identity(atStack_a4);
    tMatrix::RotLocalZ(atStack_a4,*(float *)(*(int *)(this + 0xc0) + 0x38c));
    tMatrix::operator*=(this_00,atStack_a4);
    tMatrix::RotLocalZ(this_00,*(float *)(*(int *)(this + 0xc0) + 0x390));
    iVar1 = *(int *)(this + 0xc0);
  }
  if (*(char *)(iVar1 + 0x40d) != '\0') {
    tMatrix::RotLocalZ(this_00,*(float *)(iVar1 + 0x41c));
    iVar1 = *(int *)(this + 0xc0);
  }
  tMatrix::RotLocalZ(this_00,*(float *)(iVar1 + 0x360));
  iVar1 = *(int *)(this + 0xc0);
  if ((*(char *)(iVar1 + 0x374) == '\0') || (*(int *)(*(int *)(iVar1 + 0x378) + 0x2c) != 0x1c)) {
    fVar6 = 120.0;
  }
  else {
    fVar6 = (*(float *)(iVar1 + 100) - *(float *)(*(int *)(iVar1 + 0x37c) + 0x18)) /
            *(float *)(*(int *)(iVar1 + 0x378) + 0x40);
    if (fVar6 < 0.0) {
      fVar6 = 0.0;
    }
    else {
      if (1.0 < fVar6) {
        fVar6 = 1.0;
      }
      fVar6 = fVar6 * 6.2831855;
    }
    fVar6 = (float)Cos(fVar6);
    fVar5 = fVar6 * -0.5 + 0.5;
    fVar6 = fVar5 * 50.0 + 120.0;
    cRBackdrop::SetZoom((cRBackdrop *)(*(int *)PTR__Game_001b60b8 + 0x4d2e0),fVar5 * 0.1);
  }
  *(float *)(this + 200) = *(float *)(this + 200) + (fVar6 - *(float *)(this + 200)) * 0.3;
  tMatrix::LinearInterpolate
            ((tMatrix *)this,(tMatrix *)(this + 0x80),this_00,
             *(float *)(*(int *)(this + 0xc4) + 0x4c) * 0.3);
  *(undefined4 *)(this + 0x80) = *(undefined4 *)this_00;
  *(undefined4 *)(this + 0x84) = *(undefined4 *)(this + 0x44);
  *(undefined4 *)(this + 0x88) = *(undefined4 *)(this + 0x48);
  *(undefined4 *)(this + 0x8c) = *(undefined4 *)(this + 0x4c);
  *(undefined4 *)(this + 0x90) = *(undefined4 *)(this + 0x50);
  *(undefined4 *)(this + 0x94) = *(undefined4 *)(this + 0x54);
  *(undefined4 *)(this + 0x98) = *(undefined4 *)(this + 0x58);
  *(undefined4 *)(this + 0x9c) = *(undefined4 *)(this + 0x5c);
  *(undefined4 *)(this + 0xa0) = *(undefined4 *)(this + 0x60);
  *(undefined4 *)(this + 0xa4) = *(undefined4 *)(this + 100);
  *(undefined4 *)(this + 0xa8) = *(undefined4 *)(this + 0x68);
  *(undefined4 *)(this + 0xac) = *(undefined4 *)(this + 0x6c);
  *(undefined4 *)(this + 0xb0) = *(undefined4 *)(this + 0x70);
  *(undefined4 *)(this + 0xb4) = *(undefined4 *)(this + 0x74);
  *(undefined4 *)(this + 0xb8) = *(undefined4 *)(this + 0x78);
  *(undefined4 *)(this + 0xbc) = *(undefined4 *)(this + 0x7c);
  return;
}
