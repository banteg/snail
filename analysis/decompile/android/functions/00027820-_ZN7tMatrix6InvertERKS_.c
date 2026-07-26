/*
 * mangled: _ZN7tMatrix6InvertERKS_
 * demangled: tMatrix::Invert(tMatrix const&)
 * address: 00027820
 * size: 192
 */

/* tMatrix::Invert(tMatrix const&) */

void __thiscall tMatrix::Invert(tMatrix *this,tMatrix *param_1)

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
  float fVar12;

  fVar6 = *(float *)(param_1 + 0x34);
  fVar12 = *(float *)(param_1 + 4);
  fVar4 = *(float *)param_1;
  fVar1 = *(float *)(param_1 + 0x30);
  fVar11 = *(float *)(param_1 + 0x38);
  fVar2 = *(float *)(param_1 + 8);
  fVar7 = *(float *)(param_1 + 0x10);
  fVar8 = *(float *)(param_1 + 0x24);
  fVar9 = *(float *)(param_1 + 0x20);
  fVar5 = *(float *)(param_1 + 0x14);
  fVar3 = *(float *)(param_1 + 0x18);
  *(float *)(this + 4) = fVar7;
  *(float *)(this + 8) = fVar9;
  *(float *)(this + 0x18) = fVar8;
  *(undefined4 *)(this + 0x24) = *(undefined4 *)(param_1 + 0x18);
  *(undefined4 *)(this + 0xc) = 0;
  *(undefined4 *)(this + 0x2c) = 0;
  *(undefined4 *)(this + 0x1c) = 0;
  *(undefined4 *)(this + 0x10) = *(undefined4 *)(param_1 + 4);
  *(undefined4 *)(this + 0x20) = *(undefined4 *)(param_1 + 8);
  *(undefined4 *)(this + 0x3c) = 0x3f800000;
  fVar10 = *(float *)(param_1 + 0x28);
  *(float *)this = fVar4;
  *(float *)(this + 0x14) = fVar5;
  *(float *)(this + 0x28) = fVar10;
  *(float *)(this + 0x30) = -(fVar12 * fVar6 + fVar4 * fVar1 + fVar2 * fVar11);
  fVar1 = *(float *)(param_1 + 0x30);
  *(float *)(this + 0x34) = -(fVar5 * fVar6 + fVar1 * fVar7 + fVar3 * fVar11);
  *(float *)(this + 0x38) = -(fVar8 * *(float *)(param_1 + 0x34) + fVar1 * fVar9 + fVar10 * fVar11);
  return;
}
