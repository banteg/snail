/*
 * mangled: _ZN5cRBod14IsAfterSpritesEv
 * demangled: cRBod::IsAfterSprites()
 * address: 00011914
 * size: 16
 */

/* cRBod::IsAfterSprites() */

uint __thiscall cRBod::IsAfterSprites(cRBod *this)

{
  return *(uint *)(this + 4) >> 7 & 1;
}
