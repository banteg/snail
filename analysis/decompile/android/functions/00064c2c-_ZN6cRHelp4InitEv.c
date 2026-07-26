/*
 * mangled: _ZN6cRHelp4InitEv
 * demangled: cRHelp::Init()
 * address: 00064c2c
 * size: 164
 */

/* cRHelp::Init() */

void __thiscall cRHelp::Init(cRHelp *this)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  float fVar5;

  iVar3 = DAT_00064cd0 + 0x64c48;
  RShellMusicPlay((char *)(iVar3 + DAT_00064cd8),0,(char *)(iVar3 + DAT_00064cd4));
  piVar4 = *(int **)(iVar3 + DAT_00064cdc);
  cRFade::FadeIn((cRFade *)(*piVar4 + 0x24));
  iVar2 = DAT_00064ce0;
  iVar1 = *piVar4;
  this[4] = (cRHelp)0x0;
  iVar2 = cRLandscapeManager::Import
                    ((cRLandscapeManager *)(gSegmentText + iVar1 + 0x3d8),(char *)(iVar3 + iVar2));
  fVar5 = (float)cRBackdrop::Change((cRBackdrop *)(*piVar4 + 0x4d2e0),
                                    (cRLandscape *)(gSegmentText + *piVar4 + iVar2 * 0x1ac + 0x3dc),
                                    false);
  cRBorderManager::SetJustifyCentre((cRBorderManager *)(*piVar4 + 0xd14),fVar5);
  return;
}
