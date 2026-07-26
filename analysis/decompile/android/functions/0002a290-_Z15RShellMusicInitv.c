/*
 * mangled: _Z15RShellMusicInitv
 * demangled: RShellMusicInit()
 * address: 0002a290
 * size: 52
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* RShellMusicInit() */

void RShellMusicInit(void)

{
  RShellMusicPlayingFlag = 0;
  RShellMusicPauseFlag = 0;
  RShellMusicCurrent[0] = 0;
  return;
}
