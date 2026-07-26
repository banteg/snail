/*
 * mangled: _ZN11cRHighScore14SetExitNextPosEv
 * demangled: cRHighScore::SetExitNextPos()
 * address: 00065f38
 * size: 196
 */

/* cRHighScore::SetExitNextPos() */

void __thiscall cRHighScore::SetExitNextPos(cRHighScore *this)

{
  int iVar1;
  float fVar2;

  Rstrcpy((char *)(*(int *)(this + 0x20) + 0x2c4),"Challenge Scores");
  cRBorder::RePosition(*(cRBorder **)(this + 0x20));
  fVar2 = (float)cRBorder::SetRight(*(cRBorder **)(this + 0x20),*(cRBorder **)(this + 0x1c));
  cRBorderManager::CentreRow
            ((cRBorderManager *)(Game + 0xd14),*(cRBorder **)(this + 0x1c),false,fVar2);
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
