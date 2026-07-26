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
  int *piVar8;
  int iVar9;
  int iVar10;
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
  undefined4 uVar11;
  float fVar12;
  float fVar13;
  float fVar14;
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

  iVar5 = DAT_000614a4;
  uVar4 = (uint)param_2;
  iVar7 = DAT_000614a0 + 0x61048;
  piVar8 = *(int **)(iVar7 + DAT_000614a4);
  iVar10 = *piVar8;
  iVar6 = *(int *)(iVar10 + 0x71900);
  if (iVar6 == 0) {
    if (uVar4 == 0) {
      *(undefined4 *)(this + 0x44) = 0;
    }
    else {
      uVar4 = 1;
      *(undefined4 *)(this + 0x44) = 50000;
    }
  }
  else if (iVar6 == 1) {
    if (gDirectory[iVar10 + 0x2544] == '\0') {
      iVar9 = *(int *)(*(int *)(iVar7 + DAT_000614dc) + 0x48);
      iVar6 = *(int *)(*(int *)(iVar7 + DAT_000614dc) + 0x40);
    }
    else {
      iVar9 = *(int *)(*(int *)(gDirectory + iVar10 + 0x2548) + 0x50);
      iVar6 = *(int *)(*(int *)(gDirectory + iVar10 + 0x2548) + 0x4c);
    }
    iVar6 = iVar6 / 0x14;
    uVar2 = iVar9 / 0x14;
    if (4 < (int)uVar2) {
      uVar2 = 5;
    }
    uVar2 = uVar2 & ~((int)uVar2 >> 0x1f);
    if (iVar6 < 0) {
      iVar6 = 0;
    }
    else {
      if (4 < iVar6) {
        iVar6 = 5;
      }
      if (uVar2 == 5 && iVar6 == 5) {
        *(undefined4 *)(this + 0x44) = 500000;
        goto LAB_00061078;
      }
    }
    *(int *)(this + 0x44) =
         *(int *)(*(int *)(iVar7 + DAT_000614c8) + iVar6 * 4) +
         *(int *)(*(int *)(iVar7 + DAT_000614cc) + uVar2 * 4);
  }
  else if (iVar6 == 4) {
    wprintf((char *)(iVar7 + DAT_000614b4),param_1,SUB84((double)*(float *)(iVar10 + 0x81634),0),
            (int)((ulonglong)(double)*(float *)(iVar10 + 0x81634) >> 0x20));
    wprintf((char *)(iVar7 + DAT_000614b8),extraout_r1,
            SUB84((double)*(float *)(gGroup0 +
                                    *piVar8 + (*(int *)(*piVar8 + 0x71904) + 0x16) * 0x38 + 0xce6a0)
                  ,0),
            (int)((ulonglong)
                  (double)*(float *)(gGroup0 +
                                    *piVar8 + (*(int *)(*piVar8 + 0x71904) + 0x16) * 0x38 + 0xce6a0)
                 >> 0x20));
    iVar6 = *piVar8;
    uVar4 = in_fpscr & 0xfffffff;
    in_fpscr = uVar4 | (uint)(*(float *)(iVar6 + 0x81634) <
                             *(float *)(gGroup0 +
                                       iVar6 + (*(int *)(iVar6 + 0x71904) + 0x16) * 0x38 + 0xce6a0))
                       << 0x1f;
    if ((SUB41(in_fpscr >> 0x1f,0)) ||
       (in_fpscr = uVar4 | (uint)(*(float *)(gGroup0 +
                                            iVar6 + (*(int *)(iVar6 + 0x71904) + 0x16) * 0x38 +
                                            0xce6a0) == 0.0) << 0x1e, SUB41(in_fpscr >> 0x1e,0))) {
      wprintf((char *)(iVar7 + DAT_000614bc));
      uVar4 = 1;
      iVar10 = **(int **)(iVar7 + iVar5);
    }
    else {
      wprintf((char *)(iVar7 + DAT_000614e0));
      iVar10 = *piVar8;
      uVar4 = 0;
    }
  }
LAB_00061078:
  *(uint *)(this + 0x1c) = uVar4;
  *(int *)(this + 0x18) = param_1;
  fVar14 = DAT_0006147c;
  *(int *)(this + 0x48) = param_1 * 100 + *(int *)(this + 0x44) + *(int *)(iVar10 + 0x81630);
  uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(iVar10 + 0xd14));
  *(undefined4 *)this = uVar1;
  tColour::tColour((tColour *)&local_40,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
  cRBorder::Init(uVar1,0x20400002,iVar7 + DAT_000614a8,0x14,fVar14,DAT_00061480,local_40,uStack_3c,
                 uStack_38,uStack_34,2,fVar14);
  uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(**(int **)(iVar7 + iVar5) + 0xd14));
  *(undefined4 *)(this + 4) = uVar1;
  if (*(int *)(this + 0x18) == 1) {
    tColour::tColour((tColour *)&local_50,extraout_s0_00,extraout_s1_00,extraout_s2_00,
                     extraout_s3_00);
    cRBorder::Init(uVar1,0x20400002,iVar7 + DAT_000614c4,0x14,fVar14,DAT_000614e4,local_50,uStack_4c
                   ,uStack_48,uStack_44,2,fVar14);
  }
  else {
    tColour::tColour((tColour *)&local_60,extraout_s0_00,extraout_s1_00,extraout_s2_00,
                     extraout_s3_00);
    cRBorder::Init(uVar1,0x20400002,iVar7 + DAT_000614ac,0x14,fVar14,DAT_000614e4,local_60,uStack_5c
                   ,uStack_58,uStack_54,2,fVar14);
  }
  piVar8 = *(int **)(iVar7 + iVar5);
  this_00 = (cRBorder *)cRBorderManager::GetBorder((cRBorderManager *)(*piVar8 + 0xd14));
  iVar6 = *(int *)(*piVar8 + 0x71900);
  *(cRBorder **)(this + 8) = this_00;
  if (iVar6 == 0) {
    tColour::tColour((tColour *)&local_70,extraout_s0_01,extraout_s1_01,extraout_s2_01,
                     extraout_s3_01);
    iVar6 = DAT_000614c0;
    local_90 = local_70;
    uStack_8c = uStack_6c;
    uStack_88 = uStack_68;
    uStack_84 = uStack_64;
    fVar14 = DAT_0006147c;
  }
  else {
    if (iVar6 == 1) {
      tColour::tColour((tColour *)&local_80,extraout_s0_01,extraout_s1_01,extraout_s2_01,
                       extraout_s3_01);
      cRBorder::Init(this_00,0x20400002,iVar7 + DAT_000614d0,0x14,DAT_000614e8,DAT_000614ec,local_80
                     ,uStack_7c,uStack_78,uStack_74,2,DAT_000614e8);
      cRBorder::AddTextNumber(*(int *)(this + 8));
      iVar6 = *(int *)(this + 8);
      sVar3 = strlen((char *)(iVar6 + 0x2c4));
      memcpy((char *)(iVar6 + 0x2c4) + sVar3,(void *)(iVar7 + DAT_000614d4),0xe);
      this_00 = *(cRBorder **)(this + 8);
      goto LAB_000611d8;
    }
    if (iVar6 != 4) goto LAB_000611d8;
    tColour::tColour((tColour *)&local_90,extraout_s0_01,extraout_s1_01,extraout_s2_01,
                     extraout_s3_01);
    iVar6 = DAT_000614d8;
    fVar14 = DAT_000614e8;
  }
  cRBorder::Init(this_00,0x20400002,iVar7 + iVar6,0x14,fVar14,DAT_000614ec,local_90,uStack_8c,
                 uStack_88,uStack_84,2,fVar14);
  this_00 = *(cRBorder **)(this + 8);
LAB_000611d8:
  fVar14 = DAT_0006147c;
  cRBorder::HideInit(this_00);
  uVar1 = DAT_00061484;
  piVar8 = *(int **)(iVar7 + iVar5);
  *(float *)(this + 0x3c) = fVar14;
  *(undefined4 *)(this + 0x40) = uVar1;
  uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(*piVar8 + 0xd14));
  *(undefined4 *)(this + 0xc) = uVar1;
  if (*(int *)(this + 0x1c) == 0) {
    tColour::tColour((tColour *)&local_b0,extraout_s0_02,extraout_s1_02,extraout_s2_02,
                     extraout_s3_02);
    local_a0 = local_b0;
    uStack_9c = uStack_ac;
    uStack_98 = uStack_a8;
    uStack_94 = uStack_a4;
    uVar11 = DAT_0006149c;
  }
  else {
    tColour::tColour((tColour *)&local_a0,extraout_s0_02,extraout_s1_02,extraout_s2_02,
                     extraout_s3_02);
    uVar11 = DAT_00061488;
  }
  cRBorder::Init(uVar1,0x20400002,iVar7 + DAT_000614b0,0x14,fVar14,uVar11,local_a0,uStack_9c,
                 uStack_98,uStack_94,2,fVar14);
  cRBorder::HideInit(*(cRBorder **)(this + 0xc));
  *(undefined4 *)(this + 0x28) = DAT_0006148c;
  fVar14 = DAT_00061490;
  fVar12 = (float)VectorSignedToFloat(*(int *)(this + 0x18) + 1,(byte)(in_fpscr >> 0x16) & 3);
  piVar8 = *(int **)(iVar7 + iVar5);
  *(undefined4 *)(this + 0x24) = 0;
  *(undefined4 *)(this + 0x20) = 0;
  iVar5 = *piVar8;
  *(undefined4 *)(this + 0x10) = 1;
  this[0x14] = (cRCompletion)0x1;
  iVar5 = *(int *)(iVar5 + 0x71900);
  fVar13 = DAT_0006147c;
  if (fVar14 / fVar12 != 0.0) {
    fVar13 = DAT_00061498 / ((fVar14 / fVar12) * DAT_00061494);
  }
  *(float *)(this + 0x2c) = fVar13;
  if (iVar5 == 4) {
    *(undefined4 *)(this + 0x10) = 3;
    cRBorder::HideInit(*(cRBorder **)this);
  }
  return;
}
