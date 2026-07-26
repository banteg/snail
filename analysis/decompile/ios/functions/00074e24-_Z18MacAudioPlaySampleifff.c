/*
 * mangled: _Z18MacAudioPlaySampleifff
 * demangled: MacAudioPlaySample(int, float, float, float)
 * address: 00074e24
 * size: 92
 */

/* MacAudioPlaySample(int, float, float, float) */

void MacAudioPlaySample(int param_1,float param_2,float param_3,float param_4)

{
  int iVar1;

  iVar1 = param_1 * 0x84;
  _SoundEngine_StopEffect(*(undefined4 *)(&_MacSample + iVar1),0);
  _SoundEngine_SetEffectLevel(*(undefined4 *)(&_MacSample + iVar1),param_2 * _MacSampleVolume);
  _SoundEngine_StartEffect(*(undefined4 *)(&_MacSample + iVar1));
  return;
}
