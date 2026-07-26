/*
 * mangled: _ZN14cAccelerometer2AIEv
 * demangled: cAccelerometer::AI()
 * address: 00075b48
 * size: 1376
 */

/* cAccelerometer::AI() */

void __thiscall cAccelerometer::AI(cAccelerometer *this)

{
  byte bVar1;
  undefined *puVar2;
  float fVar3;
  int iVar4;
  cAccelerometer *pcVar5;
  uint uVar6;
  bool bVar7;
  uint in_fpscr;
  float fVar9;
  int iVar10;
  double dVar8;

  puVar2 = PTR__Game_001b60b8;
  if ((*(int *)(PTR__gLoadingBar_001b60bc + 0x1c) != 8) || (10 < _gAccelerometerCounter)) {
    *(undefined4 *)(*(int *)PTR__Game_001b60b8 + 0x3c) = 0x43870000;
    *(undefined4 *)(*(int *)puVar2 + 0x40) = 0x43870000;
    *(undefined4 *)(*(int *)puVar2 + 0x48) = 0;
    MacOFOrientation();
    return;
  }
  fVar3 = (float)ATan(*(float *)this,-*(float *)(this + 4));
  fVar9 = *(float *)(this + 8);
  if (fVar9 < 0.0) {
    uVar6 = in_fpscr & 0xfffffff | (uint)(fVar9 < -0.75) << 0x1f | (uint)(fVar9 == -0.75) << 0x1e;
    bVar1 = (byte)(uVar6 >> 0x18);
    bVar7 = !(bool)(bVar1 >> 6 & 1) && (bool)(bVar1 >> 7) == NAN(fVar9);
  }
  else {
    uVar6 = in_fpscr & 0xfffffff | (uint)(fVar9 < 0.75) << 0x1f;
    if (SUB41(uVar6 >> 0x1f,0)) {
      bVar7 = true;
    }
    else {
      bVar7 = false;
    }
  }
  if (bVar7) {
    fVar3 = (float)VectorSignedToFloat((int)((fVar3 * 180.0) / 3.1415927 + 360.0) % 0x168,
                                       (byte)(uVar6 >> 0x16) & 3);
    iVar4 = (int)((fVar3 + 45.0) / 90.0) % 4;
    fVar9 = (float)VectorSignedToFloat(iVar4 * 0x5a,(byte)(uVar6 >> 0x16) & 3);
    iVar10 = (int)(fVar3 - fVar9);
    if (iVar10 < 0) {
      iVar10 = -iVar10;
    }
    if (0xb4 < iVar10) {
      iVar10 = 0x168 - iVar10;
    }
    dVar8 = (double)VectorSignedToFloat(iVar10,(byte)(uVar6 >> 0x16) & 3);
    if (dVar8 < 22.5) {
      iVar10 = 0;
      pcVar5 = this;
      do {
        if (iVar4 == iVar10) {
          if (*(float *)(this + iVar10 * 4 + 0xc) < 100.0) {
            *(float *)(this + iVar10 * 4 + 0xc) = *(float *)(this + iVar10 * 4 + 0xc) + 1.0;
          }
        }
        else if (0.0 < *(float *)(pcVar5 + 0xc)) {
          *(undefined4 *)(pcVar5 + 0xc) = 0;
        }
        iVar10 = iVar10 + 1;
        pcVar5 = pcVar5 + 4;
      } while (iVar10 != 4);
      fVar3 = *(float *)(this + 0xc);
    }
    else {
      if (iVar4 == 0) {
        fVar3 = *(float *)(this + 0xc);
LAB_00075cd4:
        if (0.0 < *(float *)(this + 0x10)) {
          *(undefined4 *)(this + 0x10) = 0;
        }
        if (iVar4 != 2) goto LAB_00075cf0;
      }
      else {
        fVar3 = *(float *)(this + 0xc);
        if (0.0 < fVar3) {
          fVar3 = 0.0;
          *(undefined4 *)(this + 0xc) = 0;
        }
        if (iVar4 != 1) goto LAB_00075cd4;
LAB_00075cf0:
        if (0.0 < *(float *)(this + 0x14)) {
          *(undefined4 *)(this + 0x14) = 0;
        }
        if (iVar4 == 3) goto LAB_00075d20;
      }
      if (0.0 < *(float *)(this + 0x18)) {
        *(undefined4 *)(this + 0x18) = 0;
      }
    }
LAB_00075d20:
    if ((90.0 < fVar3) && (*(float *)(*(int *)PTR__Game_001b60b8 + 0x40) != 0.0)) {
      *(undefined4 *)(*(int *)PTR__Game_001b60b8 + 0x40) = 0;
    }
    if ((90.0 < *(float *)(this + 0x10)) && (*(float *)(*(int *)PTR__Game_001b60b8 + 0x40) != 90.0))
    {
      *(undefined4 *)(*(int *)PTR__Game_001b60b8 + 0x40) = 0x42b40000;
    }
    if ((90.0 < *(float *)(this + 0x14)) && (*(float *)(*(int *)PTR__Game_001b60b8 + 0x40) != 180.0)
       ) {
      *(undefined4 *)(*(int *)PTR__Game_001b60b8 + 0x40) = 0x43340000;
    }
    if ((90.0 < *(float *)(this + 0x18)) && (*(float *)(*(int *)PTR__Game_001b60b8 + 0x40) != 270.0)
       ) {
      *(undefined4 *)(*(int *)PTR__Game_001b60b8 + 0x40) = 0x43870000;
    }
  }
  puVar2 = PTR__gConfig_001b60d4;
  iVar10 = *(int *)PTR__Game_001b60b8;
  *(undefined4 *)(PTR__gConfig_001b60d4 + 200) = *(undefined4 *)(iVar10 + 0x3c);
  if (*(int *)(iVar10 + 0x72bcc) == 4 || *(int *)(iVar10 + 0x72bcc) == 2) {
    uVar6 = *(uint *)(puVar2 + 8);
    bVar7 = uVar6 == 1;
    if (bVar7) {
      uVar6 = (uint)(byte)(&DAT_00353544)[iVar10];
    }
    if (!bVar7 || uVar6 != 0) goto LAB_00075e14;
    if (*(float *)(iVar10 + 0x3c) == 90.0) {
      *(undefined4 *)(iVar10 + 0x4c) = 0x3f800000;
    }
    else {
      if (*(float *)(iVar10 + 0x3c) != 270.0) goto LAB_00075e14;
      *(undefined4 *)(iVar10 + 0x4c) = 0xbf800000;
    }
  }
  else {
LAB_00075e14:
    *(undefined4 *)(iVar10 + 0x4c) = 0;
  }
  iVar10 = *(int *)PTR__Game_001b60b8;
  if (*(int *)(iVar10 + 0x72bcc) == 2) {
    uVar6 = *(uint *)(PTR__gConfig_001b60d4 + 8);
    bVar7 = uVar6 == 0;
    if (bVar7) {
      uVar6 = (uint)(byte)(&DAT_00353544)[iVar10];
    }
    if (bVar7 && uVar6 == 0) {
      iVar4 = (int)*(float *)(iVar10 + 0x3c);
      if (iVar4 == 0x5a) {
        fVar3 = (float)ACos(*(float *)(this + 4));
LAB_00075efc:
        *(float *)(iVar10 + 0x48) = (fVar3 * 180.0) / 3.1415927 - 90.0;
      }
      else if (iVar4 < 0x5b) {
        if (iVar4 == 0) {
          fVar3 = (float)ACos(*(float *)this);
          goto LAB_00075efc;
        }
      }
      else {
        if (iVar4 == 0xb4) {
          fVar3 = (float)ACos(*(float *)this);
        }
        else {
          if (iVar4 != 0x10e) goto LAB_00075f10;
          fVar3 = (float)ACos(*(float *)(this + 4));
        }
        *(float *)(iVar10 + 0x48) = (fVar3 * -180.0) / 3.1415927 + 90.0;
      }
LAB_00075f10:
      puVar2 = PTR__Game_001b60b8;
      iVar10 = *(int *)PTR__Game_001b60b8;
      if (80.0 < *(float *)(iVar10 + 0x48)) {
        *(undefined4 *)(iVar10 + 0x48) = 0x42a00000;
        iVar10 = *(int *)puVar2;
      }
      if (*(float *)(iVar10 + 0x48) < -80.0) {
        *(undefined4 *)(iVar10 + 0x48) = 0xc2a00000;
        iVar10 = *(int *)puVar2;
      }
      if (180.0 < *(float *)(iVar10 + 0x48)) {
        *(float *)(iVar10 + 0x48) = *(float *)(iVar10 + 0x48) - 360.0;
        iVar10 = *(int *)puVar2;
      }
      if (*(float *)(iVar10 + 0x48) < -180.0) {
        *(float *)(iVar10 + 0x48) = *(float *)(iVar10 + 0x48) + 360.0;
      }
      cRMouse::ClickScreen
                ((cRMouse *)(*(int *)puVar2 + 0x228),false,
                 *(float *)(*(int *)puVar2 + 0x48) * -20.0 + 320.0,479.0);
      goto LAB_00075e40;
    }
  }
  *(undefined4 *)(iVar10 + 0x48) = 0;
LAB_00075e40:
  MacOFOrientation();
  return;
}
