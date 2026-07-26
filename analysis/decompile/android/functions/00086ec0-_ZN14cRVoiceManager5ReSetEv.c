/*
 * mangled: _ZN14cRVoiceManager5ReSetEv
 * demangled: cRVoiceManager::ReSet()
 * address: 00086ec0
 * size: 40
 */

/* cRVoiceManager::ReSet() */

void __thiscall cRVoiceManager::ReSet(cRVoiceManager *this)

{
  int iVar1;

  iVar1 = 0;
  *(undefined4 *)(this + 0x180) = 0;
  do {
    iVar1 = iVar1 + 1;
    *(undefined4 *)(this + 0x10) = 0;
    this = this + 0x18;
  } while (iVar1 != 0x10);
  return;
}
