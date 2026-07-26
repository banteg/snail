/*
 * mangled: _ZN12cRInvincible5StartEv
 * demangled: cRInvincible::Start()
 * address: 0006d1fc
 * size: 104
 */

/* cRInvincible::Start() */

void __thiscall cRInvincible::Start(cRInvincible *this)

{
  undefined4 uVar1;
  int iVar2;
  int *piVar3;
  int iVar4;

  iVar4 = DAT_0006d270;
  uVar1 = DAT_0006d264;
  iVar2 = DAT_0006d26c + 0x6d210;
  if (*(int *)(this + 0x74) != 0) {
    if (*(int *)(this + 0x74) == 3) {
      *(undefined4 *)(this + 0x74) = 1;
    }
    return;
  }
  *(undefined4 *)(this + 0x80) = DAT_0006d264;
  *(undefined4 *)(this + 0x78) = uVar1;
  piVar3 = *(int **)(iVar2 + iVar4);
  *(undefined4 *)(this + 0x74) = 1;
  uVar1 = DAT_0006d268;
  *(undefined4 *)(this + 0x84) = DAT_0006d268;
  *(undefined4 *)(this + 0x7c) = uVar1;
  iVar4 = *piVar3;
  *(uint *)(iVar4 + 0x85240) = *(uint *)(iVar4 + 0x85240) | 0x20;
  return;
}
