/*
 * mangled: _ZNK7tVectormlERK7tMatrix
 * demangled: tVector::operator*(tMatrix const&) const
 * address: 00009ebc
 * size: 156
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

  _memmove(this,param_1,0xc);
  fVar3 = *(float *)(param_1 + 4);
  fVar1 = *(float *)param_1;
  fVar2 = *(float *)(param_1 + 8);
  fVar4 = in_r2[1];
  *(float *)this = fVar3 * in_r2[4] + fVar1 * *in_r2 + fVar2 * in_r2[8] + in_r2[0xc];
  fVar5 = in_r2[2];
  *(float *)(this + 4) = fVar3 * in_r2[5] + fVar1 * fVar4 + fVar2 * in_r2[9] + in_r2[0xd];
  *(float *)(this + 8) = fVar3 * in_r2[6] + fVar1 * fVar5 + fVar2 * in_r2[10] + in_r2[0xe];
  return this;
}
