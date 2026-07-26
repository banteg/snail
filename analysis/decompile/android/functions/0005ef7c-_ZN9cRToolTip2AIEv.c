/*
 * mangled: _ZN9cRToolTip2AIEv
 * demangled: cRToolTip::AI()
 * address: 0005ef7c
 * size: 1184
 */

/* cRToolTip::AI() */

void __thiscall cRToolTip::AI(cRToolTip *this)

{
  int iVar1;
  uint uVar2;
  cRBorder *this_00;
  bool bVar3;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s1;
  float extraout_s1_00;
  float extraout_s2;
  float fVar4;
  float extraout_s2_00;
  float extraout_s3;
  float fVar5;
  float extraout_s3_00;
  float fVar6;
  float fVar7;
  float fVar8;
  undefined8 unaff_d8;
  float fVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  undefined4 local_78;
  undefined4 uStack_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined4 local_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 local_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 local_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;

  fVar9 = (float)((ulonglong)unaff_d8 >> 0x20);
  iVar1 = *(int *)(this + 4);
  if (iVar1 != 2) {
    if (iVar1 == 3) {
      if ((*(uint *)(*(int *)(this + 0xc) + 0x194) & 0x20000) != 0) {
        return;
      }
      *(undefined4 *)(this + 4) = 1;
      cRBorderManager::Kill((cRBorderManager *)(Game + 0xd14),*(cRBorder **)(this + 0x18));
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
  fVar6 = *(float *)(this + 0x10) + *(float *)(this + 0x14);
  *(float *)(this + 0x10) = fVar6;
  if (fVar6 <= 1.0) {
    return;
  }
  bVar3 = *(int *)(iVar1 + 0x254) == 0;
  if (bVar3) {
    fVar6 = *(float *)(iVar1 + 0x6ec) + *(float *)(iVar1 + 0x23c) * 0.5;
  }
  else {
    fVar9 = *(float *)(iVar1 + 600);
  }
  if (bVar3) {
    fVar9 = 320.0;
  }
  *(undefined4 *)(this + 4) = 3;
  if (bVar3) {
    fVar9 = fVar6 - fVar9;
  }
  if (*(int *)(this + 0x18) == 0) {
    this_00 = (cRBorder *)cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
    *(cRBorder **)(this + 0x18) = this_00;
    fVar6 = extraout_s0_00;
    fVar7 = extraout_s1_00;
    fVar4 = extraout_s2_00;
    fVar5 = extraout_s3_00;
  }
  else {
    RShellError("Tool tip overload");
    this_00 = *(cRBorder **)(this + 0x18);
    fVar6 = extraout_s0;
    fVar7 = extraout_s1;
    fVar4 = extraout_s2;
    fVar5 = extraout_s3;
  }
  uVar2 = *(uint *)(this + 8);
  if ((uVar2 & 1) != 0) {
    fVar8 = *(float *)(Game + 0x238);
    uVar11 = *(undefined4 *)(Game + 0x234);
    tColour::tColour((tColour *)&local_38,fVar6,fVar7,fVar4,fVar5);
    cRBorder::Init(this_00,2,this,7,uVar11,fVar8 + 64.0,local_38,uStack_34,uStack_30,uStack_2c,1,
                   fVar9);
    this_00 = *(cRBorder **)(this + 0x18);
    goto LAB_0005f0cc;
  }
  if ((uVar2 & 4) == 0) {
    if ((uVar2 & 2) == 0) {
      if ((uVar2 & 0x10) != 0) {
        iVar1 = *(int *)(this + 0xc);
        fVar8 = *(float *)(iVar1 + 0x6f0) - *(float *)(iVar1 + 0x214);
        uVar10 = *(undefined4 *)(iVar1 + 0x6ec);
        tColour::tColour((tColour *)&local_68,fVar6,fVar7,fVar4,fVar5);
        fVar9 = 0.0;
        uVar11 = 0;
        goto LAB_0005f1c0;
      }
      if ((uVar2 & 8) == 0) goto LAB_0005f0cc;
      iVar1 = *(int *)(this + 0xc);
      uVar10 = *(undefined4 *)(iVar1 + 0x6ec);
      fVar8 = *(float *)(iVar1 + 0x6f0) + *(float *)(iVar1 + 0x240) + *(float *)(iVar1 + 0x214);
      tColour::tColour((tColour *)&local_78,fVar6,fVar7,fVar4,fVar5);
      fVar9 = 0.0;
      uVar11 = 0;
    }
    else {
      iVar1 = *(int *)(this + 0xc);
      uVar10 = *(undefined4 *)(iVar1 + 0x6ec);
      fVar8 = *(float *)(iVar1 + 0x6f0) + *(float *)(iVar1 + 0x240) + *(float *)(iVar1 + 0x214);
      tColour::tColour((tColour *)&local_58,fVar6,fVar7,fVar4,fVar5);
      uVar11 = 1;
      local_78 = local_58;
      uStack_74 = uStack_54;
      uStack_70 = uStack_50;
      uStack_6c = uStack_4c;
    }
    cRBorder::Init(this_00,2,this,7,uVar10,fVar8,local_78,uStack_74,uStack_70,uStack_6c,uVar11,fVar9
                  );
    this_00 = *(cRBorder **)(this + 0x18);
    *(float *)(this_00 + 0x6f0) = *(float *)(this_00 + 0x6f0) + *(float *)(this_00 + 0x214);
  }
  else {
    iVar1 = *(int *)(this + 0xc);
    fVar8 = *(float *)(iVar1 + 0x6f0) - *(float *)(iVar1 + 0x214);
    uVar10 = *(undefined4 *)(iVar1 + 0x6ec);
    tColour::tColour((tColour *)&local_48,fVar6,fVar7,fVar4,fVar5);
    uVar11 = 1;
    local_68 = local_48;
    uStack_64 = uStack_44;
    uStack_60 = uStack_40;
    uStack_5c = uStack_3c;
LAB_0005f1c0:
    cRBorder::Init(this_00,2,this,7,uVar10,fVar8,local_68,uStack_64,uStack_60,uStack_5c,uVar11,fVar9
                  );
    this_00 = *(cRBorder **)(this + 0x18);
    *(float *)(this_00 + 0x6f0) =
         *(float *)(this_00 + 0x6f0) - (*(float *)(this_00 + 0x240) + *(float *)(this_00 + 0x214));
  }
LAB_0005f0cc:
  fVar9 = *(float *)(this_00 + 0x22c);
  fVar6 = *(float *)(this_00 + 0x20c);
  fVar7 = *(float *)(this_00 + 0x264);
  if ((fVar9 - fVar6) - fVar7 < 0.0) {
    *(float *)(this_00 + 0x6ec) = fVar7;
    this_00 = *(cRBorder **)(this + 0x18);
    fVar9 = *(float *)(this_00 + 0x22c);
    fVar6 = *(float *)(this_00 + 0x20c);
    fVar7 = *(float *)(this_00 + 0x264);
  }
  fVar7 = fVar9 + *(float *)(this_00 + 0x23c) + fVar6 + fVar7;
  if (640.0 < fVar7) {
    *(float *)(this_00 + 0x6ec) = *(float *)(this_00 + 0x6ec) - (fVar7 - 640.0);
    this_00 = *(cRBorder **)(this + 0x18);
  }
  cRBorder::RePosition(this_00);
  return;
}
