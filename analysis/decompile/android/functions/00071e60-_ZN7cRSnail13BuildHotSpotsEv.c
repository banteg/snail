/*
 * mangled: _ZN7cRSnail13BuildHotSpotsEv
 * demangled: cRSnail::BuildHotSpots()
 * address: 00071e60
 * size: 236
 */

/* cRSnail::BuildHotSpots() */

void __thiscall cRSnail::BuildHotSpots(cRSnail *this)

{
  cRSnail *pcVar1;
  int iVar2;
  undefined4 local_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;

  iVar2 = 0;
  pcVar1 = this + 0x1510;
  do {
    while( true ) {
      local_2c = *(undefined4 *)pcVar1;
      uStack_28 = *(undefined4 *)(pcVar1 + 4);
      uStack_24 = *(undefined4 *)(pcVar1 + 8);
      if (10 < iVar2) break;
      iVar2 = iVar2 + 1;
      tVector::operator*=((tVector *)&local_2c,*(undefined4 *)(this + 0x14c8),
                          *(undefined4 *)(this + 0x14cc),*(undefined4 *)(this + 0x14d0),
                          *(undefined4 *)(this + 0x14d4),*(undefined4 *)(this + 0x14d8),
                          *(undefined4 *)(this + 0x14dc),*(undefined4 *)(this + 0x14e0),
                          *(undefined4 *)(this + 0x14e4),*(undefined4 *)(this + 0x14e8),
                          *(undefined4 *)(this + 0x14ec),*(undefined4 *)(this + 0x14f0),
                          *(undefined4 *)(this + 0x14f4),*(undefined4 *)(this + 0x14f8),
                          *(undefined4 *)(this + 0x14fc),*(undefined4 *)(this + 0x1500),
                          *(undefined4 *)(this + 0x1504));
      *(undefined4 *)(pcVar1 + 0xe4) = local_2c;
      *(undefined4 *)(pcVar1 + 0xe8) = uStack_28;
      *(undefined4 *)(pcVar1 + 0xec) = uStack_24;
      pcVar1 = pcVar1 + 0xc;
      if (iVar2 == 0x13) {
        return;
      }
    }
    iVar2 = iVar2 + 1;
    tVector::operator*=((tVector *)&local_2c,*(undefined4 *)(this + 0x1454),
                        *(undefined4 *)(this + 0x1458),*(undefined4 *)(this + 0x145c),
                        *(undefined4 *)(this + 0x1460),*(undefined4 *)(this + 0x1464),
                        *(undefined4 *)(this + 0x1468),*(undefined4 *)(this + 0x146c),
                        *(undefined4 *)(this + 0x1470),*(undefined4 *)(this + 0x1474),
                        *(undefined4 *)(this + 0x1478),*(undefined4 *)(this + 0x147c),
                        *(undefined4 *)(this + 0x1480),*(undefined4 *)(this + 0x1484),
                        *(undefined4 *)(this + 0x1488),*(undefined4 *)(this + 0x148c),
                        *(undefined4 *)(this + 0x1490));
    *(undefined4 *)(pcVar1 + 0xe4) = local_2c;
    *(undefined4 *)(pcVar1 + 0xe8) = uStack_28;
    *(undefined4 *)(pcVar1 + 0xec) = uStack_24;
    pcVar1 = pcVar1 + 0xc;
  } while (iVar2 != 0x13);
  return;
}
