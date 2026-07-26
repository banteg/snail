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
  int iVar2;
  tColour *ptVar3;
  int iVar4;
  cRGalaxy *pcVar5;
  int iVar6;
  int unaff_r9;
  cRGalaxy *pcVar7;
  cRGalaxy *pcVar8;
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
  float fVar9;
  float extraout_s2_02;
  float extraout_s3;
  float extraout_s3_00;
  float extraout_s3_01;
  float fVar10;
  float extraout_s3_02;
  float extraout_s4;
  float extraout_s4_00;
  float fVar11;
  float extraout_s4_01;
  float fVar12;
  float fVar13;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  float local_44;

  tColour::tColour((tColour *)&local_50);
  if (*(int *)this != 0) {
    iVar4 = *(int *)(gOFOData + Game + 0x1ebc);
    if (iVar4 == 0) {
      iVar6 = 0x80;
      local_54 = 0x81;
      iVar2 = *(int *)(this + 4);
    }
    else {
      if (iVar4 == 1) {
        local_54 = 0x84;
      }
      else {
        local_54 = 0;
      }
      iVar2 = *(int *)(this + 4);
      if (iVar4 == 1) {
        iVar6 = 0x83;
      }
      else {
        iVar6 = 0;
      }
    }
    if ((iVar2 == 1) && ((*(uint *)(*(int *)(this + 0x8e40) + 0x194) & 0x1000) == 0)) {
      tColour::Set((tColour *)&local_50,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
      fVar12 = *(float *)(*(int *)(this + 0x8e40) + 0x40);
      fVar13 = *(float *)(this + *(int *)(this + 0x8e34) * 0x2a0 + 0x210);
      if (fVar13 < fVar12) {
        ptVar3 = (tColour *)(fVar13 - 16.0);
        if ((float)ptVar3 <= fVar12 - 6.0) {
          ptVar3 = (tColour *)(fVar13 + 16.0);
        }
      }
      else {
        ptVar3 = (tColour *)(fVar13 + 16.0);
        if (fVar12 + 6.0 + *(float *)(*(int *)(this + 0x8e40) + 0x48) <= (float)ptVar3) {
          ptVar3 = (tColour *)(fVar13 - 16.0);
        }
      }
      Line(this,iVar6,extraout_s0_02,extraout_s1_02,extraout_s2_02,extraout_s3_02,extraout_s4_01,
           ptVar3);
      iVar4 = *(int *)(gOFOData + Game + 0x1ebc);
    }
    iVar6 = gConfig._160_4_;
    if ((iVar4 != 0) && (iVar6 = unaff_r9, iVar4 == 1)) {
      iVar6 = gConfig._232_4_;
    }
    if (iVar6 < 1) {
      tColour::White();
      local_44 = 0.2;
    }
    else {
      iVar4 = 1;
      pcVar5 = this;
      do {
        while( true ) {
          local_44 = 0.99;
          local_50 = 0x3f800000;
          local_4c = 0x3f800000;
          local_48 = 0x3f800000;
          if ((*(int *)(this + 0xc) != 1) || (iVar4 <= *(int *)(this + 0x8e34))) {
            OSDPrintUV(0x7e,*(float *)(pcVar5 + 0x4b0) - 16.0,*(float *)(pcVar5 + 0x4b4) - 16.0,
                       0x42000000,0x42000000,0x1000000,0x3f800000,0x3f800000,0x3f800000,0x3f7d70a4,0
                       ,0,0x3f800000,0x3f800000,1,0);
          }
          iVar4 = iVar4 + 1;
          fVar12 = *(float *)(pcVar5 + 0x4bc);
          if (fVar12 <= 0.0) break;
          pcVar7 = pcVar5 + 0x4b0;
          pcVar8 = pcVar5 + 0x4b4;
          pcVar5 = pcVar5 + 0x2a0;
          local_44 = fVar12;
          OSDPrintUV(local_54,*(float *)pcVar7 - 32.0,*(float *)pcVar8 - 32.0,0x42800000,0x42800000,
                     0x1000000,local_50,local_4c,local_48,fVar12,0,0,0x3f800000,0x3f800000,1,0);
          if (iVar6 < iVar4) goto LAB_000595d8;
        }
        pcVar5 = pcVar5 + 0x2a0;
      } while (iVar4 <= iVar6);
LAB_000595d8:
      tColour::White();
      local_44 = 0.2;
      if (1 < iVar6) {
        iVar4 = 2;
        pcVar5 = this;
        fVar12 = extraout_s0_00;
        fVar13 = extraout_s1_00;
        fVar9 = extraout_s2_00;
        fVar10 = extraout_s3_00;
        fVar11 = extraout_s4;
        do {
          if (iVar4 + -1 < *(int *)(this + 0x8e34)) {
            ptVar3 = *(tColour **)(pcVar5 + 0x4b0);
            local_44 = (float)0x3f4ccccd;
LAB_00059638:
            Line(this,0x85,fVar12,fVar13,fVar9,fVar10,fVar11,ptVar3);
            fVar12 = extraout_s0_01;
            fVar13 = extraout_s1_01;
            fVar9 = extraout_s2_01;
            fVar10 = extraout_s3_01;
            fVar11 = extraout_s4_00;
          }
          else if (*(int *)(this + 0xc) != 1) {
            local_44 = 0.2;
            ptVar3 = *(tColour **)(pcVar5 + 0x4b0);
            goto LAB_00059638;
          }
          pcVar5 = pcVar5 + 0x2a0;
          bVar1 = iVar4 < iVar6;
          iVar4 = iVar4 + 1;
        } while (bVar1);
      }
    }
    tColour::White();
  }
  return;
}
