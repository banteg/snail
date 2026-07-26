/*
 * mangled: _ZN8cRBorder4DrawEv
 * demangled: cRBorder::Draw()
 * address: 000391a0
 * size: 2720
 */

/* cRBorder::Draw() */

void __thiscall cRBorder::Draw(cRBorder *this)

{
  undefined *puVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  uint uVar7;
  cRBorder *pcVar8;
  bool bVar9;
  float fVar10;
  float fVar11;
  undefined1 *puVar12;
  float fVar13;
  float fVar14;
  undefined1 *puVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  undefined4 local_b0;
  undefined4 uStack_ac;
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  undefined4 local_a0;
  undefined4 uStack_9c;
  undefined4 uStack_98;
  undefined4 uStack_94;
  tColour atStack_90 [12];
  undefined4 local_84;
  tColour atStack_80 [16];
  undefined4 local_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  float local_60;
  float local_5c;
  float local_58;
  undefined4 local_54;

  tColour::tColour((tColour *)&local_60);
  tColour::tColour((tColour *)&local_70);
  tColour::tColour(atStack_80);
  tColour::tColour(atStack_90);
  if ((*PTR__G0RenderNextFlag_001b60f4 != '\0') && ((*(uint *)(this + 0x194) & 0x1000) == 0)) {
    bVar9 = (*(uint *)(PTR__gConfig_001b60d4 + 0x1c) & 0x80) == 0;
    if (bVar9) {
      local_54 = 0x3f800000;
      local_84 = 0x3f800000;
    }
    bVar9 = !bVar9;
    fVar17 = *(float *)(this + 0x23c);
    fVar16 = *(float *)(this + 0x240);
    if ((*(uint *)(this + 0x194) & 0x100000) != 0) {
      local_70 = *(undefined4 *)(this + 0x1d0);
      uStack_6c = *(undefined4 *)(this + 0x1d4);
      uStack_68 = *(undefined4 *)(this + 0x1d8);
      uStack_64 = *(undefined4 *)(this + 0x1dc);
      fVar10 = *(float *)(this + 0x174);
      if (0.0 < fVar10) {
        OSDPrintUV(0x17,(*(float *)(this + 0x234) + fVar17 * 0.5) - 128.0,
                   *(float *)(this + 0x238) + 50.0,fVar10 * 256.0,0x42000000,0x1000000,local_70,
                   uStack_6c,uStack_68,uStack_64,*(float *)(PTR__gSpriteReference_001b61c8 + 0x2f0),
                   1.0 - *(float *)(PTR__gSpriteReference_001b61c8 + 0x2fc),
                   fVar10 * *(float *)(PTR__gSpriteReference_001b61c8 + 0x2f8) +
                   *(float *)(PTR__gSpriteReference_001b61c8 + 0x2f0) * (1.0 - fVar10),
                   1.0 - *(float *)(PTR__gSpriteReference_001b61c8 + 0x2f4),bVar9,0);
        fVar10 = *(float *)(this + 0x174);
      }
      if (fVar10 < 1.0) {
        OSDPrintUV(0x16,((*(float *)(this + 0x234) + fVar17 * 0.5) - 128.0) + fVar10 * 256.0,
                   *(float *)(this + 0x238) + 50.0,(1.0 - fVar10) * 256.0,0x42000000,0x1000000,
                   local_70,uStack_6c,uStack_68,uStack_64,
                   *(float *)(PTR__gSpriteReference_001b61c8 + 0x2d0) * fVar10 +
                   (1.0 - fVar10) * *(float *)(PTR__gSpriteReference_001b61c8 + 0x2d8),
                   1.0 - *(float *)(PTR__gSpriteReference_001b61c8 + 0x2dc),
                   *(float *)(PTR__gSpriteReference_001b61c8 + 0x2d0),
                   1.0 - *(float *)(PTR__gSpriteReference_001b61c8 + 0x2d4),bVar9,0);
      }
    }
    if (this[0x50] == (cRBorder)0x0) {
      uVar7 = *(uint *)(this + 0x194);
      if ((uVar7 & 0x800) != 0) {
        fVar10 = *(float *)(this + 0x250);
        iVar4 = *(int *)(this + 0x268);
        uVar2 = 0x3f800000;
        fVar11 = -0.5;
        OSDPrintUV(iVar4,fVar10 * -0.5 + *(float *)(this + 0x234),
                   fVar10 * -0.5 + *(float *)(this + 0x238),fVar10 + *(float *)(this + 0x248),
                   fVar10 + *(float *)(this + 0x24c),0x1000000,*(undefined4 *)(this + 0x1d0),
                   *(undefined4 *)(this + 0x1d4),*(undefined4 *)(this + 0x1d8),
                   *(undefined4 *)(this + 0x1dc),
                   *(undefined4 *)(PTR__gSpriteReference_001b61c8 + iVar4 * 0x20 + 0x10),
                   1.0 - *(float *)(PTR__gSpriteReference_001b61c8 + iVar4 * 0x20 + 0x1c),
                   *(undefined4 *)(PTR__gSpriteReference_001b61c8 + iVar4 * 0x20 + 0x18),
                   1.0 - *(float *)(PTR__gSpriteReference_001b61c8 + iVar4 * 0x20 + 0x14),
                   *(undefined4 *)(this + 0x26c),0);
        fVar10 = *(float *)(this + 0x16c);
        if (0.0 < fVar10) {
          fVar14 = *(float *)(this + 0x250);
          uVar3 = *(undefined4 *)(this + 0x268);
          fVar13 = fVar10 + *(float *)(this + 0x234) + fVar14 * fVar11;
          fVar11 = fVar14 * fVar11 + fVar10 + *(float *)(this + 0x238);
          fVar10 = fVar14 + *(float *)(this + 0x248);
          fVar14 = fVar14 + *(float *)(this + 0x24c);
          tColour::tColour((tColour *)&local_a0,0.0,0.0,0.0,0.9);
          OSDPrintUV(uVar3,fVar13,fVar11,fVar10,fVar14,0x1000000,local_a0,uStack_9c,uStack_98,
                     uStack_94,0,0,uVar2,uVar2,8,0);
        }
        uVar7 = *(uint *)(this + 0x194);
      }
      if ((uVar7 & 0x400000) == 0) {
        if (this[0x228] == (cRBorder)0x0) {
          puVar15 = *(undefined1 **)(this + 0x214);
          puVar12 = *(undefined1 **)(this + 0x224);
          if ((float)puVar12 <= (float)puVar15) {
            fVar13 = *(float *)(this + 0x234);
            fVar14 = *(float *)(this + 0x238);
            fVar10 = 0.2;
            fVar11 = 0.8;
          }
          else {
            fVar10 = (float)puVar12 - (float)puVar15;
            fVar13 = fVar10 + *(float *)(this + 0x234);
            *(float *)(this + 0x220) = fVar10;
            fVar14 = fVar10 + *(float *)(this + 0x238);
            fVar17 = fVar10 * -2.0 + fVar17;
            fVar16 = fVar16 + fVar10 * -2.0;
            fVar10 = (float)puVar12 * 0.0078125;
            fVar11 = 1.0 - fVar10;
            puVar15 = puVar12;
          }
        }
        else {
          fVar10 = 0.1;
          fVar11 = 0.9;
          fVar13 = *(float *)(this + 0x234) + 4.0;
          fVar14 = *(float *)(this + 0x238) + 3.0;
          fVar17 = fVar17 - 8.0;
          fVar16 = fVar16 - 6.0;
          puVar15 = &DAT_40800000;
        }
        fVar18 = fVar14 - (float)puVar15;
        fVar20 = fVar13 - (float)puVar15;
        pcVar8 = this + 0x1a0;
        fVar22 = fVar13 + fVar17;
        fVar19 = 1.0;
        OSDPrintUV(*(undefined4 *)(this + 0x3c),fVar20,fVar18,puVar15,puVar15,0x1000000,
                   *(undefined4 *)pcVar8,*(undefined4 *)(this + 0x1a4),*(undefined4 *)(this + 0x1a8)
                   ,*(undefined4 *)(this + 0x1ac),0,0,fVar10,fVar10,bVar9,0);
        OSDPrintUV(*(undefined4 *)(this + 0x3c),fVar13,fVar18,fVar17,puVar15,0x1000000,
                   *(undefined4 *)pcVar8,*(undefined4 *)(this + 0x1a4),*(undefined4 *)(this + 0x1a8)
                   ,*(undefined4 *)(this + 0x1ac),fVar10,0,fVar11,fVar10,bVar9,0);
        OSDPrintUV(*(undefined4 *)(this + 0x3c),fVar22,fVar18,puVar15,puVar15,0x1000000,
                   *(undefined4 *)pcVar8,*(undefined4 *)(this + 0x1a4),*(undefined4 *)(this + 0x1a8)
                   ,*(undefined4 *)(this + 0x1ac),fVar11,0,fVar19,fVar10,bVar9,0);
        fVar18 = fVar14 + fVar16;
        OSDPrintUV(*(undefined4 *)(this + 0x3c),fVar20,fVar14,puVar15,fVar16,0x1000000,
                   *(undefined4 *)pcVar8,*(undefined4 *)(this + 0x1a4),*(undefined4 *)(this + 0x1a8)
                   ,*(undefined4 *)(this + 0x1ac),0,fVar10,fVar10,fVar11,bVar9,0);
        OSDPrintUV(*(undefined4 *)(this + 0x3c),fVar13,fVar14,fVar17,fVar16,0x1000000,
                   *(undefined4 *)pcVar8,*(undefined4 *)(this + 0x1a4),*(undefined4 *)(this + 0x1a8)
                   ,*(undefined4 *)(this + 0x1ac),fVar10,fVar10,fVar11,fVar11,bVar9,0);
        OSDPrintUV(*(undefined4 *)(this + 0x3c),fVar22,fVar14,puVar15,fVar16,0x1000000,
                   *(undefined4 *)pcVar8,*(undefined4 *)(this + 0x1a4),*(undefined4 *)(this + 0x1a8)
                   ,*(undefined4 *)(this + 0x1ac),fVar11,fVar10,fVar19,fVar11,bVar9,0);
        OSDPrintUV(*(undefined4 *)(this + 0x3c),fVar20,fVar18,puVar15,puVar15,0x1000000,
                   *(undefined4 *)pcVar8,*(undefined4 *)(this + 0x1a4),*(undefined4 *)(this + 0x1a8)
                   ,*(undefined4 *)(this + 0x1ac),0,fVar11,fVar10,fVar19,bVar9,0);
        OSDPrintUV(*(undefined4 *)(this + 0x3c),fVar13,fVar18,fVar17,puVar15,0x1000000,
                   *(undefined4 *)pcVar8,*(undefined4 *)(this + 0x1a4),*(undefined4 *)(this + 0x1a8)
                   ,*(undefined4 *)(this + 0x1ac),fVar10,fVar11,fVar11,fVar19,bVar9,0);
        OSDPrintUV(*(undefined4 *)(this + 0x3c),fVar22,fVar18,puVar15,puVar15,0x1000000,
                   *(undefined4 *)pcVar8,*(undefined4 *)(this + 0x1a4),*(undefined4 *)(this + 0x1a8)
                   ,*(undefined4 *)(this + 0x1ac),fVar11,fVar11,fVar19,fVar19,bVar9,0);
        puVar1 = PTR__Game_001b60b8;
        if ((*(char *)(*(int *)PTR__Game_001b60b8 + 0x43df8) != '\0') &&
           (*(cRBorder **)(*(int *)PTR__Game_001b60b8 + 0x43e04) == this)) {
          tColour::tColour((tColour *)&local_b0);
          tColour::White((tColour *)&local_60);
          tColour::Set((tColour *)&local_b0,local_60,local_5c,local_58,
                       fVar19 - *(float *)(*(int *)puVar1 + 0x43dfc));
          fVar20 = (fVar19 + *(float *)(*(int *)puVar1 + 0x43dfc) * 0.7) * (float)puVar15;
          fVar23 = fVar13 - fVar20;
          fVar21 = fVar14 - fVar20;
          OSDPrintUV(0x57,fVar23,fVar21,fVar20,fVar20,0x1000000,local_b0,uStack_ac,uStack_a8,
                     uStack_a4,0,0,fVar10,fVar10,1,0);
          OSDPrintUV(0x57,fVar13,fVar21,fVar17,fVar20,0x1000000,local_b0,uStack_ac,uStack_a8,
                     uStack_a4,fVar10,0,fVar11,fVar10,1,0);
          OSDPrintUV(0x57,fVar22,fVar21,fVar20,fVar20,0x1000000,local_b0,uStack_ac,uStack_a8,
                     uStack_a4,fVar11,0,fVar19,fVar10,1,0);
          OSDPrintUV(0x57,fVar23,fVar14,fVar20,fVar16,0x1000000,local_b0,uStack_ac,uStack_a8,
                     uStack_a4,0,fVar10,fVar10,fVar11,1,0);
          OSDPrintUV(0x57,fVar22,fVar14,fVar20,fVar16,0x1000000,local_b0,uStack_ac,uStack_a8,
                     uStack_a4,fVar11,fVar10,fVar19,fVar11,1,0);
          OSDPrintUV(0x57,fVar23,fVar18,fVar20,fVar20,0x1000000,local_b0,uStack_ac,uStack_a8,
                     uStack_a4,0,fVar11,fVar10,fVar19,1,0);
          OSDPrintUV(0x57,fVar13,fVar18,fVar17,fVar20,0x1000000,local_b0,uStack_ac,uStack_a8,
                     uStack_a4,fVar10,fVar11,fVar11,fVar19,1,0);
          OSDPrintUV(0x57,fVar22,fVar18,fVar20,fVar20,0x1000000,local_b0,uStack_ac,uStack_a8,
                     uStack_a4,fVar11,fVar11,fVar19,fVar19,1,0);
        }
      }
    }
    else {
      iVar4 = *(int *)PTR__Game_001b60b8;
      if ((*(char *)(iVar4 + 0x43df8) == '\0') || (*(cRBorder **)(iVar4 + 0x43e04) != this)) {
        fVar16 = 0.0;
      }
      else {
        fVar16 = (float)Sin(*(float *)(iVar4 + 0x43dfc) * 3.1415927);
        fVar16 = fVar16 * 3.0;
        if (this[0x51] == (cRBorder)0x0) {
          fVar16 = -fVar16;
        }
      }
      if ((*(uint *)(this + 0x194) & 2) == 0) {
        fVar11 = *(float *)(this + 0x250);
        iVar4 = *(int *)(this + 0x268);
        fVar10 = *(float *)(this + 0x238);
        fVar17 = *(float *)(this + 0x248);
        fVar13 = *(float *)(this + 0x234);
        fVar14 = fVar11 + *(float *)(this + 0x24c);
        uVar2 = *(undefined4 *)(this + 0x1d0);
        uVar3 = *(undefined4 *)(this + 0x1d4);
        uVar5 = *(undefined4 *)(this + 0x1d8);
        uVar6 = *(undefined4 *)(this + 0x1dc);
      }
      else {
        fVar11 = *(float *)(this + 0x250);
        iVar4 = *(int *)(this + 0x54);
        fVar10 = *(float *)(this + 0x238);
        fVar17 = *(float *)(this + 0x248);
        fVar13 = *(float *)(this + 0x234);
        fVar14 = fVar11 + *(float *)(this + 0x24c);
        uVar2 = *(undefined4 *)(this + 0x1d0);
        uVar3 = *(undefined4 *)(this + 0x1d4);
        uVar5 = *(undefined4 *)(this + 0x1d8);
        uVar6 = *(undefined4 *)(this + 0x1dc);
      }
      OSDPrintUV(iVar4,fVar16 + fVar13 + fVar11 * -0.5,fVar11 * -0.5 + fVar10,fVar11 + fVar17,fVar14
                 ,0x1000000,uVar2,uVar3,uVar5,uVar6,
                 *(undefined4 *)(PTR__gSpriteReference_001b61c8 + iVar4 * 0x20 + 0x10),
                 1.0 - *(float *)(PTR__gSpriteReference_001b61c8 + iVar4 * 0x20 + 0x1c),
                 *(undefined4 *)(PTR__gSpriteReference_001b61c8 + iVar4 * 0x20 + 0x18),
                 1.0 - *(float *)(PTR__gSpriteReference_001b61c8 + iVar4 * 0x20 + 0x14),
                 *(undefined4 *)(this + 0x26c),0);
    }
  }
  return;
}
