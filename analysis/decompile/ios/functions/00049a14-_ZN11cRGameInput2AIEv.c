/*
 * mangled: _ZN11cRGameInput2AIEv
 * demangled: cRGameInput::AI()
 * address: 00049a14
 * size: 176
 */

/* cRGameInput::AI() */

void __thiscall cRGameInput::AI(cRGameInput *this)

{
  uint uVar1;

  if (*(char *)(*(int *)PTR__Game_001b60b8 + 0x2dc) != '\0') {
    RShellInputRetrieve(*(int *)(this + 0x2c),(int *)(this + 0x68),(float *)(this + 0x40),
                        (float *)(this + 0x44),(float *)(this + 0x54),(float *)(this + 0x58),
                        (float *)(this + 0x5c),(float *)(this + 0x4c),(float *)(this + 0x50),
                        (float *)(this + 0x60),(float *)(this + 100));
    uVar1 = *(uint *)(this + 0x68);
    *(uint *)(this + 0x30) = ~*(uint *)(this + 0x38) & uVar1;
    *(uint *)(this + 0x34) = ~uVar1 & (uVar1 ^ *(uint *)(this + 0x38));
    *(uint *)(this + 0x38) = uVar1;
    *(uint *)(this + 0x3c) = ~uVar1;
    *(undefined4 *)(this + 0x68) = 0;
  }
  return;
}
