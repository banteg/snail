/*
 * mangled: _Z19ObjectProcTileSkirtP8cRObjectPci
 * demangled: ObjectProcTileSkirt(cRObject*, char*, int)
 * address: 00035b80
 * size: 280
 */

/* ObjectProcTileSkirt(cRObject*, char*, int) */

void ObjectProcTileSkirt(cRObject *param_1,char *param_2,int param_3)

{
  float in_s0;

  ObjectProcTileFast(param_1,param_2,in_s0);
  *(float *)(*(int *)(param_1 + 200) + 0x10) = 1.0 - *(float *)(*(int *)(param_1 + 200) + 0x10);
  *(float *)(*(int *)(param_1 + 200) + 0x18) = 1.0 - *(float *)(*(int *)(param_1 + 200) + 0x18);
  *(float *)(*(int *)(param_1 + 200) + 0x20) = 1.0 - *(float *)(*(int *)(param_1 + 200) + 0x20);
  *(float *)(*(int *)(param_1 + 200) + 0x28) = 1.0 - *(float *)(*(int *)(param_1 + 200) + 0x28);
  if ((param_3 & 1U) == 0) {
    *(float *)(*(int *)(param_1 + 0xa4) + 0x20) = *(float *)(*(int *)(param_1 + 0xa4) + 0x20) * 1.9;
    *(float *)(*(int *)(param_1 + 0xa4) + 0x2c) = *(float *)(*(int *)(param_1 + 0xa4) + 0x2c) * 1.9;
  }
  if ((param_3 & 2U) == 0) {
    *(float *)(*(int *)(param_1 + 0xa4) + 8) = *(float *)(*(int *)(param_1 + 0xa4) + 8) * 1.9;
    *(float *)(*(int *)(param_1 + 0xa4) + 0x14) = *(float *)(*(int *)(param_1 + 0xa4) + 0x14) * 1.9;
  }
  if ((param_3 & 4U) == 0) {
    **(float **)(param_1 + 0xa4) = **(float **)(param_1 + 0xa4) * 1.9;
    *(float *)(*(int *)(param_1 + 0xa4) + 0x18) = *(float *)(*(int *)(param_1 + 0xa4) + 0x18) * 1.9;
  }
  if ((param_3 & 8U) != 0) {
    return;
  }
  *(float *)(*(int *)(param_1 + 0xa4) + 0xc) = *(float *)(*(int *)(param_1 + 0xa4) + 0xc) * 1.9;
  *(float *)(*(int *)(param_1 + 0xa4) + 0x24) = *(float *)(*(int *)(param_1 + 0xa4) + 0x24) * 1.9;
  return;
}
