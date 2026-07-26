/*
 * mangled: _ZN13cRAnimManager2AIEv
 * demangled: cRAnimManager::AI()
 * address: 0006cd98
 * size: 560
 */

/* cRAnimManager::AI() */

void __thiscall cRAnimManager::AI(cRAnimManager *this)

{
  bool bVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  float fVar6;
  undefined4 uVar7;

  this[0x10] = (cRAnimManager)0x0;
  if (*(int *)this != 1) {
    return;
  }
  fVar6 = *(float *)(this + 4) +
          (((*(float *)(Game + 0x718ec) + *(float *)(Game + 0x718ec)) - 0.2) + 1.0) *
          *(float *)(this + 8);
  *(float *)(this + 4) = fVar6;
  if (1.0 <= fVar6) {
    uVar2 = **(ushort **)(this + 0xc);
    if ((uVar2 & 1) == 0) {
      if ((uVar2 & 4) != 0) {
        this[0x10] = (cRAnimManager)0x1;
        *(undefined4 *)(this + 4) = 0x3f7fbe77;
        *(undefined4 *)(this + 8) = 0;
        fVar6 = 0.999;
        goto LAB_0006ce60;
      }
      if ((uVar2 & 2) == 0) goto LAB_0006ce00;
      fVar6 = 2.0 - fVar6;
      *(float *)(this + 4) = fVar6;
      bVar1 = fVar6 < 0.0;
      *(float *)(this + 8) = -*(float *)(this + 8);
    }
    else {
      fVar6 = fVar6 - 1.0;
      this[0x10] = (cRAnimManager)0x1;
      bVar1 = fVar6 < 0.0;
      *(float *)(this + 4) = fVar6;
    }
  }
  else {
LAB_0006ce00:
    if (0.0 <= fVar6) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
  }
  if (bVar1) {
    uVar2 = **(ushort **)(this + 0xc);
    if ((uVar2 & 2) != 0) {
      this[0x10] = (cRAnimManager)0x1;
      *(float *)(this + 4) = -fVar6;
      *(float *)(this + 8) = -*(float *)(this + 8);
    }
    if ((uVar2 & 8) != 0) {
      *(undefined4 *)(this + 4) = 0;
      *(undefined4 *)(this + 8) = 0;
      this[0x10] = (cRAnimManager)0x1;
      fVar6 = 0.0;
      goto LAB_0006ce60;
    }
    fVar6 = *(float *)(this + 4);
    if (fVar6 < 0.0) {
      fVar6 = 0.0;
      goto LAB_0006ce60;
    }
  }
  if (0.9999 < fVar6) {
    fVar6 = 0.9999;
  }
LAB_0006ce60:
  *(float *)(this + 4) = fVar6;
  if (this[0x10] == (cRAnimManager)0x0) {
    return;
  }
  if (0 < *(int *)(this + 0x3c)) {
    if (*(int *)(this + 0x14) == -1) {
      *(undefined4 *)(this + 8) = 0;
      *(undefined4 *)(this + 4) = 0;
      *(uint *)(*(int *)(this + 0x40) + 4) = *(uint *)(*(int *)(this + 0x40) + 4) & 0xffffffdf;
    }
    else {
      iVar5 = *(int *)(this + 0x40);
      iVar3 = *(int *)(this + 0x44);
      *(undefined4 *)(this + 4) = 0;
      *(uint *)(iVar5 + 4) = *(uint *)(iVar5 + 4) | 0x20;
      iVar3 = *(int *)(*(int *)(this + 0x14) * 0x74 + iVar3 + 0x24);
      iVar4 = *(int *)(iVar3 + 0x104);
      uVar7 = *(undefined4 *)(iVar4 + 0x14);
      *(int *)(iVar5 + 0x24) = iVar3;
      *(undefined4 *)(this + 8) = uVar7;
      *(int *)(this + 0xc) = iVar4;
    }
    iVar3 = *(int *)(this + 0x3c) + -1;
    *(int *)(this + 0x3c) = iVar3;
    if (0 < iVar3) {
      iVar4 = 0;
      do {
        iVar4 = iVar4 + 1;
        *(undefined4 *)(this + 0x14) = *(undefined4 *)(this + 0x18);
        this = this + 4;
      } while (iVar4 < iVar3);
      return;
    }
    return;
  }
  return;
}
