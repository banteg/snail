/*
 * mangled: _ZN16cRTwinkleManager2AIEv
 * demangled: cRTwinkleManager::AI()
 * address: 0005d018
 * size: 68
 */

/* cRTwinkleManager::AI() */

void __thiscall cRTwinkleManager::AI(cRTwinkleManager *this)

{
  int iVar1;
  int iVar2;

  if (*(int *)(this + 0xf0) != 1) {
    return;
  }
  if (*(int *)(this + 0xf4) < 1) {
    return;
  }
  iVar1 = 0;
  do {
    iVar2 = iVar1 + 1;
    cRTwinkle::AI((cRTwinkle *)(this + iVar1 * 0x30));
    iVar1 = iVar2;
  } while (iVar2 < *(int *)(this + 0xf4));
  return;
}
