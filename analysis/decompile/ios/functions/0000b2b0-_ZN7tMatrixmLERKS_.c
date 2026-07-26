/*
 * mangled: _ZN7tMatrixmLERKS_
 * demangled: tMatrix::operator*=(tMatrix const&)
 * address: 0000b2b0
 * size: 348
 */

/* tMatrix::TEMPNAMEPLACEHOLDERVALUE(tMatrix const&) */

void __thiscall tMatrix::operator*=(tMatrix *this,tMatrix *param_1)

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
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;

  fVar16 = *(float *)(this + 4);
  fVar20 = *(float *)(param_1 + 0x10);
  fVar18 = *(float *)this;
  fVar10 = *(float *)(this + 8);
  fVar6 = *(float *)(param_1 + 0x20);
  fVar1 = *(float *)(param_1 + 0x14);
  fVar7 = *(float *)(param_1 + 0x24);
  fVar2 = *(float *)(param_1 + 0x18);
  fVar11 = *(float *)(this + 0x14);
  fVar12 = *(float *)(this + 0x10);
  fVar3 = *(float *)(this + 0x18);
  fVar13 = *(float *)(param_1 + 4);
  fVar8 = *(float *)(this + 0x24);
  fVar9 = *(float *)(this + 0x20);
  fVar21 = *(float *)(this + 0x28);
  fVar22 = *(float *)(this + 0x38);
  fVar4 = *(float *)(this + 0x34);
  fVar5 = *(float *)(this + 0x30);
  *(float *)this = fVar16 * fVar20 + fVar18 * *(float *)param_1 + fVar10 * fVar6;
  fVar14 = *(float *)(param_1 + 8);
  *(float *)(this + 4) = fVar16 * fVar1 + fVar18 * fVar13 + fVar10 * fVar7;
  fVar17 = *(float *)param_1;
  fVar19 = *(float *)(param_1 + 0x28);
  fVar15 = *(float *)(param_1 + 4);
  *(float *)(this + 8) = fVar16 * fVar2 + fVar18 * fVar14 + fVar10 * fVar19;
  fVar10 = *(float *)(param_1 + 8);
  *(float *)(this + 0x10) = fVar11 * fVar20 + fVar12 * fVar17 + fVar3 * fVar6;
  *(float *)(this + 0x14) = fVar11 * fVar1 + fVar12 * fVar15 + fVar3 * fVar7;
  fVar13 = *(float *)(param_1 + 0x14);
  fVar14 = *(float *)(param_1 + 0x10);
  *(float *)(this + 0x18) = fVar11 * fVar2 + fVar12 * fVar10 + fVar3 * fVar19;
  *(float *)(this + 0x20) = fVar8 * fVar14 + fVar9 * fVar17 + fVar21 * fVar6;
  *(float *)(this + 0x24) = fVar8 * fVar13 + fVar9 * fVar15 + fVar21 * fVar7;
  fVar1 = *(float *)(param_1 + 0x18);
  fVar2 = *(float *)(param_1 + 0x20);
  *(float *)(this + 0x28) = fVar8 * fVar1 + fVar9 * fVar10 + fVar21 * fVar19;
  fVar3 = *(float *)(param_1 + 0x24);
  *(float *)(this + 0x30) =
       fVar4 * fVar14 + fVar5 * fVar17 + fVar22 * fVar2 + *(float *)(param_1 + 0x30);
  fVar2 = *(float *)(param_1 + 0x28);
  *(float *)(this + 0x34) =
       fVar4 * fVar13 + fVar5 * fVar15 + fVar22 * fVar3 + *(float *)(param_1 + 0x34);
  *(float *)(this + 0x38) =
       fVar4 * fVar1 + fVar5 * fVar10 + fVar22 * fVar2 + *(float *)(param_1 + 0x38);
  return;
}
