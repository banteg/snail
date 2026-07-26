/*
 * mangled: _ZN7tMatrix11RotIdentityEv
 * demangled: tMatrix::RotIdentity()
 * address: 00027750
 * size: 64
 */

/* tMatrix::RotIdentity() */

void __thiscall tMatrix::RotIdentity(tMatrix *this)

{
  undefined4 uVar1;

  uVar1 = DAT_00027790;
  *(undefined4 *)(this + 4) = DAT_00027790;
  *(undefined4 *)(this + 0x2c) = uVar1;
  *(undefined4 *)(this + 0x24) = uVar1;
  *(undefined4 *)(this + 0x20) = uVar1;
  *(undefined4 *)(this + 0x1c) = uVar1;
  *(undefined4 *)(this + 0x18) = uVar1;
  *(undefined4 *)(this + 0x10) = uVar1;
  *(undefined4 *)(this + 0xc) = uVar1;
  *(undefined4 *)(this + 8) = uVar1;
  uVar1 = DAT_00027794;
  *(undefined4 *)this = DAT_00027794;
  *(undefined4 *)(this + 0x3c) = uVar1;
  *(undefined4 *)(this + 0x28) = uVar1;
  *(undefined4 *)(this + 0x14) = uVar1;
  return;
}
