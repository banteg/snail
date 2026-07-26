/*
 * mangled: _ZN6cRExit4InitEv
 * demangled: cRExit::Init()
 * address: 0006ae00
 * size: 2352
 */

/* cRExit::Init() */

void __thiscall cRExit::Init(cRExit *this)

{
  undefined4 uVar1;
  tColour *this_00;
  tColour *ptVar2;
  undefined4 uVar3;
  float fVar4;
  undefined4 uVar5;
  undefined4 local_158;
  undefined4 uStack_154;
  undefined4 uStack_150;
  undefined4 uStack_14c;
  undefined4 local_148;
  undefined4 uStack_144;
  undefined4 uStack_140;
  undefined4 uStack_13c;
  undefined4 local_138;
  undefined4 uStack_134;
  undefined4 uStack_130;
  undefined4 uStack_12c;
  undefined4 local_128;
  undefined4 uStack_124;
  undefined4 uStack_120;
  undefined4 uStack_11c;
  undefined4 local_118;
  undefined4 uStack_114;
  undefined4 uStack_110;
  undefined4 uStack_10c;
  undefined4 local_108;
  undefined4 uStack_104;
  undefined4 uStack_100;
  undefined4 uStack_fc;
  undefined4 local_f8;
  undefined4 uStack_f4;
  undefined4 uStack_f0;
  undefined4 uStack_ec;
  undefined4 local_e8;
  undefined4 uStack_e4;
  undefined4 uStack_e0;
  undefined4 uStack_dc;
  undefined4 local_d8;
  undefined4 uStack_d4;
  undefined4 uStack_d0;
  undefined4 uStack_cc;
  undefined4 local_c8;
  undefined4 uStack_c4;
  undefined4 uStack_c0;
  undefined4 uStack_bc;
  undefined4 local_b8;
  undefined4 uStack_b4;
  undefined4 uStack_b0;
  undefined4 uStack_ac;
  tColour local_a8 [16];
  undefined4 local_98;
  undefined4 uStack_94;
  undefined4 uStack_90;
  undefined4 uStack_8c;
  undefined4 local_88;
  undefined4 uStack_84;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  tColour atStack_78 [16];
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

  cRBorderManager::HideBorders((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
  switch(*(undefined4 *)this) {
  case 2:
  case 7:
    uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
    *(undefined4 *)(this + 0x10) = uVar1;
    tColour::tColour((tColour *)&local_b8,1.0,1.0,1.0,1.0);
    cRBorder::Init(uVar1,&DAT_00400002,"Do you really want to quit?",0x14,0,0x43480000,local_b8,
                   uStack_b4,uStack_b0,uStack_ac,2,0);
    uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
    *(undefined4 *)(this + 0x14) = uVar1;
    tColour::tColour((tColour *)&local_c8,1.0,1.0,1.0,1.0);
    cRBorder::Init(uVar1,0x40000014,"Yes",0x14,0,0x43a50000,local_c8,uStack_c4,uStack_c0,uStack_bc,2
                   ,0xc2a00000);
    cRBorder::SetBelow(*(cRBorder **)(this + 0x14),*(cRBorder **)(this + 0x10));
    uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
    *(undefined4 *)(this + 0x18) = uVar1;
    tColour::tColour((tColour *)&local_d8,1.0,1.0,1.0,1.0);
    uVar5 = 0;
    uVar3 = 0x43a50000;
    break;
  case 3:
    uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
    *(undefined4 *)(this + 0x10) = uVar1;
    tColour::tColour((tColour *)&local_e8,1.0,1.0,1.0,1.0);
    cRBorder::Init(uVar1,&DAT_00400002,"Do you really want to quit?",0x14,0,0x43480000,local_e8,
                   uStack_e4,uStack_e0,uStack_dc,2,0);
    uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
    *(undefined4 *)(this + 0x14) = uVar1;
    tColour::tColour((tColour *)&local_f8,1.0,1.0,1.0,1.0);
    cRBorder::Init(uVar1,0x40000014,"Yes",0x14,0,0x43a50000,local_f8,uStack_f4,uStack_f0,uStack_ec,2
                   ,0xc2a00000);
    cRBorder::SetBelow(*(cRBorder **)(this + 0x14),*(cRBorder **)(this + 0x10));
    uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
    *(undefined4 *)(this + 0x18) = uVar1;
    tColour::tColour((tColour *)&local_108,1.0,1.0,1.0,1.0);
    uVar5 = 0;
    uVar3 = 0x43a50000;
    local_d8 = local_108;
    uStack_d4 = uStack_104;
    uStack_d0 = uStack_100;
    uStack_cc = uStack_fc;
    break;
  case 4:
    uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
    *(undefined4 *)(this + 0x10) = uVar1;
    tColour::tColour((tColour *)&local_118,1.0,1.0,1.0,1.0);
    cRBorder::Init(uVar1,&DAT_00400002,"Do you really want to quit?",0x14,0,0x43480000,local_118,
                   uStack_114,uStack_110,uStack_10c,2,0);
    uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
    *(undefined4 *)(this + 0x14) = uVar1;
    tColour::tColour((tColour *)&local_128,1.0,1.0,1.0,1.0);
    cRBorder::Init(uVar1,0x40000014,"Yes",0x14,0x43ea0000,0x43ba8000,local_128,uStack_124,uStack_120
                   ,uStack_11c,2,0xc2a00000);
    cRBorder::SetBelow(*(cRBorder **)(this + 0x14),*(cRBorder **)(this + 0x10));
    uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
    *(undefined4 *)(this + 0x18) = uVar1;
    tColour::tColour((tColour *)&local_138,1.0,1.0,1.0,1.0);
    uVar5 = 0x440e0000;
    uVar3 = 0x43940000;
    local_d8 = local_138;
    uStack_d4 = uStack_134;
    uStack_d0 = uStack_130;
    uStack_cc = uStack_12c;
    break;
  case 5:
    uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
    *(undefined4 *)(this + 0x14) = uVar1;
    tColour::tColour((tColour *)&local_148,1.0,1.0,1.0,1.0);
    cRBorder::Init(uVar1,0x14,"Yes",0x14,0x43ec8000,0x42040000,local_148,uStack_144,uStack_140,
                   uStack_13c,0,0);
    uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
    *(undefined4 *)(this + 0x18) = uVar1;
    tColour::tColour((tColour *)&local_158,1.0,1.0,1.0,1.0);
    cRBorder::Init(uVar1,0x14,"No",0x14,0x440d8000,0x42d80000,local_158,uStack_154,uStack_150,
                   uStack_14c,0,0);
    return;
  default:
    goto switchD_0006ae3c_caseD_6;
  case 9:
    uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
    fVar4 = *(float *)(this + 0xc) - 54.0;
    *(undefined4 *)(this + 0x14) = uVar1;
    tColour::tColour((tColour *)&local_38,1.0,1.0,1.0,1.0);
    cRBorder::Init(uVar1,0x14,"Yes",0x14,0,fVar4,local_38,uStack_34,uStack_30,uStack_2c,2,0x430c0000
                  );
    uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
    uVar3 = *(undefined4 *)(this + 0xc);
    *(undefined4 *)(this + 0x18) = uVar1;
    tColour::tColour((tColour *)&local_48,1.0,1.0,1.0,1.0);
    cRBorder::Init(uVar1,0x14,"No",0x14,0,uVar3,local_48,uStack_44,uStack_40,uStack_3c,2,0x43860000)
    ;
    return;
  case 10:
    uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
    *(undefined4 *)(this + 0x10) = uVar1;
    tColour::tColour((tColour *)&local_58,1.0,1.0,1.0,1.0);
    cRBorder::Init(uVar1,&DAT_00400002,"Do you really want to quit?",0x14,0,0x43480000,local_58,
                   uStack_54,uStack_50,uStack_4c,2,0);
    uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
    uVar3 = *(undefined4 *)(this + 0xc);
    *(undefined4 *)(this + 0x14) = uVar1;
    tColour::tColour((tColour *)&local_68,1.0,1.0,1.0,1.0);
    ptVar2 = atStack_78;
    cRBorder::Init(uVar1,0x40000014,"Yes",0x14,0,uVar3,local_68,uStack_64,uStack_60,uStack_5c,2,
                   0xc2a00000);
    cRBorder::SetBelow(*(cRBorder **)(this + 0x14),*(cRBorder **)(this + 0x10));
    uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
    uVar3 = *(undefined4 *)(this + 0xc);
    *(undefined4 *)(this + 0x18) = uVar1;
    this_00 = atStack_78;
    goto LAB_0006afa0;
  case 0xb:
    uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
    *(undefined4 *)(this + 0x10) = uVar1;
    tColour::tColour((tColour *)&local_88,1.0,1.0,1.0,1.0);
    cRBorder::Init(uVar1,&DAT_00400002,"Do you really want to quit?",0x14,0,0x43480000,local_88,
                   uStack_84,uStack_80,uStack_7c,2,0);
    uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
    uVar3 = *(undefined4 *)(this + 0xc);
    *(undefined4 *)(this + 0x14) = uVar1;
    tColour::tColour((tColour *)&local_98,1.0,1.0,1.0,1.0);
    ptVar2 = local_a8;
    cRBorder::Init(uVar1,0x40000014,"Yes",0x14,0,uVar3,local_98,uStack_94,uStack_90,uStack_8c,2,
                   0xc2a00000);
    cRBorder::SetBelow(*(cRBorder **)(this + 0x14),*(cRBorder **)(this + 0x10));
    uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
    uVar3 = *(undefined4 *)(this + 0xc);
    *(undefined4 *)(this + 0x18) = uVar1;
    this_00 = local_a8;
LAB_0006afa0:
    tColour::tColour(this_00,1.0,1.0,1.0,1.0);
    uVar5 = 0;
    local_d8 = *(undefined4 *)ptVar2;
    uStack_d4 = *(undefined4 *)(ptVar2 + 4);
    uStack_d0 = *(undefined4 *)(ptVar2 + 8);
    uStack_cc = *(undefined4 *)(ptVar2 + 0xc);
  }
  cRBorder::Init(uVar1,0x14,"No",0x14,uVar5,uVar3,local_d8,uStack_d4,uStack_d0,uStack_cc,2,
                 0x42a00000);
  cRBorder::SetBelow(*(cRBorder **)(this + 0x18),*(cRBorder **)(this + 0x10));
switchD_0006ae3c_caseD_6:
  return;
}
