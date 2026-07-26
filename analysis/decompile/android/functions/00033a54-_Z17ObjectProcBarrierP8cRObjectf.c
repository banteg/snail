/*
 * mangled: _Z17ObjectProcBarrierP8cRObjectf
 * demangled: ObjectProcBarrier(cRObject*, float)
 * address: 00033a54
 * size: 24
 */

/* ObjectProcBarrier(cRObject*, float) */

void ObjectProcBarrier(cRObject *param_1,float param_2)

{
  undefined4 in_r1;
  int iVar1;

  iVar1 = *(int *)(param_1 + 0xa4);
  *(undefined4 *)(iVar1 + 0xa4) = in_r1;
  *(undefined4 *)(iVar1 + 0x20) = in_r1;
  *(undefined4 *)(iVar1 + 0x44) = in_r1;
  *(undefined4 *)(iVar1 + 0x80) = in_r1;
  return;
}
