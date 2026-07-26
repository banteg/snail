/*
 * mangled: _ZN7tVectorC2EPf
 * demangled: tVector::tVector(float*)
 * address: 00026948
 * size: 28
 */

/* tVector::tVector(float*) */

void __thiscall tVector::tVector(tVector *this,float *param_1)

{
  *(float *)this = *param_1;
  *(float *)(this + 4) = param_1[1];
  *(float *)(this + 8) = param_1[2];
  return;
}
