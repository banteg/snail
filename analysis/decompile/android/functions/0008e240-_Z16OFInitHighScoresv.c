/*
 * mangled: _Z16OFInitHighScoresv
 * demangled: OFInitHighScores()
 * address: 0008e240
 * size: 84
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* OFInitHighScores() */

void OFInitHighScores(void)

{
  undefined1 *puVar1;

  puVar1 = OFHS;
  do {
    *puVar1 = 0x30;
    *(undefined1 *)((int)puVar1 + 1) = 0;
    *(undefined4 *)((int)puVar1 + 0x40) = 0;
    *(undefined4 *)((int)puVar1 + 0x44) = 0;
    puVar1 = (undefined1 *)((int)puVar1 + 0x48);
  } while ((undefined4 *)puVar1 != &OFHighScoreNumber);
  OFHighScoreNumber = 0;
  OFLoadHighScores();
  return;
}
