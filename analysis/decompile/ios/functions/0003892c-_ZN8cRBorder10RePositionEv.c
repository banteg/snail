/*
 * mangled: _ZN8cRBorder10RePositionEv
 * demangled: cRBorder::RePosition()
 * address: 0003892c
 * size: 800
 */

/* cRBorder::RePosition() */

void __thiscall cRBorder::RePosition(cRBorder *this)

{
  undefined *puVar1;
  cRBorder *pcVar2;
  uint uVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;

  puVar1 = PTR__gConfig_001b60d4;
  do {
    uVar3 = *(uint *)(this + 0x194);
    if ((uVar3 & 0x800) == 0) {
      if ((uVar3 & 0x10000) == 0) {
        FontType(this + 0x2c4,*(undefined4 *)(this + 0x6e4),*(undefined4 *)(this + 0x6e8),
                 *(undefined4 *)(this + 0x6ec),*(undefined4 *)(this + 0x6f0),this + 0x22c,
                 this + 0x230,this + 0x23c,this + 0x240,*(undefined4 *)(this + 0x21c),
                 *(uint *)(puVar1 + 0x1c) >> 8 & 1,*(undefined4 *)(this + 0x254),
                 *(undefined4 *)(this + 600),0x1000000,*(undefined4 *)(this + 0x1e0),
                 *(undefined4 *)(this + 0x1e4),*(undefined4 *)(this + 0x1e8),
                 *(undefined4 *)(this + 0x1ec),1,0);
        uVar3 = *(uint *)(this + 0x194);
        fVar6 = *(float *)(this + 0x22c) + *(float *)(this + 0x23c) * -0.05;
        fVar5 = *(float *)(this + 0x23c) * 1.1;
        *(float *)(this + 0x22c) = fVar6;
        *(float *)(this + 0x23c) = fVar5;
        if ((uVar3 & 0x100000) != 0) {
          *(undefined4 *)(this + 0x23c) = 0x43c80000;
          fVar6 = fVar6 + fVar5 * 0.5 + -200.0;
          *(float *)(this + 0x22c) = fVar6;
          *(float *)(this + 0x240) = *(float *)(this + 0x240) + 50.0;
        }
        if (*(float *)(this + 0x244) == 0.0) {
          fVar5 = *(float *)(this + 0x230);
        }
        else {
          fVar5 = *(float *)(this + 0x230);
          *(float *)(this + 0x23c) = *(float *)(this + 0x244);
        }
        goto LAB_0003896c;
      }
      fVar6 = *(float *)(this + 0x40);
      fVar5 = *(float *)(this + 0x44);
      *(float *)(this + 0x22c) = fVar6;
      *(float *)(this + 0x230) = fVar5;
      *(undefined4 *)(this + 0x23c) = *(undefined4 *)(this + 0x48);
      *(undefined4 *)(this + 0x240) = *(undefined4 *)(this + 0x4c);
      *(float *)(this + 0x234) = fVar6;
      *(float *)(this + 0x238) = fVar5;
    }
    else {
      fVar6 = *(float *)(this + 0x22c);
      fVar5 = *(float *)(this + 0x230);
      *(float *)(this + 0x6ec) = fVar6;
      *(float *)(this + 0x6f0) = fVar5;
LAB_0003896c:
      *(float *)(this + 0x234) = fVar6;
      *(float *)(this + 0x238) = fVar5;
    }
    if ((uVar3 & 0x20000000) != 0) {
      return;
    }
    fVar4 = *(float *)(this + 0x23c);
    fVar8 = *(float *)(this + 0x20c);
    if (640.0 < fVar6 + fVar4 + fVar8) {
      *(float *)(this + 0x234) = (640.0 - fVar8) - fVar4;
    }
    else if (fVar6 - fVar8 < 0.0) {
      *(float *)(this + 0x234) = fVar8;
    }
    if (480.0 < fVar5 + fVar8) {
      *(float *)(this + 0x238) = 480.0 - fVar8;
    }
    else if (fVar5 - fVar8 < 0.0) {
      *(float *)(this + 0x238) = fVar8;
    }
    fVar7 = *(float *)(this + 0x234);
    fVar8 = *(float *)(this + 0x238);
    *(float *)(this + 0x22c) = fVar7;
    *(float *)(this + 0x230) = fVar8;
    *(float *)(this + 600) = *(float *)(this + 600) + (fVar7 - fVar6);
    *(float *)(this + 0x6ec) = *(float *)(this + 0x6ec) + (fVar7 - fVar6);
    *(float *)(this + 0x6f0) = *(float *)(this + 0x6f0) + (fVar8 - fVar5);
    if ((uVar3 & 0x100000) == 0) {
      return;
    }
    fVar6 = 33.0;
    pcVar2 = *(cRBorder **)(this + 0x714);
    *(float *)(this + 0x178) = (fVar7 + fVar4 * 0.1 + 4.0) - 12.0;
    *(float *)(this + 0x17c) = (fVar7 + fVar4 * 0.8) - 4.0;
    fVar5 = fVar8 + *(float *)(this + 0x240) * 0.5;
    *(float *)(this + 0x180) = fVar5 - 6.0;
    *(float *)(this + 0x184) = (fVar5 + 32.0) - 6.0;
    *(float *)(pcVar2 + 0x230) = fVar8 + 33.0;
    RePosition(pcVar2);
    pcVar2 = *(cRBorder **)(this + 0x710);
    *(float *)(pcVar2 + 0x230) = *(float *)(this + 0x238) + fVar6;
    RePosition(pcVar2);
    pcVar2 = this + 0x238;
    this = *(cRBorder **)(this + 0x718);
    *(float *)(this + 0x6f0) = *(float *)pcVar2 + 52.0;
  } while( true );
}
