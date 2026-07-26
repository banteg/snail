/*
 * mangled: _ZN7tMatrix6InvertERKS_
 * demangled: tMatrix::Invert(tMatrix const&)
 * address: 00027820
 * size: 192
 */

/* tMatrix::Invert(tMatrix const&) */

void __thiscall tMatrix::Invert(tMatrix *this,tMatrix *param_1)

{
  undefined4 uVar1;
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
  float fVar13;

  fVar7 = *(float *)(param_1 + 0x34);
  fVar13 = *(float *)(param_1 + 4);
  fVar5 = *(float *)param_1;
  fVar2 = *(float *)(param_1 + 0x30);
  fVar12 = *(float *)(param_1 + 0x38);
  fVar3 = *(float *)(param_1 + 8);
  fVar8 = *(float *)(param_1 + 0x10);
  fVar9 = *(float *)(param_1 + 0x24);
  fVar10 = *(float *)(param_1 + 0x20);
  fVar6 = *(float *)(param_1 + 0x14);
  fVar4 = *(float *)(param_1 + 0x18);
  *(float *)(this + 4) = fVar8;
  *(float *)(this + 8) = fVar10;
  *(float *)(this + 0x18) = fVar9;
  *(undefined4 *)(this + 0x24) = *(undefined4 *)(param_1 + 0x18);
  uVar1 = DAT_000278e0;
  *(undefined4 *)(this + 0xc) = DAT_000278e0;
  *(undefined4 *)(this + 0x2c) = uVar1;
  *(undefined4 *)(this + 0x1c) = uVar1;
  *(undefined4 *)(this + 0x10) = *(undefined4 *)(param_1 + 4);
  *(undefined4 *)(this + 0x20) = *(undefined4 *)(param_1 + 8);
  *(undefined4 *)(this + 0x3c) = DAT_000278e4;
  fVar11 = *(float *)(param_1 + 0x28);
  *(float *)this = fVar5;
  *(float *)(this + 0x14) = fVar6;
  *(float *)(this + 0x28) = fVar11;
  *(float *)(this + 0x30) = -(fVar13 * fVar7 + fVar5 * fVar2 + fVar3 * fVar12);
  fVar2 = *(float *)(param_1 + 0x30);
  *(float *)(this + 0x34) = -(fVar6 * fVar7 + fVar2 * fVar8 + fVar4 * fVar12);
  *(float *)(this + 0x38) = -(fVar9 * *(float *)(param_1 + 0x34) + fVar2 * fVar10 + fVar11 * fVar12)
  ;
  return;
}
