/*
 * mangled: _ZN8cRSubLoc7IsEmptyEv
 * demangled: cRSubLoc::IsEmpty()
 * address: 0006bd94
 * size: 56
 */

/* cRSubLoc::IsEmpty() */

bool __thiscall cRSubLoc::IsEmpty(cRSubLoc *this)

{
  cRSubLoc cVar1;

  cVar1 = this[0x30];
  if (((cVar1 != (cRSubLoc)0x0 && cVar1 != (cRSubLoc)0x1c) && (cVar1 != (cRSubLoc)0x23)) &&
     (cVar1 != (cRSubLoc)0xe)) {
    return cVar1 == (cRSubLoc)0x1d;
  }
  return true;
}
