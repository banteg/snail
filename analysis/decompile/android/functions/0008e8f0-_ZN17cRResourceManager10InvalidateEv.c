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
  DAT_0038c9cd = 1;
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
