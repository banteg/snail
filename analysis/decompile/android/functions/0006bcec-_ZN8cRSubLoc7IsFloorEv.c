/*
 * mangled: _ZN8cRSubLoc7IsFloorEv
 * demangled: cRSubLoc::IsFloor()
 * address: 0006bcec
 * size: 64
 */

/* cRSubLoc::IsFloor() */

bool __thiscall cRSubLoc::IsFloor(cRSubLoc *this)

{
  cRSubLoc cVar1;

  cVar1 = this[0x30];
  if ((((cVar1 != (cRSubLoc)0x1 && cVar1 != (cRSubLoc)0x14) && (cVar1 != (cRSubLoc)0x15)) &&
      (cVar1 != (cRSubLoc)0x21)) && (cVar1 != (cRSubLoc)0x22)) {
    return cVar1 == (cRSubLoc)0x1b;
  }
  return true;
}
