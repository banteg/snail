/*
 * mangled: _ZN7tMatrix9RotLocalXEf
 * demangled: tMatrix::RotLocalX(float)
 * address: 00026fe4
 * size: 144
 */

/* tMatrix::RotLocalX(float) */

void __thiscall tMatrix::RotLocalX(tMatrix *this,float param_1)

{
  float fVar1;
  float fVar2;
  float extraout_s0;
  float fVar3;
  float fVar4;
  float fVar5;

  fVar1 = (float)Cos(param_1);
  fVar2 = (float)Sin(extraout_s0);
  fVar4 = *(float *)(this + 0x10);
  fVar5 = *(float *)(this + 0x14);
  fVar3 = *(float *)(this + 0x18);
  *(float *)(this + 0x18) = fVar2 * *(float *)(this + 0x28) + fVar1 * fVar3;
  *(float *)(this + 0x10) = fVar2 * *(float *)(this + 0x20) + fVar1 * fVar4;
  *(float *)(this + 0x14) = fVar2 * *(float *)(this + 0x24) + fVar1 * fVar5;
  *(float *)(this + 0x20) = fVar1 * *(float *)(this + 0x20) - fVar2 * fVar4;
  *(float *)(this + 0x24) = fVar1 * *(float *)(this + 0x24) - fVar2 * fVar5;
  *(float *)(this + 0x28) = fVar1 * *(float *)(this + 0x28) - fVar2 * fVar3;
  return;
}
