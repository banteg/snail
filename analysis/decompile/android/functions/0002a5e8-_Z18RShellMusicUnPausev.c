/*
 * mangled: _Z18RShellMusicUnPausev
 * demangled: RShellMusicUnPause()
 * address: 0002a5e8
 * size: 68
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* RShellMusicUnPause() */

void RShellMusicUnPause(void)

{
  if (RShellMusicPlayingFlag == '\0') {
    return;
  }
  if (RShellMusicPauseFlag == '\0') {
    return;
  }
  PfmAudioUnPauseMusic();
  RShellMusicPauseFlag = 0;
  return;
}
