/*
 * mangled: _ZN17cRResourceManager10InvalidateEv
 * demangled: cRResourceManager::Invalidate()
 * address: 0008e8f0
 * size: 64
 */

/* cRResourceManager::Invalidate() */

void __thiscall cRResourceManager::Invalidate(cRResourceManager *this)

{
  int iVar1;
  int iVar2;

  iVar1 = *(int *)(this + 4);
  *(undefined1 *)(*(int *)(DAT_0008e930 + 0x8e904 + DAT_0008e934) + 0x35) = 1;
  if (iVar1 < 1) {
    return;
  }
  iVar2 = 0;
  do {
    iVar2 = iVar2 + 1;
    *(undefined4 *)(this + 8) = 1;
    this = this + 0x8c;
  } while (iVar2 < iVar1);
  return;
}
