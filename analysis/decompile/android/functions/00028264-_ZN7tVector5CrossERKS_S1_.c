/*
 * mangled: _ZN7tVector5CrossERKS_S1_
 * demangled: tVector::Cross(tVector const&, tVector const&)
 * address: 00028264
 * size: 160
 */

/* tVector::Cross(tVector const&, tVector const&) */

void __thiscall tVector::Cross(tVector *this,tVector *param_1,tVector *param_2)

{
  int iVar1;
  float fVar2;
  float fVar3;

  if (((Cross(tVector_const&,tVector_const&)::T & 1) == 0) &&
     (iVar1 = __cxa_guard_acquire(&Cross(tVector_const&,tVector_const&)::T), iVar1 != 0)) {
    __cxa_guard_release(&Cross(tVector_const&,tVector_const&)::T);
  }
  Cross(tVector_const&,tVector_const&)::T._0_4_ =
       *(float *)(param_1 + 4) * *(float *)(param_2 + 8) -
       *(float *)(param_1 + 8) * *(float *)(param_2 + 4);
  fVar2 = *(float *)(param_1 + 8) * *(float *)param_2 - *(float *)param_1 * *(float *)(param_2 + 8);
  fVar3 = *(float *)param_1 * *(float *)(param_2 + 4) - *(float *)(param_1 + 4) * *(float *)param_2;
  Cross(tVector_const&,tVector_const&)::T._4_4_ = fVar2;
  Cross(tVector_const&,tVector_const&)::T._8_4_ = fVar3;
  *(undefined4 *)this = Cross(tVector_const&,tVector_const&)::T._0_4_;
  *(float *)(this + 4) = fVar2;
  *(float *)(this + 8) = fVar3;
  return;
}
