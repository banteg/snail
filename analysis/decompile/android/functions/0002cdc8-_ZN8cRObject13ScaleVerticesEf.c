/*
 * mangled: _ZN8cRObject13ScaleVerticesEf
 * demangled: cRObject::ScaleVertices(float)
 * address: 0002cdc8
 * size: 80
 */

/* cRObject::ScaleVertices(float) */

void __thiscall cRObject::ScaleVertices(cRObject *this,float param_1)

{
  float in_r1;
  int iVar1;
  int iVar2;
  float *pfVar3;

  iVar1 = *(int *)(this + 0xa0);
  if (iVar1 < 1) {
    return;
  }
  pfVar3 = *(float **)(this + 0xa4);
  iVar2 = 0;
  do {
    iVar2 = iVar2 + 1;
    *pfVar3 = *pfVar3 * in_r1;
    pfVar3[1] = pfVar3[1] * in_r1;
    pfVar3[2] = pfVar3[2] * in_r1;
    pfVar3 = pfVar3 + 3;
  } while (iVar2 != iVar1);
  return;
}
