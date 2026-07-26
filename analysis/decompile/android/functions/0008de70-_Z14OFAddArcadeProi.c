/*
 * mangled: _Z14OFAddArcadeProi
 * demangled: OFAddArcadePro(int)
 * address: 0008de70
 * size: 172
 */

/* OFAddArcadePro(int) */

void OFAddArcadePro(int param_1)

{
  int iVar1;

  if (gOFORef == -1) {
    return;
  }
  if ((gOFOData[gOFORef * 0x168 + 0x10d] != '\0') &&
     (param_1 <= *(int *)(gOFOData + gOFORef * 0x168 + 0x30))) {
    return;
  }
  iVar1 = gOFORef * 0x168;
  gOFOData[iVar1 + 0x10d] = 1;
  *(int *)(gOFOData + iVar1 + 0x30) = param_1;
  iVar1 = OFIsUserLoggedIn();
  if (iVar1 == 0) {
    gOFOSaveFlag = 1;
    return;
  }
  JAVAOpenFeintSubmit(OFID + 0x20,param_1,gOFORef * 0x168 + 0x390bb1);
  return;
}
