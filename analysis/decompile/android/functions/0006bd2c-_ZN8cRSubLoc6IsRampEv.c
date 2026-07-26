/*
 * mangled: _ZN8cRSubLoc6IsRampEv
 * demangled: cRSubLoc::IsRamp()
 * address: 0006bd2c
 * size: 104
 */

/* cRSubLoc::IsRamp() */

bool __thiscall cRSubLoc::IsRamp(cRSubLoc *this)

{
  cRSubLoc cVar1;
  bool bVar2;

  cVar1 = this[0x30];
  bVar2 = 7 < (byte)cVar1;
  if (cVar1 != (cRSubLoc)0x8) {
    bVar2 = 1 < (byte)((char)cVar1 - 2U);
  }
  if (((((bVar2 && (cVar1 != (cRSubLoc)0x8 && (byte)((char)cVar1 - 2U) != 2)) &&
        (cVar1 != (cRSubLoc)0x9)) && (cVar1 != (cRSubLoc)0xa)) &&
      ((cVar1 != (cRSubLoc)0xb && (cVar1 != (cRSubLoc)0xc)))) &&
     ((cVar1 != (cRSubLoc)0xd && ((cVar1 != (cRSubLoc)0x5 && (cVar1 != (cRSubLoc)0x6)))))) {
    return cVar1 == (cRSubLoc)0x7;
  }
  return true;
}
