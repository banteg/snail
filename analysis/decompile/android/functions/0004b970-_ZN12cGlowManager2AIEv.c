/*
 * mangled: _ZN12cGlowManager2AIEv
 * demangled: cGlowManager::AI()
 * address: 0004b970
 * size: 64
 */

/* cGlowManager::AI() */

void __thiscall cGlowManager::AI(cGlowManager *this)

{
  int iVar1;
  int iVar2;
  int iVar3;

  iVar3 = 0;
  do {
    while( true ) {
      iVar2 = iVar3 * 0x20;
      iVar1 = iVar3 * 0x20;
      iVar3 = iVar3 + 1;
      if (*(int *)(this + iVar2) == 1) break;
      if (iVar3 == 8) {
        return;
      }
    }
    cGlow::AI((cGlow *)(this + iVar1));
  } while (iVar3 != 8);
  return;
}
