/*
 * mangled: _ZN7cRMouse11ClickScreenEbff
 * demangled: cRMouse::ClickScreen(bool, float, float)
 * address: 00030fe0
 * size: 36
 */

/* cRMouse::ClickScreen(bool, float, float) */

void cRMouse::ClickScreen(bool param_1,float param_2,float param_3)

{
  uint uVar1;
  undefined1 in_r1;
  undefined4 in_r2;
  undefined4 in_r3;

  uVar1 = (uint)param_1;
  *(undefined1 *)(uVar1 + 0x19) = in_r1;
  *(undefined4 *)(uVar1 + 0x1c) = in_r2;
  *(undefined4 *)(uVar1 + 0x20) = in_r3;
  *(undefined4 *)(uVar1 + 0x30) = 0;
  RShellSetMouse(0,param_2,param_3);
  return;
}
