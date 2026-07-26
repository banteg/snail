/*
 * mangled: _ZN8cRBorder2X0Ev
 * demangled: cRBorder::X0()
 * address: 0005bec8
 * size: 80
 */

/* cRBorder::X0() */

float __thiscall cRBorder::X0(cRBorder *this)

{
  if (*(int *)(this + 0x254) != 2) {
    return *(float *)(this + 0x6ec) - *(float *)(this + 0x20c);
  }
  return (*(float *)(this + 600) + 320.0 + *(float *)(this + 0x23c) * -0.5) -
         *(float *)(this + 0x20c);
}
