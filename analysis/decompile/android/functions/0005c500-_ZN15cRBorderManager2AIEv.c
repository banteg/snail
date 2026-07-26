/*
 * mangled: _ZN15cRBorderManager2AIEv
 * demangled: cRBorderManager::AI()
 * address: 0005c500
 * size: 212
 */

/* cRBorderManager::AI() */

void __thiscall cRBorderManager::AI(cRBorderManager *this)

{
  uint uVar1;
  int iVar2;
  float fVar3;

  if (this[0x430e4] != (cRBorderManager)0x0) {
    fVar3 = *(float *)(this + 0x430e8);
    *(float *)(this + 0x430e8) = fVar3 + *(float *)(this + 0x430ec);
    if (1.0 < fVar3 + *(float *)(this + 0x430ec)) {
      *(undefined4 *)(this + 0x430e8) = 0x3f800000;
      iVar2 = *(int *)(this + 0x430f0);
      uVar1 = *(uint *)(iVar2 + 0x194);
      if ((uVar1 & 0x40000000) == 0) {
        this[0x430e4] = (cRBorderManager)0x0;
        *(uint *)(iVar2 + 0x194) = *(uint *)(this + 0x430e0) | uVar1;
      }
      else if (*(int *)(Game + 0x24) == 4) {
        this[0x430e4] = (cRBorderManager)0x0;
        *(uint *)(iVar2 + 0x194) = *(uint *)(this + 0x430e0) | uVar1;
      }
    }
  }
  return;
}
