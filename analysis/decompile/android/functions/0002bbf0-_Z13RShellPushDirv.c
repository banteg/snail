/*
 * mangled: _Z13RShellPushDirv
 * demangled: RShellPushDir()
 * address: 0002bbf0
 * size: 60
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* RShellPushDir() */

void RShellPushDir(void)

{
  getcwd(&RShellDirectoryStack + (uint)RShellDirectoryStackLevel * 0x80,0x80);
  RShellDirectoryStackLevel = RShellDirectoryStackLevel + 1;
  return;
}
