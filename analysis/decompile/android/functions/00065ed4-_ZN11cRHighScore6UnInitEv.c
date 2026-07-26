/*
 * mangled: _ZN11cRHighScore6UnInitEv
 * demangled: cRHighScore::UnInit()
 * address: 00065ed4
 * size: 88
 */

/* cRHighScore::UnInit() */

void __thiscall cRHighScore::UnInit(cRHighScore *this)

{
  int iVar1;
  float fVar2;

  gConfig._168_4_ = *(undefined4 *)(this + 8);
  fVar2 = (float)cRBorderManager::KillBorders((cRBorderManager *)(Game + 0xd14));
  iVar1 = Game;
  *(undefined4 *)(Game + 0x2c4) = 0;
  *(undefined1 *)(iVar1 + 0x2c1) = 0;
  cRBackdrop::SetZoom((cRBackdrop *)(iVar1 + 0x4d2e0),fVar2);
  return;
}
