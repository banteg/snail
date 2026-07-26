/*
 * mangled: _ZN13cRPathManager8NameCodeEPc
 * demangled: cRPathManager::NameCode(char*)
 * address: 0004df90
 * size: 76
 */

/* cRPathManager::NameCode(char*) */

int __thiscall cRPathManager::NameCode(cRPathManager *this,char *param_1)

{
  int iVar1;
  int iVar2;

  iVar1 = 0;
  do {
    iVar2 = iVar1;
    iVar1 = Rstrcmp(param_1,(char *)(&_gPathName)[iVar2]);
    if (iVar1 != 0) {
      return iVar2;
    }
    iVar1 = iVar2 + 1;
  } while (iVar2 + 1 != 0x51);
  return iVar2 + -0x51;
}
