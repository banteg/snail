/*
 * mangled: _ZN10cRSMTracks10OpenLevelsEv
 * demangled: cRSMTracks::OpenLevels()
 * address: 00038020
 * size: 192
 */

/* cRSMTracks::OpenLevels() */

void cRSMTracks::OpenLevels(void)

{
  undefined *puVar1;
  int iVar2;
  char acStack_4018 [16384];
  int local_18;

  iVar2 = RShellFindFile("Data/LevelsDir.txt",false);
  if (iVar2 == 0) {
    RShellReadDirectory("Levels","*.txt",&local_18,acStack_4018);
    RShellSaveDirectory("Data/LevelsDir.txt",local_18,acStack_4018);
  }
  else {
    RShellLoadDirectory("Data/LevelsDir.txt",&local_18,acStack_4018);
  }
  puVar1 = PTR__Game_001b60b8;
  if (0 < local_18) {
    iVar2 = 0;
    do {
      cRSubTracks::Init((cRSubTracks *)(*(int *)puVar1 + 0x73e80),acStack_4018 + iVar2 * 0x80);
      iVar2 = iVar2 + 1;
    } while (iVar2 < local_18);
  }
  return;
}
