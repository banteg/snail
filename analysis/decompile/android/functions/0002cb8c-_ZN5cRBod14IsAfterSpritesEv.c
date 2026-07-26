/*
 * mangled: _ZN5cRBod14IsAfterSpritesEv
 * demangled: cRBod::IsAfterSprites()
 * address: 0002cb8c
 * size: 12
 */

/* cRBod::IsAfterSprites() */

uint __thiscall cRBod::IsAfterSprites(cRBod *this)

{
  return (*(uint *)(this + 4) & 0xff) >> 7;
}
