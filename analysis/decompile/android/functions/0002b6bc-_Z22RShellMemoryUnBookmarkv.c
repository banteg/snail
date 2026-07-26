/*
 * mangled: _Z22RShellMemoryUnBookmarkv
 * demangled: RShellMemoryUnBookmark()
 * address: 0002b6bc
 * size: 80
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* RShellMemoryUnBookmark() */

void RShellMemoryUnBookmark(void)

{
  if ((int)RShellMemory._0_4_ <= (int)RShellMemory._8_4_) {
    return;
  }
  do {
    RShellMemoryFree((void *)(*(int *)(RShellMemory + (RShellMemory._0_4_ + -1) * 0xc + 0x10) + 8));
  } while ((int)RShellMemory._8_4_ < (int)RShellMemory._0_4_);
  return;
}
