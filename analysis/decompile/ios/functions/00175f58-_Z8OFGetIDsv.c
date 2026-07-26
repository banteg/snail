/*
 * mangled: _Z8OFGetIDsv
 * demangled: OFGetIDs()
 * address: 00175f58
 * size: 208
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* OFGetIDs() */

void OFGetIDs(void)

{
  char *pcVar1;
  int iVar2;
  char *pcVar3;
  char cVar4;
  undefined4 uVar5;
  int iVar6;
  char acStack_11c [256];
  int local_1c;

  pcVar1 = (char *)RShellLoadFile("openfeint_offline_config.xml",&local_1c);
  iVar6 = 0;
  pcVar1[local_1c + -1] = '\0';
  do {
    while( true ) {
      uVar5 = (&_OFLeaderboardNames)[iVar6];
      _sprintf(acStack_11c,"<name>%s</name>",uVar5);
      iVar2 = Rstrfind(acStack_11c,pcVar1);
      if (iVar2 == 0) break;
      iVar2 = Rstrfind("<id>",(char *)(iVar2 + -100));
      cVar4 = *(char *)(iVar2 + 4);
      if (cVar4 != '<') {
        pcVar3 = &_OFID + iVar6 * 0x20;
        do {
          *pcVar3 = cVar4;
          cVar4 = *(char *)(iVar2 + 5);
          iVar2 = iVar2 + 1;
          pcVar3 = pcVar3 + 1;
        } while (cVar4 != '<');
      }
      iVar6 = iVar6 + 1;
      if (iVar6 == 0x38) goto LAB_00175ff8;
    }
    iVar6 = iVar6 + 1;
    RShellError("Can\'t find %s in OF Xml",uVar5);
  } while (iVar6 != 0x38);
LAB_00175ff8:
  RShellMemoryFree(pcVar1);
  return;
}
