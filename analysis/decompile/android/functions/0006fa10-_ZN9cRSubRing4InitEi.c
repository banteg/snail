/*
 * mangled: _ZN9cRSubRing4InitEi
 * demangled: cRSubRing::Init(int)
 * address: 0006fa10
 * size: 564
 */

/* cRSubRing::Init(int) */

void cRSubRing::Init(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  bool bVar9;
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
  float fVar10;
  undefined4 local_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;

  iVar7 = 0;
  *(undefined4 *)(param_1 + 0x19c) = 0;
  *(undefined4 *)(param_1 + 0x74) = 1;
  iVar6 = param_1;
  do {
    fVar10 = (float)VectorSignedToFloat(iVar7,(byte)(in_fpscr >> 0x16) & 3);
    iVar3 = *(int *)(param_1 + 0x184);
    uVar5 = *(uint *)(param_1 + 0x7c);
    *(int *)(iVar6 + 0x88) = param_1;
    bVar9 = 7 < uVar5;
    if (uVar5 != 8) {
      bVar9 = uVar5 != 4;
    }
    *(float *)(iVar6 + 0x98) = (fVar10 + fVar10) * 3.1415927 * 0.125;
    *(float *)(iVar6 + 0x9c) = *(float *)(iVar3 + 0x54) * 0.104719765;
    uVar1 = *(undefined4 *)(param_1 + 0x5c);
    uVar2 = *(undefined4 *)(param_1 + 0x60);
    uVar4 = *(undefined4 *)(param_1 + 100);
    *(undefined4 *)(iVar6 + 0xa0) = 0x3f99999a;
    *(undefined4 *)(iVar6 + 0x8c) = uVar1;
    *(undefined4 *)(iVar6 + 0x90) = uVar2;
    *(undefined4 *)(iVar6 + 0x94) = uVar4;
    if (bVar9 && (uVar5 != 8 && uVar5 != 5)) {
      if (uVar5 == 2 || uVar5 == 6) {
        iVar3 = cRSpriteManager::New
                          ((int)&gRSpriteManager,*(int *)(*(int *)(param_1 + 0x78) + 0x370),0x77,-1)
        ;
        *(undefined4 *)(param_1 + 0x1a0) = 0x78;
        *(int *)(iVar6 + 0x84) = iVar3;
        *(undefined4 *)(iVar3 + 0x28) = 5;
        in_s0 = extraout_s0_01;
        in_s1 = extraout_s1_01;
        in_s2 = extraout_s2_01;
        in_s3 = extraout_s3_01;
      }
      else if (uVar5 == 3 || uVar5 == 7) {
        iVar3 = cRSpriteManager::New
                          ((int)&gRSpriteManager,*(int *)(*(int *)(param_1 + 0x78) + 0x370),0x79,-1)
        ;
        *(undefined4 *)(param_1 + 0x1a0) = 0x7a;
        *(int *)(iVar6 + 0x84) = iVar3;
        *(undefined4 *)(iVar3 + 0x28) = 5;
        in_s0 = extraout_s0_02;
        in_s1 = extraout_s1_02;
        in_s2 = extraout_s2_02;
        in_s3 = extraout_s3_02;
      }
      else {
        iVar3 = *(int *)(iVar6 + 0x84);
      }
    }
    else {
      iVar3 = cRSpriteManager::New
                        ((int)&gRSpriteManager,*(int *)(*(int *)(param_1 + 0x78) + 0x370),0x7b,-1);
      *(undefined4 *)(param_1 + 0x1a0) = 0x7c;
      *(int *)(iVar6 + 0x84) = iVar3;
      *(undefined4 *)(iVar3 + 0x28) = 5;
      in_s0 = extraout_s0_00;
      in_s1 = extraout_s1_00;
      in_s2 = extraout_s2_00;
      in_s3 = extraout_s3_00;
    }
    tColour::tColour((tColour *)&local_50,in_s0,in_s1,in_s2,in_s3);
    iVar8 = *(int *)(iVar6 + 0x84);
    *(undefined4 *)(iVar8 + 0x68) = 0;
    *(undefined4 *)(iVar8 + 0x6c) = 0;
    *(undefined4 *)(iVar8 + 0x78) = 0;
    *(undefined4 *)(iVar8 + 0x60) = 0x3f666667;
    uVar5 = *(uint *)(iVar8 + 4);
    *(undefined4 *)(iVar8 + 100) = 0x3f666667;
    *(undefined4 *)(iVar3 + 0x2c) = local_50;
    *(undefined4 *)(iVar3 + 0x30) = uStack_4c;
    *(undefined4 *)(iVar3 + 0x34) = uStack_48;
    *(undefined4 *)(iVar3 + 0x38) = uStack_44;
    uVar1 = *(undefined4 *)(param_1 + 0x5c);
    uVar2 = *(undefined4 *)(param_1 + 0x60);
    uVar4 = *(undefined4 *)(param_1 + 100);
    *(uint *)(iVar8 + 4) = uVar5 | 0x800;
    iVar3 = *(int *)(param_1 + 0x7c);
    *(undefined4 *)(iVar8 + 0x48) = uVar1;
    *(undefined4 *)(iVar8 + 0x4c) = uVar2;
    *(undefined4 *)(iVar8 + 0x50) = uVar4;
    *(undefined4 *)(iVar8 + 0x7c) = *(undefined4 *)(iVar6 + 0x98);
    if (iVar3 == 3 || iVar3 == 6) {
      *(undefined4 *)(iVar8 + 0x80) = 0;
    }
    else {
      *(float *)(iVar8 + 0x80) = -*(float *)(iVar6 + 0x9c);
    }
    iVar7 = iVar7 + 1;
    iVar6 = iVar6 + 0x20;
    cRSubRingStar::AI();
    in_s0 = extraout_s0;
    in_s1 = extraout_s1;
    in_s2 = extraout_s2;
    in_s3 = extraout_s3;
  } while (iVar7 != 8);
  return;
}
