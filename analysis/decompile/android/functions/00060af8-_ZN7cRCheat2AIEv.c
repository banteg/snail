/*
 * mangled: _ZN7cRCheat2AIEv
 * demangled: cRCheat::AI()
 * address: 00060af8
 * size: 84
 */

/* cRCheat::AI() */

void __thiscall cRCheat::AI(cRCheat *this)

{
  cRCheat cVar1;
  int iVar2;
  cRCheat *pcVar3;

  cVar1 = (cRCheat)RShellInkey();
  if ((byte)((char)cVar1 + 0x9fU) < 0x1a) {
    cVar1 = (cRCheat)((char)cVar1 + -0x20);
  }
  if ((byte)((char)cVar1 + 0xbfU) < 0x1a) {
    iVar2 = 7;
    pcVar3 = this;
    do {
      iVar2 = iVar2 + -1;
      pcVar3[0xf] = pcVar3[0xe];
      pcVar3 = pcVar3 + -1;
    } while (iVar2 != 0);
    this[8] = cVar1;
    return;
  }
  return;
}
