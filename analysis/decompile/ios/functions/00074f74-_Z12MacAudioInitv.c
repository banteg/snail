/*
 * mangled: _Z12MacAudioInitv
 * demangled: MacAudioInit()
 * address: 00074f74
 * size: 96
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* MacAudioInit() */

void MacAudioInit(void)

{
  NSBundle::mainBundle((ID)&_OBJC_CLASS___NSBundle,"mainBundle");
  _SoundEngine_Initialize(0x462c4400);
  _SoundEngine_SetListenerPosition(0,0,0x3f800000);
  _MacSampleCount = 0;
  _MacSampleVolume = 0x3f800000;
  _memcpy(&_MacCurrentMusicFileName,"None",5);
  return;
}
