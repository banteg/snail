/*
 * mangled: _ZN15cRBorderManager15ActivateBordersEv
 * demangled: cRBorderManager::ActivateBorders()
 * address: 0005c29c
 * size: 84
 */

/* cRBorderManager::ActivateBorders() */

void __thiscall cRBorderManager::ActivateBorders(cRBorderManager *this)

{
  cRBorderManager *pcVar1;
  int iVar2;
  uint uVar3;

  iVar2 = 0;
  pcVar1 = this + 0x878;
  do {
    uVar3 = *(uint *)(pcVar1 + -0x6c);
    iVar2 = iVar2 + 1;
    *(undefined4 *)(pcVar1 + 0x14) = *(undefined4 *)(pcVar1 + 8);
    if (-1 < (int)uVar3) {
      uVar3 = uVar3 & 0xffff7fff;
      *(uint *)(pcVar1 + -0x6c) = uVar3;
    }
    *(undefined4 *)(pcVar1 + 0x10) = *(undefined4 *)(pcVar1 + 8);
    *(uint *)(pcVar1 + -0x6c) = uVar3 & 0x7fffffff;
    *(undefined4 *)pcVar1 = 0;
    pcVar1 = pcVar1 + 0x71c;
  } while (iVar2 != 0x96);
  return;
}
