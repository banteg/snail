/*
 * mangled: _ZN12cRCompletion4InitEib
 * demangled: cRCompletion::Init(int, bool)
 * address: 0006102c
 * size: 1696
 */

/* cRCompletion::Init(int, bool) */

void __thiscall cRCompletion::Init(cRCompletion *this,int param_1,bool param_2)

{
  undefined4 uVar1;
  cRBorder *this_00;
  uint uVar2;
  size_t sVar3;
  undefined4 extraout_r1;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint in_fpscr;
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
  float extraout_s2_02;
  float extraout_s3;
  float extraout_s3_00;
  float extraout_s3_01;
  float extraout_s3_02;
  undefined4 uVar8;
  float fVar9;
  undefined4 local_b0;
  undefined4 uStack_ac;
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  undefined4 local_a0;
  undefined4 uStack_9c;
  undefined4 uStack_98;
  undefined4 uStack_94;
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

  iVar6 = Game;
  uVar4 = (uint)param_2;
  iVar5 = *(int *)(Game + 0x71900);
  if (iVar5 == 0) {
    if (uVar4 == 0) {
      *(undefined4 *)(this + 0x44) = 0;
    }
    else {
      uVar4 = 1;
      *(undefined4 *)(this + 0x44) = 50000;
    }
  }
  else if (iVar5 == 1) {
    iVar5 = gConfig._72_4_;
    iVar7 = gConfig._64_4_;
    if (gDirectory[Game + 0x2544] != '\0') {
      iVar5 = *(int *)(*(int *)(gDirectory + Game + 0x2548) + 0x50);
      iVar7 = *(int *)(*(int *)(gDirectory + Game + 0x2548) + 0x4c);
    }
    iVar7 = iVar7 / 0x14;
    uVar2 = iVar5 / 0x14;
    if (4 < (int)uVar2) {
      uVar2 = 5;
    }
    uVar2 = uVar2 & ~((int)uVar2 >> 0x1f);
    if (iVar7 < 0) {
      iVar7 = 0;
    }
    else {
      if (4 < iVar7) {
        iVar7 = 5;
      }
      if (uVar2 == 5 && iVar7 == 5) {
        *(undefined4 *)(this + 0x44) = 500000;
        goto LAB_00061078;
      }
    }
    *(int *)(this + 0x44) =
         *(int *)(gBonusScoreSpeed + iVar7 * 4) + *(int *)(&gBonusScoreDifficulty + uVar2 * 4);
  }
  else if (iVar5 == 4) {
    wprintf("Your time %f\n",param_1,SUB84((double)*(float *)(Game + 0x81634),0),
            (int)((ulonglong)(double)*(float *)(Game + 0x81634) >> 0x20));
    wprintf("Best Time %f\n",extraout_r1,
            SUB84((double)*(float *)(gGroup0 +
                                    Game + (*(int *)(Game + 0x71904) + 0x16) * 0x38 + 0xce6a0),0),
            (int)((ulonglong)
                  (double)*(float *)(gGroup0 +
                                    Game + (*(int *)(Game + 0x71904) + 0x16) * 0x38 + 0xce6a0) >>
                 0x20));
    uVar4 = in_fpscr & 0xfffffff;
    in_fpscr = uVar4 | (uint)(*(float *)(Game + 0x81634) <
                             *(float *)(gGroup0 +
                                       Game + (*(int *)(Game + 0x71904) + 0x16) * 0x38 + 0xce6a0))
                       << 0x1f;
    if ((SUB41(in_fpscr >> 0x1f,0)) ||
       (in_fpscr = uVar4 | (uint)(*(float *)(gGroup0 +
                                            Game + (*(int *)(Game + 0x71904) + 0x16) * 0x38 +
                                            0xce6a0) == 0.0) << 0x1e, SUB41(in_fpscr >> 0x1e,0))) {
      wprintf("!! TIMETRIAL NEW FASTEST!!!");
      uVar4 = 1;
      iVar6 = Game;
    }
    else {
      wprintf("!! RIMETRIAL SLOWER !!!");
      uVar4 = 0;
      iVar6 = Game;
    }
  }
LAB_00061078:
  *(uint *)(this + 0x1c) = uVar4;
  *(int *)(this + 0x18) = param_1;
  *(int *)(this + 0x48) = param_1 * 100 + *(int *)(this + 0x44) + *(int *)(iVar6 + 0x81630);
  uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(iVar6 + 0xd14));
  *(undefined4 *)this = uVar1;
  tColour::tColour((tColour *)&local_40,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
  cRBorder::Init(uVar1,0x20400002,"Delivery>Complete!",0x14,0,0x42a00000,local_40,uStack_3c,
                 uStack_38,uStack_34,2,0);
  uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
  *(undefined4 *)(this + 4) = uVar1;
  if (*(int *)(this + 0x18) == 1) {
    tColour::tColour((tColour *)&local_50,extraout_s0_00,extraout_s1_00,extraout_s2_00,
                     extraout_s3_00);
    cRBorder::Init(uVar1,0x20400002," 0 Package Delivered",0x14,0,0x43200000,local_50,uStack_4c,
                   uStack_48,uStack_44,2,0);
  }
  else {
    tColour::tColour((tColour *)&local_60,extraout_s0_00,extraout_s1_00,extraout_s2_00,
                     extraout_s3_00);
    cRBorder::Init(uVar1,0x20400002,"00 Packages Delivered",0x14,0,0x43200000,local_60,uStack_5c,
                   uStack_58,uStack_54,2,0);
  }
  this_00 = (cRBorder *)cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
  iVar6 = *(int *)(Game + 0x71900);
  *(cRBorder **)(this + 8) = this_00;
  if (iVar6 == 0) {
    tColour::tColour((tColour *)&local_70,extraout_s0_01,extraout_s1_01,extraout_s2_01,
                     extraout_s3_01);
    iVar6 = -0x7bc8;
    local_90 = local_70;
    uStack_8c = uStack_6c;
    uStack_88 = uStack_68;
    uStack_84 = uStack_64;
  }
  else {
    if (iVar6 == 1) {
      tColour::tColour((tColour *)&local_80,extraout_s0_01,extraout_s1_01,extraout_s2_01,
                       extraout_s3_01);
      cRBorder::Init(this_00,0x20400002,"LEVEL COMPLETE!>",0x14,0,0x43970000,local_80,uStack_7c,
                     uStack_78,uStack_74,2,0);
      cRBorder::AddTextNumber(*(int *)(this + 8));
      iVar6 = *(int *)(this + 8);
      sVar3 = strlen((char *)(iVar6 + 0x2c4));
      memcpy((char *)(iVar6 + 0x2c4) + sVar3," Bonus Points",0xe);
      this_00 = *(cRBorder **)(this + 8);
      goto LAB_000611d8;
    }
    if (iVar6 != 4) goto LAB_000611d8;
    tColour::tColour((tColour *)&local_90,extraout_s0_01,extraout_s1_01,extraout_s2_01,
                     extraout_s3_01);
    iVar6 = -0x7b80;
  }
  cRBorder::Init(this_00,0x20400002,(int)&__DT_PLTGOT + iVar6,0x14,0,0x43970000,local_90,uStack_8c,
                 uStack_88,uStack_84,2,0);
  this_00 = *(cRBorder **)(this + 8);
LAB_000611d8:
  cRBorder::HideInit(this_00);
  *(undefined4 *)(this + 0x3c) = 0;
  *(undefined4 *)(this + 0x40) = 0x3d2aaaab;
  uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
  *(undefined4 *)(this + 0xc) = uVar1;
  if (*(int *)(this + 0x1c) == 0) {
    tColour::tColour((tColour *)&local_b0,extraout_s0_02,extraout_s1_02,extraout_s2_02,
                     extraout_s3_02);
    uVar8 = 0x43a00000;
    local_a0 = local_b0;
    uStack_9c = uStack_ac;
    uStack_98 = uStack_a8;
    uStack_94 = uStack_a4;
  }
  else {
    tColour::tColour((tColour *)&local_a0,extraout_s0_02,extraout_s1_02,extraout_s2_02,
                     extraout_s3_02);
    uVar8 = 0x43c80000;
  }
  cRBorder::Init(uVar1,0x20400002,"Touch Screen to>Continue",0x14,0,uVar8,local_a0,uStack_9c,
                 uStack_98,uStack_94,2,0);
  cRBorder::HideInit(*(cRBorder **)(this + 0xc));
  *(undefined4 *)(this + 0x28) = 0x3f555555;
  fVar9 = (float)VectorSignedToFloat(*(int *)(this + 0x18) + 1,(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)(this + 0x24) = 0;
  *(undefined4 *)(this + 0x20) = 0;
  iVar6 = Game;
  *(undefined4 *)(this + 0x10) = 1;
  this[0x14] = (cRCompletion)0x1;
  iVar6 = *(int *)(iVar6 + 0x71900);
  if (3.4 / fVar9 == 0.0) {
    fVar9 = 0.0;
  }
  else {
    fVar9 = 1.0 / ((3.4 / fVar9) * 60.0);
  }
  *(float *)(this + 0x2c) = fVar9;
  if (iVar6 == 4) {
    *(undefined4 *)(this + 0x10) = 3;
    cRBorder::HideInit(*(cRBorder **)this);
  }
  return;
}
