/*
 * mangled: _ZN9cRLogoRow2AIEv
 * demangled: cRLogoRow::AI()
 * address: 0006652c
 * size: 196
 */

/* cRLogoRow::AI() */

void __thiscall cRLogoRow::AI(cRLogoRow *this)

{
  float fVar1;

  *(float *)(this + 0x5c) = *(float *)(this + 0x5c) + *(float *)(this + 0x74);
  *(float *)(this + 0x60) = *(float *)(this + 0x60) + *(float *)(this + 0x78);
  fVar1 = *(float *)(this + 100) + *(float *)(this + 0x7c);
  *(float *)(this + 100) = fVar1;
  if (fVar1 <= 7.0) {
    tColourSmall::Alpha((tColourSmall *)(this + 0x28),0.999);
  }
  else {
    tColourSmall::Alpha((tColourSmall *)(this + 0x28),(1.0 - (fVar1 - 7.0) / 3.0) * 0.999);
  }
  if ((*(float *)(this + 100) <= 10.0) && (-1.0 <= *(float *)(this + 100))) {
    *(uint *)(this + 4) = *(uint *)(this + 4) | 0x20;
    return;
  }
  *(uint *)(this + 4) = *(uint *)(this + 4) & 0xffffffdf;
  return;
}
