/*
 * mangled: _ZN17cRResourceManager4InitEv
 * demangled: cRResourceManager::Init()
 * address: 0008e8b4
 * size: 60
 */

/* cRResourceManager::Init() */

void __thiscall cRResourceManager::Init(cRResourceManager *this)

{
  cRResourceManager *pcVar1;
  int iVar2;

  iVar2 = 0;
  *(undefined4 *)(this + 4) = 0;
  pcVar1 = this;
  do {
    iVar2 = iVar2 + 1;
    *(undefined4 *)(pcVar1 + 8) = 0;
    pcVar1 = pcVar1 + 0x8c;
  } while (iVar2 != 0x4b0);
  *(undefined4 *)this = 0;
  this[0x29048] = (cRResourceManager)0x0;
  return;
}
