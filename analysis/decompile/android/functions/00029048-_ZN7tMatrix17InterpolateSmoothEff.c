/*
 * mangled: _ZN7tMatrix17InterpolateSmoothEff
 * demangled: tMatrix::InterpolateSmooth(float, float)
 * address: 00029048
 * size: 412
 */

/* tMatrix::InterpolateSmooth(float, float) */

void __thiscall tMatrix::InterpolateSmooth(tMatrix *this,float param_1,float param_2)

{
  float in_r1;
  undefined4 uVar1;
  float in_r2;
  undefined4 uVar2;
  undefined4 uVar3;
  tMatrix *this_00;
  float fVar4;
  float fVar5;
  tMatrix atStack_d0 [64];
  tMatrix local_90 [64];
  float local_50;
  float fStack_4c;
  float fStack_48;
  undefined4 uStack_44;
  tAxis atStack_40 [12];
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  undefined4 uStack_24;

  this_00 = atStack_d0;
  tQuaternian::tQuaternian((tQuaternian *)&local_30);
  tAxis::tAxis(atStack_40);
  tQuaternian::tQuaternian((tQuaternian *)&local_50,this);
  local_30 = local_50;
  local_2c = fStack_4c;
  local_28 = fStack_48;
  uStack_24 = uStack_44;
  if ((-0.001 < local_50) && (local_50 < 0.001)) {
    local_30 = 0.0;
  }
  if ((-0.001 < fStack_4c) && (fStack_4c < 0.001)) {
    local_2c = 0.0;
  }
  if ((-0.001 < fStack_48) && (fStack_48 < 0.001)) {
    local_28 = 0.0;
  }
  if (((local_30 != 0.0) || (local_2c != 0.0)) || (local_28 != 0.0)) {
    tAxis::operator=(atStack_40,(tQuaternian *)&local_30);
    if (local_34 == 0.0) {
      return;
    }
    fVar4 = local_34 * in_r1 - local_34;
    fVar5 = -in_r2;
    if ((-in_r2 <= fVar4) && (fVar5 = fVar4, in_r2 < fVar4)) {
      fVar5 = in_r2;
    }
    local_34 = fVar5 + local_34;
    this_00 = local_90;
    tQuaternian::operator=((tQuaternian *)&local_30,atStack_40);
  }
  tMatrix(this_00,(tQuaternian *)&local_30);
  uVar1 = *(undefined4 *)(this_00 + 4);
  uVar2 = *(undefined4 *)(this_00 + 8);
  uVar3 = *(undefined4 *)(this_00 + 0xc);
  *(undefined4 *)this = *(undefined4 *)this_00;
  *(undefined4 *)(this + 4) = uVar1;
  *(undefined4 *)(this + 8) = uVar2;
  *(undefined4 *)(this + 0xc) = uVar3;
  uVar1 = *(undefined4 *)(this_00 + 0x14);
  uVar2 = *(undefined4 *)(this_00 + 0x18);
  uVar3 = *(undefined4 *)(this_00 + 0x1c);
  *(undefined4 *)(this + 0x10) = *(undefined4 *)(this_00 + 0x10);
  *(undefined4 *)(this + 0x14) = uVar1;
  *(undefined4 *)(this + 0x18) = uVar2;
  *(undefined4 *)(this + 0x1c) = uVar3;
  uVar1 = *(undefined4 *)(this_00 + 0x24);
  uVar2 = *(undefined4 *)(this_00 + 0x28);
  uVar3 = *(undefined4 *)(this_00 + 0x2c);
  *(undefined4 *)(this + 0x20) = *(undefined4 *)(this_00 + 0x20);
  *(undefined4 *)(this + 0x24) = uVar1;
  *(undefined4 *)(this + 0x28) = uVar2;
  *(undefined4 *)(this + 0x2c) = uVar3;
  uVar1 = *(undefined4 *)(this_00 + 0x34);
  uVar2 = *(undefined4 *)(this_00 + 0x38);
  uVar3 = *(undefined4 *)(this_00 + 0x3c);
  *(undefined4 *)(this + 0x30) = *(undefined4 *)(this_00 + 0x30);
  *(undefined4 *)(this + 0x34) = uVar1;
  *(undefined4 *)(this + 0x38) = uVar2;
  *(undefined4 *)(this + 0x3c) = uVar3;
  return;
}
