/*
 * mangled: _ZN11cRGameInput2AIEv
 * demangled: cRGameInput::AI()
 * address: 0004a68c
 * size: 144
 */

/* cRGameInput::AI() */

void __thiscall cRGameInput::AI(cRGameInput *this)

{
  if (*(char *)(**(int **)(DAT_0004a71c + 0x4a69c + DAT_0004a720) + 0x2dc) == '\0') {
    return;
  }
  RShellInputRetrieve(*(int *)(this + 0x2c),(int *)(this + 0x68),(float *)(this + 0x40),
                      (float *)(this + 0x44),(float *)(this + 0x54),(float *)(this + 0x58),
                      (float *)(this + 0x5c),(float *)(this + 0x4c),(float *)(this + 0x50),
                      (float *)(this + 0x60),(float *)(this + 100));
  cRInput::Update((cRInput *)(this + 0x2c));
  return;
}
