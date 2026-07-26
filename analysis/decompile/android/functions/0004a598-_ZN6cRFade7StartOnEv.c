/*
 * mangled: _ZN6cRFade7StartOnEv
 * demangled: cRFade::StartOn()
 * address: 0004a598
 * size: 20
 */

/* cRFade::StartOn() */

void __thiscall cRFade::StartOn(cRFade *this)

{
  *(undefined4 *)(this + 4) = 0x3f800000;
  *(undefined4 *)this = 1;
  AI();
  return;
}
