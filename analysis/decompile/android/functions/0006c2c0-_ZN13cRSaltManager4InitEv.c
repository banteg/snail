/*
 * mangled: _ZN13cRSaltManager4InitEv
 * demangled: cRSaltManager::Init()
 * address: 0006c2c0
 * size: 32
 */

/* cRSaltManager::Init() */

void __thiscall cRSaltManager::Init(cRSaltManager *this)

{
  int iVar1;

  iVar1 = 0;
  do {
    iVar1 = iVar1 + 1;
    *(undefined4 *)(this + 0x74) = 0;
    this = this + 0x8c;
  } while (iVar1 != 0x28);
  return;
}
