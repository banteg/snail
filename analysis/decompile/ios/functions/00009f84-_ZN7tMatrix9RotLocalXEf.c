/*
 * mangled: _ZN7tMatrix9RotLocalXEf
 * demangled: tMatrix::RotLocalX(float)
 * address: 00009f84
 * size: 164
 */

/* tMatrix::RotLocalX(float) */

void __thiscall tMatrix::RotLocalX(tMatrix *this,float param_1)

{
  uint uVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;

  fVar3 = *(float *)(this + 0x20);
  uVar1 = (int)((param_1 / 6.2831855) * 32768.0) & 0x7fff;
  fVar2 = (float)(&_RMathCos)[uVar1];
  fVar5 = (float)(&_RMathSin)[uVar1];
  *(float *)(this + 0x20) = fVar2 * fVar3 - fVar5 * *(float *)(this + 0x10);
  fVar4 = *(float *)(this + 0x24);
  *(float *)(this + 0x10) = fVar5 * fVar3 + fVar2 * *(float *)(this + 0x10);
  *(float *)(this + 0x24) = fVar2 * fVar4 - fVar5 * *(float *)(this + 0x14);
  fVar3 = *(float *)(this + 0x28);
  *(float *)(this + 0x14) = fVar5 * fVar4 + fVar2 * *(float *)(this + 0x14);
  *(float *)(this + 0x28) = fVar2 * fVar3 - fVar5 * *(float *)(this + 0x18);
  *(float *)(this + 0x18) = fVar5 * fVar3 + fVar2 * *(float *)(this + 0x18);
  return;
}
