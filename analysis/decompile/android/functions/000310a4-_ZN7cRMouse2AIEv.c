/*
 * mangled: _ZN7cRMouse2AIEv
 * demangled: cRMouse::AI()
 * address: 000310a4
 * size: 348
 */

/* cRMouse::AI() */

void __thiscall cRMouse::AI(cRMouse *this)

{
  cRMouse cVar1;
  int iVar2;
  undefined8 uVar3;

  if (this[0x16] == (cRMouse)0x0) {
    iVar2 = *(int *)(this + 0x30) + 1;
    *(int *)(this + 0x30) = iVar2;
  }
  else {
    *(undefined4 *)(this + 0x30) = 0;
    RShellInputRegisterMouseClickOnly();
    iVar2 = *(int *)(this + 0x30);
  }
  if (iVar2 < 0) {
    *(undefined4 *)(this + 0x30) = 0;
  }
  if (this[0x18] == (cRMouse)0x0) {
    if (this[0x19] == (cRMouse)0x0) {
      uVar3 = RShellInputRegisterMouse
                        (0,0,0,0x280,0x1e0,(int)*(float *)(this + 0x1c),(int)*(float *)(this + 0x20)
                         ,0,false,false,false,true,false);
      cVar1 = this[0x24];
    }
    else {
      uVar3 = RShellInputRegisterMouse
                        (0,0,0,0x280,0x1e0,(int)*(float *)(this + 0x1c),(int)*(float *)(this + 0x20)
                         ,0,true,false,false,true,false);
      cVar1 = this[0x24];
    }
    if (cVar1 == (cRMouse)0x0) {
      RShellInputRegisterMouseExtra((float)uVar3,(float)((ulonglong)uVar3 >> 0x20));
      goto LAB_00031154;
    }
  }
  else {
    uVar3 = RShellInputRegisterMouseClickOnly();
    if (this[0x24] == (cRMouse)0x0) goto LAB_00031154;
  }
  RShellInputRegisterMouseExtra((float)uVar3,(float)((ulonglong)uVar3 >> 0x20));
LAB_00031154:
  this[0x18] = (cRMouse)0x0;
  this[0x19] = (cRMouse)0x0;
  this[0x24] = (cRMouse)0x0;
  return;
}
