/*
 * mangled: _ZN7tMatrix9RotWorldXEf
 * demangled: tMatrix::RotWorldX(float)
 * address: 00026e34
 * size: 144
 */

/* tMatrix::RotWorldX(float) */

void __thiscall tMatrix::RotWorldX(tMatrix *this,float param_1)

{
  float fVar1;
  float fVar2;
  float extraout_s0;
  float fVar3;
  float fVar4;
  float fVar5;

  fVar1 = (float)Cos(param_1);
  fVar2 = (float)Sin(extraout_s0);
  fVar4 = *(float *)(this + 4);
  fVar5 = *(float *)(this + 0x14);
  fVar3 = *(float *)(this + 0x24);
  *(float *)(this + 0x24) = fVar1 * fVar3 - fVar2 * *(float *)(this + 0x28);
  *(float *)(this + 4) = fVar1 * fVar4 - fVar2 * *(float *)(this + 8);
  *(float *)(this + 0x14) = fVar1 * fVar5 - fVar2 * *(float *)(this + 0x18);
  *(float *)(this + 8) = fVar2 * fVar4 + fVar1 * *(float *)(this + 8);
  *(float *)(this + 0x18) = fVar2 * fVar5 + fVar1 * *(float *)(this + 0x18);
  *(float *)(this + 0x28) = fVar2 * fVar3 + fVar1 * *(float *)(this + 0x28);
  return;
}
