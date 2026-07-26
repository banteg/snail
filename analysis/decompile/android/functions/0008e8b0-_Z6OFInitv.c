/*
 * mangled: _Z6OFInitv
 * demangled: OFInit()
 * address: 0008e8b0
 * size: 4
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* OFInit() */

void OFInit(void)

{
  int iVar1;
  undefined4 *puVar2;
  char *pcVar3;
  int iVar4;
  int aiStack_1c [2];

  iVar4 = 0;
  wprintf("OF Init");
  pcVar3 = (char *)RShellLoadFile("openfeint_offline_config.xml",aiStack_1c);
  pcVar3[aiStack_1c[0] + -1] = '\0';
  wprintf("OFXml FileSize=%i",aiStack_1c[0]);
  do {
    puVar2 = &OFLeaderboardNames + iVar4;
    iVar1 = iVar4 * 0x20;
    iVar4 = iVar4 + 1;
    OFGetID((char *)*puVar2,pcVar3,OFID + iVar1);
  } while (iVar4 != 0x38);
  RShellMemoryFree(pcVar3);
  return;
}
