/*
 * mangled: _ZN9cRSubGame9WarnTrackEv
 * demangled: cRSubGame::WarnTrack()
 * address: 00080ef4
 * size: 544
 */

/* cRSubGame::WarnTrack() */

void __thiscall cRSubGame::WarnTrack(cRSubGame *this)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  cRSubGame *pcVar8;
  int iVar9;
  int iVar10;

  if (1 < *(int *)(this + 0x74)) {
    iVar3 = 0;
    do {
      iVar4 = iVar3 + 1;
      iVar7 = 0;
      iVar3 = iVar3 * 0x240;
      pcVar8 = this + iVar3 + 0x13adc;
      do {
        iVar5 = iVar7 * 0x48 + iVar3;
        this[iVar5 + 0x13b10] = (cRSubGame)((byte)this[iVar5 + 0x13b10] & 0xdf);
        iVar1 = cRSubLoc::IsEmpty((cRSubLoc *)(this + iVar7 * 0x48 + iVar4 * 0x240 + 0x13adc));
        if (iVar1 != 0) {
          iVar2 = *(int *)(pcVar8 + 0x24);
          iVar6 = 0x1e;
          iVar1 = Game;
          do {
            while ((iVar9 = iVar6 * 0x2c + iVar1, *(int *)(iVar9 + 0x43e48) == iVar2 ||
                   (*(int *)(iVar9 + 0x44108) == iVar2))) {
              iVar2 = iVar6 * 0x2c;
              iVar6 = iVar6 + 1;
              cRBod::SetObject((cRBod *)(this + iVar5 + 0x13adc),
                               *(cRObject **)(iVar2 + iVar1 + 0x43fa8));
              this[iVar5 + 0x13b10] = (cRSubGame)((byte)this[iVar5 + 0x13b10] | 0x20);
              iVar2 = *(int *)(pcVar8 + 0x24);
              iVar1 = Game;
              if (iVar6 == 0x26) goto LAB_00081044;
            }
            iVar6 = iVar6 + 1;
          } while (iVar6 != 0x26);
LAB_00081044:
          iVar6 = 5;
          iVar9 = iVar3 + iVar7 * 0x48;
          while( true ) {
            iVar10 = iVar6 * 0x2c + iVar1;
            if ((*(int *)(iVar10 + 0x43e48) == iVar2) || (*(int *)(iVar10 + 0x43fa8) == iVar2)) {
              cRBod::SetObject((cRBod *)(this + iVar5 + 0x13adc),
                               *(cRObject **)(iVar6 * 0x2c + iVar1 + 0x43ef8));
              this[iVar9 + 0x13b10] = (cRSubGame)((byte)this[iVar9 + 0x13b10] | 0x20);
            }
            iVar6 = iVar6 + 1;
            if (iVar6 == 9) break;
            iVar2 = *(int *)(pcVar8 + 0x24);
            iVar1 = Game;
          }
        }
        iVar7 = iVar7 + 1;
        pcVar8 = pcVar8 + 0x48;
      } while (iVar7 != 8);
      iVar3 = iVar4;
    } while (iVar4 < *(int *)(this + 0x74) + -1);
  }
  return;
}
