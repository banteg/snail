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
  uint *puVar3;
  uint uVar4;
  undefined4 uVar5;
  int iVar6;
  undefined4 uVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  tVector *ptVar11;
  int iVar12;
  undefined4 uVar13;
  cRVapour *this_00;
  float *unaff_r9;
  int iVar14;
  undefined4 uVar15;
  bool bVar16;
  uint in_fpscr;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s1;
  float extraout_s1_00;
  float extraout_s2;
  float extraout_s2_00;
  float extraout_s3;
  float extraout_s3_00;
  float fVar17;
  float fVar18;
  float fVar19;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;

  uVar4 = *(uint *)(this + 4);
  this[0x19d] = (cRSubGolb)0x0;
  this[0x19c] = (cRSubGolb)0x0;
  iVar14 = Game;
  if ((uVar4 & 0x200) == 0) {
    if (*(int *)(Game + 0x35c) == 0) {
      *(cRSubGolb **)(Game + 0x35c) = this;
      *(undefined4 *)(this + 8) = 0;
      *(undefined4 *)(*(int *)(iVar14 + 0x35c) + 0xc) = 0;
    }
    else {
      *(cRSubGolb **)(*(int *)(Game + 0x35c) + 8) = this;
      *(int *)(*(int *)(*(int *)(iVar14 + 0x35c) + 8) + 0xc) = *(int *)(iVar14 + 0x35c);
      iVar6 = *(int *)(*(int *)(iVar14 + 0x35c) + 8);
      *(int *)(iVar14 + 0x35c) = iVar6;
      *(undefined4 *)(iVar6 + 8) = 0;
    }
    *(uint *)(this + 4) = uVar4 | 0x200;
  }
  else {
    RShellError("List ADD");
  }
  uVar4 = *(uint *)(param_1 + 0x324);
  *(cRSubGoldy **)(this + 600) = param_1;
  if ((uVar4 & 7) == 0) {
    if ((uVar4 & 0x18) == 0) {
      if ((uVar4 & 0x60) != 0) {
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
  ptVar11 = (tVector *)(this + 0x1d4);
  tMatrix::Identity((tMatrix *)(this + 0x25c));
  iVar14 = *(int *)(this + 600);
  fVar19 = *(float *)(iVar14 + 0x4c);
  fVar17 = *(float *)(iVar14 + 0x50);
  fVar18 = *(float *)(iVar14 + 0x54);
  uVar2 = *(undefined4 *)(iVar14 + 0x5c);
  uVar5 = *(undefined4 *)(iVar14 + 0x60);
  uVar7 = *(undefined4 *)(iVar14 + 100);
  *(undefined4 *)(this + 0x224) = 1;
  *(undefined4 *)(this + 0x198) = 0;
  uVar4 = *(uint *)(iVar14 + 0x324);
  *(undefined4 *)ptVar11 = uVar2;
  *(undefined4 *)(this + 0x1d8) = uVar5;
  *(undefined4 *)(this + 0x1dc) = uVar7;
  fVar19 = *(float *)(this + 0x1d4) + fVar19 * 0.5;
  *(float *)(this + 0x1d4) = fVar19;
  *(float *)(this + 0x1d8) = *(float *)(this + 0x1d8) + fVar17 * 0.5;
  *(float *)(this + 0x1dc) = *(float *)(this + 0x1dc) + fVar18 * 0.5;
  if ((uVar4 & 5) == 0) {
    if ((uVar4 & 2) != 0) {
      if (param_2 == 2) {
        uVar2 = *(undefined4 *)(iVar14 + 0x3df8);
        uVar5 = *(undefined4 *)(iVar14 + 0x3dfc);
        *(undefined4 *)ptVar11 = *(undefined4 *)(iVar14 + 0x3df4);
        *(undefined4 *)(this + 0x1d8) = uVar2;
        *(undefined4 *)(this + 0x1dc) = uVar5;
        *(float *)(this + 0x1d4) = *(float *)(this + 0x1d4) + 0.5;
      }
      else if (param_2 == 1) {
        uVar2 = *(undefined4 *)(iVar14 + 0x3e10);
        uVar5 = *(undefined4 *)(iVar14 + 0x3e14);
        *(undefined4 *)ptVar11 = *(undefined4 *)(iVar14 + 0x3e0c);
        *(undefined4 *)(this + 0x1d8) = uVar2;
        *(undefined4 *)(this + 0x1dc) = uVar5;
        *(float *)(this + 0x1d4) = *(float *)(this + 0x1d4) - 0.5;
      }
      goto LAB_00062e54;
    }
    if ((uVar4 & 0x18) == 0) {
      if ((uVar4 & 0x60) == 0) {
        if ((uVar4 & 0x29) != 0) goto LAB_00062e54;
        if ((uVar4 & 0x52) != 0) {
          *(undefined4 *)(this + 0x22c) = 0;
          fVar17 = *(float *)(iVar14 + 0x410);
          *(undefined4 *)(this + 0x230) = 0;
          if (param_2 == 2) {
            fVar19 = fVar19 + 0.5;
            *(float *)(this + 0x1d4) = fVar19;
          }
          else {
            fVar19 = fVar19 - 0.5;
          }
          if (param_2 != 2) {
            *(float *)(this + 0x1d4) = fVar19;
          }
          *(float *)(this + 0x234) = fVar17 + 1.0;
        }
      }
      else {
        uVar2 = *(undefined4 *)(iVar14 + 0x3e6c);
        uVar5 = *(undefined4 *)(iVar14 + 0x3e70);
        uVar7 = *(undefined4 *)(iVar14 + 0x3e74);
        *(undefined4 *)(this + 0x22c) = 0;
        *(undefined4 *)(this + 0x230) = 0;
        *(undefined4 *)ptVar11 = uVar2;
        *(undefined4 *)(this + 0x1d8) = uVar5;
        *(undefined4 *)(this + 0x1dc) = uVar7;
        *(float *)(this + 0x234) = *(float *)(iVar14 + 0x410) + 0.6;
      }
    }
    else {
      if (param_2 == 2) {
        uVar4 = in_fpscr & 0xfffffff | (uint)(fVar18 < 0.0) << 0x1f | (uint)(fVar18 == 0.0) << 0x1e;
        in_fpscr = uVar4 | (uint)NAN(fVar18) << 0x1c;
        uVar2 = *(undefined4 *)(iVar14 + 0x3e40);
        uVar5 = *(undefined4 *)(iVar14 + 0x3e44);
        bVar1 = (byte)(uVar4 >> 0x18);
        *(undefined4 *)ptVar11 = *(undefined4 *)(iVar14 + 0x3e3c);
        *(undefined4 *)(this + 0x1d8) = uVar2;
        *(undefined4 *)(this + 0x1dc) = uVar5;
        if ((bool)(bVar1 >> 6 & 1) || bVar1 >> 7 != ((byte)(in_fpscr >> 0x1c) & 1))
        goto LAB_000634fc;
LAB_00063358:
        unaff_r9 = (float *)(iVar14 + 0x3e44);
      }
      else {
        uVar4 = in_fpscr & 0xfffffff | (uint)(fVar18 < 0.0) << 0x1f | (uint)(fVar18 == 0.0) << 0x1e;
        in_fpscr = uVar4 | (uint)NAN(fVar18) << 0x1c;
        uVar2 = *(undefined4 *)(iVar14 + 0x3e4c);
        uVar5 = *(undefined4 *)(iVar14 + 0x3e50);
        bVar1 = (byte)(uVar4 >> 0x18);
        *(undefined4 *)ptVar11 = *(undefined4 *)(iVar14 + 0x3e48);
        *(undefined4 *)(this + 0x1d8) = uVar2;
        *(undefined4 *)(this + 0x1dc) = uVar5;
        if (!(bool)(bVar1 >> 6 & 1) && bVar1 >> 7 == ((byte)(in_fpscr >> 0x1c) & 1))
        goto LAB_00063358;
LAB_000634fc:
        unaff_r9 = (float *)0x0;
      }
      *(undefined4 *)(this + 0x22c) = 0;
      fVar19 = *(float *)(iVar14 + 0x410);
      *(undefined4 *)(this + 0x230) = 0;
      this[0x19c] = (cRSubGolb)0x1;
      *(float *)(this + 0x234) = fVar19 + 1.0;
    }
  }
  else {
    if (param_2 == 3) {
      uVar2 = *(undefined4 *)(iVar14 + 0x3df8);
      uVar5 = *(undefined4 *)(iVar14 + 0x3dfc);
      *(undefined4 *)ptVar11 = *(undefined4 *)(iVar14 + 0x3df4);
      *(undefined4 *)(this + 0x1d8) = uVar2;
      *(undefined4 *)(this + 0x1dc) = uVar5;
    }
    else if (param_2 == 2) {
      uVar2 = *(undefined4 *)(iVar14 + 0x3e10);
      uVar5 = *(undefined4 *)(iVar14 + 0x3e14);
      *(undefined4 *)ptVar11 = *(undefined4 *)(iVar14 + 0x3e0c);
      *(undefined4 *)(this + 0x1d8) = uVar2;
      *(undefined4 *)(this + 0x1dc) = uVar5;
    }
    else if (param_2 == 1) {
      uVar2 = *(undefined4 *)(iVar14 + 0x3e28);
      uVar5 = *(undefined4 *)(iVar14 + 0x3e2c);
      *(undefined4 *)ptVar11 = *(undefined4 *)(iVar14 + 0x3e24);
      *(undefined4 *)(this + 0x1d8) = uVar2;
      *(undefined4 *)(this + 0x1dc) = uVar5;
    }
    if ((uVar4 & 4) != 0) {
      if (param_2 == 3) {
        fVar17 = *(float *)(iVar14 + 0x410);
        fVar19 = *(float *)(this + 0x1d4) + 0.5;
        *(undefined4 *)(this + 0x230) = 0;
        uVar2 = 0x3dcccccd;
      }
      else {
        if (param_2 != 2) goto LAB_00062e54;
        fVar17 = *(float *)(iVar14 + 0x410);
        fVar19 = *(float *)(this + 0x1d4) - 0.5;
        *(undefined4 *)(this + 0x230) = 0;
        uVar2 = 0xbdcccccd;
      }
      *(undefined4 *)(this + 0x22c) = uVar2;
      iVar6 = *(int *)(this + 0x1a0);
      *(float *)(this + 0x1d4) = fVar19;
      *(float *)(this + 0x234) = fVar17 + 1.0;
      goto joined_r0x00063078;
    }
LAB_00062e54:
    *(undefined4 *)(this + 0x22c) = 0;
    fVar19 = *(float *)(iVar14 + 0x410);
    *(undefined4 *)(this + 0x230) = 0;
    *(float *)(this + 0x234) = fVar19 + 1.0;
  }
  iVar6 = *(int *)(this + 0x1a0);
joined_r0x00063078:
  if (iVar6 == 1) {
    *(float *)(this + 0x22c) = *(float *)(this + 0x22c) + *(float *)(this + 0x22c);
    *(float *)(this + 0x230) = *(float *)(this + 0x230) + *(float *)(this + 0x230);
    *(float *)(this + 0x234) = *(float *)(this + 0x234) + *(float *)(this + 0x234);
    *(undefined4 *)(this + 0x238) = *(undefined4 *)(this + 0x22c);
    *(undefined4 *)(this + 0x23c) = *(undefined4 *)(this + 0x230);
    *(undefined4 *)(this + 0x240) = *(undefined4 *)(this + 0x234);
  }
  else {
    if (iVar6 == 2) {
      *(float *)(this + 0x22c) = *(float *)(this + 0x22c) * 0.8;
      *(float *)(this + 0x234) = *(float *)(this + 0x234) * 0.8;
      *(float *)(this + 0x230) = *(float *)(this + 0x230) * 0.8;
    }
    *(undefined4 *)(this + 0x238) = *(undefined4 *)(this + 0x22c);
    *(undefined4 *)(this + 0x23c) = *(undefined4 *)(this + 0x230);
    *(undefined4 *)(this + 0x240) = *(undefined4 *)(this + 0x234);
  }
  if (iVar6 == 1) {
    *(undefined4 *)(this + 0x248) = 0;
    fVar19 = *(float *)(*(int *)(this + 0x250) + 0x54);
    *(cRSubGolb **)(this + 0xfc) = this;
    iVar14 = Game;
    *(float *)(this + 0x24c) = fVar19 * 0.041666668;
    if ((*(uint *)(this + 0x78) & 0x200) == 0) {
      uVar2 = *(undefined4 *)(iVar14 + 0x74680);
      *(int *)(this + 0x7c) = iVar14 + 0x74674;
      *(uint *)(this + 0x78) = *(uint *)(this + 0x78) | 0x200;
      *(undefined4 *)(this + 0x80) = uVar2;
      *(cRSubGolb **)(iVar14 + 0x74680) = this + 0x74;
      if (*(int *)(this + 0x80) != 0) {
        *(cRSubGolb **)(*(int *)(this + 0x80) + 8) = this + 0x74;
      }
    }
    else {
      RShellError("List ADDafter");
    }
    this_00 = (cRVapour *)(this + 0x74);
    cRVapour::ReSet(this_00,unaff_r9);
    tColourSmall::Set((tColourSmall *)(this + 0x9c),extraout_s0_00,extraout_s1_00,extraout_s2_00,
                      extraout_s3_00);
    *(int *)(this + 0x254) = param_3;
    cRVapour::Add(this_00,(tMatrix *)(this + 0x1a4));
    cRVapour::AI(this_00);
    iVar14 = *(int *)(this + 600);
  }
  else if (iVar6 == 2) {
    iVar6 = *(int *)(this + 0x250);
    *(undefined4 *)(this + 0x248) = 0;
    fVar19 = *(float *)(iVar6 + 0x54);
    uVar4 = *(uint *)(this + 0x104);
    *(undefined4 *)(this + 400) = 0;
    *(undefined4 *)(this + 0x194) = 0x3e567751;
    *(cRSubGolb **)(this + 0x184) = this;
    *(undefined4 *)(this + 0x174) = 0;
    iVar14 = Game;
    *(float *)(this + 0x24c) = fVar19 * 0.027777778;
    if ((uVar4 & 0x200) == 0) {
      if (*(int *)(iVar14 + 0x35c) == 0) {
        *(cRSubGolb **)(iVar14 + 0x35c) = this + 0x100;
        *(undefined4 *)(this + 0x108) = 0;
        *(undefined4 *)(*(int *)(iVar14 + 0x35c) + 0xc) = 0;
      }
      else {
        *(cRSubGolb **)(*(int *)(iVar14 + 0x35c) + 8) = this + 0x100;
        *(int *)(*(int *)(*(int *)(iVar14 + 0x35c) + 8) + 0xc) = *(int *)(iVar14 + 0x35c);
        iVar9 = *(int *)(*(int *)(iVar14 + 0x35c) + 8);
        *(int *)(iVar14 + 0x35c) = iVar9;
        *(undefined4 *)(iVar9 + 8) = 0;
      }
      *(uint *)(this + 0x104) = uVar4 | 0x200;
    }
    else {
      RShellError("List ADD");
      iVar6 = *(int *)(this + 0x250);
    }
    *(int *)(this + 0x254) = param_3;
    puVar3 = (uint *)cREnemyManager::Find((cREnemyManager *)(gGroup0 + iVar6 + 0xc0700),ptVar11);
    if (puVar3 == (uint *)0x0) {
      iVar14 = *(int *)(this + 600);
    }
    else {
      uVar4 = *puVar3;
      uVar10 = puVar3[5];
      bVar16 = uVar4 == 0;
      iVar14 = *(int *)(this + 600);
      if (bVar16) {
        uVar4 = *(uint *)(uVar10 + 4);
      }
      *(uint *)(this + 0x174) = uVar10;
      if (bVar16) {
        *(uint *)(uVar10 + 4) = uVar4 | 0x1000;
      }
      uVar4 = puVar3[1];
      uVar10 = puVar3[2];
      uVar8 = puVar3[3];
      *(undefined4 *)(this + 0x188) = 0;
      *(undefined4 *)(this + 0x18c) = 0x3d088889;
      *(uint *)(this + 0x178) = uVar4;
      *(uint *)(this + 0x17c) = uVar10;
      *(uint *)(this + 0x180) = uVar8;
    }
  }
  else if (iVar6 == 0) {
    *(undefined4 *)(this + 0x248) = 0;
    iVar14 = *(int *)(iVar14 + 0x370);
    *(float *)(this + 0x24c) = *(float *)(*(int *)(this + 0x250) + 0x54) * 0.041666668;
    iVar14 = cRSpriteManager::New((int)&gRSpriteManager,iVar14,0x76,-1);
    uVar4 = *(uint *)(iVar14 + 4);
    *(undefined4 *)(iVar14 + 0x78) = 0;
    *(undefined4 *)(iVar14 + 0x68) = 0;
    *(undefined4 *)(iVar14 + 0x6c) = 0;
    *(int *)(this + 0x228) = iVar14;
    *(uint *)(iVar14 + 4) = uVar4 | 0x800;
    tColour::tColour((tColour *)&local_38,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
    iVar12 = *(int *)(this + 0x228);
    *(undefined4 *)(iVar12 + 100) = 0x3efae148;
    *(undefined4 *)(iVar12 + 0x60) = 0x3efae148;
    *(undefined4 *)(iVar14 + 0x2c) = local_38;
    *(undefined4 *)(iVar14 + 0x30) = uStack_34;
    *(undefined4 *)(iVar14 + 0x34) = uStack_30;
    *(undefined4 *)(iVar14 + 0x38) = uStack_2c;
    uVar2 = *(undefined4 *)(this + 0x1d8);
    uVar5 = *(undefined4 *)(this + 0x1dc);
    *(undefined4 *)(iVar12 + 0x48) = *(undefined4 *)ptVar11;
    *(undefined4 *)(iVar12 + 0x4c) = uVar2;
    *(undefined4 *)(iVar12 + 0x50) = uVar5;
    uVar2 = gRMathRand2();
    iVar6 = *(int *)(this + 0x250);
    iVar14 = *(int *)(this + 600);
    iVar9 = *(int *)(this + 0x228);
    *(int *)(this + 0x254) = param_3;
    fVar19 = (float)VectorSignedToFloat(uVar2,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(iVar12 + 0x7c) = (fVar19 - 16384.0) * 6.1035156e-05 * 3.1415927;
    *(float *)(iVar9 + 0x80) = *(float *)(iVar6 + 0x54) * 0.58177644;
  }
  if ((*(char *)(iVar14 + 0x374) == '\0') || (0.5 <= *(float *)(iVar14 + 0x388))) {
    this[0x29c] = (cRSubGolb)0x0;
    *(undefined4 *)(this + 0x2c4) = 0xbf800000;
  }
  else {
    *(undefined4 *)(this + 0x2ac) = *(undefined4 *)(iVar14 + 900);
    *(undefined4 *)(this + 0x2b0) = 0;
    uVar2 = *(undefined4 *)(iVar14 + 0x3a0);
    uVar5 = *(undefined4 *)(iVar14 + 0x3a4);
    uVar7 = *(undefined4 *)(iVar14 + 0x3a8);
    uVar13 = *(undefined4 *)(iVar14 + 0x37c);
    uVar15 = *(undefined4 *)(iVar14 + 0x380);
    *(undefined4 *)(this + 0x2a0) = *(undefined4 *)(iVar14 + 0x378);
    *(undefined4 *)(this + 0x2b4) = uVar2;
    *(undefined4 *)(this + 0x2b8) = uVar5;
    *(undefined4 *)(this + 700) = uVar7;
    *(undefined4 *)(this + 0x2c4) = *(undefined4 *)(iVar14 + 0x3a8);
    this[0x29c] = (cRSubGolb)0x1;
    *(undefined4 *)(this + 0x2a4) = uVar13;
    *(undefined4 *)(this + 0x2a8) = uVar15;
    *(cRSubGolb **)(this + 0x2c0) = this;
  }
  uVar2 = tVector::Magnitude((tVector *)(this + 0x22c));
  *(undefined4 *)(this + 0x244) = uVar2;
  *(undefined4 *)(this + 0x214) = *(undefined4 *)ptVar11;
  *(undefined4 *)(this + 0x218) = *(undefined4 *)(this + 0x1d8);
  *(undefined4 *)(this + 0x21c) = *(undefined4 *)(this + 0x1dc);
  (*(code *)**(undefined4 **)this)(this);
  return;
}
