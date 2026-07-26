/*
 * mangled: _ZN7cRMouse11ClickiPhoneEbff
 * demangled: cRMouse::ClickiPhone(bool, float, float)
 * address: 0000e5dc
 * size: 260
 */

/* cRMouse::ClickiPhone(bool, float, float) */

void __thiscall cRMouse::ClickiPhone(cRMouse *this,bool param_1,float param_2,float param_3)

{
  undefined *puVar1;
  float fVar2;
  float in_s13;
  float fVar3;
  int iVar4;

  puVar1 = PTR__Game_001b60b8;
  fVar2 = 0.0;
  *(undefined4 *)(this + 0x30) = 0;
  fVar3 = (param_3 * 460.0) / 470.0 + 10.0;
  iVar4 = (int)*(float *)(*(int *)puVar1 + 0x3c);
  if (iVar4 == 0x5a) {
    fVar2 = fVar3 * 640.0;
    fVar3 = (param_2 * 480.0) / 640.0;
    param_2 = fVar2 / -480.0 + 639.0;
    goto LAB_0000e64c;
  }
  if (iVar4 < 0x5b) {
    if (iVar4 == 0) goto LAB_0000e64c;
  }
  else {
    if (iVar4 == 0xb4) {
      fVar3 = 479.0 - fVar3;
      param_2 = 639.0 - param_2;
      goto LAB_0000e64c;
    }
    fVar2 = 3.78351e-43;
    if (iVar4 == 0x10e) {
      fVar2 = fVar3 * 640.0;
      fVar3 = (param_2 * 480.0) / -640.0 + 479.0;
      param_2 = fVar2 / 480.0;
      goto LAB_0000e64c;
    }
  }
  param_2 = in_s13;
  fVar3 = fVar2;
LAB_0000e64c:
  this[0x19] = (cRMouse)param_1;
  *(float *)(this + 0x1c) = param_2;
  *(float *)(this + 0x20) = fVar3;
  RShellSetMouse(0,param_2,fVar3);
  return;
}
