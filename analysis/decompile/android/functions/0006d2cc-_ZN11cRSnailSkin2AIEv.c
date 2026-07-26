/*
 * mangled: _ZN11cRSnailSkin2AIEv
 * demangled: cRSnailSkin::AI()
 * address: 0006d2cc
 * size: 100
 */

/* cRSnailSkin::AI() */

void __thiscall cRSnailSkin::AI(cRSnailSkin *this)

{
  int iVar1;
  uint *puVar2;
  float fVar3;

  puVar2 = *(uint **)(*(int *)(this + 0x10) + 0x24);
  *puVar2 = *puVar2 | 8;
  iVar1 = *(int *)(this + 0x14);
  puVar2[3] = *(uint *)(this + *(int *)this * 4 + 4);
  if (iVar1 == 1) {
    fVar3 = *(float *)(this + 0x18);
    *(float *)(this + 0x18) = fVar3 + *(float *)(this + 0x1c);
    if (1.0 < fVar3 + *(float *)(this + 0x1c)) {
      *(undefined4 *)this = 0;
      *(undefined4 *)(this + 0x14) = 0;
      *(undefined4 *)(this + 0x18) = 0;
    }
    return;
  }
  return;
}
