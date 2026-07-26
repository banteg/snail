/*
 * mangled: _ZN17cRResourceManager3AddE13eResourceTypePvPc
 * demangled: cRResourceManager::Add(eResourceType, void*, char*)
 * address: 0008ea9c
 * size: 108
 */

/* cRResourceManager::Add(eResourceType, void*, char*) */

int __thiscall
cRResourceManager::Add(cRResourceManager *this,undefined4 param_2,undefined4 param_3,char *param_4)

{
  int iVar1;

  wprintf("ResourceManager::Add %i",*(undefined4 *)(this + 4));
  iVar1 = *(int *)(this + 4);
  *(undefined4 *)(this + iVar1 * 0x8c + 0x10) = param_3;
  *(undefined4 *)(this + iVar1 * 0x8c + 8) = 2;
  *(undefined4 *)(this + iVar1 * 0x8c + 0xc) = param_2;
  strcpy((char *)(this + iVar1 * 0x8c + 0x14),param_4);
  iVar1 = *(int *)(this + 4);
  *(int *)(this + 4) = iVar1 + 1;
  return iVar1;
}
