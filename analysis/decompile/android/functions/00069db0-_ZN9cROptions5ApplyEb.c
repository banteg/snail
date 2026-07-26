/*
 * mangled: _ZN9cROptions5ApplyEb
 * demangled: cROptions::Apply(bool)
 * address: 00069db0
 * size: 128
 */

/* cROptions::Apply(bool) */

void cROptions::Apply(bool param_1)

{
  int in_r1;
  float in_s0;
  float fVar1;

  fVar1 = (float)PfmAudioSetSampleVolume(in_s0);
  RShellMusicVolume(fVar1);
  if ((float)gConfig._4_4_ == 0.0) {
    RShellMusicPause();
    if (in_r1 != 0) {
      return;
    }
  }
  else if (in_r1 != 0) {
    return;
  }
  if ((float)gConfig._4_4_ == 0.0) {
    return;
  }
  RShellMusicUnPause();
  return;
}
