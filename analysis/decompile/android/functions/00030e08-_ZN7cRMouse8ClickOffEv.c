/*
 * mangled: _ZN7cRMouse8ClickOffEv
 * demangled: cRMouse::ClickOff()
 * address: 00030e08
 * size: 60
 */

/* cRMouse::ClickOff() */

void __thiscall cRMouse::ClickOff(cRMouse *this)

{
  this[0x15] = (cRMouse)0x0;
  this[0x16] = (cRMouse)0x0;
  if (gConfig._8_4_ == 1) {
    this[0x17] = (cRMouse)((byte)this[0x17] ^ 1);
  }
  else {
    this[0x17] = (cRMouse)0x1;
  }
  return;
}
