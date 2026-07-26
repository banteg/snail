/*
 * mangled: _ZN8cRBorder5XLeftEv
 * demangled: cRBorder::XLeft()
 * address: 0005bf80
 * size: 80
 */

/* cRBorder::XLeft() */

float __thiscall cRBorder::XLeft(cRBorder *this)

{
  if (*(int *)(this + 0x254) != 2) {
    return *(float *)(this + 0x6ec) - *(float *)(this + 0x20c);
  }
  return (DAT_0005bfd0 + *(float *)(this + 600) + DAT_0005bfd4 * *(float *)(this + 0x23c)) -
         *(float *)(this + 0x20c);
}
