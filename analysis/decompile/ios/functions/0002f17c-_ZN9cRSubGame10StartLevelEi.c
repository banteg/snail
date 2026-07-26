/*
 * mangled: _ZN9cRSubGame10StartLevelEi
 * demangled: cRSubGame::StartLevel(int)
 * address: 0002f17c
 * size: 4212
 */

/* cRSubGame::StartLevel(int) */

void __thiscall cRSubGame::StartLevel(cRSubGame *this,int param_1)

{
  byte bVar1;
  undefined *puVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  cRSubGame *pcVar7;
  int iVar8;
  cRSubGame *pcVar9;
  cRSubGoldy *this_00;
  uint in_fpscr;
  float fVar10;
  float fVar11;
  float fVar12;

  puVar2 = PTR__Game_001b60b8;
  cRFade::FadeIn((cRFade *)(*(int *)PTR__Game_001b60b8 + 0x24));
  cRStarManager::UnHide((cRStarManager *)(*(int *)puVar2 + 0x4e718));
  cRQuit::Init((cRQuit *)(this + 8));
  cRBorder::UnHideInit(*(cRBorder **)(this + 0xc));
  if (*(int *)(this + 0x58) == 7) {
    if (*(cRBorder **)(this + 0x85e4) != (cRBorder *)0x0) {
      cRBorder::HideInit(*(cRBorder **)(this + 0x85e4));
    }
    if (*(cRBorder **)(this + 0x85e0) != (cRBorder *)0x0) {
      cRBorder::HideInit(*(cRBorder **)(this + 0x85e0));
    }
  }
  else {
    cRBorder::UnHideInit(*(cRBorder **)(this + 0x85e4));
    cRBorder::UnHideInit(*(cRBorder **)(this + 0x85e0));
  }
  uVar3 = gRMathRand2();
  fVar10 = (float)VectorSignedToFloat(uVar3,(byte)(in_fpscr >> 0x16) & 3);
  switch((int)(fVar10 * 3.0517578e-05 * 4.0)) {
  case 0:
    RShellMusicPlay("1.wav",0,"");
    break;
  case 1:
    RShellMusicPlay("2.wav",0,"");
    break;
  case 2:
  case 4:
    RShellMusicPlay("3.wav",0,"");
    break;
  case 3:
    RShellMusicPlay("4.wav",0,"");
  }
  *(undefined4 *)(this + 0x303aac) = 0x42480000;
  *(undefined4 *)(this + 0x303ab0) = 0x42c80000;
  *(undefined4 *)(this + 0x28) = 0;
  *(undefined4 *)(this + 0x2c) = 0;
  *(undefined4 *)(this + 0x30) = 0x3b888889;
  cREnemyManager::Init((cREnemyManager *)(this + 0x303ab4));
  *(undefined4 *)(this + 0xf818) = 0;
  *(undefined4 *)(this + 0xf81c) = 0;
  *(undefined4 *)(this + 0xf80c) = 0;
  *(undefined4 *)(this + 0xf814) = 0;
  *(undefined4 *)(this + 0xf800) = 0;
  this[0xf808] = (cRSubGame)0x0;
  *(undefined4 *)(this + 0xf7fc) = 0;
  *(undefined4 *)(this + 0xf804) = 0x3caaaaab;
  *(undefined4 *)(this + 0xf820) = 0;
  *(undefined4 *)(this + 0xf824) = 0x3d088889;
  *(undefined4 *)(this + 0xf888) = 0;
  *(undefined4 *)(this + 0xf794) = 0;
  *(undefined4 *)(this + 0x3ba4) = 0;
  iVar8 = 0xa4;
  do {
    iVar6 = iVar8 + 0xa4;
    *(undefined4 *)(this + iVar8 + 0x3ba4) = 0;
    iVar8 = iVar6;
  } while (iVar6 != 0xcd0);
  *(undefined4 *)(this + 0x4874) = 0;
  iVar8 = 0x8c;
  do {
    iVar6 = iVar8 + 0x8c;
    *(undefined4 *)(this + iVar8 + 0x4874) = 0;
    iVar8 = iVar6;
  } while (iVar6 != 0x15e0);
  pcVar9 = this + 0x2e0900;
  cRVoiceManager::ReSet((cRVoiceManager *)PTR__gVoiceManager_001b61d8);
  cRSubTracks::Load((cRSubTracks *)(this + 0x98),*(int *)(this + 0x58),param_1);
  puVar2 = PTR__gConfig_001b60d4;
  if ((this[0x2e09cc] == (cRSubGame)0x0) && (this[0x2e09cd] == (cRSubGame)0x0)) {
    iVar8 = *(int *)(this + 0x58);
    if (iVar8 == 3) {
      *(undefined4 *)(this + 0x44) = *(undefined4 *)(PTR__gConfig_001b60d4 + 0x44);
      goto LAB_0002f450;
    }
    if ((iVar8 == 4 || iVar8 == 0) || (iVar8 == 7)) {
      in_fpscr = in_fpscr & 0xfffffff | (uint)(*(float *)(this + 0x12ec) == -1.0) << 0x1e;
      if (SUB41(in_fpscr >> 0x1e,0)) {
        *(undefined4 *)(this + 0x44) = 0x3e4ccccd;
      }
      else {
        *(float *)(this + 0x44) = (*(float *)(this + 0x12ec) / 100.0) * 0.90000004 + 0.2;
      }
      goto LAB_0002f450;
    }
    if (iVar8 == 1) {
      fVar10 = (float)VectorSignedToFloat(*(undefined4 *)(PTR__gConfig_001b60d4 + 0x40),
                                          (byte)(in_fpscr >> 0x16) & 3);
      in_fpscr = in_fpscr & 0xfffffff | (uint)(fVar10 / 100.0 == 1.0) << 0x1e;
      if (SUB41(in_fpscr >> 0x1e,0)) {
        fVar10 = 1.1;
      }
      else {
        fVar10 = (fVar10 / 100.0) * 0.90000004 + 0.2;
      }
      *(float *)(this + 0x44) = fVar10;
      fVar10 = (float)VectorSignedToFloat(*(undefined4 *)(puVar2 + 0x48),
                                          (byte)(in_fpscr >> 0x16) & 3);
      *(float *)(this + 0x48) = fVar10 / 100.0;
      goto LAB_0002f450;
    }
    if (iVar8 - 2U < 2) {
      in_fpscr = in_fpscr & 0xfffffff |
                 (uint)(*(float *)(PTR__gConfig_001b60d4 + 0x44) == 1.0) << 0x1e;
      if (SUB41(in_fpscr >> 0x1e,0)) {
        fVar10 = 1.1;
      }
      else {
        fVar10 = *(float *)(PTR__gConfig_001b60d4 + 0x44) * 0.90000004 + 0.2;
      }
      *(float *)(this + 0x44) = fVar10;
      goto LAB_0002f450;
    }
  }
  else {
    iVar8 = *(int *)(this + 0x2e09d0);
    *(undefined4 *)(this + 0x44) = *(undefined4 *)(iVar8 + 0x48);
    *(undefined4 *)(this + 0x58) = *(undefined4 *)(iVar8 + 0x2c);
    *(undefined4 *)(this + 0x40) = *(undefined4 *)(iVar8 + 0x50);
    *(undefined4 *)(this + 0x3c) = *(undefined4 *)(iVar8 + 0x4c);
    fVar10 = (float)VectorSignedToFloat(*(undefined4 *)(iVar8 + 0x50),(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(this + 0x48) = fVar10 / 100.0;
LAB_0002f450:
    if ((this[0x2e09cc] != (cRSubGame)0x0) || (this[0x2e09cd] != (cRSubGame)0x0)) {
      *(undefined4 *)(this + 0x2f1d7c) = *(undefined4 *)(*(int *)(this + 0x2e09d0) + 0x1fab0);
      *(undefined4 *)(this + 0x2f1d80) = *(undefined4 *)(*(int *)(this + 0x2e09d0) + 0x1fab4);
      goto LAB_0002f48c;
    }
    iVar8 = *(int *)(this + 0x58);
    if (iVar8 - 2U < 2) {
      *(float *)(this + 0x2f1d7c) = *(float *)(this + 0x12f0) / 100.0;
      *(float *)(this + 0x2f1d80) = *(float *)(this + 0x12f4) / 100.0;
      goto LAB_0002f48c;
    }
  }
  puVar2 = PTR__gConfig_001b60d4;
  if ((iVar8 == 4 || iVar8 == 0) || (iVar8 == 7)) {
    *(float *)(this + 0x2f1d7c) = *(float *)(this + 0x12f0) / 100.0;
    *(float *)(this + 0x2f1d80) = *(float *)(this + 0x12f4) / 100.0;
  }
  else if (iVar8 == 1) {
    fVar10 = (float)VectorSignedToFloat(*(undefined4 *)(PTR__gConfig_001b60d4 + 0x48),
                                        (byte)(in_fpscr >> 0x16) & 3);
    *(float *)(this + 0x2f1d7c) = (fVar10 / 100.0) * 0.8;
    fVar10 = (float)VectorSignedToFloat(*(undefined4 *)(puVar2 + 0x48),(byte)(in_fpscr >> 0x16) & 3)
    ;
    *(float *)(this + 0x2f1d80) = (fVar10 / 100.0) * 0.8;
  }
LAB_0002f48c:
  iVar8 = 1;
  *(undefined4 *)(this + 0x2f04a8) = 0;
  puVar2 = PTR__Game_001b60b8;
  pcVar7 = this + 0x2f0528;
  *(int *)(this + 0x2f04ac) = *(int *)PTR__Game_001b60b8 + 0x72b78;
  do {
    *(undefined4 *)pcVar7 = 0;
    iVar8 = iVar8 + 1;
    *(int *)(pcVar7 + 4) = *(int *)puVar2 + 0x72b78;
    pcVar7 = pcVar7 + 0x80;
  } while (iVar8 != 0x32);
  if (*(char *)(*(int *)puVar2 + 0x4e6b4) != '\0') {
    cRBorder::HideInit(*(cRBorder **)(this + 0x85e0));
    cRBorder::HideInit(*(cRBorder **)(this + 0x85e4));
  }
  GenerateLevel(this,param_1);
  if (((this[0x2e09cc] == (cRSubGame)0x0) && (this[0x2e09cd] == (cRSubGame)0x0)) &&
     (*(int *)(this + 0x58) == 0)) {
    SetGameState(1,*(int *)(this + 0xf714),*(int *)(this + 0x5c),*(int *)(this + 0x13434));
  }
  if (*(int *)(this + 0x1300) == 8) {
    fVar10 = (float)RAND(4.0,(char *)0x0);
    switch((int)fVar10) {
    case 0:
      pcVar9 = (cRSubGame *)
               cRLandscapeManager::Import
                         ((cRLandscapeManager *)(&DAT_003593d8 + *(int *)PTR__Game_001b60b8),
                          "SpaceBluesWhorl.txt");
      break;
    case 1:
      pcVar9 = (cRSubGame *)
               cRLandscapeManager::Import
                         ((cRLandscapeManager *)(&DAT_003593d8 + *(int *)PTR__Game_001b60b8),
                          "SpaceGreenWarp.txt");
      break;
    case 2:
      pcVar9 = (cRSubGame *)
               cRLandscapeManager::Import
                         ((cRLandscapeManager *)(&DAT_003593d8 + *(int *)PTR__Game_001b60b8),
                          "SpacePurple.txt");
      break;
    case 3:
      pcVar9 = (cRSubGame *)
               cRLandscapeManager::Import
                         ((cRLandscapeManager *)(&DAT_003593d8 + *(int *)PTR__Game_001b60b8),
                          "SpaceRed.txt");
    }
    cRLandscapeManager::Init((cRLandscapeManager *)(this + 0x2e6860),(int)pcVar9);
    fVar10 = (float)RAND(1.0,(char *)0x0);
    uVar4 = in_fpscr & 0xfffffff | (uint)(fVar10 < 0.5) << 0x1f | (uint)(fVar10 == 0.5) << 0x1e;
    in_fpscr = uVar4 | (uint)NAN(fVar10) << 0x1c;
    bVar1 = (byte)(uVar4 >> 0x18);
    if ((bool)(bVar1 >> 6 & 1) || bVar1 >> 7 != ((byte)(in_fpscr >> 0x1c) & 1)) {
      *(undefined1 *)(*(int *)PTR__Game_001b60b8 + 0x4d348) = 0;
    }
    else {
      *(undefined1 *)(*(int *)PTR__Game_001b60b8 + 0x4d348) = 1;
    }
    fVar10 = (float)RAND(1.0,(char *)0x0);
    fVar11 = (float)VectorSignedToFloat((uint)*(ushort *)(*(int *)(this + 0x50) + 0xc),
                                        (byte)(in_fpscr >> 0x16) & 3);
    iVar8 = (int)(fVar10 * fVar11) * 4 + *(int *)(this + 0x50);
    fVar10 = (float)VectorSignedToFloat((uint)*(byte *)(iVar8 + 0x12),(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(this + 0x1258) = fVar10 / 255.0;
    fVar10 = (float)VectorSignedToFloat((uint)*(byte *)(iVar8 + 0x13),(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(this + 0x125c) = fVar10 / 255.0;
    bVar1 = *(byte *)(iVar8 + 0x14);
    *(undefined4 *)(this + 0x1264) = 0x3efefeff;
    fVar10 = (float)VectorSignedToFloat((uint)bVar1,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(this + 0x1260) = fVar10 / 255.0;
  }
  else {
    cRLandscapeManager::Init((cRLandscapeManager *)(this + 0x2e6860),*(int *)(this + 0x12f8));
  }
  uVar4 = *(uint *)(this + 0xf37c);
  if ((uVar4 & 0x200) == 0) {
    *(cRSubGame **)(this + 0xf380) = this + 0x25a4;
    iVar8 = *(int *)(this + 0x25b0);
    if (iVar8 != 0) {
      *(cRSubGame **)(iVar8 + 8) = this + 0xf378;
    }
    *(int *)(this + 0xf384) = iVar8;
    uVar5 = *(uint *)(this + 0xf3a8);
    *(cRSubGame **)(this + 0x25b0) = this + 0xf378;
    *(uint *)(this + 0xf37c) = uVar4 | 0x200;
  }
  else {
    RShellError("List ADDafter");
    uVar5 = *(uint *)(this + 0xf3a8);
  }
  if ((uVar5 & 0x200) == 0) {
    *(cRSubGame **)(this + 0xf3ac) = this + 0x2578;
    iVar8 = *(int *)(this + 0x2584);
    *(int *)(this + 0xf3b0) = iVar8;
    if (iVar8 != 0) {
      *(cRSubGame **)(iVar8 + 8) = this + 0xf3a4;
    }
    *(cRSubGame **)(this + 0x2584) = this + 0xf3a4;
    *(uint *)(this + 0xf3a8) = uVar5 | 0x200;
  }
  else {
    RShellError("List ADDafter");
  }
  uVar4 = *(uint *)(this + 0x5de4);
  *(undefined4 *)(this + 0xf3bc) = 0;
  *(undefined4 *)(this + 0xf3b8) = 0;
  *(undefined4 *)(this + 0xf3b4) = 0;
  *(undefined4 *)(this + 0xf390) = 0;
  *(undefined4 *)(this + 0xf38c) = 0;
  *(undefined4 *)(this + 0xf388) = 0;
  if ((uVar4 & 0x200) == 0) {
    *(cRSubGame **)(this + 0x5de8) = this + 0x2654;
    *(undefined4 *)(this + 0x5dec) = *(undefined4 *)(this + 0x2660);
    *(cRSubGame **)(this + 0x2660) = this + 0x5de0;
    if (*(int *)(this + 0x5dec) != 0) {
      *(cRSubGame **)(*(int *)(this + 0x5dec) + 8) = this + 0x5de0;
    }
    *(uint *)(this + 0x5de4) = uVar4 | 0x200;
  }
  else {
    RShellError("List ADDafter");
  }
  *(undefined4 *)(this + 0x5df4) = 0;
  this_00 = (cRSubGoldy *)(this + 0xf448);
  *(undefined4 *)(this + 0x5df8) = 0;
  *(undefined4 *)(this + 0x5df0) = 0;
  *(cRSubGoldy **)(this + 0x5e28) = this_00;
  uVar3 = VectorSignedToFloat(*(undefined4 *)(this + 0x68),(byte)(in_fpscr >> 0x16) & 3);
  *(uint *)(this + 0x5de4) = *(uint *)(this + 0x5de4) & 0xffffffdf;
  *(undefined4 *)(this + 0x5df8) = uVar3;
  tColourSmall::Alpha((tColourSmall *)(this + 0x5e08),0.99);
  *(undefined4 *)(*(int *)(this + 0x5e04) + 8) = 2;
  uVar4 = *(uint *)(this + 0x5e38);
  if ((uVar4 & 0x200) == 0) {
    *(cRSubGame **)(this + 0x5e3c) = this + 0x2654;
    *(undefined4 *)(this + 0x5e40) = *(undefined4 *)(this + 0x2660);
    *(cRSubGame **)(this + 0x2660) = this + 0x5e34;
    if (*(int *)(this + 0x5e40) != 0) {
      *(cRSubGame **)(*(int *)(this + 0x5e40) + 8) = this + 0x5e34;
    }
    *(uint *)(this + 0x5e38) = uVar4 | 0x200;
  }
  else {
    RShellError("List ADDafter");
  }
  *(undefined4 *)(this + 0x5e48) = 0;
  *(undefined4 *)(this + 0x5e4c) = 0;
  *(undefined4 *)(this + 0x5e44) = 0;
  *(cRSubGoldy **)(this + 0x5e7c) = this_00;
  uVar3 = VectorSignedToFloat(*(undefined4 *)(this + 0x70),(byte)(in_fpscr >> 0x16) & 3);
  *(uint *)(this + 0x5e38) = *(uint *)(this + 0x5e38) & 0xffffffdf;
  *(undefined4 *)(this + 0x5e4c) = uVar3;
  tColourSmall::Alpha((tColourSmall *)(this + 0x5e5c),0.99);
  puVar2 = PTR__Game_001b60b8;
  *(undefined4 *)(*(int *)(this + 0x5e58) + 8) = 2;
  *(undefined4 *)(this + 0x2e09d8) = 0;
  *(undefined4 *)(this + 0x305304) = 0;
  this[0x78] = (cRSubGame)0x0;
  *(undefined4 *)(this + 0x54) = 2;
  cRMouse::SetInActive((cRMouse *)(*(int *)puVar2 + 0x228));
  *(undefined4 *)(this + 0x11c2c) = 0;
  *(undefined4 *)(this + 0xf844) = 1;
  cRSubGoldy::Init(this_00,1);
  iVar8 = *(int *)puVar2;
  if ((*(uint *)(this + 77000) & 0x200) == 0) {
    if (*(int *)(iVar8 + 0x35c) == 0) {
      *(cRSubGame **)(iVar8 + 0x35c) = this + 0x12cc4;
      *(undefined4 *)(this + 0x12ccc) = 0;
      *(undefined4 *)(*(int *)(iVar8 + 0x35c) + 0xc) = 0;
    }
    else {
      *(cRSubGame **)(*(int *)(iVar8 + 0x35c) + 8) = this + 0x12cc4;
      *(int *)(*(int *)(*(int *)(iVar8 + 0x35c) + 8) + 0xc) = *(int *)(iVar8 + 0x35c);
      iVar6 = *(int *)(*(int *)(iVar8 + 0x35c) + 8);
      *(int *)(iVar8 + 0x35c) = iVar6;
      *(undefined4 *)(iVar6 + 8) = 0;
    }
    *(uint *)(this + 77000) = *(uint *)(this + 77000) | 0x200;
    iVar8 = *(int *)PTR__Game_001b60b8;
    uVar4 = *(uint *)(this + 0x1220c);
  }
  else {
    RShellError("List ADD");
    iVar8 = *(int *)PTR__Game_001b60b8;
    uVar4 = *(uint *)(this + 0x1220c);
  }
  if ((uVar4 & 0x200) == 0) {
    if (*(int *)(iVar8 + 0x35c) == 0) {
      *(cRSubGame **)(iVar8 + 0x35c) = this + 0x12208;
      *(undefined4 *)(this + 0x12210) = 0;
      *(undefined4 *)(*(int *)(iVar8 + 0x35c) + 0xc) = 0;
    }
    else {
      *(cRSubGame **)(*(int *)(iVar8 + 0x35c) + 8) = this + 0x12208;
      *(int *)(*(int *)(*(int *)(iVar8 + 0x35c) + 8) + 0xc) = *(int *)(iVar8 + 0x35c);
      iVar6 = *(int *)(*(int *)(iVar8 + 0x35c) + 8);
      *(int *)(iVar8 + 0x35c) = iVar6;
      *(undefined4 *)(iVar6 + 8) = 0;
    }
    *(uint *)(this + 0x1220c) = *(uint *)(this + 0x1220c) | 0x200;
    iVar8 = *(int *)PTR__Game_001b60b8;
    uVar4 = *(uint *)(this + 0x125a0);
  }
  else {
    RShellError("List ADD");
    iVar8 = *(int *)PTR__Game_001b60b8;
    uVar4 = *(uint *)(this + 0x125a0);
  }
  if ((uVar4 & 0x200) == 0) {
    if (*(int *)(iVar8 + 0x35c) == 0) {
      *(cRSubGame **)(iVar8 + 0x35c) = this + 0x1259c;
      *(undefined4 *)(this + 0x125a4) = 0;
      *(undefined4 *)(*(int *)(iVar8 + 0x35c) + 0xc) = 0;
    }
    else {
      *(cRSubGame **)(*(int *)(iVar8 + 0x35c) + 8) = this + 0x1259c;
      *(int *)(*(int *)(*(int *)(iVar8 + 0x35c) + 8) + 0xc) = *(int *)(iVar8 + 0x35c);
      iVar6 = *(int *)(*(int *)(iVar8 + 0x35c) + 8);
      *(int *)(iVar8 + 0x35c) = iVar6;
      *(undefined4 *)(iVar6 + 8) = 0;
    }
    *(uint *)(this + 0x125a0) = *(uint *)(this + 0x125a0) | 0x200;
    iVar8 = *(int *)PTR__Game_001b60b8;
    uVar4 = *(uint *)(this + 0x12934);
  }
  else {
    RShellError("List ADD");
    iVar8 = *(int *)PTR__Game_001b60b8;
    uVar4 = *(uint *)(this + 0x12934);
  }
  if ((uVar4 & 0x200) == 0) {
    if (*(int *)(iVar8 + 0x35c) == 0) {
      *(cRSubGame **)(iVar8 + 0x35c) = this + 0x12930;
      *(undefined4 *)(this + 0x12938) = 0;
      *(undefined4 *)(*(int *)(iVar8 + 0x35c) + 0xc) = 0;
    }
    else {
      *(cRSubGame **)(*(int *)(iVar8 + 0x35c) + 8) = this + 0x12930;
      *(int *)(*(int *)(*(int *)(iVar8 + 0x35c) + 8) + 0xc) = *(int *)(iVar8 + 0x35c);
      iVar6 = *(int *)(*(int *)(iVar8 + 0x35c) + 8);
      *(int *)(iVar8 + 0x35c) = iVar6;
      *(undefined4 *)(iVar6 + 8) = 0;
    }
    *(uint *)(this + 0x12934) = *(uint *)(this + 0x12934) | 0x200;
    iVar8 = *(int *)PTR__Game_001b60b8;
    uVar4 = *(uint *)(this + 0x1331c);
  }
  else {
    RShellError("List ADD");
    iVar8 = *(int *)PTR__Game_001b60b8;
    uVar4 = *(uint *)(this + 0x1331c);
  }
  if ((uVar4 & 0x200) == 0) {
    if (*(int *)(iVar8 + 0x35c) == 0) {
      *(cRSubGame **)(iVar8 + 0x35c) = this + 0x13318;
      *(undefined4 *)(this + 0x13320) = 0;
      *(undefined4 *)(*(int *)(iVar8 + 0x35c) + 0xc) = 0;
    }
    else {
      *(cRSubGame **)(*(int *)(iVar8 + 0x35c) + 8) = this + 0x13318;
      *(int *)(*(int *)(*(int *)(iVar8 + 0x35c) + 8) + 0xc) = *(int *)(iVar8 + 0x35c);
      iVar6 = *(int *)(*(int *)(iVar8 + 0x35c) + 8);
      *(int *)(iVar8 + 0x35c) = iVar6;
      *(undefined4 *)(iVar6 + 8) = 0;
    }
    *(uint *)(this + 0x1331c) = *(uint *)(this + 0x1331c) | 0x200;
  }
  else {
    RShellError("List ADD");
  }
  *(uint *)(this + 0x1331c) = *(uint *)(this + 0x1331c) | 0x80;
  iVar8 = *(int *)PTR__Game_001b60b8;
  if ((*(uint *)(this + 0x11c44) & 0x200) == 0) {
    if (*(int *)(iVar8 + 0x35c) == 0) {
      *(cRSubGame **)(iVar8 + 0x35c) = this + 0x11c40;
      *(undefined4 *)(this + 0x11c48) = 0;
      *(undefined4 *)(*(int *)(iVar8 + 0x35c) + 0xc) = 0;
    }
    else {
      *(cRSubGame **)(*(int *)(iVar8 + 0x35c) + 8) = this + 0x11c40;
      *(int *)(*(int *)(*(int *)(iVar8 + 0x35c) + 8) + 0xc) = *(int *)(iVar8 + 0x35c);
      iVar6 = *(int *)(*(int *)(iVar8 + 0x35c) + 8);
      *(int *)(iVar8 + 0x35c) = iVar6;
      *(undefined4 *)(iVar6 + 8) = 0;
    }
    *(uint *)(this + 0x11c44) = *(uint *)(this + 0x11c44) | 0x200;
  }
  else {
    RShellError("List ADD");
  }
  iVar8 = *(int *)PTR__Game_001b60b8;
  if ((*(uint *)(this + 0xf44c) & 0x200) == 0) {
    if (*(int *)(iVar8 + 0x35c) == 0) {
      *(cRSubGoldy **)(iVar8 + 0x35c) = this_00;
      *(undefined4 *)(this + 0xf450) = 0;
      *(undefined4 *)(*(int *)(iVar8 + 0x35c) + 0xc) = 0;
    }
    else {
      *(cRSubGoldy **)(*(int *)(iVar8 + 0x35c) + 8) = this_00;
      *(int *)(*(int *)(*(int *)(iVar8 + 0x35c) + 8) + 0xc) = *(int *)(iVar8 + 0x35c);
      iVar6 = *(int *)(*(int *)(iVar8 + 0x35c) + 8);
      *(int *)(iVar8 + 0x35c) = iVar6;
      *(undefined4 *)(iVar6 + 8) = 0;
    }
    *(uint *)(this + 0xf44c) = *(uint *)(this + 0xf44c) | 0x200;
  }
  else {
    RShellError("List ADD");
  }
  this[0x85d4] = (cRSubGame)0x0;
  uVar4 = *(uint *)(this + 0x2e6834);
  *(undefined4 *)(this + 0x85d8) = 0;
  *(undefined4 *)(this + 0x85dc) = 0x3c888889;
  if ((uVar4 & 0x200) == 0) {
    *(cRSubGame **)(this + 0x2e6838) = this + 0x2628;
    iVar8 = *(int *)(this + 0x2634);
    *(int *)(this + 0x2e683c) = iVar8;
    if (iVar8 != 0) {
      *(cRSubGame **)(iVar8 + 8) = this + 0x2e6830;
    }
    *(cRSubGame **)(this + 0x2634) = this + 0x2e6830;
    *(uint *)(this + 0x2e6834) = uVar4 | 0x200;
  }
  else {
    RShellError("List ADDafter");
  }
  *(cRSubGoldy **)(this + 0x2e685c) = this_00;
  if (*(int *)(this + 0x58) == 0) {
    _sprintf((char *)(*(int *)(this + 0x85ec) + 0x2c4),"0/%i",*(undefined4 *)(this + 0x12fc));
    cRBorder::UnHideInit(*(cRBorder **)(this + 0x85e8));
    cRBorder::UnHideInit(*(cRBorder **)(this + 0x85ec));
  }
  RShellSetMouse(0,320.0,240.0);
  RShellSetMouse(1,320.0,240.0);
  *(undefined4 *)(this + 0x119f8) = 0x43a00000;
  *(undefined4 *)(this + 0x119fc) = 0x43a00000;
  *this = (cRSubGame)0x1;
  if (*(int *)(this + 0x54) == 2) {
    fVar10 = (float)VectorSignedToFloat(*(undefined4 *)(this + 0x70),(byte)(in_fpscr >> 0x16) & 3);
    fVar10 = *(float *)(this + 0xf4ac) / fVar10;
    if (fVar10 < 0.0) {
      fVar10 = 0.0;
    }
    else if (1.0 < fVar10) {
      fVar10 = 1.0;
    }
    iVar8 = *(int *)(this + 0x58);
    if (iVar8 == 3 || iVar8 == 1) {
      *(float *)(this + 0x4c) = *(float *)(this + 0x44) + fVar10 * 0.3;
    }
    else {
      *(float *)(this + 0x4c) = *(float *)(this + 0x44) + fVar10 * 0.2;
    }
    if (*(int *)(this + 0xf7fc) == 2) {
      fVar10 = 0.3;
      if (iVar8 != 4 && iVar8 != 1) {
        fVar10 = 0.4;
      }
      fVar11 = *(float *)(this + 0xf81c);
      if ((fVar11 < 0.25) || (0.75 < fVar11)) {
        fVar12 = *(float *)(this + 0x4c);
        fVar11 = (float)Sin((fVar11 + fVar11 + fVar11 + fVar11) * 3.1415927 + 1.5707964);
        *(float *)(this + 0x4c) = fVar12 + (1.0 - fVar11) * 0.5 * fVar10;
      }
      else {
        *(float *)(this + 0x4c) = *(float *)(this + 0x4c) + fVar10;
      }
    }
    if (*(int *)(this + 0x11a18) == 1) {
      *(float *)(this + 0x4c) = *(float *)(this + 0x4c) + *(float *)(this + 0x11c18) * 0.5;
    }
  }
  else {
    *(undefined4 *)(this + 0x4c) = *(undefined4 *)(this + 0x44);
  }
  return;
}
