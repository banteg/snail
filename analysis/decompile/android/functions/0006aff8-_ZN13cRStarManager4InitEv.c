/*
 * mangled: _ZN13cRStarManager4InitEv
 * demangled: cRStarManager::Init()
 * address: 0006aff8
 * size: 868
 */

/* cRStarManager::Init() */

void __thiscall cRStarManager::Init(cRStarManager *this)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  uint in_fpscr;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float extraout_s1;
  float extraout_s2;
  float extraout_s3;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  undefined4 local_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;

  iVar4 = *(int *)(this + 0x34);
  if (0 < iVar4) {
    iVar5 = 0;
    iVar6 = 0;
    do {
      iVar7 = *(int *)(this + 0x30);
      iVar6 = iVar6 + 1;
      uVar1 = cRSpriteManager::New((int)&gRSpriteManager,2,0x12,-1);
      iVar4 = *(int *)(this + 0x34);
      iVar7 = iVar7 + iVar5;
      iVar5 = iVar5 + 0x2c;
      *(undefined4 *)(iVar7 + 0x1c) = uVar1;
    } while (iVar6 < iVar4);
  }
  *(undefined4 *)(this + 0x38) = 0x3f800000;
  if (0 < iVar4) {
    iVar4 = 0;
    iVar6 = *(int *)(this + 0x30);
    iVar5 = 0;
    do {
      iVar7 = 1;
      *(undefined4 *)(iVar6 + iVar4) = 1;
      if (iVar5 == 0) {
        iVar7 = iVar6 + iVar4;
      }
      if (iVar5 == 0) {
        *(undefined4 *)(iVar7 + 0x28) = 0x3ecccccd;
      }
      else {
        iVar7 = iVar6 + iVar4;
        uVar1 = gRMathRand2();
        iVar6 = *(int *)(this + 0x30);
        fVar17 = (float)VectorSignedToFloat(uVar1,(byte)(in_fpscr >> 0x16) & 3);
        *(float *)(iVar7 + 0x28) = (fVar17 - 16384.0) * 6.1035156e-05 * 0.1 + 0.4;
      }
      iVar6 = iVar6 + iVar4;
      iVar5 = iVar5 + 1;
      fVar12 = *(float *)(Game + 0x458);
      fVar10 = *(float *)(Game + 0x444);
      fVar17 = *(float *)(Game + 0x448);
      fVar15 = *(float *)(Game + 0x454);
      *(float *)(iVar6 + 4) = *(float *)(Game + 0x450) + *(float *)(Game + 0x440) * 50.0;
      *(float *)(iVar6 + 0xc) = fVar12 + fVar17 * 50.0;
      *(float *)(iVar6 + 8) = fVar15 + fVar10 * 50.0;
      uVar1 = gRMathRand2();
      iVar7 = *(int *)(this + 0x30) + iVar4;
      VectorSignedToFloat(uVar1,(byte)(in_fpscr >> 0x16) & 3);
      uVar1 = Sin(extraout_s0);
      uVar2 = Cos(extraout_s0_00);
      iVar6 = *(int *)(this + 0x30);
      *(undefined4 *)(iVar7 + 0x10) = uVar1;
      *(undefined4 *)(iVar7 + 0x18) = 0;
      *(undefined4 *)(iVar7 + 0x14) = uVar2;
      tVector::Normalize((tVector *)(iVar6 + iVar4 + 0x10));
      iVar6 = *(int *)(this + 0x30);
      uVar1 = gRMathRand2();
      iVar6 = iVar6 + iVar4;
      fVar10 = *(float *)(iVar6 + 0x14);
      fVar12 = *(float *)(iVar6 + 0x10);
      iVar7 = *(int *)(this + 0x30) + iVar4;
      fVar17 = (float)VectorSignedToFloat(uVar1,(byte)(in_fpscr >> 0x16) & 3);
      fVar17 = fVar17 * 3.0517578e-05 * 0.6 + 0.3;
      *(float *)(iVar6 + 0x18) = *(float *)(iVar6 + 0x18) * fVar17;
      *(undefined4 *)(iVar7 + 0x18) = 0;
      *(float *)(iVar6 + 0x10) = fVar12 * fVar17;
      *(float *)(iVar6 + 0x14) = fVar10 * fVar17;
      uVar1 = tVector::Magnitude((tVector *)(iVar7 + 0x10));
      iVar6 = *(int *)(this + 0x30);
      *(undefined4 *)(iVar7 + 0x20) = uVar1;
      uVar1 = gRMathRand2();
      iVar8 = *(int *)(this + 0x30) + iVar4;
      fVar10 = *(float *)(iVar8 + 0x10);
      fVar17 = *(float *)(iVar8 + 0x14);
      fVar13 = *(float *)(iVar8 + 0x18);
      fVar16 = *(float *)(iVar8 + 0x20);
      fVar12 = *(float *)(iVar8 + 4);
      fVar15 = *(float *)(iVar8 + 8);
      fVar11 = *(float *)(iVar8 + 0xc);
      iVar7 = *(int *)(iVar8 + 0x1c);
      *(uint *)(iVar7 + 4) = *(uint *)(iVar7 + 4) | 0x402;
      fVar14 = (float)VectorSignedToFloat(uVar1,(byte)(in_fpscr >> 0x16) & 3);
      *(float *)(iVar6 + iVar4 + 0x24) = fVar14 * 3.0517578e-05 * 35.0;
      fVar14 = *(float *)(iVar8 + 0x24);
      *(float *)(iVar8 + 4) = (fVar14 * fVar10) / fVar16 + fVar12;
      *(float *)(iVar8 + 8) = (fVar14 * fVar17) / fVar16 + fVar15;
      *(float *)(iVar8 + 0xc) = fVar11 + (fVar14 * fVar13) / fVar16;
      *(undefined4 *)(iVar7 + 0x68) = 0;
      *(undefined4 *)(iVar7 + 0x6c) = 0;
      *(undefined4 *)(iVar7 + 0x78) = 0;
      tColour::tColour((tColour *)&local_60,extraout_s0_01,extraout_s1,extraout_s2,extraout_s3);
      iVar6 = *(int *)(this + 0x30);
      iVar9 = iVar6 + iVar4;
      iVar4 = iVar4 + 0x2c;
      *(undefined4 *)(iVar7 + 0x2c) = local_60;
      *(undefined4 *)(iVar7 + 0x30) = uStack_5c;
      *(undefined4 *)(iVar7 + 0x34) = uStack_58;
      *(undefined4 *)(iVar7 + 0x38) = uStack_54;
      iVar8 = *(int *)(iVar9 + 0x1c);
      *(undefined4 *)(iVar8 + 100) = 0x3f4ccccd;
      *(undefined4 *)(iVar8 + 0x60) = 0x3f4ccccd;
      fVar17 = *(float *)(iVar9 + 0x20);
      *(undefined4 *)(iVar8 + 0x28) = 1;
      iVar7 = *(int *)(this + 0x34);
      *(float *)(iVar8 + 0x84) = fVar17 * 4.0 + 4.0;
      uVar1 = *(undefined4 *)(iVar9 + 0x14);
      uVar2 = *(undefined4 *)(iVar9 + 0x18);
      *(undefined4 *)(iVar8 + 0x54) = *(undefined4 *)(iVar9 + 0x10);
      *(undefined4 *)(iVar8 + 0x58) = uVar1;
      *(undefined4 *)(iVar8 + 0x5c) = uVar2;
      uVar1 = *(undefined4 *)(iVar9 + 4);
      uVar2 = *(undefined4 *)(iVar9 + 8);
      uVar3 = *(undefined4 *)(iVar9 + 0xc);
      *(undefined4 *)(iVar8 + 0x88) = 0;
      *(undefined4 *)(iVar8 + 0x48) = uVar1;
      *(undefined4 *)(iVar8 + 0x4c) = uVar2;
      *(undefined4 *)(iVar8 + 0x50) = uVar3;
    } while (iVar5 < iVar7);
  }
  (*(code *)**(undefined4 **)this)(this);
  return;
}
