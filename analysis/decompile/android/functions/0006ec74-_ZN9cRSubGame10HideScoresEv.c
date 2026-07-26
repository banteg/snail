/*
 * mangled: _ZN9cRSubGame10HideScoresEv
 * demangled: cRSubGame::HideScores()
 * address: 0006ec74
 * size: 52
 */

/* cRSubGame::HideScores() */

void __thiscall cRSubGame::HideScores(cRSubGame *this)

{
  if (*(cRBorder **)(this + 0x8c5c) != (cRBorder *)0x0) {
    cRBorder::HideInit(*(cRBorder **)(this + 0x8c5c));
  }
  if (*(cRBorder **)(this + 0x8c58) == (cRBorder *)0x0) {
    return;
  }
  cRBorder::HideInit(*(cRBorder **)(this + 0x8c58));
  return;
}
