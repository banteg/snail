/*
 * mangled: _ZN15cRBorderManager11KillBordersEv
 * demangled: cRBorderManager::KillBorders()
 * address: 000384f0
 * size: 72
 */

/* cRBorderManager::KillBorders() */

void __thiscall cRBorderManager::KillBorders(cRBorderManager *this)

{
  cRBorderManager *pcVar1;
  int iVar2;
  uint uVar3;

  pcVar1 = this + 0x80c;
  iVar2 = 0;
  do {
    uVar3 = *(uint *)pcVar1;
    if (((uVar3 != 0) && ((uVar3 & 0x400) == 0)) && ((uVar3 & 0x10000000) == 0)) {
      *(uint *)pcVar1 = uVar3 & 0xffffff09 | 0x200;
    }
    iVar2 = iVar2 + 1;
    pcVar1 = pcVar1 + 0x71c;
  } while (iVar2 != 0x96);
  return;
}
