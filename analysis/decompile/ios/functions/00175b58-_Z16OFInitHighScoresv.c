/*
 * mangled: _Z16OFInitHighScoresv
 * demangled: OFInitHighScores()
 * address: 00175b58
 * size: 56
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* OFInitHighScores() */

void OFInitHighScores(void)

{
  undefined4 *puVar1;

  puVar1 = (undefined4 *)&_OFHS;
  do {
    *(undefined1 *)puVar1 = 0x30;
    *(undefined1 *)((int)puVar1 + 1) = 0;
    puVar1[0x10] = 0;
    puVar1[0x11] = 0;
    puVar1 = puVar1 + 0x12;
  } while (puVar1 != &_OFHighScoreNumber);
  _OFHighScoreNumber = 0;
  OFLoadHighScores();
  return;
}
