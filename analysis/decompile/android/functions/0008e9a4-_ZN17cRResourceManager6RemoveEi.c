/*
 * mangled: _ZN17cRResourceManager6RemoveEi
 * demangled: cRResourceManager::Remove(int)
 * address: 0008e9a4
 * size: 148
 */

/* cRResourceManager::Remove(int) */

void __thiscall cRResourceManager::Remove(cRResourceManager *this,int param_1)

{
  int iVar1;
  cRResourceManager *pcVar2;
  int iVar3;

  iVar1 = *(int *)(this + 4);
  if (param_1 < iVar1 + -1) {
    pcVar2 = this + param_1 * 0x8c + 0x9c;
    do {
      iVar3 = param_1 + 1;
      *(undefined4 *)(pcVar2 + -0x94) = *(undefined4 *)(pcVar2 + -8);
      *(undefined4 *)(pcVar2 + -0x90) = *(undefined4 *)(pcVar2 + -4);
      *(undefined4 *)(pcVar2 + -0x8c) = *(undefined4 *)pcVar2;
      strcpy((char *)(this + param_1 * 0x8c + 0x14),(char *)(this + iVar3 * 0x8c + 0x14));
      iVar1 = *(int *)(this + 4);
      pcVar2 = pcVar2 + 0x8c;
      param_1 = iVar3;
    } while (iVar3 < iVar1 + -1);
  }
  *(int *)(this + 4) = iVar1 + -1;
  *(undefined4 *)(this + 0x28fbc) = 0;
  return;
}
