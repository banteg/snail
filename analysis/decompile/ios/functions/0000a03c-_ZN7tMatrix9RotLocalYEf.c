/*
 * mangled: _ZN7tMatrix9RotLocalYEf
 * demangled: tMatrix::RotLocalY(float)
 * address: 0000a03c
 * size: 164
 */

/* tMatrix::RotLocalY(float) */

void __thiscall tMatrix::RotLocalY(tMatrix *this,float param_1)

{
  uint uVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;

  fVar3 = *(float *)this;
  uVar1 = (int)((param_1 / 6.2831855) * 32768.0) & 0x7fff;
  fVar2 = (float)(&_RMathCos)[uVar1];
  fVar5 = (float)(&_RMathSin)[uVar1];
  *(float *)this = fVar2 * fVar3 - fVar5 * *(float *)(this + 0x20);
  fVar4 = *(float *)(this + 4);
  *(float *)(this + 0x20) = fVar5 * fVar3 + fVar2 * *(float *)(this + 0x20);
  *(float *)(this + 4) = fVar2 * fVar4 - fVar5 * *(float *)(this + 0x24);
  fVar3 = *(float *)(this + 8);
  *(float *)(this + 0x24) = fVar5 * fVar4 + fVar2 * *(float *)(this + 0x24);
  *(float *)(this + 8) = fVar2 * fVar3 - fVar5 * *(float *)(this + 0x28);
  *(float *)(this + 0x28) = fVar5 * fVar3 + fVar2 * *(float *)(this + 0x28);
  return;
}
