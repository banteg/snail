/*
 * mangled: _ZN12cGlowManager4InitEv
 * demangled: cGlowManager::Init()
 * address: 0004b564
 * size: 28
 */

/* cGlowManager::Init() */

void __thiscall cGlowManager::Init(cGlowManager *this)

{
  int iVar1;

  iVar1 = 0;
  do {
    *(undefined4 *)(this + iVar1) = 0;
    iVar1 = iVar1 + 0x20;
  } while (iVar1 != 0x100);
  return;
}
