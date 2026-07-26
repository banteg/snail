/*
 * mangled: _Z16OFSaveHighScoresv
 * demangled: OFSaveHighScores()
 * address: 00175b98
 * size: 192
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* OFSaveHighScores() */

void OFSaveHighScores(void)

{
  char *pcVar1;
  size_t sVar2;
  int iVar3;
  undefined1 *puVar4;
  char acStack_9c [128];

  pcVar1 = (char *)RShellMemoryMalloc(40000,"OF Highscore");
  iVar3 = 0;
  *pcVar1 = '\0';
  _sprintf(pcVar1,"Number:%i\n",_OFHighScoreNumber);
  if (0 < _OFHighScoreNumber) {
    puVar4 = &_OFHS;
    do {
      _sprintf(acStack_9c,"ID:%s ,%i ,%i\n",&_OFHS + iVar3 * 0x48,*(undefined4 *)(puVar4 + 0x40),
               *(undefined4 *)(puVar4 + 0x44));
      _strcat(pcVar1,acStack_9c);
      iVar3 = iVar3 + 1;
      puVar4 = puVar4 + 0x48;
    } while (iVar3 < _OFHighScoreNumber);
  }
  sVar2 = _strlen(pcVar1);
  RShellSaveFile("OFHighScores.txt",pcVar1,sVar2 + 1);
  RShellMemoryFree(pcVar1);
  return;
}
