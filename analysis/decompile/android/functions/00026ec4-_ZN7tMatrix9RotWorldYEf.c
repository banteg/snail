/*
 * mangled: _ZN7tMatrix9RotWorldYEf
 * demangled: tMatrix::RotWorldY(float)
 * address: 00026ec4
 * size: 144
 */

/* tMatrix::RotWorldY(float) */

void __thiscall tMatrix::RotWorldY(tMatrix *this,float param_1)

{
  float fVar1;
  float fVar2;
  float extraout_s0;
  float fVar3;
  float fVar4;
  float fVar5;

  fVar1 = (float)Cos(param_1);
  fVar2 = (float)Sin(extraout_s0);
  fVar4 = *(float *)(this + 8);
  fVar5 = *(float *)(this + 0x18);
  fVar3 = *(float *)(this + 0x28);
  *(float *)(this + 0x28) = fVar1 * fVar3 - fVar2 * *(float *)(this + 0x20);
  *(float *)(this + 8) = fVar1 * fVar4 - fVar2 * *(float *)this;
  *(float *)(this + 0x18) = fVar1 * fVar5 - fVar2 * *(float *)(this + 0x10);
  *(float *)this = fVar2 * fVar4 + fVar1 * *(float *)this;
  *(float *)(this + 0x10) = fVar2 * fVar5 + fVar1 * *(float *)(this + 0x10);
  *(float *)(this + 0x20) = fVar2 * fVar3 + fVar1 * *(float *)(this + 0x20);
  return;
}
