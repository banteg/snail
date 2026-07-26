/*
 * mangled: _ZN7cRCheat4InitEv
 * demangled: cRCheat::Init()
 * address: 00060a30
 * size: 44
 */

/* cRCheat::Init() */

void __thiscall cRCheat::Init(cRCheat *this)

{
  cRCheat *pcVar1;
  int iVar2;

  iVar2 = 0;
  pcVar1 = this;
  do {
    iVar2 = iVar2 + 1;
    pcVar1[8] = (cRCheat)0x0;
    pcVar1 = pcVar1 + 1;
  } while (iVar2 != 8);
  *(undefined4 *)this = 0;
  return;
}
