/*
 * mangled: _Z20ObjectProcShadeEarthP8cRObject
 * demangled: ObjectProcShadeEarth(cRObject*)
 * address: 00036f90
 * size: 152
 */

/* ObjectProcShadeEarth(cRObject*) */

void ObjectProcShadeEarth(cRObject *param_1)

{
  tColour *this;
  int iVar1;
  int iVar2;
  int iVar3;
  float fVar4;

  fVar4 = (float)cRObject::RequestColours(param_1);
  iVar3 = *(int *)(param_1 + 0xa4);
  this = *(tColour **)(param_1 + 0xb4);
  *(uint *)param_1 = *(uint *)param_1 | 0x10000;
  if (*(int *)(param_1 + 0xa0) < 1) {
    return;
  }
  iVar1 = 0;
  iVar2 = 0;
  do {
    while (0.0 <= *(float *)(iVar3 + iVar1 + 4)) {
      fVar4 = (float)tColour::Grey(this,fVar4);
      iVar2 = iVar2 + 1;
      iVar1 = iVar1 + 0xc;
      this = this + 0x10;
      if (*(int *)(param_1 + 0xa0) <= iVar2) {
        return;
      }
    }
    iVar2 = iVar2 + 1;
    iVar1 = iVar1 + 0xc;
    fVar4 = (float)tColour::Grey(this,fVar4);
    this = this + 0x10;
  } while (iVar2 < *(int *)(param_1 + 0xa0));
  return;
}
