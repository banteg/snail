/*
 * mangled: _Z26ObjectProcResizeTrampolineP8cRObjectii
 * demangled: ObjectProcResizeTrampoline(cRObject*, int, int)
 * address: 00033a1c
 * size: 52
 */

/* ObjectProcResizeTrampoline(cRObject*, int, int) */

void ObjectProcResizeTrampoline(cRObject *param_1,int param_2,int param_3)

{
  float *pfVar1;
  uint in_fpscr;
  float fVar2;
  float fVar3;

  fVar2 = (float)VectorSignedToFloat(param_3,(byte)(in_fpscr >> 0x16) & 3);
  pfVar1 = *(float **)(param_1 + 0xa4);
  fVar3 = (float)VectorSignedToFloat(param_2,(byte)(in_fpscr >> 0x16) & 3);
  pfVar1[2] = fVar3 - 0.5;
  pfVar1[5] = fVar3 - 0.5;
  *pfVar1 = fVar2 - 0.5;
  pfVar1[6] = fVar2 - 0.5;
  return;
}
