/*
 * mangled: _ZN7tVector3DotERKS_
 * demangled: tVector::Dot(tVector const&)
 * address: 00009f58
 * size: 44
 */

/* tVector::Dot(tVector const&) */

float __thiscall tVector::Dot(tVector *this,tVector *param_1)

{
  return *(float *)(this + 4) * *(float *)(param_1 + 4) + *(float *)this * *(float *)param_1 +
         *(float *)(this + 8) * *(float *)(param_1 + 8);
}
