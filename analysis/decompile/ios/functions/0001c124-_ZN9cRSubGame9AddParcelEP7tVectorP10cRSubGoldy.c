/*
 * mangled: _ZN9cRSubGame9AddParcelEP7tVectorP10cRSubGoldy
 * demangled: cRSubGame::AddParcel(tVector*, cRSubGoldy*)
 * address: 0001c124
 * size: 448
 */

/* cRSubGame::AddParcel(tVector*, cRSubGoldy*) */

tVector * cRSubGame::AddParcel(tVector *param_1,cRSubGoldy *param_2)

{
  undefined4 uVar1;
  int iVar2;
  tVector *ptVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 uVar6;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;

  iVar5 = 0;
  ptVar3 = param_1 + 0x2f04a8;
  do {
    if (*(int *)ptVar3 == 0) {
      iVar5 = iVar5 * 0x80;
      if (param_1 + (int)(&DAT_002f047c + iVar5) == (tVector *)0x0) {
        return (tVector *)0x0;
      }
      *(undefined4 *)(param_1 + iVar5 + 0x2f04a8) = 1;
      uVar1 = *(undefined4 *)param_2;
      uVar4 = *(undefined4 *)(param_2 + 4);
      uVar6 = *(undefined4 *)(param_2 + 8);
      *(tVector **)(param_1 + iVar5 + 0x2f04d4) = param_1 + 0xf448;
      *(undefined4 *)(param_1 + iVar5 + 0x2f048c) = uVar1;
      *(undefined4 *)(param_1 + iVar5 + 0x2f0490) = uVar4;
      *(undefined4 *)(param_1 + iVar5 + 0x2f0494) = uVar6;
      iVar2 = cRSpriteManager::New
                        ((int)PTR__gRSpriteManager_001b61e4,*(int *)(param_1 + 0xf7b8),0x6d,-1);
      *(int *)(param_1 + iVar5 + 0x2f04c4) = iVar2;
      *(uint *)(iVar2 + 4) = *(uint *)(iVar2 + 4) | 0x800;
      *(undefined4 *)(*(int *)(param_1 + iVar5 + 0x2f04c4) + 0x28) = 7;
      *(undefined4 *)(*(int *)(param_1 + iVar5 + 0x2f04c4) + 0x68) = 0;
      *(undefined4 *)(*(int *)(param_1 + iVar5 + 0x2f04c4) + 0x6c) = 0;
      *(undefined4 *)(*(int *)(param_1 + iVar5 + 0x2f04c4) + 0x78) = 0;
      iVar2 = *(int *)(param_1 + iVar5 + 0x2f04c4);
      tColour::tColour((tColour *)&local_30,1.0,1.0,1.0,1.0);
      *(undefined4 *)(iVar2 + 0x2c) = local_30;
      *(undefined4 *)(iVar2 + 0x30) = uStack_2c;
      *(undefined4 *)(iVar2 + 0x34) = uStack_28;
      *(undefined4 *)(iVar2 + 0x38) = uStack_24;
      *(undefined4 *)(*(int *)(param_1 + iVar5 + 0x2f04c4) + 0x60) = 0x3f800000;
      *(undefined4 *)(*(int *)(param_1 + iVar5 + 0x2f04c4) + 100) = 0x3f800000;
      uVar1 = *(undefined4 *)(param_1 + iVar5 + 0x2f0490);
      uVar4 = *(undefined4 *)(param_1 + iVar5 + 0x2f0494);
      iVar2 = *(int *)(param_1 + iVar5 + 0x2f04c4);
      *(undefined4 *)(iVar2 + 0x48) = *(undefined4 *)(param_1 + iVar5 + 0x2f048c);
      *(undefined4 *)(iVar2 + 0x4c) = uVar1;
      *(undefined4 *)(iVar2 + 0x50) = uVar4;
      if (((int)*(float *)(param_2 + 8) & 1U) == 0) {
        *(undefined4 *)(param_1 + iVar5 + 0x2f04cc) = 0x3f000000;
      }
      else {
        *(undefined4 *)(param_1 + iVar5 + 0x2f04cc) = 0;
      }
      *(undefined4 *)(param_1 + iVar5 + 0x2f04d0) = 0x3c520d21;
      return param_1 + (int)(&DAT_002f047c + iVar5);
    }
    iVar5 = iVar5 + 1;
    ptVar3 = ptVar3 + 0x80;
  } while (iVar5 != 0x32);
  RShellError("Too Many Parcels increase RPARCEL_MAXIMUM");
  return (tVector *)0x0;
}
