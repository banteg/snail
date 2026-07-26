/*
 * mangled: _Z14OFGetHighScorev
 * demangled: OFGetHighScore()
 * address: 00175dd4
 * size: 356
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* OFGetHighScore() */

void OFGetHighScore(void)

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
  puVar1 = PTR__gConfig_001b60d4;
  if (sVar5 == 1) {
    *(undefined4 *)(PTR__gConfig_001b60d4 + 0x10) = 0;
    *(undefined4 *)(puVar1 + 0xc) = 0;
    RShellMemoryFree(pcVar3);
  }
  else {
    if (0 < _OFHighScoreNumber) {
      iVar7 = 0;
      do {
        iVar6 = Rstrcmp(&_OFHS + iVar7 * 0x48,pcVar3);
        puVar1 = PTR__gConfig_001b60d4;
        if (iVar6 != 0) {
          *(undefined4 *)(PTR__gConfig_001b60d4 + 0x10) = (&DAT_004e3114)[iVar7 * 0x12];
          *(undefined4 *)(puVar1 + 0xc) = (&DAT_004e3118)[iVar7 * 0x12];
          RShellMemoryFree(pcVar3);
          return;
        }
        iVar7 = iVar7 + 1;
      } while (iVar7 < _OFHighScoreNumber);
    }
    _strcpy(&_OFHS + _OFHighScoreNumber * 0x48,pcVar3);
    (&DAT_004e3114)[_OFHighScoreNumber * 0x12] = 0;
    (&DAT_004e3118)[_OFHighScoreNumber * 0x12] = 0;
    puVar1 = PTR__gConfig_001b60d4;
    _OFHighScoreNumber = _OFHighScoreNumber + 1;
    *(undefined4 *)(PTR__gConfig_001b60d4 + 0x10) = 0;
    *(undefined4 *)(puVar1 + 0xc) = 0;
    RShellMemoryFree(pcVar3);
  }
  return;
}
