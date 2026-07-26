/*
 * mangled: _Z10RShellInitv
 * demangled: RShellInit()
 * address: 0000db30
 * size: 200
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* RShellInit() */

undefined4 RShellInit(void)

{
  int iVar1;

  _RShellDirectoryStackLevel = 0;
  _RShellMallocCount = 0;
  _RShellMemory = 0;
  DAT_0023a638 = 0;
  _gRShellKeyRepeatLife = 0;
  _gRShellKeyRepeatLifeRate = 0;
  _gRShellOldKey = 0;
  iVar1 = RShellDatInit("iSM.dat");
  if (iVar1 != 0) {
    _RShellSoundCount = 0;
    _RShellScratch = _malloc(0x500000);
    _RShellMusicMemoryBuffer = _malloc(0x64000);
    DAT_00266574 = 0;
    DAT_00266578 = 0;
    DAT_0026657c = 0;
    DAT_00266588 = *(float *)PTR__gG0ScreenWidth_001b610c * 0.5;
    DAT_00266590 = 0;
    DAT_0026658c = *(float *)PTR__gG0ScreenHeight_001b6114 * 0.5;
    return 1;
  }
  return 0;
}
