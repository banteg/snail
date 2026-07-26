/*
 * mangled: _ZN8cRGalaxy6RenderEv
 * demangled: cRGalaxy::Render()
 * address: 000593e0
 * size: 1052
 */

/* cRGalaxy::Render() */

void __thiscall cRGalaxy::Render(cRGalaxy *this)

{
  bool bVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  tColour *ptVar5;
  int iVar6;
  int iVar7;
  cRGalaxy *pcVar8;
  int iVar9;
  int unaff_r9;
  cRGalaxy *pcVar10;
  cRGalaxy *pcVar11;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float extraout_s0_02;
  float extraout_s1;
  float extraout_s1_00;
  float extraout_s1_01;
  float extraout_s1_02;
  float extraout_s2;
  float extraout_s2_00;
  float extraout_s2_01;
  float fVar12;
  float extraout_s2_02;
  float extraout_s3;
  float extraout_s3_00;
  float extraout_s3_01;
  float extraout_s3_02;
  float extraout_s4;
  float extraout_s4_00;
  float fVar13;
  float extraout_s4_01;
  float fVar14;
  float fVar15;
  float fVar16;
  undefined4 uVar17;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  float local_44;

  iVar7 = DAT_00059824;
  tColour::tColour((tColour *)&local_50);
  iVar3 = DAT_00059828;
  iVar7 = iVar7 + 0x5940c;
  if (*(int *)this != 0) {
    iVar6 = *(int *)(gOFOData + **(int **)(iVar7 + DAT_00059828) + 0x1ebc);
    if (iVar6 == 0) {
      iVar9 = 0x80;
      local_54 = 0x81;
      iVar4 = *(int *)(this + 4);
    }
    else {
      if (iVar6 == 1) {
        local_54 = 0x84;
      }
      else {
        local_54 = 0;
      }
      iVar4 = *(int *)(this + 4);
      if (iVar6 == 1) {
        iVar9 = 0x83;
      }
      else {
        iVar9 = 0;
      }
    }
    if ((iVar4 == 1) && ((*(uint *)(*(int *)(this + 0x8e40) + 0x194) & 0x1000) == 0)) {
      tColour::Set((tColour *)&local_50,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
      fVar14 = *(float *)(*(int *)(this + 0x8e40) + 0x40);
      fVar16 = *(float *)(this + *(int *)(this + 0x8e34) * 0x2a0 + 0x210);
      if (fVar16 < fVar14) {
        ptVar5 = (tColour *)(fVar16 - DAT_00059804);
        if ((float)ptVar5 <= fVar14 - DAT_00059820) {
          ptVar5 = (tColour *)(fVar16 + DAT_00059804);
        }
      }
      else {
        ptVar5 = (tColour *)(fVar16 + DAT_00059804);
        if (fVar14 + DAT_00059820 + *(float *)(*(int *)(this + 0x8e40) + 0x48) <= (float)ptVar5) {
          ptVar5 = (tColour *)(fVar16 - DAT_00059804);
        }
      }
      Line(this,iVar9,extraout_s0_02,extraout_s1_02,extraout_s2_02,extraout_s3_02,extraout_s4_01,
           ptVar5);
      iVar6 = *(int *)(gOFOData + **(int **)(iVar7 + iVar3) + 0x1ebc);
    }
    uVar17 = DAT_0005980c;
    fVar12 = DAT_00059808;
    fVar16 = DAT_00059804;
    fVar14 = DAT_00059800;
    uVar2 = DAT_000597fc;
    if (iVar6 == 0) {
      unaff_r9 = *(int *)(*(int *)(iVar7 + DAT_0005982c) + 0xa0);
    }
    else if (iVar6 == 1) {
      unaff_r9 = *(int *)(*(int *)(iVar7 + DAT_0005982c) + 0xe8);
    }
    if (unaff_r9 < 1) {
      tColour::White();
      local_44 = (float)DAT_00059810;
    }
    else {
      iVar7 = 1;
      pcVar8 = this;
      do {
        while( true ) {
          local_44 = fVar14;
          local_50 = uVar2;
          local_4c = uVar2;
          local_48 = uVar2;
          if ((*(int *)(this + 0xc) != 1) || (iVar7 <= *(int *)(this + 0x8e34))) {
            OSDPrintUV(0x7e,*(float *)(pcVar8 + 0x4b0) - fVar16,*(float *)(pcVar8 + 0x4b4) - fVar16,
                       fVar12,fVar12,0x1000000,uVar2,uVar2,uVar2,fVar14,uVar17,uVar17,uVar2,uVar2,1,
                       uVar17);
          }
          iVar7 = iVar7 + 1;
          fVar15 = *(float *)(pcVar8 + 0x4bc);
          if (fVar15 <= 0.0) break;
          pcVar10 = pcVar8 + 0x4b0;
          pcVar11 = pcVar8 + 0x4b4;
          pcVar8 = pcVar8 + 0x2a0;
          local_44 = fVar15;
          OSDPrintUV(local_54,*(float *)pcVar10 - fVar12,*(float *)pcVar11 - fVar12,0x42800000,
                     0x42800000,0x1000000,local_50,local_4c,local_48,fVar15,uVar17,uVar17,uVar2,
                     uVar2,1,uVar17);
          if (unaff_r9 < iVar7) goto LAB_000595d8;
        }
        pcVar8 = pcVar8 + 0x2a0;
      } while (iVar7 <= unaff_r9);
LAB_000595d8:
      tColour::White();
      uVar2 = DAT_00059810;
      local_44 = (float)DAT_00059810;
      if (1 < unaff_r9) {
        uVar17 = DAT_00059818;
        iVar7 = 2;
        pcVar8 = this;
        fVar14 = extraout_s0_00;
        fVar16 = extraout_s1_00;
        fVar12 = extraout_s2_00;
        fVar15 = extraout_s3_00;
        fVar13 = extraout_s4;
        do {
          if (iVar7 + -1 < *(int *)(this + 0x8e34)) {
            ptVar5 = *(tColour **)(pcVar8 + 0x4b0);
            local_44 = (float)uVar17;
LAB_00059638:
            Line(this,0x85,fVar14,fVar16,fVar12,fVar15,fVar13,ptVar5);
            fVar14 = extraout_s0_01;
            fVar16 = extraout_s1_01;
            fVar12 = extraout_s2_01;
            fVar15 = extraout_s3_01;
            fVar13 = extraout_s4_00;
          }
          else if (*(int *)(this + 0xc) != 1) {
            local_44 = (float)uVar2;
            ptVar5 = *(tColour **)(pcVar8 + 0x4b0);
            goto LAB_00059638;
          }
          pcVar8 = pcVar8 + 0x2a0;
          bVar1 = iVar7 < unaff_r9;
          iVar7 = iVar7 + 1;
        } while (bVar1);
      }
    }
    tColour::White();
  }
  return;
}
