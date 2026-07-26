/*
 * mangled: _Z22ObjectProcTileFastRampiP8cRObject
 * demangled: ObjectProcTileFastRamp(int, cRObject*)
 * address: 00015644
 * size: 108
 */

/* ObjectProcTileFastRamp(int, cRObject*) */

void ObjectProcTileFastRamp(int param_1,cRObject *param_2)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;

  *(uint *)param_2 = *(uint *)param_2 & 0xf7ffffff;
  puVar1 = (undefined4 *)param_1;
  if (0 < param_1) {
    puVar1 = &_ObjectProcFloorRampData;
  }
  iVar2 = *(int *)(param_2 + 0xa4);
  if (param_1 < 1) {
    puVar1 = &_ObjectProcFloorRampData;
    iVar3 = _ObjectProcFloorRampData * 0xc + iVar2;
    *(float *)(iVar3 + 4) = *(float *)(iVar3 + 4) + 0.5;
    if (param_1 != 0) {
      return;
    }
  }
  iVar2 = puVar1[1] * 0xc + iVar2;
  *(float *)(iVar2 + 4) = *(float *)(iVar2 + 4) + 0.5;
  return;
}
