/*
 * mangled: _ZN7cRMouse9SetActiveEv
 * demangled: cRMouse::SetActive()
 * address: 0000e3d4
 * size: 156
 */

/* cRMouse::SetActive() */

void __thiscall cRMouse::SetActive(cRMouse *this)

{
  undefined *puVar1;
  int iVar2;
  uint in_fpscr;
  undefined4 uVar3;
  undefined4 uVar4;

  if (*this == (cRMouse)0x0) {
    *(float *)(this + 0xc) = *(float *)(this + 4);
    _gMouseOldX = (int)*(float *)(this + 4);
    _gMouseOldY = (int)*(float *)(this + 8);
    *(float *)(this + 0x10) = *(float *)(this + 8);
    puVar1 = PTR__Game_001b60b8;
    uVar3 = VectorSignedToFloat(_gMouseOldX,(byte)(in_fpscr >> 0x16) & 3);
    uVar4 = VectorSignedToFloat(_gMouseOldY,(byte)(in_fpscr >> 0x16) & 3);
    _gmX = uVar3;
    _gmY = uVar4;
    *(undefined4 *)(*(int *)(*(int *)PTR__Game_001b60b8 + 0x224) + 0x54) = uVar3;
    *(undefined4 *)(*(int *)(*(int *)puVar1 + 0x224) + 0x58) = uVar4;
    *(undefined4 *)(*(int *)puVar1 + 0x234) = uVar3;
    iVar2 = *(int *)puVar1;
    this[0x24] = (cRMouse)0x0;
    this[0x19] = (cRMouse)0x0;
    this[0x18] = (cRMouse)0x0;
    *(undefined4 *)(iVar2 + 0x238) = uVar4;
    this[0x14] = (cRMouse)0x1;
  }
  *this = (cRMouse)0x1;
  return;
}
