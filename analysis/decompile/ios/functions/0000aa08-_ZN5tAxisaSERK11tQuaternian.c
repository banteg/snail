/*
 * mangled: _ZN5tAxisaSERK11tQuaternian
 * demangled: tAxis::operator=(tQuaternian const&)
 * address: 0000aa08
 * size: 124
 */

/* tAxis::TEMPNAMEPLACEHOLDERVALUE(tQuaternian const&) */

void __thiscall tAxis::operator=(tAxis *this,tQuaternian *param_1)

{
  float fVar1;
  float fVar2;

  fVar1 = (float)_acosf(*(undefined4 *)(param_1 + 0xc));
  fVar2 = (float)(&_RMathSin)[(int)((fVar1 / 6.2831855) * 32768.0) & 0x7fff];
  *(float *)this = *(float *)param_1 / fVar2;
  *(float *)(this + 4) = *(float *)(param_1 + 4) / fVar2;
  *(float *)(this + 8) = *(float *)(param_1 + 8) / fVar2;
  *(float *)(this + 0xc) = fVar1 + fVar1;
  return;
}
