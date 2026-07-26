/*
 * mangled: _Z19ObjectProcFadeFloorP8cRObjectff
 * demangled: ObjectProcFadeFloor(cRObject*, float, float)
 * address: 0003c348
 * size: 196
 */

/* ObjectProcFadeFloor(cRObject*, float, float) */

void ObjectProcFadeFloor(cRObject *param_1,float param_2,float param_3)

{
  int iVar1;
  tVector *this;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  float extraout_s0;
  float extraout_s1;
  float extraout_s2;
  float extraout_s3;
  undefined4 local_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;

  cRObject::RequestColours(param_1);
  this = *(tVector **)(param_1 + 0xa4);
  iVar2 = *(int *)(param_1 + 0xb4);
  *(uint *)param_1 = *(uint *)param_1 | 0x10000;
  if (0 < *(int *)(param_1 + 0xa0)) {
    iVar1 = 0;
    do {
      tVector::Magnitude(this);
      this = this + 0xc;
      tColour::tColour((tColour *)&local_40,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
      iVar3 = *(int *)(param_1 + 0xa0);
      puVar4 = (undefined4 *)(iVar2 + iVar1 * 0x10);
      iVar1 = iVar1 + 1;
      *puVar4 = local_40;
      puVar4[1] = uStack_3c;
      puVar4[2] = uStack_38;
      puVar4[3] = uStack_34;
    } while (iVar1 < iVar3);
  }
  return;
}
