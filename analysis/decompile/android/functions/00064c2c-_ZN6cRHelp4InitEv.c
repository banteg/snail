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
  float fVar2;

  RShellMusicPlay("mainmenu",0,"");
  cRFade::FadeIn((cRFade *)(Game + 0x24));
  iVar1 = Game;
  this[4] = (cRHelp)0x0;
  iVar1 = cRLandscapeManager::Import
                    ((cRLandscapeManager *)(gSegmentText + iVar1 + 0x3d8),"Help.txt");
  fVar2 = (float)cRBackdrop::Change((cRBackdrop *)(Game + 0x4d2e0),
                                    (cRLandscape *)(gSegmentText + Game + iVar1 * 0x1ac + 0x3dc),
                                    false);
  cRBorderManager::SetJustifyCentre((cRBorderManager *)(Game + 0xd14),fVar2);
  return;
}
