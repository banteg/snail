/*
 * mangled: _ZN8cRGalaxy6RenderEv
 * demangled: cRGalaxy::Render()
 * address: 0006a6c4
 * size: 1368
 */

/* cRGalaxy::Render() */

void __thiscall cRGalaxy::Render(cRGalaxy *this)

{
  bool bVar1;
  int iVar2;
  cRGalaxy *pcVar3;
  undefined4 unaff_r8;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  undefined4 local_54;
  int local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  float local_40;
  float local_3c;
  float local_38;
  undefined4 local_34;

  tColour::tColour((tColour *)&local_4c);
  if (*(int *)this != 0) {
    if (*(int *)(&DAT_00364944 + *(int *)PTR__Game_001b60b8) == 0) {
      unaff_r8 = 0x80;
      local_54 = 0x81;
      iVar2 = *(int *)(this + 4);
    }
    else {
      if (*(int *)(&DAT_00364944 + *(int *)PTR__Game_001b60b8) == 1) {
        unaff_r8 = 0x83;
        local_54 = 0x84;
      }
      iVar2 = *(int *)(this + 4);
    }
    if ((iVar2 == 1) && ((*(uint *)(*(int *)(this + 0x8e40) + 0x194) & 0x1000) == 0)) {
      tColour::Set((tColour *)&local_4c,1.0,1.0,1.0,0.999);
      fVar4 = *(float *)(*(int *)(this + 0x8e40) + 0x40);
      fVar5 = *(float *)(this + *(int *)(this + 0x8e34) * 0x2a0 + 0x210);
      if (fVar5 < fVar4) {
        fVar6 = fVar5 - 16.0;
        fVar4 = fVar4 - 6.0;
        if (fVar6 <= fVar4) {
          fVar6 = fVar5 + 16.0;
        }
      }
      else {
        fVar6 = fVar5 + 16.0;
        fVar4 = fVar4 + 6.0 + *(float *)(*(int *)(this + 0x8e40) + 0x48);
        if (fVar4 <= fVar6) {
          fVar6 = fVar5 - 16.0;
        }
      }
      local_3c = fVar4 - fVar6;
      fVar8 = *(float *)(this + *(int *)(this + 0x8e34) * 0x2a0 + 0x214);
      local_34 = 0;
      local_38 = fVar8 - fVar8;
      tVector::Normalize((tVector *)&local_3c);
      fVar7 = -(local_38 * 4.0) * 0.5;
      fVar9 = local_3c * 4.0 * 0.5;
      fVar5 = fVar8 - fVar9;
      fVar8 = fVar8 + fVar9;
      OSDPrintUV(unaff_r8,fVar6 - fVar7,fVar5,fVar4 - fVar7,fVar5,fVar4 + fVar7,fVar8,fVar6 + fVar7,
                 fVar8,0,0,0x1000000,local_4c,local_48,local_44,local_40,0,0,0x3f800000,0x3f800000,1
                 ,0);
    }
    if (*(int *)(&DAT_00364944 + *(int *)PTR__Game_001b60b8) == 0) {
      local_50 = *(int *)(PTR__gConfig_001b60d4 + 0xa0);
    }
    else if (*(int *)(&DAT_00364944 + *(int *)PTR__Game_001b60b8) == 1) {
      local_50 = *(int *)(PTR__gConfig_001b60d4 + 0xe8);
    }
    if (local_50 < 1) {
      tColour::White((tColour *)&local_4c);
      local_40 = 0.2;
    }
    else {
      iVar2 = 1;
      pcVar3 = this;
      do {
        local_4c = 0x3f800000;
        local_48 = 0x3f800000;
        local_44 = 0x3f800000;
        local_40 = 0.99;
        if ((*(int *)(this + 0xc) != 1) || (iVar2 <= *(int *)(this + 0x8e34))) {
          OSDPrintUV(0x7e,*(float *)(pcVar3 + 0x4b0) - 16.0,*(float *)(pcVar3 + 0x4b4) - 16.0,
                     0x42000000,0x42000000,0x1000000,0x3f800000,0x3f800000,0x3f800000,0x3f7d70a4,0,0
                     ,0x3f800000,0x3f800000,1,0);
        }
        fVar5 = *(float *)(pcVar3 + 0x4bc);
        if (0.0 < fVar5) {
          local_40 = fVar5;
          OSDPrintUV(local_54,*(float *)(pcVar3 + 0x4b0) - 32.0,*(float *)(pcVar3 + 0x4b4) - 32.0,
                     0x42800000,0x42800000,0x1000000,local_4c,local_48,local_44,fVar5,0,0,0x3f800000
                     ,0x3f800000,1,0);
        }
        iVar2 = iVar2 + 1;
        pcVar3 = pcVar3 + 0x2a0;
      } while (iVar2 != local_50 + 1);
      tColour::White((tColour *)&local_4c);
      local_40 = 0.2;
      if (1 < local_50) {
        pcVar3 = this;
        iVar2 = 2;
        do {
          if (iVar2 + -1 < *(int *)(this + 0x8e34)) {
            local_40 = 0.8;
LAB_0006a944:
            fVar9 = *(float *)(pcVar3 + 0x4b0);
            fVar7 = *(float *)(pcVar3 + 0x750);
            local_3c = fVar7 - fVar9;
            fVar8 = *(float *)(pcVar3 + 0x4b4);
            fVar6 = *(float *)(pcVar3 + 0x754);
            local_34 = 0;
            local_38 = fVar6 - fVar8;
            tVector::Normalize((tVector *)&local_3c);
            fVar5 = -(local_38 * 4.0) * 0.5;
            fVar4 = local_3c * 4.0 * 0.5;
            OSDPrintUV(0x85,fVar9 - fVar5,fVar8 - fVar4,fVar7 - fVar5,fVar6 - fVar4,fVar7 + fVar5,
                       fVar6 + fVar4,fVar9 + fVar5,fVar8 + fVar4,0,0,0x1000000,local_4c,local_48,
                       local_44,local_40,0,0,0x3f800000,0x3f800000,1,0);
          }
          else if (*(int *)(this + 0xc) != 1) {
            local_40 = 0.2;
            goto LAB_0006a944;
          }
          pcVar3 = pcVar3 + 0x2a0;
          bVar1 = iVar2 < local_50;
          iVar2 = iVar2 + 1;
        } while (bVar1);
      }
    }
    tColour::White((tColour *)&local_4c);
  }
  return;
}
