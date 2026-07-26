/*
 * mangled: _ZN8cRBorder10RePositionEv
 * demangled: cRBorder::RePosition()
 * address: 0005d24c
 * size: 768
 */

/* cRBorder::RePosition() */

void __thiscall cRBorder::RePosition(cRBorder *this)

{
  float fVar1;
  float fVar2;
  float fVar3;
  undefined4 uVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  int iVar10;
  uint uVar11;
  cRBorder *pcVar12;
  int iVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;

  iVar10 = DAT_0005d58c;
  fVar9 = DAT_0005d56c;
  fVar8 = DAT_0005d568;
  fVar7 = DAT_0005d564;
  fVar6 = DAT_0005d560;
  fVar5 = DAT_0005d55c;
  uVar4 = DAT_0005d558;
  fVar3 = DAT_0005d554;
  fVar2 = DAT_0005d550;
  fVar1 = DAT_0005d54c;
  iVar13 = DAT_0005d590 + 0x5d274;
  while( true ) {
    uVar11 = *(uint *)(this + 0x194);
    if ((uVar11 & 0x800) == 0) {
      if ((uVar11 & 0x10000) == 0) {
        FontType(this + 0x2c4,*(undefined4 *)(this + 0x6e4),*(undefined4 *)(this + 0x6e8),
                 *(undefined4 *)(this + 0x6ec),*(undefined4 *)(this + 0x6f0),this + 0x22c,
                 this + 0x230,this + 0x23c,this + 0x240,*(undefined4 *)(this + 0x21c),
                 (*(uint *)(*(int *)(iVar13 + iVar10) + 0x1c) & 0x1ff) >> 8,
                 *(undefined4 *)(this + 0x254),*(undefined4 *)(this + 600),0x1000000,
                 *(undefined4 *)(this + 0x1e0),*(undefined4 *)(this + 0x1e4),
                 *(undefined4 *)(this + 0x1e8),*(undefined4 *)(this + 0x1ec),1,0);
        fVar17 = *(float *)(this + 0x22c) + fVar1 * *(float *)(this + 0x23c);
        uVar11 = *(uint *)(this + 0x194);
        fVar19 = fVar2 * *(float *)(this + 0x23c);
        *(float *)(this + 0x22c) = fVar17;
        *(float *)(this + 0x23c) = fVar19;
        if ((uVar11 & 0x100000) != 0) {
          *(undefined4 *)(this + 0x23c) = uVar4;
          fVar17 = (fVar17 + fVar19 * fVar3) - fVar5;
          *(float *)(this + 0x22c) = fVar17;
          *(float *)(this + 0x240) = *(float *)(this + 0x240) + fVar6;
        }
        fVar19 = *(float *)(this + 0x230);
        if (*(float *)(this + 0x244) != 0.0) {
          *(float *)(this + 0x23c) = *(float *)(this + 0x244);
        }
      }
      else {
        fVar19 = *(float *)(this + 0x44);
        fVar17 = *(float *)(this + 0x40);
        *(undefined4 *)(this + 0x23c) = *(undefined4 *)(this + 0x48);
        *(float *)(this + 0x230) = fVar19;
        *(float *)(this + 0x22c) = fVar17;
        *(undefined4 *)(this + 0x240) = *(undefined4 *)(this + 0x4c);
      }
    }
    else {
      fVar17 = *(float *)(this + 0x22c);
      fVar19 = *(float *)(this + 0x230);
      *(float *)(this + 0x6ec) = fVar17;
      *(float *)(this + 0x6f0) = fVar19;
    }
    *(float *)(this + 0x234) = fVar17;
    *(float *)(this + 0x238) = fVar19;
    if ((uVar11 & 0x20000000) != 0) {
      return;
    }
    fVar17 = *(float *)(this + 0x23c);
    fVar18 = *(float *)(this + 0x22c);
    fVar21 = *(float *)(this + 0x20c);
    if (fVar7 < fVar18 + fVar17 + fVar21) {
      *(float *)(this + 0x234) = (fVar7 - fVar21) - fVar17;
    }
    else if (fVar18 - fVar21 < 0.0) {
      *(float *)(this + 0x234) = fVar21;
    }
    if (fVar8 < fVar19 + fVar21) {
      *(float *)(this + 0x238) = fVar8 - fVar21;
    }
    else if (fVar19 - fVar21 < 0.0) {
      *(float *)(this + 0x238) = fVar21;
    }
    fVar16 = *(float *)(this + 0x234);
    fVar22 = *(float *)(this + 0x238);
    *(float *)(this + 0x22c) = fVar16;
    *(float *)(this + 0x230) = fVar22;
    *(float *)(this + 0x6ec) = *(float *)(this + 0x6ec) + (fVar16 - fVar18);
    *(float *)(this + 0x6f0) = *(float *)(this + 0x6f0) + (fVar22 - fVar19);
    *(float *)(this + 600) = *(float *)(this + 600) + (fVar16 - fVar18);
    fVar21 = DAT_0005d584;
    fVar18 = DAT_0005d580;
    fVar19 = DAT_0005d578;
    if ((uVar11 & 0x100000) == 0) break;
    pcVar12 = *(cRBorder **)(this + 0x714);
    fVar20 = fVar22 + fVar3 * *(float *)(this + 0x240);
    fVar14 = fVar20 + DAT_0005d57c;
    fVar15 = fVar16 + fVar9 * fVar17 + DAT_0005d574;
    fVar17 = (fVar16 + DAT_0005d570 * fVar17) - DAT_0005d574;
    *(float *)(pcVar12 + 0x230) = fVar22 + DAT_0005d578;
    *(float *)(this + 0x17c) = fVar17;
    *(float *)(this + 0x178) = fVar15 - fVar21;
    *(float *)(this + 0x184) = fVar14 - fVar18;
    *(float *)(this + 0x180) = fVar20 - fVar18;
    RePosition(pcVar12);
    pcVar12 = *(cRBorder **)(this + 0x710);
    *(float *)(pcVar12 + 0x230) = *(float *)(this + 0x238) + fVar19;
    RePosition(pcVar12);
    pcVar12 = this + 0x238;
    this = *(cRBorder **)(this + 0x718);
    *(float *)(this + 0x6f0) = *(float *)pcVar12 + DAT_0005d588;
  }
  return;
}
