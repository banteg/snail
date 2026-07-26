/*
 * mangled: _Z14OFSetHighScorev
 * demangled: OFSetHighScore()
 * address: 00175c74
 * size: 320
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* OFSetHighScore() */

void OFSetHighScore(void)

{
  undefined *puVar1;
  ID self;
  ID IVar2;
  char *pcVar3;
  char *pcVar4;
  size_t sVar5;
  int iVar6;
  int iVar7;

  self = _objc_msgSend((ID)&objc::class_t::OpenFeint,"lastLoggedInUserId");
  IVar2 = _objc_msgSend(self,"length");
  pcVar3 = (char *)RShellMemoryMalloc(IVar2 + 1,"NOT GIVEN");
  pcVar4 = (char *)_objc_msgSend(self,"UTF8String");
  _strcpy(pcVar3,pcVar4);
  sVar5 = _strlen(pcVar3);
  if (sVar5 != 1) {
    if (0 < _OFHighScoreNumber) {
      iVar7 = 0;
      do {
        iVar6 = Rstrcmp(&_OFHS + iVar7 * 0x48,pcVar3);
        puVar1 = PTR__gConfig_001b60d4;
        if (iVar6 != 0) {
          (&DAT_004e3114)[iVar7 * 0x12] = *(undefined4 *)(PTR__gConfig_001b60d4 + 0x10);
          (&DAT_004e3118)[iVar7 * 0x12] = *(undefined4 *)(puVar1 + 0xc);
          RShellMemoryFree(pcVar3);
          return;
        }
        iVar7 = iVar7 + 1;
      } while (iVar7 < _OFHighScoreNumber);
    }
    _strcpy(&_OFHS + _OFHighScoreNumber * 0x48,pcVar3);
    puVar1 = PTR__gConfig_001b60d4;
    (&DAT_004e3114)[_OFHighScoreNumber * 0x12] = *(undefined4 *)(PTR__gConfig_001b60d4 + 0x10);
    (&DAT_004e3118)[_OFHighScoreNumber * 0x12] = *(undefined4 *)(puVar1 + 0xc);
    _OFHighScoreNumber = _OFHighScoreNumber + 1;
  }
  RShellMemoryFree(pcVar3);
  return;
}
