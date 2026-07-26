/*
 * mangled: _Z23MacOFAddParcelDeliveredv
 * demangled: MacOFAddParcelDelivered()
 * address: 000080a0
 * size: 128
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* MacOFAddParcelDelivered() */

void MacOFAddParcelDelivered(void)

{
  if ((&DAT_00353544)[_Game] != '\0') {
    return;
  }
  DAT_001f24ec = DAT_001f24ec + 1;
  OFSetHighScore();
  if (DAT_001f24ec == 100) {
    MacOFAddAchievement(0x20);
  }
  if (DAT_001f24ec == 500) {
    MacOFAddAchievement(0x21);
  }
  if (DAT_001f24ec != 1000) {
    return;
  }
  MacOFAddAchievement(0x22);
  return;
}
