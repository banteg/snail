/*
 * mangled: _Z15RShellMusicStopv
 * demangled: RShellMusicStop()
 * address: 0002a5b4
 * size: 44
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* RShellMusicStop() */

void RShellMusicStop(void)

{
  if (RShellMusicPlayingFlag != '\0') {
    PfmAudioStopMusic();
  }
  RShellMusicInit();
  return;
}
