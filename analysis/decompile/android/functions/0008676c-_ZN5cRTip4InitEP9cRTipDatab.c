/*
 * mangled: _ZN5cRTip4InitEP9cRTipDatab
 * demangled: cRTip::Init(cRTipData*, bool)
 * address: 0008676c
 * size: 756
 */

/* cRTip::Init(cRTipData*, bool) */

void __thiscall cRTip::Init(cRTip *this,cRTipData *param_1,bool param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  uint *puVar4;
  uint uVar5;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float extraout_s1;
  float extraout_s1_00;
  float extraout_s1_01;
  float extraout_s2;
  float extraout_s2_00;
  float extraout_s2_01;
  float extraout_s3;
  float extraout_s3_00;
  float extraout_s3_01;
  float fVar6;
  uint uVar7;
  undefined4 local_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined4 local_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 local_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 local_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;

  *(undefined4 *)this = 1;
  if (param_1 == (cRTipData *)0x0) {
    *(undefined1 **)(this + 8) = &gTips;
  }
  else {
    *(cRTipData **)(this + 8) = param_1;
  }
  uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
  puVar4 = *(uint **)(this + 8);
  uVar7 = puVar4[2];
  uVar5 = puVar4[4];
  if ((*puVar4 & 4) == 0) {
    uVar3 = 2;
  }
  else {
    uVar3 = 0;
  }
  *(undefined4 *)(this + 0xc) = uVar2;
  tColour::tColour((tColour *)&local_40,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
  cRBorder::Init(uVar2,2,uVar5,0x14,*(undefined4 *)(*(int *)(this + 8) + 4),uVar7,local_40,uStack_3c
                 ,uStack_38,uStack_34,uVar3,*(undefined4 *)(*(int *)(this + 8) + 4));
  puVar4 = *(uint **)(this + 8);
  uVar5 = *puVar4;
  *(undefined4 *)(*(int *)(this + 0xc) + 0x6e8) = 0x3f8ccccd;
  if ((uVar5 & 2) != 0) {
    fVar6 = 0.0;
    *(undefined4 *)(this + 0x18) = 0;
    uVar5 = *puVar4;
    if ((float)puVar4[3] != 0.0) {
      fVar6 = 1.0 / ((float)puVar4[3] * 60.0);
    }
    *(float *)(this + 0x1c) = fVar6;
  }
  if ((uVar5 & 1) == 0) {
    *(undefined4 *)(this + 0x14) = 0;
    *(undefined4 *)(this + 0x10) = 0;
  }
  else {
    uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
    *(undefined4 *)(this + 0x10) = uVar2;
    if (param_2) {
      tColour::tColour((tColour *)&local_70,extraout_s0_00,extraout_s1_00,extraout_s2_00,
                       extraout_s3_00);
      cRBorder::Init(uVar2,0x14,&DAT_00093290,0x14,0,0,local_70,uStack_6c,uStack_68,uStack_64,2,
                     *(undefined4 *)(*(int *)(this + 8) + 4));
      *(undefined4 *)(this + 0x14) = 0;
    }
    else {
      tColour::tColour((tColour *)&local_50,extraout_s0_00,extraout_s1_00,extraout_s2_00,
                       extraout_s3_00);
      cRBorder::Init(uVar2,0x14,&DAT_00093290,0x14,0,0,local_50,uStack_4c,uStack_48,uStack_44,2,
                     *(float *)(*(int *)(this + 8) + 4) + 40.0);
      uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
      *(undefined4 *)(this + 0x14) = uVar2;
      tColour::tColour((tColour *)&local_60,extraout_s0_01,extraout_s1_01,extraout_s2_01,
                       extraout_s3_01);
      cRBorder::Init(uVar2,0x14,"Disable",0x14,0,0,local_60,uStack_5c,uStack_58,uStack_54,2,
                     *(float *)(*(int *)(this + 8) + 4) - 60.0);
      cRBorder::SetBelow(*(cRBorder **)(this + 0x14),*(cRBorder **)(this + 0xc));
    }
    cRBorder::SetBelow(*(cRBorder **)(this + 0x10),*(cRBorder **)(this + 0xc));
    puVar4 = *(uint **)(this + 8);
  }
  iVar1 = Game;
  *(undefined4 *)(this + 4) = *(undefined4 *)(Game + 0x15c);
  if ((*puVar4 & 1) != 0) {
    *(undefined4 *)(iVar1 + 0x15c) = 0x16;
  }
  return;
}
