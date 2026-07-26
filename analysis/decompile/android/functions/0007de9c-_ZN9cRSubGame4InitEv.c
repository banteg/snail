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
  undefined4 uVar3;
  cRBorder *this_00;
  void *pvVar4;
  int iVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  int iVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  int iVar11;
  cRSubGame *pcVar12;
  uint uVar13;
  undefined4 uVar14;
  undefined4 uVar15;
  int iVar16;
  int *piVar17;
  bool bVar18;
  uint in_fpscr;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float fVar19;
  float extraout_s0_02;
  float extraout_s0_03;
  float fVar20;
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
  float fVar21;
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
  int local_98;
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

  iVar16 = DAT_0007e274;
  iVar5 = 0;
  *(undefined4 *)(this + 0x7c) = 0;
  iVar16 = iVar16 + 0x7dec8;
  this[0x10] = (cRSubGame)0x0;
  do {
    iVar8 = 0;
    pcVar12 = this + iVar5 * 0x240 + 0x13adc;
    do {
      iVar8 = iVar8 + 1;
      *(undefined4 *)(pcVar12 + 0x38) = 0;
      *(undefined4 *)(pcVar12 + 0x3c) = 0;
      *(undefined4 *)(pcVar12 + 0x40) = 0;
      *(undefined4 *)(pcVar12 + 0x44) = 0;
      pcVar12 = pcVar12 + 0x48;
    } while (iVar8 != 8);
    iVar5 = iVar5 + 1;
  } while (iVar5 != 0xe10);
  uVar13 = *(uint *)(this + 0x332d9c);
  bVar18 = 3 < uVar13;
  if (uVar13 != 4) {
    bVar18 = uVar13 != 1;
  }
  if (!bVar18 || (uVar13 == 4 || uVar13 == 2)) {
    local_a8 = DAT_0007e284;
    RShellMusicPlay((char *)(iVar16 + DAT_0007e288),0,(char *)(iVar16 + DAT_0007e28c));
    piVar17 = *(int **)(iVar16 + local_a8);
    iVar5 = cRLandscapeManager::Import
                      ((cRLandscapeManager *)(gSegmentText + *piVar17 + 0x3d8),
                       (char *)(iVar16 + DAT_0007e290));
    fVar20 = (float)cRBackdrop::Change((cRBackdrop *)(*piVar17 + 0x4d2e0),
                                       (cRLandscape *)
                                       (gSegmentText + iVar5 * 0x1ac + *piVar17 + 0x3dc),false);
    cRBorderManager::SetJustifyCentre((cRBorderManager *)(*piVar17 + 0xd14),fVar20);
  }
  else {
    local_a8 = DAT_0007e284;
  }
  iVar5 = *(int *)(this + 0x60);
  if (iVar5 == 1) {
    iVar8 = 0x2cf710;
    *(undefined4 *)(this + 0x2e2c) = *(undefined4 *)(this + 0x2cf728);
    iVar5 = 0x2cf70c;
LAB_0007e4f8:
    pcVar12 = this + iVar8;
    uVar6 = *(undefined4 *)pcVar12;
    uVar9 = *(undefined4 *)(pcVar12 + 4);
    uVar14 = *(undefined4 *)(pcVar12 + 8);
    uVar3 = *(undefined4 *)(pcVar12 + 0xc);
    *(cRSubGame **)(this + 0x2cf49c) = this + iVar5;
    *(undefined4 *)(this + 0x2e30) = uVar6;
    *(undefined4 *)(this + 0x2e34) = uVar9;
    *(undefined4 *)(this + 0x2e38) = uVar14;
    *(undefined4 *)(this + 0x2e3c) = uVar3;
    uVar6 = *(undefined4 *)(pcVar12 + 0x14);
    *(undefined4 *)(this + 0x2e40) = *(undefined4 *)(pcVar12 + 0x10);
    *(undefined4 *)(this + 0x2e44) = uVar6;
  }
  else {
    if (iVar5 == 4) {
      iVar8 = 0x2cf978;
      iVar5 = 0x2cf974;
      *(undefined4 *)(this + 0x2e2c) = *(undefined4 *)(this + 0x2cf990);
      goto LAB_0007e4f8;
    }
    if (iVar5 == 0) {
      if (*(int *)(this + 0x3210c0) == 0) {
        *(cRSubGame **)(this + 0x2cf49c) = this + 0x2cf4a4;
      }
      else if (*(int *)(this + 0x3210c0) == 1) {
        *(cRSubGame **)(this + 0x2cf49c) = this + 0x2d04d4;
      }
      iVar5 = *(int *)(this + 0x2cf49c);
      *(undefined4 *)(this + 0x2e2c) = *(undefined4 *)(iVar5 + 0x1c);
      uVar6 = *(undefined4 *)(iVar5 + 8);
      uVar9 = *(undefined4 *)(iVar5 + 0xc);
      uVar14 = *(undefined4 *)(iVar5 + 0x10);
      *(undefined4 *)(this + 0x2e30) = *(undefined4 *)(iVar5 + 4);
      *(undefined4 *)(this + 0x2e34) = uVar6;
      *(undefined4 *)(this + 0x2e38) = uVar9;
      *(undefined4 *)(this + 0x2e3c) = uVar14;
      uVar6 = *(undefined4 *)(iVar5 + 0x18);
      *(undefined4 *)(this + 0x2e40) = *(undefined4 *)(iVar5 + 0x14);
      *(undefined4 *)(this + 0x2e44) = uVar6;
    }
  }
  this[0x19] = (cRSubGame)0x0;
  piVar17 = *(int **)(iVar16 + local_a8);
  bVar18 = this[0x30fcc1] != (cRSubGame)0x0;
  this[0x18] = (cRSubGame)0x0;
  uVar13 = 0;
  if (bVar18) {
    uVar13 = 0xfcc4;
  }
  *(undefined4 *)(this + 0x5c) = 0;
  if (bVar18) {
    uVar13 = uVar13 | 0x300000;
  }
  iVar5 = *piVar17;
  if (bVar18) {
    uVar13 = *(uint *)(this + uVar13);
  }
  if (bVar18) {
    *(undefined4 *)(this + 0x4c) = *(undefined4 *)(uVar13 + 0x48);
  }
  *(undefined4 *)(this + 0x1c) = 0;
  uVar6 = DAT_0007e258;
  *(undefined4 *)(this + 0x334600) = 0;
  *(undefined4 *)(this + 0x20) = uVar6;
  uVar6 = cRBorderManager::GetBorder((cRBorderManager *)(iVar5 + 0xd14));
  *(undefined4 *)(this + 0x8c58) = uVar6;
  tColour::tColour((tColour *)&local_48,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
  local_ac = &local_c8;
  local_94 = DAT_0007e278;
  local_98 = iVar16 + DAT_0007e278;
  local_c8 = local_48;
  uStack_c4 = uStack_44;
  uStack_c0 = uStack_40;
  local_bc = uStack_3c;
  local_b4 = DAT_0007e264;
  local_b8 = 3;
  cRBorder::Init(uVar6,0x400002,local_98,0x14,DAT_0007e25c,DAT_0007e260);
  uVar6 = DAT_0007e268;
  iVar5 = *(int *)(this + 0x8c58);
  *(undefined1 *)(iVar5 + 0x2c4) = 0;
  *(undefined4 *)(iVar5 + 0x26c) = 1;
  iVar8 = *(int *)(this + 0x60);
  *(undefined4 *)(iVar5 + 0x6e8) = uVar6;
  if (iVar8 == 0) {
    local_a4 = local_68;
    local_b0 = iVar8;
    local_9c = cRBorderManager::GetBorder((cRBorderManager *)(*piVar17 + 0xd14));
    uVar6 = DAT_0007e2a0;
    fVar20 = DAT_0007e29c;
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
    local_8c = piVar17;
    fVar19 = (float)cRBorder::Init(local_9c,0x400800,0x6e,0,DAT_0007e2a4,local_58);
    cRBorder::Scale(*(cRBorder **)(this + 0x8c60),fVar19);
    cRBorder::HideInit(*(cRBorder **)(this + 0x8c60));
    iVar5 = *piVar17;
    *(undefined4 *)(*(int *)(this + 0x8c60) + 0x16c) = 0;
    uVar3 = cRBorderManager::GetBorder((cRBorderManager *)(iVar5 + 0xd14));
    *(undefined4 *)(this + 0x8c64) = uVar3;
    tColour::tColour(local_a4,extraout_s0_02,extraout_s1_02,extraout_s2_02,extraout_s3_02);
    puVar1 = local_ac;
    fVar19 = DAT_0007e2ac;
    uVar7 = *(undefined4 *)(local_a4 + 4);
    uVar10 = *(undefined4 *)(local_a4 + 8);
    uVar15 = *(undefined4 *)(local_a4 + 0xc);
    uVar9 = DAT_0007e2a8;
    uVar14 = DAT_0007e2b0;
    *local_ac = *(undefined4 *)local_a4;
    puVar1[1] = uVar7;
    puVar1[2] = uVar10;
    puVar1[3] = uVar15;
    local_b8 = local_b0;
    local_b4 = 0;
    cRBorder::Init(uVar3,0x400002,local_98,0x14,uVar9,uVar14);
    cRBorder::HideInit(*(cRBorder **)(this + 0x8c64));
    piVar17 = local_8c;
    *(undefined4 *)(*(int *)(this + 0x8c64) + 0x6e8) = DAT_0007e2b4;
    iVar5 = local_90;
    pcVar12 = this + 0x8c68;
    do {
      uVar9 = cRBorderManager::GetBorder((cRBorderManager *)(*piVar17 + 0xd14));
      *(undefined4 *)pcVar12 = uVar9;
      tColour::tColour(local_a0,extraout_s0_03,extraout_s1_03,extraout_s2_03,extraout_s3_03);
      fVar21 = (float)VectorSignedToFloat(iVar5,(byte)(in_fpscr >> 0x16) & 3);
      iVar5 = iVar5 + 1;
      local_c8 = *(undefined4 *)(local_a0 + 4);
      uStack_c4 = *(undefined4 *)(local_a0 + 8);
      uStack_c0 = *(undefined4 *)(local_a0 + 0xc);
      local_bc = 0;
      local_b8 = 1;
      cRBorder::Init(uVar9,0x400800,0x6f,fVar19 + fVar21 * fVar20,uVar6,*(undefined4 *)local_a0);
      this_00 = *(cRBorder **)pcVar12;
      *(undefined4 *)(this_00 + 0x16c) = 0;
      cRBorder::HideInit(this_00);
      pcVar12 = pcVar12 + 4;
    } while (iVar5 != 9);
  }
  wprintf((char *)(iVar16 + DAT_0007e27c));
  uVar6 = cRBorderManager::GetBorder((cRBorderManager *)(**(int **)(iVar16 + local_a8) + 0xd14));
  *(undefined4 *)(this + 0x8c5c) = uVar6;
  tColour::tColour((tColour *)&local_88,extraout_s0_00,extraout_s1_00,extraout_s2_00,extraout_s3_00)
  ;
  puVar1 = local_ac;
  *local_ac = local_88;
  puVar1[1] = uStack_84;
  puVar1[2] = uStack_80;
  puVar1[3] = uStack_7c;
  local_b4 = DAT_0007e270;
  local_b8 = 3;
  cRBorder::Init(uVar6,0x400002,iVar16 + local_94,0x14,DAT_0007e26c,DAT_0007e260);
  uVar6 = DAT_0007e268;
  iVar5 = *(int *)(this + 0x8c5c);
  *(undefined1 *)(iVar5 + 0x2c4) = 0;
  *(undefined4 *)(iVar5 + 0x26c) = 1;
  uVar9 = *(undefined4 *)(this + 0x60);
  *(undefined4 *)(iVar5 + 0x6e8) = uVar6;
  switch(uVar9) {
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
    iVar5 = *(int *)(this + 0x8c5c);
    pcVar2 = (char *)cRTimeTrial::TimeString
                               ((cRTimeTrial *)(this + 0x30fcd0),(cRTime *)(this + 0x2e30));
    Rstrcpy((char *)(iVar5 + 0x2c4),pcVar2);
  }
  if ((*(char *)(**(int **)(iVar16 + local_a8) + 0x4d3dc) != '\0') || (*(int *)(this + 0x60) == 7))
  {
    cRBorder::HideInit(*(cRBorder **)(this + 0x8c5c));
    cRBorder::HideInit(*(cRBorder **)(this + 0x8c58));
  }
  iVar5 = **(int **)(iVar16 + local_a8);
  if (*(char *)(iVar5 + 0x2c1) != '\0') {
    return;
  }
  *(undefined4 *)(iVar5 + 0x2c4) = 0;
  *(undefined1 *)(iVar5 + 0x2c1) = 0;
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
  iVar5 = DAT_0007e294;
  iVar8 = *(int *)(this + 0x332d9c);
  if (iVar8 == 0 || iVar8 == 3) goto LAB_0007e608;
  if (this[0x30fcc1] != (cRSubGame)0x0) {
    *(undefined4 *)(this + 0x4c) = *(undefined4 *)(*(int *)(this + 0x30fcc4) + 0x48);
    goto LAB_0007e608;
  }
  switch(*(undefined4 *)(this + 0x60)) {
  case 0:
    if (iVar8 == 1) {
      if (*(int *)(this + 0x3210c0) == 0) {
        iVar8 = *(int *)(this + 100) + 1;
        pvVar4 = *(void **)(iVar16 + DAT_0007e294);
        *(int *)(this + 100) = iVar8;
        iVar11 = *(int *)(this + 0x3210dc);
        if (iVar11 < iVar8) {
          *(int *)(this + 100) = iVar11;
          iVar8 = iVar11;
        }
        if (*(int *)((int)pvVar4 + 0xa0) < iVar8) {
          *(int *)((int)pvVar4 + 0xa0) = iVar8;
          gRegisterSaveFile((char *)(iVar16 + DAT_0007e298),pvVar4,0x130);
          iVar8 = *(int *)(this + 100);
        }
        *(int *)(*(int *)(iVar16 + iVar5) + 0xa4) = iVar8;
      }
      else if (*(int *)(this + 0x3210c0) == 1) {
        iVar8 = *(int *)(this + 100) + 1;
        pvVar4 = *(void **)(iVar16 + DAT_0007e294);
        *(int *)(this + 100) = iVar8;
        iVar11 = *(int *)(this + 0x329f48);
        if (iVar11 < iVar8) {
          *(int *)(this + 100) = iVar11;
          iVar8 = iVar11;
        }
        if (*(int *)((int)pvVar4 + 0xe8) < iVar8) {
          *(int *)((int)pvVar4 + 0xe8) = iVar8;
          gRegisterSaveFile((char *)(iVar16 + DAT_0007e298),pvVar4,0x130);
          iVar8 = *(int *)(this + 100);
        }
        *(int *)(*(int *)(iVar16 + iVar5) + 0xec) = iVar8;
      }
    }
    else if (iVar8 == 4) {
      if (*(int *)(this + 0x3210c0) == 0) {
        *(undefined4 *)(*(int *)(iVar16 + DAT_0007e294) + 0xa4) = *(undefined4 *)(this + 100);
      }
      else if (*(int *)(this + 0x3210c0) == 1) {
        *(undefined4 *)(*(int *)(iVar16 + DAT_0007e294) + 0xec) = *(undefined4 *)(this + 100);
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
  RShellError((char *)(iVar16 + DAT_0007e280));
LAB_0007e608:
  ReSet(this);
  return;
}
