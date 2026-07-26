/*
 * mangled: _ZN12cRLoadingBar2AIEv
 * demangled: cRLoadingBar::AI()
 * address: 0008a5b0
 * size: 168
 */

/* cRLoadingBar::AI() */

void __thiscall cRLoadingBar::AI(cRLoadingBar *this)

{
  int iVar1;
  int iVar2;
  cRSplashManager *this_00;
  float fVar3;

  iVar2 = DAT_0008a658 + 0x8a5cc;
  if (this[0x34] != (cRLoadingBar)0x0) {
    this[0x34] = (cRLoadingBar)0x0;
    iVar1 = DAT_0008a65c;
    if (this[0x35] != (cRLoadingBar)0x0) {
      if (this[0x36] != (cRLoadingBar)0x0) {
        this_00 = *(cRSplashManager **)(iVar2 + DAT_0008a65c);
        cRSplashManager::SetSplash(this_00,(char *)(this + 0x37));
        this_00[0x45] = (cRSplashManager)0x0;
      }
      if (this[0x77] != (cRLoadingBar)0x0) {
        cRSplashManager::SetBar(*(cRSplashManager **)(iVar2 + iVar1),(char *)(this + 0x78));
      }
      this[0x35] = (cRLoadingBar)0x0;
    }
    fVar3 = (float)ScriptAI(this);
    cRSplashManager::Render(fVar3);
    this[0x34] = (cRLoadingBar)0x1;
    return;
  }
  return;
}
