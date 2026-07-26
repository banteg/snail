/*
 * mangled: _ZN10cRVoiceSet4PlayEi
 * demangled: cRVoiceSet::Play(int)
 * address: 00086fa4
 * size: 156
 */

/* cRVoiceSet::Play(int) */

undefined4 cRVoiceSet::Play(int param_1)

{
  int in_r1;
  int iVar1;
  float in_s0;
  float in_s1;
  float in_s2;

  if (*(float *)(param_1 + 0x10) != 0.0) {
    return 0;
  }
  *(undefined4 *)(param_1 + 0x10) = *(undefined4 *)(param_1 + 0x14);
  if (in_r1 == -1) {
    RShellVoicePlay(*(int *)(*(int *)(param_1 + 0xc) +
                            *(int *)(*(int *)(param_1 + 8) + *(int *)(param_1 + 4) * 4) * 0x8c),
                    in_s0,in_s1,in_s2);
    iVar1 = *(int *)(param_1 + 4) + 1;
    *(int *)(param_1 + 4) = iVar1;
    if (iVar1 == *(int *)param_1) {
      *(undefined4 *)(param_1 + 4) = 0;
    }
    return 1;
  }
  RShellVoicePlay(in_r1,in_s0,in_s1,in_s2);
  return 1;
}
