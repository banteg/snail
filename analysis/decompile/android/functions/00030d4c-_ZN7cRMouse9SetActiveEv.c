/*
 * mangled: _ZN7cRMouse9SetActiveEv
 * demangled: cRMouse::SetActive()
 * address: 00030d4c
 * size: 92
 */

/* cRMouse::SetActive() */

void __thiscall cRMouse::SetActive(cRMouse *this)

{
  if (*this == (cRMouse)0x0) {
    *(float *)(this + 0xc) = *(float *)(this + 4);
    *(float *)(this + 0x10) = *(float *)(this + 8);
    MouseSet(0,(int)*(float *)(this + 4),(int)*(float *)(this + 8));
    this[0x18] = (cRMouse)0x0;
    this[0x24] = (cRMouse)0x0;
    this[0x14] = (cRMouse)0x1;
    this[0x19] = (cRMouse)0x0;
  }
  *this = (cRMouse)0x1;
  return;
}
