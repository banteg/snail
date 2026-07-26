/*
 * mangled: _ZN7cRMouse9ClickOnlyEff
 * demangled: cRMouse::ClickOnly(float, float)
 * address: 0000e484
 * size: 300
 */

/* cRMouse::ClickOnly(float, float) */

void __thiscall cRMouse::ClickOnly(cRMouse *this,float param_1,float param_2)

{
  undefined4 in_s12;
  float fVar1;
  int iVar2;

  *(undefined4 *)(this + 0x30) = 0;
  fVar1 = (param_2 * 460.0) / 470.0 + 10.0;
  iVar2 = (int)*(float *)(*(int *)PTR__Game_001b60b8 + 0x3c);
  if (iVar2 == 0x5a) {
    this[0x24] = (cRMouse)0x1;
    *(float *)(this + 0x28) = (fVar1 * 640.0) / -480.0 + 639.0;
    *(float *)(this + 0x2c) = (param_1 * 480.0) / 640.0;
    return;
  }
  if (iVar2 < 0x5b) {
    if (iVar2 == 0) {
      this[0x24] = (cRMouse)0x1;
      *(float *)(this + 0x28) = param_1;
      *(float *)(this + 0x2c) = fVar1;
      return;
    }
  }
  else {
    if (iVar2 == 0xb4) {
      this[0x24] = (cRMouse)0x1;
      *(float *)(this + 0x28) = 639.0 - param_1;
      *(float *)(this + 0x2c) = 479.0 - fVar1;
      return;
    }
    param_2 = 3.78351e-43;
    if (iVar2 == 0x10e) {
      this[0x24] = (cRMouse)0x1;
      *(float *)(this + 0x28) = (fVar1 * 640.0) / 480.0;
      *(float *)(this + 0x2c) = (param_1 * 480.0) / -640.0 + 479.0;
      return;
    }
  }
  this[0x24] = (cRMouse)0x1;
  *(undefined4 *)(this + 0x28) = in_s12;
  *(float *)(this + 0x2c) = param_2;
  return;
}
