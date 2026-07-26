/*
 * mangled: _Z12RShellPopDirv
 * demangled: RShellPopDir()
 * address: 0002c218
 * size: 48
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* RShellPopDir() */

void RShellPopDir(void)

{
  RShellDirectoryStackLevel = RShellDirectoryStackLevel - 1;
  chdir(&RShellDirectoryStack + (uint)RShellDirectoryStackLevel * 0x80);
  return;
}
