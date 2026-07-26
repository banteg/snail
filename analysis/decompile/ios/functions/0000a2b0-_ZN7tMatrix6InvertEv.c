/*
 * mangled: _ZN7tMatrix6InvertEv
 * demangled: tMatrix::Invert()
 * address: 0000a2b0
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
  fVar6 = *(float *)(this + 4);
  fVar9 = *(float *)(this + 0x30);
  fVar7 = *(float *)(this + 0x38);
  fVar5 = *(float *)(this + 8);
  fVar3 = *(float *)(this + 0x10);
  fVar4 = *(float *)(this + 0x18);
  fVar1 = *(float *)(this + 0x24);
  fVar2 = *(float *)(this + 0x20);
  *(float *)(this + 4) = fVar3;
  *(float *)(this + 8) = fVar2;
  *(float *)(this + 0x10) = fVar6;
  *(float *)(this + 0x18) = fVar1;
  *(float *)(this + 0x20) = fVar5;
  *(float *)(this + 0x24) = fVar4;
  *(float *)(this + 0x30) = -(fVar8 * fVar6 + fVar9 * *(float *)this + fVar7 * fVar5);
  *(float *)(this + 0x34) = -(*(float *)(this + 0x14) * fVar8 + fVar3 * fVar9 + fVar4 * fVar7);
  *(float *)(this + 0x38) = -(fVar1 * fVar8 + fVar2 * fVar9 + *(float *)(this + 0x28) * fVar7);
  return;
}
