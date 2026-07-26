/*
 * mangled: _ZN11cRHighScore14SetExitNextPosEv
 * demangled: cRHighScore::SetExitNextPos()
 * address: 0003d574
 * size: 172
 */

/* cRHighScore::SetExitNextPos() */

void __thiscall cRHighScore::SetExitNextPos(cRHighScore *this)

{
  int iVar1;

  Rstrcpy((char *)(*(int *)(this + 0x20) + 0x2c4),"Challenge Scores");
  cRBorder::RePosition(*(cRBorder **)(this + 0x20));
  cRBorder::SetRight(*(cRBorder **)(this + 0x20),*(cRBorder **)(this + 0x1c));
  cRBorderManager::CentreRow
            ((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14),*(cRBorder **)(this + 0x1c),
             false,100.0);
  iVar1 = *(int *)(this + 8);
  if (iVar1 == 1) {
    Rstrcpy((char *)(*(int *)(this + 0x20) + 0x2c4),"Pro Scores");
    return;
  }
  if (iVar1 != 3) {
    if (iVar1 != 0) {
      return;
    }
    Rstrcpy((char *)(*(int *)(this + 0x20) + 0x2c4),"Challenge Scores");
    return;
  }
  Rstrcpy((char *)(*(int *)(this + 0x20) + 0x2c4),"Postal Scores");
  return;
}
