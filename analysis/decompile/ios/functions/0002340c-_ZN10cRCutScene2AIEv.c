/*
 * mangled: _ZN10cRCutScene2AIEv
 * demangled: cRCutScene::AI()
 * address: 0002340c
 * size: 2400
 */

/* cRCutScene::AI() */

void __thiscall cRCutScene::AI(cRCutScene *this)

{
  undefined *this_00;
  float fVar1;
  float fVar2;
  ushort *puVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  char *pcVar7;
  undefined4 uVar8;
  int iVar9;
  undefined4 local_a8;
  undefined4 uStack_a4;
  undefined4 uStack_a0;
  undefined4 uStack_9c;
  undefined4 local_98;
  undefined4 uStack_94;
  undefined4 uStack_90;
  undefined4 uStack_8c;
  undefined4 local_88;
  undefined4 uStack_84;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  float local_78;
  float local_74;
  float local_70;
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
  float local_38;
  float local_34;
  float local_30;
  undefined4 uStack_2c;
  float local_28;
  float local_24;
  float local_20;

  this[0x58] = (cRCutScene)0x0;
  switch(*(undefined4 *)(this + 0xc)) {
  case 1:
    *(undefined4 *)(this + 0xc) = 2;
    *(undefined4 *)(this + 0x50) = 0;
    *(undefined4 *)(this + 0x54) = 0x3c088889;
    this[0x58] = (cRCutScene)0x1;
    iVar9 = *(int *)this;
    puVar3 = *(ushort **)(*(int *)(iVar9 + 0x578) + 0x104);
    *(ushort **)(iVar9 + 0x104) = puVar3;
    if ((*puVar3 & 8) == 0) {
      *(undefined4 *)(iVar9 + 0xfc) = 0;
      *(float *)(iVar9 + 0x100) = ABS(*(float *)(puVar3 + 10));
    }
    else {
      fVar1 = *(float *)(puVar3 + 10);
      *(float *)(iVar9 + 0x100) = -ABS(fVar1);
      *(float *)(iVar9 + 0xfc) = -ABS(fVar1) + 1.0;
    }
    *(undefined4 *)(iVar9 + 0x134) = 0;
    *(int *)(iVar9 + 0x24) = *(int *)(iVar9 + 0x578);
    *(uint *)(*(int *)(iVar9 + 0x138) + 4) = *(uint *)(*(int *)(iVar9 + 0x138) + 4) | 0x20;
    iVar6 = *(int *)this;
    iVar9 = *(int *)(iVar6 + 0x134);
    *(undefined4 *)(iVar9 * 4 + iVar6 + 0x10c) = 9;
    *(int *)(iVar6 + 0x134) = iVar9 + 1;
    iVar6 = *(int *)this;
    iVar9 = *(int *)(iVar6 + 0x134);
    *(undefined4 *)(iVar9 * 4 + iVar6 + 0x10c) = 1;
    *(int *)(iVar6 + 0x134) = iVar9 + 1;
  case 2:
    *(undefined4 *)(this + 8) = 1;
    tMatrix::Identity((tMatrix *)(this + 0x10));
    iVar9 = *(int *)this;
    uVar4 = *(undefined4 *)(section_0000169c.segname + iVar9 + 0x24);
    uVar5 = *(undefined4 *)(section_0000169c.segname + iVar9 + 0x28);
    *(undefined4 *)(this + 0x40) = *(undefined4 *)(section_0000169c.segname + iVar9 + 0x20);
    *(undefined4 *)(this + 0x44) = uVar4;
    *(undefined4 *)(this + 0x48) = uVar5;
    tMatrix::LookAt((tMatrix *)(this + 0x10),(tVector *)(iVar9 + 0x5c));
    fVar1 = *(float *)(this + 0x50);
    *(float *)(this + 0x50) = fVar1 + *(float *)(this + 0x54);
    if (1.0 < fVar1 + *(float *)(this + 0x54)) {
      uVar4 = 8;
LAB_0002379c:
      *(undefined4 *)(this + 0xc) = uVar4;
      *(undefined4 *)(this + 0x50) = 0;
      *(undefined4 *)(this + 0x54) = 0x3c088889;
    }
    break;
  default:
    break;
  case 5:
    *(undefined4 *)(this + 0xc) = 7;
    *(undefined4 *)(this + 8) = 0xffffffff;
    iVar9 = *(int *)this;
    puVar3 = *(ushort **)(*(int *)(iVar9 + 0x504) + 0x104);
    *(ushort **)(iVar9 + 0x104) = puVar3;
    if ((*puVar3 & 8) == 0) {
      *(undefined4 *)(iVar9 + 0xfc) = 0;
      *(float *)(iVar9 + 0x100) = ABS(*(float *)(puVar3 + 10));
    }
    else {
      fVar1 = *(float *)(puVar3 + 10);
      *(float *)(iVar9 + 0x100) = -ABS(fVar1);
      *(float *)(iVar9 + 0xfc) = -ABS(fVar1) + 1.0;
    }
    *(undefined4 *)(iVar9 + 0x134) = 0;
    *(int *)(iVar9 + 0x24) = *(int *)(iVar9 + 0x504);
    *(uint *)(*(int *)(iVar9 + 0x138) + 4) = *(uint *)(*(int *)(iVar9 + 0x138) + 4) | 0x20;
    iVar6 = *(int *)this;
    iVar9 = *(int *)(iVar6 + 0x134);
    *(undefined4 *)(iVar9 * 4 + iVar6 + 0x10c) = 9;
    *(int *)(iVar6 + 0x134) = iVar9 + 1;
    iVar6 = *(int *)this;
    iVar9 = *(int *)(iVar6 + 0x134);
    *(undefined4 *)(iVar9 * 4 + iVar6 + 0x10c) = 9;
    *(int *)(iVar6 + 0x134) = iVar9 + 1;
    *(undefined4 *)(this + 0xc) = 6;
    *(undefined4 *)(this + 0x50) = 0;
    *(undefined4 *)(this + 0x54) = 0x3c088889;
    pcVar7 = segment_command_00001768.segname + *(int *)this + -8;
    pcVar7[0] = -0x77;
    pcVar7[1] = -0x78;
    pcVar7[2] = -0x78;
    pcVar7[3] = '<';
    *(undefined4 *)(section_00001724.segname + *(int *)this + 0x30) =
         *(undefined4 *)(segment_command_00001768.segname + *(int *)this + -8);
    this[0x58] = (cRCutScene)0x1;
    iVar6 = *(int *)PTR__Game_001b60b8;
    iVar9 = *(int *)(iVar6 + 0x72bd0);
    if (iVar9 == 0) {
      cRCompletion::Init((cRCompletion *)(iVar6 + 0x377e30),
                         *(int *)((int)&DAT_00003fe4 + *(int *)(this + 4)),
                         *(int *)((int)&DAT_00003fe4 + *(int *)(this + 4)) ==
                         *(int *)(iVar6 + 0x73e74));
    }
    else if (iVar9 == 1) {
      cRCompletion::Init((cRCompletion *)(iVar6 + 0x377e30),
                         *(int *)((int)&DAT_00003fe4 + *(int *)(this + 4)),true);
    }
    else if (iVar9 == 4) {
      cRCompletion::Init((cRCompletion *)(iVar6 + 0x377e30),0,false);
    }
    cRSound::Play((cRSound *)PTR__gRSound_001b61e0,0x2f);
  case 6:
    *(undefined4 *)(this + 8) = 0xffffffff;
    tMatrix::Identity((tMatrix *)&local_a8);
    iVar9 = *(int *)this;
    local_38 = *(float *)(section_00001658.segname + iVar9 + 0x1c);
    local_34 = *(float *)(section_00001658.segname + iVar9 + 0x20);
    local_30 = *(float *)(section_00001658.segname + iVar9 + 0x24);
    fVar1 = *(float *)(this + 0x50);
    fVar2 = local_38 + (*(float *)(section_0000169c.segname + iVar9 + 0x20) - local_38) * fVar1;
    local_74 = local_34 + (*(float *)(section_0000169c.segname + iVar9 + 0x24) - local_34) * fVar1;
    local_70 = local_30 + (*(float *)(section_0000169c.segname + iVar9 + 0x28) - local_30) * fVar1;
    local_78 = fVar2;
    fVar1 = (float)Sin(fVar1 * 3.1415927);
    local_78 = fVar2 + fVar1 * -0.5;
    tMatrix::LookAt((tMatrix *)&local_a8,(tVector *)(*(int *)this + 0x5c));
    iVar9 = *(int *)(*(int *)this + 0xf4);
    local_68 = *(undefined4 *)(iVar9 + 0x1e8);
    uStack_64 = *(undefined4 *)(iVar9 + 0x1ec);
    uStack_60 = *(undefined4 *)(iVar9 + 0x1f0);
    uStack_5c = *(undefined4 *)(iVar9 + 500);
    local_58 = *(undefined4 *)(iVar9 + 0x1f8);
    uStack_54 = *(undefined4 *)(iVar9 + 0x1fc);
    uStack_50 = *(undefined4 *)(iVar9 + 0x200);
    uStack_4c = *(undefined4 *)(iVar9 + 0x204);
    local_48 = *(undefined4 *)(iVar9 + 0x208);
    uStack_44 = *(undefined4 *)(iVar9 + 0x20c);
    uStack_40 = *(undefined4 *)(iVar9 + 0x210);
    uStack_3c = *(undefined4 *)(iVar9 + 0x214);
    local_38 = *(float *)(iVar9 + 0x218);
    local_34 = *(float *)(iVar9 + 0x21c);
    local_30 = *(float *)(iVar9 + 0x220);
    uStack_2c = *(undefined4 *)(iVar9 + 0x224);
    fVar1 = (float)Sin(*(float *)(this + 0x50) * 1.5707964);
    tMatrix::LinearInterpolate
              ((tMatrix *)(this + 0x10),(tMatrix *)&local_68,(tMatrix *)&local_a8,fVar1);
    fVar1 = *(float *)(this + 0x50);
    *(float *)(this + 0x50) = fVar1 + *(float *)(this + 0x54);
    if (1.0 < fVar1 + *(float *)(this + 0x54)) {
      uVar4 = 7;
LAB_00023674:
      *(undefined4 *)(this + 0xc) = uVar4;
      *(undefined4 *)(this + 0x50) = 0;
      *(undefined4 *)(this + 0x54) = 0x3c888889;
    }
    break;
  case 7:
    *(undefined4 *)(this + 8) = 0xffffffff;
    this[0x58] = (cRCutScene)0x1;
    tMatrix::Identity((tMatrix *)(this + 0x10));
    iVar9 = *(int *)this;
    uVar4 = *(undefined4 *)(section_0000169c.segname + iVar9 + 0x24);
    uVar5 = *(undefined4 *)(section_0000169c.segname + iVar9 + 0x28);
    *(undefined4 *)(this + 0x40) = *(undefined4 *)(section_0000169c.segname + iVar9 + 0x20);
    *(undefined4 *)(this + 0x44) = uVar4;
    *(undefined4 *)(this + 0x48) = uVar5;
    tMatrix::LookAt((tMatrix *)(this + 0x10),(tVector *)(iVar9 + 0x5c));
    iVar9 = *(int *)this;
    if (*(int *)(iVar9 + 0x134) == 0) {
      *(undefined4 *)(iVar9 + 0x10c) = 9;
      *(undefined4 *)(iVar9 + 0x134) = 1;
    }
    goto LAB_000234c4;
  case 8:
    *(undefined1 *)(*(int *)PTR__Game_001b60b8 + 0x820f0) = 0;
    *(undefined4 *)(this + 8) = 1;
    tMatrix::Identity((tMatrix *)&local_68);
    iVar9 = *(int *)this;
    fVar1 = *(float *)(section_0000169c.segname + iVar9 + 0x20);
    local_34 = *(float *)(section_0000169c.segname + iVar9 + 0x24);
    local_30 = *(float *)(section_0000169c.segname + iVar9 + 0x28);
    local_38 = fVar1;
    fVar2 = (float)Sin(*(float *)(this + 0x50) * 3.1415927);
    local_38 = fVar1 + fVar2 + fVar2;
    tMatrix::LookAt((tMatrix *)&local_68,(tVector *)(*(int *)this + 0x5c));
    iVar9 = *(int *)(*(int *)this + 0xf4);
    local_a8 = *(undefined4 *)(iVar9 + 0x1e8);
    uStack_a4 = *(undefined4 *)(iVar9 + 0x1ec);
    uStack_a0 = *(undefined4 *)(iVar9 + 0x1f0);
    uStack_9c = *(undefined4 *)(iVar9 + 500);
    local_98 = *(undefined4 *)(iVar9 + 0x1f8);
    uStack_94 = *(undefined4 *)(iVar9 + 0x1fc);
    uStack_90 = *(undefined4 *)(iVar9 + 0x200);
    uStack_8c = *(undefined4 *)(iVar9 + 0x204);
    local_88 = *(undefined4 *)(iVar9 + 0x208);
    uStack_84 = *(undefined4 *)(iVar9 + 0x20c);
    uStack_80 = *(undefined4 *)(iVar9 + 0x210);
    uStack_7c = *(undefined4 *)(iVar9 + 0x214);
    local_78 = *(float *)(iVar9 + 0x218);
    local_74 = *(float *)(iVar9 + 0x21c);
    local_70 = *(float *)(iVar9 + 0x220);
    uStack_6c = *(undefined4 *)(iVar9 + 0x224);
    fVar1 = (float)Sin(*(float *)(this + 0x50) * 1.5707964);
    tMatrix::LinearInterpolate
              ((tMatrix *)(this + 0x10),(tMatrix *)&local_68,(tMatrix *)&local_a8,fVar1);
    iVar9 = *(int *)this;
    local_28 = *(float *)(this + 0x40) - *(float *)(iVar9 + 0x5c);
    local_24 = *(float *)(this + 0x44) - *(float *)(iVar9 + 0x60);
    local_20 = *(float *)(this + 0x48) - *(float *)(iVar9 + 100);
    fVar1 = (float)tVector::Normalize((tVector *)&local_28);
    if (fVar1 < 1.5) {
      fVar1 = 1.5 - fVar1;
      *(float *)(this + 0x40) = *(float *)(this + 0x40) + fVar1 * local_28;
      *(float *)(this + 0x44) = *(float *)(this + 0x44) + fVar1 * local_24;
      *(float *)(this + 0x48) = *(float *)(this + 0x48) + fVar1 * local_20;
    }
    fVar1 = *(float *)(this + 0x50);
    *(float *)(this + 0x50) = fVar1 + *(float *)(this + 0x54);
    if (fVar1 + *(float *)(this + 0x54) <= 1.0) {
      return;
    }
    uVar4 = 9;
    goto LAB_0002379c;
  case 9:
    iVar9 = *(int *)(*(int *)this + 0xf4);
    uVar4 = *(undefined4 *)(iVar9 + 0x1ec);
    uVar5 = *(undefined4 *)(iVar9 + 0x1f0);
    uVar8 = *(undefined4 *)(iVar9 + 500);
    *(undefined4 *)(this + 0x10) = *(undefined4 *)(iVar9 + 0x1e8);
    *(undefined4 *)(this + 0x14) = uVar4;
    *(undefined4 *)(this + 0x18) = uVar5;
    *(undefined4 *)(this + 0x1c) = uVar8;
    uVar4 = *(undefined4 *)(iVar9 + 0x1fc);
    uVar5 = *(undefined4 *)(iVar9 + 0x200);
    uVar8 = *(undefined4 *)(iVar9 + 0x204);
    *(undefined4 *)(this + 0x20) = *(undefined4 *)(iVar9 + 0x1f8);
    *(undefined4 *)(this + 0x24) = uVar4;
    *(undefined4 *)(this + 0x28) = uVar5;
    *(undefined4 *)(this + 0x2c) = uVar8;
    uVar4 = *(undefined4 *)(iVar9 + 0x20c);
    uVar5 = *(undefined4 *)(iVar9 + 0x210);
    uVar8 = *(undefined4 *)(iVar9 + 0x214);
    *(undefined4 *)(this + 0x30) = *(undefined4 *)(iVar9 + 0x208);
    *(undefined4 *)(this + 0x34) = uVar4;
    *(undefined4 *)(this + 0x38) = uVar5;
    *(undefined4 *)(this + 0x3c) = uVar8;
    uVar4 = *(undefined4 *)(iVar9 + 0x21c);
    uVar5 = *(undefined4 *)(iVar9 + 0x220);
    uVar8 = *(undefined4 *)(iVar9 + 0x224);
    *(undefined4 *)(this + 0x40) = *(undefined4 *)(iVar9 + 0x218);
    *(undefined4 *)(this + 0x44) = uVar4;
    *(undefined4 *)(this + 0x48) = uVar5;
    *(undefined4 *)(this + 0x4c) = uVar8;
    *(undefined4 *)(this + 0xc) = 0;
    return;
  case 10:
    *(undefined4 *)(this + 8) = 0xffffffff;
    iVar9 = *(int *)this;
    puVar3 = *(ushort **)(*(int *)(iVar9 + 0x490) + 0x104);
    *(ushort **)(iVar9 + 0x104) = puVar3;
    if ((*puVar3 & 8) == 0) {
      *(undefined4 *)(iVar9 + 0xfc) = 0;
      *(float *)(iVar9 + 0x100) = ABS(*(float *)(puVar3 + 10));
    }
    else {
      fVar1 = *(float *)(puVar3 + 10);
      *(float *)(iVar9 + 0x100) = -ABS(fVar1);
      *(float *)(iVar9 + 0xfc) = -ABS(fVar1) + 1.0;
    }
    *(undefined4 *)(iVar9 + 0x134) = 0;
    *(int *)(iVar9 + 0x24) = *(int *)(iVar9 + 0x490);
    this_00 = PTR__gVoiceManager_001b61d8;
    *(uint *)(*(int *)(iVar9 + 0x138) + 4) = *(uint *)(*(int *)(iVar9 + 0x138) + 4) | 0x20;
    *(undefined4 *)(this + 0xc) = 0xb;
    *(undefined4 *)(this + 0x50) = 0;
    this[0x58] = (cRCutScene)0x1;
    *(undefined4 *)(this + 0x54) = 0x3c088889;
    cRVoiceManager::Play((cRVoiceManager *)this_00,3,2,-1);
    *(undefined1 *)(*(int *)(*(int *)this + 0xf4) + 0x43c) = 1;
    cRSnail::ReleaseWeapons(*(cRSnail **)this);
  case 0xb:
    *(undefined4 *)(this + 8) = 0xffffffff;
    tMatrix::Identity((tMatrix *)&local_a8);
    iVar9 = *(int *)this;
    fVar1 = *(float *)(section_0000169c.segname + iVar9 + 0x20);
    local_74 = *(float *)(section_0000169c.segname + iVar9 + 0x24);
    local_70 = *(float *)(section_0000169c.segname + iVar9 + 0x28);
    local_78 = fVar1;
    fVar2 = (float)Sin(*(float *)(this + 0x50) * 3.1415927);
    local_78 = fVar1 + fVar2 + fVar2;
    if (local_74 < 0.0) {
      local_74 = 0.0;
    }
    tMatrix::LookAt((tMatrix *)&local_a8,(tVector *)(*(int *)this + 0x5c));
    iVar9 = *(int *)(*(int *)this + 0xf4);
    local_68 = *(undefined4 *)(iVar9 + 0x1e8);
    uStack_64 = *(undefined4 *)(iVar9 + 0x1ec);
    uStack_60 = *(undefined4 *)(iVar9 + 0x1f0);
    uStack_5c = *(undefined4 *)(iVar9 + 500);
    local_58 = *(undefined4 *)(iVar9 + 0x1f8);
    uStack_54 = *(undefined4 *)(iVar9 + 0x1fc);
    uStack_50 = *(undefined4 *)(iVar9 + 0x200);
    uStack_4c = *(undefined4 *)(iVar9 + 0x204);
    local_48 = *(undefined4 *)(iVar9 + 0x208);
    uStack_44 = *(undefined4 *)(iVar9 + 0x20c);
    uStack_40 = *(undefined4 *)(iVar9 + 0x210);
    uStack_3c = *(undefined4 *)(iVar9 + 0x214);
    local_38 = *(float *)(iVar9 + 0x218);
    local_34 = *(float *)(iVar9 + 0x21c);
    local_30 = *(float *)(iVar9 + 0x220);
    uStack_2c = *(undefined4 *)(iVar9 + 0x224);
    fVar1 = (float)Sin(*(float *)(this + 0x50) * 1.5707964);
    tMatrix::LinearInterpolate
              ((tMatrix *)(this + 0x10),(tMatrix *)&local_68,(tMatrix *)&local_a8,fVar1);
    fVar1 = *(float *)(this + 0x50);
    *(float *)(this + 0x50) = fVar1 + *(float *)(this + 0x54);
    if (fVar1 + *(float *)(this + 0x54) <= 1.0) {
      return;
    }
    uVar4 = 0xc;
    goto LAB_00023674;
  case 0xc:
    *(undefined4 *)(this + 8) = 0xffffffff;
    this[0x58] = (cRCutScene)0x1;
    tMatrix::Identity((tMatrix *)(this + 0x10));
    iVar9 = *(int *)this;
    uVar4 = *(undefined4 *)(section_0000169c.segname + iVar9 + 0x24);
    uVar5 = *(undefined4 *)(section_0000169c.segname + iVar9 + 0x28);
    *(undefined4 *)(this + 0x40) = *(undefined4 *)(section_0000169c.segname + iVar9 + 0x20);
    *(undefined4 *)(this + 0x44) = uVar4;
    *(undefined4 *)(this + 0x48) = uVar5;
    if (*(float *)(this + 0x44) < 0.0) {
      *(undefined4 *)(this + 0x44) = 0;
    }
    tMatrix::LookAt((tMatrix *)(this + 0x10),(tVector *)(iVar9 + 0x5c));
    iVar9 = *(int *)(this + 4);
    if (*(char *)(iVar9 + 0x78) != '\0') goto LAB_000234c4;
    switch(*(undefined4 *)(*(int *)(iVar9 + 0x3f8) + 0x58)) {
    case 0:
      if (0 < *(int *)(::__static_initialization_and_destruction_0 + iVar9 + 4)) {
        SetGameState(1,*(int *)(iVar9 + 0x2cc),*(int *)(*(int *)(iVar9 + 0x3f8) + 0x5c),
                     *(int *)(::__static_initialization_and_destruction_0 + iVar9 + 4) + -1);
        goto switchD_00023c20_caseD_7;
      }
      SetGameState(0,0,0,0);
      *(undefined4 *)(iVar9 + 0x74) = 1;
      break;
    case 1:
    case 4:
      *(undefined4 *)(iVar9 + 0x74) = 1;
      break;
    default:
      goto switchD_00023c20_caseD_2;
    case 7:
switchD_00023c20_caseD_7:
      *(undefined4 *)(iVar9 + 0x74) = 0;
    }
    *(undefined1 *)(iVar9 + 0x78) = 1;
    *(undefined4 *)(iVar9 + 0x80) = 0;
    *(undefined4 *)(iVar9 + 0x84) = 0x3c088889;
    iVar9 = *(int *)(this + 4);
switchD_00023c20_caseD_2:
    if (*(char *)(iVar9 + 0x43d) == '\0') {
      cRVoiceManager::Play((cRVoiceManager *)PTR__gVoiceManager_001b61d8,0xb,2,-1);
      *(undefined1 *)(*(int *)(this + 4) + 0x43d) = 1;
      *(undefined1 *)(*(int *)(this + 4) + 0x43c) = 1;
    }
LAB_000234c4:
    *(float *)(this + 0x50) = *(float *)(this + 0x50) + *(float *)(this + 0x54);
  }
  return;
}
