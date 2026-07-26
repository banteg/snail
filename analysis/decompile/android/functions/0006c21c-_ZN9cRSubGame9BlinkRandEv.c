/*
 * mangled: _ZN9cRSubGame9BlinkRandEv
 * demangled: cRSubGame::BlinkRand()
 * address: 0006c21c
 * size: 64
 */

/* cRSubGame::BlinkRand() */

undefined4 __thiscall cRSubGame::BlinkRand(cRSubGame *this)

{
  int iVar1;

  iVar1 = (*(int *)(this + 0xfa60) + 1) % 0x18;
  *(int *)(this + 0xfa60) = iVar1;
  return *(undefined4 *)(this + (iVar1 + 0x3e98) * 4 + 4);
}
