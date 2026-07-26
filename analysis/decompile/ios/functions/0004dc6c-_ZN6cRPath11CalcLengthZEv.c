/*
 * mangled: _ZN6cRPath11CalcLengthZEv
 * demangled: cRPath::CalcLengthZ()
 * address: 0004dc6c
 * size: 432
 */

/* cRPath::CalcLengthZ() */

void __thiscall cRPath::CalcLengthZ(cRPath *this)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  float fVar6;
  tVector atStack_24 [12];

  iVar1 = 0;
  iVar3 = *(int *)(this + 0x38);
  *(undefined4 *)(this + 0x3c) = 0;
  if (0 < iVar3) {
    iVar5 = 0;
    do {
      iVar4 = *(int *)(this + 0x50) + iVar5;
      iVar1 = iVar1 + 1;
      iVar5 = iVar5 + 0xa8;
      iVar4 = (int)(*(float *)(iVar4 + 0x38) + 1.0);
      if (*(int *)(this + 0x3c) < iVar4) {
        *(int *)(this + 0x3c) = iVar4;
      }
    } while (iVar1 < iVar3);
    if (0 < iVar3) {
      iVar5 = 0;
      iVar1 = 0;
      do {
        iVar5 = iVar5 + 1;
        tMatrix::Invert((tMatrix *)(iVar1 + *(int *)(this + 0x4c)) + 0x40,
                        (tMatrix *)(iVar1 + *(int *)(this + 0x4c)));
        tMatrix::Invert((tMatrix *)(iVar1 + *(int *)(this + 0x50)) + 0x40,
                        (tMatrix *)(iVar1 + *(int *)(this + 0x50)));
        iVar3 = *(int *)(this + 0x38);
        iVar1 = iVar1 + 0xa8;
      } while (iVar5 < iVar3);
    }
  }
  if (iVar3 + -1 < 1) {
    iVar1 = *(int *)(this + 0x4c);
  }
  else {
    iVar1 = *(int *)(this + 0x4c);
    iVar4 = 0;
    iVar5 = 0;
    do {
      tVector::Cross(atStack_24,(tVector *)(iVar1 + iVar5 + 0x20),(tVector *)(iVar5 + iVar1 + 200));
      iVar1 = *(int *)(this + 0x4c);
      iVar4 = iVar4 + 1;
      uVar2 = tVector::Dot(atStack_24,(tVector *)(iVar5 + iVar1));
      *(undefined4 *)(iVar5 + iVar1 + 0xa4) = uVar2;
      iVar1 = 0;
      if (this[0x30] != (cRPath)0x0) {
        iVar1 = iVar5 + *(int *)(this + 0x4c);
      }
      if (this[0x30] != (cRPath)0x0) {
        *(float *)(iVar1 + 0xa4) = -*(float *)(iVar1 + 0xa4);
      }
      iVar1 = *(int *)(this + 0x4c);
      iVar3 = iVar5 + iVar1;
      fVar6 = *(float *)(iVar3 + 0xa4);
      if (0.0 < fVar6) {
        *(undefined4 *)(iVar3 + 0xa4) = 0;
        iVar1 = *(int *)(this + 0x4c);
        iVar3 = iVar5 + iVar1;
      }
      iVar5 = iVar5 + 0xa8;
      if (0.0 < fVar6) {
        fVar6 = *(float *)(iVar3 + 0xa4);
      }
      if (fVar6 < -0.1) {
        *(undefined4 *)(iVar3 + 0xa4) = 0xbdcccccd;
      }
      iVar3 = *(int *)(this + 0x38);
      if (fVar6 < -0.1) {
        iVar1 = *(int *)(this + 0x4c);
      }
    } while (iVar4 < iVar3 + -1);
  }
  *(undefined4 *)(iVar3 * 0xa8 + iVar1 + -4) = 0;
  **(uint **)(this + 0x24) = **(uint **)(this + 0x24) | 0x80;
  **(uint **)(this + 0x24) = **(uint **)(this + 0x24) & 0xffefffff;
  return;
}
