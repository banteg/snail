/*
 * mangled: _Z20OFAddParcelDeliveredv
 * demangled: OFAddParcelDelivered()
 * address: 0008e4f4
 * size: 196
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* OFAddParcelDelivered() */

void OFAddParcelDelivered(void)

{
  if (gDirectory[Game + 0x2544] != '\0') {
    return;
  }
  gConfig._16_4_ = gConfig._16_4_ + 1;
  OFSetHighScore();
  if (gOFORef != -1) {
    *(int *)(gOFOData + gOFORef * 0x168 + 0x24) = *(int *)(gOFOData + gOFORef * 0x168 + 0x24) + 1;
  }
  if (gConfig._16_4_ == 100) {
    OFAddAchievement(0x20);
  }
  if (gConfig._16_4_ == 500) {
    OFAddAchievement(0x21);
  }
  if (gConfig._16_4_ != 1000) {
    return;
  }
  OFAddAchievement(0x22);
  return;
}
