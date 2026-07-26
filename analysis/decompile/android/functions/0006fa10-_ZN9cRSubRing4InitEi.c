/*
 * mangled: _ZN9cRSubRing4InitEi
 * demangled: cRSubRing::Init(int)
 * address: 0006fa10
 * size: 564
 */

/* cRSubRing::Init(int) */

void cRSubRing::Init(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int iVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  int iVar10;
  undefined4 uVar11;
  uint uVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  bool bVar17;
  uint in_fpscr;
  float in_s0;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float extraout_s0_02;
  float in_s1;
  float extraout_s1;
  float extraout_s1_00;
  float extraout_s1_01;
  float extraout_s1_02;
  float in_s2;
  float extraout_s2;
  float extraout_s2_00;
  float extraout_s2_01;
  float extraout_s2_02;
  float in_s3;
  float extraout_s3;
  float extraout_s3_00;
  float extraout_s3_01;
  float extraout_s3_02;
  float fVar18;
  undefined4 local_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;

  iVar7 = DAT_0006fc5c;
  fVar1 = DAT_0006fc44;
  iVar14 = 0;
  iVar15 = DAT_0006fc60 + 0x6fa38;
  *(undefined4 *)(param_1 + 0x19c) = 0;
  *(undefined4 *)(param_1 + 0x74) = 1;
  uVar6 = DAT_0006fc58;
  uVar5 = DAT_0006fc54;
  uVar4 = DAT_0006fc50;
  fVar3 = DAT_0006fc4c;
  fVar2 = DAT_0006fc48;
  iVar13 = param_1;
  do {
    fVar18 = (float)VectorSignedToFloat(iVar14,(byte)(in_fpscr >> 0x16) & 3);
    iVar10 = *(int *)(param_1 + 0x184);
    uVar12 = *(uint *)(param_1 + 0x7c);
    *(int *)(iVar13 + 0x88) = param_1;
    bVar17 = 7 < uVar12;
    if (uVar12 != 8) {
      bVar17 = uVar12 != 4;
    }
    *(float *)(iVar13 + 0x98) = (fVar18 + fVar18) * fVar1 * fVar2;
    *(float *)(iVar13 + 0x9c) = *(float *)(iVar10 + 0x54) * fVar3;
    uVar8 = *(undefined4 *)(param_1 + 0x5c);
    uVar9 = *(undefined4 *)(param_1 + 0x60);
    uVar11 = *(undefined4 *)(param_1 + 100);
    *(undefined4 *)(iVar13 + 0xa0) = uVar4;
    *(undefined4 *)(iVar13 + 0x8c) = uVar8;
    *(undefined4 *)(iVar13 + 0x90) = uVar9;
    *(undefined4 *)(iVar13 + 0x94) = uVar11;
    if (bVar17 && (uVar12 != 8 && uVar12 != 5)) {
      if (uVar12 == 2 || uVar12 == 6) {
        iVar10 = cRSpriteManager::New
                           (*(int *)(iVar15 + iVar7),*(int *)(*(int *)(param_1 + 0x78) + 0x370),0x77
                            ,-1);
        *(undefined4 *)(param_1 + 0x1a0) = 0x78;
        *(int *)(iVar13 + 0x84) = iVar10;
        *(undefined4 *)(iVar10 + 0x28) = 5;
        in_s0 = extraout_s0_01;
        in_s1 = extraout_s1_01;
        in_s2 = extraout_s2_01;
        in_s3 = extraout_s3_01;
      }
      else if (uVar12 == 3 || uVar12 == 7) {
        iVar10 = cRSpriteManager::New
                           (*(int *)(iVar15 + iVar7),*(int *)(*(int *)(param_1 + 0x78) + 0x370),0x79
                            ,-1);
        *(undefined4 *)(param_1 + 0x1a0) = 0x7a;
        *(int *)(iVar13 + 0x84) = iVar10;
        *(undefined4 *)(iVar10 + 0x28) = 5;
        in_s0 = extraout_s0_02;
        in_s1 = extraout_s1_02;
        in_s2 = extraout_s2_02;
        in_s3 = extraout_s3_02;
      }
      else {
        iVar10 = *(int *)(iVar13 + 0x84);
      }
    }
    else {
      iVar10 = cRSpriteManager::New
                         (*(int *)(iVar15 + iVar7),*(int *)(*(int *)(param_1 + 0x78) + 0x370),0x7b,
                          -1);
      *(undefined4 *)(param_1 + 0x1a0) = 0x7c;
      *(int *)(iVar13 + 0x84) = iVar10;
      *(undefined4 *)(iVar10 + 0x28) = 5;
      in_s0 = extraout_s0_00;
      in_s1 = extraout_s1_00;
      in_s2 = extraout_s2_00;
      in_s3 = extraout_s3_00;
    }
    tColour::tColour((tColour *)&local_50,in_s0,in_s1,in_s2,in_s3);
    iVar16 = *(int *)(iVar13 + 0x84);
    *(undefined4 *)(iVar16 + 0x68) = uVar5;
    *(undefined4 *)(iVar16 + 0x6c) = uVar5;
    *(undefined4 *)(iVar16 + 0x78) = uVar5;
    *(undefined4 *)(iVar16 + 0x60) = uVar6;
    uVar12 = *(uint *)(iVar16 + 4);
    *(undefined4 *)(iVar16 + 100) = uVar6;
    *(undefined4 *)(iVar10 + 0x2c) = local_50;
    *(undefined4 *)(iVar10 + 0x30) = uStack_4c;
    *(undefined4 *)(iVar10 + 0x34) = uStack_48;
    *(undefined4 *)(iVar10 + 0x38) = uStack_44;
    uVar8 = *(undefined4 *)(param_1 + 0x5c);
    uVar9 = *(undefined4 *)(param_1 + 0x60);
    uVar11 = *(undefined4 *)(param_1 + 100);
    *(uint *)(iVar16 + 4) = uVar12 | 0x800;
    iVar10 = *(int *)(param_1 + 0x7c);
    *(undefined4 *)(iVar16 + 0x48) = uVar8;
    *(undefined4 *)(iVar16 + 0x4c) = uVar9;
    *(undefined4 *)(iVar16 + 0x50) = uVar11;
    *(undefined4 *)(iVar16 + 0x7c) = *(undefined4 *)(iVar13 + 0x98);
    if (iVar10 == 3 || iVar10 == 6) {
      *(undefined4 *)(iVar16 + 0x80) = uVar5;
    }
    else {
      *(float *)(iVar16 + 0x80) = -*(float *)(iVar13 + 0x9c);
    }
    iVar14 = iVar14 + 1;
    iVar13 = iVar13 + 0x20;
    cRSubRingStar::AI();
    in_s0 = extraout_s0;
    in_s1 = extraout_s1;
    in_s2 = extraout_s2;
    in_s3 = extraout_s3;
  } while (iVar14 != 8);
  return;
}
