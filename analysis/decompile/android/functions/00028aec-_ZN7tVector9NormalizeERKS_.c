/*
 * mangled: _ZN7tVector9NormalizeERKS_
 * demangled: tVector::Normalize(tVector const&)
 * address: 00028aec
 * size: 20
 */

/* tVector::Normalize(tVector const&) */

void __thiscall tVector::Normalize(tVector *this,tVector *param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;

  uVar1 = *(undefined4 *)(param_1 + 4);
  uVar2 = *(undefined4 *)(param_1 + 8);
  *(undefined4 *)this = *(undefined4 *)param_1;
  *(undefined4 *)(this + 4) = uVar1;
  *(undefined4 *)(this + 8) = uVar2;
  Normalize(this);
  return;
}
