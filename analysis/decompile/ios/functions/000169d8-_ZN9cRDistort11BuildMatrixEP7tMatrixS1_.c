/*
 * mangled: _ZN9cRDistort11BuildMatrixEP7tMatrixS1_
 * demangled: cRDistort::BuildMatrix(tMatrix*, tMatrix*)
 * address: 000169d8
 * size: 404
 */

/* cRDistort::BuildMatrix(tMatrix*, tMatrix*) */

void __thiscall cRDistort::BuildMatrix(cRDistort *this,tMatrix *param_1,tMatrix *param_2)

{
  float fVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  float fVar5;
  float fVar6;
  float fVar7;

  uVar2 = *(undefined4 *)(param_1 + 4);
  uVar3 = *(undefined4 *)(param_1 + 8);
  uVar4 = *(undefined4 *)(param_1 + 0xc);
  *(undefined4 *)param_2 = *(undefined4 *)param_1;
  *(undefined4 *)(param_2 + 4) = uVar2;
  *(undefined4 *)(param_2 + 8) = uVar3;
  *(undefined4 *)(param_2 + 0xc) = uVar4;
  uVar2 = *(undefined4 *)(param_1 + 0x14);
  uVar3 = *(undefined4 *)(param_1 + 0x18);
  uVar4 = *(undefined4 *)(param_1 + 0x1c);
  *(undefined4 *)(param_2 + 0x10) = *(undefined4 *)(param_1 + 0x10);
  *(undefined4 *)(param_2 + 0x14) = uVar2;
  *(undefined4 *)(param_2 + 0x18) = uVar3;
  *(undefined4 *)(param_2 + 0x1c) = uVar4;
  uVar2 = *(undefined4 *)(param_1 + 0x24);
  uVar3 = *(undefined4 *)(param_1 + 0x28);
  uVar4 = *(undefined4 *)(param_1 + 0x2c);
  *(undefined4 *)(param_2 + 0x20) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_2 + 0x24) = uVar2;
  *(undefined4 *)(param_2 + 0x28) = uVar3;
  *(undefined4 *)(param_2 + 0x2c) = uVar4;
  uVar2 = *(undefined4 *)(param_1 + 0x34);
  uVar3 = *(undefined4 *)(param_1 + 0x38);
  uVar4 = *(undefined4 *)(param_1 + 0x3c);
  *(undefined4 *)(param_2 + 0x30) = *(undefined4 *)(param_1 + 0x30);
  *(undefined4 *)(param_2 + 0x34) = uVar2;
  *(undefined4 *)(param_2 + 0x38) = uVar3;
  *(undefined4 *)(param_2 + 0x3c) = uVar4;
  if (*(float *)(this + 4) != 0.0) {
    fVar1 = 1.5707964;
    fVar6 = 1.0;
    fVar5 = (float)Sin(*(float *)(this + 4) * 1.5707964);
    fVar5 = fVar5 + fVar6;
    fVar1 = (float)Sin(*(float *)(this + 4) * fVar1);
    fVar6 = fVar6 - fVar1;
    *(float *)param_2 = *(float *)param_2 * fVar5;
    *(float *)(param_2 + 4) = *(float *)(param_2 + 4) * fVar5;
    *(float *)(param_2 + 8) = *(float *)(param_2 + 8) * fVar5;
    *(float *)(param_2 + 0x10) = *(float *)(param_2 + 0x10) * fVar6;
    *(float *)(param_2 + 0x14) = *(float *)(param_2 + 0x14) * fVar6;
    *(float *)(param_2 + 0x18) = *(float *)(param_2 + 0x18) * fVar6;
  }
  if (*(float *)(this + 8) != 0.0) {
    fVar7 = 1.5707964;
    fVar6 = 1.0;
    fVar5 = fVar6;
    fVar1 = (float)Sin(*(float *)(this + 8) * 1.5707964);
    fVar6 = fVar6 + fVar1 * 0.1;
    fVar1 = (float)Sin(*(float *)(this + 8) * fVar7);
    fVar5 = fVar5 - fVar1;
    *(float *)param_2 = *(float *)param_2 * fVar6;
    *(float *)(param_2 + 4) = *(float *)(param_2 + 4) * fVar6;
    *(float *)(param_2 + 8) = *(float *)(param_2 + 8) * fVar6;
    *(float *)(param_2 + 0x10) = *(float *)(param_2 + 0x10) * fVar6;
    *(float *)(param_2 + 0x14) = *(float *)(param_2 + 0x14) * fVar6;
    *(float *)(param_2 + 0x18) = *(float *)(param_2 + 0x18) * fVar6;
    *(float *)(param_2 + 0x20) = *(float *)(param_2 + 0x20) * fVar5;
    *(float *)(param_2 + 0x24) = *(float *)(param_2 + 0x24) * fVar5;
    *(float *)(param_2 + 0x28) = *(float *)(param_2 + 0x28) * fVar5;
  }
  return;
}
