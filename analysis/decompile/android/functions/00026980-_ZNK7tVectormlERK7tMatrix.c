/*
 * mangled: _ZNK7tVectormlERK7tMatrix
 * demangled: tVector::operator*(tMatrix const&) const
 * address: 00026980
 * size: 160
 */

/* tVector::TEMPNAMEPLACEHOLDERVALUE(tMatrix const&) const */

tVector * __thiscall tVector::operator*(tVector *this,tMatrix *param_1)

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
  float fVar10;
  float fVar11;

  memmove(this,param_1,0xc);
  fVar7 = *(float *)(param_1 + 4);
  fVar8 = *(float *)(param_1 + 8);
  fVar10 = in_r2[5];
  fVar1 = in_r2[1];
  fVar2 = in_r2[9];
  fVar3 = in_r2[0xd];
  fVar11 = in_r2[6];
  fVar4 = in_r2[2];
  fVar5 = in_r2[10];
  fVar6 = in_r2[0xe];
  *(float *)this = fVar7 * in_r2[4] + *(float *)param_1 * *in_r2 + fVar8 * in_r2[8] + in_r2[0xc];
  fVar9 = *(float *)param_1;
  *(float *)(this + 4) = fVar7 * fVar10 + fVar9 * fVar1 + fVar8 * fVar2 + fVar3;
  *(float *)(this + 8) = *(float *)(param_1 + 4) * fVar11 + fVar9 * fVar4 + fVar8 * fVar5 + fVar6;
  return this;
}
