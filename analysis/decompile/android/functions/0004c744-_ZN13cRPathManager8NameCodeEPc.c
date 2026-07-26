/*
 * mangled: _ZN13cRPathManager8NameCodeEPc
 * demangled: cRPathManager::NameCode(char*)
 * address: 0004c744
 * size: 84
 */

/* cRPathManager::NameCode(char*) */

int __thiscall cRPathManager::NameCode(cRPathManager *this,char *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;

  iVar2 = 0;
  iVar3 = *(int *)(DAT_0004c798 + 0x4c754 + DAT_0004c79c);
  do {
    iVar1 = Rstrcmp(param_1,*(char **)(iVar3 + iVar2 * 4));
    if (iVar1 != 0) {
      return iVar2;
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 != 0x51);
  return -1;
}
