/*
 * mangled: _ZN11tQuaternianC1ERK5tAxis
 * demangled: tQuaternian::tQuaternian(tAxis const&)
 * address: 00027a20
 * size: 108
 */

/* tQuaternian::tQuaternian(tAxis const&) */

tQuaternian * __thiscall tQuaternian::tQuaternian(tQuaternian *this,tAxis *param_1)

{
  float fVar1;
  undefined4 uVar2;
  float in_s0;
  float extraout_s0;

  fVar1 = (float)Sin(in_s0);
  *(float *)this = fVar1 * *(float *)param_1;
  *(float *)(this + 4) = fVar1 * *(float *)(param_1 + 4);
  *(float *)(this + 8) = fVar1 * *(float *)(param_1 + 8);
  uVar2 = Cos(extraout_s0);
  *(undefined4 *)(this + 0xc) = uVar2;
  return this;
}
