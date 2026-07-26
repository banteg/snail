/*
 * mangled: _ZN14cRVoiceManager5ReSetEv
 * demangled: cRVoiceManager::ReSet()
 * address: 00086ec0
 * size: 40
 */

/* cRVoiceManager::ReSet() */

void __thiscall cRVoiceManager::ReSet(cRVoiceManager *this)

{
  undefined4 uVar1;
  int iVar2;

  uVar1 = DAT_00086ee8;
  iVar2 = 0;
  *(undefined4 *)(this + 0x180) = DAT_00086ee8;
  do {
    iVar2 = iVar2 + 1;
    *(undefined4 *)(this + 0x10) = uVar1;
    this = this + 0x18;
  } while (iVar2 != 0x10);
  return;
}
