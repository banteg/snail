/*
 * mangled: _ZN15cRBorderManager4KillEP8cRBorder
 * demangled: cRBorderManager::Kill(cRBorder*)
 * address: 0003b104
 * size: 684
 */

/* cRBorderManager::Kill(cRBorder*) */

void cRBorderManager::Kill(cRBorder *param_1)

{
  int in_r1;
  uint in_r3;
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;

  if (in_r1 != 0) {
    in_r3 = *(uint *)(in_r1 + 0x194);
  }
  if (in_r1 == 0 || in_r3 == 0) {
    return;
  }
  if ((in_r3 & 0x400) != 0) {
    return;
  }
  uVar1 = in_r3 & 0xffffff09 | 0x200;
  *(uint *)(in_r1 + 0x194) = uVar1;
  if ((in_r3 & 0x100000) == 0) {
    return;
  }
  while( true ) {
    iVar3 = *(int *)(in_r1 + 0x710);
    if (iVar3 != 0) {
      uVar1 = *(uint *)(iVar3 + 0x194);
    }
    uVar2 = uVar1;
    if ((iVar3 != 0 && uVar1 != 0) && ((uVar1 & 0x400) == 0)) {
      uVar2 = uVar1 & 0xffffff09 | 0x200;
      *(uint *)(iVar3 + 0x194) = uVar2;
      if ((uVar1 & 0x100000) != 0) {
        Kill(param_1);
        Kill(param_1);
        Kill(param_1);
      }
    }
    iVar3 = *(int *)(in_r1 + 0x714);
    if (iVar3 != 0) {
      uVar2 = *(uint *)(iVar3 + 0x194);
    }
    if (((iVar3 != 0 && uVar2 != 0) && ((uVar2 & 0x400) == 0)) &&
       (*(uint *)(iVar3 + 0x194) = uVar2 & 0xffffff09 | 0x200, (uVar2 & 0x100000) != 0)) {
      Kill(param_1);
      Kill(param_1);
      iVar3 = *(int *)(iVar3 + 0x718);
      if (((iVar3 != 0) && (uVar1 = *(uint *)(iVar3 + 0x194), uVar1 != 0)) &&
         (((uVar1 & 0x400) == 0 &&
          (*(uint *)(iVar3 + 0x194) = uVar1 & 0xffffff09 | 0x200, (uVar1 & 0x100000) != 0)))) {
        Kill(param_1);
        Kill(param_1);
        Kill(param_1);
      }
    }
    iVar3 = *(int *)(in_r1 + 0x718);
    if (iVar3 == 0) {
      return;
    }
    uVar1 = *(uint *)(iVar3 + 0x194);
    if (uVar1 == 0) {
      return;
    }
    if ((uVar1 & 0x400) != 0) {
      return;
    }
    uVar2 = uVar1 & 0xffffff09 | 0x200;
    *(uint *)(iVar3 + 0x194) = uVar2;
    if ((uVar1 & 0x100000) == 0) {
      return;
    }
    iVar4 = *(int *)(iVar3 + 0x710);
    if (iVar4 != 0) {
      uVar2 = *(uint *)(iVar4 + 0x194);
    }
    uVar1 = uVar2;
    if ((iVar4 != 0 && uVar2 != 0) && ((uVar2 & 0x400) == 0)) {
      uVar1 = uVar2 & 0xffffff09 | 0x200;
      *(uint *)(iVar4 + 0x194) = uVar1;
      if ((uVar2 & 0x100000) != 0) {
        Kill(param_1);
        Kill(param_1);
        Kill(param_1);
      }
    }
    iVar4 = *(int *)(iVar3 + 0x714);
    if (iVar4 != 0) {
      uVar1 = *(uint *)(iVar4 + 0x194);
    }
    if (((iVar4 == 0 || uVar1 == 0) || ((uVar1 & 0x400) != 0)) ||
       (*(uint *)(iVar4 + 0x194) = uVar1 & 0xffffff09 | 0x200, (uVar1 & 0x100000) == 0)) {
      iVar3 = *(int *)(iVar3 + 0x718);
      if (iVar3 == 0) {
        return;
      }
    }
    else {
      Kill(param_1);
      Kill(param_1);
      Kill(param_1);
      iVar3 = *(int *)(iVar3 + 0x718);
      if (iVar3 == 0) {
        return;
      }
    }
    uVar1 = *(uint *)(iVar3 + 0x194);
    if (uVar1 == 0) {
      return;
    }
    if ((uVar1 & 0x400) != 0) {
      return;
    }
    *(uint *)(iVar3 + 0x194) = uVar1 & 0xffffff09 | 0x200;
    if ((uVar1 & 0x100000) == 0) break;
    Kill(param_1);
    Kill(param_1);
    in_r1 = *(int *)(iVar3 + 0x718);
    if (in_r1 == 0) {
      return;
    }
    uVar2 = *(uint *)(in_r1 + 0x194);
    if (uVar2 == 0) {
      return;
    }
    if ((uVar2 & 0x400) != 0) {
      return;
    }
    uVar1 = uVar2 & 0xffffff09 | 0x200;
    *(uint *)(in_r1 + 0x194) = uVar1;
    if ((uVar2 & 0x100000) == 0) {
      return;
    }
  }
  return;
}
