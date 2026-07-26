/*
 * mangled: _ZN8cRSubLoc7IsSlideEv
 * demangled: cRSubLoc::IsSlide()
 * address: 0006bdcc
 * size: 80
 */

/* cRSubLoc::IsSlide() */

bool __thiscall cRSubLoc::IsSlide(cRSubLoc *this)

{
  cRSubLoc cVar1;

  cVar1 = this[0x30];
  if ((((cVar1 != (cRSubLoc)0xf && cVar1 != (cRSubLoc)0x17) && (cVar1 != (cRSubLoc)0x18)) &&
      (cVar1 != (cRSubLoc)0x19)) &&
     (((cVar1 != (cRSubLoc)0x1a && (cVar1 != (cRSubLoc)0x10)) && (cVar1 != (cRSubLoc)0x12)))) {
    return cVar1 == (cRSubLoc)0x13;
  }
  return true;
}
