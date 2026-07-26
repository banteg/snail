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
  float fVar2;
  float fVar3;

  fVar2 = DAT_0004a680;
  fVar3 = *(float *)(this + 0x20) +
          (*(float *)(this + 0x10) - *(float *)(this + 0x20)) * DAT_0004a680;
  fVar1 = (*(float *)(this + 4) - *(float *)(this + 0x14)) * DAT_0004a680;
  *(float *)(this + 0x20) = fVar3;
  *(float *)(this + 0x14) = *(float *)(this + 0x14) + fVar1;
  fVar1 = DAT_0004a684;
  *(float *)(this + 0x18) =
       *(float *)(this + 0x18) + (*(float *)(this + 8) - *(float *)(this + 0x18)) * fVar2;
  *(float *)(this + 0x1c) =
       *(float *)(this + 0x1c) + (*(float *)(this + 0xc) - *(float *)(this + 0x1c)) * fVar2;
  if (fVar1 < fVar3) {
    OSDPrint(3,0,0,0x44200000,DAT_0004a688,*(uint *)this & 0xff000000,*(undefined4 *)(this + 0x14),
             *(undefined4 *)(this + 0x18),*(undefined4 *)(this + 0x1c),*(undefined4 *)(this + 0x20),
             5);
  }
  return;
}
