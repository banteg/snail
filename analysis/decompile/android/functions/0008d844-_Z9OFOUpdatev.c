/*
 * mangled: _Z9OFOUpdatev
 * demangled: OFOUpdate()
 * address: 0008d844
 * size: 348
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* OFOUpdate() */

void OFOUpdate(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;

  iVar1 = OFIsUserLoggedIn();
  if (iVar1 == 0) {
    wprintf("OFOUpdate with no one logged in");
    return;
  }
  iVar4 = 0;
  iVar1 = gOFORef;
  do {
    while (gOFOData[iVar1 * 0x168 + iVar4 + 0x10c] == '\x01') {
      wprintf(":OF updating Leaderboard %i",iVar4);
      iVar3 = gOFORef * 0x5a + iVar4;
      iVar1 = iVar4 * 0x20;
      iVar2 = gOFORef * 0x168 + iVar4;
      iVar4 = iVar4 + 1;
      JAVAOpenFeintSubmit(OFID + iVar1,*(int *)(gOFOData + iVar3 * 4 + 0x2c),iVar2 + 0x390bb0);
      iVar1 = gOFORef;
      if (iVar4 == 0x38) goto LAB_0008d904;
    }
    iVar4 = iVar4 + 1;
  } while (iVar4 != 0x38);
LAB_0008d904:
  iVar4 = 0;
  while( true ) {
    if (gOFOData[iVar1 * 0x168 + iVar4 + 0x144] == '\x01') {
      wprintf(":OF updating Achievement %i",iVar4);
      JAVAOpenFeintUnlock(*(char **)(OFAID + iVar4 * 4),gOFORef * 0x168 + iVar4 + 0x390be8);
    }
    if (iVar4 == 0x22) break;
    iVar4 = iVar4 + 1;
    iVar1 = gOFORef;
  }
  return;
}
