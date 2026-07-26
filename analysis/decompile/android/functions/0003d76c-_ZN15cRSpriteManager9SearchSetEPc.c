/*
 * mangled: _ZN15cRSpriteManager9SearchSetEPc
 * demangled: cRSpriteManager::SearchSet(char*)
 * address: 0003d76c
 * size: 124
 */

/* cRSpriteManager::SearchSet(char*) */

int __thiscall cRSpriteManager::SearchSet(cRSpriteManager *this,char *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;

  if (0 < *(int *)(this + 0x2af98)) {
    iVar2 = 0;
    iVar3 = 0;
    do {
      iVar3 = iVar3 + 1;
      iVar1 = Rstrcmp((char *)(*(int *)(this + 0x2afa0) + iVar2),param_1);
      if (iVar1 != 0) {
        return *(int *)(this + 0x2afa0) + iVar2;
      }
      iVar2 = iVar2 + 0x58;
    } while (iVar3 < *(int *)(this + 0x2af98));
  }
  return 0;
}
