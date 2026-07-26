/*
 * mangled: _ZN7cRMouse8ClickOffEv
 * demangled: cRMouse::ClickOff()
 * address: 0000e210
 * size: 52
 */

/* cRMouse::ClickOff() */

void __thiscall cRMouse::ClickOff(cRMouse *this)

{
  this[0x16] = (cRMouse)0x0;
  this[0x15] = (cRMouse)0x0;
  if (*(int *)(PTR__gConfig_001b60d4 + 8) == 1) {
    this[0x17] = (cRMouse)((byte)this[0x17] ^ 1);
  }
  else {
    this[0x17] = (cRMouse)0x1;
  }
  return;
}
