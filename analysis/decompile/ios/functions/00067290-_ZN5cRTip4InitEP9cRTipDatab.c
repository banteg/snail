/*
 * mangled: _ZN5cRTip4InitEP9cRTipDatab
 * demangled: cRTip::Init(cRTipData*, bool)
 * address: 00067290
 * size: 756
 */

/* cRTip::Init(cRTipData*, bool) */

void __thiscall cRTip::Init(cRTip *this,cRTipData *param_1,bool param_2)

{
  undefined *puVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  uint uVar4;
  uint *puVar5;
  uint uVar6;
  undefined4 uVar7;
  float fVar8;
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
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;

  puVar3 = (undefined4 *)(uint)param_2;
  if (param_1 == (cRTipData *)0x0) {
    puVar3 = &_gTips;
  }
  *(undefined4 *)this = 1;
  if (param_1 == (cRTipData *)0x0) {
    *(undefined4 **)(this + 8) = puVar3;
  }
  else {
    *(cRTipData **)(this + 8) = param_1;
  }
  uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
  puVar5 = *(uint **)(this + 8);
  *(undefined4 *)(this + 0xc) = uVar2;
  uVar4 = puVar5[4];
  if ((*puVar5 & 4) == 0) {
    uVar7 = 2;
  }
  else {
    uVar7 = 0;
  }
  uVar6 = puVar5[2];
  tColour::tColour((tColour *)&local_30,1.0,1.0,1.0,1.0);
  cRBorder::Init(uVar2,2,uVar4,0x14,*(undefined4 *)(*(int *)(this + 8) + 4),uVar6,local_30,uStack_2c
                 ,uStack_28,uStack_24,uVar7,*(undefined4 *)(*(int *)(this + 8) + 4));
  *(undefined4 *)(*(int *)(this + 0xc) + 0x6e8) = 0x3f99999a;
  puVar5 = *(uint **)(this + 8);
  uVar4 = *puVar5;
  if ((uVar4 & 2) != 0) {
    *(undefined4 *)(this + 0x18) = 0;
    if ((float)puVar5[3] == 0.0) {
      fVar8 = 0.0;
    }
    else {
      fVar8 = 1.0 / ((float)puVar5[3] * 60.0);
    }
    *(float *)(this + 0x1c) = fVar8;
    uVar4 = *puVar5;
  }
  if ((uVar4 & 1) == 0) {
    *(undefined4 *)(this + 0x10) = 0;
    *(undefined4 *)(this + 0x14) = 0;
  }
  else {
    uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
    *(undefined4 *)(this + 0x10) = uVar2;
    if ((undefined4 *)(uint)param_2 == (undefined4 *)0x0) {
      tColour::tColour((tColour *)&local_40,1.0,1.0,1.0,1.0);
      cRBorder::Init(uVar2,0x14,"OK",0x14,0,0,local_40,uStack_3c,uStack_38,uStack_34,2,
                     *(float *)(*(int *)(this + 8) + 4) + 40.0);
      uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
      *(undefined4 *)(this + 0x14) = uVar2;
      tColour::tColour((tColour *)&local_50,1.0,1.0,1.0,1.0);
      cRBorder::Init(uVar2,0x14,"Disable",0x14,0,0,local_50,uStack_4c,uStack_48,uStack_44,2,
                     *(float *)(*(int *)(this + 8) + 4) - 60.0);
      cRBorder::SetBelow(*(cRBorder **)(this + 0x14),*(cRBorder **)(this + 0xc));
    }
    else {
      tColour::tColour((tColour *)&local_60,1.0,1.0,1.0,1.0);
      cRBorder::Init(uVar2,0x14,"OK",0x14,0,0,local_60,uStack_5c,uStack_58,uStack_54,2,
                     *(undefined4 *)(*(int *)(this + 8) + 4));
      *(undefined4 *)(this + 0x14) = 0;
    }
    cRBorder::SetBelow(*(cRBorder **)(this + 0x10),*(cRBorder **)(this + 0xc));
    puVar5 = *(uint **)(this + 8);
  }
  puVar1 = PTR__Game_001b60b8;
  *(undefined4 *)(this + 4) = *(undefined4 *)(*(int *)PTR__Game_001b60b8 + 0x15c);
  if ((*puVar5 & 1) != 0) {
    *(undefined4 *)(*(int *)puVar1 + 0x15c) = 0x16;
  }
  return;
}
