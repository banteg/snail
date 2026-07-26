/*
 * mangled: _ZN8cRBorder4DrawEv
 * demangled: cRBorder::Draw()
 * address: 0005f5b0
 * size: 2704
 */

/* cRBorder::Draw() */

void __thiscall cRBorder::Draw(cRBorder *this)

{
  uint uVar1;
  undefined4 *puVar2;
  uint uVar3;
  cRBorder *pcVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  bool bVar8;
  float fVar9;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s1;
  float extraout_s1_00;
  float extraout_s2;
  float extraout_s2_00;
  float extraout_s3;
  float extraout_s3_00;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  undefined4 uVar20;
  undefined4 local_f0;
  undefined4 uStack_ec;
  undefined4 uStack_e8;
  undefined4 uStack_e4;
  float local_e0;
  float local_dc;
  float local_d8;
  float local_d4;
  uint local_d0;
  undefined4 local_cc;
  undefined4 *local_c4;
  undefined4 local_c0;
  undefined4 uStack_bc;
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  undefined4 local_b0;
  undefined4 uStack_ac;
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  tColour atStack_a0 [12];
  undefined4 local_94;
  tColour atStack_90 [16];
  undefined4 local_80;
  undefined4 uStack_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  tColour local_70 [12];
  undefined4 local_64;

  tColour::tColour(local_70);
  tColour::tColour((tColour *)&local_80);
  tColour::tColour(atStack_90);
  fVar9 = (float)tColour::tColour(atStack_a0);
  if ((G0RenderNextFlag == '\x01') && ((*(uint *)(this + 0x194) & 0x1000) == 0)) {
    bVar8 = (gConfig._28_4_ & 0x80) == 0;
    if (bVar8) {
      local_94 = 0x3f800000;
      local_64 = 0x3f800000;
    }
    uVar1 = (uint)!bVar8;
    fVar11 = *(float *)(this + 0x23c);
    fVar16 = *(float *)(this + 0x240);
    if ((*(uint *)(this + 0x194) & 0x100000) != 0) {
      fVar10 = *(float *)(this + 0x174);
      local_80 = *(undefined4 *)(this + 0x1d0);
      uStack_7c = *(undefined4 *)(this + 0x1d4);
      uStack_78 = *(undefined4 *)(this + 0x1d8);
      uStack_74 = *(undefined4 *)(this + 0x1dc);
      if (0.0 < fVar10) {
        local_e0 = (float)gSpriteReference._752_4_;
        local_dc = 1.0 - (float)gSpriteReference._764_4_;
        local_d8 = fVar10 * (float)gSpriteReference._760_4_ +
                   (float)gSpriteReference._752_4_ * (1.0 - fVar10);
        local_cc = 0;
        local_d4 = 1.0 - (float)gSpriteReference._756_4_;
        local_f0 = local_80;
        uStack_ec = uStack_7c;
        uStack_e8 = uStack_78;
        uStack_e4 = uStack_74;
        local_d0 = uVar1;
        fVar9 = (float)OSDPrintUV(0x17,(*(float *)(this + 0x234) + fVar11 * 0.5) - 128.0,
                                  *(float *)(this + 0x238) + 50.0,fVar10 * 256.0,0x42000000,
                                  0x1000000);
        fVar10 = *(float *)(this + 0x174);
      }
      if (fVar10 < 1.0) {
        local_d8 = (float)gSpriteReference._720_4_;
        local_f0 = local_80;
        uStack_ec = uStack_7c;
        uStack_e8 = uStack_78;
        uStack_e4 = uStack_74;
        local_e0 = (float)gSpriteReference._720_4_ * fVar10 +
                   (1.0 - fVar10) * (float)gSpriteReference._728_4_;
        local_dc = 1.0 - (float)gSpriteReference._732_4_;
        local_cc = 0;
        local_d4 = 1.0 - (float)gSpriteReference._724_4_;
        local_d0 = uVar1;
        fVar9 = (float)OSDPrintUV(0x16,((*(float *)(this + 0x234) + fVar11 * 0.5) - 128.0) +
                                       fVar10 * 256.0,*(float *)(this + 0x238) + 50.0,
                                  (1.0 - fVar10) * 256.0,0x42000000,0x1000000);
      }
    }
    if (this[0x50] == (cRBorder)0x0) {
      uVar3 = *(uint *)(this + 0x194);
      if ((uVar3 & 0x800) != 0) {
        fVar9 = *(float *)(this + 0x250);
        iVar7 = *(int *)(this + 0x268);
        local_c4 = &local_f0;
        local_f0 = *(undefined4 *)(this + 0x1d0);
        uStack_ec = *(undefined4 *)(this + 0x1d4);
        uStack_e8 = *(undefined4 *)(this + 0x1d8);
        uStack_e4 = *(undefined4 *)(this + 0x1dc);
        iVar6 = (iVar7 * 2 + 1) * 0x10;
        local_e0 = *(float *)(gSpriteReference + iVar6);
        local_d0 = *(uint *)(this + 0x26c);
        local_dc = 1.0 - *(float *)(gSpriteReference + iVar7 * 0x20 + 0x1c);
        local_d8 = *(float *)(gSpriteReference + iVar7 * 0x20 + 0x18);
        local_cc = 0;
        local_d4 = 1.0 - *(float *)(gSpriteReference + iVar6 + 4);
        OSDPrintUV(iVar7,fVar9 * -0.5 + *(float *)(this + 0x234),
                   fVar9 * -0.5 + *(float *)(this + 0x238),fVar9 + *(float *)(this + 0x248),
                   fVar9 + *(float *)(this + 0x24c),0x1000000);
        fVar9 = *(float *)(this + 0x16c);
        if (0.0 < fVar9) {
          fVar12 = *(float *)(this + 0x250);
          fVar10 = *(float *)(this + 0x234);
          fVar15 = *(float *)(this + 0x238);
          fVar13 = *(float *)(this + 0x248);
          uVar5 = *(undefined4 *)(this + 0x268);
          fVar14 = fVar12 + *(float *)(this + 0x24c);
          tColour::tColour((tColour *)&local_b0,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
          puVar2 = local_c4;
          uVar20 = 0x1000000;
          *local_c4 = local_b0;
          puVar2[1] = uStack_ac;
          puVar2[2] = uStack_a8;
          puVar2[3] = uStack_a4;
          local_d0 = 8;
          local_d4 = 1.0;
          local_cc = 0;
          local_e0 = 0.0;
          local_dc = 0.0;
          local_d8 = 1.0;
          OSDPrintUV(uVar5,fVar9 + fVar10 + fVar12 * -0.5,fVar12 * -0.5 + fVar9 + fVar15,
                     fVar12 + fVar13,fVar14,uVar20);
          uVar3 = *(uint *)(this + 0x194);
        }
        else {
          uVar3 = *(uint *)(this + 0x194);
        }
      }
      if ((uVar3 & 0x400000) == 0) {
        if (this[0x228] == (cRBorder)0x0) {
          fVar9 = *(float *)(this + 0x214);
          fVar10 = *(float *)(this + 0x224);
          if (fVar10 <= fVar9) {
            fVar15 = *(float *)(this + 0x234);
            fVar14 = *(float *)(this + 0x238);
            fVar13 = 0.8;
            fVar12 = 0.2;
          }
          else {
            fVar9 = fVar10 - fVar9;
            *(float *)(this + 0x220) = fVar9;
            fVar12 = fVar10 * 0.0078125;
            fVar16 = fVar16 + fVar9 * -2.0;
            fVar15 = fVar9 + *(float *)(this + 0x234);
            fVar14 = fVar9 + *(float *)(this + 0x238);
            fVar11 = fVar9 * -2.0 + fVar11;
            fVar13 = 1.0 - fVar12;
            fVar9 = fVar10;
          }
        }
        else {
          fVar13 = 0.9;
          fVar12 = 0.1;
          fVar15 = *(float *)(this + 0x234) + 4.0;
          fVar11 = fVar11 - 8.0;
          fVar14 = *(float *)(this + 0x238) + 3.0;
          fVar16 = fVar16 - 6.0;
          fVar9 = 4.0;
        }
        fVar18 = fVar15 - fVar9;
        pcVar4 = this + 0x1a0;
        local_f0 = *(undefined4 *)pcVar4;
        uStack_ec = *(undefined4 *)(this + 0x1a4);
        uStack_e8 = *(undefined4 *)(this + 0x1a8);
        uStack_e4 = *(undefined4 *)(this + 0x1ac);
        local_e0 = 0.0;
        local_dc = 0.0;
        local_cc = 0;
        fVar10 = fVar15 + fVar11;
        local_d8 = fVar12;
        local_d4 = fVar12;
        local_d0 = uVar1;
        OSDPrintUV(*(undefined4 *)(this + 0x3c),fVar18);
        local_f0 = *(undefined4 *)pcVar4;
        uStack_ec = *(undefined4 *)(this + 0x1a4);
        uStack_e8 = *(undefined4 *)(this + 0x1a8);
        uStack_e4 = *(undefined4 *)(this + 0x1ac);
        local_dc = 0.0;
        local_cc = 0;
        local_e0 = fVar12;
        local_d8 = fVar13;
        local_d4 = fVar12;
        local_d0 = uVar1;
        OSDPrintUV(*(undefined4 *)(this + 0x3c),fVar15);
        local_f0 = *(undefined4 *)pcVar4;
        uStack_ec = *(undefined4 *)(this + 0x1a4);
        uStack_e8 = *(undefined4 *)(this + 0x1a8);
        uStack_e4 = *(undefined4 *)(this + 0x1ac);
        fVar17 = fVar14 + fVar16;
        local_dc = 0.0;
        local_d8 = 1.0;
        local_cc = 0;
        local_e0 = fVar13;
        local_d4 = fVar12;
        local_d0 = uVar1;
        OSDPrintUV(*(undefined4 *)(this + 0x3c),fVar10,fVar14 - fVar9,fVar9,fVar9,0x1000000);
        local_f0 = *(undefined4 *)pcVar4;
        uStack_ec = *(undefined4 *)(this + 0x1a4);
        uStack_e8 = *(undefined4 *)(this + 0x1a8);
        uStack_e4 = *(undefined4 *)(this + 0x1ac);
        local_e0 = 0.0;
        local_cc = 0;
        local_dc = fVar12;
        local_d8 = fVar12;
        local_d4 = fVar13;
        local_d0 = uVar1;
        OSDPrintUV(*(undefined4 *)(this + 0x3c),fVar18,fVar14,fVar9,fVar16,0x1000000);
        local_f0 = *(undefined4 *)pcVar4;
        uStack_ec = *(undefined4 *)(this + 0x1a4);
        uStack_e8 = *(undefined4 *)(this + 0x1a8);
        uStack_e4 = *(undefined4 *)(this + 0x1ac);
        local_cc = 0;
        local_e0 = fVar12;
        local_dc = fVar12;
        local_d8 = fVar13;
        local_d4 = fVar13;
        local_d0 = uVar1;
        OSDPrintUV(*(undefined4 *)(this + 0x3c),fVar15,fVar14,fVar11,fVar16,0x1000000);
        local_f0 = *(undefined4 *)pcVar4;
        uStack_ec = *(undefined4 *)(this + 0x1a4);
        uStack_e8 = *(undefined4 *)(this + 0x1a8);
        uStack_e4 = *(undefined4 *)(this + 0x1ac);
        local_d8 = 1.0;
        local_cc = 0;
        local_e0 = fVar13;
        local_dc = fVar12;
        local_d4 = fVar13;
        local_d0 = uVar1;
        OSDPrintUV(*(undefined4 *)(this + 0x3c),fVar10,fVar14,fVar9,fVar16,0x1000000);
        local_f0 = *(undefined4 *)pcVar4;
        uStack_ec = *(undefined4 *)(this + 0x1a4);
        uStack_e8 = *(undefined4 *)(this + 0x1a8);
        uStack_e4 = *(undefined4 *)(this + 0x1ac);
        local_e0 = 0.0;
        local_d4 = 1.0;
        local_cc = 0;
        local_dc = fVar13;
        local_d8 = fVar12;
        local_d0 = uVar1;
        OSDPrintUV(*(undefined4 *)(this + 0x3c),fVar18,fVar17,fVar9,fVar9,0x1000000);
        local_f0 = *(undefined4 *)pcVar4;
        uStack_ec = *(undefined4 *)(this + 0x1a4);
        uStack_e8 = *(undefined4 *)(this + 0x1a8);
        uStack_e4 = *(undefined4 *)(this + 0x1ac);
        local_d4 = 1.0;
        local_cc = 0;
        local_e0 = fVar12;
        local_dc = fVar13;
        local_d8 = fVar13;
        local_d0 = uVar1;
        OSDPrintUV(*(undefined4 *)(this + 0x3c),fVar15,fVar17,fVar11,fVar9,0x1000000);
        local_f0 = *(undefined4 *)pcVar4;
        uStack_ec = *(undefined4 *)(this + 0x1a4);
        uStack_e8 = *(undefined4 *)(this + 0x1a8);
        uStack_e4 = *(undefined4 *)(this + 0x1ac);
        local_d8 = 1.0;
        local_d4 = 1.0;
        local_cc = 0;
        local_e0 = fVar13;
        local_dc = fVar13;
        local_d0 = uVar1;
        OSDPrintUV(*(undefined4 *)(this + 0x3c),fVar10,fVar17,fVar9,fVar9,0x1000000);
        if ((*(char *)(Game + 0x43df8) != '\0') && (*(cRBorder **)(Game + 0x43e04) == this)) {
          tColour::tColour((tColour *)&local_c0);
          tColour::White();
          tColour::Set((tColour *)&local_c0,extraout_s0_00,extraout_s1_00,extraout_s2_00,
                       extraout_s3_00);
          fVar9 = (*(float *)(Game + 0x43dfc) * 0.7 + 1.0) * fVar9;
          fVar19 = fVar15 - fVar9;
          local_f0 = local_c0;
          uStack_ec = uStack_bc;
          uStack_e8 = uStack_b8;
          uStack_e4 = uStack_b4;
          local_e0 = 0.0;
          local_dc = 0.0;
          local_d0 = 1;
          local_cc = 0;
          fVar18 = fVar14 - fVar9;
          local_d8 = fVar12;
          local_d4 = fVar12;
          OSDPrintUV(0x57,fVar19,fVar18,fVar9,fVar9,0x1000000);
          local_f0 = local_c0;
          uStack_ec = uStack_bc;
          uStack_e8 = uStack_b8;
          uStack_e4 = uStack_b4;
          local_dc = 0.0;
          local_d0 = 1;
          local_cc = 0;
          local_e0 = fVar12;
          local_d8 = fVar13;
          local_d4 = fVar12;
          OSDPrintUV(0x57,fVar15,fVar18,fVar11,fVar9,0x1000000);
          local_f0 = local_c0;
          uStack_ec = uStack_bc;
          uStack_e8 = uStack_b8;
          uStack_e4 = uStack_b4;
          local_dc = 0.0;
          local_d8 = 1.0;
          local_d0 = 1;
          local_cc = 0;
          local_e0 = fVar13;
          local_d4 = fVar12;
          OSDPrintUV(0x57,fVar10,fVar18,fVar9,fVar9,0x1000000);
          local_f0 = local_c0;
          uStack_ec = uStack_bc;
          uStack_e8 = uStack_b8;
          uStack_e4 = uStack_b4;
          local_e0 = 0.0;
          local_d0 = 1;
          local_cc = 0;
          local_dc = fVar12;
          local_d8 = fVar12;
          local_d4 = fVar13;
          OSDPrintUV(0x57,fVar19,fVar14,fVar9,fVar16,0x1000000);
          local_f0 = local_c0;
          uStack_ec = uStack_bc;
          uStack_e8 = uStack_b8;
          uStack_e4 = uStack_b4;
          local_d8 = 1.0;
          local_d0 = 1;
          local_cc = 0;
          local_e0 = fVar13;
          local_dc = fVar12;
          local_d4 = fVar13;
          OSDPrintUV(0x57,fVar10,fVar14,fVar9,fVar16,0x1000000);
          local_f0 = local_c0;
          uStack_ec = uStack_bc;
          uStack_e8 = uStack_b8;
          uStack_e4 = uStack_b4;
          local_e0 = 0.0;
          local_d4 = 1.0;
          local_d0 = 1;
          local_cc = 0;
          local_dc = fVar13;
          local_d8 = fVar12;
          OSDPrintUV(0x57,fVar19,fVar17,fVar9,fVar9,0x1000000);
          local_f0 = local_c0;
          uStack_ec = uStack_bc;
          uStack_e8 = uStack_b8;
          uStack_e4 = uStack_b4;
          local_d4 = 1.0;
          local_d0 = 1;
          local_cc = 0;
          local_e0 = fVar12;
          local_dc = fVar13;
          local_d8 = fVar13;
          OSDPrintUV(0x57,fVar15,fVar17,fVar11,fVar9,0x1000000);
          local_f0 = local_c0;
          uStack_ec = uStack_bc;
          uStack_e8 = uStack_b8;
          uStack_e4 = uStack_b4;
          local_d4 = 1.0;
          local_d0 = 1;
          local_cc = 0;
          local_d8 = 1.0;
          local_e0 = fVar13;
          local_dc = fVar13;
          OSDPrintUV(0x57,fVar10,fVar17,fVar9,fVar9,0x1000000);
        }
      }
    }
    else {
      if ((*(char *)(Game + 0x43df8) == '\0') || (*(cRBorder **)(Game + 0x43e04) != this)) {
        fVar9 = 0.0;
      }
      else {
        fVar9 = (float)Sin(fVar9);
        fVar9 = fVar9 * 3.0;
        if (this[0x51] == (cRBorder)0x0) {
          fVar9 = -fVar9;
        }
      }
      bVar8 = (*(uint *)(this + 0x194) & 2) != 0;
      if (bVar8) {
        fVar16 = *(float *)(this + 0x250);
        fVar11 = fVar16 + *(float *)(this + 0x24c);
        iVar6 = *(int *)(this + 0x54);
      }
      else {
        fVar16 = *(float *)(this + 0x250);
        fVar11 = *(float *)(this + 0x24c);
        iVar6 = *(int *)(this + 0x268);
      }
      local_f0 = *(undefined4 *)(this + 0x1d0);
      uStack_ec = *(undefined4 *)(this + 0x1d4);
      uStack_e8 = *(undefined4 *)(this + 0x1d8);
      uStack_e4 = *(undefined4 *)(this + 0x1dc);
      iVar7 = (iVar6 * 2 + 1) * 0x10;
      if (!bVar8) {
        fVar11 = fVar16 + fVar11;
      }
      local_e0 = *(float *)(gSpriteReference + iVar7);
      local_d0 = *(uint *)(this + 0x26c);
      local_dc = 1.0 - *(float *)(gSpriteReference + iVar6 * 0x20 + 0x1c);
      local_d8 = *(float *)(gSpriteReference + iVar6 * 0x20 + 0x18);
      local_cc = 0;
      local_d4 = 1.0 - *(float *)(gSpriteReference + iVar7 + 4);
      OSDPrintUV(iVar6,fVar9 + *(float *)(this + 0x234) + fVar16 * -0.5,
                 fVar16 * -0.5 + *(float *)(this + 0x238),fVar16 + *(float *)(this + 0x248),fVar11,
                 0x1000000);
    }
  }
  return;
}
