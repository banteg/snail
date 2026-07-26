/*
 * mangled: _Z29ObjectProcTileFloorCornerFastiP8cRObjectPc
 * demangled: ObjectProcTileFloorCornerFast(int, cRObject*, char*)
 * address: 000159f8
 * size: 140
 */

/* ObjectProcTileFloorCornerFast(int, cRObject*, char*) */

void ObjectProcTileFloorCornerFast(int param_1,cRObject *param_2,char *param_3)

{
  int iVar1;
  float *pfVar2;
  undefined4 uVar3;
  float fVar4;

  ObjectProcTileFloorFast(param_2,param_3,0.0);
  iVar1 = *(int *)(param_2 + 0xa4);
  pfVar2 = (float *)(*(int *)(&_ObjectProcFloorCornerFastData + param_1 * 4) * 0xc + iVar1);
  fVar4 = *pfVar2;
  if (fVar4 < 0.0) {
    fVar4 = -0.3;
  }
  else if (fVar4 == 0.0) {
    fVar4 = 0.0;
  }
  else {
    fVar4 = 0.3;
  }
  *pfVar2 = fVar4;
  iVar1 = *(int *)(&_ObjectProcFloorCornerFastData + param_1 * 4) * 0xc + iVar1;
  fVar4 = *(float *)(iVar1 + 8);
  if (fVar4 < 0.0) {
    uVar3 = 0xbe99999a;
  }
  else if (fVar4 == 0.0) {
    uVar3 = 0;
  }
  else {
    uVar3 = 0x3e99999a;
  }
  *(undefined4 *)(iVar1 + 8) = uVar3;
  return;
}
