/*
 * mangled: _ZN7tMatrix23LinearInterpolateSmoothERKS_S1_ff
 * demangled: tMatrix::LinearInterpolateSmooth(tMatrix const&, tMatrix const&, float, float)
 * address: 000291f0
 * size: 152
 */

/* tMatrix::LinearInterpolateSmooth(tMatrix const&, tMatrix const&, float, float) */

void tMatrix::LinearInterpolateSmooth(tMatrix *param_1,tMatrix *param_2,float param_3,float param_4)

{
  tMatrix *in_r2;
  float in_r3;
  undefined8 uVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;

  Invert(param_1,param_2);
  uVar1 = operator*=(param_1,in_r2);
  InterpolateSmooth(param_1,(float)uVar1,(float)((ulonglong)uVar1 >> 0x20));
  operator/=(param_1,param_2);
  Orthoganalize(param_1);
  fVar4 = *(float *)(in_r2 + 0x38);
  fVar5 = *(float *)(in_r2 + 0x34);
  fVar2 = *(float *)(param_2 + 0x38);
  fVar3 = *(float *)(param_2 + 0x34);
  fVar6 = DAT_00029288 - in_r3;
  *(float *)(param_1 + 0x30) = in_r3 * *(float *)(in_r2 + 0x30) + fVar6 * *(float *)(param_2 + 0x30)
  ;
  *(float *)(param_1 + 0x38) = in_r3 * fVar4 + fVar6 * fVar2;
  *(float *)(param_1 + 0x34) = in_r3 * fVar5 + fVar6 * fVar3;
  return;
}
