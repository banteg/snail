/*
 * mangled: _ZN6cRPath11CalcLengthZEv
 * demangled: cRPath::CalcLengthZ()
 * address: 0004c454
 * size: 400
 */

/* cRPath::CalcLengthZ() */

void __thiscall cRPath::CalcLengthZ(cRPath *this)

{
  float *pfVar1;
  float fVar2;
  undefined4 uVar3;
  int iVar4;
  tMatrix *ptVar5;
  undefined4 uVar6;
  int iVar7;
  uint *puVar8;
  int iVar9;
  int iVar10;
  bool bVar11;
  int iVar12;
  float extraout_s15;
  float fVar13;
  tVector atStack_34 [16];

  iVar10 = *(int *)(this + 0x38);
  iVar9 = 0;
  *(undefined4 *)(this + 0x3c) = 0;
  fVar2 = DAT_0004c5e4;
  if (0 < iVar10) {
    iVar4 = *(int *)(this + 0x50);
    iVar7 = 0;
    while( true ) {
      pfVar1 = (float *)(iVar4 + 0x38);
      iVar7 = iVar7 + 1;
      iVar4 = iVar4 + 0xa8;
      iVar12 = (int)(fVar2 + *pfVar1);
      if (iVar9 < iVar12) {
        *(int *)(this + 0x3c) = iVar12;
      }
      if (iVar10 <= iVar7) break;
      iVar9 = *(int *)(this + 0x3c);
    }
    iVar9 = 0;
    iVar4 = 0;
    do {
      iVar4 = iVar4 + 1;
      tMatrix::Invert((tMatrix *)(*(int *)(this + 0x4c) + iVar9) + 0x40,
                      (tMatrix *)(*(int *)(this + 0x4c) + iVar9));
      ptVar5 = (tMatrix *)(*(int *)(this + 0x50) + iVar9);
      iVar9 = iVar9 + 0xa8;
      tMatrix::Invert(ptVar5 + 0x40,ptVar5);
      fVar2 = DAT_0004c5ec;
      uVar3 = DAT_0004c5e8;
      iVar10 = *(int *)(this + 0x38);
    } while (iVar4 < iVar10);
    if (1 < iVar10) {
      iVar4 = *(int *)(this + 0x4c);
      iVar7 = 0;
      iVar9 = 0;
      do {
        iVar12 = iVar9 + 0xa8;
        tVector::Cross(atStack_34,(tVector *)(iVar4 + iVar9 + 0x20),
                       (tVector *)(iVar4 + iVar12 + 0x20));
        iVar10 = *(int *)(this + 0x4c);
        uVar6 = tVector::Dot(atStack_34,(tVector *)(iVar10 + iVar9));
        bVar11 = this[0x30] == (cRPath)0x0;
        if (bVar11) {
          iVar4 = *(int *)(this + 0x4c);
        }
        else {
          iVar4 = *(int *)(this + 0x4c);
        }
        *(undefined4 *)((tVector *)(iVar10 + iVar9) + 0xa4) = uVar6;
        if (!bVar11) {
          iVar9 = iVar4 + iVar9;
        }
        if (bVar11) {
          iVar9 = iVar4 + iVar9;
          fVar13 = extraout_s15;
        }
        else {
          fVar13 = -*(float *)(iVar9 + 0xa4);
        }
        if (bVar11) {
          fVar13 = *(float *)(iVar9 + 0xa4);
        }
        else {
          *(float *)(iVar9 + 0xa4) = fVar13;
        }
        if (0.0 < fVar13) {
          *(undefined4 *)(iVar9 + 0xa4) = uVar3;
        }
        else if (fVar13 < fVar2) {
          *(float *)(iVar9 + 0xa4) = fVar2;
        }
        iVar7 = iVar7 + 1;
        iVar10 = *(int *)(this + 0x38) + -1;
        iVar9 = iVar12;
      } while (iVar7 < iVar10);
      goto LAB_0004c5a8;
    }
  }
  iVar10 = iVar10 + -1;
  iVar4 = *(int *)(this + 0x4c);
LAB_0004c5a8:
  puVar8 = *(uint **)(this + 0x24);
  *(undefined4 *)(iVar10 * 0xa8 + iVar4 + 0xa4) = DAT_0004c5e8;
  *puVar8 = *puVar8 & 0xffefffff | 0x80;
  return;
}
