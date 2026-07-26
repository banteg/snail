/*
 * mangled: _ZN7tMatrix17LinearInterpolateERKS_S1_f
 * demangled: tMatrix::LinearInterpolate(tMatrix const&, tMatrix const&, float)
 * address: 0000b808
 * size: 932
 */

/* tMatrix::LinearInterpolate(tMatrix const&, tMatrix const&, float) */

void __thiscall
tMatrix::LinearInterpolate(tMatrix *this,tMatrix *param_1,tMatrix *param_2,float param_3)

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

  fVar6 = *(float *)(param_1 + 0x34);
  fVar17 = *(float *)(param_1 + 4);
  fVar4 = *(float *)param_1;
  fVar12 = *(float *)(param_1 + 0x30);
  fVar9 = *(float *)(param_1 + 0x38);
  fVar3 = *(float *)(param_1 + 0x14);
  fVar8 = *(float *)(param_1 + 0x10);
  fVar5 = *(float *)(param_1 + 0x24);
  fVar1 = *(float *)(param_1 + 0x28);
  *(float *)this = fVar4;
  *(float *)(this + 4) = fVar8;
  fVar22 = 1.0;
  fVar13 = *(float *)(param_1 + 8);
  *(float *)(this + 0x14) = fVar3;
  *(float *)(this + 0x28) = fVar1;
  *(undefined4 *)(this + 0x2c) = 0;
  *(undefined4 *)(this + 0x1c) = 0;
  fVar14 = *(float *)(param_1 + 0x18);
  *(float *)(this + 0x18) = fVar5;
  *(undefined4 *)(this + 0xc) = 0;
  *(undefined4 *)(this + 0x3c) = 0x3f800000;
  fVar12 = -(fVar17 * fVar6 + fVar4 * fVar12 + fVar13 * fVar9);
  fVar7 = *(float *)(param_1 + 4);
  *(float *)(this + 0x30) = fVar12;
  *(float *)(this + 0x10) = fVar7;
  fVar17 = *(float *)(param_1 + 0x30);
  fVar21 = *(float *)(param_2 + 0x10);
  fVar15 = *(float *)(param_1 + 0x20);
  *(float *)(this + 8) = fVar15;
  fVar6 = -(fVar3 * fVar6 + fVar8 * fVar17 + fVar14 * fVar9);
  fVar14 = *(float *)(param_1 + 8);
  *(float *)(this + 0x34) = fVar6;
  *(float *)(this + 0x20) = fVar14;
  fVar18 = *(float *)(param_1 + 0x34);
  fVar13 = *(float *)(param_2 + 0x20);
  fVar2 = *(float *)(param_1 + 0x18);
  *(float *)(this + 0x24) = fVar2;
  fVar10 = *(float *)param_2;
  fVar17 = -(fVar5 * fVar18 + fVar15 * fVar17 + fVar1 * fVar9);
  *(float *)(this + 0x38) = fVar17;
  *(float *)this = fVar8 * fVar21 + fVar4 * fVar10 + fVar15 * fVar13;
  fVar20 = *(float *)(param_2 + 0x14);
  fVar9 = *(float *)(param_2 + 0x24);
  fVar19 = *(float *)(param_2 + 0x18);
  fVar10 = *(float *)(param_2 + 8);
  *(float *)(this + 4) = fVar8 * fVar20 + fVar4 * *(float *)(param_2 + 4) + fVar15 * fVar9;
  fVar18 = *(float *)(param_2 + 4);
  fVar11 = *(float *)(param_2 + 0x28);
  fVar16 = *(float *)param_2;
  *(float *)(this + 8) = fVar8 * fVar19 + fVar4 * fVar10 + fVar15 * fVar11;
  fVar4 = *(float *)(param_2 + 8);
  *(float *)(this + 0x10) = fVar3 * fVar21 + fVar7 * fVar16 + fVar5 * fVar13;
  *(float *)(this + 0x14) = fVar3 * fVar20 + fVar7 * fVar18 + fVar5 * fVar9;
  fVar10 = *(float *)(param_2 + 0x10);
  fVar8 = *(float *)(param_2 + 0x14);
  *(float *)(this + 0x18) = fVar3 * fVar19 + fVar7 * fVar4 + fVar5 * fVar11;
  fVar3 = *(float *)(param_2 + 0x18);
  *(float *)(this + 0x20) = fVar2 * fVar10 + fVar14 * fVar16 + fVar1 * fVar13;
  *(float *)(this + 0x24) = fVar2 * fVar8 + fVar14 * fVar18 + fVar1 * fVar9;
  *(float *)(this + 0x28) = fVar2 * fVar3 + fVar14 * fVar4 + fVar1 * fVar11;
  fVar13 = *(float *)(param_2 + 0x24);
  *(float *)(this + 0x30) =
       fVar6 * fVar10 + fVar12 * fVar16 + fVar17 * *(float *)(param_2 + 0x20) +
       *(float *)(param_2 + 0x30);
  fVar9 = *(float *)(param_2 + 0x28);
  *(float *)(this + 0x34) =
       fVar6 * fVar8 + fVar12 * fVar18 + fVar17 * fVar13 + *(float *)(param_2 + 0x34);
  *(float *)(this + 0x38) =
       fVar6 * fVar3 + fVar12 * fVar4 + fVar17 * fVar9 + *(float *)(param_2 + 0x38);
  Interpolate(this,param_3);
  fVar2 = *(float *)(this + 0x10);
  fVar5 = *(float *)(param_1 + 4);
  fVar3 = *(float *)this;
  fVar14 = *(float *)(this + 0x20);
  fVar9 = *(float *)(this + 0x14);
  fVar1 = *(float *)(this + 4);
  fVar13 = *(float *)(this + 0x24);
  fVar6 = *(float *)(this + 0x18);
  fVar17 = *(float *)(this + 8);
  fVar12 = *(float *)(this + 0x28);
  fVar7 = *(float *)(param_1 + 8);
  *(float *)this = fVar2 * fVar5 + fVar3 * *(float *)param_1 + fVar14 * fVar7;
  fVar8 = *(float *)(param_1 + 0x14);
  fVar4 = *(float *)param_1;
  *(float *)(this + 4) = fVar9 * fVar5 + fVar1 * fVar4 + fVar13 * fVar7;
  fVar5 = *(float *)(param_1 + 0x10);
  *(float *)(this + 8) = fVar6 * *(float *)(param_1 + 4) + fVar17 * fVar4 + fVar12 * fVar7;
  fVar7 = *(float *)(param_1 + 0x18);
  *(float *)(this + 0x10) = fVar2 * fVar8 + fVar3 * fVar5 + fVar14 * fVar7;
  fVar5 = *(float *)(param_1 + 0x24);
  fVar4 = *(float *)(param_1 + 0x10);
  *(float *)(this + 0x14) = fVar9 * fVar8 + fVar1 * fVar4 + fVar13 * fVar7;
  fVar8 = *(float *)(param_1 + 0x20);
  *(float *)(this + 0x18) = fVar6 * *(float *)(param_1 + 0x14) + fVar17 * fVar4 + fVar12 * fVar7;
  fVar7 = *(float *)(param_1 + 0x28);
  *(float *)(this + 0x20) = fVar2 * fVar5 + fVar3 * fVar8 + fVar14 * fVar7;
  fVar4 = *(float *)(param_1 + 0x20);
  *(float *)(this + 0x24) = fVar9 * fVar5 + fVar1 * fVar4 + fVar13 * fVar7;
  fVar5 = *(float *)(param_1 + 0x34);
  fVar8 = *(float *)(param_1 + 0x30);
  *(float *)(this + 0x28) = fVar6 * *(float *)(param_1 + 0x24) + fVar17 * fVar4 + fVar12 * fVar7;
  fVar4 = *(float *)(param_1 + 0x38);
  *(float *)(this + 0x30) = fVar2 * fVar5 + fVar3 * fVar8 + fVar14 * fVar4 + *(float *)(this + 0x30)
  ;
  fVar14 = *(float *)(param_1 + 0x30);
  *(float *)(this + 0x34) =
       fVar9 * fVar5 + fVar1 * fVar14 + fVar13 * fVar4 + *(float *)(this + 0x34);
  *(float *)(this + 0x38) =
       fVar6 * *(float *)(param_1 + 0x34) + fVar17 * fVar14 + fVar12 * fVar4 +
       *(float *)(this + 0x38);
  Orthoganalize(this);
  fVar22 = fVar22 - param_3;
  fVar12 = *(float *)(param_1 + 0x34);
  fVar13 = *(float *)(param_2 + 0x34);
  fVar17 = *(float *)(param_2 + 0x38);
  *(float *)(this + 0x30) =
       param_3 * *(float *)(param_2 + 0x30) + fVar22 * *(float *)(param_1 + 0x30);
  fVar6 = *(float *)(param_1 + 0x38);
  *(float *)(this + 0x34) = param_3 * fVar13 + fVar22 * fVar12;
  *(float *)(this + 0x38) = param_3 * fVar17 + fVar22 * fVar6;
  return;
}
