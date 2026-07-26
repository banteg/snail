/*
 * mangled: _ZN5cRGUI4InitEv
 * demangled: cRGUI::Init()
 * address: 00064188
 * size: 956
 */

/* cRGUI::Init() */

void __thiscall cRGUI::Init(cRGUI *this)

{
  undefined4 uVar1;
  undefined4 uVar2;
  cRBorder *pcVar3;
  undefined4 *puVar4;
  cRBorder *this_00;
  int iVar5;
  uint in_fpscr;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float extraout_s0_02;
  float extraout_s0_03;
  float extraout_s1;
  float extraout_s1_00;
  float extraout_s1_01;
  float extraout_s1_02;
  float extraout_s1_03;
  float extraout_s2;
  float extraout_s2_00;
  float extraout_s2_01;
  float extraout_s2_02;
  float extraout_s2_03;
  float extraout_s3;
  float extraout_s3_00;
  float extraout_s3_01;
  float extraout_s3_02;
  float extraout_s3_03;
  float fVar6;
  undefined4 local_88;
  undefined4 uStack_84;
  undefined4 uStack_80;
  undefined4 uStack_7c;
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

  cRFade::FadeIn((cRFade *)(Game + 0x24));
  cRMouse::SetActive((cRMouse *)(Game + 0x228));
  if (*(int *)(*(int *)this + 0x60) == 1) {
    uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
    *(undefined4 *)(this + 0x20) = uVar1;
    tColour::tColour((tColour *)&local_48,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
    cRBorder::Init(uVar1,0x100004,"Select Difficulty",0x14,0x41a00000,0x42c80000,local_48,uStack_44,
                   uStack_40,uStack_3c,2,0);
    puVar4 = *(undefined4 **)(this + 0x20);
    fVar6 = (float)VectorSignedToFloat(gConfig._72_4_,(byte)(in_fpscr >> 0x16) & 3);
    puVar4[0x5d] = fVar6 / 100.0;
    puVar4[0x5c] = fVar6 / 100.0;
    (**(code **)*puVar4)(puVar4);
    uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
    *(undefined4 *)(this + 0x1c) = uVar1;
    tColour::tColour((tColour *)&local_58,extraout_s0_00,extraout_s1_00,extraout_s2_00,
                     extraout_s3_00);
    cRBorder::Init(uVar1,0x100004,"Select Speed",0x14,0x41a00000,0x43110000,local_58,uStack_54,
                   uStack_50,uStack_4c,2,0);
    fVar6 = (float)VectorSignedToFloat(gConfig._64_4_,(byte)(in_fpscr >> 0x16) & 3);
    this_00 = *(cRBorder **)(this + 0x1c);
    pcVar3 = *(cRBorder **)(this + 0x20);
    *(float *)(this_00 + 0x174) = fVar6 / 100.0;
    *(float *)(this_00 + 0x170) = fVar6 / 100.0;
    cRBorder::SetBelow(this_00,pcVar3);
    (**(code **)**(undefined4 **)(this + 0x1c))(*(undefined4 **)(this + 0x1c));
    uVar1 = 0x42c80000;
    if (*(int *)(gGroup0 + *(int *)this + 0x5ddf4) != 1) {
      uVar1 = 0;
    }
    uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
    *(undefined4 *)(this + 0x10) = uVar2;
    tColour::tColour((tColour *)&local_68,extraout_s0_01,extraout_s1_01,extraout_s2_01,
                     extraout_s3_01);
    cRBorder::Init(uVar2,0x40000016,&DAT_00092f24,0x14,0x41a00000,0x437a0000,local_68,uStack_64,
                   uStack_60,uStack_5c,2,uVar1);
    cRBorder::SetBelow(*(cRBorder **)(this + 0x10),*(cRBorder **)(this + 0x1c));
    iVar5 = Game;
    *(undefined4 *)(*(int *)(this + 0x10) + 0x264) = 0x41000000;
    uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(iVar5 + 0xd14));
    *(undefined4 *)(this + 0x24) = uVar1;
    tColour::tColour((tColour *)&local_78,extraout_s0_02,extraout_s1_02,extraout_s2_02,
                     extraout_s3_02);
    cRBorder::Init(uVar1,0x40000016,"Watch Replay",0x14,0x41a00000,0x428c0000,local_78,uStack_74,
                   uStack_70,uStack_6c,2,0xc2c80000);
    cRBorder::SetBelow(*(cRBorder **)(this + 0x24),*(cRBorder **)(this + 0x1c));
    iVar5 = *(int *)this;
    pcVar3 = *(cRBorder **)(this + 0x24);
    *(undefined4 *)(pcVar3 + 0x264) = 0x41000000;
    if (*(int *)(gGroup0 + iVar5 + 0x5ddf4) == 1) {
      fVar6 = (float)cRBorder::SetRight(*(cRBorder **)(this + 0x10),pcVar3);
    }
    else {
      fVar6 = (float)cRBorder::HideInit(pcVar3);
    }
    cRBorderManager::CentreRow
              ((cRBorderManager *)(Game + 0xd14),*(cRBorder **)(this + 0x10),false,fVar6);
    uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
    *(undefined4 *)(this + 0x18) = uVar1;
    tColour::tColour((tColour *)&local_88,extraout_s0_03,extraout_s1_03,extraout_s2_03,
                     extraout_s3_03);
    cRBorder::Init(uVar1,0x16,&DAT_00092f10,0x14,0x41a00000,0x41a00000,local_88,uStack_84,uStack_80,
                   uStack_7c,2,0);
    cRBorder::SetBelow(*(cRBorder **)(this + 0x18),*(cRBorder **)(this + 0x24));
  }
  return;
}
