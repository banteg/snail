/*
 * mangled: _Z18MacAudioStartMusicv
 * demangled: MacAudioStartMusic()
 * address: 000751f8
 * size: 56
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* MacAudioStartMusic() */

void MacAudioStartMusic(void)

{
  int iVar1;

  if (_MacLatestMusicFileName == '\0') {
    return;
  }
  iVar1 = Rstrcmp("None",&_MacCurrentMusicFileName);
  if (iVar1 == 0) {
    return;
  }
  MacAudioPlayMusic(&_MacLatestMusicFileName);
  return;
}
