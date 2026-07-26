/*
 * mangled: _ZN7tVector6RotateERK7tMatrix
 * demangled: tVector::Rotate(tMatrix const&)
 * address: 00026c78
 * size: 100
 */

/* tVector::Rotate(tMatrix const&) */

void __thiscall tVector::Rotate(tVector *this,tMatrix *param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;

  fVar9 = *(float *)(this + 4);
  fVar8 = *(float *)(param_1 + 0x10);
  fVar1 = *(float *)(param_1 + 0x14);
  fVar6 = *(float *)this;
  fVar2 = *(float *)param_1;
  fVar3 = *(float *)(param_1 + 4);
  fVar7 = *(float *)(this + 8);
  fVar4 = *(float *)(param_1 + 0x20);
  fVar5 = *(float *)(param_1 + 0x24);
  *(float *)(this + 8) =
       fVar9 * *(float *)(param_1 + 0x18) + fVar6 * *(float *)(param_1 + 8) +
       fVar7 * *(float *)(param_1 + 0x28);
  *(float *)this = fVar9 * fVar8 + fVar6 * fVar2 + fVar7 * fVar4;
  *(float *)(this + 4) = fVar9 * fVar1 + fVar6 * fVar3 + fVar7 * fVar5;
  return;
}
