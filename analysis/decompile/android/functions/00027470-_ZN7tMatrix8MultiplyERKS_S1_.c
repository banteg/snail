/*
 * mangled: _ZN7tMatrix8MultiplyERKS_S1_
 * demangled: tMatrix::Multiply(tMatrix const&, tMatrix const&)
 * address: 00027470
 * size: 380
 */

/* tMatrix::Multiply(tMatrix const&, tMatrix const&) */

void __thiscall tMatrix::Multiply(tMatrix *this,tMatrix *param_1,tMatrix *param_2)

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
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;

  fVar9 = *(float *)(param_2 + 0x10);
  fVar15 = *(float *)(param_1 + 4);
  fVar6 = *(float *)(param_1 + 8);
  fVar12 = *(float *)(param_2 + 0x20);
  fVar14 = *(float *)(param_2 + 0x14);
  fVar4 = *(float *)(param_1 + 0x14);
  fVar18 = *(float *)(param_2 + 4);
  fVar3 = *(float *)(param_1 + 0x10);
  fVar13 = *(float *)(param_2 + 0x24);
  fVar7 = *(float *)(param_1 + 0x18);
  fVar1 = *(float *)(param_2 + 0x18);
  fVar17 = *(float *)(param_2 + 8);
  fVar2 = *(float *)(param_1 + 0x24);
  fVar11 = *(float *)(param_2 + 0x28);
  fVar16 = *(float *)(param_1 + 0x20);
  fVar10 = *(float *)(param_1 + 0x28);
  *(float *)this = fVar15 * fVar9 + *(float *)param_1 * *(float *)param_2 + fVar6 * fVar12;
  fVar5 = *(float *)param_1;
  fVar8 = *(float *)param_2;
  *(float *)(this + 4) = fVar15 * fVar14 + fVar5 * fVar18 + fVar6 * fVar13;
  fVar18 = *(float *)(param_1 + 4);
  fVar15 = *(float *)(param_2 + 4);
  *(float *)(this + 0x10) = fVar4 * fVar9 + fVar3 * fVar8 + fVar7 * fVar12;
  fVar9 = *(float *)(param_1 + 0x10);
  fVar3 = *(float *)(param_2 + 0x10);
  *(float *)(this + 0x14) = fVar4 * fVar14 + fVar9 * fVar15 + fVar7 * fVar13;
  fVar4 = *(float *)(param_1 + 0x14);
  fVar14 = *(float *)(param_2 + 0x14);
  *(float *)(this + 8) = fVar18 * fVar1 + fVar5 * fVar17 + fVar6 * fVar11;
  fVar18 = *(float *)(param_2 + 8);
  *(float *)(this + 0x20) = fVar2 * fVar3 + fVar16 * fVar8 + fVar10 * fVar12;
  fVar5 = *(float *)(param_1 + 0x34);
  fVar6 = *(float *)(param_1 + 0x20);
  fVar17 = *(float *)(param_1 + 0x30);
  fVar12 = *(float *)(param_2 + 0x20);
  fVar16 = *(float *)(param_2 + 0x30);
  *(float *)(this + 0x18) = fVar4 * fVar1 + fVar9 * fVar18 + fVar7 * fVar11;
  fVar9 = *(float *)(param_2 + 0x18);
  fVar4 = *(float *)(param_2 + 0x38);
  fVar7 = *(float *)(param_1 + 0x38);
  *(float *)(this + 0x24) = fVar2 * fVar14 + fVar6 * fVar15 + fVar10 * fVar13;
  fVar1 = *(float *)(param_2 + 0x24);
  fVar2 = *(float *)(param_1 + 0x24);
  fVar13 = *(float *)(param_2 + 0x34);
  *(float *)(this + 0x30) = fVar5 * fVar3 + fVar17 * fVar8 + fVar7 * fVar12 + fVar16;
  fVar3 = *(float *)(param_1 + 0x30);
  *(float *)(this + 0x34) = fVar5 * fVar14 + fVar3 * fVar15 + fVar7 * fVar1 + fVar13;
  fVar1 = *(float *)(param_1 + 0x34);
  *(float *)(this + 0x28) = fVar2 * fVar9 + fVar6 * fVar18 + fVar10 * fVar11;
  *(float *)(this + 0x38) =
       fVar1 * fVar9 + fVar3 * fVar18 + fVar7 * *(float *)(param_2 + 0x28) + fVar4;
  return;
}
