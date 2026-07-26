/*
 * mangled: _ZN7cRSound10PlayVolumeEif
 * demangled: cRSound::PlayVolume(int, float)
 * address: 000631b4
 * size: 32
 */

/* cRSound::PlayVolume(int, float) */

void __thiscall cRSound::PlayVolume(cRSound *this,int param_1,float param_2)

{
  RShellSoundPlay(param_1,param_2,-1.0,0.0);
  return;
}
