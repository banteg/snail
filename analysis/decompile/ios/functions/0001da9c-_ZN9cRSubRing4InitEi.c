/*
 * mangled: _ZN9cRSubRing4InitEi
 * demangled: cRSubRing::Init(int)
 * address: 0001da9c
 * size: 576
 */

/* cRSubRing::Init(int) */

void cRSubRing::Init(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  bool bVar9;
  uint in_fpscr;
  float fVar10;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;

  *(undefined4 *)(param_1 + 0x74) = 1;
  iVar8 = 0;
  *(undefined4 *)(param_1 + 0x19c) = 0;
  iVar6 = param_1;
  do {
    fVar10 = (float)VectorSignedToFloat(iVar8,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(iVar6 + 0x98) = (fVar10 + fVar10) * 3.1415927 * 0.125;
    fVar10 = *(float *)(*(int *)(param_1 + 0x184) + 0x4c);
    *(int *)(iVar6 + 0x88) = param_1;
    fVar10 = fVar10 * 0.104719765;
    *(float *)(iVar6 + 0x9c) = fVar10;
    _memcpy((void *)(iVar6 + 0x8c),(undefined4 *)(param_1 + 0x5c),0xc);
    *(undefined4 *)(iVar6 + 0xa0) = 0x3f99999a;
    uVar5 = *(uint *)(param_1 + 0x7c);
    bVar9 = 7 < uVar5;
    if (uVar5 != 8) {
      bVar9 = uVar5 != 4;
    }
    if (bVar9 && (uVar5 != 8 && uVar5 != 5)) {
      if (uVar5 == 6 || uVar5 == 2) {
        uVar1 = cRSpriteManager::New
                          ((int)PTR__gRSpriteManager_001b61e4,
                           *(int *)(*(int *)(param_1 + 0x78) + 0x370),0x77,-1);
        *(undefined4 *)(iVar6 + 0x84) = uVar1;
        *(undefined4 *)(param_1 + 0x1a0) = 0x78;
        *(undefined4 *)(*(int *)(iVar6 + 0x84) + 0x28) = 5;
      }
      else if (uVar5 == 7 || uVar5 == 3) {
        uVar1 = cRSpriteManager::New
                          ((int)PTR__gRSpriteManager_001b61e4,
                           *(int *)(*(int *)(param_1 + 0x78) + 0x370),0x79,-1);
        *(undefined4 *)(iVar6 + 0x84) = uVar1;
        *(undefined4 *)(param_1 + 0x1a0) = 0x7a;
        *(undefined4 *)(*(int *)(iVar6 + 0x84) + 0x28) = 5;
      }
    }
    else {
      uVar1 = cRSpriteManager::New
                        ((int)PTR__gRSpriteManager_001b61e4,
                         *(int *)(*(int *)(param_1 + 0x78) + 0x370),0x7b,-1);
      *(undefined4 *)(iVar6 + 0x84) = uVar1;
      *(undefined4 *)(param_1 + 0x1a0) = 0x7c;
      *(undefined4 *)(*(int *)(iVar6 + 0x84) + 0x28) = 5;
    }
    iVar7 = *(int *)(iVar6 + 0x84);
    tColour::tColour((tColour *)&local_30,1.0,1.0,1.0,0.8);
    *(undefined4 *)(iVar7 + 0x2c) = local_30;
    *(undefined4 *)(iVar7 + 0x30) = uStack_2c;
    *(undefined4 *)(iVar7 + 0x34) = uStack_28;
    *(undefined4 *)(iVar7 + 0x38) = uStack_24;
    *(uint *)(*(int *)(iVar6 + 0x84) + 4) = *(uint *)(*(int *)(iVar6 + 0x84) + 4) | 0x800;
    *(undefined4 *)(*(int *)(iVar6 + 0x84) + 0x68) = 0;
    *(undefined4 *)(*(int *)(iVar6 + 0x84) + 0x6c) = 0;
    *(undefined4 *)(*(int *)(iVar6 + 0x84) + 0x78) = 0;
    *(undefined4 *)(*(int *)(iVar6 + 0x84) + 0x60) = 0x3f666667;
    *(undefined4 *)(*(int *)(iVar6 + 0x84) + 100) = 0x3f666667;
    uVar1 = *(undefined4 *)(param_1 + 0x60);
    uVar2 = *(undefined4 *)(param_1 + 100);
    iVar7 = *(int *)(iVar6 + 0x84);
    *(undefined4 *)(iVar7 + 0x48) = *(undefined4 *)(param_1 + 0x5c);
    *(undefined4 *)(iVar7 + 0x4c) = uVar1;
    *(undefined4 *)(iVar7 + 0x50) = uVar2;
    iVar7 = iVar8 * 0x20;
    *(undefined4 *)(*(int *)(iVar6 + 0x84) + 0x7c) = *(undefined4 *)(iVar6 + 0x98);
    iVar3 = *(int *)(param_1 + 0x7c);
    iVar8 = iVar8 + 1;
    if (iVar3 != 6 && iVar3 != 3) {
      iVar4 = *(int *)(iVar6 + 0x84);
      fVar10 = -*(float *)(iVar6 + 0x9c);
    }
    else {
      iVar4 = *(int *)(iVar6 + 0x84);
      *(undefined4 *)(iVar4 + 0x80) = 0;
    }
    iVar6 = iVar6 + 0x20;
    if (iVar3 != 6 && iVar3 != 3) {
      *(float *)(iVar4 + 0x80) = fVar10;
    }
    cRSubRingStar::AI((cRSubRingStar *)(param_1 + iVar7 + 0x84));
  } while (iVar8 != 8);
  return;
}
