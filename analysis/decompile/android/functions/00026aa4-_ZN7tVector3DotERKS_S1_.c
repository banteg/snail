/*
 * mangled: _ZN7tVector3DotERKS_S1_
 * demangled: tVector::Dot(tVector const&, tVector const&)
 * address: 00026aa4
 * size: 44
 */

/* tVector::Dot(tVector const&, tVector const&) */

float __thiscall tVector::Dot(tVector *this,tVector *param_1,tVector *param_2)

{
  return *(float *)(param_1 + 4) * *(float *)(param_2 + 4) + *(float *)param_1 * *(float *)param_2 +
         *(float *)(param_1 + 8) * *(float *)(param_2 + 8);
}
