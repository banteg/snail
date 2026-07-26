/*
 * mangled: _ZN15cRBorderManager13UnHideBordersEv
 * demangled: cRBorderManager::UnHideBorders()
 * address: 0003af6c
 * size: 232
 */

/* cRBorderManager::UnHideBorders() */

void cRBorderManager::UnHideBorders(void)

{
  int in_r0;
  int iVar1;
  int in_r2;
  int iVar2;

  iVar2 = *(int *)(in_r0 + 0x2c);
  if (0 < iVar2) {
    in_r2 = iVar2 + -1;
    iVar2 = *(int *)(in_r0 + 0x30);
    *(int *)(in_r0 + 0x2c) = in_r2;
  }
  if (iVar2 < 1) {
    return;
  }
  iVar1 = iVar2 + -1;
  *(int *)(in_r0 + 0x30) = iVar1;
  if (*(int *)(iVar2 * 8 + in_r0 + 0x2c) == in_r2) {
    do {
      iVar2 = *(int *)(iVar1 * 8 + in_r0 + 0x38);
      *(uint *)(iVar2 + 0x194) = *(uint *)(iVar2 + 0x194) & 0xffffefff;
      iVar2 = *(int *)(*(int *)(in_r0 + 0x30) * 8 + in_r0 + 0x38);
      *(undefined4 *)(iVar2 + 0x210) = *(undefined4 *)(iVar2 + 0x208);
      iVar2 = *(int *)(*(int *)(in_r0 + 0x30) * 8 + in_r0 + 0x38);
      *(undefined4 *)(iVar2 + 0x214) = *(undefined4 *)(iVar2 + 0x208);
      *(undefined4 *)(*(int *)(*(int *)(in_r0 + 0x30) * 8 + in_r0 + 0x38) + 0x200) = 0;
      *(undefined4 *)(*(int *)(*(int *)(in_r0 + 0x30) * 8 + in_r0 + 0x38) + 0x204) = 0;
      iVar2 = *(int *)(in_r0 + 0x30);
      iVar1 = iVar2 + -1;
      *(int *)(in_r0 + 0x30) = iVar1;
      if (iVar1 < 0) break;
    } while (*(int *)(iVar2 * 8 + in_r0 + 0x2c) == *(int *)(in_r0 + 0x2c));
  }
  *(int *)(in_r0 + 0x30) = iVar1 + 1;
  return;
}
