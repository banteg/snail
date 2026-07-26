/*
 * mangled: _ZN15cRParcelManager2AIEv
 * demangled: cRParcelManager::AI()
 * address: 0006cb5c
 * size: 84
 */

/* cRParcelManager::AI() */

void __thiscall cRParcelManager::AI(cRParcelManager *this)

{
  int iVar1;
  cRParcelManager *pcVar2;
  int iVar3;

  iVar3 = 0;
  pcVar2 = this;
  do {
    while (*(int *)(pcVar2 + 0x2c) != 0) {
      iVar1 = iVar3 * 0x80;
      iVar3 = iVar3 + 1;
      (*(code *)**(undefined4 **)pcVar2)(this + iVar1);
      pcVar2 = pcVar2 + 0x80;
      if (iVar3 == 0x32) {
        return;
      }
    }
    iVar3 = iVar3 + 1;
    pcVar2 = pcVar2 + 0x80;
  } while (iVar3 != 0x32);
  return;
}
