/*
 * mangled: _ZN17cRResourceManager13RemoveTextureEi
 * demangled: cRResourceManager::RemoveTexture(int)
 * address: 0008ea38
 * size: 100
 */

/* cRResourceManager::RemoveTexture(int) */

void __thiscall cRResourceManager::RemoveTexture(cRResourceManager *this,int param_1)

{
  cRResourceManager *pcVar1;
  int iVar2;

  if (0 < *(int *)(this + 4)) {
    iVar2 = 0;
    pcVar1 = this;
    do {
      if (((*(int *)(pcVar1 + 8) == 2) && (*(int *)(pcVar1 + 0xc) == 0)) &&
         (*(int *)(pcVar1 + 0x10) == param_1)) {
        Remove(this,iVar2);
        return;
      }
      iVar2 = iVar2 + 1;
      pcVar1 = pcVar1 + 0x8c;
    } while (iVar2 < *(int *)(this + 4));
  }
  return;
}
