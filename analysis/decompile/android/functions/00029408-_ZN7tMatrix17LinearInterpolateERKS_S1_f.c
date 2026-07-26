/*
 * mangled: _ZN7tMatrix17LinearInterpolateERKS_S1_f
 * demangled: tMatrix::LinearInterpolate(tMatrix const&, tMatrix const&, float)
 * address: 00029408
 * size: 148
 */

/* tMatrix::LinearInterpolate(tMatrix const&, tMatrix const&, float) */

void __thiscall
tMatrix::LinearInterpolate(tMatrix *this,tMatrix *param_1,tMatrix *param_2,float param_3)

{
  float in_r3;
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;

  Invert(this,param_1);
  fVar1 = (float)operator*=(this,param_2);
  Interpolate(this,fVar1);
  operator/=(this,param_1);
  Orthoganalize(this);
  fVar3 = *(float *)(param_2 + 0x38);
  fVar4 = *(float *)(param_2 + 0x34);
  fVar1 = *(float *)(param_1 + 0x38);
  fVar2 = *(float *)(param_1 + 0x34);
  fVar5 = DAT_0002949c - in_r3;
  *(float *)(this + 0x30) = in_r3 * *(float *)(param_2 + 0x30) + fVar5 * *(float *)(param_1 + 0x30);
  *(float *)(this + 0x38) = in_r3 * fVar3 + fVar5 * fVar1;
  *(float *)(this + 0x34) = in_r3 * fVar4 + fVar5 * fVar2;
  return;
}
