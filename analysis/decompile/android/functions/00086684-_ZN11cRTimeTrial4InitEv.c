/*
 * mangled: _ZN11cRTimeTrial4InitEv
 * demangled: cRTimeTrial::Init()
 * address: 00086684
 * size: 44
 */

/* cRTimeTrial::Init() */

void __thiscall cRTimeTrial::Init(cRTimeTrial *this)

{
  int iVar1;
  int iVar2;

  iVar2 = 0;
  iVar1 = *(int *)(DAT_000866b0 + 0x86698 + DAT_000866b4);
  do {
    *(undefined4 *)(this + iVar2 * 4) = *(undefined4 *)(iVar1 + iVar2);
    iVar2 = iVar2 + 4;
  } while (iVar2 != 0xcc);
  return;
}
