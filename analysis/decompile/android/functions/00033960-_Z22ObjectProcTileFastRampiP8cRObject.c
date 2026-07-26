/*
 * mangled: _Z22ObjectProcTileFastRampiP8cRObject
 * demangled: ObjectProcTileFastRamp(int, cRObject*)
 * address: 00033960
 * size: 116
 */

/* ObjectProcTileFastRamp(int, cRObject*) */

void ObjectProcTileFastRamp(int param_1,cRObject *param_2)

{
  int iVar1;
  int iVar2;

  iVar1 = *(int *)(param_2 + 0xa4);
  *(uint *)param_2 = *(uint *)param_2 & 0xf7ffffff;
  if ((param_1 < 1) &&
     (iVar2 = iVar1 + ObjectProcFloorRampData._0_4_ * 0xc,
     *(float *)(iVar2 + 4) = *(float *)(iVar2 + 4) + 0.5, param_1 != 0)) {
    return;
  }
  iVar1 = iVar1 + ObjectProcFloorRampData._4_4_ * 0xc;
  *(float *)(iVar1 + 4) = *(float *)(iVar1 + 4) + 0.5;
  return;
}
