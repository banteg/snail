/*
 * mangled: _Z16OFAddAchievementi
 * demangled: OFAddAchievement(int)
 * address: 0008dbe8
 * size: 144
 */

/* OFAddAchievement(int) */

void OFAddAchievement(int param_1)

{
  int iVar1;

  if (gOFORef == -1) {
    return;
  }
  iVar1 = param_1 + gOFORef * 0x168;
  if (gOFOData[iVar1 + 0x144] != '\0') {
    return;
  }
  gOFOData[iVar1 + 0x144] = 1;
  iVar1 = OFIsUserLoggedIn();
  if (iVar1 == 0) {
    gOFOSaveFlag = 1;
    return;
  }
  JAVAOpenFeintUnlock(*(char **)(OFAID + param_1 * 4),gOFORef * 0x168 + param_1 + 0x390be8);
  return;
}
