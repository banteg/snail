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
  float fVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  float extraout_s0;
  float extraout_s1;
  float extraout_s2;
  float extraout_s3;
  float fVar6;
  float fVar7;
  float fVar8;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;

  uVar3 = DAT_0006fd78;
  if ((*(uint *)(**(int **)(DAT_0006fd90 + 0x6fc80 + DAT_0006fd94) + 0x2d8) & 3) == 0) {
    iVar2 = cRSpriteManager::New
                      (*(int *)(DAT_0006fd90 + 0x6fc80 + DAT_0006fd98),*(int *)(param_3 + 0x370),
                       0x13,-1);
    fVar6 = DAT_0006fd80;
    fVar1 = DAT_0006fd7c;
    iVar5 = *(int *)(this + 0x80);
    *(undefined4 *)(iVar2 + 0x68) = uVar3;
    fVar8 = *(float *)(iVar5 + 0x54);
    *(undefined4 *)(iVar2 + 0x70) = uVar3;
    *(uint *)(iVar2 + 4) = *(uint *)(iVar2 + 4) | 0x800;
    *(float *)(iVar2 + 0x6c) = fVar8 * fVar6;
    *(float *)(iVar2 + 0x74) = fVar8 * fVar1;
    tColour::tColour((tColour *)&local_30,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
    fVar1 = DAT_0006fd84;
    *(undefined4 *)(iVar2 + 0x60) = DAT_0006fd88;
    *(undefined4 *)(iVar2 + 100) = DAT_0006fd8c;
    *(undefined4 *)(iVar2 + 0x2c) = local_30;
    *(undefined4 *)(iVar2 + 0x30) = uStack_2c;
    *(undefined4 *)(iVar2 + 0x34) = uStack_28;
    *(undefined4 *)(iVar2 + 0x38) = uStack_24;
    fVar8 = *(float *)(param_2 + 8);
    fVar6 = *(float *)(param_2 + 4);
    fVar7 = *(float *)param_2;
    *(undefined4 *)(iVar2 + 0x78) = uVar3;
    *(float *)(iVar2 + 0x5c) = fVar8 * fVar1;
    *(float *)(iVar2 + 0x54) = fVar1 * fVar7;
    *(float *)(iVar2 + 0x58) = fVar1 * fVar6;
    uVar3 = *(undefined4 *)(param_1 + 4);
    uVar4 = *(undefined4 *)(param_1 + 8);
    *(undefined4 *)(iVar2 + 0x48) = *(undefined4 *)param_1;
    *(undefined4 *)(iVar2 + 0x4c) = uVar3;
    *(undefined4 *)(iVar2 + 0x50) = uVar4;
  }
  return;
}
