/*
 * mangled: _ZN10cRSubHover3EndEv
 * demangled: cRSubHover::End()
 * address: 0006be4c
 * size: 36
 */

/* cRSubHover::End() */

void __thiscall cRSubHover::End(cRSubHover *this)

{
  if (*(int *)(this + 0xc) != 1) {
    return;
  }
  if (*(float *)this < 0.94) {
    *(undefined4 *)this = 0x3f70a3d7;
  }
  return;
}
