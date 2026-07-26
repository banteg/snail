/*
 * mangled: _ZN7cRMouse11SetInActiveEv
 * demangled: cRMouse::SetInActive()
 * address: 00030da8
 * size: 36
 */

/* cRMouse::SetInActive() */

void __thiscall cRMouse::SetInActive(cRMouse *this)

{
  cRMouse cVar1;
  undefined4 in_s15;

  cVar1 = *this;
  if (cVar1 != (cRMouse)0x0) {
    in_s15 = *(undefined4 *)(this + 0xc);
  }
  *this = (cRMouse)0x0;
  if (cVar1 != (cRMouse)0x0) {
    *(undefined4 *)(this + 4) = in_s15;
    *(undefined4 *)(this + 8) = *(undefined4 *)(this + 0x10);
  }
  return;
}
