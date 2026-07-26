/*
 * mangled: _ZN7tMatrix6InvertEv
 * demangled: tMatrix::Invert()
 * address: 00027798
 * size: 136
 */

/* tMatrix::Invert() */

void __thiscall tMatrix::Invert(tMatrix *this)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;

  fVar8 = *(float *)(this + 0x34);
  fVar9 = *(float *)(this + 0x24);
  fVar1 = *(float *)(this + 4);
  fVar5 = *(float *)(this + 0x18);
  *(float *)(this + 0x18) = fVar9;
  fVar6 = *(float *)(this + 0x30);
  fVar2 = *(float *)(this + 0x20);
  fVar3 = *(float *)(this + 0x10);
  fVar7 = *(float *)(this + 0x38);
  fVar4 = *(float *)(this + 8);
  *(float *)(this + 0x24) = fVar5;
  *(float *)(this + 4) = fVar3;
  *(float *)(this + 8) = fVar2;
  *(float *)(this + 0x10) = fVar1;
  *(float *)(this + 0x20) = fVar4;
  *(float *)(this + 0x30) = -(fVar8 * fVar1 + fVar6 * *(float *)this + fVar7 * fVar4);
  *(float *)(this + 0x34) = -(*(float *)(this + 0x14) * fVar8 + fVar3 * fVar6 + fVar5 * fVar7);
  *(float *)(this + 0x38) = -(fVar9 * fVar8 + fVar2 * fVar6 + *(float *)(this + 0x28) * fVar7);
  return;
}
