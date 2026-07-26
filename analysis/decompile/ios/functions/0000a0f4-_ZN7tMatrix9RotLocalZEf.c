/*
 * mangled: _ZN7tMatrix9RotLocalZEf
 * demangled: tMatrix::RotLocalZ(float)
 * address: 0000a0f4
 * size: 164
 */

/* tMatrix::RotLocalZ(float) */

void __thiscall tMatrix::RotLocalZ(tMatrix *this,float param_1)

{
  uint uVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;

  fVar3 = *(float *)(this + 0x10);
  uVar1 = (int)((param_1 / 6.2831855) * 32768.0) & 0x7fff;
  fVar2 = (float)(&_RMathCos)[uVar1];
  fVar5 = (float)(&_RMathSin)[uVar1];
  *(float *)(this + 0x10) = fVar2 * fVar3 - fVar5 * *(float *)this;
  fVar4 = *(float *)(this + 0x14);
  *(float *)this = fVar5 * fVar3 + fVar2 * *(float *)this;
  *(float *)(this + 0x14) = fVar2 * fVar4 - fVar5 * *(float *)(this + 4);
  fVar3 = *(float *)(this + 0x18);
  *(float *)(this + 4) = fVar5 * fVar4 + fVar2 * *(float *)(this + 4);
  *(float *)(this + 0x18) = fVar2 * fVar3 - fVar5 * *(float *)(this + 8);
  *(float *)(this + 8) = fVar5 * fVar3 + fVar2 * *(float *)(this + 8);
  return;
}
