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
  if (*(float *)this < DAT_0006be70) {
    *(float *)this = DAT_0006be70;
  }
  return;
}
