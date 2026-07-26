/*
 * mangled: _Z10OFODisplayv
 * demangled: OFODisplay()
 * address: 0008d494
 * size: 520
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* OFODisplay() */

void OFODisplay(void)

{
  char cVar1;
  char *pcVar2;
  int extraout_r1;
  int extraout_r1_00;
  int extraout_r1_01;
  int iVar3;
  int iVar4;
  int iVar5;

  wprintf("******************");
  wprintf("* OFO User %s *",gOFUser);
  wprintf("******************");
  if (gOFORef == -1) {
    wprintf(" NOONE LOGGED IN");
    return;
  }
  wprintf(" Parcel Count %i",*(undefined4 *)(gOFOData + gOFORef * 0x168 + 0x24));
  wprintf(" Slug Count %i",*(undefined4 *)(gOFOData + gOFORef * 0x168 + 0x28));
  iVar3 = gOFORef;
  iVar5 = 0;
  do {
    while( true ) {
      cVar1 = gOFOData[iVar3 * 0x168 + iVar5 + 0x10c];
      pcVar2 = " Leaderboard %i VALID %i";
      if (cVar1 != '\x01') break;
LAB_0008d5ac:
      iVar4 = iVar5 + 1;
      wprintf(pcVar2,iVar5,*(undefined4 *)(gOFOData + (iVar3 * 0x5a + iVar5) * 4 + 0x2c));
      iVar3 = gOFORef;
      iVar5 = iVar4;
      if (iVar4 == 0x38) goto LAB_0008d5cc;
    }
    if (cVar1 == '\0') {
      wprintf(" Leaderboard %i INVALID",iVar5);
      iVar3 = gOFORef;
    }
    else {
      pcVar2 = " Leaderboard %i SUBMITTED %i";
      if (cVar1 == '\x02') goto LAB_0008d5ac;
    }
    iVar5 = iVar5 + 1;
  } while (iVar5 != 0x38);
LAB_0008d5cc:
  iVar5 = 0;
  while( true ) {
    cVar1 = gOFOData[iVar3 * 0x168 + iVar5 + 0x144];
    if (cVar1 == '\x01') {
      wprintf(" Achievement %i VALID",iVar5);
      iVar3 = extraout_r1_00;
    }
    else if (cVar1 == '\0') {
      wprintf(" Achievement %i INVALID",iVar5);
      iVar3 = extraout_r1;
    }
    else {
      iVar3 = iVar5;
      if (cVar1 == '\x02') {
        wprintf(" Achievement %i SUBMITTED",iVar5);
        iVar3 = extraout_r1_01;
      }
    }
    if (iVar5 == 0x22) break;
    iVar5 = iVar5 + 1;
    iVar3 = gOFORef;
  }
  wprintf("******************",iVar3);
  return;
}
