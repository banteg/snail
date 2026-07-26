/*
 * mangled: _Z7OFOLoadv
 * demangled: OFOLoad()
 * address: 0008d9c0
 * size: 496
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* OFOLoad() */

void OFOLoad(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  int iVar6;

  iVar3 = 0;
  wprintf(":OFOLoad");
  gOFOValid = 1;
  do {
    iVar4 = iVar3 * 0x168;
    iVar3 = iVar3 + 1;
    cOFOData::Init((cOFOData *)(gOFOData + iVar4));
  } while (iVar3 != 0x20);
  iVar4 = 0;
  iVar3 = 0;
  iVar6 = 0;
  gRegisterLoadFile("of.cfg",gOFOData);
  do {
    pcVar5 = gOFOData + iVar4;
    iVar4 = iVar4 + 0x168;
    if (*pcVar5 != '\0') {
      iVar6 = iVar6 + 1;
      iVar1 = iVar3 * 0x168;
      pcVar5 = gOFOData + iVar1 + 1;
      wprintf("  Searching OFUSer %s ",pcVar5);
      iVar2 = Rstrcmp(pcVar5,gOFUser);
      if (iVar2 != 0) {
        wprintf(" Found OFUSer %s ",pcVar5);
        gConfig._16_4_ = *(undefined4 *)(gOFOData + iVar1 + 0x24);
        gConfig._12_4_ = *(undefined4 *)(gOFOData + iVar1 + 0x28);
        gOFORef = iVar3;
        wprintf(":OFO Imported %s OFO Data",gOFUser);
        OFOUpdate();
        goto LAB_0008dae8;
      }
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 != 0x20);
  if (gOFUser[0] == '\0') {
    wprintf(":OFO No User or last user");
    gOFORef = -1;
  }
  else {
    wprintf(":OFO Adding %s OFO Data");
    iVar3 = 0;
    iVar4 = 0;
    do {
      pcVar5 = gOFOData + iVar3;
      iVar3 = iVar3 + 0x168;
      if (*pcVar5 == '\0') {
        iVar3 = iVar4 * 0x168;
        cOFOData::Init((cOFOData *)(gOFOData + iVar3));
        gOFOData[iVar3] = 1;
        gOFORef = iVar4;
        strcpy(gOFOData + iVar3 + 1,gOFUser);
        break;
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 != 0x20);
  }
LAB_0008dae8:
  wprintf("Found %i OfUsers",iVar6);
  OFOSave();
  return;
}
