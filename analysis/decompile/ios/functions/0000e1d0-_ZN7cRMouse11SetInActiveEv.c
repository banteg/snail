/*
 * mangled: _ZN7cRMouse11SetInActiveEv
 * demangled: cRMouse::SetInActive()
 * address: 0000e1d0
 * size: 36
 */

/* cRMouse::SetInActive() */

void __thiscall cRMouse::SetInActive(cRMouse *this)

{
  if (*this != (cRMouse)0x0) {
    *(undefined4 *)(this + 4) = *(undefined4 *)(this + 0xc);
    *(undefined4 *)(this + 8) = *(undefined4 *)(this + 0x10);
  }
  *this = (cRMouse)0x0;
  return;
}
