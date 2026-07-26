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
  int iVar2;
  tMatrix *ptVar3;
  undefined4 uVar4;
  int iVar5;
  uint *puVar6;
  int iVar7;
  int iVar8;
  bool bVar9;
  int iVar10;
  float extraout_s15;
  float fVar11;
  tVector atStack_34 [16];

  iVar8 = *(int *)(this + 0x38);
  iVar7 = 0;
  *(undefined4 *)(this + 0x3c) = 0;
  if (0 < iVar8) {
    iVar2 = *(int *)(this + 0x50);
    iVar5 = 0;
    while( true ) {
      pfVar1 = (float *)(iVar2 + 0x38);
      iVar5 = iVar5 + 1;
      iVar2 = iVar2 + 0xa8;
      iVar10 = (int)(*pfVar1 + 1.0);
      if (iVar7 < iVar10) {
        *(int *)(this + 0x3c) = iVar10;
      }
      if (iVar8 <= iVar5) break;
      iVar7 = *(int *)(this + 0x3c);
    }
    iVar7 = 0;
    iVar2 = 0;
    do {
      iVar2 = iVar2 + 1;
      tMatrix::Invert((tMatrix *)(*(int *)(this + 0x4c) + iVar7) + 0x40,
                      (tMatrix *)(*(int *)(this + 0x4c) + iVar7));
      ptVar3 = (tMatrix *)(*(int *)(this + 0x50) + iVar7);
      iVar7 = iVar7 + 0xa8;
      tMatrix::Invert(ptVar3 + 0x40,ptVar3);
      iVar8 = *(int *)(this + 0x38);
    } while (iVar2 < iVar8);
    if (1 < iVar8) {
      iVar2 = *(int *)(this + 0x4c);
      iVar5 = 0;
      iVar7 = 0;
      do {
        iVar10 = iVar7 + 0xa8;
        tVector::Cross(atStack_34,(tVector *)(iVar2 + iVar7 + 0x20),
                       (tVector *)(iVar2 + iVar10 + 0x20));
        iVar8 = *(int *)(this + 0x4c);
        uVar4 = tVector::Dot(atStack_34,(tVector *)(iVar8 + iVar7));
        bVar9 = this[0x30] == (cRPath)0x0;
        if (bVar9) {
          iVar2 = *(int *)(this + 0x4c);
        }
        else {
          iVar2 = *(int *)(this + 0x4c);
        }
        *(undefined4 *)((tVector *)(iVar8 + iVar7) + 0xa4) = uVar4;
        if (!bVar9) {
          iVar7 = iVar2 + iVar7;
        }
        if (bVar9) {
          iVar7 = iVar2 + iVar7;
          fVar11 = extraout_s15;
        }
        else {
          fVar11 = -*(float *)(iVar7 + 0xa4);
        }
        if (bVar9) {
          fVar11 = *(float *)(iVar7 + 0xa4);
        }
        else {
          *(float *)(iVar7 + 0xa4) = fVar11;
        }
        if (0.0 < fVar11) {
          *(undefined4 *)(iVar7 + 0xa4) = 0;
        }
        else if (fVar11 < -0.1) {
          *(undefined4 *)(iVar7 + 0xa4) = 0xbdcccccd;
        }
        iVar5 = iVar5 + 1;
        iVar8 = *(int *)(this + 0x38) + -1;
        iVar7 = iVar10;
      } while (iVar5 < iVar8);
      goto LAB_0004c5a8;
    }
  }
  iVar8 = iVar8 + -1;
  iVar2 = *(int *)(this + 0x4c);
LAB_0004c5a8:
  puVar6 = *(uint **)(this + 0x24);
  *(undefined4 *)(iVar8 * 0xa8 + iVar2 + 0xa4) = 0;
  *puVar6 = *puVar6 & 0xffefffff | 0x80;
  return;
}
