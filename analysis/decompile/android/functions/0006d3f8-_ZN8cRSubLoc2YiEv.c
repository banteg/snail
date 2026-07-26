/*
 * mangled: _ZN8cRSubLoc2YiEv
 * demangled: cRSubLoc::Yi()
 * address: 0006d3f8
 * size: 100
 */

/* cRSubLoc::Yi() */

int __thiscall cRSubLoc::Yi(cRSubLoc *this)

{
  int iVar1;

  iVar1 = ((int)((int)this -
                (**(int **)(DAT_0006d45c + 0x6d410 + DAT_0006d460) + ((byte)this[0x34] & 7) * 0x48 +
                0x8537c)) >> 3) * 0x38e38e39;
  if (iVar1 < 0) {
    iVar1 = iVar1 + 7;
  }
  return iVar1 >> 3;
}
