/*
 * mangled: _Z21ObjectProcSightResizeP8cRObjectR7tVector
 * demangled: ObjectProcSightResize(cRObject*, tVector&)
 * address: 00033900
 * size: 92
 */

/* ObjectProcSightResize(cRObject*, tVector&) */

void ObjectProcSightResize(cRObject *param_1,tVector *param_2)

{
  int iVar1;
  float *pfVar2;
  int iVar3;

  iVar3 = *(int *)(param_1 + 0xa0);
  pfVar2 = *(float **)(param_1 + 0xa4);
  if (0 < iVar3) {
    iVar1 = 0;
    do {
      iVar1 = iVar1 + 1;
      if (0.0 < *pfVar2) {
        *pfVar2 = *(float *)param_2 + 0.5;
      }
      if (0.0 < pfVar2[2]) {
        pfVar2[2] = *(float *)(param_2 + 8) + 0.5;
      }
      pfVar2 = pfVar2 + 3;
    } while (iVar1 != iVar3);
    return;
  }
  return;
}
