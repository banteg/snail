/*
 * mangled: _ZN15cRBorderManager4KillEP8cRBorder
 * demangled: cRBorderManager::Kill(cRBorder*)
 * address: 0005c2f4
 * size: 140
 */

/* cRBorderManager::Kill(cRBorder*) */

void __thiscall cRBorderManager::Kill(cRBorderManager *this,cRBorder *param_1)

{
  uint uVar1;

  if (param_1 == (cRBorder *)0x0) {
    return;
  }
  uVar1 = *(uint *)(param_1 + 0x194);
  if (uVar1 == 0) {
    return;
  }
  if ((uVar1 & 0x400) != 0) {
    return;
  }
  *(uint *)(param_1 + 0x194) = uVar1 & 0xffffff09 | 0x200;
  if ((uVar1 & 0x100000) == 0) {
    return;
  }
  do {
    Kill(this,*(cRBorder **)(param_1 + 0x710));
    Kill(this,*(cRBorder **)(param_1 + 0x714));
    param_1 = *(cRBorder **)(param_1 + 0x718);
    if (param_1 == (cRBorder *)0x0) {
      return;
    }
    uVar1 = *(uint *)(param_1 + 0x194);
    if (uVar1 == 0) {
      return;
    }
    if ((uVar1 & 0x400) != 0) {
      return;
    }
    *(uint *)(param_1 + 0x194) = uVar1 & 0xffffff09 | 0x200;
  } while ((uVar1 & 0x100000) != 0);
  return;
}
