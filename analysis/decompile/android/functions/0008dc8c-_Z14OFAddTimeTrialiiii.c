/*
 * mangled: _Z14OFAddTimeTrialiiii
 * demangled: OFAddTimeTrial(int, int, int, int)
 * address: 0008dc8c
 * size: 272
 */

/* OFAddTimeTrial(int, int, int, int) */

void OFAddTimeTrial(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;

  if (gOFORef != -1) {
    iVar2 = param_4 + 5;
    iVar3 = param_2 * 100 + param_1 * 10000 + param_3 % 100;
    if (((gOFOData[gOFORef * 0x168 + iVar2 + 0x10c] == '\0') ||
        (*(int *)(gOFOData + (gOFORef * 0x5a + iVar2) * 4 + 0x2c) == 0)) ||
       (iVar3 <= *(int *)(gOFOData + (gOFORef * 0x5a + iVar2) * 4 + 0x2c))) {
      iVar1 = gOFORef * 0x168;
      *(int *)(gOFOData + (gOFORef * 0x5a + iVar2) * 4 + 0x2c) = iVar3;
      gOFOData[iVar1 + iVar2 + 0x10c] = 1;
      iVar1 = OFIsUserLoggedIn();
      if (iVar1 != 0) {
        JAVAOpenFeintSubmit(OFID + iVar2 * 0x20,iVar3,gOFORef * 0x168 + iVar2 + 0x390bb0);
        return;
      }
      gOFOSaveFlag = 1;
    }
  }
  return;
}
