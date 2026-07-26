/*
 * mangled: _ZN9cROptions5ApplyEb
 * demangled: cROptions::Apply(bool)
 * address: 00061dac
 * size: 120
 */

/* cROptions::Apply(bool) */

void __thiscall cROptions::Apply(cROptions *this,bool param_1)

{
  undefined *puVar1;

  puVar1 = PTR__gConfig_001b60d4;
  MacAudioSetSampleVolume(*(float *)PTR__gConfig_001b60d4);
  MacAudioSetMusicVolume(*(float *)(puVar1 + 4) * *(float *)PTR__MacNormalizeMusic_001b61f0);
  if (*(float *)(puVar1 + 4) == 0.0) {
    MacAudioStopMusic();
    if (param_1) {
      return;
    }
  }
  else if (param_1) {
    return;
  }
  if (*(float *)(puVar1 + 4) == 0.0) {
    return;
  }
  MacAudioStartMusic();
  return;
}
