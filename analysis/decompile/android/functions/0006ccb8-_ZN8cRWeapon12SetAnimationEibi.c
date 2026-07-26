/*
 * mangled: _ZN8cRWeapon12SetAnimationEibi
 * demangled: cRWeapon::SetAnimation(int, bool, int)
 * address: 0006ccb8
 * size: 184
 */

/* cRWeapon::SetAnimation(int, bool, int) */

void __thiscall cRWeapon::SetAnimation(cRWeapon *this,int param_1,bool param_2,int param_3)

{
  ushort *puVar1;
  int iVar2;
  bool bVar3;
  float fVar4;
  float fVar5;

  if (!param_2) {
    iVar2 = *(int *)(this + 0x138);
    *(int *)(this + 0x138) = iVar2 + 1;
    *(int *)(this + iVar2 * 4 + 0x110) = param_1;
    return;
  }
  bVar3 = param_3 != -1;
  if (bVar3) {
    param_3 = param_3 & 0xffff;
  }
  puVar1 = *(ushort **)(*(int *)(this + param_1 * 0x74 + 0x168) + 0x104);
  if (bVar3) {
    *puVar1 = (ushort)param_3;
  }
  else {
    param_3 = (int)*puVar1;
  }
  *(ushort **)(this + 0x108) = puVar1;
  if ((param_3 & 8U) == 0) {
    *(undefined4 *)(this + 0x100) = DAT_0006cd70;
    fVar5 = *(float *)(puVar1 + 10);
    if (fVar5 < 0.0) {
      fVar5 = -fVar5;
    }
    *(float *)(this + 0x104) = fVar5;
  }
  else {
    fVar5 = *(float *)(puVar1 + 10);
    if (0.0 <= fVar5) {
      fVar5 = -fVar5;
    }
    fVar4 = fVar5 + DAT_0006cd74;
    *(float *)(this + 0x104) = fVar5;
    *(float *)(this + 0x100) = fVar4;
  }
  *(undefined4 *)(this + 0x138) = 0;
  *(uint *)(*(int *)(this + 0x13c) + 4) = *(uint *)(*(int *)(this + 0x13c) + 4) | 0x20;
  *(undefined4 *)(this + 0x24) = *(undefined4 *)(this + param_1 * 0x74 + 0x168);
  return;
}
