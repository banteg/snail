/*
 * mangled: _ZN6cRFade6FadeInEv
 * demangled: cRFade::FadeIn()
 * address: 0003e0b0
 * size: 48
 */

/* cRFade::FadeIn() */

void __thiscall cRFade::FadeIn(cRFade *this)

{
  undefined4 uVar1;

  uVar1 = DAT_0003e0e0;
  if (*(int *)this != 4) {
    return;
  }
  *(undefined4 *)this = 5;
  *(undefined4 *)(this + 8) = uVar1;
  uVar1 = DAT_0003e0e4;
  *(undefined4 *)(this + 0x14) = 3;
  *(undefined4 *)(this + 4) = uVar1;
  return;
}
