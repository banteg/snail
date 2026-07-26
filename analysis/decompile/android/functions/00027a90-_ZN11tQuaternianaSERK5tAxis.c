/*
 * mangled: _ZN11tQuaternianaSERK5tAxis
 * demangled: tQuaternian::operator=(tAxis const&)
 * address: 00027a90
 * size: 104
 */

/* tQuaternian::TEMPNAMEPLACEHOLDERVALUE(tAxis const&) */

void __thiscall tQuaternian::operator=(tQuaternian *this,tAxis *param_1)

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
  return;
}
