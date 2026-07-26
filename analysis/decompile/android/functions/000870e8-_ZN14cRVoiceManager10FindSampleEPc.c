/*
 * mangled: _ZN14cRVoiceManager10FindSampleEPc
 * demangled: cRVoiceManager::FindSample(char*)
 * address: 000870e8
 * size: 136
 */

/* cRVoiceManager::FindSample(char*) */

undefined4 __thiscall cRVoiceManager::FindSample(cRVoiceManager *this,char *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  cRVoiceManager *pcVar4;
  int iVar5;

  iVar5 = 0;
  pcVar4 = this;
  do {
    if (0 < *(int *)pcVar4) {
      iVar2 = 0;
      iVar3 = iVar2;
      do {
        iVar3 = iVar3 + 1;
        iVar1 = Rstrcmp((char *)(*(int *)(pcVar4 + 0xc) + iVar2 + 4),param_1);
        if (iVar1 != 0) {
          return *(undefined4 *)(*(int *)(this + iVar5 * 0x18 + 0xc) + iVar2);
        }
        iVar2 = iVar2 + 0x8c;
      } while (iVar3 < *(int *)pcVar4);
    }
    iVar5 = iVar5 + 1;
    pcVar4 = pcVar4 + 0x18;
  } while (iVar5 != 0x10);
  return 0xffffffff;
}
