/*
 * mangled: _ZN7tMatrix9RotLocalZEf
 * demangled: tMatrix::RotLocalZ(float)
 * address: 000271cc
 * size: 144
 */

/* tMatrix::RotLocalZ(float) */

void __thiscall tMatrix::RotLocalZ(tMatrix *this,float param_1)

{
  float fVar1;
  float fVar2;
  float extraout_s0;
  float fVar3;
  float fVar4;
  float fVar5;

  fVar1 = (float)Cos(param_1);
  fVar2 = (float)Sin(extraout_s0);
  fVar4 = *(float *)this;
  fVar5 = *(float *)(this + 4);
  fVar3 = *(float *)(this + 8);
  *(float *)(this + 8) = fVar2 * *(float *)(this + 0x18) + fVar1 * fVar3;
  *(float *)this = fVar2 * *(float *)(this + 0x10) + fVar1 * fVar4;
  *(float *)(this + 4) = fVar2 * *(float *)(this + 0x14) + fVar1 * fVar5;
  *(float *)(this + 0x10) = fVar1 * *(float *)(this + 0x10) - fVar2 * fVar4;
  *(float *)(this + 0x14) = fVar1 * *(float *)(this + 0x14) - fVar2 * fVar5;
  *(float *)(this + 0x18) = fVar1 * *(float *)(this + 0x18) - fVar2 * fVar3;
  return;
}
