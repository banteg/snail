/*
 * mangled: _ZN8cRSubLoc2YiEv
 * demangled: cRSubLoc::Yi()
 * address: 00017d08
 * size: 80
 */

/* cRSubLoc::Yi() */

int __thiscall cRSubLoc::Yi(cRSubLoc *this)

{
  int iVar1;

  iVar1 = ((int)((int)this - (((byte)this[0x32] & 7) * 0x44 + 0x85fd0 + *(int *)PTR__Game_001b60b8))
          >> 2) * -0xf0f0f0f;
  if (iVar1 < 0) {
    iVar1 = iVar1 + 7;
  }
  return iVar1 >> 3;
}
