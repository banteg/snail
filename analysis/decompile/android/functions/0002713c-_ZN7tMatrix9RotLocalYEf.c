/*
 * mangled: _ZN7tMatrix9RotLocalYEf
 * demangled: tMatrix::RotLocalY(float)
 * address: 0002713c
 * size: 144
 */

/* tMatrix::RotLocalY(float) */

void __thiscall tMatrix::RotLocalY(tMatrix *this,float param_1)

{
  float fVar1;
  float fVar2;
  float extraout_s0;
  float fVar3;
  float fVar4;
  float fVar5;

  fVar1 = (float)Cos(param_1);
  fVar2 = (float)Sin(extraout_s0);
  fVar4 = *(float *)(this + 0x20);
  fVar5 = *(float *)(this + 0x24);
  fVar3 = *(float *)(this + 0x28);
  *(float *)(this + 0x28) = fVar2 * *(float *)(this + 8) + fVar1 * fVar3;
  *(float *)(this + 0x20) = fVar2 * *(float *)this + fVar1 * fVar4;
  *(float *)(this + 0x24) = fVar2 * *(float *)(this + 4) + fVar1 * fVar5;
  *(float *)this = fVar1 * *(float *)this - fVar2 * fVar4;
  *(float *)(this + 4) = fVar1 * *(float *)(this + 4) - fVar2 * fVar5;
  *(float *)(this + 8) = fVar1 * *(float *)(this + 8) - fVar2 * fVar3;
  return;
}
