/*
 * mangled: _ZN7tMatrix13OrthoganalizeEv
 * demangled: tMatrix::Orthoganalize()
 * address: 0000b0cc
 * size: 472
 */

/* tMatrix::Orthoganalize() */

void __thiscall tMatrix::Orthoganalize(tMatrix *this)

{
  int iVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;

  fVar3 = *(float *)(this + 4);
  fVar4 = *(float *)this;
  fVar2 = *(float *)(this + 8);
  fVar5 = SQRT(fVar3 * fVar3 + fVar4 * fVar4 + fVar2 * fVar2);
  if (fVar5 != 0.0) {
    fVar5 = 1.0 / fVar5;
    *(float *)this = fVar4 * fVar5;
    *(float *)(this + 4) = fVar3 * fVar5;
    *(float *)(this + 8) = fVar2 * fVar5;
  }
  fVar3 = *(float *)(this + 0x14);
  fVar4 = *(float *)(this + 0x10);
  fVar2 = *(float *)(this + 0x18);
  fVar5 = SQRT(fVar3 * fVar3 + fVar4 * fVar4 + fVar2 * fVar2);
  if (fVar5 != 0.0) {
    fVar5 = 1.0 / fVar5;
    *(float *)(this + 0x10) = fVar4 * fVar5;
    *(float *)(this + 0x14) = fVar3 * fVar5;
    *(float *)(this + 0x18) = fVar2 * fVar5;
  }
  fVar3 = *(float *)(this + 0x24);
  fVar4 = *(float *)(this + 0x20);
  fVar2 = *(float *)(this + 0x28);
  fVar5 = SQRT(fVar3 * fVar3 + fVar4 * fVar4 + fVar2 * fVar2);
  if (fVar5 != 0.0) {
    fVar5 = 1.0 / fVar5;
    *(float *)(this + 0x20) = fVar4 * fVar5;
    *(float *)(this + 0x24) = fVar3 * fVar5;
    *(float *)(this + 0x28) = fVar2 * fVar5;
  }
  if ((tVector::Cross(tVector_const&,tVector_const&)::T == '\0') &&
     (iVar1 = ___cxa_guard_acquire(&tVector::Cross(tVector_const&,tVector_const&)::T), iVar1 != 0))
  {
    ___cxa_guard_release(&tVector::Cross(tVector_const&,tVector_const&)::T);
  }
  tVector::Cross(tVector_const&,tVector_const&)::T =
       *(float *)(this + 0x14) * *(float *)(this + 0x28) -
       *(float *)(this + 0x18) * *(float *)(this + 0x24);
  fVar3 = *(float *)(this + 0x10);
  fVar2 = *(float *)(this + 0x20);
  fVar4 = *(float *)(this + 0x18) * fVar2 - *(float *)(this + 0x28) * fVar3;
  fVar2 = *(float *)(this + 0x24) * fVar3 - *(float *)(this + 0x14) * fVar2;
  DAT_004e6928 = fVar4;
  DAT_004e692c = fVar2;
  *(float *)this = tVector::Cross(tVector_const&,tVector_const&)::T;
  *(float *)(this + 4) = fVar4;
  *(float *)(this + 8) = fVar2;
  if ((tVector::Cross(tVector_const&,tVector_const&)::T == '\0') &&
     (iVar1 = ___cxa_guard_acquire(&tVector::Cross(tVector_const&,tVector_const&)::T), iVar1 != 0))
  {
    ___cxa_guard_release(&tVector::Cross(tVector_const&,tVector_const&)::T);
  }
  tVector::Cross(tVector_const&,tVector_const&)::T =
       *(float *)(this + 4) * *(float *)(this + 0x18) -
       *(float *)(this + 8) * *(float *)(this + 0x14);
  fVar2 = *(float *)(this + 0x10);
  fVar3 = *(float *)(this + 8) * fVar2 - *(float *)(this + 0x18) * *(float *)this;
  fVar2 = *(float *)(this + 0x14) * *(float *)this - *(float *)(this + 4) * fVar2;
  DAT_004e6928 = fVar3;
  DAT_004e692c = fVar2;
  *(float *)(this + 0x20) = tVector::Cross(tVector_const&,tVector_const&)::T;
  *(float *)(this + 0x24) = fVar3;
  *(float *)(this + 0x28) = fVar2;
  return;
}
