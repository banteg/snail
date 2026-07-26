/*
 * mangled: _ZN12cRCompletion4InitEib
 * demangled: cRCompletion::Init(int, bool)
 * address: 0006258c
 * size: 1580
 */

/* cRCompletion::Init(int, bool) */

void __thiscall cRCompletion::Init(cRCompletion *this,int param_1,bool param_2)

{
  undefined *puVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  undefined4 uVar6;
  uint uVar7;
  tColour *ptVar8;
  uint in_fpscr;
  float fVar9;
  tColour atStack_a0 [16];
  tColour local_90 [16];
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
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;

  puVar1 = PTR__Game_001b60b8;
  uVar4 = (uint)param_2;
  iVar3 = *(int *)PTR__Game_001b60b8;
  iVar5 = *(int *)(iVar3 + 0x72bd0);
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
    if ((&DAT_00353544)[iVar3] == '\0') {
      iVar5 = *(int *)(PTR__gConfig_001b60d4 + 0x48);
      iVar3 = *(int *)(PTR__gConfig_001b60d4 + 0x40);
    }
    else {
      iVar5 = *(int *)(*(int *)(&DAT_00353548 + iVar3) + 0x50);
      iVar3 = *(int *)(*(int *)(&DAT_00353548 + iVar3) + 0x4c);
    }
    uVar7 = iVar5 / 0x14;
    iVar3 = iVar3 / 0x14;
    if (4 < (int)uVar7) {
      uVar7 = 5;
    }
    uVar7 = uVar7 & ~((int)uVar7 >> 0x1f);
    if (iVar3 < 0) {
      iVar3 = 0;
    }
    else {
      if (4 < iVar3) {
        iVar3 = 5;
      }
      if (uVar7 == 5 && iVar3 == 5) {
        *(undefined4 *)(this + 0x44) = 500000;
        goto LAB_000625d8;
      }
    }
    *(int *)(this + 0x44) =
         (&_gBonusScoreSpeed)[iVar3] + *(int *)(&_gBonusScoreDifficulty + uVar7 * 4);
  }
  else if (iVar5 == 4) {
    wprintf("Your time %f\n",SUB84((double)*(float *)(iVar3 + 0x82290),0),
            (int)((ulonglong)(double)*(float *)(iVar3 + 0x82290) >> 0x20));
    iVar3 = *(int *)puVar1;
    wprintf("Best Time %f\n",
            SUB84((double)*(float *)(&DAT_003131fc + *(int *)(iVar3 + 0x72bd4) * 0x38 + iVar3),0),
            (int)((ulonglong)
                  (double)*(float *)(&DAT_003131fc + *(int *)(iVar3 + 0x72bd4) * 0x38 + iVar3) >>
                 0x20));
    iVar3 = *(int *)puVar1;
    uVar4 = in_fpscr & 0xfffffff;
    in_fpscr = uVar4 | (uint)(*(float *)(iVar3 + 0x82290) <
                             *(float *)(&DAT_003131fc + *(int *)(iVar3 + 0x72bd4) * 0x38 + iVar3))
                       << 0x1f;
    if ((SUB41(in_fpscr >> 0x1f,0)) ||
       (in_fpscr = uVar4 | (uint)(*(float *)(&DAT_003131fc +
                                            *(int *)(iVar3 + 0x72bd4) * 0x38 + iVar3) == 0.0) <<
                           0x1e, SUB41(in_fpscr >> 0x1e,0))) {
      wprintf("!! TIMETRIAL NEW FASTEST!!!");
      uVar4 = 1;
    }
    else {
      wprintf("!! RIMETRIAL SLOWER !!!");
      uVar4 = 0;
    }
  }
LAB_000625d8:
  *(int *)(this + 0x18) = param_1;
  *(uint *)(this + 0x1c) = uVar4;
  *(int *)(this + 0x48) =
       *(int *)(this + 0x44) + *(int *)(*(int *)PTR__Game_001b60b8 + 0x8228c) + param_1 * 100;
  uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
  *(undefined4 *)this = uVar2;
  tColour::tColour((tColour *)&local_30,1.0,1.0,1.0,1.0);
  cRBorder::Init(uVar2,0x20400002,"Delivery>Complete!",0x14,0,0x42a00000,local_30,uStack_2c,
                 uStack_28,uStack_24,2,0);
  uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
  *(undefined4 *)(this + 4) = uVar2;
  if (*(int *)(this + 0x18) == 1) {
    tColour::tColour((tColour *)&local_40,1.0,1.0,1.0,1.0);
    cRBorder::Init(uVar2,0x20400002," 0 Package Delivered",0x14,0,0x43200000,local_40,uStack_3c,
                   uStack_38,uStack_34,2,0);
  }
  else {
    tColour::tColour((tColour *)&local_50,1.0,1.0,1.0,1.0);
    cRBorder::Init(uVar2,0x20400002,"00 Packages Delivered",0x14,0,0x43200000,local_50,uStack_4c,
                   uStack_48,uStack_44,2,0);
  }
  puVar1 = PTR__Game_001b60b8;
  uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
  *(undefined4 *)(this + 8) = uVar2;
  iVar3 = *(int *)(*(int *)puVar1 + 0x72bd0);
  if (iVar3 == 0) {
    tColour::tColour((tColour *)&local_60,1.0,1.0,1.0,1.0);
    cRBorder::Init(uVar2,0x20400002,"PERFECT SCORE!>50,000 Bonus Points",0x14,0,0x43970000,local_60,
                   uStack_5c,uStack_58,uStack_54,2,0);
  }
  else if (iVar3 == 1) {
    tColour::tColour((tColour *)&local_70,1.0,1.0,1.0,1.0);
    cRBorder::Init(uVar2,0x20400002,"LEVEL COMPLETE!>",0x14,0,0x43970000,local_70,uStack_6c,
                   uStack_68,uStack_64,2,0);
    cRBorder::AddTextNumber(*(cRBorder **)(this + 8),*(int *)(this + 0x44));
    _strcat((char *)(*(int *)(this + 8) + 0x2c4)," Bonus Points");
  }
  else if (iVar3 == 4) {
    tColour::tColour((tColour *)&local_80,1.0,1.0,1.0,1.0);
    cRBorder::Init(uVar2,0x20400002,"NEW FASTEST TIME!",0x14,0,0x43970000,local_80,uStack_7c,
                   uStack_78,uStack_74,2,0);
  }
  cRBorder::HideInit(*(cRBorder **)(this + 8));
  *(undefined4 *)(this + 0x3c) = 0;
  puVar1 = PTR__Game_001b60b8;
  *(undefined4 *)(this + 0x40) = 0x3d2aaaab;
  uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)puVar1 + 0xd14));
  *(undefined4 *)(this + 0xc) = uVar2;
  if (*(int *)(this + 0x1c) == 0) {
    tColour::tColour(atStack_a0,1.0,1.0,1.0,1.0);
    uVar6 = 0x43a00000;
    ptVar8 = atStack_a0;
  }
  else {
    tColour::tColour(local_90,1.0,1.0,1.0,1.0);
    uVar6 = 0x43c80000;
    ptVar8 = local_90;
  }
  cRBorder::Init(uVar2,0x20400002,"Touch Screen to>Continue",0x14,0,uVar6,*(undefined4 *)ptVar8,
                 *(undefined4 *)(ptVar8 + 4),*(undefined4 *)(ptVar8 + 8),
                 *(undefined4 *)(ptVar8 + 0xc),2,0);
  cRBorder::HideInit(*(cRBorder **)(this + 0xc));
  *(undefined4 *)(this + 0x10) = 1;
  *(undefined4 *)(this + 0x20) = 0;
  *(undefined4 *)(this + 0x24) = 0;
  *(undefined4 *)(this + 0x28) = 0x3f555555;
  this[0x14] = (cRCompletion)0x1;
  puVar1 = PTR__Game_001b60b8;
  fVar9 = (float)VectorSignedToFloat(*(int *)(this + 0x18) + 1,(byte)(in_fpscr >> 0x16) & 3);
  if (3.4 / fVar9 == 0.0) {
    fVar9 = 0.0;
  }
  else {
    fVar9 = 1.0 / ((3.4 / fVar9) * 60.0);
  }
  *(float *)(this + 0x2c) = fVar9;
  if (*(int *)(*(int *)puVar1 + 0x72bd0) == 4) {
    *(undefined4 *)(this + 0x10) = 3;
    cRBorder::HideInit(*(cRBorder **)this);
  }
  return;
}
