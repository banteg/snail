/*
 * mangled: _ZN8cRBorder2X1Ev
 * demangled: cRBorder::X1()
 * address: 0005bf20
 * size: 88
 */

/* cRBorder::X1() */

float __thiscall cRBorder::X1(cRBorder *this)

{
  if (*(int *)(this + 0x254) != 2) {
    return *(float *)(this + 0x6ec) + *(float *)(this + 0x23c) + *(float *)(this + 0x20c);
  }
  return DAT_0005bf78 + *(float *)(this + 600) + DAT_0005bf7c * *(float *)(this + 0x23c) +
         *(float *)(this + 0x20c);
}
