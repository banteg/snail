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
  char acStack_4014 [16384];
  int local_14;

  iVar2 = RShellFindFile("Data/LevelsDir.txt",false);
  if (iVar2 == 0) {
    RShellReadDirectory("Levels","*.txt",&local_14,acStack_4014);
    RShellSaveDirectory("Data/LevelsDir.txt",local_14,acStack_4014);
  }
  else {
    RShellLoadDirectory("Data/LevelsDir.txt",&local_14,acStack_4014);
  }
  if (0 < local_14) {
    iVar2 = 0;
    do {
      iVar1 = iVar2 * 0x80;
      iVar2 = iVar2 + 1;
      cRSubTracks::Init((cRSubTracks *)(Game + 0x72ee8),acStack_4014 + iVar1);
    } while (iVar2 < local_14);
  }
  return;
}
