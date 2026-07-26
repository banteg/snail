/*
 * mangled: _ZN7tMatrixC1ERK11tQuaternian
 * demangled: tMatrix::tMatrix(tQuaternian const&)
 * address: 00027bec
 * size: 220
 */

/* tMatrix::tMatrix(tQuaternian const&) */

void __thiscall tMatrix::tMatrix(tMatrix *this,tQuaternian *param_1)

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

  uVar1 = DAT_00027cc8;
  fVar5 = *(float *)param_1;
  fVar7 = *(float *)(param_1 + 4);
  fVar8 = *(float *)(param_1 + 8);
  fVar2 = *(float *)(param_1 + 0xc);
  *(undefined4 *)(this + 0x30) = DAT_00027cc8;
  *(undefined4 *)(this + 0x2c) = uVar1;
  *(undefined4 *)(this + 0x1c) = uVar1;
  *(undefined4 *)(this + 0xc) = uVar1;
  *(undefined4 *)(this + 0x38) = uVar1;
  *(undefined4 *)(this + 0x34) = uVar1;
  fVar4 = DAT_00027cd0;
  fVar3 = DAT_00027ccc;
  *(float *)(this + 0x3c) = DAT_00027ccc;
  *(float *)(this + 0x28) = fVar3 + (fVar5 * fVar5 + fVar7 * fVar7) * fVar4;
  *(float *)this = fVar3 + (fVar7 * fVar7 + fVar8 * fVar8) * fVar4;
  fVar10 = fVar7 * fVar8 + fVar5 * fVar2;
  *(float *)(this + 0x14) = fVar3 + (fVar5 * fVar5 + fVar8 * fVar8) * fVar4;
  fVar6 = fVar5 * fVar7 + fVar8 * fVar2;
  fVar9 = fVar5 * fVar8 - fVar7 * fVar2;
  fVar3 = fVar5 * fVar7 - fVar8 * fVar2;
  fVar4 = fVar5 * fVar8 + fVar7 * fVar2;
  fVar2 = fVar7 * fVar8 - fVar5 * fVar2;
  *(float *)(this + 0x10) = fVar3 + fVar3;
  *(float *)(this + 0x20) = fVar4 + fVar4;
  *(float *)(this + 4) = fVar6 + fVar6;
  *(float *)(this + 0x24) = fVar2 + fVar2;
  *(float *)(this + 8) = fVar9 + fVar9;
  *(float *)(this + 0x18) = fVar10 + fVar10;
  return;
}
