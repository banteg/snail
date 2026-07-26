/*
 * mangled: _ZN17cRSubLazerManager4InitEv
 * demangled: cRSubLazerManager::Init()
 * address: 0006c2e0
 * size: 32
 */

/* cRSubLazerManager::Init() */

void __thiscall cRSubLazerManager::Init(cRSubLazerManager *this)

{
  int iVar1;

  iVar1 = 0;
  do {
    iVar1 = iVar1 + 1;
    *(undefined4 *)(this + 0x74) = 0;
    this = this + 0xa4;
  } while (iVar1 != 0x14);
  return;
}
