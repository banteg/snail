/*
 * mangled: _ZN11cRSnailSkin2AIEv
 * demangled: cRSnailSkin::AI()
 * address: 0006d2cc
 * size: 100
 */

/* cRSnailSkin::AI() */

void __thiscall cRSnailSkin::AI(cRSnailSkin *this)

{
  float fVar1;
  undefined4 uVar2;
  int iVar3;
  uint *puVar4;
  float fVar5;

  puVar4 = *(uint **)(*(int *)(this + 0x10) + 0x24);
  *puVar4 = *puVar4 | 8;
  iVar3 = *(int *)(this + 0x14);
  puVar4[3] = *(uint *)(this + *(int *)this * 4 + 4);
  fVar1 = DAT_0006d330;
  if (iVar3 == 1) {
    fVar5 = *(float *)(this + 0x18);
    *(float *)(this + 0x18) = fVar5 + *(float *)(this + 0x1c);
    uVar2 = DAT_0006d334;
    if (fVar1 < fVar5 + *(float *)(this + 0x1c)) {
      *(undefined4 *)this = 0;
      *(undefined4 *)(this + 0x14) = 0;
      *(undefined4 *)(this + 0x18) = uVar2;
    }
    return;
  }
  return;
}
