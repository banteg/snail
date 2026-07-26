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
  undefined4 uVar2;
  undefined4 uVar3;
  size_t sVar4;
  undefined4 *puVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  undefined4 *puVar9;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float extraout_s0_02;
  float extraout_s0_03;
  float extraout_s0_04;
  float fVar10;
  float extraout_s0_05;
  float extraout_s1;
  float extraout_s1_00;
  float extraout_s1_01;
  float extraout_s1_02;
  float extraout_s1_03;
  float extraout_s1_04;
  float fVar11;
  float extraout_s1_05;
  float extraout_s2;
  float extraout_s2_00;
  float extraout_s2_01;
  float extraout_s2_02;
  float extraout_s2_03;
  float extraout_s2_04;
  float fVar12;
  float extraout_s2_05;
  float extraout_s3;
  float extraout_s3_00;
  float extraout_s3_01;
  float extraout_s3_02;
  float extraout_s3_03;
  float extraout_s3_04;
  float fVar13;
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

  uVar3 = DAT_0006a268;
  iVar7 = DAT_0006a284 + 0x69f04;
  piVar8 = *(int **)(iVar7 + DAT_0006a288);
  iVar6 = *piVar8;
  *(undefined1 *)(iVar6 + 0x324) = 1;
  uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(iVar6 + 0xd14));
  uVar1 = DAT_0006a26c;
  *(undefined4 *)(this + 0x14) = uVar2;
  tColour::tColour((tColour *)&local_40,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
  cRBorder::Init(uVar2,0x14,iVar7 + DAT_0006a28c,0x14,uVar3,DAT_0006a270,local_40,uStack_3c,
                 uStack_38,uStack_34,2,0);
  iVar6 = *piVar8;
  *(float *)(*(int *)(this + 0x14) + 0x6f0) =
       *(float *)(*(int *)(this + 0x14) + 0x6f0) + DAT_0006a274;
  uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(iVar6 + 0xd14));
  *(undefined4 *)(this + 0x18) = uVar2;
  tColour::tColour((tColour *)&local_50,extraout_s0_00,extraout_s1_00,extraout_s2_00,extraout_s3_00)
  ;
  cRBorder::Init(uVar2,0x900004,iVar7 + DAT_0006a290,0x14,uVar3,uVar1,local_50,uStack_4c,uStack_48,
                 uStack_44,2,0);
  cRBorder::SetBelow(*(cRBorder **)(this + 0x18),*(cRBorder **)(this + 0x14));
  puVar5 = *(undefined4 **)(this + 0x18);
  puVar9 = *(undefined4 **)(iVar7 + DAT_0006a294);
  uVar2 = *puVar9;
  puVar5[0x5d] = uVar2;
  puVar5[0x5c] = uVar2;
  (**(code **)*puVar5)(puVar5);
  uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(*piVar8 + 0xd14));
  *(undefined4 *)(this + 0x1c) = uVar2;
  tColour::tColour((tColour *)&local_60,extraout_s0_01,extraout_s1_01,extraout_s2_01,extraout_s3_01)
  ;
  cRBorder::Init(uVar2,0x100004,iVar7 + DAT_0006a298,0x14,uVar3,uVar1,local_60,uStack_5c,uStack_58,
                 uStack_54,2,0);
  cRBorder::SetBelow(*(cRBorder **)(this + 0x1c),*(cRBorder **)(this + 0x18));
  puVar5 = *(undefined4 **)(this + 0x1c);
  uVar2 = puVar9[1];
  puVar5[0x5d] = uVar2;
  puVar5[0x5c] = uVar2;
  (**(code **)*puVar5)(puVar5);
  uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(*piVar8 + 0xd14));
  *(undefined4 *)(this + 0x10) = uVar2;
  tColour::tColour((tColour *)&local_70,extraout_s0_02,extraout_s1_02,extraout_s2_02,extraout_s3_02)
  ;
  cRBorder::Init(uVar2,0x14,iVar7 + DAT_0006a29c,0x14,uVar3,uVar1,local_70,uStack_6c,uStack_68,
                 uStack_64,2,0);
  cRBorder::SetBelow(*(cRBorder **)(this + 0x10),*(cRBorder **)(this + 0x1c));
  iVar6 = *piVar8;
  *(undefined4 *)(this + 0x24) = *puVar9;
  uVar3 = cRBorderManager::GetBorder((cRBorderManager *)(iVar6 + 0xd14));
  *(undefined4 *)(this + 0x20) = uVar3;
  iVar6 = Rstrcmp((char *)(iVar7 + DAT_0006a2a0),(char *)(puVar9 + 0x18));
  if (iVar6 == 0) {
    uVar3 = *(undefined4 *)(this + 0x20);
    tColour::tColour((tColour *)&local_90,extraout_s0_03,extraout_s1_03,extraout_s2_03,
                     extraout_s3_03);
    cRBorder::Init(uVar3,0x20400000,iVar7 + DAT_0006a2a4,0x14,DAT_0006a278,DAT_0006a2b0,local_90,
                   uStack_8c,uStack_88,uStack_84,0,0);
    iVar6 = *(int *)(this + 0x20);
    sVar4 = strlen((char *)(iVar6 + 0x2c4));
    *(undefined1 *)(iVar6 + sVar4 + 0x2c2) = 0;
    fVar10 = extraout_s0_04;
    fVar11 = extraout_s1_04;
    fVar12 = extraout_s2_04;
    fVar13 = extraout_s3_04;
  }
  else {
    uVar3 = *(undefined4 *)(this + 0x20);
    tColour::tColour((tColour *)&local_80,extraout_s0_03,extraout_s1_03,extraout_s2_03,
                     extraout_s3_03);
    cRBorder::Init(uVar3,0x20400000,iVar7 + DAT_0006a2a4,0x14,DAT_0006a2ac,DAT_0006a2b0,local_80,
                   uStack_7c,uStack_78,uStack_74,0,0);
    fVar10 = extraout_s0_05;
    fVar11 = extraout_s1_05;
    fVar12 = extraout_s2_05;
    fVar13 = extraout_s3_05;
  }
  tColour::Set((tColour *)(*(int *)(this + 0x20) + 0x1e0),fVar10,fVar11,fVar12,fVar13);
  iVar6 = *(int *)(this + 0x20);
  *(undefined4 *)(iVar6 + 0x6e8) = DAT_0006a280;
  *(undefined1 *)(iVar6 + 0x228) = 1;
  return;
}
