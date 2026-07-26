/*
 * mangled: _ZN10cRCutScene2AIEv
 * demangled: cRCutScene::AI()
 * address: 00072a5c
 * size: 2044
 */

/* cRCutScene::AI() */

void __thiscall cRCutScene::AI(cRCutScene *this)

{
  float fVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  cRSnail *this_00;
  undefined4 uVar5;
  int iVar6;
  float fVar7;
  float fVar8;
  undefined4 local_a4;
  undefined4 uStack_a0;
  undefined4 uStack_9c;
  undefined4 uStack_98;
  undefined4 local_94;
  undefined4 uStack_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  undefined4 local_84;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined4 uStack_78;
  float local_74;
  float local_70;
  float local_6c;
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
  float local_34;
  float local_30;
  float local_2c;
  undefined4 uStack_28;
  float local_24;
  float local_20;
  float local_1c;

  this[0x58] = (cRCutScene)0x0;
  switch(*(undefined4 *)(this + 0xc)) {
  case 1:
    this[0x58] = (cRCutScene)0x1;
    *(undefined4 *)(this + 0xc) = 2;
    *(undefined4 *)(this + 0x50) = 0;
    *(undefined4 *)(this + 0x54) = 0x3c088889;
    cRSnail::SetAnimation(*(cRSnail **)this,9,true,-1);
    cRSnail::SetAnimation(*(cRSnail **)this,9,false,-1);
    cRSnail::SetAnimation(*(cRSnail **)this,1,false,-1);
    goto LAB_00072cfc;
  case 2:
LAB_00072cfc:
    *(undefined4 *)(this + 8) = 1;
    tMatrix::Identity((tMatrix *)(this + 0x10));
    iVar6 = *(int *)this;
    uVar3 = *(undefined4 *)(iVar6 + 0x16d0);
    uVar4 = *(undefined4 *)(iVar6 + 0x16d4);
    *(undefined4 *)(this + 0x40) = *(undefined4 *)(iVar6 + 0x16cc);
    *(undefined4 *)(this + 0x44) = uVar3;
    *(undefined4 *)(this + 0x48) = uVar4;
    tMatrix::LookAt((tMatrix *)(this + 0x10),(tVector *)(iVar6 + 0x5c));
    fVar1 = *(float *)(this + 0x50);
    *(float *)(this + 0x50) = fVar1 + *(float *)(this + 0x54);
    if (1.0 < fVar1 + *(float *)(this + 0x54)) {
      uVar3 = 8;
LAB_00072d58:
      *(undefined4 *)(this + 0xc) = uVar3;
      *(undefined4 *)(this + 0x50) = 0;
      *(undefined4 *)(this + 0x54) = 0x3c088889;
    }
    break;
  case 3:
    break;
  case 4:
    break;
  case 5:
    *(undefined4 *)(this + 8) = 0xffffffff;
    *(undefined4 *)(this + 0xc) = 7;
    cRSnail::SetAnimation(*(cRSnail **)this,8,true,-1);
    cRSnail::SetAnimation(*(cRSnail **)this,9,false,-1);
    cRSnail::SetAnimation(*(cRSnail **)this,9,false,-1);
    *(undefined4 *)(this + 0xc) = 6;
    iVar2 = *(int *)this;
    *(undefined4 *)(this + 0x50) = 0;
    *(undefined4 *)(this + 0x54) = 0x3c088889;
    *(undefined4 *)(iVar2 + 0x1764) = 0x3c888889;
    iVar6 = Game;
    *(undefined4 *)(iVar2 + 0x1768) = 0x3c888889;
    iVar2 = *(int *)(iVar6 + 0x71900);
    this[0x58] = (cRCutScene)0x1;
    if (iVar2 == 0) {
      cRCompletion::Init((cRCompletion *)(iVar6 + 0x3a5e4c),*(int *)(*(int *)(this + 4) + 0x3fec),
                         *(int *)(*(int *)(this + 4) + 0x3fec) == *(int *)(iVar6 + 0x72edc));
    }
    else if (iVar2 == 1) {
      cRCompletion::Init((cRCompletion *)(iVar6 + 0x3a5e4c),*(int *)(*(int *)(this + 4) + 0x3fec),
                         true);
    }
    else if (iVar2 == 4) {
      cRCompletion::Init((cRCompletion *)(iVar6 + 0x3a5e4c),0,false);
    }
    cRSound::Play((int)&gRSound);
    goto LAB_00072e68;
  case 6:
LAB_00072e68:
    *(undefined4 *)(this + 8) = 0xffffffff;
    fVar1 = (float)tMatrix::Identity((tMatrix *)&local_a4);
    iVar6 = *(int *)this;
    fVar7 = *(float *)(this + 0x50);
    local_34 = *(float *)(iVar6 + 0x1684);
    local_30 = *(float *)(iVar6 + 0x1688);
    local_2c = *(float *)(iVar6 + 0x168c);
    fVar8 = local_34 + fVar7 * (*(float *)(iVar6 + 0x16cc) - local_34);
    local_6c = local_2c + fVar7 * (*(float *)(iVar6 + 0x16d4) - local_2c);
    local_70 = local_30 + fVar7 * (*(float *)(iVar6 + 0x16d0) - local_30);
    local_74 = fVar8;
    fVar1 = (float)Sin(fVar1);
    local_74 = fVar8 + fVar1 * -0.5;
    fVar1 = (float)tMatrix::LookAt((tMatrix *)&local_a4,(tVector *)(*(int *)this + 0x5c));
    iVar6 = *(int *)(*(int *)this + 0xf4);
    local_64 = *(undefined4 *)(iVar6 + 0x1e8);
    uStack_60 = *(undefined4 *)(iVar6 + 0x1ec);
    uStack_5c = *(undefined4 *)(iVar6 + 0x1f0);
    uStack_58 = *(undefined4 *)(iVar6 + 500);
    local_54 = *(undefined4 *)(iVar6 + 0x1f8);
    uStack_50 = *(undefined4 *)(iVar6 + 0x1fc);
    uStack_4c = *(undefined4 *)(iVar6 + 0x200);
    uStack_48 = *(undefined4 *)(iVar6 + 0x204);
    local_44 = *(undefined4 *)(iVar6 + 0x208);
    uStack_40 = *(undefined4 *)(iVar6 + 0x20c);
    uStack_3c = *(undefined4 *)(iVar6 + 0x210);
    uStack_38 = *(undefined4 *)(iVar6 + 0x214);
    local_34 = *(float *)(iVar6 + 0x218);
    local_30 = *(float *)(iVar6 + 0x21c);
    local_2c = *(float *)(iVar6 + 0x220);
    uStack_28 = *(undefined4 *)(iVar6 + 0x224);
    fVar1 = (float)Sin(fVar1);
    tMatrix::LinearInterpolate
              ((tMatrix *)(this + 0x10),(tMatrix *)&local_64,(tMatrix *)&local_a4,fVar1);
    fVar1 = *(float *)(this + 0x50);
    *(float *)(this + 0x50) = fVar1 + *(float *)(this + 0x54);
    if (1.0 < fVar1 + *(float *)(this + 0x54)) {
      uVar3 = 7;
LAB_00072c88:
      *(undefined4 *)(this + 0xc) = uVar3;
      *(undefined4 *)(this + 0x50) = 0;
      *(undefined4 *)(this + 0x54) = 0x3c888889;
    }
    break;
  case 7:
    this[0x58] = (cRCutScene)0x1;
    *(undefined4 *)(this + 8) = 0xffffffff;
    tMatrix::Identity((tMatrix *)(this + 0x10));
    iVar6 = *(int *)this;
    uVar3 = *(undefined4 *)(iVar6 + 0x16d0);
    uVar4 = *(undefined4 *)(iVar6 + 0x16d4);
    *(undefined4 *)(this + 0x40) = *(undefined4 *)(iVar6 + 0x16cc);
    *(undefined4 *)(this + 0x44) = uVar3;
    *(undefined4 *)(this + 0x48) = uVar4;
    tMatrix::LookAt((tMatrix *)(this + 0x10),(tVector *)(iVar6 + 0x5c));
    if (*(int *)(*(cRSnail **)this + 0x134) == 0) {
      cRSnail::SetAnimation(*(cRSnail **)this,9,false,-1);
    }
    goto LAB_00072b10;
  case 8:
    *(undefined4 *)(this + 8) = 1;
    *(undefined1 *)(Game + 0x81494) = 0;
    fVar7 = (float)tMatrix::Identity((tMatrix *)&local_64);
    iVar6 = *(int *)this;
    fVar1 = *(float *)(iVar6 + 0x16cc);
    local_30 = *(float *)(iVar6 + 0x16d0);
    local_2c = *(float *)(iVar6 + 0x16d4);
    local_34 = fVar1;
    fVar7 = (float)Sin(fVar7);
    local_34 = fVar1 + fVar7 + fVar7;
    fVar1 = (float)tMatrix::LookAt((tMatrix *)&local_64,(tVector *)(*(int *)this + 0x5c));
    iVar6 = *(int *)(*(int *)this + 0xf4);
    local_a4 = *(undefined4 *)(iVar6 + 0x1e8);
    uStack_a0 = *(undefined4 *)(iVar6 + 0x1ec);
    uStack_9c = *(undefined4 *)(iVar6 + 0x1f0);
    uStack_98 = *(undefined4 *)(iVar6 + 500);
    local_94 = *(undefined4 *)(iVar6 + 0x1f8);
    uStack_90 = *(undefined4 *)(iVar6 + 0x1fc);
    uStack_8c = *(undefined4 *)(iVar6 + 0x200);
    uStack_88 = *(undefined4 *)(iVar6 + 0x204);
    local_84 = *(undefined4 *)(iVar6 + 0x208);
    uStack_80 = *(undefined4 *)(iVar6 + 0x20c);
    uStack_7c = *(undefined4 *)(iVar6 + 0x210);
    uStack_78 = *(undefined4 *)(iVar6 + 0x214);
    local_74 = *(float *)(iVar6 + 0x218);
    local_70 = *(float *)(iVar6 + 0x21c);
    local_6c = *(float *)(iVar6 + 0x220);
    uStack_68 = *(undefined4 *)(iVar6 + 0x224);
    fVar1 = (float)Sin(fVar1);
    tMatrix::LinearInterpolate
              ((tMatrix *)(this + 0x10),(tMatrix *)&local_64,(tMatrix *)&local_a4,fVar1);
    iVar6 = *(int *)this;
    local_24 = *(float *)(this + 0x40) - *(float *)(iVar6 + 0x5c);
    local_20 = *(float *)(this + 0x44) - *(float *)(iVar6 + 0x60);
    local_1c = *(float *)(this + 0x48) - *(float *)(iVar6 + 100);
    fVar1 = (float)tVector::Normalize((tVector *)&local_24);
    if (fVar1 < 1.5) {
      fVar1 = 1.5 - fVar1;
      *(float *)(this + 0x48) = *(float *)(this + 0x48) + fVar1 * local_1c;
      *(float *)(this + 0x40) = *(float *)(this + 0x40) + fVar1 * local_24;
      *(float *)(this + 0x44) = *(float *)(this + 0x44) + fVar1 * local_20;
    }
    fVar1 = *(float *)(this + 0x50);
    *(float *)(this + 0x50) = fVar1 + *(float *)(this + 0x54);
    if (fVar1 + *(float *)(this + 0x54) <= 1.0) {
      return;
    }
    uVar3 = 9;
    goto LAB_00072d58;
  case 9:
    iVar6 = *(int *)(*(int *)this + 0xf4);
    uVar3 = *(undefined4 *)(iVar6 + 0x1ec);
    uVar4 = *(undefined4 *)(iVar6 + 0x1f0);
    uVar5 = *(undefined4 *)(iVar6 + 500);
    *(undefined4 *)(this + 0x10) = *(undefined4 *)(iVar6 + 0x1e8);
    *(undefined4 *)(this + 0x14) = uVar3;
    *(undefined4 *)(this + 0x18) = uVar4;
    *(undefined4 *)(this + 0x1c) = uVar5;
    uVar3 = *(undefined4 *)(iVar6 + 0x1fc);
    uVar4 = *(undefined4 *)(iVar6 + 0x200);
    uVar5 = *(undefined4 *)(iVar6 + 0x204);
    *(undefined4 *)(this + 0x20) = *(undefined4 *)(iVar6 + 0x1f8);
    *(undefined4 *)(this + 0x24) = uVar3;
    *(undefined4 *)(this + 0x28) = uVar4;
    *(undefined4 *)(this + 0x2c) = uVar5;
    uVar3 = *(undefined4 *)(iVar6 + 0x20c);
    uVar4 = *(undefined4 *)(iVar6 + 0x210);
    uVar5 = *(undefined4 *)(iVar6 + 0x214);
    *(undefined4 *)(this + 0x30) = *(undefined4 *)(iVar6 + 0x208);
    *(undefined4 *)(this + 0x34) = uVar3;
    *(undefined4 *)(this + 0x38) = uVar4;
    *(undefined4 *)(this + 0x3c) = uVar5;
    uVar3 = *(undefined4 *)(iVar6 + 0x21c);
    uVar4 = *(undefined4 *)(iVar6 + 0x220);
    uVar5 = *(undefined4 *)(iVar6 + 0x224);
    *(undefined4 *)(this + 0x40) = *(undefined4 *)(iVar6 + 0x218);
    *(undefined4 *)(this + 0x44) = uVar3;
    *(undefined4 *)(this + 0x48) = uVar4;
    *(undefined4 *)(this + 0x4c) = uVar5;
    *(undefined4 *)(this + 0xc) = 0;
    break;
  case 10:
    *(undefined4 *)(this + 8) = 0xffffffff;
    cRSnail::SetAnimation(*(cRSnail **)this,7,true,-1);
    *(undefined4 *)(this + 0x50) = 0;
    this[0x58] = (cRCutScene)0x1;
    *(undefined4 *)(this + 0xc) = 0xb;
    *(undefined4 *)(this + 0x54) = 0x3c088889;
    cRVoiceManager::Play((int)&gVoiceManager,3,2);
    this_00 = *(cRSnail **)this;
    *(undefined1 *)(*(int *)(this_00 + 0xf4) + 0x444) = 1;
    cRSnail::ReleaseWeapons(this_00);
    goto LAB_00072b94;
  case 0xb:
LAB_00072b94:
    *(undefined4 *)(this + 8) = 0xffffffff;
    fVar7 = (float)tMatrix::Identity((tMatrix *)&local_a4);
    iVar6 = *(int *)this;
    fVar1 = *(float *)(iVar6 + 0x16cc);
    local_70 = *(float *)(iVar6 + 0x16d0);
    local_6c = *(float *)(iVar6 + 0x16d4);
    local_74 = fVar1;
    fVar7 = (float)Sin(fVar7);
    local_74 = fVar1 + fVar7 + fVar7;
    if (local_70 < 0.0) {
      local_70 = 0.0;
    }
    fVar1 = (float)tMatrix::LookAt((tMatrix *)&local_a4,(tVector *)(*(int *)this + 0x5c));
    iVar6 = *(int *)(*(int *)this + 0xf4);
    local_64 = *(undefined4 *)(iVar6 + 0x1e8);
    uStack_60 = *(undefined4 *)(iVar6 + 0x1ec);
    uStack_5c = *(undefined4 *)(iVar6 + 0x1f0);
    uStack_58 = *(undefined4 *)(iVar6 + 500);
    local_54 = *(undefined4 *)(iVar6 + 0x1f8);
    uStack_50 = *(undefined4 *)(iVar6 + 0x1fc);
    uStack_4c = *(undefined4 *)(iVar6 + 0x200);
    uStack_48 = *(undefined4 *)(iVar6 + 0x204);
    local_44 = *(undefined4 *)(iVar6 + 0x208);
    uStack_40 = *(undefined4 *)(iVar6 + 0x20c);
    uStack_3c = *(undefined4 *)(iVar6 + 0x210);
    uStack_38 = *(undefined4 *)(iVar6 + 0x214);
    local_34 = *(float *)(iVar6 + 0x218);
    local_30 = *(float *)(iVar6 + 0x21c);
    local_2c = *(float *)(iVar6 + 0x220);
    uStack_28 = *(undefined4 *)(iVar6 + 0x224);
    fVar1 = (float)Sin(fVar1);
    tMatrix::LinearInterpolate
              ((tMatrix *)(this + 0x10),(tMatrix *)&local_64,(tMatrix *)&local_a4,fVar1);
    fVar1 = *(float *)(this + 0x50);
    *(float *)(this + 0x50) = fVar1 + *(float *)(this + 0x54);
    if (fVar1 + *(float *)(this + 0x54) <= 1.0) {
      return;
    }
    uVar3 = 0xc;
    goto LAB_00072c88;
  case 0xc:
    *(undefined4 *)(this + 8) = 0xffffffff;
    this[0x58] = (cRCutScene)0x1;
    tMatrix::Identity((tMatrix *)(this + 0x10));
    iVar6 = *(int *)this;
    uVar3 = *(undefined4 *)(iVar6 + 0x16d0);
    uVar4 = *(undefined4 *)(iVar6 + 0x16d4);
    *(undefined4 *)(this + 0x40) = *(undefined4 *)(iVar6 + 0x16cc);
    *(undefined4 *)(this + 0x44) = uVar3;
    *(undefined4 *)(this + 0x48) = uVar4;
    if (*(float *)(this + 0x44) < 0.0) {
      *(undefined4 *)(this + 0x44) = 0;
    }
    tMatrix::LookAt((tMatrix *)(this + 0x10),(tVector *)(iVar6 + 0x5c));
    if (((*(cRSubGoldy **)(this + 4))[0x78] == (cRSubGoldy)0x0) &&
       (cRSubGoldy::DeathInit(*(cRSubGoldy **)(this + 4)),
       *(char *)(*(int *)(this + 4) + 0x445) == '\0')) {
      cRVoiceManager::Play((int)&gVoiceManager,0xb,2);
      iVar6 = *(int *)(this + 4);
      *(undefined1 *)(iVar6 + 0x444) = 1;
      *(undefined1 *)(iVar6 + 0x445) = 1;
    }
LAB_00072b10:
    *(float *)(this + 0x50) = *(float *)(this + 0x50) + *(float *)(this + 0x54);
  }
  return;
}
