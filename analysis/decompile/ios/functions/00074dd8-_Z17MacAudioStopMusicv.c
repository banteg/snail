/*
 * mangled: _Z17MacAudioStopMusicv
 * demangled: MacAudioStopMusic()
 * address: 00074dd8
 * size: 52
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* MacAudioStopMusic() */

void MacAudioStopMusic(void)

{
  int iVar1;

  iVar1 = Rstrcmp("None",&_MacCurrentMusicFileName);
  if (iVar1 != 0) {
    return;
  }
  _SoundEngine_StopBackgroundMusic();
  _SoundEngine_UnloadBackgroundMusicTrack();
  Rstrcpy(&_MacCurrentMusicFileName,"None");
  return;
}
