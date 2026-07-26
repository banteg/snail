/*
 * mangled: _ZN15cRParcelManager4InitEv
 * demangled: cRParcelManager::Init()
 * address: 0006cbb0
 * size: 64
 */

/* cRParcelManager::Init() */

void __thiscall cRParcelManager::Init(cRParcelManager *this)

{
  int iVar1;
  int iVar2;

  iVar2 = 0;
  iVar1 = Game + 0x718a0;
  do {
    iVar2 = iVar2 + 1;
    *(undefined4 *)(this + 0x2c) = 0;
    *(int *)(this + 0x30) = iVar1;
    this = this + 0x80;
  } while (iVar2 != 0x32);
  return;
}
