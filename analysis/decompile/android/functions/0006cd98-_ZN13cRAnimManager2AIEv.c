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
  float fVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  undefined4 uVar10;

  iVar4 = DAT_0006cfe0;
  this[0x10] = (cRAnimManager)0x0;
  fVar3 = DAT_0006cfcc;
  if (*(int *)this != 1) {
    return;
  }
  fVar7 = *(float *)(**(int **)(iVar4 + 0x6cdb4 + DAT_0006cfe4) + 0x718ec);
  fVar8 = *(float *)(this + 4) +
          (((fVar7 + fVar7) - DAT_0006cfc8) + DAT_0006cfcc) * *(float *)(this + 8);
  bVar1 = DAT_0006cfcc <= fVar8;
  *(float *)(this + 4) = fVar8;
  fVar9 = DAT_0006cfd8;
  fVar7 = DAT_0006cfd0;
  if (bVar1) {
    uVar2 = **(ushort **)(this + 0xc);
    if ((uVar2 & 1) == 0) {
      if ((uVar2 & 4) != 0) {
        this[0x10] = (cRAnimManager)0x1;
        *(float *)(this + 4) = fVar9;
        *(float *)(this + 8) = fVar7;
        goto LAB_0006ce60;
      }
      if ((uVar2 & 2) == 0) goto LAB_0006ce00;
      fVar8 = DAT_0006cfd4 - fVar8;
      *(float *)(this + 4) = fVar8;
      bVar1 = fVar8 < 0.0;
      *(float *)(this + 8) = -*(float *)(this + 8);
    }
    else {
      fVar8 = fVar8 - fVar3;
      this[0x10] = (cRAnimManager)0x1;
      bVar1 = fVar8 < 0.0;
      *(float *)(this + 4) = fVar8;
    }
  }
  else {
LAB_0006ce00:
    if (0.0 <= fVar8) {
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
      *(float *)(this + 4) = -fVar8;
      *(float *)(this + 8) = -*(float *)(this + 8);
    }
    fVar9 = DAT_0006cfd0;
    if ((uVar2 & 8) != 0) {
      *(float *)(this + 4) = DAT_0006cfd0;
      *(float *)(this + 8) = fVar9;
      this[0x10] = (cRAnimManager)0x1;
      goto LAB_0006ce60;
    }
    fVar8 = *(float *)(this + 4);
    if (fVar8 < 0.0) goto LAB_0006ce60;
  }
  fVar9 = fVar8;
  if (DAT_0006cfdc < fVar8) {
    fVar9 = DAT_0006cfdc;
  }
LAB_0006ce60:
  *(float *)(this + 4) = fVar9;
  fVar3 = DAT_0006cfd0;
  if (this[0x10] == (cRAnimManager)0x0) {
    return;
  }
  if (0 < *(int *)(this + 0x3c)) {
    if (*(int *)(this + 0x14) == -1) {
      *(float *)(this + 8) = DAT_0006cfd0;
      *(float *)(this + 4) = fVar3;
      *(uint *)(*(int *)(this + 0x40) + 4) = *(uint *)(*(int *)(this + 0x40) + 4) & 0xffffffdf;
    }
    else {
      iVar6 = *(int *)(this + 0x40);
      iVar4 = *(int *)(this + 0x44);
      *(float *)(this + 4) = DAT_0006cfd0;
      *(uint *)(iVar6 + 4) = *(uint *)(iVar6 + 4) | 0x20;
      iVar4 = *(int *)(*(int *)(this + 0x14) * 0x74 + iVar4 + 0x24);
      iVar5 = *(int *)(iVar4 + 0x104);
      uVar10 = *(undefined4 *)(iVar5 + 0x14);
      *(int *)(iVar6 + 0x24) = iVar4;
      *(undefined4 *)(this + 8) = uVar10;
      *(int *)(this + 0xc) = iVar5;
    }
    iVar4 = *(int *)(this + 0x3c) + -1;
    *(int *)(this + 0x3c) = iVar4;
    if (0 < iVar4) {
      iVar5 = 0;
      do {
        iVar5 = iVar5 + 1;
        *(undefined4 *)(this + 0x14) = *(undefined4 *)(this + 0x18);
        this = this + 4;
      } while (iVar5 < iVar4);
      return;
    }
    return;
  }
  return;
}
