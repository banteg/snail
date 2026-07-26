/*
 * mangled: _ZN7cRMouse11ClickScreenEbff
 * demangled: cRMouse::ClickScreen(bool, float, float)
 * address: 0000e248
 * size: 48
 */

/* cRMouse::ClickScreen(bool, float, float) */

void __thiscall cRMouse::ClickScreen(cRMouse *this,bool param_1,float param_2,float param_3)

{
  *(undefined4 *)(this + 0x30) = 0;
  this[0x19] = (cRMouse)param_1;
  *(float *)(this + 0x1c) = param_2;
  *(float *)(this + 0x20) = param_3;
  RShellSetMouse(0,param_2,param_3);
  return;
}
