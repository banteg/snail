/*
 * mangled: _Z7OFOSavev
 * demangled: OFOSave()
 * address: 0008d6d8
 * size: 52
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* OFOSave() */

void OFOSave(void)

{
  if (gOFOValid == '\0') {
    return;
  }
  gRegisterSaveFile("of.cfg",gOFOData,0x2d00);
  return;
}
