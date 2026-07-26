/*
 * mangled: _ZN9cRSubGolb6CreateEP10cRSubGoldyii
 * demangled: cRSubGolb::Create(cRSubGoldy*, int, int)
 * address: 0003f9a4
 * size: 2192
 */

/* cRSubGolb::Create(cRSubGoldy*, int, int) */

void __thiscall cRSubGolb::Create(cRSubGolb *this,cRSubGoldy *param_1,int param_2,int param_3)

{
  undefined *puVar1;
  undefined4 *puVar2;
  uint uVar3;
  undefined4 uVar4;
  int *piVar5;
  int iVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  int iVar9;
  int iVar10;
  cRVapour *this_00;
  float *pfVar11;
  cRSubGolb *pcVar12;
  byte bVar13;
  bool bVar14;
  byte bVar15;
  uint in_fpscr;
  float fVar16;
  float fVar17;
  float fVar18;
  ulonglong uVar19;
  tVector *local_48;
  undefined4 local_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  float local_34;
  float local_30;
  float local_2c;

  this[0x19c] = (cRSubGolb)0x0;
  this[0x19d] = (cRSubGolb)0x0;
  iVar6 = *(int *)PTR__Game_001b60b8;
  if ((*(uint *)(this + 4) & 0x200) == 0) {
    if (*(int *)(iVar6 + 0x35c) == 0) {
      *(cRSubGolb **)(iVar6 + 0x35c) = this;
      *(undefined4 *)(this + 8) = 0;
      *(undefined4 *)(*(int *)(iVar6 + 0x35c) + 0xc) = 0;
    }
    else {
      *(cRSubGolb **)(*(int *)(iVar6 + 0x35c) + 8) = this;
      *(int *)(*(int *)(*(int *)(iVar6 + 0x35c) + 8) + 0xc) = *(int *)(iVar6 + 0x35c);
      iVar10 = *(int *)(*(int *)(iVar6 + 0x35c) + 8);
      *(int *)(iVar6 + 0x35c) = iVar10;
      *(undefined4 *)(iVar10 + 8) = 0;
    }
    *(uint *)(this + 4) = *(uint *)(this + 4) | 0x200;
  }
  else {
    RShellError("List ADD");
  }
  *(cRSubGoldy **)(this + 600) = param_1;
  uVar3 = *(uint *)(param_1 + 0x324);
  if ((uVar3 & 7) == 0) {
    if ((uVar3 & 0x18) == 0) {
      if ((uVar3 & 0x60) != 0) {
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
  tMatrix::Identity((tMatrix *)(this + 0x25c));
  iVar6 = *(int *)(this + 600);
  *(undefined4 *)(this + 0x224) = 1;
  *(undefined4 *)(this + 0x198) = 0;
  uVar4 = *(undefined4 *)(iVar6 + 0x60);
  uVar7 = *(undefined4 *)(iVar6 + 100);
  pcVar12 = this + 0x1d4;
  fVar18 = *(float *)(iVar6 + 0x4c);
  fVar16 = *(float *)(iVar6 + 0x50);
  *(undefined4 *)pcVar12 = *(undefined4 *)(iVar6 + 0x5c);
  *(undefined4 *)(this + 0x1d8) = uVar4;
  *(undefined4 *)(this + 0x1dc) = uVar7;
  fVar17 = *(float *)(iVar6 + 0x54);
  fVar18 = *(float *)(this + 0x1d4) + fVar18 * 0.5;
  *(float *)(this + 0x1d4) = fVar18;
  *(float *)(this + 0x1d8) = *(float *)(this + 0x1d8) + fVar16 * 0.5;
  *(float *)(this + 0x1dc) = *(float *)(this + 0x1dc) + fVar17 * 0.5;
  uVar3 = *(uint *)(iVar6 + 0x324);
  if (((uVar3 & 1) == 0) && ((uVar3 & 4) == 0)) {
    if ((uVar3 & 2) != 0) {
      if (param_2 == 2) {
        uVar4 = *(undefined4 *)(iVar6 + 0x3df0);
        uVar7 = *(undefined4 *)((int)&DAT_00003df4 + iVar6);
        *(undefined4 *)pcVar12 = *(undefined4 *)(iVar6 + 0x3dec);
        *(undefined4 *)(this + 0x1d8) = uVar4;
        *(undefined4 *)(this + 0x1dc) = uVar7;
        *(float *)(this + 0x1d4) = *(float *)(this + 0x1d4) + 0.5;
      }
      else if (param_2 == 1) {
        uVar4 = *(undefined4 *)(&__GLOBAL__I__ZN13OFSmartObject6s_RTTIE + iVar6);
        uVar7 = *(undefined4 *)(&LAB_00003e0c + iVar6);
        *(undefined4 *)pcVar12 = *(undefined4 *)((int)&DAT_00003e04 + iVar6);
        *(undefined4 *)(this + 0x1d8) = uVar4;
        *(undefined4 *)(this + 0x1dc) = uVar7;
        *(float *)(this + 0x1d4) = *(float *)(this + 0x1d4) - 0.5;
      }
      goto LAB_0003fb00;
    }
    if ((uVar3 & 0x18) == 0) {
      if ((uVar3 & 0x60) == 0) {
        if ((uVar3 & 0x29) != 0) goto LAB_0003fb00;
        if ((uVar3 & 0x52) != 0) {
          fVar16 = *(float *)(iVar6 + 0x408);
          *(undefined4 *)(this + 0x230) = 0;
          *(undefined4 *)(this + 0x22c) = 0;
          *(float *)(this + 0x234) = fVar16 + 1.0;
          if (param_2 == 2) {
            *(float *)(this + 0x1d4) = fVar18 + 0.5;
          }
          else {
            *(float *)(this + 0x1d4) = fVar18 - 0.5;
          }
        }
        goto LAB_0003fb24;
      }
      uVar4 = *(undefined4 *)((int)&DAT_00003e68 + iVar6);
      uVar7 = *(undefined4 *)((int)&DAT_00003e6c + iVar6);
      fVar17 = 0.6;
      *(undefined4 *)pcVar12 = *(undefined4 *)((int)&DAT_00003e64 + iVar6);
      *(undefined4 *)(this + 0x1d8) = uVar4;
      *(undefined4 *)(this + 0x1dc) = uVar7;
      fVar16 = *(float *)(iVar6 + 0x408);
      goto LAB_0003fb10;
    }
    if (param_2 == 2) {
      puVar2 = (undefined4 *)(iVar6 + 0x3e34);
    }
    else {
      puVar2 = (undefined4 *)(iVar6 + 0x3e40);
    }
    uVar4 = puVar2[1];
    uVar7 = puVar2[2];
    uVar3 = in_fpscr & 0xfffffff | (uint)(fVar17 < 0.0) << 0x1f | (uint)(fVar17 == 0.0) << 0x1e;
    in_fpscr = uVar3 | (uint)NAN(fVar17) << 0x1c;
    *(undefined4 *)pcVar12 = *puVar2;
    *(undefined4 *)(this + 0x1d8) = uVar4;
    *(undefined4 *)(this + 0x1dc) = uVar7;
    fVar16 = *(float *)(iVar6 + 0x408);
    bVar15 = (byte)(uVar3 >> 0x18);
    bVar13 = bVar15 >> 7;
    bVar14 = (bool)(bVar15 >> 6 & 1);
    bVar15 = (byte)(in_fpscr >> 0x1c) & 1;
    *(undefined4 *)(this + 0x230) = 0;
    if (!bVar14 && bVar13 == bVar15) {
      param_2 = iVar6 + 0x3e00;
    }
    *(undefined4 *)(this + 0x22c) = 0;
    if (bVar14 || bVar13 != bVar15) {
      param_2 = 0;
    }
    else {
      param_2 = param_2 + 0x3c;
    }
    this[0x19c] = (cRSubGolb)0x1;
    *(float *)(this + 0x234) = fVar16 + 1.0;
  }
  else {
    if (param_2 == 3) {
      uVar4 = *(undefined4 *)(iVar6 + 0x3df0);
      uVar7 = *(undefined4 *)((int)&DAT_00003df4 + iVar6);
      *(undefined4 *)pcVar12 = *(undefined4 *)(iVar6 + 0x3dec);
      *(undefined4 *)(this + 0x1d8) = uVar4;
      *(undefined4 *)(this + 0x1dc) = uVar7;
      uVar3 = *(uint *)(iVar6 + 0x324);
    }
    else if (param_2 == 2) {
      uVar4 = *(undefined4 *)(&__GLOBAL__I__ZN13OFSmartObject6s_RTTIE + iVar6);
      uVar7 = *(undefined4 *)(&LAB_00003e0c + iVar6);
      *(undefined4 *)pcVar12 = *(undefined4 *)((int)&DAT_00003e04 + iVar6);
      *(undefined4 *)(this + 0x1d8) = uVar4;
      *(undefined4 *)(this + 0x1dc) = uVar7;
      uVar3 = *(uint *)(iVar6 + 0x324);
    }
    else if (param_2 == 1) {
      uVar4 = *(undefined4 *)(iVar6 + 0x3e20);
      uVar7 = *(undefined4 *)(iVar6 + 0x3e24);
      *(undefined4 *)pcVar12 =
           *(undefined4 *)(::__static_initialization_and_destruction_0 + iVar6 + 4);
      *(undefined4 *)(this + 0x1d8) = uVar4;
      *(undefined4 *)(this + 0x1dc) = uVar7;
      uVar3 = *(uint *)(iVar6 + 0x324);
    }
    if ((uVar3 & 4) != 0) {
      if (param_2 == 3) {
        fVar16 = *(float *)(iVar6 + 0x408);
        *(undefined4 *)(this + 0x230) = 0;
        *(undefined4 *)(this + 0x22c) = 0x3dcccccd;
        *(float *)(this + 0x234) = fVar16 + 1.0;
        *(float *)(this + 0x1d4) = *(float *)(this + 0x1d4) + 0.5;
      }
      else {
        if (param_2 != 2) goto LAB_0003fb00;
        fVar16 = *(float *)(iVar6 + 0x408);
        *(undefined4 *)(this + 0x230) = 0;
        *(undefined4 *)(this + 0x22c) = 0xbdcccccd;
        *(float *)(this + 0x234) = fVar16 + 1.0;
        *(float *)(this + 0x1d4) = *(float *)(this + 0x1d4) - 0.5;
      }
      goto LAB_0003fb24;
    }
LAB_0003fb00:
    fVar17 = 1.0;
    fVar16 = *(float *)(iVar6 + 0x408);
LAB_0003fb10:
    *(undefined4 *)(this + 0x230) = 0;
    *(undefined4 *)(this + 0x22c) = 0;
    *(float *)(this + 0x234) = fVar16 + fVar17;
  }
LAB_0003fb24:
  iVar10 = *(int *)(this + 0x1a0);
  if (iVar10 == 1) {
    *(float *)(this + 0x22c) = *(float *)(this + 0x22c) + *(float *)(this + 0x22c);
    *(float *)(this + 0x230) = *(float *)(this + 0x230) + *(float *)(this + 0x230);
    *(float *)(this + 0x234) = *(float *)(this + 0x234) + *(float *)(this + 0x234);
LAB_0003fb38:
    *(undefined4 *)(this + 0x238) = *(undefined4 *)(this + 0x22c);
    *(undefined4 *)(this + 0x23c) = *(undefined4 *)(this + 0x230);
    *(undefined4 *)(this + 0x240) = *(undefined4 *)(this + 0x234);
    if (iVar10 == 1) {
      *(undefined4 *)(this + 0x248) = 0;
      uVar3 = *(uint *)(this + 0x78);
      fVar16 = *(float *)(*(int *)(this + 0x250) + 0x4c);
      *(cRSubGolb **)(this + 0xfc) = this;
      puVar1 = PTR__Game_001b60b8;
      *(float *)(this + 0x24c) = fVar16 * 0.041666668;
      iVar6 = *(int *)puVar1;
      if ((uVar3 & 0x200) == 0) {
        *(int *)(this + 0x7c) = (int)&DAT_000752d4 + iVar6;
        *(undefined4 *)(this + 0x80) = *(undefined4 *)(iVar6 + 0x752e0);
        *(cRSubGolb **)(iVar6 + 0x752e0) = this + 0x74;
        if (*(int *)(this + 0x80) != 0) {
          *(cRSubGolb **)(*(int *)(this + 0x80) + 8) = this + 0x74;
        }
        *(uint *)(this + 0x78) = uVar3 | 0x200;
      }
      else {
        RShellError("List ADDafter");
      }
      this_00 = (cRVapour *)(this + 0x74);
      cRVapour::ReSet(this_00,(float *)param_2);
      tColourSmall::Set((tColourSmall *)(this + 0x9c),1.0,1.0,1.0,0.99);
      *(int *)(this + 0x254) = param_3;
      cRVapour::Add(this_00,(tMatrix *)(this + 0x1a4));
      cRVapour::AI(this_00);
      iVar6 = *(int *)(this + 600);
      goto LAB_0003fc60;
    }
  }
  else {
    if (iVar10 != 2) goto LAB_0003fb38;
    *(float *)(this + 0x22c) = *(float *)(this + 0x22c) * 0.8;
    *(float *)(this + 0x230) = *(float *)(this + 0x230) * 0.8;
    *(float *)(this + 0x234) = *(float *)(this + 0x234) * 0.8;
    *(undefined4 *)(this + 0x238) = *(undefined4 *)(this + 0x22c);
    *(undefined4 *)(this + 0x23c) = *(undefined4 *)(this + 0x230);
    *(undefined4 *)(this + 0x240) = *(undefined4 *)(this + 0x234);
  }
  if (iVar10 == 2) {
    *(undefined4 *)(this + 0x248) = 0;
    fVar16 = *(float *)(*(int *)(this + 0x250) + 0x4c);
    *(cRSubGolb **)(this + 0x184) = this;
    *(undefined4 *)(this + 400) = 0;
    *(undefined4 *)(this + 0x194) = 0x3e567751;
    *(undefined4 *)(this + 0x174) = 0;
    *(float *)(this + 0x24c) = fVar16 * 0.027777778;
    iVar6 = *(int *)PTR__Game_001b60b8;
    if ((*(uint *)(this + 0x104) & 0x200) == 0) {
      if (*(int *)(iVar6 + 0x35c) == 0) {
        *(cRSubGolb **)(iVar6 + 0x35c) = this + 0x100;
        *(undefined4 *)(this + 0x108) = 0;
        *(undefined4 *)(*(int *)(iVar6 + 0x35c) + 0xc) = 0;
      }
      else {
        *(cRSubGolb **)(*(int *)(iVar6 + 0x35c) + 8) = this + 0x100;
        *(int *)(*(int *)(*(int *)(iVar6 + 0x35c) + 8) + 0xc) = *(int *)(iVar6 + 0x35c);
        iVar10 = *(int *)(*(int *)(iVar6 + 0x35c) + 8);
        *(int *)(iVar6 + 0x35c) = iVar10;
        *(undefined4 *)(iVar10 + 8) = 0;
      }
      *(uint *)(this + 0x104) = *(uint *)(this + 0x104) | 0x200;
    }
    else {
      RShellError("List ADD");
    }
    iVar6 = *(int *)(this + 0x250);
    *(int *)(this + 0x254) = param_3;
    if (0 < *(int *)(&DAT_00303ab4 + iVar6)) {
      uVar19 = 0x4e6e6b28;
      piVar5 = (int *)0x0;
      pfVar11 = (float *)(&DAT_00303abc + iVar6);
      iVar10 = 0;
      do {
        while( true ) {
          local_34 = *pfVar11 - *(float *)(this + 0x1d4);
          local_30 = pfVar11[1] - *(float *)(this + 0x1d8);
          local_2c = pfVar11[2] - *(float *)(this + 0x1dc);
          if (((0.0 < local_2c) && (local_2c < 30.0)) &&
             (fVar16 = (float)tVector::Magnitude((tVector *)&local_34), fVar16 < (float)uVar19))
          break;
          iVar10 = iVar10 + 1;
          pfVar11 = pfVar11 + 6;
          if (*(int *)(&DAT_00303ab4 + iVar6) <= iVar10) goto LAB_00040058;
        }
        uVar19 = (ulonglong)(uint)fVar16;
        iVar9 = iVar10 * 0x18;
        iVar10 = iVar10 + 1;
        pfVar11 = pfVar11 + 6;
        piVar5 = (int *)(&DAT_00303ab8 + iVar6 + iVar9);
      } while (iVar10 < *(int *)(&DAT_00303ab4 + iVar6));
LAB_00040058:
      if (piVar5 != (int *)0x0) {
        iVar6 = piVar5[5];
        *(int *)(this + 0x174) = iVar6;
        if (*piVar5 == 0) {
          *(uint *)(iVar6 + 4) = *(uint *)(iVar6 + 4) | 0x1000;
        }
        iVar10 = piVar5[2];
        iVar9 = piVar5[3];
        iVar6 = *(int *)(this + 600);
        *(int *)(this + 0x178) = piVar5[1];
        *(int *)(this + 0x17c) = iVar10;
        *(int *)(this + 0x180) = iVar9;
        *(undefined4 *)(this + 0x188) = 0;
        *(undefined4 *)(this + 0x18c) = 0x3d088889;
        goto LAB_0003fc60;
      }
    }
    iVar6 = *(int *)(this + 600);
  }
  else if (iVar10 == 0) {
    *(undefined4 *)(this + 0x248) = 0;
    puVar1 = PTR__gRSpriteManager_001b61e4;
    *(float *)(this + 0x24c) = *(float *)(*(int *)(this + 0x250) + 0x4c) * 0.041666668;
    iVar6 = cRSpriteManager::New((int)puVar1,*(int *)(iVar6 + 0x370),0x76,-1);
    *(int *)(this + 0x228) = iVar6;
    *(uint *)(iVar6 + 4) = *(uint *)(iVar6 + 4) | 0x800;
    *(undefined4 *)(*(int *)(this + 0x228) + 0x68) = 0;
    *(undefined4 *)(*(int *)(this + 0x228) + 0x6c) = 0;
    *(undefined4 *)(*(int *)(this + 0x228) + 0x78) = 0;
    iVar6 = *(int *)(this + 0x228);
    tColour::tColour((tColour *)&local_44,1.0,1.0,1.0,1.0);
    *(undefined4 *)(iVar6 + 0x2c) = local_44;
    *(undefined4 *)(iVar6 + 0x30) = uStack_40;
    *(undefined4 *)(iVar6 + 0x34) = uStack_3c;
    *(undefined4 *)(iVar6 + 0x38) = uStack_38;
    *(undefined4 *)(*(int *)(this + 0x228) + 0x60) = 0x3efae148;
    *(undefined4 *)(*(int *)(this + 0x228) + 100) = 0x3efae148;
    iVar6 = *(int *)(this + 0x228);
    uVar4 = *(undefined4 *)(this + 0x1d8);
    uVar7 = *(undefined4 *)(this + 0x1dc);
    *(undefined4 *)(iVar6 + 0x48) = *(undefined4 *)pcVar12;
    *(undefined4 *)(iVar6 + 0x4c) = uVar4;
    *(undefined4 *)(iVar6 + 0x50) = uVar7;
    iVar6 = *(int *)(this + 0x228);
    uVar4 = gRMathRand2();
    fVar16 = (float)VectorSignedToFloat(uVar4,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(iVar6 + 0x7c) = (fVar16 - 16384.0) * 6.1035156e-05 * 3.1415927;
    *(float *)(*(int *)(this + 0x228) + 0x80) =
         *(float *)(*(int *)(this + 0x250) + 0x4c) * 0.58177644;
    *(int *)(this + 0x254) = param_3;
    iVar6 = *(int *)(this + 600);
  }
LAB_0003fc60:
  local_48 = (tVector *)(this + 0x22c);
  if ((*(char *)(iVar6 + 0x374) == '\0') || (0.5 <= *(float *)(iVar6 + 0x388))) {
    this[0x29c] = (cRSubGolb)0x0;
    *(undefined4 *)(this + 0x2c4) = 0xbf800000;
  }
  else {
    this[0x29c] = (cRSubGolb)0x1;
    *(undefined4 *)(this + 0x2a0) = *(undefined4 *)(iVar6 + 0x378);
    *(undefined4 *)(this + 0x2a4) = *(undefined4 *)(iVar6 + 0x37c);
    *(undefined4 *)(this + 0x2a8) = *(undefined4 *)(iVar6 + 0x380);
    *(undefined4 *)(this + 0x2ac) = *(undefined4 *)(iVar6 + 900);
    *(undefined4 *)(this + 0x2b0) = 0;
    uVar4 = *(undefined4 *)(iVar6 + 0x3a0);
    uVar7 = *(undefined4 *)(iVar6 + 0x3a4);
    uVar8 = *(undefined4 *)(iVar6 + 0x3a8);
    *(cRSubGolb **)(this + 0x2c0) = this;
    *(undefined4 *)(this + 0x2b4) = uVar4;
    *(undefined4 *)(this + 0x2b8) = uVar7;
    *(undefined4 *)(this + 700) = uVar8;
    *(undefined4 *)(this + 0x2c4) = *(undefined4 *)(iVar6 + 0x3a8);
  }
  uVar4 = tVector::Magnitude(local_48);
  *(undefined4 *)(this + 0x244) = uVar4;
  *(undefined4 *)(this + 0x214) = *(undefined4 *)pcVar12;
  *(undefined4 *)(this + 0x218) = *(undefined4 *)(this + 0x1d8);
  *(undefined4 *)(this + 0x21c) = *(undefined4 *)(this + 0x1dc);
  (*(code *)**(undefined4 **)this)(this);
  return;
}
