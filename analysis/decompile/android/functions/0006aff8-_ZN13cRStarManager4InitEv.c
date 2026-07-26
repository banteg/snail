/*
 * mangled: _ZN13cRStarManager4InitEv
 * demangled: cRStarManager::Init()
 * address: 0006aff8
 * size: 868
 */

/* cRStarManager::Init() */

void __thiscall cRStarManager::Init(cRStarManager *this)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  int iVar11;
  undefined4 uVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  uint in_fpscr;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float extraout_s1;
  float extraout_s2;
  float extraout_s3;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  float fVar25;
  float fVar26;
  float fVar27;
  undefined4 local_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;

  iVar13 = *(int *)(this + 0x34);
  iVar11 = DAT_0006b390 + 0x6b018;
  if (0 < iVar13) {
    iVar14 = 0;
    iVar15 = 0;
    iVar17 = *(int *)(iVar11 + DAT_0006b394);
    do {
      iVar16 = *(int *)(this + 0x30);
      iVar15 = iVar15 + 1;
      uVar8 = cRSpriteManager::New(iVar17,2,0x12,-1);
      iVar13 = *(int *)(this + 0x34);
      iVar16 = iVar16 + iVar14;
      iVar14 = iVar14 + 0x2c;
      *(undefined4 *)(iVar16 + 0x1c) = uVar8;
    } while (iVar15 < iVar13);
  }
  *(undefined4 *)(this + 0x38) = DAT_0006b35c;
  iVar14 = DAT_0006b398;
  fVar7 = DAT_0006b380;
  uVar8 = DAT_0006b37c;
  fVar6 = DAT_0006b374;
  fVar5 = DAT_0006b370;
  fVar4 = DAT_0006b36c;
  fVar3 = DAT_0006b368;
  fVar2 = DAT_0006b364;
  fVar1 = DAT_0006b360;
  if (0 < iVar13) {
    iVar13 = 0;
    iVar17 = *(int *)(this + 0x30);
    iVar15 = 0;
    do {
      iVar16 = 1;
      *(undefined4 *)(iVar17 + iVar13) = 1;
      if (iVar15 == 0) {
        iVar16 = iVar17 + iVar13;
      }
      if (iVar15 == 0) {
        *(float *)(iVar16 + 0x28) = fVar4;
      }
      else {
        iVar16 = iVar17 + iVar13;
        uVar10 = gRMathRand2();
        iVar17 = *(int *)(this + 0x30);
        fVar27 = (float)VectorSignedToFloat(uVar10,(byte)(in_fpscr >> 0x16) & 3);
        *(float *)(iVar16 + 0x28) = fVar4 + (fVar27 - fVar1) * fVar2 * fVar3;
      }
      iVar17 = iVar17 + iVar13;
      iVar15 = iVar15 + 1;
      iVar16 = **(int **)(iVar11 + iVar14);
      fVar22 = *(float *)(iVar16 + 0x458);
      fVar20 = *(float *)(iVar16 + 0x444);
      fVar27 = *(float *)(iVar16 + 0x448);
      fVar25 = *(float *)(iVar16 + 0x454);
      *(float *)(iVar17 + 4) = *(float *)(iVar16 + 0x450) + fVar5 * *(float *)(iVar16 + 0x440);
      *(float *)(iVar17 + 0xc) = fVar22 + fVar5 * fVar27;
      *(float *)(iVar17 + 8) = fVar25 + fVar5 * fVar20;
      uVar10 = gRMathRand2();
      iVar16 = *(int *)(this + 0x30) + iVar13;
      VectorSignedToFloat(uVar10,(byte)(in_fpscr >> 0x16) & 3);
      uVar10 = Sin(extraout_s0);
      uVar9 = Cos(extraout_s0_00);
      iVar17 = *(int *)(this + 0x30);
      *(undefined4 *)(iVar16 + 0x10) = uVar10;
      *(undefined4 *)(iVar16 + 0x18) = uVar8;
      *(undefined4 *)(iVar16 + 0x14) = uVar9;
      tVector::Normalize((tVector *)(iVar17 + iVar13 + 0x10));
      iVar17 = *(int *)(this + 0x30);
      uVar10 = gRMathRand2();
      iVar17 = iVar17 + iVar13;
      fVar20 = *(float *)(iVar17 + 0x14);
      fVar22 = *(float *)(iVar17 + 0x10);
      iVar16 = *(int *)(this + 0x30) + iVar13;
      fVar27 = (float)VectorSignedToFloat(uVar10,(byte)(in_fpscr >> 0x16) & 3);
      fVar27 = DAT_0006b384 + fVar27 * fVar6 * fVar7;
      *(float *)(iVar17 + 0x18) = *(float *)(iVar17 + 0x18) * fVar27;
      *(undefined4 *)(iVar16 + 0x18) = uVar8;
      *(float *)(iVar17 + 0x10) = fVar22 * fVar27;
      *(float *)(iVar17 + 0x14) = fVar20 * fVar27;
      uVar10 = tVector::Magnitude((tVector *)(iVar16 + 0x10));
      iVar17 = *(int *)(this + 0x30);
      *(undefined4 *)(iVar16 + 0x20) = uVar10;
      uVar10 = gRMathRand2();
      iVar18 = *(int *)(this + 0x30) + iVar13;
      fVar20 = *(float *)(iVar18 + 0x10);
      fVar27 = *(float *)(iVar18 + 0x14);
      fVar23 = *(float *)(iVar18 + 0x18);
      fVar26 = *(float *)(iVar18 + 0x20);
      fVar22 = *(float *)(iVar18 + 4);
      fVar25 = *(float *)(iVar18 + 8);
      fVar21 = *(float *)(iVar18 + 0xc);
      iVar16 = *(int *)(iVar18 + 0x1c);
      *(uint *)(iVar16 + 4) = *(uint *)(iVar16 + 4) | 0x402;
      fVar24 = (float)VectorSignedToFloat(uVar10,(byte)(in_fpscr >> 0x16) & 3);
      *(float *)(iVar17 + iVar13 + 0x24) = fVar24 * fVar6 * DAT_0006b388;
      fVar24 = *(float *)(iVar18 + 0x24);
      *(float *)(iVar18 + 4) = (fVar24 * fVar20) / fVar26 + fVar22;
      *(float *)(iVar18 + 8) = (fVar24 * fVar27) / fVar26 + fVar25;
      *(float *)(iVar18 + 0xc) = fVar21 + (fVar24 * fVar23) / fVar26;
      *(undefined4 *)(iVar16 + 0x68) = uVar8;
      *(undefined4 *)(iVar16 + 0x6c) = uVar8;
      *(undefined4 *)(iVar16 + 0x78) = uVar8;
      tColour::tColour((tColour *)&local_60,extraout_s0_01,extraout_s1,extraout_s2,extraout_s3);
      fVar27 = DAT_0006b38c;
      iVar17 = *(int *)(this + 0x30);
      iVar19 = iVar17 + iVar13;
      iVar13 = iVar13 + 0x2c;
      *(undefined4 *)(iVar16 + 0x2c) = local_60;
      *(undefined4 *)(iVar16 + 0x30) = uStack_5c;
      *(undefined4 *)(iVar16 + 0x34) = uStack_58;
      *(undefined4 *)(iVar16 + 0x38) = uStack_54;
      iVar18 = *(int *)(iVar19 + 0x1c);
      *(undefined4 *)(iVar18 + 100) = 0x3f4ccccd;
      *(undefined4 *)(iVar18 + 0x60) = 0x3f4ccccd;
      fVar20 = *(float *)(iVar19 + 0x20);
      *(undefined4 *)(iVar18 + 0x28) = 1;
      iVar16 = *(int *)(this + 0x34);
      *(float *)(iVar18 + 0x84) = fVar27 + fVar27 * fVar20;
      uVar10 = *(undefined4 *)(iVar19 + 0x14);
      uVar9 = *(undefined4 *)(iVar19 + 0x18);
      *(undefined4 *)(iVar18 + 0x54) = *(undefined4 *)(iVar19 + 0x10);
      *(undefined4 *)(iVar18 + 0x58) = uVar10;
      *(undefined4 *)(iVar18 + 0x5c) = uVar9;
      uVar10 = *(undefined4 *)(iVar19 + 4);
      uVar9 = *(undefined4 *)(iVar19 + 8);
      uVar12 = *(undefined4 *)(iVar19 + 0xc);
      *(undefined4 *)(iVar18 + 0x88) = uVar8;
      *(undefined4 *)(iVar18 + 0x48) = uVar10;
      *(undefined4 *)(iVar18 + 0x4c) = uVar9;
      *(undefined4 *)(iVar18 + 0x50) = uVar12;
    } while (iVar15 < iVar16);
  }
  (*(code *)**(undefined4 **)this)(this);
  return;
}
