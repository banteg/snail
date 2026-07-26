/*
 * mangled: _ZN9cRToolTip2AIEv
 * demangled: cRToolTip::AI()
 * address: 0003b41c
 * size: 1344
 */

/* cRToolTip::AI() */

void __thiscall cRToolTip::AI(cRToolTip *this)

{
  int iVar1;
  uint uVar2;
  float *pfVar3;
  char *pcVar4;
  int iVar5;
  cRBorder *pcVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  bool bVar9;
  float in_s13;
  float fVar10;
  float fVar11;
  undefined8 in_d8;
  float fVar12;
  undefined4 uVar13;
  undefined4 local_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 local_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 local_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 local_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 local_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;

  fVar12 = (float)((ulonglong)in_d8 >> 0x20);
  iVar1 = *(int *)(this + 4);
  if (iVar1 != 2) {
    if (iVar1 == 3) {
      if ((*(uint *)(*(int *)(this + 0xc) + 0x194) & 0x20000) != 0) {
        return;
      }
      *(undefined4 *)(this + 4) = 1;
      iVar5 = *(int *)(this + 0x18);
      iVar1 = *(int *)PTR__Game_001b60b8;
      if ((((iVar5 != 0) && (uVar2 = *(uint *)(iVar5 + 0x194), uVar2 != 0)) &&
          ((uVar2 & 0x400) == 0)) &&
         (*(uint *)(iVar5 + 0x194) = uVar2 & 0xffffff09 | 0x200, (uVar2 & 0x100000) != 0)) {
        pcVar6 = (cRBorder *)(iVar1 + 0xd14);
        cRBorderManager::Kill(pcVar6);
        cRBorderManager::Kill(pcVar6);
        cRBorderManager::Kill(pcVar6);
      }
      *(undefined4 *)(this + 0x18) = 0;
      return;
    }
    if (iVar1 != 1) {
      return;
    }
    if ((*(uint *)(*(int *)(this + 0xc) + 0x194) & 0x20000) == 0) {
      return;
    }
    *(undefined4 *)(this + 0x10) = 0;
    *(undefined4 *)(this + 4) = 2;
    return;
  }
  iVar1 = *(int *)(this + 0xc);
  if ((*(uint *)(iVar1 + 0x194) & 0x20000) == 0) {
    *(undefined4 *)(this + 4) = 1;
    return;
  }
  fVar11 = *(float *)(this + 0x10) + *(float *)(this + 0x14);
  fVar10 = 1.0;
  *(float *)(this + 0x10) = fVar11;
  if (fVar11 <= 1.0) {
    return;
  }
  bVar9 = *(int *)(iVar1 + 0x254) == 0;
  if (bVar9) {
    fVar10 = 0.5;
    fVar11 = *(float *)(iVar1 + 0x6ec);
    in_s13 = *(float *)(iVar1 + 0x23c);
  }
  else {
    fVar12 = *(float *)(iVar1 + 600);
  }
  *(undefined4 *)(this + 4) = 3;
  if (bVar9) {
    fVar12 = (fVar11 + in_s13 * fVar10) - 320.0;
  }
  if (*(int *)(this + 0x18) == 0) {
    iVar5 = *(int *)PTR__Game_001b60b8;
    pcVar4 = section_00001504.segname + iVar5 + 0xc;
    iVar1 = 0;
    do {
      if (*(int *)pcVar4 == 0) {
        *(undefined4 *)((int)&section_00001504 + iVar1 * 0x71c + iVar5 + 0x18) =
             *(undefined4 *)(iVar5 + 0x2d8);
        *(int *)(this + 0x18) = iVar5 + iVar1 * 0x71c + 0x138c;
        goto LAB_0003b594;
      }
      iVar1 = iVar1 + 1;
      pcVar4 = pcVar4 + 0x71c;
    } while (iVar1 != 0x96);
    RShellError("Run out of Borders - Increase RGAME_BORDER_NUMBER");
    *(undefined4 *)(this + 0x18) = 0;
  }
  else {
    RShellError("Tool tip overload");
  }
LAB_0003b594:
  uVar2 = *(uint *)(this + 8);
  if ((uVar2 & 1) != 0) {
    uVar8 = *(undefined4 *)(this + 0x18);
    uVar13 = *(undefined4 *)(*(int *)PTR__Game_001b60b8 + 0x234);
    fVar11 = *(float *)(*(int *)PTR__Game_001b60b8 + 0x238) + 64.0;
    tColour::tColour((tColour *)&local_34,1.0,1.0,1.0,1.0);
    cRBorder::Init(uVar8,2,this,7,uVar13,fVar11,local_34,uStack_30,uStack_2c,uStack_28,1,fVar12);
    goto LAB_0003b5c0;
  }
  if ((uVar2 & 4) == 0) {
    if ((uVar2 & 2) == 0) {
      if ((uVar2 & 0x10) != 0) {
        iVar1 = *(int *)(this + 0xc);
        uVar7 = *(undefined4 *)(iVar1 + 0x6ec);
        uVar8 = *(undefined4 *)(this + 0x18);
        fVar11 = *(float *)(iVar1 + 0x6f0) - *(float *)(iVar1 + 0x214);
        tColour::tColour((tColour *)&local_64,1.0,1.0,1.0,1.0);
        fVar12 = 0.0;
        uVar13 = 0;
        goto LAB_0003b810;
      }
      if ((uVar2 & 8) == 0) goto LAB_0003b5c0;
      iVar1 = *(int *)(this + 0xc);
      uVar7 = *(undefined4 *)(iVar1 + 0x6ec);
      uVar8 = *(undefined4 *)(this + 0x18);
      fVar11 = *(float *)(iVar1 + 0x6f0) + *(float *)(iVar1 + 0x240) + *(float *)(iVar1 + 0x214);
      tColour::tColour((tColour *)&local_74,1.0,1.0,1.0,1.0);
      fVar12 = 0.0;
      uVar13 = 0;
    }
    else {
      iVar1 = *(int *)(this + 0xc);
      uVar7 = *(undefined4 *)(iVar1 + 0x6ec);
      uVar8 = *(undefined4 *)(this + 0x18);
      fVar11 = *(float *)(iVar1 + 0x6f0) + *(float *)(iVar1 + 0x240) + *(float *)(iVar1 + 0x214);
      tColour::tColour((tColour *)&local_54,1.0,1.0,1.0,1.0);
      uVar13 = 1;
      local_74 = local_54;
      uStack_70 = uStack_50;
      uStack_6c = uStack_4c;
      uStack_68 = uStack_48;
    }
    cRBorder::Init(uVar8,2,this,7,uVar7,fVar11,local_74,uStack_70,uStack_6c,uStack_68,uVar13,fVar12)
    ;
    pfVar3 = (float *)(*(int *)(this + 0x18) + 0x6f0);
    *pfVar3 = *pfVar3 + *(float *)(*(int *)(this + 0x18) + 0x214);
  }
  else {
    iVar1 = *(int *)(this + 0xc);
    uVar7 = *(undefined4 *)(iVar1 + 0x6ec);
    uVar8 = *(undefined4 *)(this + 0x18);
    fVar11 = *(float *)(iVar1 + 0x6f0) - *(float *)(iVar1 + 0x214);
    tColour::tColour((tColour *)&local_44,1.0,1.0,1.0,1.0);
    uVar13 = 1;
    local_64 = local_44;
    uStack_60 = uStack_40;
    uStack_5c = uStack_3c;
    uStack_58 = uStack_38;
LAB_0003b810:
    cRBorder::Init(uVar8,2,this,7,uVar7,fVar11,local_64,uStack_60,uStack_5c,uStack_58,uVar13,fVar12)
    ;
    iVar1 = *(int *)(this + 0x18);
    *(float *)(iVar1 + 0x6f0) =
         *(float *)(iVar1 + 0x6f0) - (*(float *)(iVar1 + 0x240) + *(float *)(iVar1 + 0x214));
  }
LAB_0003b5c0:
  pcVar6 = *(cRBorder **)(this + 0x18);
  fVar11 = *(float *)(pcVar6 + 0x22c);
  fVar10 = *(float *)(pcVar6 + 0x20c);
  fVar12 = *(float *)(pcVar6 + 0x264);
  if ((fVar11 - fVar10) - fVar12 < 0.0) {
    *(float *)(pcVar6 + 0x6ec) = fVar12;
    pcVar6 = *(cRBorder **)(this + 0x18);
    fVar11 = *(float *)(pcVar6 + 0x22c);
    fVar10 = *(float *)(pcVar6 + 0x20c);
    fVar12 = *(float *)(pcVar6 + 0x264);
  }
  fVar12 = fVar11 + *(float *)(pcVar6 + 0x23c) + fVar10 + fVar12;
  if (640.0 < fVar12) {
    *(float *)(pcVar6 + 0x6ec) = *(float *)(pcVar6 + 0x6ec) - (fVar12 - 640.0);
    pcVar6 = *(cRBorder **)(this + 0x18);
  }
  cRBorder::RePosition(pcVar6);
  return;
}
