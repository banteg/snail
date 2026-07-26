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
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;

  iVar1 = DAT_00028308;
  iVar5 = DAT_00028304 + 0x2827c;
  iVar6 = iVar5 + DAT_00028308;
  if (((*(uint *)(iVar5 + DAT_00028308) & 1) == 0) &&
     (iVar2 = __cxa_guard_acquire(iVar6), iVar2 != 0)) {
    __cxa_guard_release(iVar6);
  }
  fVar7 = *(float *)(param_1 + 8);
  fVar8 = *(float *)(param_2 + 8);
  iVar5 = iVar5 + iVar1;
  *(float *)(iVar5 + 4) = *(float *)(param_1 + 4) * fVar8 - fVar7 * *(float *)(param_2 + 4);
  fVar10 = *(float *)param_1;
  fVar9 = *(float *)param_2;
  *(float *)(iVar5 + 8) = fVar7 * fVar9 - fVar10 * fVar8;
  *(float *)(iVar5 + 0xc) = fVar10 * *(float *)(param_2 + 4) - *(float *)(param_1 + 4) * fVar9;
  uVar3 = *(undefined4 *)(iVar5 + 8);
  uVar4 = *(undefined4 *)(iVar5 + 0xc);
  *(undefined4 *)this = *(undefined4 *)(iVar5 + 4);
  *(undefined4 *)(this + 4) = uVar3;
  *(undefined4 *)(this + 8) = uVar4;
  return;
}
