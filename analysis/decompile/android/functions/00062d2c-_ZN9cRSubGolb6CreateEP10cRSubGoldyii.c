/*
 * mangled: _ZN9cRSubGolb6CreateEP10cRSubGoldyii
 * demangled: cRSubGolb::Create(cRSubGoldy*, int, int)
 * address: 00062d2c
 * size: 1964
 */

/* cRSubGolb::Create(cRSubGoldy*, int, int) */

void __thiscall cRSubGolb::Create(cRSubGolb *this,cRSubGoldy *param_1,int param_2,int param_3)

{
  byte bVar1;
  undefined4 uVar2;
  int iVar3;
  uint *puVar4;
  uint uVar5;
  undefined4 uVar6;
  int *piVar7;
  int iVar8;
  undefined4 uVar9;
  uint uVar10;
  int iVar11;
  uint uVar12;
  tVector *ptVar13;
  int iVar14;
  undefined4 uVar15;
  cRVapour *this_00;
  float *unaff_r9;
  undefined4 uVar16;
  bool bVar17;
  uint in_fpscr;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s1;
  float extraout_s1_00;
  float extraout_s2;
  float extraout_s2_00;
  float extraout_s3;
  float extraout_s3_00;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;

  iVar3 = DAT_000631bc;
  iVar14 = DAT_000631b8 + 0x62d48;
  uVar5 = *(uint *)(this + 4);
  piVar7 = *(int **)(iVar14 + DAT_000631bc);
  this[0x19d] = (cRSubGolb)0x0;
  this[0x19c] = (cRSubGolb)0x0;
  iVar11 = *piVar7;
  if ((uVar5 & 0x200) == 0) {
    if (*(int *)(iVar11 + 0x35c) == 0) {
      *(cRSubGolb **)(iVar11 + 0x35c) = this;
      *(undefined4 *)(this + 8) = 0;
      *(undefined4 *)(*(int *)(iVar11 + 0x35c) + 0xc) = 0;
    }
    else {
      *(cRSubGolb **)(*(int *)(iVar11 + 0x35c) + 8) = this;
      *(int *)(*(int *)(*(int *)(iVar11 + 0x35c) + 8) + 0xc) = *(int *)(iVar11 + 0x35c);
      iVar8 = *(int *)(*(int *)(iVar11 + 0x35c) + 8);
      *(int *)(iVar11 + 0x35c) = iVar8;
      *(undefined4 *)(iVar8 + 8) = 0;
    }
    *(uint *)(this + 4) = uVar5 | 0x200;
  }
  else {
    RShellError((char *)(iVar14 + DAT_000631c8));
  }
  uVar5 = *(uint *)(param_1 + 0x324);
  *(cRSubGoldy **)(this + 600) = param_1;
  if ((uVar5 & 7) == 0) {
    if ((uVar5 & 0x18) == 0) {
      if ((uVar5 & 0x60) != 0) {
        *(undefined4 *)(this + 0x1a0) = 2;
      }
    }
    else {
      *(undefined4 *)(this + 0x1a0) = 1;
    }
  }
  else {
    *(undefined4 *)(this + 0x1a0) = 0;
  }
  ptVar13 = (tVector *)(this + 0x1d4);
  tMatrix::Identity((tMatrix *)(this + 0x25c));
  fVar21 = DAT_00063190;
  iVar11 = *(int *)(this + 600);
  fVar20 = *(float *)(iVar11 + 0x4c);
  fVar18 = *(float *)(iVar11 + 0x50);
  fVar19 = *(float *)(iVar11 + 0x54);
  uVar2 = *(undefined4 *)(iVar11 + 0x5c);
  uVar6 = *(undefined4 *)(iVar11 + 0x60);
  uVar9 = *(undefined4 *)(iVar11 + 100);
  *(undefined4 *)(this + 0x224) = 1;
  *(undefined4 *)(this + 0x198) = 0;
  uVar5 = *(uint *)(iVar11 + 0x324);
  *(undefined4 *)ptVar13 = uVar2;
  *(undefined4 *)(this + 0x1d8) = uVar6;
  *(undefined4 *)(this + 0x1dc) = uVar9;
  fVar20 = *(float *)(this + 0x1d4) + fVar21 * fVar20;
  *(float *)(this + 0x1d4) = fVar20;
  *(float *)(this + 0x1d8) = *(float *)(this + 0x1d8) + fVar21 * fVar18;
  *(float *)(this + 0x1dc) = *(float *)(this + 0x1dc) + fVar21 * fVar19;
  fVar18 = DAT_000631ec;
  uVar2 = DAT_000631e8;
  if ((uVar5 & 5) == 0) {
    if ((uVar5 & 2) != 0) {
      if (param_2 == 2) {
        uVar2 = *(undefined4 *)(iVar11 + 0x3df8);
        uVar6 = *(undefined4 *)(iVar11 + 0x3dfc);
        *(undefined4 *)ptVar13 = *(undefined4 *)(iVar11 + 0x3df4);
        *(undefined4 *)(this + 0x1d8) = uVar2;
        *(undefined4 *)(this + 0x1dc) = uVar6;
        *(float *)(this + 0x1d4) = *(float *)(this + 0x1d4) + fVar21;
      }
      else if (param_2 == 1) {
        uVar2 = *(undefined4 *)(iVar11 + 0x3e10);
        uVar6 = *(undefined4 *)(iVar11 + 0x3e14);
        *(undefined4 *)ptVar13 = *(undefined4 *)(iVar11 + 0x3e0c);
        *(undefined4 *)(this + 0x1d8) = uVar2;
        *(undefined4 *)(this + 0x1dc) = uVar6;
        *(float *)(this + 0x1d4) = *(float *)(this + 0x1d4) - fVar21;
      }
      goto LAB_00062e54;
    }
    if ((uVar5 & 0x18) == 0) {
      if ((uVar5 & 0x60) == 0) {
        if ((uVar5 & 0x29) != 0) goto LAB_00062e54;
        if ((uVar5 & 0x52) != 0) {
          *(undefined4 *)(this + 0x22c) = DAT_000631e8;
          fVar19 = *(float *)(iVar11 + 0x410);
          *(undefined4 *)(this + 0x230) = uVar2;
          fVar18 = DAT_000631e4;
          if (param_2 == 2) {
            fVar20 = fVar20 + fVar21;
            *(float *)(this + 0x1d4) = fVar20;
          }
          else {
            fVar20 = fVar20 - fVar21;
          }
          if (param_2 != 2) {
            *(float *)(this + 0x1d4) = fVar20;
          }
          *(float *)(this + 0x234) = fVar18 + fVar19;
        }
      }
      else {
        uVar6 = *(undefined4 *)(iVar11 + 0x3e6c);
        uVar9 = *(undefined4 *)(iVar11 + 0x3e70);
        uVar15 = *(undefined4 *)(iVar11 + 0x3e74);
        *(undefined4 *)(this + 0x22c) = DAT_000631e8;
        *(undefined4 *)(this + 0x230) = uVar2;
        *(undefined4 *)ptVar13 = uVar6;
        *(undefined4 *)(this + 0x1d8) = uVar9;
        *(undefined4 *)(this + 0x1dc) = uVar15;
        *(float *)(this + 0x234) = fVar18 + *(float *)(iVar11 + 0x410);
      }
    }
    else {
      if (param_2 == 2) {
        uVar5 = in_fpscr & 0xfffffff | (uint)(fVar19 < 0.0) << 0x1f | (uint)(fVar19 == 0.0) << 0x1e;
        in_fpscr = uVar5 | (uint)NAN(fVar19) << 0x1c;
        uVar2 = *(undefined4 *)(iVar11 + 0x3e40);
        uVar6 = *(undefined4 *)(iVar11 + 0x3e44);
        bVar1 = (byte)(uVar5 >> 0x18);
        *(undefined4 *)ptVar13 = *(undefined4 *)(iVar11 + 0x3e3c);
        *(undefined4 *)(this + 0x1d8) = uVar2;
        *(undefined4 *)(this + 0x1dc) = uVar6;
        if ((bool)(bVar1 >> 6 & 1) || bVar1 >> 7 != ((byte)(in_fpscr >> 0x1c) & 1))
        goto LAB_000634fc;
LAB_00063358:
        unaff_r9 = (float *)(iVar11 + 0x3e44);
      }
      else {
        uVar5 = in_fpscr & 0xfffffff | (uint)(fVar19 < 0.0) << 0x1f | (uint)(fVar19 == 0.0) << 0x1e;
        in_fpscr = uVar5 | (uint)NAN(fVar19) << 0x1c;
        uVar2 = *(undefined4 *)(iVar11 + 0x3e4c);
        uVar6 = *(undefined4 *)(iVar11 + 0x3e50);
        bVar1 = (byte)(uVar5 >> 0x18);
        *(undefined4 *)ptVar13 = *(undefined4 *)(iVar11 + 0x3e48);
        *(undefined4 *)(this + 0x1d8) = uVar2;
        *(undefined4 *)(this + 0x1dc) = uVar6;
        if (!(bool)(bVar1 >> 6 & 1) && bVar1 >> 7 == ((byte)(in_fpscr >> 0x1c) & 1))
        goto LAB_00063358;
LAB_000634fc:
        unaff_r9 = (float *)0x0;
      }
      uVar2 = DAT_000631e8;
      *(undefined4 *)(this + 0x22c) = DAT_000631e8;
      fVar20 = *(float *)(iVar11 + 0x410);
      *(undefined4 *)(this + 0x230) = uVar2;
      fVar20 = DAT_000631e4 + fVar20;
      this[0x19c] = (cRSubGolb)0x1;
      *(float *)(this + 0x234) = fVar20;
    }
  }
  else {
    if (param_2 == 3) {
      uVar2 = *(undefined4 *)(iVar11 + 0x3df8);
      uVar6 = *(undefined4 *)(iVar11 + 0x3dfc);
      *(undefined4 *)ptVar13 = *(undefined4 *)(iVar11 + 0x3df4);
      *(undefined4 *)(this + 0x1d8) = uVar2;
      *(undefined4 *)(this + 0x1dc) = uVar6;
    }
    else if (param_2 == 2) {
      uVar2 = *(undefined4 *)(iVar11 + 0x3e10);
      uVar6 = *(undefined4 *)(iVar11 + 0x3e14);
      *(undefined4 *)ptVar13 = *(undefined4 *)(iVar11 + 0x3e0c);
      *(undefined4 *)(this + 0x1d8) = uVar2;
      *(undefined4 *)(this + 0x1dc) = uVar6;
    }
    else if (param_2 == 1) {
      uVar2 = *(undefined4 *)(iVar11 + 0x3e28);
      uVar6 = *(undefined4 *)(iVar11 + 0x3e2c);
      *(undefined4 *)ptVar13 = *(undefined4 *)(iVar11 + 0x3e24);
      *(undefined4 *)(this + 0x1d8) = uVar2;
      *(undefined4 *)(this + 0x1dc) = uVar6;
    }
    if ((uVar5 & 4) != 0) {
      if (param_2 == 3) {
        fVar21 = *(float *)(iVar11 + 0x410);
        fVar20 = *(float *)(this + 0x1d4) + DAT_000631dc;
        *(undefined4 *)(this + 0x230) = DAT_000631e8;
        uVar2 = DAT_000631e0;
      }
      else {
        if (param_2 != 2) goto LAB_00062e54;
        fVar21 = *(float *)(iVar11 + 0x410);
        fVar20 = *(float *)(this + 0x1d4) - DAT_00063190;
        *(undefined4 *)(this + 0x230) = DAT_000631e8;
        uVar2 = DAT_000631b0;
      }
      *(undefined4 *)(this + 0x22c) = uVar2;
      fVar21 = DAT_000631e4 + fVar21;
      iVar8 = *(int *)(this + 0x1a0);
      *(float *)(this + 0x1d4) = fVar20;
      *(float *)(this + 0x234) = fVar21;
      fVar20 = DAT_000631cc;
      goto joined_r0x00063078;
    }
LAB_00062e54:
    uVar2 = DAT_000631e8;
    *(undefined4 *)(this + 0x22c) = DAT_000631e8;
    fVar20 = *(float *)(iVar11 + 0x410);
    *(undefined4 *)(this + 0x230) = uVar2;
    *(float *)(this + 0x234) = DAT_000631e4 + fVar20;
  }
  iVar8 = *(int *)(this + 0x1a0);
  fVar20 = DAT_000631cc;
joined_r0x00063078:
  DAT_000631cc = fVar20;
  if (iVar8 == 1) {
    *(float *)(this + 0x22c) = *(float *)(this + 0x22c) + *(float *)(this + 0x22c);
    *(float *)(this + 0x230) = *(float *)(this + 0x230) + *(float *)(this + 0x230);
    *(float *)(this + 0x234) = *(float *)(this + 0x234) + *(float *)(this + 0x234);
    *(undefined4 *)(this + 0x238) = *(undefined4 *)(this + 0x22c);
    *(undefined4 *)(this + 0x23c) = *(undefined4 *)(this + 0x230);
    *(undefined4 *)(this + 0x240) = *(undefined4 *)(this + 0x234);
    uVar2 = DAT_000631e8;
  }
  else {
    if (iVar8 == 2) {
      *(float *)(this + 0x22c) = *(float *)(this + 0x22c) * fVar20;
      *(float *)(this + 0x234) = *(float *)(this + 0x234) * fVar20;
      *(float *)(this + 0x230) = *(float *)(this + 0x230) * fVar20;
    }
    *(undefined4 *)(this + 0x238) = *(undefined4 *)(this + 0x22c);
    *(undefined4 *)(this + 0x23c) = *(undefined4 *)(this + 0x230);
    *(undefined4 *)(this + 0x240) = *(undefined4 *)(this + 0x234);
    uVar2 = DAT_000631e8;
  }
  DAT_000631e8 = uVar2;
  if (iVar8 == 1) {
    *(undefined4 *)(this + 0x248) = uVar2;
    fVar20 = *(float *)(*(int *)(this + 0x250) + 0x54) * DAT_00063194;
    piVar7 = *(int **)(iVar14 + iVar3);
    *(cRSubGolb **)(this + 0xfc) = this;
    iVar3 = *piVar7;
    *(float *)(this + 0x24c) = fVar20;
    if ((*(uint *)(this + 0x78) & 0x200) == 0) {
      uVar2 = *(undefined4 *)(iVar3 + 0x74680);
      *(int *)(this + 0x7c) = iVar3 + 0x74674;
      *(uint *)(this + 0x78) = *(uint *)(this + 0x78) | 0x200;
      *(undefined4 *)(this + 0x80) = uVar2;
      *(cRSubGolb **)(iVar3 + 0x74680) = this + 0x74;
      if (*(int *)(this + 0x80) != 0) {
        *(cRSubGolb **)(*(int *)(this + 0x80) + 8) = this + 0x74;
      }
    }
    else {
      RShellError((char *)(iVar14 + DAT_000631c4));
    }
    this_00 = (cRVapour *)(this + 0x74);
    cRVapour::ReSet(this_00,unaff_r9);
    tColourSmall::Set((tColourSmall *)(this + 0x9c),extraout_s0_00,extraout_s1_00,extraout_s2_00,
                      extraout_s3_00);
    *(int *)(this + 0x254) = param_3;
    cRVapour::Add(this_00,(tMatrix *)(this + 0x1a4));
    cRVapour::AI(this_00);
    iVar11 = *(int *)(this + 600);
  }
  else if (iVar8 == 2) {
    iVar11 = *(int *)(this + 0x250);
    *(undefined4 *)(this + 0x248) = uVar2;
    fVar20 = *(float *)(iVar11 + 0x54) * DAT_000631d0;
    uVar5 = *(uint *)(this + 0x104);
    *(undefined4 *)(this + 400) = uVar2;
    piVar7 = *(int **)(iVar14 + iVar3);
    *(undefined4 *)(this + 0x194) = DAT_000631d4;
    *(cRSubGolb **)(this + 0x184) = this;
    *(undefined4 *)(this + 0x174) = 0;
    iVar3 = *piVar7;
    *(float *)(this + 0x24c) = fVar20;
    if ((uVar5 & 0x200) == 0) {
      if (*(int *)(iVar3 + 0x35c) == 0) {
        *(cRSubGolb **)(iVar3 + 0x35c) = this + 0x100;
        *(undefined4 *)(this + 0x108) = 0;
        *(undefined4 *)(*(int *)(iVar3 + 0x35c) + 0xc) = 0;
      }
      else {
        *(cRSubGolb **)(*(int *)(iVar3 + 0x35c) + 8) = this + 0x100;
        *(int *)(*(int *)(*(int *)(iVar3 + 0x35c) + 8) + 0xc) = *(int *)(iVar3 + 0x35c);
        iVar14 = *(int *)(*(int *)(iVar3 + 0x35c) + 8);
        *(int *)(iVar3 + 0x35c) = iVar14;
        *(undefined4 *)(iVar14 + 8) = 0;
      }
      *(uint *)(this + 0x104) = uVar5 | 0x200;
    }
    else {
      RShellError((char *)(iVar14 + DAT_000631c8));
      iVar11 = *(int *)(this + 0x250);
    }
    *(int *)(this + 0x254) = param_3;
    puVar4 = (uint *)cREnemyManager::Find((cREnemyManager *)(gGroup0 + iVar11 + 0xc0700),ptVar13);
    uVar2 = DAT_000631e8;
    if (puVar4 == (uint *)0x0) {
      iVar11 = *(int *)(this + 600);
    }
    else {
      uVar5 = *puVar4;
      uVar12 = puVar4[5];
      bVar17 = uVar5 == 0;
      iVar11 = *(int *)(this + 600);
      if (bVar17) {
        uVar5 = *(uint *)(uVar12 + 4);
      }
      *(uint *)(this + 0x174) = uVar12;
      if (bVar17) {
        *(uint *)(uVar12 + 4) = uVar5 | 0x1000;
      }
      uVar5 = puVar4[1];
      uVar12 = puVar4[2];
      uVar10 = puVar4[3];
      *(undefined4 *)(this + 0x188) = uVar2;
      *(undefined4 *)(this + 0x18c) = DAT_000631d8;
      *(uint *)(this + 0x178) = uVar5;
      *(uint *)(this + 0x17c) = uVar12;
      *(uint *)(this + 0x180) = uVar10;
    }
  }
  else if (iVar8 == 0) {
    *(undefined4 *)(this + 0x248) = uVar2;
    iVar11 = *(int *)(iVar11 + 0x370);
    iVar3 = *(int *)(iVar14 + DAT_000631c0);
    *(float *)(this + 0x24c) = *(float *)(*(int *)(this + 0x250) + 0x54) * DAT_00063194;
    iVar3 = cRSpriteManager::New(iVar3,iVar11,0x76,-1);
    uVar5 = *(uint *)(iVar3 + 4);
    *(undefined4 *)(iVar3 + 0x78) = uVar2;
    *(undefined4 *)(iVar3 + 0x68) = uVar2;
    *(undefined4 *)(iVar3 + 0x6c) = uVar2;
    *(int *)(this + 0x228) = iVar3;
    *(uint *)(iVar3 + 4) = uVar5 | 0x800;
    tColour::tColour((tColour *)&local_38,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
    uVar2 = DAT_00063198;
    iVar8 = *(int *)(this + 0x228);
    *(undefined4 *)(iVar8 + 100) = DAT_00063198;
    *(undefined4 *)(iVar8 + 0x60) = uVar2;
    *(undefined4 *)(iVar3 + 0x2c) = local_38;
    *(undefined4 *)(iVar3 + 0x30) = uStack_34;
    *(undefined4 *)(iVar3 + 0x34) = uStack_30;
    *(undefined4 *)(iVar3 + 0x38) = uStack_2c;
    uVar2 = *(undefined4 *)(this + 0x1d8);
    uVar6 = *(undefined4 *)(this + 0x1dc);
    *(undefined4 *)(iVar8 + 0x48) = *(undefined4 *)ptVar13;
    *(undefined4 *)(iVar8 + 0x4c) = uVar2;
    *(undefined4 *)(iVar8 + 0x50) = uVar6;
    uVar2 = gRMathRand2();
    iVar3 = *(int *)(this + 0x250);
    iVar11 = *(int *)(this + 600);
    iVar14 = *(int *)(this + 0x228);
    *(int *)(this + 0x254) = param_3;
    fVar20 = (float)VectorSignedToFloat(uVar2,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(iVar8 + 0x7c) = (fVar20 - DAT_0006319c) * DAT_000631a0 * DAT_000631a4;
    *(float *)(iVar14 + 0x80) = *(float *)(iVar3 + 0x54) * DAT_000631a8;
  }
  uVar2 = DAT_000631ac;
  if ((*(char *)(iVar11 + 0x374) == '\0') || (DAT_00063190 <= *(float *)(iVar11 + 0x388))) {
    this[0x29c] = (cRSubGolb)0x0;
    *(undefined4 *)(this + 0x2c4) = uVar2;
  }
  else {
    *(undefined4 *)(this + 0x2ac) = *(undefined4 *)(iVar11 + 900);
    *(undefined4 *)(this + 0x2b0) = DAT_000631e8;
    uVar2 = *(undefined4 *)(iVar11 + 0x3a0);
    uVar6 = *(undefined4 *)(iVar11 + 0x3a4);
    uVar9 = *(undefined4 *)(iVar11 + 0x3a8);
    uVar15 = *(undefined4 *)(iVar11 + 0x37c);
    uVar16 = *(undefined4 *)(iVar11 + 0x380);
    *(undefined4 *)(this + 0x2a0) = *(undefined4 *)(iVar11 + 0x378);
    *(undefined4 *)(this + 0x2b4) = uVar2;
    *(undefined4 *)(this + 0x2b8) = uVar6;
    *(undefined4 *)(this + 700) = uVar9;
    *(undefined4 *)(this + 0x2c4) = *(undefined4 *)(iVar11 + 0x3a8);
    this[0x29c] = (cRSubGolb)0x1;
    *(undefined4 *)(this + 0x2a4) = uVar15;
    *(undefined4 *)(this + 0x2a8) = uVar16;
    *(cRSubGolb **)(this + 0x2c0) = this;
  }
  uVar2 = tVector::Magnitude((tVector *)(this + 0x22c));
  *(undefined4 *)(this + 0x244) = uVar2;
  *(undefined4 *)(this + 0x214) = *(undefined4 *)ptVar13;
  *(undefined4 *)(this + 0x218) = *(undefined4 *)(this + 0x1d8);
  *(undefined4 *)(this + 0x21c) = *(undefined4 *)(this + 0x1dc);
  (*(code *)**(undefined4 **)this)(this);
  return;
}
