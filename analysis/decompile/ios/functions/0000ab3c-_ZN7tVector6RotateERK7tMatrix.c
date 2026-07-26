/*
 * mangled: _ZN7tVector6RotateERK7tMatrix
 * demangled: tVector::Rotate(tMatrix const&)
 * address: 0000ab3c
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

  fVar2 = *(float *)(this + 4);
  fVar3 = *(float *)this;
  fVar1 = *(float *)(this + 8);
  fVar4 = *(float *)(param_1 + 4);
  *(float *)this =
       fVar2 * *(float *)(param_1 + 0x10) + fVar3 * *(float *)param_1 +
       fVar1 * *(float *)(param_1 + 0x20);
  fVar5 = *(float *)(param_1 + 8);
  *(float *)(this + 4) =
       fVar2 * *(float *)(param_1 + 0x14) + fVar3 * fVar4 + fVar1 * *(float *)(param_1 + 0x24);
  *(float *)(this + 8) =
       fVar2 * *(float *)(param_1 + 0x18) + fVar3 * fVar5 + fVar1 * *(float *)(param_1 + 0x28);
  return;
}
