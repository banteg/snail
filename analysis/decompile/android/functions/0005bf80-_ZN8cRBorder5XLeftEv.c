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
  return (*(float *)(this + 600) + 320.0 + *(float *)(this + 0x23c) * -0.5) -
         *(float *)(this + 0x20c);
}
