/*
 * mangled: _ZN7cRCheat2AIEv
 * demangled: cRCheat::AI()
 * address: 00066984
 * size: 128
 */

/* cRCheat::AI() */

void __thiscall cRCheat::AI(cRCheat *this)

{
  cRCheat cVar1;
  cRCheat cVar2;

  cVar2 = (cRCheat)RShellInkey();
  if ((byte)((char)cVar2 + 0x9fU) < 0x1a) {
    cVar2 = (cRCheat)((char)cVar2 + -0x20);
  }
  if (0x19 < (byte)((char)cVar2 + 0xbfU)) {
    return;
  }
  this[0xf] = this[0xe];
  this[0xe] = this[0xd];
  this[0xd] = this[0xc];
  this[0xc] = this[0xb];
  this[0xb] = this[10];
  this[10] = this[9];
  cVar1 = this[8];
  this[8] = cVar2;
  this[9] = cVar1;
  return;
}
