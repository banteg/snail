/*
 * mangled: _ZN6cRFade6FadeInEv
 * demangled: cRFade::FadeIn()
 * address: 0003e0b0
 * size: 48
 */

/* cRFade::FadeIn() */

void __thiscall cRFade::FadeIn(cRFade *this)

{
  if (*(int *)this != 4) {
    return;
  }
  *(undefined4 *)this = 5;
  *(undefined4 *)(this + 8) = 0;
  *(undefined4 *)(this + 0x14) = 3;
  *(undefined4 *)(this + 4) = 0x3f800000;
  return;
}
