/*
 * mangled: _Z14OFGetHighScorev
 * demangled: OFGetHighScore()
 * address: 0008e5cc
 * size: 308
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* OFGetHighScore() */

void OFGetHighScore(void)

{
  int iVar1;
  size_t sVar2;
  int iVar3;
  int iVar4;
  char acStack_6c [64];
  int local_2c;

  local_2c = __stack_chk_guard;
  JAVAOpenFeintLastLoggedInUserID(acStack_6c,0x40);
  sVar2 = strlen(acStack_6c);
  if (sVar2 == 1) {
    gConfig._12_4_ = 0;
    gConfig._16_4_ = 0;
  }
  else {
    if (0 < OFHighScoreNumber) {
      iVar4 = 0;
      do {
        iVar1 = iVar4 * 0x48;
        iVar3 = Rstrcmp(OFHS + iVar1,acStack_6c);
        if (iVar3 != 0) {
          gConfig._16_4_ = *(undefined4 *)(OFHS + iVar1 + 0x40);
          gConfig._12_4_ = *(undefined4 *)(OFHS + iVar1 + 0x44);
          goto LAB_0008e678;
        }
        iVar4 = iVar4 + 1;
      } while (iVar4 < OFHighScoreNumber);
    }
    strcpy(OFHS + OFHighScoreNumber * 0x48,acStack_6c);
    *(undefined4 *)(OFHS + OFHighScoreNumber * 0x48 + 0x44) = 0;
    *(undefined4 *)(OFHS + OFHighScoreNumber * 0x48 + 0x40) = 0;
    gConfig._12_4_ = 0;
    gConfig._16_4_ = 0;
    OFHighScoreNumber = OFHighScoreNumber + 1;
  }
LAB_0008e678:
  if (local_2c != __stack_chk_guard) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}
