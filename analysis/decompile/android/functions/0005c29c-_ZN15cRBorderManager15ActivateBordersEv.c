/*
 * mangled: _ZN15cRBorderManager15ActivateBordersEv
 * demangled: cRBorderManager::ActivateBorders()
 * address: 0005c29c
 * size: 84
 */

/* cRBorderManager::ActivateBorders() */

void __thiscall cRBorderManager::ActivateBorders(cRBorderManager *this)

{
  undefined4 uVar1;
  cRBorderManager *pcVar2;
  int iVar3;
  uint uVar4;

  uVar1 = DAT_0005c2f0;
  iVar3 = 0;
  pcVar2 = this + 0x878;
  do {
    uVar4 = *(uint *)(pcVar2 + -0x6c);
    iVar3 = iVar3 + 1;
    *(undefined4 *)(pcVar2 + 0x14) = *(undefined4 *)(pcVar2 + 8);
    if (-1 < (int)uVar4) {
      uVar4 = uVar4 & 0xffff7fff;
      *(uint *)(pcVar2 + -0x6c) = uVar4;
    }
    *(undefined4 *)(pcVar2 + 0x10) = *(undefined4 *)(pcVar2 + 8);
    *(uint *)(pcVar2 + -0x6c) = uVar4 & 0x7fffffff;
    *(undefined4 *)pcVar2 = uVar1;
    pcVar2 = pcVar2 + 0x71c;
  } while (iVar3 != 0x96);
  return;
}
