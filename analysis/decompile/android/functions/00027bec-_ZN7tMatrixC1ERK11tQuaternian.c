/*
 * mangled: _ZN7tMatrixC1ERK11tQuaternian
 * demangled: tMatrix::tMatrix(tQuaternian const&)
 * address: 00027bec
 * size: 220
 */

/* tMatrix::tMatrix(tQuaternian const&) */

void __thiscall tMatrix::tMatrix(tMatrix *this,tQuaternian *param_1)

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

  fVar4 = *(float *)param_1;
  fVar6 = *(float *)(param_1 + 4);
  fVar7 = *(float *)(param_1 + 8);
  fVar1 = *(float *)(param_1 + 0xc);
  *(undefined4 *)(this + 0x30) = 0;
  *(undefined4 *)(this + 0x2c) = 0;
  *(undefined4 *)(this + 0x1c) = 0;
  *(undefined4 *)(this + 0xc) = 0;
  *(undefined4 *)(this + 0x38) = 0;
  *(undefined4 *)(this + 0x34) = 0;
  *(undefined4 *)(this + 0x3c) = 0x3f800000;
  *(float *)(this + 0x28) = (fVar4 * fVar4 + fVar6 * fVar6) * -2.0 + 1.0;
  *(float *)this = (fVar6 * fVar6 + fVar7 * fVar7) * -2.0 + 1.0;
  fVar9 = fVar6 * fVar7 + fVar4 * fVar1;
  *(float *)(this + 0x14) = (fVar4 * fVar4 + fVar7 * fVar7) * -2.0 + 1.0;
  fVar5 = fVar4 * fVar6 + fVar7 * fVar1;
  fVar8 = fVar4 * fVar7 - fVar6 * fVar1;
  fVar2 = fVar4 * fVar6 - fVar7 * fVar1;
  fVar3 = fVar4 * fVar7 + fVar6 * fVar1;
  fVar1 = fVar6 * fVar7 - fVar4 * fVar1;
  *(float *)(this + 0x10) = fVar2 + fVar2;
  *(float *)(this + 0x20) = fVar3 + fVar3;
  *(float *)(this + 4) = fVar5 + fVar5;
  *(float *)(this + 0x24) = fVar1 + fVar1;
  *(float *)(this + 8) = fVar8 + fVar8;
  *(float *)(this + 0x18) = fVar9 + fVar9;
  return;
}
