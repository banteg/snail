/*
 * mangled: _ZN9cROptions5ApplyEb
 * demangled: cROptions::Apply(bool)
 * address: 00069db0
 * size: 128
 */

/* cROptions::Apply(bool) */

void cROptions::Apply(bool param_1)

{
  int iVar1;
  int in_r1;
  int iVar2;
  int iVar3;
  float in_s0;
  float fVar4;

  iVar1 = DAT_00069e34;
  iVar2 = DAT_00069e30 + 0x69dc8;
  iVar3 = *(int *)(iVar2 + DAT_00069e34);
  fVar4 = (float)PfmAudioSetSampleVolume(in_s0);
  RShellMusicVolume(fVar4);
  if (*(float *)(iVar3 + 4) == 0.0) {
    RShellMusicPause();
    if (in_r1 != 0) {
      return;
    }
  }
  else if (in_r1 != 0) {
    return;
  }
  if (*(float *)(*(int *)(iVar2 + iVar1) + 4) == 0.0) {
    return;
  }
  RShellMusicUnPause();
  return;
}
