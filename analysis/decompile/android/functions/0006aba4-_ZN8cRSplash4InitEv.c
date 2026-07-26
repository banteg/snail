/*
 * mangled: _ZN8cRSplash4InitEv
 * demangled: cRSplash::Init()
 * address: 0006aba4
 * size: 508
 */

/* cRSplash::Init() */

void __thiscall cRSplash::Init(cRSplash *this)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  float fVar7;
  float extraout_s0;
  float extraout_s1;
  float extraout_s2;
  float extraout_s3;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 local_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;

  iVar3 = DAT_0006adb4;
  iVar5 = DAT_0006adb0 + 0x6abbc;
  piVar6 = *(int **)(iVar5 + DAT_0006adb4);
  cRFade::FadeIn((cRFade *)(*piVar6 + 0x24));
  cRStarManager::Hide((cRStarManager *)(*piVar6 + 0x4d440));
  RShellMusicPlay((char *)(iVar5 + DAT_0006adb8),0,(char *)(iVar5 + DAT_0006adbc));
  iVar4 = *piVar6;
  if (*(int *)(gOFOData + iVar4 + 0x1ebc) == 0) {
    iVar4 = cRLandscapeManager::Import
                      ((cRLandscapeManager *)(gSegmentText + iVar4 + 0x3d8),
                       (char *)(iVar5 + DAT_0006adc0));
  }
  else {
    iVar4 = cRLandscapeManager::Import
                      ((cRLandscapeManager *)(gSegmentText + iVar4 + 0x3d8),
                       (char *)(iVar5 + DAT_0006adcc));
  }
  piVar6 = *(int **)(iVar5 + iVar3);
  fVar7 = (float)cRBackdrop::Change((cRBackdrop *)(*piVar6 + 0x4d2e0),
                                    (cRLandscape *)(gSegmentText + iVar4 * 0x1ac + *piVar6 + 0x3dc),
                                    false);
  cRBorderManager::SetJustifyCentre((cRBorderManager *)(*piVar6 + 0xd14),fVar7);
  iVar3 = cRBorderManager::GetBorder((cRBorderManager *)(*piVar6 + 0xd14));
  iVar4 = *(int *)(gOFOData + *piVar6 + 0x1ebc);
  *(int *)(this + 8) = iVar3;
  if (iVar4 == 0) {
    tColour::tColour((tColour *)&local_28,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
    iVar4 = DAT_0006adc4;
  }
  else {
    if (iVar4 != 1) goto LAB_0006ad00;
    tColour::tColour((tColour *)&local_38,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
    iVar4 = DAT_0006adc8;
    local_28 = local_38;
    uStack_24 = uStack_34;
    uStack_20 = uStack_30;
    uStack_1c = uStack_2c;
  }
  cRBorder::Init(iVar3,0x20400002,iVar5 + iVar4,0x14,0,DAT_0006ada0,local_28,uStack_24,uStack_20,
                 uStack_1c,2,0);
  iVar3 = *(int *)(this + 8);
LAB_0006ad00:
  uVar1 = DAT_0006ada4;
  *(undefined4 *)(this + 0xc) = 0;
  *this = (cRSplash)0x0;
  uVar2 = DAT_0006ada8;
  *(undefined4 *)(iVar3 + 0x6e8) = uVar1;
  *(undefined4 *)(this + 0x10) = uVar2;
  *(undefined4 *)(this + 0x14) = DAT_0006adac;
  return;
}
