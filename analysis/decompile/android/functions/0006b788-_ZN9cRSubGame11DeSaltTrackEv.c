/*
 * mangled: _ZN9cRSubGame11DeSaltTrackEv
 * demangled: cRSubGame::DeSaltTrack()
 * address: 0006b788
 * size: 320
 */

/* cRSubGame::DeSaltTrack() */

void __thiscall cRSubGame::DeSaltTrack(cRSubGame *this)

{
  cRSubGame cVar1;
  cRSubGame *pcVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  bool bVar9;

  iVar6 = *(int *)(this + 0x74);
  if (1 < iVar6) {
    iVar7 = 0;
    do {
      iVar8 = -1;
      iVar3 = 0;
      pcVar2 = this + iVar7 * 0x240 + 0x13adc;
      do {
        while( true ) {
          cVar1 = pcVar2[0x30];
          bVar9 = 0x16 < (byte)cVar1;
          if (cVar1 != (cRSubGame)0x17) {
            bVar9 = 0xb < (byte)((char)cVar1 - 2U);
          }
          if (((bVar9 && (cVar1 != (cRSubGame)0x17 && (byte)((char)cVar1 - 2U) != 0xc)) &&
              (cVar1 != (cRSubGame)0x19)) && (cVar1 != (cRSubGame)0x21)) break;
          iVar4 = 0;
          iVar5 = iVar7;
          do {
            if ((-1 < iVar5) && (iVar5 < iVar6 + -1)) {
              iVar6 = iVar8 * 0x48 + iVar5 * 0x240;
              if (iVar8 != -1) {
                this[iVar6 + 0x13b10] = (cRSubGame)((byte)this[iVar6 + 0x13b10] & 0xe7 | 0x18);
                iVar6 = *(int *)(this + 0x74);
                if (iVar6 + -1 <= iVar5) goto LAB_0006b864;
              }
              iVar6 = iVar3 * 0x48 + iVar5 * 0x240;
              this[iVar6 + 0x13b10] = (cRSubGame)((byte)this[iVar6 + 0x13b10] & 0xe7 | 0x18);
              iVar6 = *(int *)(this + 0x74);
            }
LAB_0006b864:
            iVar4 = iVar4 + -1;
            iVar5 = iVar5 + -1;
          } while (iVar4 != -6);
          iVar3 = iVar3 + 1;
          pcVar2 = pcVar2 + 0x48;
          iVar8 = iVar8 + 1;
          if (iVar3 == 8) goto LAB_0006b888;
        }
        iVar3 = iVar3 + 1;
        pcVar2 = pcVar2 + 0x48;
        iVar8 = iVar8 + 1;
      } while (iVar3 != 8);
LAB_0006b888:
      iVar7 = iVar7 + 1;
    } while (iVar7 < iVar6 + -1);
  }
  return;
}
