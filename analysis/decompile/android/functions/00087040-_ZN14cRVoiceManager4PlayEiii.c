/*
 * mangled: _ZN14cRVoiceManager4PlayEiii
 * demangled: cRVoiceManager::Play(int, int, int)
 * address: 00087040
 * size: 164
 */

/* cRVoiceManager::Play(int, int, int) */

int cRVoiceManager::Play(int param_1,int param_2,int param_3)

{
  int iVar1;

  if ((uint)param_3 < 2) {
    iVar1 = IsPlaying();
    if ((iVar1 != -1) ||
       ((param_3 == 1 && (*(float *)(param_1 + 0x180) < *(float *)(param_1 + 0x184))))) {
      return 0;
    }
  }
  else if (param_3 == 2) {
    IsPlaying();
    iVar1 = cRVoiceSet::Play(param_1 + param_2 * 0x18);
    if (iVar1 == 0) {
      return 0;
    }
    goto LAB_0008707c;
  }
  iVar1 = cRVoiceSet::Play(param_1 + param_2 * 0x18);
  if (iVar1 == 0) {
    return 0;
  }
LAB_0008707c:
  if (param_3 - 1U < 2) {
    *(undefined4 *)(param_1 + 0x180) = 0;
  }
  return iVar1;
}
