/*
 * mangled: _Z16OFLoadHighScoresv
 * demangled: OFLoadHighScores()
 * address: 0008dfec
 * size: 552
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* OFLoadHighScores() */

void OFLoadHighScores(void)

{
  char *__s;
  char *pcVar1;
  int iVar2;
  int iVar3;
  size_t sVar4;
  char cVar5;
  int iVar6;
  undefined1 *puVar7;
  int iStack_b0;
  char acStack_ac [128];
  int local_2c;

  local_2c = __stack_chk_guard;
  __s = (char *)RShellLoadFile("ofhighscores.txt",&iStack_b0);
  if (__s == (char *)0x0) {
    OFHighScoreNumber = 0;
  }
  else {
    pcVar1 = (char *)Rstrfind("Number:",__s);
    iVar2 = Rstrfind(":",pcVar1);
    pcVar1 = (char *)(iVar2 + 1);
    iVar2 = atoi(pcVar1);
    OFHighScoreNumber = iVar2;
    if (0 < iVar2) {
      iVar6 = 0;
      puVar7 = OFHS;
      do {
        pcVar1 = (char *)Rstrfind("ID:",pcVar1);
        iVar2 = Rstrfind(":",pcVar1);
        cVar5 = *(char *)(iVar2 + 1);
        pcVar1 = (char *)(iVar2 + 1);
        if (cVar5 != ' ') {
          iVar2 = 0;
          do {
            OFHS[iVar2 + iVar6 * 0x48] = cVar5;
            iVar2 = iVar2 + 1;
            pcVar1 = pcVar1 + 1;
            cVar5 = *pcVar1;
          } while (cVar5 != ' ');
        }
        iVar6 = iVar6 + 1;
        iVar2 = atoi(pcVar1 + 1);
        *(int *)(puVar7 + 0x40) = iVar2;
        iVar2 = Rstrfind(",",pcVar1 + 1);
        pcVar1 = (char *)(iVar2 + 1);
        iVar3 = atoi(pcVar1);
        iVar2 = OFHighScoreNumber;
        *(int *)(puVar7 + 0x44) = iVar3;
        puVar7 = puVar7 + 0x48;
      } while (iVar6 < iVar2);
    }
    sprintf(__s,"Number:%i\n",iVar2);
    if (0 < OFHighScoreNumber) {
      iVar2 = 0;
      puVar7 = OFHS;
      do {
        sprintf(acStack_ac,"ID:%s ,%i ,%i\n",OFHS + iVar2 * 0x48,*(undefined4 *)(puVar7 + 0x40),
                *(undefined4 *)(puVar7 + 0x44));
        strcat(__s,acStack_ac);
        iVar2 = iVar2 + 1;
        puVar7 = puVar7 + 0x48;
      } while (iVar2 < OFHighScoreNumber);
    }
    sVar4 = strlen(__s);
    RShellSaveFile("ofhighscores.txt",__s,sVar4 + 1);
    RShellMemoryFree(__s);
  }
  if (local_2c == __stack_chk_guard) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}
