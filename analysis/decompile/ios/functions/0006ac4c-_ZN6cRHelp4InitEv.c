/*
 * mangled: _ZN6cRHelp4InitEv
 * demangled: cRHelp::Init()
 * address: 0006ac4c
 * size: 136
 */

/* cRHelp::Init() */

void __thiscall cRHelp::Init(cRHelp *this)

{
  undefined *puVar1;
  int iVar2;

  RShellMusicPlay("mainmenu.mp4",0,"");
  puVar1 = PTR__Game_001b60b8;
  cRFade::FadeIn((cRFade *)(*(int *)PTR__Game_001b60b8 + 0x24));
  this[4] = (cRHelp)0x0;
  iVar2 = cRLandscapeManager::Import
                    ((cRLandscapeManager *)(&DAT_003593d8 + *(int *)puVar1),"Help.txt");
  cRBackdrop::Change((cRBackdrop *)(*(int *)puVar1 + 0x4d2e0),
                     (cRLandscape *)(&DAT_003593dc + *(int *)puVar1 + iVar2 * 0x1ac),false);
  cRBorderManager::SetJustifyCentre((cRBorderManager *)(*(int *)puVar1 + 0xd14),0.0);
  return;
}
