/*
 * mangled: _Z15RShellMusicPlayPciS_
 * demangled: RShellMusicPlay(char*, int, char*)
 * address: 0002a688
 * size: 116
 */

/* RShellMusicPlay(char*, int, char*) */

void RShellMusicPlay(char *param_1,int param_2,char *param_3)

{
  int iVar1;

  iVar1 = Rstrcmp(param_1,RShellMusicCurrent);
  if (iVar1 != 0) {
    return;
  }
  if (RShellMusicPlayingFlag != '\0') {
    RShellMusicStop();
  }
  Rstrcpy(RShellMusicCurrent,param_1);
  PfmAudioPlayMusic(param_1);
  RShellMusicPlayingFlag = 1;
  RShellMusicPauseFlag = 0;
  return;
}
