/*
 * mangled: _ZN6cRLogo2AIEv
 * demangled: cRLogo::AI()
 * address: 00068ea4
 * size: 292
 */

/* cRLogo::AI() */

void __thiscall cRLogo::AI(cRLogo *this)

{
  int iVar1;
  float fVar2;

  iVar1 = *(int *)(Game + 0x24);
  if (iVar1 == 0) {
    if (((*(uint *)(*(int *)(Game + 0x224) + 0x30) & 0x4000) == 0) &&
       (iVar1 = RShellInkey(), iVar1 != 0xb)) {
      iVar1 = *(int *)(Game + 0x24);
    }
    else {
      cRFade::Start((cRFade *)(Game + 0x24),(_func_void *)0x0);
      *this = (cRLogo)0x1;
      iVar1 = *(int *)(Game + 0x24);
    }
  }
  if ((iVar1 == 4) && (*this != (cRLogo)0x0)) {
    UnInit(this);
  }
  if (*(int *)(this + 0xc) == 0) {
    fVar2 = 0.0;
    *(undefined4 *)(this + 4) = 0;
    *(undefined4 *)(this + 0xc) = 1;
    if (*(float *)(this + 0x14) != 0.0) {
      fVar2 = 1.0 / (*(float *)(this + 0x14) * 60.0);
    }
    *(float *)(this + 8) = fVar2;
    return;
  }
  if (*(int *)(this + 0xc) != 1) {
    return;
  }
  fVar2 = *(float *)(this + 4);
  *(float *)(this + 4) = fVar2 + *(float *)(this + 8);
  if (fVar2 + *(float *)(this + 8) <= 1.0) {
    return;
  }
  cRFade::Start((cRFade *)(Game + 0x24),(_func_void *)0x0);
  *this = (cRLogo)0x1;
  *(int *)(this + 0xc) = *(int *)(this + 0xc) + 1;
  return;
}
