/*
 * mangled: _Z10RShellInitv
 * demangled: RShellInit()
 * address: 0002b718
 * size: 240
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* RShellInit() */

undefined4 RShellInit(void)

{
  RShellDirectoryStackLevel = 0;
  RShellMallocCount = 0;
  cRShellMemory::Init((cRShellMemory *)RShellMemory);
  RShellMusicInit();
  gRShellKeyRepeatLife = 0;
  gRShellOldKey = 0;
  gRShellKeyRepeatLifeRate = 0;
  RShellSoundInit();
  RShellScratch = RShellMemoryMalloc(0x200000,"Scratch Pad");
  RShellMusicMemoryBuffer = RShellMemoryMalloc(0x64000,"Music Memory Buffer");
  RShellInput._48_4_ = 0;
  RShellInput._20_4_ = 0;
  RShellInput._24_4_ = 0;
  RShellInput._40_4_ = gG0ScreenWidth * 0.5;
  RShellInput._28_4_ = 0;
  RShellInput._44_4_ = gG0ScreenHeight * 0.5;
  return 1;
}
