/*
 * mangled: _ZN14cRVoiceManager2AIEv
 * demangled: cRVoiceManager::AI()
 * address: 00086f28
 * size: 56
 */

/* cRVoiceManager::AI() */

void __thiscall cRVoiceManager::AI(cRVoiceManager *this)

{
  int iVar1;
  int iVar2;

  iVar1 = 0;
  do {
    iVar2 = iVar1 + 1;
    cRVoiceSet::AI((cRVoiceSet *)(this + iVar1 * 0x18));
    iVar1 = iVar2;
  } while (iVar2 != 0x10);
  *(float *)(this + 0x180) = *(float *)(this + 0x180) + 0.016666668;
  return;
}
