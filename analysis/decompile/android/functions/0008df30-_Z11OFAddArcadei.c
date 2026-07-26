/*
 * mangled: _Z11OFAddArcadei
 * demangled: OFAddArcade(int)
 * address: 0008df30
 * size: 164
 */

/* OFAddArcade(int) */

void OFAddArcade(int param_1)

{
  int iVar1;

  if (gOFORef == -1) {
    return;
  }
  if ((gOFOData[gOFORef * 0x168 + 0x10c] != '\0') &&
     (param_1 <= *(int *)(gOFOData + gOFORef * 0x168 + 0x2c))) {
    return;
  }
  iVar1 = gOFORef * 0x168;
  gOFOData[iVar1 + 0x10c] = 1;
  *(int *)(gOFOData + iVar1 + 0x2c) = param_1;
  iVar1 = OFIsUserLoggedIn();
  if (iVar1 == 0) {
    gOFOSaveFlag = 1;
    return;
  }
  JAVAOpenFeintSubmit(OFID,param_1,gOFORef * 0x168 + 0x390bb0);
  return;
}
