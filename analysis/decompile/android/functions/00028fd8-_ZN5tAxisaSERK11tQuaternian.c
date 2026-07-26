/*
 * mangled: _ZN5tAxisaSERK11tQuaternian
 * demangled: tAxis::operator=(tQuaternian const&)
 * address: 00028fd8
 * size: 112
 */

/* tAxis::TEMPNAMEPLACEHOLDERVALUE(tQuaternian const&) */

void __thiscall tAxis::operator=(tAxis *this,tQuaternian *param_1)

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
  return;
}
