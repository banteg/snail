/*
 * mangled: _Z16OFLoadHighScoresv
 * demangled: OFLoadHighScores()
 * address: 001759a8
 * size: 396
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* OFLoadHighScores() */

void OFLoadHighScores(void)

{
  char *pcVar1;
  char *pcVar2;
  int iVar3;
  int iVar4;
  size_t sVar5;
  char *pcVar6;
  char cVar7;
  int iVar8;
  undefined1 *puVar9;
  char acStack_a4 [128];
  int iStack_24;

  pcVar1 = (char *)RShellLoadFile("OFHighScores.txt",&iStack_24);
  if (pcVar1 == (char *)0x0) {
    _OFHighScoreNumber = 0;
  }
  else {
    pcVar2 = (char *)Rstrfind("Number:",pcVar1);
    iVar3 = Rstrfind(":",pcVar2);
    _OFHighScoreNumber = _atoi((char *)(iVar3 + 1));
    if (0 < _OFHighScoreNumber) {
      puVar9 = &_OFHS;
      iVar8 = 0;
      do {
        pcVar2 = (char *)Rstrfind("ID:",(char *)(iVar3 + 1));
        iVar3 = Rstrfind(":",pcVar2);
        cVar7 = *(char *)(iVar3 + 1);
        pcVar2 = (char *)(iVar3 + 1);
        if (cVar7 != ' ') {
          pcVar6 = &_OFHS + iVar8 * 0x48;
          do {
            *pcVar6 = cVar7;
            pcVar2 = pcVar2 + 1;
            cVar7 = *pcVar2;
            pcVar6 = pcVar6 + 1;
          } while (cVar7 != ' ');
        }
        iVar3 = _atoi(pcVar2 + 1);
        iVar8 = iVar8 + 1;
        *(int *)(puVar9 + 0x40) = iVar3;
        iVar3 = Rstrfind(",",pcVar2 + 1);
        iVar4 = _atoi((char *)(iVar3 + 1));
        *(int *)(puVar9 + 0x44) = iVar4;
        puVar9 = puVar9 + 0x48;
      } while (iVar8 < _OFHighScoreNumber);
    }
    _sprintf(pcVar1,"Number:%i\n");
    if (0 < _OFHighScoreNumber) {
      puVar9 = &_OFHS;
      iVar3 = 0;
      do {
        _sprintf(acStack_a4,"ID:%s ,%i ,%i\n",&_OFHS + iVar3 * 0x48,*(undefined4 *)(puVar9 + 0x40),
                 *(undefined4 *)(puVar9 + 0x44));
        _strcat(pcVar1,acStack_a4);
        iVar3 = iVar3 + 1;
        puVar9 = puVar9 + 0x48;
      } while (iVar3 < _OFHighScoreNumber);
    }
    sVar5 = _strlen(pcVar1);
    RShellSaveFile("OFHighScores.txt",pcVar1,sVar5 + 1);
    RShellMemoryFree(pcVar1);
  }
  return;
}
