/*
 * mangled: _Z14OFAddChallengei
 * demangled: OFAddChallenge(int)
 * address: 0008ddb0
 * size: 172
 */

/* OFAddChallenge(int) */

void OFAddChallenge(int param_1)

{
  int iVar1;

  if (gOFORef == -1) {
    return;
  }
  if ((gOFOData[gOFORef * 0x168 + 0x10e] != '\0') &&
     (param_1 <= *(int *)(gOFOData + gOFORef * 0x168 + 0x34))) {
    return;
  }
  iVar1 = gOFORef * 0x168;
  gOFOData[iVar1 + 0x10e] = 1;
  *(int *)(gOFOData + iVar1 + 0x34) = param_1;
  iVar1 = OFIsUserLoggedIn();
  if (iVar1 == 0) {
    gOFOSaveFlag = 1;
    return;
  }
  JAVAOpenFeintSubmit(OFID + 0x40,param_1,gOFORef * 0x168 + 0x390bb2);
  return;
}
