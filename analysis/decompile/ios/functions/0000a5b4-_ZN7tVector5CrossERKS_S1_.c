/*
 * mangled: _ZN7tVector5CrossERKS_S1_
 * demangled: tVector::Cross(tVector const&, tVector const&)
 * address: 0000a5b4
 * size: 148
 */

/* tVector::Cross(tVector const&, tVector const&) */

void __thiscall tVector::Cross(tVector *this,tVector *param_1,tVector *param_2)

{
  int iVar1;
  float fVar2;
  float fVar3;

  if ((Cross(tVector_const&,tVector_const&)::T == '\0') &&
     (iVar1 = ___cxa_guard_acquire(&Cross(tVector_const&,tVector_const&)::T), iVar1 != 0)) {
    ___cxa_guard_release(&Cross(tVector_const&,tVector_const&)::T);
  }
  Cross(tVector_const&,tVector_const&)::T =
       *(float *)(param_1 + 4) * *(float *)(param_2 + 8) -
       *(float *)(param_1 + 8) * *(float *)(param_2 + 4);
  fVar2 = *(float *)(param_1 + 8) * *(float *)param_2 - *(float *)(param_2 + 8) * *(float *)param_1;
  fVar3 = *(float *)(param_2 + 4) * *(float *)param_1 - *(float *)(param_1 + 4) * *(float *)param_2;
  DAT_004e6928 = fVar2;
  DAT_004e692c = fVar3;
  *(float *)this = Cross(tVector_const&,tVector_const&)::T;
  *(float *)(this + 4) = fVar2;
  *(float *)(this + 8) = fVar3;
  return;
}
