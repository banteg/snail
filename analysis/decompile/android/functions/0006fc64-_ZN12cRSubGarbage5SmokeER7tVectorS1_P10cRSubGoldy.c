/*
 * mangled: _ZN12cRSubGarbage5SmokeER7tVectorS1_P10cRSubGoldy
 * demangled: cRSubGarbage::Smoke(tVector&, tVector&, cRSubGoldy*)
 * address: 0006fc64
 * size: 276
 */

/* cRSubGarbage::Smoke(tVector&, tVector&, cRSubGoldy*) */

void __thiscall
cRSubGarbage::Smoke(cRSubGarbage *this,tVector *param_1,tVector *param_2,cRSubGoldy *param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  float extraout_s0;
  float extraout_s1;
  float extraout_s2;
  float extraout_s3;
  float fVar5;
  float fVar6;
  float fVar7;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;

  if ((*(uint *)(Game + 0x2d8) & 3) == 0) {
    iVar1 = cRSpriteManager::New((int)&gRSpriteManager,*(int *)(param_3 + 0x370),0x13,-1);
    iVar4 = *(int *)(this + 0x80);
    *(undefined4 *)(iVar1 + 0x68) = 0;
    fVar7 = *(float *)(iVar4 + 0x54);
    *(undefined4 *)(iVar1 + 0x70) = 0;
    *(uint *)(iVar1 + 4) = *(uint *)(iVar1 + 4) | 0x800;
    *(float *)(iVar1 + 0x6c) = fVar7 * 0.033333335;
    *(float *)(iVar1 + 0x74) = fVar7 * 0.4166667;
    tColour::tColour((tColour *)&local_30,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
    *(undefined4 *)(iVar1 + 0x60) = 0x3e99999a;
    *(undefined4 *)(iVar1 + 100) = 0x3fa66666;
    *(undefined4 *)(iVar1 + 0x2c) = local_30;
    *(undefined4 *)(iVar1 + 0x30) = uStack_2c;
    *(undefined4 *)(iVar1 + 0x34) = uStack_28;
    *(undefined4 *)(iVar1 + 0x38) = uStack_24;
    fVar5 = *(float *)(param_2 + 8);
    fVar7 = *(float *)(param_2 + 4);
    fVar6 = *(float *)param_2;
    *(undefined4 *)(iVar1 + 0x78) = 0;
    *(float *)(iVar1 + 0x5c) = fVar5 * 0.2;
    *(float *)(iVar1 + 0x54) = fVar6 * 0.2;
    *(float *)(iVar1 + 0x58) = fVar7 * 0.2;
    uVar2 = *(undefined4 *)(param_1 + 4);
    uVar3 = *(undefined4 *)(param_1 + 8);
    *(undefined4 *)(iVar1 + 0x48) = *(undefined4 *)param_1;
    *(undefined4 *)(iVar1 + 0x4c) = uVar2;
    *(undefined4 *)(iVar1 + 0x50) = uVar3;
  }
  return;
}
