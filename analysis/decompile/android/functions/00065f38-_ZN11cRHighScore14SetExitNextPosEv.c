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
  int iVar2;
  char *pcVar3;
  float fVar4;

  iVar2 = DAT_00065ffc + 0x65f50;
  pcVar3 = (char *)(iVar2 + DAT_00066000);
  Rstrcpy((char *)(*(int *)(this + 0x20) + 0x2c4),pcVar3);
  cRBorder::RePosition(*(cRBorder **)(this + 0x20));
  fVar4 = (float)cRBorder::SetRight(*(cRBorder **)(this + 0x20),*(cRBorder **)(this + 0x1c));
  cRBorderManager::CentreRow
            ((cRBorderManager *)(**(int **)(iVar2 + DAT_00066004) + 0xd14),
             *(cRBorder **)(this + 0x1c),false,fVar4);
  iVar1 = *(int *)(this + 8);
  if (iVar1 == 1) {
    Rstrcpy((char *)(*(int *)(this + 0x20) + 0x2c4),(char *)(iVar2 + DAT_0006600c));
    return;
  }
  if (iVar1 != 3) {
    if (iVar1 != 0) {
      return;
    }
    Rstrcpy((char *)(*(int *)(this + 0x20) + 0x2c4),pcVar3);
    return;
  }
  Rstrcpy((char *)(*(int *)(this + 0x20) + 0x2c4),(char *)(iVar2 + DAT_00066008));
  return;
}
