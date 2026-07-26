/*
 * mangled: _ZN8cRBorder6XRightEv
 * demangled: cRBorder::XRight()
 * address: 0005bfd8
 * size: 88
 */

/* cRBorder::XRight() */

float __thiscall cRBorder::XRight(cRBorder *this)

{
  if (*(int *)(this + 0x254) != 2) {
    return *(float *)(this + 0x6ec) + *(float *)(this + 0x23c) + *(float *)(this + 0x20c);
  }
  return DAT_0005c030 + *(float *)(this + 600) + DAT_0005c034 * *(float *)(this + 0x23c) +
         *(float *)(this + 0x20c);
}
