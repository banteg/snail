/*
 * mangled: _Z19MacOFSaveHighScoresv
 * demangled: MacOFSaveHighScores()
 * address: 00007714
 * size: 32
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* MacOFSaveHighScores() */

void MacOFSaveHighScores(void)

{
  if (_gMacLoadedHighscores == '\0') {
    return;
  }
  OFSaveHighScores();
  return;
}
