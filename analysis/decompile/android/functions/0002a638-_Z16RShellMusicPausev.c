/*
 * mangled: _Z16RShellMusicPausev
 * demangled: RShellMusicPause()
 * address: 0002a638
 * size: 68
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* RShellMusicPause() */

void RShellMusicPause(void)

{
  if (RShellMusicPlayingFlag == '\0') {
    return;
  }
  if (RShellMusicPauseFlag != '\0') {
    return;
  }
  PfmAudioPauseMusic();
  RShellMusicPauseFlag = 1;
  return;
}
