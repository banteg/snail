/*
 * mangled: _ZN9cROverlay2AIEv
 * demangled: cROverlay::AI()
 * address: 0004b250
 * size: 144
 */

/* cROverlay::AI() */

void __thiscall cROverlay::AI(cROverlay *this)

{
  tMatrix *this_00;
  float fVar1;

  fVar1 = *(float *)(this + 300) + *(float *)(this + 0x130);
  *(float *)(this + 300) = fVar1;
  if (6.2831855 < fVar1) {
    *(float *)(this + 300) = fVar1 - 6.2831855;
  }
  else if (fVar1 < 0.0) {
    *(float *)(this + 300) = fVar1 + 6.2831855;
  }
  this_00 = (tMatrix *)(this + 0x2c);
  fVar1 = (float)tMatrix::Identity(this_00);
  tMatrix::RotLocalZ(this_00,fVar1);
  *(undefined4 *)(this + 0xa0) = *(undefined4 *)this_00;
  *(undefined4 *)(this + 0xa4) = *(undefined4 *)(this + 0x30);
  *(undefined4 *)(this + 0xa8) = *(undefined4 *)(this + 0x34);
  *(undefined4 *)(this + 0xac) = *(undefined4 *)(this + 0x38);
  *(undefined4 *)(this + 0xb0) = *(undefined4 *)(this + 0x3c);
  *(undefined4 *)(this + 0xb4) = *(undefined4 *)(this + 0x40);
  *(undefined4 *)(this + 0xb8) = *(undefined4 *)(this + 0x44);
  *(undefined4 *)(this + 0xbc) = *(undefined4 *)(this + 0x48);
  *(undefined4 *)(this + 0xc0) = *(undefined4 *)(this + 0x4c);
  *(undefined4 *)(this + 0xc4) = *(undefined4 *)(this + 0x50);
  *(undefined4 *)(this + 200) = *(undefined4 *)(this + 0x54);
  *(undefined4 *)(this + 0xcc) = *(undefined4 *)(this + 0x58);
  *(undefined4 *)(this + 0xd0) = *(undefined4 *)(this + 0x5c);
  *(undefined4 *)(this + 0xd4) = *(undefined4 *)(this + 0x60);
  *(undefined4 *)(this + 0xd8) = *(undefined4 *)(this + 100);
  *(undefined4 *)(this + 0xdc) = *(undefined4 *)(this + 0x68);
  tMatrix::Invert((tMatrix *)(this + 0xe8),this_00);
  return;
}
