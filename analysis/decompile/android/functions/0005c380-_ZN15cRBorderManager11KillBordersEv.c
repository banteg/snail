/*
 * mangled: _ZN15cRBorderManager11KillBordersEv
 * demangled: cRBorderManager::KillBorders()
 * address: 0005c380
 * size: 72
 */

/* cRBorderManager::KillBorders() */

void __thiscall cRBorderManager::KillBorders(cRBorderManager *this)

{
  cRBorderManager *pcVar1;
  uint uVar2;
  int iVar3;

  iVar3 = 0;
  pcVar1 = this + 0x80c;
  do {
    uVar2 = *(uint *)pcVar1;
    iVar3 = iVar3 + 1;
    if (((uVar2 != 0) && ((uVar2 & 0x400) == 0)) && ((uVar2 & 0x10000000) == 0)) {
      *(uint *)pcVar1 = uVar2 & 0xffffff09 | 0x200;
    }
    pcVar1 = pcVar1 + 0x71c;
  } while (iVar3 != 0x96);
  return;
}
