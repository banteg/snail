/*
 * mangled: _Z23ObjectProcTileFloorRampiP8cRObject
 * demangled: ObjectProcTileFloorRamp(int, cRObject*)
 * address: 00036784
 * size: 320
 */

/* ObjectProcTileFloorRamp(int, cRObject*) */

void ObjectProcTileFloorRamp(int param_1,cRObject *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  cRFaceQuad *this;
  int iVar6;

  iVar2 = *(int *)(param_2 + 0xa4);
  this = *(cRFaceQuad **)(param_2 + 200);
  iVar3 = *(int *)(param_2 + 0xc0);
  iVar5 = param_1 * 0x10;
  iVar4 = iVar2 + *(int *)(ObjectProcFloorRampData + param_1 * 0x10) * 0xc;
  iVar6 = iVar2 + *(int *)(ObjectProcFloorRampData + iVar5 + 4) * 0xc;
  iVar1 = iVar2 + *(int *)(ObjectProcFloorRampData + iVar5 + 8) * 0xc;
  iVar2 = iVar2 + *(int *)(ObjectProcFloorRampData + iVar5 + 0xc) * 0xc;
  *(float *)(iVar4 + 4) = *(float *)(iVar4 + 4) + 0.5;
  *(float *)(iVar6 + 4) = *(float *)(iVar6 + 4) + 0.5;
  *(float *)(iVar1 + 4) = *(float *)(iVar1 + 4) + 0.425;
  *(float *)(iVar2 + 4) = *(float *)(iVar2 + 4) + 0.425;
  if (iVar3 < 1) {
    return;
  }
  iVar5 = 0;
  if (param_1 == 1) {
    do {
      iVar5 = iVar5 + 1;
      cRFaceQuad::RotateUVCCW(this);
      cRFaceQuad::RotateUVCCW(this);
      this = this + 0x30;
    } while (iVar5 < *(int *)(param_2 + 0xc0));
    return;
  }
  if (param_1 == 3) {
    do {
      iVar5 = iVar5 + 1;
      cRFaceQuad::RotateUVCCW(this);
      cRFaceQuad::RotateUVCCW(this);
      cRFaceQuad::RotateUVCCW(this);
      this = this + 0x30;
    } while (iVar5 < *(int *)(param_2 + 0xc0));
    return;
  }
  if (param_1 == 0) {
    do {
      iVar5 = iVar5 + 1;
      cRFaceQuad::RotateUVCCW(this);
      this = this + 0x30;
    } while (iVar5 < *(int *)(param_2 + 0xc0));
    return;
  }
  do {
    iVar5 = iVar5 + 1;
  } while (iVar5 < iVar3);
  return;
}
