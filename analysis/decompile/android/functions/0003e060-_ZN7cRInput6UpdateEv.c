/*
 * mangled: _ZN7cRInput6UpdateEv
 * demangled: cRInput::Update()
 * address: 0003e060
 * size: 52
 */

/* cRInput::Update() */

void __thiscall cRInput::Update(cRInput *this)

{
  uint uVar1;
  uint uVar2;

  uVar2 = *(uint *)(this + 0x3c);
  uVar1 = *(uint *)(this + 0xc);
  *(undefined4 *)(this + 0x3c) = 0;
  *(uint *)(this + 0xc) = uVar2;
  *(uint *)(this + 0x10) = ~uVar2;
  *(uint *)(this + 4) = uVar2 & ~uVar1;
  *(uint *)(this + 8) = ~uVar2 & (uVar2 ^ uVar1);
  return;
}
