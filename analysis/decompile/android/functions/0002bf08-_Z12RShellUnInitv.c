/*
 * mangled: _Z12RShellUnInitv
 * demangled: RShellUnInit()
 * address: 0002bf08
 * size: 80
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* RShellUnInit() */

void RShellUnInit(void)

{
  RShellMemoryFree(RShellScratch);
  if (gDat != 0) {
    fclose(gDatFP);
  }
  gDat = 0;
  return;
}
