/*
 * mangled: _ZN7tMatrix7SetZDirERK7tVector
 * demangled: tMatrix::SetZDir(tVector const&)
 * address: 0000b40c
 * size: 308
 */

/* tMatrix::SetZDir(tVector const&) */

void __thiscall tMatrix::SetZDir(tMatrix *this,tVector *param_1)

{
  int iVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;

  fVar4 = *(float *)(param_1 + 4);
  fVar5 = *(float *)param_1;
  fVar3 = *(float *)(param_1 + 8);
  fVar6 = SQRT(fVar4 * fVar4 + fVar5 * fVar5 + fVar3 * fVar3);
  if (fVar6 != 0.0) {
    fVar2 = 1.0;
    fVar6 = 1.0 / fVar6;
    fVar5 = fVar6 * fVar5;
    fVar4 = fVar6 * fVar4;
    fVar6 = fVar6 * fVar3;
    *(float *)(this + 0x20) = fVar5;
    *(float *)(this + 0x24) = fVar4;
    *(float *)(this + 0x28) = fVar6;
    if ((fVar5 == 0.0) && (fVar6 == 0.0)) {
      fVar8 = 0.0;
      fVar3 = fVar2;
    }
    else {
      fVar8 = -fVar5;
      fVar2 = fVar6 * fVar6 + 0.0 + fVar5 * fVar5;
      fVar3 = fVar6;
    }
    if (SQRT(fVar2) == 0.0) {
      fVar2 = 0.0;
    }
    else {
      fVar7 = 1.0 / SQRT(fVar2);
      fVar3 = fVar3 * fVar7;
      fVar2 = fVar7 * 0.0;
      fVar8 = fVar8 * fVar7;
    }
    *(float *)this = fVar3;
    *(float *)(this + 4) = fVar2;
    *(float *)(this + 8) = fVar8;
    if ((tVector::Cross(tVector_const&,tVector_const&)::T == '\0') &&
       (iVar1 = ___cxa_guard_acquire(&tVector::Cross(tVector_const&,tVector_const&)::T), iVar1 != 0)
       ) {
      ___cxa_guard_release(&tVector::Cross(tVector_const&,tVector_const&)::T);
    }
    tVector::Cross(tVector_const&,tVector_const&)::T = fVar4 * fVar8 - fVar6 * fVar2;
    fVar6 = fVar6 * fVar3 - fVar5 * fVar8;
    fVar3 = fVar5 * fVar2 - fVar4 * fVar3;
    DAT_004e6928 = fVar6;
    DAT_004e692c = fVar3;
    *(float *)(this + 0x10) = tVector::Cross(tVector_const&,tVector_const&)::T;
    *(float *)(this + 0x14) = fVar6;
    *(float *)(this + 0x18) = fVar3;
  }
  return;
}
