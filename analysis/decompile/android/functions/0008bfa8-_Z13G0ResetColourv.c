/*
 * mangled: _Z13G0ResetColourv
 * demangled: G0ResetColour()
 * address: 0008bfa8
 * size: 44
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* G0ResetColour() */

void G0ResetColour(void)

{
  tColourSmall atStack_c [4];

  tColourSmall::tColourSmall(atStack_c);
  tColourSmall::White(atStack_c);
  G0SetColour(atStack_c);
  return;
}
