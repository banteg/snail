/*
 * mangled: _ZN12cRGalaxyStar2AIEv
 * demangled: cRGalaxyStar::AI()
 * address: 00058c8c
 * size: 28
 */

/* cRGalaxyStar::AI() */

void __thiscall cRGalaxyStar::AI(cRGalaxyStar *this)

{
  *(float *)(this + 0x18) =
       *(float *)(this + 0x18) + (*(float *)(this + 0x1c) - *(float *)(this + 0x18)) * DAT_00058ca8;
  return;
}
