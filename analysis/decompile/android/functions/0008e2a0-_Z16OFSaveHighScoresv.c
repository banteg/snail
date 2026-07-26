/*
 * mangled: _Z16OFSaveHighScoresv
 * demangled: OFSaveHighScores()
 * address: 0008e2a0
 * size: 264
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* OFSaveHighScores() */

void OFSaveHighScores(void)

{
  char *__s;
  size_t sVar1;
  int iVar2;
  undefined1 *puVar3;
  char acStack_ac [128];
  int local_2c;

  iVar2 = 0;
  local_2c = __stack_chk_guard;
  __s = (char *)RShellMemoryMalloc(40000,"OF Highscore");
  *__s = '\0';
  sprintf(__s,"Number:%i\n",OFHighScoreNumber);
  if (0 < OFHighScoreNumber) {
    puVar3 = OFHS;
    do {
      sprintf(acStack_ac,"ID:%s ,%i ,%i\n",OFHS + iVar2 * 0x48,*(undefined4 *)(puVar3 + 0x40),
              *(undefined4 *)(puVar3 + 0x44));
      strcat(__s,acStack_ac);
      iVar2 = iVar2 + 1;
      puVar3 = puVar3 + 0x48;
    } while (iVar2 < OFHighScoreNumber);
  }
  sVar1 = strlen(__s);
  RShellSaveFile("ofhighscores.txt",__s,sVar1 + 1);
  RShellMemoryFree(__s);
  if (local_2c == __stack_chk_guard) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}
