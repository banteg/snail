/*
 * mangled: _ZN10cRSMTracks10OpenLevelsEv
 * demangled: cRSMTracks::OpenLevels()
 * address: 0008658c
 * size: 228
 */

/* cRSMTracks::OpenLevels() */

void cRSMTracks::OpenLevels(void)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  char *pcVar4;
  char acStack_4014 [16384];
  int local_14;

  iVar2 = DAT_00086670 + 0x865a4;
  pcVar4 = (char *)(iVar2 + DAT_00086674);
  iVar1 = RShellFindFile(pcVar4,false);
  if (iVar1 == 0) {
    RShellReadDirectory((char *)(iVar2 + DAT_0008667c),(char *)(iVar2 + DAT_00086680),&local_14,
                        acStack_4014);
    RShellSaveDirectory(pcVar4,local_14,acStack_4014);
  }
  else {
    RShellLoadDirectory(pcVar4,&local_14,acStack_4014);
  }
  if (0 < local_14) {
    iVar1 = 0;
    piVar3 = *(int **)(iVar2 + DAT_00086678);
    do {
      iVar2 = iVar1 * 0x80;
      iVar1 = iVar1 + 1;
      cRSubTracks::Init((cRSubTracks *)(*piVar3 + 0x72ee8),acStack_4014 + iVar2);
    } while (iVar1 < local_14);
  }
  return;
}
