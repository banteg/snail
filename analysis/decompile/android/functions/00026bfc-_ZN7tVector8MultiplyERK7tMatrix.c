/*
 * mangled: _ZN7tVector8MultiplyERK7tMatrix
 * demangled: tVector::Multiply(tMatrix const&)
 * address: 00026bfc
 * size: 124
 */

/* tVector::Multiply(tMatrix const&) */

void __thiscall tVector::Multiply(tVector *this,tMatrix *param_1)

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
  float fVar10;
  float fVar11;

  fVar7 = *(float *)(this + 4);
  fVar10 = *(float *)(param_1 + 0x14);
  fVar11 = *(float *)(param_1 + 0x18);
  fVar8 = *(float *)this;
  fVar2 = *(float *)(param_1 + 4);
  fVar1 = *(float *)(param_1 + 8);
  fVar9 = *(float *)(this + 8);
  fVar4 = *(float *)(param_1 + 0x24);
  fVar3 = *(float *)(param_1 + 0x28);
  fVar6 = *(float *)(param_1 + 0x38);
  fVar5 = *(float *)(param_1 + 0x34);
  *(float *)this =
       fVar7 * *(float *)(param_1 + 0x10) + fVar8 * *(float *)param_1 +
       fVar9 * *(float *)(param_1 + 0x20) + *(float *)(param_1 + 0x30);
  *(float *)(this + 4) = fVar7 * fVar10 + fVar8 * fVar2 + fVar9 * fVar4 + fVar5;
  *(float *)(this + 8) = fVar7 * fVar11 + fVar8 * fVar1 + fVar9 * fVar3 + fVar6;
  return;
}
