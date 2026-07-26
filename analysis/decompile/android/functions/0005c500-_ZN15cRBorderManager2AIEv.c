/*
 * mangled: _ZN15cRBorderManager2AIEv
 * demangled: cRBorderManager::AI()
 * address: 0005c500
 * size: 212
 */

/* cRBorderManager::AI() */

void __thiscall cRBorderManager::AI(cRBorderManager *this)

{
  float fVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  float fVar5;

  fVar1 = DAT_0005c5d4;
  iVar3 = DAT_0005c5d8 + 0x5c514;
  if (this[0x430e4] != (cRBorderManager)0x0) {
    fVar5 = *(float *)(this + 0x430e8);
    *(float *)(this + 0x430e8) = fVar5 + *(float *)(this + 0x430ec);
    if (fVar1 < fVar5 + *(float *)(this + 0x430ec)) {
      *(float *)(this + 0x430e8) = fVar1;
      iVar4 = *(int *)(this + 0x430f0);
      uVar2 = *(uint *)(iVar4 + 0x194);
      if ((uVar2 & 0x40000000) == 0) {
        this[0x430e4] = (cRBorderManager)0x0;
        *(uint *)(iVar4 + 0x194) = *(uint *)(this + 0x430e0) | uVar2;
      }
      else if (*(int *)(**(int **)(iVar3 + DAT_0005c5dc) + 0x24) == 4) {
        this[0x430e4] = (cRBorderManager)0x0;
        *(uint *)(iVar4 + 0x194) = *(uint *)(this + 0x430e0) | uVar2;
      }
    }
  }
  return;
}
