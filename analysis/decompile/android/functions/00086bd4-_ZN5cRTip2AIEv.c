/*
 * mangled: _ZN5cRTip2AIEv
 * demangled: cRTip::AI()
 * address: 00086bd4
 * size: 296
 */

/* cRTip::AI() */

void __thiscall cRTip::AI(cRTip *this)

{
  int iVar1;
  float fVar2;

  if (*(char *)(Game + 0x718b9) != '\0') {
    cRBorder::HideInit(*(cRBorder **)(this + 0xc));
    return;
  }
  cRBorder::UnHideInit(*(cRBorder **)(this + 0xc));
  iVar1 = *(int *)(this + 0x10);
  if ((iVar1 != 0) && ((*(uint *)(iVar1 + 0x194) & 0x20) != 0)) {
    *(uint *)(iVar1 + 0x194) = *(uint *)(iVar1 + 0x194) & 0xffffffdf;
    *(undefined4 *)(Game + 0x15c) = *(undefined4 *)(this + 4);
    UnInit(this);
    cRBorderManager::UnHideBorders((cRBorderManager *)(Game + 0xd14));
    *(undefined4 *)this = 0;
    return;
  }
  iVar1 = *(int *)(this + 0x14);
  if ((iVar1 != 0) && ((*(uint *)(iVar1 + 0x194) & 0x20) != 0)) {
    *(uint *)(iVar1 + 0x194) = *(uint *)(iVar1 + 0x194) & 0xffffffdf;
    *(undefined4 *)(Game + 0x15c) = *(undefined4 *)(this + 4);
    UnInit(this);
    cRBorderManager::UnHideBorders((cRBorderManager *)(Game + 0xd14));
    *(undefined4 *)this = 0;
    return;
  }
  if ((**(uint **)(this + 8) & 2) == 0) {
    return;
  }
  fVar2 = *(float *)(this + 0x18);
  *(float *)(this + 0x18) = fVar2 + *(float *)(this + 0x1c);
  if (fVar2 + *(float *)(this + 0x1c) <= 1.0) {
    return;
  }
  UnInit(this);
  *(undefined4 *)this = 0;
  return;
}
