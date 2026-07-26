/*
 * mangled: _ZN8cRGalaxy6BoxOffEv
 * demangled: cRGalaxy::BoxOff()
 * address: 0006867c
 * size: 80
 */

/* cRGalaxy::BoxOff() */

void __thiscall cRGalaxy::BoxOff(cRGalaxy *this)

{
  *(undefined4 *)(this + 4) = 0;
  *(undefined4 *)(this + 0x8e34) = 0xffffffff;
  cRBorder::HideInit(*(cRBorder **)(this + 0x8e40));
  cRBorder::HideInit(*(cRBorder **)(this + 0x8e44));
  cRBorder::HideInit(*(cRBorder **)(this + 0x8e48));
  cRBorder::HideInit(*(cRBorder **)(this + 0x8e4c));
  cRBorder::HideInit(*(cRBorder **)(this + 0x8e50));
  cRBorder::HideInit(*(cRBorder **)(this + 0x8e54));
  return;
}
