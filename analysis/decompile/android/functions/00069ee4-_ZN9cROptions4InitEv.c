/*
 * mangled: _ZN9cROptions4InitEv
 * demangled: cROptions::Init()
 * address: 00069ee4
 * size: 1000
 */

/* cROptions::Init() */

void __thiscall cROptions::Init(cROptions *this)

{
  undefined4 uVar1;
  cRBorderManager *this_00;
  int iVar2;
  size_t sVar3;
  undefined4 *puVar4;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float extraout_s0_02;
  float extraout_s0_03;
  float extraout_s0_04;
  float fVar5;
  float extraout_s0_05;
  float extraout_s1;
  float extraout_s1_00;
  float extraout_s1_01;
  float extraout_s1_02;
  float extraout_s1_03;
  float extraout_s1_04;
  float fVar6;
  float extraout_s1_05;
  float extraout_s2;
  float extraout_s2_00;
  float extraout_s2_01;
  float extraout_s2_02;
  float extraout_s2_03;
  float extraout_s2_04;
  float fVar7;
  float extraout_s2_05;
  float extraout_s3;
  float extraout_s3_00;
  float extraout_s3_01;
  float extraout_s3_02;
  float extraout_s3_03;
  float extraout_s3_04;
  float fVar8;
  float extraout_s3_05;
  undefined4 local_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined4 local_80;
  undefined4 uStack_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
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

  iVar2 = Game;
  *(undefined1 *)(Game + 0x324) = 1;
  uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(iVar2 + 0xd14));
  *(undefined4 *)(this + 0x14) = uVar1;
  tColour::tColour((tColour *)&local_40,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
  cRBorder::Init(uVar1,0x14,"",0x14,0x42b40000,0x42be0000,local_40,uStack_3c,uStack_38,uStack_34,2,0
                );
  this_00 = (cRBorderManager *)(Game + 0xd14);
  *(float *)(*(int *)(this + 0x14) + 0x6f0) = *(float *)(*(int *)(this + 0x14) + 0x6f0) + 8.0;
  uVar1 = cRBorderManager::GetBorder(this_00);
  *(undefined4 *)(this + 0x18) = uVar1;
  tColour::tColour((tColour *)&local_50,extraout_s0_00,extraout_s1_00,extraout_s2_00,extraout_s3_00)
  ;
  cRBorder::Init(uVar1,0x900004,"Sounds Volume",0x14,0x42b40000,0x43c80000,local_50,uStack_4c,
                 uStack_48,uStack_44,2,0);
  cRBorder::SetBelow(*(cRBorder **)(this + 0x18),*(cRBorder **)(this + 0x14));
  uVar1 = gConfig._0_4_;
  puVar4 = *(undefined4 **)(this + 0x18);
  puVar4[0x5d] = gConfig._0_4_;
  puVar4[0x5c] = uVar1;
  (**(code **)*puVar4)(puVar4);
  uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
  *(undefined4 *)(this + 0x1c) = uVar1;
  tColour::tColour((tColour *)&local_60,extraout_s0_01,extraout_s1_01,extraout_s2_01,extraout_s3_01)
  ;
  cRBorder::Init(uVar1,0x100004,"Music Volume",0x14,0x42b40000,0x43c80000,local_60,uStack_5c,
                 uStack_58,uStack_54,2,0);
  cRBorder::SetBelow(*(cRBorder **)(this + 0x1c),*(cRBorder **)(this + 0x18));
  uVar1 = gConfig._4_4_;
  puVar4 = *(undefined4 **)(this + 0x1c);
  puVar4[0x5d] = gConfig._4_4_;
  puVar4[0x5c] = uVar1;
  (**(code **)*puVar4)(puVar4);
  uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
  *(undefined4 *)(this + 0x10) = uVar1;
  tColour::tColour((tColour *)&local_70,extraout_s0_02,extraout_s1_02,extraout_s2_02,extraout_s3_02)
  ;
  cRBorder::Init(uVar1,0x14,&DAT_00092f10,0x14,0x42b40000,0x43c80000,local_70,uStack_6c,uStack_68,
                 uStack_64,2,0);
  cRBorder::SetBelow(*(cRBorder **)(this + 0x10),*(cRBorder **)(this + 0x1c));
  iVar2 = Game;
  *(undefined4 *)(this + 0x24) = gConfig._0_4_;
  uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(iVar2 + 0xd14));
  *(undefined4 *)(this + 0x20) = uVar1;
  iVar2 = Rstrcmp("Fluctuosa",gConfig + 0x60);
  if (iVar2 == 0) {
    uVar1 = *(undefined4 *)(this + 0x20);
    tColour::tColour((tColour *)&local_90,extraout_s0_03,extraout_s1_03,extraout_s2_03,
                     extraout_s3_03);
    cRBorder::Init(uVar1,0x20400000,"V1.00.06",0x14,0x44128000,0x43e80000,local_90,uStack_8c,
                   uStack_88,uStack_84,0,0);
    iVar2 = *(int *)(this + 0x20);
    sVar3 = strlen((char *)(iVar2 + 0x2c4));
    *(undefined1 *)(iVar2 + sVar3 + 0x2c2) = 0;
    fVar5 = extraout_s0_04;
    fVar6 = extraout_s1_04;
    fVar7 = extraout_s2_04;
    fVar8 = extraout_s3_04;
  }
  else {
    uVar1 = *(undefined4 *)(this + 0x20);
    tColour::tColour((tColour *)&local_80,extraout_s0_03,extraout_s1_03,extraout_s2_03,
                     extraout_s3_03);
    cRBorder::Init(uVar1,0x20400000,"V1.00.06",0x14,0x440d8000,0x43e80000,local_80,uStack_7c,
                   uStack_78,uStack_74,0,0);
    fVar5 = extraout_s0_05;
    fVar6 = extraout_s1_05;
    fVar7 = extraout_s2_05;
    fVar8 = extraout_s3_05;
  }
  tColour::Set((tColour *)(*(int *)(this + 0x20) + 0x1e0),fVar5,fVar6,fVar7,fVar8);
  iVar2 = *(int *)(this + 0x20);
  *(undefined4 *)(iVar2 + 0x6e8) = 0x3f19999a;
  *(undefined1 *)(iVar2 + 0x228) = 1;
  return;
}
