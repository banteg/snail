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
  int iVar3;
  int *piVar4;
  undefined4 uVar5;
  uint *puVar6;
  uint uVar7;
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
  float fVar8;
  uint uVar9;
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

  iVar3 = DAT_00086a70 + 0x86790;
  *(undefined4 *)this = 1;
  if (param_1 == (cRTipData *)0x0) {
    *(undefined4 *)(this + 8) = *(undefined4 *)(iVar3 + DAT_00086a80);
  }
  else {
    *(cRTipData **)(this + 8) = param_1;
  }
  iVar1 = DAT_00086a74;
  uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(**(int **)(iVar3 + DAT_00086a74) + 0xd14));
  puVar6 = *(uint **)(this + 8);
  uVar9 = puVar6[2];
  uVar7 = puVar6[4];
  if ((*puVar6 & 4) == 0) {
    uVar5 = 2;
  }
  else {
    uVar5 = 0;
  }
  *(undefined4 *)(this + 0xc) = uVar2;
  tColour::tColour((tColour *)&local_40,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
  cRBorder::Init(uVar2,2,uVar7,0x14,*(undefined4 *)(*(int *)(this + 8) + 4),uVar9,local_40,uStack_3c
                 ,uStack_38,uStack_34,uVar5,*(undefined4 *)(*(int *)(this + 8) + 4));
  puVar6 = *(uint **)(this + 8);
  uVar7 = *puVar6;
  *(undefined4 *)(*(int *)(this + 0xc) + 0x6e8) = DAT_00086a60;
  fVar8 = DAT_00086a64;
  if ((uVar7 & 2) != 0) {
    *(float *)(this + 0x18) = DAT_00086a64;
    uVar7 = *puVar6;
    if ((float)puVar6[3] != fVar8) {
      fVar8 = 1.0 / ((float)puVar6[3] * DAT_00086a68);
    }
    *(float *)(this + 0x1c) = fVar8;
  }
  if ((uVar7 & 1) == 0) {
    *(undefined4 *)(this + 0x14) = 0;
    *(undefined4 *)(this + 0x10) = 0;
  }
  else {
    piVar4 = *(int **)(iVar3 + iVar1);
    uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(*piVar4 + 0xd14));
    *(undefined4 *)(this + 0x10) = uVar2;
    if (param_2) {
      tColour::tColour((tColour *)&local_70,extraout_s0_00,extraout_s1_00,extraout_s2_00,
                       extraout_s3_00);
      cRBorder::Init(uVar2,0x14,iVar3 + DAT_00086a78,0x14,DAT_00086a64,DAT_00086a64,local_70,
                     uStack_6c,uStack_68,uStack_64,2,*(undefined4 *)(*(int *)(this + 8) + 4));
      *(undefined4 *)(this + 0x14) = 0;
    }
    else {
      tColour::tColour((tColour *)&local_50,extraout_s0_00,extraout_s1_00,extraout_s2_00,
                       extraout_s3_00);
      fVar8 = DAT_00086a64;
      cRBorder::Init(uVar2,0x14,iVar3 + DAT_00086a78,0x14,DAT_00086a64,DAT_00086a64,local_50,
                     uStack_4c,uStack_48,uStack_44,2,
                     DAT_00086a6c + *(float *)(*(int *)(this + 8) + 4));
      uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(*piVar4 + 0xd14));
      *(undefined4 *)(this + 0x14) = uVar2;
      tColour::tColour((tColour *)&local_60,extraout_s0_01,extraout_s1_01,extraout_s2_01,
                       extraout_s3_01);
      cRBorder::Init(uVar2,0x14,iVar3 + DAT_00086a7c,0x14,fVar8,fVar8,local_60,uStack_5c,uStack_58,
                     uStack_54,2,*(float *)(*(int *)(this + 8) + 4) - DAT_00086a68);
      cRBorder::SetBelow(*(cRBorder **)(this + 0x14),*(cRBorder **)(this + 0xc));
    }
    cRBorder::SetBelow(*(cRBorder **)(this + 0x10),*(cRBorder **)(this + 0xc));
    puVar6 = *(uint **)(this + 8);
  }
  iVar3 = **(int **)(iVar3 + iVar1);
  *(undefined4 *)(this + 4) = *(undefined4 *)(iVar3 + 0x15c);
  if ((*puVar6 & 1) != 0) {
    *(undefined4 *)(iVar3 + 0x15c) = 0x16;
  }
  return;
}
