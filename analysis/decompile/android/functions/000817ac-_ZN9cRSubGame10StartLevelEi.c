/*
 * mangled: _ZN9cRSubGame10StartLevelEi
 * demangled: cRSubGame::StartLevel(int)
 * address: 000817ac
 * size: 2556
 */

/* cRSubGame::StartLevel(int) */

void __thiscall cRSubGame::StartLevel(cRSubGame *this,int param_1)

{
  uint uVar1;
  byte bVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int unaff_r7;
  cRSubGoldy *this_00;
  int *piVar7;
  uint in_fpscr;
  float fVar8;
  float extraout_s0;
  undefined8 uVar9;
  float fVar10;
  undefined4 uVar11;

  iVar4 = DAT_00081864;
  iVar6 = DAT_00081860 + 0x817c8;
  piVar7 = *(int **)(iVar6 + DAT_00081864);
  cRFade::FadeIn((cRFade *)(*piVar7 + 0x24));
  cRStarManager::UnHide((cRStarManager *)(*piVar7 + 0x4d440));
  cRQuit::Init((cRQuit *)(this + 8));
  cRQuit::On((cRQuit *)(this + 8));
  if (*(int *)(this + 0x60) == 7) {
    HideScores(this);
  }
  else {
    UnHideScores(this);
  }
  uVar3 = gRMathRand2();
  fVar10 = (float)VectorSignedToFloat(uVar3,(byte)(in_fpscr >> 0x16) & 3);
  switch((int)(fVar10 * DAT_00081858 * DAT_0008185c)) {
  case 0:
    RShellMusicPlay((char *)(iVar6 + DAT_000821fc),0,(char *)(iVar6 + DAT_000821f8));
    break;
  case 1:
    RShellMusicPlay((char *)(iVar6 + DAT_00082200),0,(char *)(iVar6 + DAT_000821f8));
    break;
  case 2:
    goto LAB_00081888;
  case 3:
    RShellMusicPlay((char *)(iVar6 + DAT_000821f4),0,(char *)(iVar6 + DAT_000821f8));
    break;
  case 4:
LAB_00081888:
    RShellMusicPlay((char *)(iVar6 + DAT_00081868),0,(char *)(iVar6 + DAT_0008186c));
  }
  uVar11 = DAT_00081884;
  uVar3 = DAT_00081878;
  *(undefined4 *)(this + 0x34) = DAT_00081884;
  fVar10 = DAT_00081880;
  *(undefined4 *)(this + 0x332da0) = uVar3;
  *(undefined4 *)(this + 0x38) = DAT_0008187c;
  *(float *)(this + 0x332da4) = fVar10;
  *(undefined4 *)(this + 0x30) = 0;
  cREnemyManager::Init((cREnemyManager *)(this + 0x332da8));
  cRDamageGuage::Init((cRDamageGuage *)(this + 0xfe78));
  cRProgressBar::Init();
  *(undefined4 *)(this + 0xff0c) = uVar11;
  *(undefined4 *)(this + 0xfe10) = uVar11;
  cRSubLazerManager::Init((cRSubLazerManager *)(this + 0x41a8));
  cRSaltManager::Init((cRSaltManager *)(this + 0x4e78));
  cRVoiceManager::ReSet(*(cRVoiceManager **)(iVar6 + DAT_00081870));
  fVar8 = (float)cRSubTracks::Load((cRSubTracks *)(this + 0xa0),*(int *)(this + 0x60),param_1);
  if ((this[0x30fcc0] == (cRSubGame)0x0) && (this[0x30fcc1] == (cRSubGame)0x0)) {
    iVar5 = *(int *)(this + 0x60);
    if (iVar5 == 3) {
      *(undefined4 *)(this + 0x4c) = *(undefined4 *)(*(int *)(iVar6 + DAT_00082204) + 0x44);
      goto LAB_000819b4;
    }
    if ((iVar5 == 0 || iVar5 == 4) || (iVar5 == 7)) {
      in_fpscr = in_fpscr & 0xfffffff | (uint)(*(float *)(this + 0x162c) == DAT_000821d8) << 0x1e;
      if (SUB41(in_fpscr >> 0x1e,0)) {
        uVar3 = CalcSliderToRate(this,fVar8);
        *(undefined4 *)(this + 0x4c) = uVar3;
      }
      else {
        *(float *)(this + 0x4c) =
             DAT_000821e0 + (*(float *)(this + 0x162c) / DAT_000821dc) * DAT_000821e4;
      }
      goto LAB_000819b4;
    }
    if (iVar5 == 1) {
      iVar5 = *(int *)(iVar6 + DAT_00082204);
      VectorSignedToFloat(*(undefined4 *)(iVar5 + 0x40),(byte)(in_fpscr >> 0x16) & 3);
      uVar3 = CalcSliderToRate(this,fVar8);
      fVar8 = (float)VectorSignedToFloat(*(undefined4 *)(iVar5 + 0x48),(byte)(in_fpscr >> 0x16) & 3)
      ;
      *(undefined4 *)(this + 0x4c) = uVar3;
      *(float *)(this + 0x50) = fVar8 / fVar10;
      goto LAB_000819b4;
    }
    if (iVar5 - 2U < 2) {
      uVar3 = CalcSliderToRate(this,fVar8);
      *(undefined4 *)(this + 0x4c) = uVar3;
      goto LAB_000819b4;
    }
  }
  else {
    iVar5 = *(int *)(this + 0x30fcc4);
    *(undefined4 *)(this + 0x4c) = *(undefined4 *)(iVar5 + 0x48);
    fVar10 = DAT_00081880;
    *(undefined4 *)(this + 0x60) = *(undefined4 *)(iVar5 + 0x2c);
    *(undefined4 *)(this + 0x48) = *(undefined4 *)(iVar5 + 0x50);
    *(undefined4 *)(this + 0x44) = *(undefined4 *)(iVar5 + 0x4c);
    fVar8 = (float)VectorSignedToFloat(*(undefined4 *)(iVar5 + 0x50),(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(this + 0x50) = fVar8 / fVar10;
LAB_000819b4:
    if ((this[0x30fcc0] != (cRSubGame)0x0) || (this[0x30fcc1] != (cRSubGame)0x0)) {
      *(undefined4 *)(this + 0x321070) =
           *(undefined4 *)
            ("_ZN10cRSubGoldy13HealthCollectEP11cRSubHealth" + *(int *)(this + 0x30fcc4) + 6);
      *(undefined4 *)(this + 0x321074) =
           *(undefined4 *)
            ("_ZN10cRSubGoldy13HealthCollectEP11cRSubHealth" + *(int *)(this + 0x30fcc4) + 10);
      goto LAB_00081a14;
    }
    iVar5 = *(int *)(this + 0x60);
    if (iVar5 - 2U < 2) {
      fVar10 = *(float *)(this + 0x1634) / DAT_000821dc;
      *(float *)(this + 0x321070) = *(float *)(this + 0x1630) / DAT_000821dc;
      *(float *)(this + 0x321074) = fVar10;
      goto LAB_00081a14;
    }
  }
  if ((iVar5 == 0 || iVar5 == 4) || (iVar5 == 7)) {
    fVar10 = *(float *)(this + 0x1634) / DAT_000821dc;
    *(float *)(this + 0x321070) = *(float *)(this + 0x1630) / DAT_000821dc;
    *(float *)(this + 0x321074) = fVar10;
  }
  else if (iVar5 == 1) {
    fVar10 = (float)VectorSignedToFloat(*(undefined4 *)(*(int *)(iVar6 + DAT_00082204) + 0x48),
                                        (byte)(in_fpscr >> 0x16) & 3);
    fVar10 = (fVar10 / DAT_000821dc) * DAT_000821ec;
    *(float *)(this + 0x321074) = fVar10;
    *(float *)(this + 0x321070) = fVar10;
  }
LAB_00081a14:
  cRParcelManager::Init((cRParcelManager *)(this + 0x31f770));
  if (*(char *)(**(int **)(iVar6 + iVar4) + 0x4d3dc) != '\0') {
    cRBorder::HideInit(*(cRBorder **)(this + 0x8c58));
    cRBorder::HideInit(*(cRBorder **)(this + 0x8c5c));
  }
  fVar10 = (float)GenerateLevel(this,param_1);
  if (((this[0x30fcc0] == (cRSubGame)0x0) && (this[0x30fcc1] == (cRSubGame)0x0)) &&
     (*(int *)(this + 0x60) == 0)) {
    fVar10 = (float)SetGameState(1,*(int *)(this + 0xfd90),*(int *)(this + 100),
                                 *(int *)(this + 0x13ab8));
  }
  if (*(int *)(this + 0x1640) == 8) {
    fVar10 = (float)RAND(fVar10,(char *)0x40800000);
    switch((int)fVar10) {
    case 0:
      unaff_r7 = cRLandscapeManager::Import
                           ((cRLandscapeManager *)(gSegmentText + **(int **)(iVar6 + iVar4) + 0x3d8)
                            ,(char *)(iVar6 + DAT_00082210));
      break;
    case 1:
      unaff_r7 = cRLandscapeManager::Import
                           ((cRLandscapeManager *)(gSegmentText + **(int **)(iVar6 + iVar4) + 0x3d8)
                            ,(char *)(iVar6 + DAT_0008220c));
      break;
    case 2:
      unaff_r7 = cRLandscapeManager::Import
                           ((cRLandscapeManager *)(gSegmentText + **(int **)(iVar6 + iVar4) + 0x3d8)
                            ,(char *)(iVar6 + DAT_00082208));
      break;
    case 3:
      unaff_r7 = cRLandscapeManager::Import
                           ((cRLandscapeManager *)(gSegmentText + **(int **)(iVar6 + iVar4) + 0x3d8)
                            ,(char *)(iVar6 + DAT_000821f0));
    }
    fVar10 = (float)cRLandscapeManager::Init((cRLandscapeManager *)(this + 0x315b54),unaff_r7);
    fVar10 = (float)RAND(fVar10,(char *)0x3f800000);
    uVar1 = in_fpscr & 0xfffffff | (uint)(fVar10 < DAT_000821e8) << 0x1f |
            (uint)(fVar10 == DAT_000821e8) << 0x1e;
    in_fpscr = uVar1 | (uint)(NAN(fVar10) || NAN(DAT_000821e8)) << 0x1c;
    bVar2 = (byte)(uVar1 >> 0x18);
    if ((bool)(bVar2 >> 6 & 1) || bVar2 >> 7 != ((byte)(in_fpscr >> 0x1c) & 1)) {
      *(undefined1 *)(**(int **)(iVar6 + iVar4) + 0x4d354) = 0;
    }
    else {
      *(undefined1 *)(**(int **)(iVar6 + iVar4) + 0x4d354) = 1;
    }
    fVar10 = (float)RAND(extraout_s0,(char *)0x3f800000);
    GetSkirtColourRandom(this,(tColour *)(this + 0x1598),fVar10);
  }
  else {
    cRLandscapeManager::Init((cRLandscapeManager *)(this + 0x315b54),*(int *)(this + 0x1638));
  }
  uVar3 = DAT_00081884;
  piVar7 = *(int **)(iVar6 + iVar4);
  cLinkedList<cRBod>::AddAfter
            ((cLinkedList<cRBod> *)(*piVar7 + 0x358),(cRBod *)(this + 0xf9f0),
             (cRBod *)(this + 0x2c1c));
  cLinkedList<cRBod>::AddAfter
            ((cLinkedList<cRBod> *)(*piVar7 + 0x358),(cRBod *)(this + 0xfa1c),
             (cRBod *)(this + 0x2bf0));
  *(undefined4 *)(this + 0xfa34) = uVar3;
  iVar4 = *piVar7;
  *(undefined4 *)(this + 0xfa30) = uVar3;
  this_00 = (cRSubGoldy *)(this + 0xfac4);
  *(undefined4 *)(this + 0xfa2c) = uVar3;
  *(undefined4 *)(this + 0xfa08) = uVar3;
  *(undefined4 *)(this + 0xfa04) = uVar3;
  *(undefined4 *)(this + 64000) = uVar3;
  fVar10 = (float)cLinkedList<cRBod>::AddAfter
                            ((cLinkedList<cRBod> *)(iVar4 + 0x358),(cRBod *)(this + 0x6458),
                             (cRBod *)(this + 0x2ccc));
  uVar11 = VectorSignedToFloat(*(undefined4 *)(this + 0x70),(byte)(in_fpscr >> 0x16) & 3);
  *(uint *)(this + 0x645c) = *(uint *)(this + 0x645c) & 0xffffffdf;
  *(undefined4 *)(this + 0x646c) = uVar3;
  *(cRSubGoldy **)(this + 0x64a0) = this_00;
  *(undefined4 *)(this + 0x6468) = uVar3;
  *(undefined4 *)(this + 0x6470) = uVar11;
  tColourSmall::Alpha((tColourSmall *)(this + 0x6480),fVar10);
  iVar4 = *piVar7;
  *(undefined4 *)(*(int *)(this + 0x647c) + 8) = 2;
  fVar10 = (float)cLinkedList<cRBod>::AddAfter
                            ((cLinkedList<cRBod> *)(iVar4 + 0x358),(cRBod *)(this + 0x64ac),
                             (cRBod *)(this + 0x2ccc));
  uVar11 = VectorSignedToFloat(*(undefined4 *)(this + 0x78),(byte)(in_fpscr >> 0x16) & 3);
  *(uint *)(this + 0x64b0) = *(uint *)(this + 0x64b0) & 0xffffffdf;
  *(undefined4 *)(this + 0x64bc) = uVar3;
  *(cRSubGoldy **)(this + 0x64f4) = this_00;
  *(undefined4 *)(this + 0x64c0) = uVar3;
  *(undefined4 *)(this + 0x64c4) = uVar11;
  tColourSmall::Alpha((tColourSmall *)(this + 0x64d4),fVar10);
  iVar4 = *piVar7;
  this[0x80] = (cRSubGame)0x0;
  *(undefined4 *)(*(int *)(this + 0x64d0) + 8) = 2;
  *(undefined4 *)(this + 0x30fccc) = 0;
  *(undefined4 *)(this + 0x334600) = 0;
  *(undefined4 *)(this + 0x5c) = 2;
  cRMouse::SetInActive((cRMouse *)(iVar4 + 0x228));
  *(undefined4 *)(this + 0x122b0) = 0;
  *(undefined4 *)(this + 0xfec8) = 1;
  cRSubGoldy::Init(this_00,1);
  cLinkedList<cRBod>::Add((cLinkedList<cRBod> *)(*piVar7 + 0x358),(cRBod *)(this + 0x13348));
  cLinkedList<cRBod>::Add((cLinkedList<cRBod> *)(*piVar7 + 0x358),(cRBod *)(this + 0x1288c));
  cLinkedList<cRBod>::Add((cLinkedList<cRBod> *)(*piVar7 + 0x358),(cRBod *)(this + 0x12c20));
  cLinkedList<cRBod>::Add((cLinkedList<cRBod> *)(*piVar7 + 0x358),(cRBod *)(this + 0x12fb4));
  cLinkedList<cRBod>::Add((cLinkedList<cRBod> *)(*piVar7 + 0x358),(cRBod *)(this + 0x1399c));
  iVar4 = *piVar7;
  *(uint *)(this + 0x139a0) = *(uint *)(this + 0x139a0) | 0x80;
  cLinkedList<cRBod>::Add((cLinkedList<cRBod> *)(iVar4 + 0x358),(cRBod *)(this + 0x122c4));
  cLinkedList<cRBod>::Add((cLinkedList<cRBod> *)(*piVar7 + 0x358),(cRBod *)this_00);
  cRSlugVoiceManager::Init((cRSlugVoiceManager *)(this + 0x8c4c));
  uVar9 = cLinkedList<cRBod>::AddAfter
                    ((cLinkedList<cRBod> *)(*piVar7 + 0x358),(cRBod *)(this + 0x315b24),
                     (cRBod *)(this + 0x2ca0));
  *(cRSubGoldy **)(this + 0x315b50) = this_00;
  if (*(int *)(this + 0x60) == 0) {
    sprintf((char *)(*(int *)(this + 0x8c64) + 0x2c4),(char *)(iVar6 + DAT_00081874),
            *(undefined4 *)(this + 0x163c));
    cRBorder::UnHideInit(*(cRBorder **)(this + 0x8c60));
    uVar9 = cRBorder::UnHideInit(*(cRBorder **)(this + 0x8c64));
  }
  uVar9 = RShellSetMouse(0,(float)uVar9,(float)((ulonglong)uVar9 >> 0x20));
  RShellSetMouse(1,(float)uVar9,(float)((ulonglong)uVar9 >> 0x20));
  *(undefined4 *)(this + 0x1207c) = 0x43a00000;
  *(undefined4 *)(this + 0x12080) = 0x43a00000;
  *this = (cRSubGame)0x1;
  CalcRate();
  return;
}
