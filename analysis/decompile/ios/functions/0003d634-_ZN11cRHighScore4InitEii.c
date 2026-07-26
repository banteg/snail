/*
 * mangled: _ZN11cRHighScore4InitEii
 * demangled: cRHighScore::Init(int, int)
 * address: 0003d634
 * size: 3288
 */

/* cRHighScore::Init(int, int) */

void cRHighScore::Init(int param_1,int param_2)

{
  char cVar1;
  undefined *puVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  int in_r2;
  undefined *puVar8;
  undefined1 in_r3;
  int iVar9;
  uint uVar10;
  uint in_fpscr;
  float fVar11;
  int local_174;
  int local_170;
  tColour local_158 [16];
  tColour local_148 [16];
  tColour local_138 [16];
  tColour local_128 [16];
  undefined4 local_118;
  undefined4 uStack_114;
  undefined4 uStack_110;
  undefined4 uStack_10c;
  undefined4 local_108;
  undefined4 uStack_104;
  undefined4 uStack_100;
  undefined4 uStack_fc;
  tColour local_f8 [16];
  tColour local_e8 [16];
  tColour local_d8 [16];
  tColour local_c8 [16];
  tColour local_b8 [16];
  tColour local_a8 [16];
  tColour local_98 [16];
  tColour local_88 [16];
  tColour local_78 [16];
  tColour local_68 [16];
  tColour local_58 [16];
  tColour local_48 [16];
  tColour local_38 [24];

  puVar2 = PTR__Game_001b60b8;
  cRFade::FadeIn((cRFade *)(*(int *)PTR__Game_001b60b8 + 0x24));
  cRBackdrop::SetZoom((cRBackdrop *)(*(int *)puVar2 + 0x4d2e0),0.09);
  if (in_r2 == -1) {
    in_r3 = 0;
  }
  *(int *)(param_1 + 8) = param_2;
  *(int *)(param_1 + 0x14) = in_r2;
  puVar2 = PTR__Game_001b60b8;
  if (in_r2 == -1) {
    *(undefined1 *)(param_1 + 0x10) = in_r3;
  }
  else {
    *(undefined1 *)(param_1 + 0x10) = 1;
  }
  cRStarManager::Hide((cRStarManager *)(*(int *)puVar2 + 0x4e718));
  cRSubGame::HideScores((cRSubGame *)(*(int *)puVar2 + 0x72b78));
  RShellMusicPlay("mainmenu.mp4",0,"");
  iVar3 = cRLandscapeManager::Import
                    ((cRLandscapeManager *)(&DAT_003593d8 + *(int *)puVar2),"Menubg.txt");
  cRBackdrop::Change((cRBackdrop *)(*(int *)puVar2 + 0x4d2e0),
                     (cRLandscape *)(&DAT_003593dc + *(int *)puVar2 + iVar3 * 0x1ac),false);
  cRBorderManager::SetJustifyCentre((cRBorderManager *)(*(int *)puVar2 + 0xd14),0.0);
  cRMouse::SetActive((cRMouse *)(*(int *)puVar2 + 0x228));
  uVar4 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)puVar2 + 0xd14));
  iVar3 = *(int *)(param_1 + 8);
  *(undefined4 *)(param_1 + 0x18) = uVar4;
  if (iVar3 == 1) {
    tColour::tColour(local_58,1.0,1.0,1.0,1.0);
    cRBorder::Init(uVar4,0,"Challenge High Scores",0x17,0,0x41600000);
    iVar3 = *(int *)puVar2;
    puVar8 = &DAT_00312f90;
    iVar5 = iVar3 + 0x312000;
  }
  else if (iVar3 == 3) {
    tColour::tColour(local_48,1.0,1.0,1.0,1.0);
    cRBorder::Init(uVar4,0,"Pro High Scores",0x17,0,0x41600000);
    iVar3 = *(int *)puVar2;
    puVar8 = &DAT_00313d58;
    iVar5 = iVar3 + 0x312000;
  }
  else {
    if (iVar3 != 0) {
      cVar1 = *(char *)(param_1 + 0x10);
      goto joined_r0x0003d77c;
    }
    tColour::tColour(local_38,1.0,1.0,1.0,1.0);
    cRBorder::Init(uVar4,0,"Postal High Scores",0x17,0,0x41600000);
    iVar3 = *(int *)puVar2;
    puVar8 = &DAT_00312d28;
    iVar5 = iVar3 + 0x312000;
  }
  *(undefined **)(iVar5 + 0xd20) = puVar8 + iVar3;
  *(undefined4 *)(&DAT_00312d24 + *(int *)puVar2) = 10;
  cVar1 = *(char *)(param_1 + 0x10);
joined_r0x0003d77c:
  if (cVar1 != '\0') {
    Rstrcpy((char *)(*(int *)(param_1 + 0x18) + 0x2c4),"Enter your name here!");
    cRBorder::RePosition(*(cRBorder **)(param_1 + 0x18));
  }
  local_174 = 1;
  local_170 = 0;
  iVar3 = param_1;
  do {
    *(undefined4 *)(iVar3 + 0xcc) = 0;
    uVar10 = local_174 - 1;
    if (uVar10 == *(uint *)(param_1 + 0x14)) {
      uVar6 = 2;
    }
    else {
      uVar6 = 0;
    }
    iVar5 = *(int *)PTR__Game_001b60b8;
    if (*(int *)(*(int *)(&DAT_00312d20 + iVar5) + local_170) == 1) {
      iVar9 = *(int *)(param_1 + 8);
      if (iVar9 == 1) {
        fVar11 = (float)VectorSignedToFloat(uVar10,(byte)(in_fpscr >> 0x16) & 3);
        fVar11 = fVar11 * 36.0 + 66.0;
        uVar4 = cRBorderManager::GetBorder((cRBorderManager *)(iVar5 + 0xd14));
        *(undefined4 *)(iVar3 + 0x2c) = uVar4;
        tColour::tColour(local_b8,1.0,1.0,1.0,1.0);
        cRBorder::Init(uVar4,uVar6 | 0x20000000," ",0x16,0,fVar11);
        *(undefined4 *)(*(int *)(iVar3 + 0x2c) + 0x244) = 0x43de8000;
        uVar4 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
        *(undefined4 *)(iVar3 + 0x54) = uVar4;
        uVar7 = uVar6 | 0x20400000;
        tColour::tColour(local_c8,1.0,1.0,1.0,1.0);
        cRBorder::Init(uVar4,uVar7,"",0x16,0,fVar11);
        cRBorder::AddTextNumber(*(cRBorder **)(iVar3 + 0x54),local_174);
        cRBorder::RePosition(*(cRBorder **)(iVar3 + 0x54));
        uVar4 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
        puVar2 = PTR__Game_001b60b8;
        *(undefined4 *)(iVar3 + 0x7c) = uVar4;
        iVar5 = *(int *)(&DAT_00312d20 + *(int *)puVar2);
        tColour::tColour(local_d8,1.0,1.0,1.0,1.0);
        cRBorder::Init(uVar4,uVar7,local_170 + iVar5 + 0x25,0x16,0,fVar11);
        if (uVar10 == *(uint *)(param_1 + 0x14)) {
          iVar5 = uVar10 * 4 + param_1;
          cRBorder::InputTextInit
                    (*(cRBorder **)(iVar5 + 0x7c),0x10,PTR__gConfig_001b60d4 + 0x60,0x10);
          iVar5 = *(int *)(iVar5 + 0x7c);
          *(uint *)(iVar5 + 0x194) = *(uint *)(iVar5 + 0x194) | 0x2002010;
        }
        cRBorder::RePosition(*(cRBorder **)(iVar3 + 0x7c));
        uVar4 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
        *(undefined4 *)(iVar3 + 0xa4) = uVar4;
        tColour::tColour(local_e8,1.0,1.0,1.0,1.0);
        cRBorder::Init(uVar4,uVar7,"",0x16,0,fVar11);
        cRBorder::AddTextNumber
                  (*(cRBorder **)(iVar3 + 0xa4),
                   *(int *)(*(int *)(&DAT_00312d20 + *(int *)PTR__Game_001b60b8) + local_170 + 0x1c)
                  );
        cRBorder::RePosition(*(cRBorder **)(iVar3 + 0xa4));
        uVar4 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
        *(undefined4 *)(iVar3 + 0xcc) = uVar4;
        tColour::tColour(local_f8,1.0,1.0,1.0,1.0);
        cRBorder::Init(uVar4,uVar6 | 0x60000014,"Replay",0x16,0,fVar11);
        if (*(char *)(param_1 + 0x10) != '\0') {
          cRBorder::HideInit(*(cRBorder **)(iVar3 + 0xcc));
        }
        if (*(char *)(*(int *)(&DAT_00312d20 + *(int *)PTR__Game_001b60b8) + local_170 + 0x24) ==
            '\0') {
          cRBorder::HideInit(*(cRBorder **)(iVar3 + 0xcc));
        }
      }
      else if ((iVar9 == 3) || (iVar9 == 0)) {
        fVar11 = (float)VectorSignedToFloat(uVar10,(byte)(in_fpscr >> 0x16) & 3);
        fVar11 = fVar11 * 36.0 + 66.0;
        uVar4 = cRBorderManager::GetBorder((cRBorderManager *)(iVar5 + 0xd14));
        *(undefined4 *)(iVar3 + 0x2c) = uVar4;
        tColour::tColour(local_68,1.0,1.0,1.0,1.0);
        cRBorder::Init(uVar4,uVar6 | 0x20000000," ",0x16,0,fVar11);
        *(undefined4 *)(*(int *)(iVar3 + 0x2c) + 0x244) = 0x43f00000;
        uVar4 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
        *(undefined4 *)(iVar3 + 0x54) = uVar4;
        uVar7 = uVar6 | 0x20400000;
        tColour::tColour(local_78,1.0,1.0,1.0,1.0);
        cRBorder::Init(uVar4,uVar7,"",0x16,0,fVar11);
        cRBorder::AddTextNumber(*(cRBorder **)(iVar3 + 0x54),local_174);
        cRBorder::RePosition(*(cRBorder **)(iVar3 + 0x54));
        uVar4 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
        puVar2 = PTR__Game_001b60b8;
        *(undefined4 *)(iVar3 + 0x7c) = uVar4;
        iVar5 = *(int *)(&DAT_00312d20 + *(int *)puVar2);
        tColour::tColour(local_88,1.0,1.0,1.0,1.0);
        cRBorder::Init(uVar4,uVar7,local_170 + iVar5 + 0x25,0x16,0,fVar11);
        if (uVar10 == *(uint *)(param_1 + 0x14)) {
          iVar5 = uVar10 * 4 + param_1;
          cRBorder::InputTextInit
                    (*(cRBorder **)(iVar5 + 0x7c),0x10,PTR__gConfig_001b60d4 + 0x60,0x10);
          iVar5 = *(int *)(iVar5 + 0x7c);
          *(uint *)(iVar5 + 0x194) = *(uint *)(iVar5 + 0x194) | 0x2002010;
        }
        cRBorder::RePosition(*(cRBorder **)(iVar3 + 0x7c));
        uVar4 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
        *(undefined4 *)(iVar3 + 0xa4) = uVar4;
        tColour::tColour(local_98,1.0,1.0,1.0,1.0);
        cRBorder::Init(uVar4,uVar7,"",0x16,0,fVar11);
        cRBorder::AddTextNumber
                  (*(cRBorder **)(iVar3 + 0xa4),
                   *(int *)(*(int *)(&DAT_00312d20 + *(int *)PTR__Game_001b60b8) + local_170 + 0x1c)
                  );
        cRBorder::RePosition(*(cRBorder **)(iVar3 + 0xa4));
        uVar4 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
        *(undefined4 *)(iVar3 + 0xcc) = uVar4;
        tColour::tColour(local_a8,1.0,1.0,1.0,1.0);
        cRBorder::Init(uVar4,uVar6 | 0x20000014,"Replay",0x16,0,fVar11);
        cRBorder::HideInit(*(cRBorder **)(iVar3 + 0xcc));
      }
      if ((uVar10 & 1) != 0) {
        iVar5 = *(int *)(iVar3 + 0x2c);
        tColour::tColour((tColour *)&local_108,0.78431374,0.78431374,0.78431374,0.7);
        *(undefined4 *)(iVar5 + 0x1b0) = local_108;
        *(undefined4 *)(iVar5 + 0x1b4) = uStack_104;
        *(undefined4 *)(iVar5 + 0x1b8) = uStack_100;
        *(undefined4 *)(iVar5 + 0x1bc) = uStack_fc;
        iVar5 = *(int *)(iVar3 + 0xcc);
        tColour::tColour((tColour *)&local_118,0.78431374,0.78431374,0.78431374,0.7);
        *(undefined4 *)(iVar5 + 0x1b0) = local_118;
        *(undefined4 *)(iVar5 + 0x1b4) = uStack_114;
        *(undefined4 *)(iVar5 + 0x1b8) = uStack_110;
        *(undefined4 *)(iVar5 + 0x1bc) = uStack_10c;
      }
    }
    iVar3 = iVar3 + 4;
    local_174 = local_174 + 1;
    local_170 = local_170 + 0x38;
  } while (local_174 != 0xb);
  if (*(char *)(param_1 + 0x10) == '\0') {
    uVar4 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
    *(undefined4 *)(param_1 + 0x1c) = uVar4;
    tColour::tColour(local_148,1.0,1.0,1.0,1.0);
    cRBorder::Init(uVar4,0x20000014,"Back",0x17,0,0x43d80000);
    uVar4 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
    *(undefined4 *)(param_1 + 0x20) = uVar4;
    tColour::tColour(local_158,1.0,1.0,1.0,1.0);
    cRBorder::Init(uVar4,0x20000014,"Challenge Scores",0x17,0,0x43d80000);
    SetExitNextPos((cRHighScore *)param_1);
  }
  else {
    uVar4 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
    *(undefined4 *)(param_1 + 0x24) = uVar4;
    tColour::tColour(local_128,1.0,1.0,1.0,1.0);
    cRBorder::Init(uVar4,0x20000014,"Cancel",0x17,0,0x43d80000);
    cRBorder::SetKeyLeft(*(cRBorder **)(param_1 + 0x24),0xb);
    uVar4 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
    *(undefined4 *)(param_1 + 0x28) = uVar4;
    tColour::tColour(local_138,1.0,1.0,1.0,1.0);
    cRBorder::Init(uVar4,0x20000014,"Submit",0x17,0,0x43d80000);
    cRBorder::SetKeyLeft(*(cRBorder **)(param_1 + 0x28),5);
  }
  return;
}
