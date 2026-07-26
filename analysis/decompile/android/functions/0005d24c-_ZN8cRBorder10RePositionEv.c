/*
 * mangled: _ZN8cRBorder10RePositionEv
 * demangled: cRBorder::RePosition()
 * address: 0005d24c
 * size: 768
 */

/* cRBorder::RePosition() */

void __thiscall cRBorder::RePosition(cRBorder *this)

{
  uint uVar1;
  cRBorder *pcVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;

  while( true ) {
    uVar1 = *(uint *)(this + 0x194);
    if ((uVar1 & 0x800) == 0) {
      if ((uVar1 & 0x10000) == 0) {
        FontType(this + 0x2c4,*(undefined4 *)(this + 0x6e4),*(undefined4 *)(this + 0x6e8),
                 *(undefined4 *)(this + 0x6ec),*(undefined4 *)(this + 0x6f0),this + 0x22c,
                 this + 0x230,this + 0x23c,this + 0x240,*(undefined4 *)(this + 0x21c),
                 (gConfig._28_4_ & 0x1ff) >> 8,*(undefined4 *)(this + 0x254),
                 *(undefined4 *)(this + 600),0x1000000,*(undefined4 *)(this + 0x1e0),
                 *(undefined4 *)(this + 0x1e4),*(undefined4 *)(this + 0x1e8),
                 *(undefined4 *)(this + 0x1ec),1,0);
        fVar3 = *(float *)(this + 0x22c) + *(float *)(this + 0x23c) * -0.05;
        uVar1 = *(uint *)(this + 0x194);
        fVar5 = *(float *)(this + 0x23c) * 1.1;
        *(float *)(this + 0x22c) = fVar3;
        *(float *)(this + 0x23c) = fVar5;
        if ((uVar1 & 0x100000) != 0) {
          *(undefined4 *)(this + 0x23c) = 0x43c80000;
          fVar3 = (fVar3 + fVar5 * 0.5) - 200.0;
          *(float *)(this + 0x22c) = fVar3;
          *(float *)(this + 0x240) = *(float *)(this + 0x240) + 50.0;
        }
        fVar5 = *(float *)(this + 0x230);
        if (*(float *)(this + 0x244) != 0.0) {
          *(float *)(this + 0x23c) = *(float *)(this + 0x244);
        }
      }
      else {
        fVar5 = *(float *)(this + 0x44);
        fVar3 = *(float *)(this + 0x40);
        *(undefined4 *)(this + 0x23c) = *(undefined4 *)(this + 0x48);
        *(float *)(this + 0x230) = fVar5;
        *(float *)(this + 0x22c) = fVar3;
        *(undefined4 *)(this + 0x240) = *(undefined4 *)(this + 0x4c);
      }
    }
    else {
      fVar3 = *(float *)(this + 0x22c);
      fVar5 = *(float *)(this + 0x230);
      *(float *)(this + 0x6ec) = fVar3;
      *(float *)(this + 0x6f0) = fVar5;
    }
    *(float *)(this + 0x234) = fVar3;
    *(float *)(this + 0x238) = fVar5;
    if ((uVar1 & 0x20000000) != 0) {
      return;
    }
    fVar3 = *(float *)(this + 0x23c);
    fVar4 = *(float *)(this + 0x22c);
    fVar6 = *(float *)(this + 0x20c);
    if (640.0 < fVar4 + fVar3 + fVar6) {
      *(float *)(this + 0x234) = (640.0 - fVar6) - fVar3;
    }
    else if (fVar4 - fVar6 < 0.0) {
      *(float *)(this + 0x234) = fVar6;
    }
    if (480.0 < fVar5 + fVar6) {
      *(float *)(this + 0x238) = 480.0 - fVar6;
    }
    else if (fVar5 - fVar6 < 0.0) {
      *(float *)(this + 0x238) = fVar6;
    }
    fVar6 = *(float *)(this + 0x234);
    fVar7 = *(float *)(this + 0x238);
    *(float *)(this + 0x22c) = fVar6;
    *(float *)(this + 0x230) = fVar7;
    *(float *)(this + 0x6ec) = *(float *)(this + 0x6ec) + (fVar6 - fVar4);
    *(float *)(this + 0x6f0) = *(float *)(this + 0x6f0) + (fVar7 - fVar5);
    *(float *)(this + 600) = *(float *)(this + 600) + (fVar6 - fVar4);
    if ((uVar1 & 0x100000) == 0) break;
    pcVar2 = *(cRBorder **)(this + 0x714);
    fVar5 = fVar7 + *(float *)(this + 0x240) * 0.5;
    *(float *)(pcVar2 + 0x230) = fVar7 + 33.0;
    *(float *)(this + 0x17c) = (fVar6 + fVar3 * 0.8) - 4.0;
    *(float *)(this + 0x178) = (fVar6 + fVar3 * 0.1 + 4.0) - 12.0;
    *(float *)(this + 0x184) = (fVar5 + 32.0) - 6.0;
    *(float *)(this + 0x180) = fVar5 - 6.0;
    RePosition(pcVar2);
    pcVar2 = *(cRBorder **)(this + 0x710);
    *(float *)(pcVar2 + 0x230) = *(float *)(this + 0x238) + 33.0;
    RePosition(pcVar2);
    pcVar2 = this + 0x238;
    this = *(cRBorder **)(this + 0x718);
    *(float *)(this + 0x6f0) = *(float *)pcVar2 + 52.0;
  }
  return;
}
