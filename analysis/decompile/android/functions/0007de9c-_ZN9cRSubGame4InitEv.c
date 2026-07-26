/*
 * mangled: _ZN9cRSubGame4InitEv
 * demangled: cRSubGame::Init()
 * address: 0007de9c
 * size: 2444
 */

/* cRSubGame::Init() */

void __thiscall cRSubGame::Init(cRSubGame *this)

{
  undefined4 *puVar1;
  char *pcVar2;
  cRBorder *this_00;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 uVar6;
  cRSubGame *pcVar7;
  uint uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  int iVar11;
  int *piVar12;
  bool bVar13;
  uint in_fpscr;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float fVar14;
  float extraout_s0_02;
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
  undefined4 uVar15;
  undefined4 uVar16;
  undefined4 local_c8;
  undefined4 uStack_c4;
  undefined4 uStack_c0;
  undefined4 local_bc;
  int local_b8;
  undefined4 local_b4;
  int local_b0;
  undefined4 *local_ac;
  int local_a8;
  tColour *local_a4;
  tColour *local_a0;
  undefined4 local_9c;
  char *local_98;
  int local_94;
  int local_90;
  int *local_8c;
  undefined4 local_88;
  undefined4 uStack_84;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  tColour local_78 [16];
  tColour local_68 [16];
  undefined4 local_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 local_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;

  iVar3 = 0;
  *(undefined4 *)(this + 0x7c) = 0;
  this[0x10] = (cRSubGame)0x0;
  do {
    iVar5 = 0;
    pcVar7 = this + iVar3 * 0x240 + 0x13adc;
    do {
      iVar5 = iVar5 + 1;
      *(undefined4 *)(pcVar7 + 0x38) = 0;
      *(undefined4 *)(pcVar7 + 0x3c) = 0;
      *(undefined4 *)(pcVar7 + 0x40) = 0;
      *(undefined4 *)(pcVar7 + 0x44) = 0;
      pcVar7 = pcVar7 + 0x48;
    } while (iVar5 != 8);
    iVar3 = iVar3 + 1;
  } while (iVar3 != 0xe10);
  uVar8 = *(uint *)(this + 0x332d9c);
  bVar13 = 3 < uVar8;
  if (uVar8 != 4) {
    bVar13 = uVar8 != 1;
  }
  if (!bVar13 || (uVar8 == 4 || uVar8 == 2)) {
    local_a8 = 0x2e0;
    RShellMusicPlay("mainmenu",0,"");
    piVar12 = *(int **)((int)&__DT_PLTGOT + local_a8);
    iVar3 = cRLandscapeManager::Import
                      ((cRLandscapeManager *)(gSegmentText + *piVar12 + 0x3d8),"Menubg.txt");
    fVar14 = (float)cRBackdrop::Change((cRBackdrop *)(*piVar12 + 0x4d2e0),
                                       (cRLandscape *)
                                       (gSegmentText + iVar3 * 0x1ac + *piVar12 + 0x3dc),false);
    cRBorderManager::SetJustifyCentre((cRBorderManager *)(*piVar12 + 0xd14),fVar14);
  }
  else {
    local_a8 = 0x2e0;
  }
  iVar3 = *(int *)(this + 0x60);
  if (iVar3 == 1) {
    iVar5 = 0x2cf710;
    *(undefined4 *)(this + 0x2e2c) = *(undefined4 *)(this + 0x2cf728);
    iVar3 = 0x2cf70c;
LAB_0007e4f8:
    pcVar7 = this + iVar5;
    uVar4 = *(undefined4 *)pcVar7;
    uVar6 = *(undefined4 *)(pcVar7 + 4);
    uVar9 = *(undefined4 *)(pcVar7 + 8);
    uVar10 = *(undefined4 *)(pcVar7 + 0xc);
    *(cRSubGame **)(this + 0x2cf49c) = this + iVar3;
    *(undefined4 *)(this + 0x2e30) = uVar4;
    *(undefined4 *)(this + 0x2e34) = uVar6;
    *(undefined4 *)(this + 0x2e38) = uVar9;
    *(undefined4 *)(this + 0x2e3c) = uVar10;
    uVar4 = *(undefined4 *)(pcVar7 + 0x14);
    *(undefined4 *)(this + 0x2e40) = *(undefined4 *)(pcVar7 + 0x10);
    *(undefined4 *)(this + 0x2e44) = uVar4;
  }
  else {
    if (iVar3 == 4) {
      iVar5 = 0x2cf978;
      iVar3 = 0x2cf974;
      *(undefined4 *)(this + 0x2e2c) = *(undefined4 *)(this + 0x2cf990);
      goto LAB_0007e4f8;
    }
    if (iVar3 == 0) {
      if (*(int *)(this + 0x3210c0) == 0) {
        *(cRSubGame **)(this + 0x2cf49c) = this + 0x2cf4a4;
      }
      else if (*(int *)(this + 0x3210c0) == 1) {
        *(cRSubGame **)(this + 0x2cf49c) = this + 0x2d04d4;
      }
      iVar3 = *(int *)(this + 0x2cf49c);
      *(undefined4 *)(this + 0x2e2c) = *(undefined4 *)(iVar3 + 0x1c);
      uVar4 = *(undefined4 *)(iVar3 + 8);
      uVar6 = *(undefined4 *)(iVar3 + 0xc);
      uVar9 = *(undefined4 *)(iVar3 + 0x10);
      *(undefined4 *)(this + 0x2e30) = *(undefined4 *)(iVar3 + 4);
      *(undefined4 *)(this + 0x2e34) = uVar4;
      *(undefined4 *)(this + 0x2e38) = uVar6;
      *(undefined4 *)(this + 0x2e3c) = uVar9;
      uVar4 = *(undefined4 *)(iVar3 + 0x18);
      *(undefined4 *)(this + 0x2e40) = *(undefined4 *)(iVar3 + 0x14);
      *(undefined4 *)(this + 0x2e44) = uVar4;
    }
  }
  this[0x19] = (cRSubGame)0x0;
  piVar12 = *(int **)((int)&__DT_PLTGOT + local_a8);
  bVar13 = this[0x30fcc1] != (cRSubGame)0x0;
  this[0x18] = (cRSubGame)0x0;
  uVar8 = 0;
  if (bVar13) {
    uVar8 = 0xfcc4;
  }
  *(undefined4 *)(this + 0x5c) = 0;
  if (bVar13) {
    uVar8 = uVar8 | 0x300000;
  }
  iVar3 = *piVar12;
  if (bVar13) {
    uVar8 = *(uint *)(this + uVar8);
  }
  if (bVar13) {
    *(undefined4 *)(this + 0x4c) = *(undefined4 *)(uVar8 + 0x48);
  }
  *(undefined4 *)(this + 0x1c) = 0;
  *(undefined4 *)(this + 0x334600) = 0;
  *(undefined4 *)(this + 0x20) = 0x3d088889;
  uVar4 = cRBorderManager::GetBorder((cRBorderManager *)(iVar3 + 0xd14));
  *(undefined4 *)(this + 0x8c58) = uVar4;
  tColour::tColour((tColour *)&local_48,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
  local_ac = &local_c8;
  local_94 = -0x43c8;
  local_98 = "0";
  local_c8 = local_48;
  uStack_c4 = uStack_44;
  uStack_c0 = uStack_40;
  local_bc = uStack_3c;
  local_b4 = 0x439b0000;
  local_b8 = 3;
  cRBorder::Init(uVar4,0x400002,"0",0x14,0x43c80000,0x41600000);
  iVar3 = *(int *)(this + 0x8c58);
  *(undefined1 *)(iVar3 + 0x2c4) = 0;
  *(undefined4 *)(iVar3 + 0x26c) = 1;
  iVar5 = *(int *)(this + 0x60);
  *(undefined4 *)(iVar3 + 0x6e8) = 0x3f99999a;
  if (iVar5 == 0) {
    local_a4 = local_68;
    local_b0 = iVar5;
    local_9c = cRBorderManager::GetBorder((cRBorderManager *)(*piVar12 + 0xd14));
    *(undefined4 *)(this + 0x8c60) = local_9c;
    tColour::tColour((tColour *)&local_58,extraout_s0_01,extraout_s1_01,extraout_s2_01,
                     extraout_s3_01);
    local_a0 = local_78;
    local_90 = local_b0;
    local_c8 = uStack_54;
    uStack_c4 = uStack_50;
    uStack_c0 = uStack_4c;
    local_bc = 0;
    local_b8 = 1;
    local_8c = piVar12;
    fVar14 = (float)cRBorder::Init(local_9c,0x400800,0x6e,0,0x42680000,local_58);
    cRBorder::Scale(*(cRBorder **)(this + 0x8c60),fVar14);
    cRBorder::HideInit(*(cRBorder **)(this + 0x8c60));
    iVar3 = *piVar12;
    *(undefined4 *)(*(int *)(this + 0x8c60) + 0x16c) = 0;
    uVar4 = cRBorderManager::GetBorder((cRBorderManager *)(iVar3 + 0xd14));
    *(undefined4 *)(this + 0x8c64) = uVar4;
    tColour::tColour(local_a4,extraout_s0_02,extraout_s1_02,extraout_s2_02,extraout_s3_02);
    puVar1 = local_ac;
    uVar6 = *(undefined4 *)(local_a4 + 4);
    uVar9 = *(undefined4 *)(local_a4 + 8);
    uVar10 = *(undefined4 *)(local_a4 + 0xc);
    uVar15 = 0x42780000;
    uVar16 = 0x42b20000;
    *local_ac = *(undefined4 *)local_a4;
    puVar1[1] = uVar6;
    puVar1[2] = uVar9;
    puVar1[3] = uVar10;
    local_b8 = local_b0;
    local_b4 = 0;
    cRBorder::Init(uVar4,0x400002,local_98,0x14,uVar15,uVar16);
    cRBorder::HideInit(*(cRBorder **)(this + 0x8c64));
    piVar12 = local_8c;
    *(undefined4 *)(*(int *)(this + 0x8c64) + 0x6e8) = 0x3f59999a;
    iVar3 = local_90;
    pcVar7 = this + 0x8c68;
    do {
      uVar4 = cRBorderManager::GetBorder((cRBorderManager *)(*piVar12 + 0xd14));
      *(undefined4 *)pcVar7 = uVar4;
      tColour::tColour(local_a0,extraout_s0_03,extraout_s1_03,extraout_s2_03,extraout_s3_03);
      fVar14 = (float)VectorSignedToFloat(iVar3,(byte)(in_fpscr >> 0x16) & 3);
      iVar3 = iVar3 + 1;
      local_c8 = *(undefined4 *)(local_a0 + 4);
      uStack_c4 = *(undefined4 *)(local_a0 + 8);
      uStack_c0 = *(undefined4 *)(local_a0 + 0xc);
      local_bc = 0;
      local_b8 = 1;
      cRBorder::Init(uVar4,0x400800,0x6f,fVar14 * 24.0 + 13.0,0x43d70000,*(undefined4 *)local_a0);
      this_00 = *(cRBorder **)pcVar7;
      *(undefined4 *)(this_00 + 0x16c) = 0;
      cRBorder::HideInit(this_00);
      pcVar7 = pcVar7 + 4;
    } while (iVar3 != 9);
  }
  wprintf("***TODO*** Score last\n");
  uVar4 = cRBorderManager::GetBorder
                    ((cRBorderManager *)(**(int **)((int)&__DT_PLTGOT + local_a8) + 0xd14));
  *(undefined4 *)(this + 0x8c5c) = uVar4;
  tColour::tColour((tColour *)&local_88,extraout_s0_00,extraout_s1_00,extraout_s2_00,extraout_s3_00)
  ;
  puVar1 = local_ac;
  *local_ac = local_88;
  puVar1[1] = uStack_84;
  puVar1[2] = uStack_80;
  puVar1[3] = uStack_7c;
  local_b4 = 0x41f00000;
  local_b8 = 3;
  cRBorder::Init(uVar4,0x400002,(int)&__DT_PLTGOT + local_94,0x14,0x42a00000,0x41600000);
  iVar3 = *(int *)(this + 0x8c5c);
  *(undefined1 *)(iVar3 + 0x2c4) = 0;
  *(undefined4 *)(iVar3 + 0x26c) = 1;
  uVar4 = *(undefined4 *)(this + 0x60);
  *(undefined4 *)(iVar3 + 0x6e8) = 0x3f99999a;
  switch(uVar4) {
  case 0:
    goto LAB_0007e208;
  case 1:
LAB_0007e208:
    cRBorder::AddTextNumber(*(int *)(this + 0x8c5c));
    break;
  case 2:
    goto LAB_0007e1a0;
  case 3:
LAB_0007e1a0:
    cRBorder::HideInit(*(cRBorder **)(this + 0x8c5c));
    cRBorder::HideInit(*(cRBorder **)(this + 0x8c58));
    break;
  case 4:
    iVar3 = *(int *)(this + 0x8c5c);
    pcVar2 = (char *)cRTimeTrial::TimeString
                               ((cRTimeTrial *)(this + 0x30fcd0),(cRTime *)(this + 0x2e30));
    Rstrcpy((char *)(iVar3 + 0x2c4),pcVar2);
  }
  if ((*(char *)(**(int **)((int)&__DT_PLTGOT + local_a8) + 0x4d3dc) != '\0') ||
     (*(int *)(this + 0x60) == 7)) {
    cRBorder::HideInit(*(cRBorder **)(this + 0x8c5c));
    cRBorder::HideInit(*(cRBorder **)(this + 0x8c58));
  }
  iVar3 = **(int **)((int)&__DT_PLTGOT + local_a8);
  if (*(char *)(iVar3 + 0x2c1) != '\0') {
    return;
  }
  *(undefined4 *)(iVar3 + 0x2c4) = 0;
  *(undefined1 *)(iVar3 + 0x2c1) = 0;
  tMatrix::Identity((tMatrix *)(this + 0xfaf0));
  *(uint *)(this + 0xfac8) = *(uint *)(this + 0xfac8) & 0xffffffdf;
  *(undefined4 *)(this + 0xfec8) = 0;
  *(undefined4 *)(this + 0x122a4) = *(undefined4 *)(this + 0xfb20);
  *(undefined4 *)(this + 0x122a8) = *(undefined4 *)(this + 0xfb24);
  *(undefined4 *)(this + 0x122ac) = *(undefined4 *)(this + 0xfb28);
  *(undefined4 *)(this + 0xfec0) = 0;
  *(cRSubGame **)(this + 0xfec4) = this;
  this[0xfed9] = (cRSubGame)0x0;
  this[0xfed8] = (cRSubGame)0x0;
  cRWarning::Init((cRWarning *)(this + 0xfea8));
  iVar3 = *(int *)(this + 0x332d9c);
  if (iVar3 == 0 || iVar3 == 3) goto LAB_0007e608;
  if (this[0x30fcc1] != (cRSubGame)0x0) {
    *(undefined4 *)(this + 0x4c) = *(undefined4 *)(*(int *)(this + 0x30fcc4) + 0x48);
    goto LAB_0007e608;
  }
  iVar5 = gConfig._164_4_;
  iVar11 = gConfig._236_4_;
  switch(*(undefined4 *)(this + 0x60)) {
  case 0:
    if (iVar3 == 1) {
      if (*(int *)(this + 0x3210c0) == 0) {
        iVar5 = *(int *)(this + 100) + 1;
        *(int *)(this + 100) = iVar5;
        iVar3 = *(int *)(this + 0x3210dc);
        if (iVar3 < iVar5) {
          *(int *)(this + 100) = iVar3;
          iVar5 = iVar3;
        }
        iVar11 = gConfig._236_4_;
        if ((int)gConfig._160_4_ < iVar5) {
          gConfig._160_4_ = iVar5;
          gRegisterSaveFile("asm.cfg",gConfig,0x130);
          iVar5 = *(undefined4 *)(this + 100);
          iVar11 = gConfig._236_4_;
        }
      }
      else if (*(int *)(this + 0x3210c0) == 1) {
        iVar11 = *(int *)(this + 100) + 1;
        *(int *)(this + 100) = iVar11;
        iVar3 = *(int *)(this + 0x329f48);
        if (iVar3 < iVar11) {
          *(int *)(this + 100) = iVar3;
          iVar11 = iVar3;
        }
        iVar5 = gConfig._164_4_;
        if ((int)gConfig._232_4_ < iVar11) {
          gConfig._232_4_ = iVar11;
          gRegisterSaveFile("asm.cfg",gConfig,0x130);
          iVar5 = gConfig._164_4_;
          iVar11 = *(undefined4 *)(this + 100);
        }
      }
    }
    else if (iVar3 == 4) {
      if (*(int *)(this + 0x3210c0) == 0) {
        iVar5 = *(undefined4 *)(this + 100);
      }
      else if (*(int *)(this + 0x3210c0) == 1) {
        iVar11 = *(undefined4 *)(this + 100);
      }
    }
    goto LAB_0007e758;
  case 1:
    cRGUI::Init((cRGUI *)(this + 0x321078));
    goto LAB_0007e608;
  case 2:
    break;
  case 3:
    break;
  case 4:
LAB_0007e758:
    gConfig._236_4_ = iVar11;
    gConfig._164_4_ = iVar5;
    cRGalaxy::Init((cRGalaxy *)(this + *(int *)(this + 0x3210c0) * 0x8e6c + 0x3210c4));
    goto LAB_0007e608;
  case 5:
    break;
  case 6:
    break;
  case 7:
    *(undefined4 *)(this + 0x5c) = 0;
    goto LAB_0007e608;
  }
  RShellError("Unknown game mode");
LAB_0007e608:
  ReSet(this);
  return;
}
