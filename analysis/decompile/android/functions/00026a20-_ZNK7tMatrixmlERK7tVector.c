/*
 * mangled: _ZNK7tMatrixmlERK7tVector
 * demangled: tMatrix::operator*(tVector const&) const
 * address: 00026a20
 * size: 132
 */

/* tMatrix::TEMPNAMEPLACEHOLDERVALUE(tVector const&) const */

void __thiscall tMatrix::operator*(tMatrix *this,tVector *param_1)

{
  float *in_r2;
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;

  fVar4 = in_r2[1];
  fVar6 = in_r2[2];
  fVar8 = *(float *)(param_1 + 0x14);
  fVar1 = *(float *)(param_1 + 0x18);
  fVar9 = *(float *)(param_1 + 0x34);
  fVar2 = *(float *)(param_1 + 0x28);
  fVar3 = *(float *)(param_1 + 0x38);
  *(float *)this =
       fVar4 * *(float *)(param_1 + 4) + *in_r2 * *(float *)param_1 +
       fVar6 * *(float *)(param_1 + 8) + *(float *)(param_1 + 0x30);
  fVar7 = *in_r2;
  fVar5 = *(float *)(param_1 + 0x20);
  *(float *)(this + 4) = fVar4 * fVar8 + fVar7 * *(float *)(param_1 + 0x10) + fVar6 * fVar1 + fVar9;
  *(float *)(this + 8) =
       in_r2[1] * *(float *)(param_1 + 0x24) + fVar7 * fVar5 + fVar6 * fVar2 + fVar3;
  return;
}
