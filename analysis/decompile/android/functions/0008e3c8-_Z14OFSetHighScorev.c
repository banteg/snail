/*
 * mangled: _Z14OFSetHighScorev
 * demangled: OFSetHighScore()
 * address: 0008e3c8
 * size: 280
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* OFSetHighScore() */

void OFSetHighScore(void)

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
  if (1 < sVar2) {
    if (0 < OFHighScoreNumber) {
      iVar4 = 0;
      do {
        iVar1 = iVar4 * 0x48;
        iVar3 = Rstrcmp(OFHS + iVar1,acStack_6c);
        if (iVar3 != 0) {
          *(undefined4 *)(OFHS + iVar1 + 0x40) = gConfig._16_4_;
          *(undefined4 *)(OFHS + iVar1 + 0x44) = gConfig._12_4_;
          goto LAB_0008e474;
        }
        iVar4 = iVar4 + 1;
      } while (iVar4 < OFHighScoreNumber);
    }
    strcpy(OFHS + OFHighScoreNumber * 0x48,acStack_6c);
    *(undefined4 *)(OFHS + OFHighScoreNumber * 0x48 + 0x40) = gConfig._16_4_;
    *(undefined4 *)(OFHS + OFHighScoreNumber * 0x48 + 0x44) = gConfig._12_4_;
    OFHighScoreNumber = OFHighScoreNumber + 1;
  }
LAB_0008e474:
  if (local_2c != __stack_chk_guard) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}
