/*
 * mangled: _ZN12cGlowManager6UnInitEv
 * demangled: cGlowManager::UnInit()
 * address: 0004b580
 * size: 28
 */

/* cGlowManager::UnInit() */

void __thiscall cGlowManager::UnInit(cGlowManager *this)

{
  int iVar1;

  iVar1 = 0;
  do {
    *(undefined4 *)(this + iVar1) = 0;
    iVar1 = iVar1 + 0x20;
  } while (iVar1 != 0x100);
  return;
}
