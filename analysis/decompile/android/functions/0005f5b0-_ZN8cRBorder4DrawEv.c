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
  uint uVar2;
  int iVar3;
  int *piVar4;
  cRBorder *pcVar5;
  undefined4 *puVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  bool bVar10;
  float fVar11;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s1;
  float extraout_s1_00;
  float extraout_s2;
  float extraout_s2_00;
  float extraout_s3;
  float extraout_s3_00;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  undefined4 uVar24;
  undefined4 local_f0;
  undefined4 uStack_ec;
  undefined4 uStack_e8;
  undefined4 uStack_e4;
  float local_e0;
  float local_dc;
  float local_d8;
  float local_d4;
  uint local_d0;
  float local_cc;
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
  float local_94;
  tColour atStack_90 [16];
  undefined4 local_80;
  undefined4 uStack_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  tColour local_70 [12];
  float local_64;

  tColour::tColour(local_70);
  tColour::tColour((tColour *)&local_80);
  tColour::tColour(atStack_90);
  iVar3 = DAT_0005fa24;
  fVar11 = (float)tColour::tColour(atStack_a0);
  iVar3 = iVar3 + 0x5f5f8;
  if ((**(char **)(iVar3 + DAT_0005fa28) == '\x01') && ((*(uint *)(this + 0x194) & 0x1000) == 0)) {
    bVar10 = (*(uint *)(*(int *)(iVar3 + DAT_0005fa2c) + 0x1c) & 0x80) == 0;
    if (bVar10) {
      local_94 = DAT_0005fa0c;
      local_64 = DAT_0005fa0c;
    }
    uVar1 = (uint)!bVar10;
    fVar14 = *(float *)(this + 0x23c);
    fVar18 = *(float *)(this + 0x240);
    if ((*(uint *)(this + 0x194) & 0x100000) != 0) {
      fVar12 = *(float *)(this + 0x174);
      local_80 = *(undefined4 *)(this + 0x1d0);
      uStack_7c = *(undefined4 *)(this + 0x1d4);
      uStack_78 = *(undefined4 *)(this + 0x1d8);
      uStack_74 = *(undefined4 *)(this + 0x1dc);
      if (0.0 < fVar12) {
        iVar8 = *(int *)(iVar3 + DAT_0005fa34);
        local_e0 = *(float *)(iVar8 + 0x2f0);
        local_dc = DAT_0005fa5c - *(float *)(iVar8 + 0x2fc);
        local_d8 = fVar12 * *(float *)(iVar8 + 0x2f8) + local_e0 * (DAT_0005fa5c - fVar12);
        local_cc = DAT_0005fa48;
        local_d4 = DAT_0005fa5c - *(float *)(iVar8 + 0x2f4);
        local_f0 = local_80;
        uStack_ec = uStack_7c;
        uStack_e8 = uStack_78;
        uStack_e4 = uStack_74;
        local_d0 = uVar1;
        fVar11 = (float)OSDPrintUV(0x17,(*(float *)(this + 0x234) + fVar14 * DAT_0005fa44) -
                                        DAT_0005fa50,DAT_0005fa54 + *(float *)(this + 0x238),
                                   fVar12 * DAT_0005fa4c,DAT_0005fa40,0x1000000);
        fVar12 = *(float *)(this + 0x174);
      }
      if (fVar12 < DAT_0005fa0c) {
        iVar8 = *(int *)(iVar3 + DAT_0005fa34);
        local_d8 = *(float *)(iVar8 + 0x2d0);
        local_f0 = local_80;
        uStack_ec = uStack_7c;
        uStack_e8 = uStack_78;
        uStack_e4 = uStack_74;
        local_e0 = local_d8 * fVar12 + (DAT_0005fa0c - fVar12) * *(float *)(iVar8 + 0x2d8);
        local_dc = DAT_0005fa0c - *(float *)(iVar8 + 0x2dc);
        local_cc = DAT_0005fa48;
        local_d4 = DAT_0005fa0c - *(float *)(iVar8 + 0x2d4);
        local_d0 = uVar1;
        fVar11 = (float)OSDPrintUV(0x16,((*(float *)(this + 0x234) + fVar14 * DAT_0005fa44) -
                                        DAT_0005fa50) + fVar12 * DAT_0005fa4c,
                                   DAT_0005fa54 + *(float *)(this + 0x238),
                                   (DAT_0005fa0c - fVar12) * DAT_0005fa4c,DAT_0005fa40,0x1000000);
      }
    }
    fVar21 = DAT_0005fa5c;
    fVar12 = DAT_0005fa58;
    if (this[0x50] == (cRBorder)0x0) {
      uVar2 = *(uint *)(this + 0x194);
      if ((uVar2 & 0x800) != 0) {
        fVar11 = *(float *)(this + 0x250);
        iVar8 = *(int *)(this + 0x268);
        local_c4 = &local_f0;
        local_f0 = *(undefined4 *)(this + 0x1d0);
        uStack_ec = *(undefined4 *)(this + 0x1d4);
        uStack_e8 = *(undefined4 *)(this + 0x1d8);
        uStack_e4 = *(undefined4 *)(this + 0x1dc);
        iVar9 = *(int *)(iVar3 + DAT_0005fa34) + iVar8 * 0x20;
        puVar6 = (undefined4 *)(*(int *)(iVar3 + DAT_0005fa34) + (iVar8 * 2 + 1) * 0x10);
        local_e0 = (float)*puVar6;
        local_d0 = *(uint *)(this + 0x26c);
        local_dc = DAT_0005fa5c - *(float *)(iVar9 + 0x1c);
        local_d8 = *(float *)(iVar9 + 0x18);
        local_cc = 0.0;
        local_d4 = DAT_0005fa5c - (float)puVar6[1];
        OSDPrintUV(iVar8,fVar11 * DAT_0005fa58 + *(float *)(this + 0x234),
                   fVar11 * DAT_0005fa58 + *(float *)(this + 0x238),
                   fVar11 + *(float *)(this + 0x248),fVar11 + *(float *)(this + 0x24c),0x1000000);
        fVar11 = *(float *)(this + 0x16c);
        if (0.0 < fVar11) {
          fVar15 = *(float *)(this + 0x250);
          fVar13 = *(float *)(this + 0x234);
          fVar19 = *(float *)(this + 0x238);
          fVar16 = *(float *)(this + 0x248);
          uVar7 = *(undefined4 *)(this + 0x268);
          fVar17 = fVar15 + *(float *)(this + 0x24c);
          tColour::tColour((tColour *)&local_b0,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
          puVar6 = local_c4;
          uVar24 = 0x1000000;
          *local_c4 = local_b0;
          puVar6[1] = uStack_ac;
          puVar6[2] = uStack_a8;
          puVar6[3] = uStack_a4;
          local_d0 = 8;
          local_d4 = fVar21;
          local_cc = 0.0;
          local_e0 = 0.0;
          local_dc = 0.0;
          local_d8 = fVar21;
          OSDPrintUV(uVar7,fVar11 + fVar13 + fVar15 * fVar12,fVar15 * fVar12 + fVar11 + fVar19,
                     fVar15 + fVar16,fVar17,uVar24);
          uVar2 = *(uint *)(this + 0x194);
        }
        else {
          uVar2 = *(uint *)(this + 0x194);
        }
      }
      fVar12 = DAT_0005fa5c;
      fVar11 = DAT_0005fa38;
      if ((uVar2 & 0x400000) == 0) {
        if (this[0x228] == (cRBorder)0x0) {
          fVar21 = *(float *)(this + 0x214);
          fVar13 = *(float *)(this + 0x224);
          if (fVar13 <= fVar21) {
            fVar17 = *(float *)(this + 0x234);
            fVar16 = *(float *)(this + 0x238);
            fVar15 = DAT_0005fa64;
            fVar12 = DAT_0005fa60;
          }
          else {
            fVar21 = fVar13 - fVar21;
            *(float *)(this + 0x220) = fVar21;
            fVar15 = fVar13 * DAT_0005fa3c;
            fVar18 = fVar18 + fVar21 * fVar11;
            fVar17 = fVar21 + *(float *)(this + 0x234);
            fVar16 = fVar21 + *(float *)(this + 0x238);
            fVar14 = fVar21 * fVar11 + fVar14;
            fVar12 = fVar12 - fVar15;
            fVar21 = fVar13;
          }
        }
        else {
          fVar17 = DAT_0005fa10 + *(float *)(this + 0x234);
          fVar14 = fVar14 - DAT_0005fa18;
          fVar16 = DAT_0005fa14 + *(float *)(this + 0x238);
          fVar18 = fVar18 - DAT_0005fa20;
          fVar15 = DAT_0005fa1c;
          fVar12 = DAT_0005fa68;
          fVar21 = DAT_0005fa10;
        }
        fVar13 = DAT_0005fa48;
        fVar11 = DAT_0005fa0c;
        fVar22 = fVar17 - fVar21;
        pcVar5 = this + 0x1a0;
        local_f0 = *(undefined4 *)pcVar5;
        uStack_ec = *(undefined4 *)(this + 0x1a4);
        uStack_e8 = *(undefined4 *)(this + 0x1a8);
        uStack_e4 = *(undefined4 *)(this + 0x1ac);
        local_e0 = DAT_0005fa48;
        local_dc = DAT_0005fa48;
        local_cc = DAT_0005fa48;
        fVar19 = fVar17 + fVar14;
        local_d8 = fVar15;
        local_d4 = fVar15;
        local_d0 = uVar1;
        OSDPrintUV(*(undefined4 *)(this + 0x3c),fVar22);
        local_f0 = *(undefined4 *)pcVar5;
        uStack_ec = *(undefined4 *)(this + 0x1a4);
        uStack_e8 = *(undefined4 *)(this + 0x1a8);
        uStack_e4 = *(undefined4 *)(this + 0x1ac);
        local_dc = fVar13;
        local_cc = fVar13;
        local_e0 = fVar15;
        local_d8 = fVar12;
        local_d4 = fVar15;
        local_d0 = uVar1;
        OSDPrintUV(*(undefined4 *)(this + 0x3c),fVar17);
        local_f0 = *(undefined4 *)pcVar5;
        uStack_ec = *(undefined4 *)(this + 0x1a4);
        uStack_e8 = *(undefined4 *)(this + 0x1a8);
        uStack_e4 = *(undefined4 *)(this + 0x1ac);
        fVar20 = fVar16 + fVar18;
        local_dc = fVar13;
        local_d8 = fVar11;
        local_cc = fVar13;
        local_e0 = fVar12;
        local_d4 = fVar15;
        local_d0 = uVar1;
        OSDPrintUV(*(undefined4 *)(this + 0x3c),fVar19,fVar16 - fVar21,fVar21,fVar21,0x1000000);
        local_f0 = *(undefined4 *)pcVar5;
        uStack_ec = *(undefined4 *)(this + 0x1a4);
        uStack_e8 = *(undefined4 *)(this + 0x1a8);
        uStack_e4 = *(undefined4 *)(this + 0x1ac);
        local_e0 = fVar13;
        local_cc = fVar13;
        local_dc = fVar15;
        local_d8 = fVar15;
        local_d4 = fVar12;
        local_d0 = uVar1;
        OSDPrintUV(*(undefined4 *)(this + 0x3c),fVar22,fVar16,fVar21,fVar18,0x1000000);
        local_f0 = *(undefined4 *)pcVar5;
        uStack_ec = *(undefined4 *)(this + 0x1a4);
        uStack_e8 = *(undefined4 *)(this + 0x1a8);
        uStack_e4 = *(undefined4 *)(this + 0x1ac);
        local_cc = fVar13;
        local_e0 = fVar15;
        local_dc = fVar15;
        local_d8 = fVar12;
        local_d4 = fVar12;
        local_d0 = uVar1;
        OSDPrintUV(*(undefined4 *)(this + 0x3c),fVar17,fVar16,fVar14,fVar18,0x1000000);
        local_f0 = *(undefined4 *)pcVar5;
        uStack_ec = *(undefined4 *)(this + 0x1a4);
        uStack_e8 = *(undefined4 *)(this + 0x1a8);
        uStack_e4 = *(undefined4 *)(this + 0x1ac);
        local_d8 = fVar11;
        local_cc = fVar13;
        local_e0 = fVar12;
        local_dc = fVar15;
        local_d4 = fVar12;
        local_d0 = uVar1;
        OSDPrintUV(*(undefined4 *)(this + 0x3c),fVar19,fVar16,fVar21,fVar18,0x1000000);
        local_f0 = *(undefined4 *)pcVar5;
        uStack_ec = *(undefined4 *)(this + 0x1a4);
        uStack_e8 = *(undefined4 *)(this + 0x1a8);
        uStack_e4 = *(undefined4 *)(this + 0x1ac);
        local_e0 = fVar13;
        local_d4 = fVar11;
        local_cc = fVar13;
        local_dc = fVar12;
        local_d8 = fVar15;
        local_d0 = uVar1;
        OSDPrintUV(*(undefined4 *)(this + 0x3c),fVar22,fVar20,fVar21,fVar21,0x1000000);
        local_f0 = *(undefined4 *)pcVar5;
        uStack_ec = *(undefined4 *)(this + 0x1a4);
        uStack_e8 = *(undefined4 *)(this + 0x1a8);
        uStack_e4 = *(undefined4 *)(this + 0x1ac);
        local_d4 = fVar11;
        local_cc = fVar13;
        local_e0 = fVar15;
        local_dc = fVar12;
        local_d8 = fVar12;
        local_d0 = uVar1;
        OSDPrintUV(*(undefined4 *)(this + 0x3c),fVar17,fVar20,fVar14,fVar21,0x1000000);
        local_f0 = *(undefined4 *)pcVar5;
        uStack_ec = *(undefined4 *)(this + 0x1a4);
        uStack_e8 = *(undefined4 *)(this + 0x1a8);
        uStack_e4 = *(undefined4 *)(this + 0x1ac);
        local_d8 = fVar11;
        local_d4 = fVar11;
        local_cc = fVar13;
        local_e0 = fVar12;
        local_dc = fVar12;
        local_d0 = uVar1;
        OSDPrintUV(*(undefined4 *)(this + 0x3c),fVar19,fVar20,fVar21,fVar21,0x1000000);
        piVar4 = *(int **)(iVar3 + DAT_0005fa30);
        iVar3 = *piVar4;
        if ((*(char *)(iVar3 + 0x43df8) != '\0') && (*(cRBorder **)(iVar3 + 0x43e04) == this)) {
          tColour::tColour((tColour *)&local_c0);
          tColour::White();
          tColour::Set((tColour *)&local_c0,extraout_s0_00,extraout_s1_00,extraout_s2_00,
                       extraout_s3_00);
          fVar21 = (fVar11 + DAT_000600a0 * *(float *)(*piVar4 + 0x43dfc)) * fVar21;
          fVar23 = fVar17 - fVar21;
          local_f0 = local_c0;
          uStack_ec = uStack_bc;
          uStack_e8 = uStack_b8;
          uStack_e4 = uStack_b4;
          local_e0 = fVar13;
          local_dc = fVar13;
          local_d0 = 1;
          local_cc = fVar13;
          fVar22 = fVar16 - fVar21;
          local_d8 = fVar15;
          local_d4 = fVar15;
          OSDPrintUV(0x57,fVar23,fVar22,fVar21,fVar21,0x1000000);
          local_f0 = local_c0;
          uStack_ec = uStack_bc;
          uStack_e8 = uStack_b8;
          uStack_e4 = uStack_b4;
          local_dc = fVar13;
          local_d0 = 1;
          local_cc = fVar13;
          local_e0 = fVar15;
          local_d8 = fVar12;
          local_d4 = fVar15;
          OSDPrintUV(0x57,fVar17,fVar22,fVar14,fVar21,0x1000000);
          local_f0 = local_c0;
          uStack_ec = uStack_bc;
          uStack_e8 = uStack_b8;
          uStack_e4 = uStack_b4;
          local_dc = fVar13;
          local_d8 = fVar11;
          local_d0 = 1;
          local_cc = fVar13;
          local_e0 = fVar12;
          local_d4 = fVar15;
          OSDPrintUV(0x57,fVar19,fVar22,fVar21,fVar21,0x1000000);
          local_f0 = local_c0;
          uStack_ec = uStack_bc;
          uStack_e8 = uStack_b8;
          uStack_e4 = uStack_b4;
          local_e0 = fVar13;
          local_d0 = 1;
          local_cc = fVar13;
          local_dc = fVar15;
          local_d8 = fVar15;
          local_d4 = fVar12;
          OSDPrintUV(0x57,fVar23,fVar16,fVar21,fVar18,0x1000000);
          local_f0 = local_c0;
          uStack_ec = uStack_bc;
          uStack_e8 = uStack_b8;
          uStack_e4 = uStack_b4;
          local_d8 = fVar11;
          local_d0 = 1;
          local_cc = fVar13;
          local_e0 = fVar12;
          local_dc = fVar15;
          local_d4 = fVar12;
          OSDPrintUV(0x57,fVar19,fVar16,fVar21,fVar18,0x1000000);
          local_f0 = local_c0;
          uStack_ec = uStack_bc;
          uStack_e8 = uStack_b8;
          uStack_e4 = uStack_b4;
          local_e0 = fVar13;
          local_d4 = fVar11;
          local_d0 = 1;
          local_cc = fVar13;
          local_dc = fVar12;
          local_d8 = fVar15;
          OSDPrintUV(0x57,fVar23,fVar20,fVar21,fVar21,0x1000000);
          local_f0 = local_c0;
          uStack_ec = uStack_bc;
          uStack_e8 = uStack_b8;
          uStack_e4 = uStack_b4;
          local_d4 = fVar11;
          local_d0 = 1;
          local_cc = fVar13;
          local_e0 = fVar15;
          local_dc = fVar12;
          local_d8 = fVar12;
          OSDPrintUV(0x57,fVar17,fVar20,fVar14,fVar21,0x1000000);
          local_f0 = local_c0;
          uStack_ec = uStack_bc;
          uStack_e8 = uStack_b8;
          uStack_e4 = uStack_b4;
          local_d4 = fVar11;
          local_d0 = 1;
          local_cc = fVar13;
          local_d8 = fVar11;
          local_e0 = fVar12;
          local_dc = fVar12;
          OSDPrintUV(0x57,fVar19,fVar20,fVar21,fVar21,0x1000000);
        }
      }
    }
    else {
      fVar14 = DAT_0005fa48;
      if ((*(char *)(**(int **)(iVar3 + DAT_0005fa30) + 0x43df8) != '\0') &&
         (*(cRBorder **)(**(int **)(iVar3 + DAT_0005fa30) + 0x43e04) == this)) {
        fVar14 = (float)Sin(fVar11);
        fVar14 = fVar14 * DAT_000600a8;
        if (this[0x51] == (cRBorder)0x0) {
          fVar14 = -fVar14;
        }
      }
      bVar10 = (*(uint *)(this + 0x194) & 2) != 0;
      if (bVar10) {
        fVar18 = *(float *)(this + 0x250);
        fVar11 = fVar18 + *(float *)(this + 0x24c);
        iVar8 = *(int *)(this + 0x54);
      }
      else {
        fVar18 = *(float *)(this + 0x250);
        fVar11 = *(float *)(this + 0x24c);
        iVar8 = *(int *)(this + 0x268);
      }
      local_f0 = *(undefined4 *)(this + 0x1d0);
      uStack_ec = *(undefined4 *)(this + 0x1d4);
      uStack_e8 = *(undefined4 *)(this + 0x1d8);
      uStack_e4 = *(undefined4 *)(this + 0x1dc);
      iVar9 = *(int *)(iVar3 + DAT_0005fa34) + iVar8 * 0x20;
      puVar6 = (undefined4 *)(*(int *)(iVar3 + DAT_0005fa34) + (iVar8 * 2 + 1) * 0x10);
      if (!bVar10) {
        fVar11 = fVar18 + fVar11;
      }
      local_e0 = (float)*puVar6;
      local_d0 = *(uint *)(this + 0x26c);
      local_dc = DAT_0005fa5c - *(float *)(iVar9 + 0x1c);
      local_d8 = *(float *)(iVar9 + 0x18);
      local_cc = DAT_0005fa48;
      local_d4 = DAT_0005fa5c - (float)puVar6[1];
      OSDPrintUV(iVar8,fVar14 + *(float *)(this + 0x234) + fVar18 * DAT_0005fa58,
                 fVar18 * DAT_0005fa58 + *(float *)(this + 0x238),fVar18 + *(float *)(this + 0x248),
                 fVar11,0x1000000);
    }
  }
  return;
}
