/*
 * mangled: _Z21ObjectProcLightObjectP8cRObject7tVectorff
 * demangled: ObjectProcLightObject(cRObject*, tVector, float, float)
 * address: 00036198
 * size: 188
 */

/* ObjectProcLightObject(cRObject*, tVector, float, float) */

void ObjectProcLightObject(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  tVector *ptVar1;
  tColour *this;
  int iVar2;
  float extraout_s0;
  float extraout_s1;
  float extraout_s2;
  float extraout_s3;
  undefined4 local_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;

  this = *(tColour **)(param_1 + 0xb4);
  ptVar1 = *(tVector **)(param_1 + 0xb0);
  if (0 < *(int *)(param_1 + 0xa0)) {
    iVar2 = 0;
    do {
      local_3c = param_2;
      uStack_38 = param_3;
      uStack_34 = param_4;
      tVector::Dot((tVector *)&local_3c,ptVar1);
      tColour::Set(this,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
      iVar2 = iVar2 + 1;
      this = this + 0x10;
      ptVar1 = ptVar1 + 0xc;
    } while (iVar2 < *(int *)(param_1 + 0xa0));
  }
  return;
}
