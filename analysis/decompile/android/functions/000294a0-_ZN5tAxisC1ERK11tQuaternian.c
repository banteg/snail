/*
 * mangled: _ZN5tAxisC1ERK11tQuaternian
 * demangled: tAxis::tAxis(tQuaternian const&)
 * address: 000294a0
 * size: 116
 */

/* tAxis::tAxis(tQuaternian const&) */

tAxis * __thiscall tAxis::tAxis(tAxis *this,tQuaternian *param_1)

{
  float fVar1;
  float fVar2;
  float in_s0;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float fVar3;

  fVar1 = (float)ACos(in_s0);
  fVar3 = *(float *)param_1;
  fVar2 = (float)Sin(extraout_s0);
  *(float *)this = fVar3 / fVar2;
  fVar3 = *(float *)(param_1 + 4);
  fVar2 = (float)Sin(extraout_s0_00);
  *(float *)(this + 4) = fVar3 / fVar2;
  fVar3 = *(float *)(param_1 + 8);
  fVar2 = (float)Sin(extraout_s0_01);
  *(float *)(this + 0xc) = fVar1 + fVar1;
  *(float *)(this + 8) = fVar3 / fVar2;
  return this;
}
