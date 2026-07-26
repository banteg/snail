/*
 * mangled: _ZN8cRBorder8HideInitEv
 * demangled: cRBorder::HideInit()
 * address: 0003b3b0
 * size: 104
 */

/* cRBorder::HideInit() */

void __thiscall cRBorder::HideInit(cRBorder *this)

{
  if ((*(uint *)(this + 0x194) & 0x1000) != 0) {
    return;
  }
  *(uint *)(this + 0x194) = *(uint *)(this + 0x194) | 0x1000;
  *(undefined4 *)(this + 0x38) = 0;
  if (*(int *)(this + 0x288) != 2) {
    if (*(int *)(this + 0x288) != 3) {
      return;
    }
    cRBorderManager::Kill((cRBorder *)(*(int *)PTR__Game_001b60b8 + 0xd14));
    *(undefined4 *)(this + 0x29c) = 0;
  }
  *(undefined4 *)(this + 0x288) = 1;
  return;
}
