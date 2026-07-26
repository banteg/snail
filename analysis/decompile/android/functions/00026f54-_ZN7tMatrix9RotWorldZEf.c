/*
 * mangled: _ZN7tMatrix9RotWorldZEf
 * demangled: tMatrix::RotWorldZ(float)
 * address: 00026f54
 * size: 144
 */

/* tMatrix::RotWorldZ(float) */

void __thiscall tMatrix::RotWorldZ(tMatrix *this,float param_1)

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
  fVar5 = *(float *)(this + 0x10);
  fVar3 = *(float *)(this + 0x20);
  *(float *)(this + 0x20) = fVar1 * fVar3 - fVar2 * *(float *)(this + 0x24);
  *(float *)this = fVar1 * fVar4 - fVar2 * *(float *)(this + 4);
  *(float *)(this + 0x10) = fVar1 * fVar5 - fVar2 * *(float *)(this + 0x14);
  *(float *)(this + 4) = fVar2 * fVar4 + fVar1 * *(float *)(this + 4);
  *(float *)(this + 0x14) = fVar2 * fVar5 + fVar1 * *(float *)(this + 0x14);
  *(float *)(this + 0x24) = fVar2 * fVar3 + fVar1 * *(float *)(this + 0x24);
  return;
}
