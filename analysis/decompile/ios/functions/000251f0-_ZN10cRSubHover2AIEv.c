/*
 * mangled: _ZN10cRSubHover2AIEv
 * demangled: cRSubHover::AI()
 * address: 000251f0
 * size: 628
 */

/* cRSubHover::AI() */

void __thiscall cRSubHover::AI(cRSubHover *this)

{
  byte bVar1;
  cRSubHover *pcVar2;
  int iVar3;
  uint in_fpscr;
  float fVar4;
  float fVar5;
  uint uVar6;
  float fVar7;
  float fVar8;
  float fVar9;

  if (*(int *)(this + 0xc) != 1) {
    return;
  }
  fVar5 = *(float *)this + *(float *)(this + 4);
  uVar6 = in_fpscr & 0xfffffff | (uint)(fVar5 < 1.0) << 0x1f | (uint)(fVar5 == 1.0) << 0x1e;
  *(float *)this = fVar5;
  bVar1 = (byte)(uVar6 >> 0x18);
  if (((bool)(bVar1 >> 6 & 1) || (bool)(bVar1 >> 7) != NAN(fVar5)) &&
     (fVar4 = (float)VectorSignedToFloat(*(int *)(*(int *)(this + 0x200) + 0x70) + -5,
                                         (byte)(uVar6 >> 0x16) & 3),
     *(float *)(*(int *)(this + 0x10) + 100) <= fVar4)) {
    if (fVar5 < 0.1) {
      *(float *)(this + 0x210) = fVar5 / 0.1;
    }
    else if (fVar5 <= 0.94) {
      *(undefined4 *)(this + 0x210) = 0x3f800000;
      uVar6 = (uint)*(float *)(*(int *)PTR__Game_001b60b8 + 0x82024);
      if (0xdaa < (int)uVar6) {
        uVar6 = 0xdab;
      }
      if ((*(uint *)(&DAT_00256d50 +
                    (uVar6 & ~((int)uVar6 >> 0x1f)) * 0xdc + *(int *)PTR__Game_001b60b8) & 0x8000)
          != 0) {
        *(undefined4 *)this = 0x3f70a3d7;
        wprintf("Auto Shutoff Jetpack\n");
      }
    }
    else {
      *(float *)(this + 0x210) = (1.0 - fVar5) / 0.06;
      if (fVar5 - *(float *)(this + 4) <= 0.94) {
        cRSnail::SetJetPack((cRSnail *)(*(int *)PTR__Game_001b60b8 + 0x847b8),0);
        cRSprite::Kill(*(cRSprite **)(this + 0x20));
        cRSprite::Kill(*(cRSprite **)(this + 0x30));
        iVar3 = 1;
        pcVar2 = this;
        do {
          cRSprite::Kill(*(cRSprite **)(pcVar2 + 0x40));
          iVar3 = iVar3 + 1;
          cRSprite::Kill(*(cRSprite **)(pcVar2 + 0x50));
          pcVar2 = pcVar2 + 0x20;
        } while (iVar3 != 0xf);
      }
    }
    fVar8 = 3.1415927;
    fVar9 = 0.25;
    fVar5 = (float)Cos(*(float *)(this + 0x210) * 3.1415927);
    fVar4 = 1.0 - (fVar5 * 0.5 + 0.5);
    *(float *)(this + 0x210) = fVar4;
    fVar5 = (float)Sin(*(float *)this * 8.0 * fVar8);
    fVar7 = *(float *)(this + 0x210);
    *(float *)(this + 0x14) = fVar4 * fVar5 * fVar9;
    fVar5 = (float)Sin(*(float *)this * 12.0 * fVar8);
    *(undefined4 *)(this + 0x1c) = 0;
    *(undefined4 *)(this + 0x20c) = *(undefined4 *)(this + 0x210);
    *(float *)(this + 0x18) = fVar7 + fVar7 * fVar5 * fVar9;
    return;
  }
  if (fVar5 < 0.94) {
    *(undefined4 *)this = 0x3f70a3d7;
  }
  else if (0.94 < fVar5) goto LAB_00025274;
  cRSnail::SetJetPack((cRSnail *)(*(int *)PTR__Game_001b60b8 + 0x847b8),0);
LAB_00025274:
  *(undefined4 *)(this + 0xc) = 0;
  *(undefined4 *)(this + 0x1c) = 0;
  *(undefined4 *)(this + 0x18) = 0;
  *(undefined4 *)(this + 0x14) = 0;
  return;
}
