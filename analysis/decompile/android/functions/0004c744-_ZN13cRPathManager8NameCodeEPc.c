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

  iVar2 = 0;
  do {
    iVar1 = Rstrcmp(param_1,(char *)(&gPathName)[iVar2]);
    if (iVar1 != 0) {
      return iVar2;
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 != 0x51);
  return -1;
}
