/*
 * mangled: _ZN9cRSubGame10HideScoresEv
 * demangled: cRSubGame::HideScores()
 * address: 00017ed0
 * size: 48
 */

/* cRSubGame::HideScores() */

void __thiscall cRSubGame::HideScores(cRSubGame *this)

{
  if (*(cRBorder **)(this + 0x85e4) != (cRBorder *)0x0) {
    cRBorder::HideInit(*(cRBorder **)(this + 0x85e4));
  }
  if (*(cRBorder **)(this + 0x85e0) == (cRBorder *)0x0) {
    return;
  }
  cRBorder::HideInit(*(cRBorder **)(this + 0x85e0));
  return;
}
