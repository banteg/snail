/*
 * mangled: _ZN5cRGUI4InitEv
 * demangled: cRGUI::Init()
 * address: 00064188
 * size: 956
 */

/* cRGUI::Init() */

void __thiscall cRGUI::Init(cRGUI *this)

{
  float fVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  cRBorder *pcVar6;
  undefined4 *puVar7;
  cRBorder *this_00;
  int iVar8;
  int *piVar9;
  int iVar10;
  uint in_fpscr;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float extraout_s0_02;
  float fVar11;
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
  float fVar12;
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

  iVar3 = DAT_00064568;
  iVar8 = DAT_00064564 + 0x641a4;
  piVar9 = *(int **)(iVar8 + DAT_00064568);
  cRFade::FadeIn((cRFade *)(*piVar9 + 0x24));
  cRMouse::SetActive((cRMouse *)(*piVar9 + 0x228));
  fVar11 = DAT_00064548;
  uVar5 = DAT_00064544;
  if (*(int *)(*(int *)this + 0x60) == 1) {
    uVar4 = cRBorderManager::GetBorder((cRBorderManager *)(*piVar9 + 0xd14));
    uVar2 = DAT_00064550;
    fVar1 = DAT_0006454c;
    *(undefined4 *)(this + 0x20) = uVar4;
    tColour::tColour((tColour *)&local_48,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
    cRBorder::Init(uVar4,0x100004,iVar8 + DAT_0006456c,0x14,uVar5,fVar11,local_48,uStack_44,
                   uStack_40,uStack_3c,2,fVar1);
    puVar7 = *(undefined4 **)(this + 0x20);
    iVar10 = *(int *)(iVar8 + DAT_00064570);
    fVar12 = (float)VectorSignedToFloat(*(undefined4 *)(iVar10 + 0x48),(byte)(in_fpscr >> 0x16) & 3)
    ;
    puVar7[0x5d] = fVar12 / fVar11;
    puVar7[0x5c] = fVar12 / fVar11;
    (**(code **)*puVar7)(puVar7);
    uVar4 = cRBorderManager::GetBorder((cRBorderManager *)(*piVar9 + 0xd14));
    *(undefined4 *)(this + 0x1c) = uVar4;
    tColour::tColour((tColour *)&local_58,extraout_s0_00,extraout_s1_00,extraout_s2_00,
                     extraout_s3_00);
    cRBorder::Init(uVar4,0x100004,iVar8 + DAT_00064574,0x14,uVar5,DAT_00064554,local_58,uStack_54,
                   uStack_50,uStack_4c,2,fVar1);
    fVar12 = (float)VectorSignedToFloat(*(undefined4 *)(iVar10 + 0x40),(byte)(in_fpscr >> 0x16) & 3)
    ;
    this_00 = *(cRBorder **)(this + 0x1c);
    pcVar6 = *(cRBorder **)(this + 0x20);
    *(float *)(this_00 + 0x174) = fVar12 / fVar11;
    *(float *)(this_00 + 0x170) = fVar12 / fVar11;
    cRBorder::SetBelow(this_00,pcVar6);
    (**(code **)**(undefined4 **)(this + 0x1c))(*(undefined4 **)(this + 0x1c));
    if (*(int *)(gGroup0 + *(int *)this + 0x5ddf4) != 1) {
      fVar11 = fVar1;
    }
    uVar4 = cRBorderManager::GetBorder((cRBorderManager *)(*piVar9 + 0xd14));
    *(undefined4 *)(this + 0x10) = uVar4;
    tColour::tColour((tColour *)&local_68,extraout_s0_01,extraout_s1_01,extraout_s2_01,
                     extraout_s3_01);
    cRBorder::Init(uVar4,0x40000016,iVar8 + DAT_00064578,0x14,uVar5,DAT_00064558,local_68,uStack_64,
                   uStack_60,uStack_5c,2,fVar11);
    cRBorder::SetBelow(*(cRBorder **)(this + 0x10),*(cRBorder **)(this + 0x1c));
    iVar10 = *piVar9;
    *(undefined4 *)(*(int *)(this + 0x10) + 0x264) = uVar2;
    uVar4 = cRBorderManager::GetBorder((cRBorderManager *)(iVar10 + 0xd14));
    *(undefined4 *)(this + 0x24) = uVar4;
    tColour::tColour((tColour *)&local_78,extraout_s0_02,extraout_s1_02,extraout_s2_02,
                     extraout_s3_02);
    cRBorder::Init(uVar4,0x40000016,iVar8 + DAT_0006457c,0x14,uVar5,DAT_0006455c,local_78,uStack_74,
                   uStack_70,uStack_6c,2,DAT_00064560);
    cRBorder::SetBelow(*(cRBorder **)(this + 0x24),*(cRBorder **)(this + 0x1c));
    iVar10 = *(int *)this;
    pcVar6 = *(cRBorder **)(this + 0x24);
    *(undefined4 *)(pcVar6 + 0x264) = uVar2;
    if (*(int *)(gGroup0 + iVar10 + 0x5ddf4) == 1) {
      fVar11 = (float)cRBorder::SetRight(*(cRBorder **)(this + 0x10),pcVar6);
    }
    else {
      fVar11 = (float)cRBorder::HideInit(pcVar6);
    }
    piVar9 = *(int **)(iVar8 + iVar3);
    cRBorderManager::CentreRow
              ((cRBorderManager *)(*piVar9 + 0xd14),*(cRBorder **)(this + 0x10),false,fVar11);
    uVar5 = cRBorderManager::GetBorder((cRBorderManager *)(*piVar9 + 0xd14));
    *(undefined4 *)(this + 0x18) = uVar5;
    tColour::tColour((tColour *)&local_88,extraout_s0_03,extraout_s1_03,extraout_s2_03,
                     extraout_s3_03);
    cRBorder::Init(uVar5,0x16,iVar8 + DAT_00064580,0x14,DAT_00064544,DAT_00064544,local_88,uStack_84
                   ,uStack_80,uStack_7c,2,DAT_0006454c);
    cRBorder::SetBelow(*(cRBorder **)(this + 0x18),*(cRBorder **)(this + 0x24));
  }
  return;
}
