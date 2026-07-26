/*
 * mangled: _ZN7cRMouse8ClickOffEv
 * demangled: cRMouse::ClickOff()
 * address: 00030e08
 * size: 60
 */

/* cRMouse::ClickOff() */

void __thiscall cRMouse::ClickOff(cRMouse *this)

{
  int iVar1;

  iVar1 = DAT_00030e44;
  this[0x15] = (cRMouse)0x0;
  this[0x16] = (cRMouse)0x0;
  if (*(int *)(*(int *)(iVar1 + 0x30e20 + DAT_00030e48) + 8) == 1) {
    this[0x17] = (cRMouse)((byte)this[0x17] ^ 1);
  }
  else {
    this[0x17] = (cRMouse)0x1;
  }
  return;
}
