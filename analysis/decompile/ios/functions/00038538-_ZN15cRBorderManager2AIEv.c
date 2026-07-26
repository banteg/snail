/*
 * mangled: _ZN15cRBorderManager2AIEv
 * demangled: cRBorderManager::AI()
 * address: 00038538
 * size: 132
 */

/* cRBorderManager::AI() */

void __thiscall cRBorderManager::AI(cRBorderManager *this)

{
  int iVar1;
  uint uVar2;
  float fVar3;

  if (this[0x430e4] == (cRBorderManager)0x0) {
    return;
  }
  fVar3 = *(float *)(this + 0x430e8);
  *(float *)(this + 0x430e8) = fVar3 + *(float *)(this + 0x430ec);
  if (1.0 < fVar3 + *(float *)(this + 0x430ec)) {
    *(undefined4 *)(this + 0x430e8) = 0x3f800000;
    iVar1 = *(int *)(this + 0x430f0);
    uVar2 = *(uint *)(iVar1 + 0x194);
    if ((uVar2 & 0x40000000) == 0) {
      *(uint *)(iVar1 + 0x194) = *(uint *)(this + 0x430e0) | uVar2;
      this[0x430e4] = (cRBorderManager)0x0;
      return;
    }
    if (*(int *)(*(int *)PTR__Game_001b60b8 + 0x24) == 4) {
      *(uint *)(iVar1 + 0x194) = *(uint *)(this + 0x430e0) | uVar2;
      this[0x430e4] = (cRBorderManager)0x0;
    }
    return;
  }
  return;
}
