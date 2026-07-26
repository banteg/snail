/*
 * mangled: _ZN7cRFlash2AIEv
 * demangled: cRFlash::AI()
 * address: 0004a5cc
 * size: 180
 */

/* cRFlash::AI() */

void __thiscall cRFlash::AI(cRFlash *this)

{
  float fVar1;

  fVar1 = *(float *)(this + 0x20) + (*(float *)(this + 0x10) - *(float *)(this + 0x20)) * 0.145;
  *(float *)(this + 0x20) = fVar1;
  *(float *)(this + 0x14) =
       *(float *)(this + 0x14) + (*(float *)(this + 4) - *(float *)(this + 0x14)) * 0.145;
  *(float *)(this + 0x18) =
       *(float *)(this + 0x18) + (*(float *)(this + 8) - *(float *)(this + 0x18)) * 0.145;
  *(float *)(this + 0x1c) =
       *(float *)(this + 0x1c) + (*(float *)(this + 0xc) - *(float *)(this + 0x1c)) * 0.145;
  if (0.01 < fVar1) {
    OSDPrint(3,0,0,0x44200000,0x43f00000,*(uint *)this & 0xff000000,*(undefined4 *)(this + 0x14),
             *(undefined4 *)(this + 0x18),*(undefined4 *)(this + 0x1c),*(undefined4 *)(this + 0x20),
             5);
  }
  return;
}
