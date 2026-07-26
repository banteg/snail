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
  int *piVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  cRSubGame *pcVar10;
  int iVar11;
  int iVar12;
  int iVar13;

  iVar1 = DAT_00081118;
  iVar11 = DAT_00081114 + 0x80f14;
  if (1 < *(int *)(this + 0x74)) {
    iVar3 = 0;
    do {
      iVar4 = iVar3 + 1;
      iVar9 = 0;
      iVar3 = iVar3 * 0x240;
      pcVar10 = this + iVar3 + 0x13adc;
      do {
        iVar7 = iVar9 * 0x48 + iVar3;
        this[iVar7 + 0x13b10] = (cRSubGame)((byte)this[iVar7 + 0x13b10] & 0xdf);
        iVar2 = cRSubLoc::IsEmpty((cRSubLoc *)(this + iVar9 * 0x48 + iVar4 * 0x240 + 0x13adc));
        if (iVar2 != 0) {
          iVar2 = *(int *)(pcVar10 + 0x24);
          iVar8 = 0x1e;
          iVar5 = **(int **)(iVar11 + iVar1);
          do {
            while ((iVar12 = iVar8 * 0x2c + iVar5, *(int *)(iVar12 + 0x43e48) == iVar2 ||
                   (*(int *)(iVar12 + 0x44108) == iVar2))) {
              iVar2 = iVar8 * 0x2c;
              iVar8 = iVar8 + 1;
              cRBod::SetObject((cRBod *)(this + iVar7 + 0x13adc),
                               *(cRObject **)(iVar2 + iVar5 + 0x43fa8));
              piVar6 = *(int **)(iVar11 + iVar1);
              this[iVar7 + 0x13b10] = (cRSubGame)((byte)this[iVar7 + 0x13b10] | 0x20);
              iVar5 = *piVar6;
              iVar2 = *(int *)(pcVar10 + 0x24);
              if (iVar8 == 0x26) goto LAB_00081044;
            }
            iVar8 = iVar8 + 1;
          } while (iVar8 != 0x26);
LAB_00081044:
          iVar8 = 5;
          iVar12 = iVar3 + iVar9 * 0x48;
          while( true ) {
            iVar13 = iVar8 * 0x2c + iVar5;
            if ((*(int *)(iVar13 + 0x43e48) == iVar2) || (*(int *)(iVar13 + 0x43fa8) == iVar2)) {
              cRBod::SetObject((cRBod *)(this + iVar7 + 0x13adc),
                               *(cRObject **)(iVar8 * 0x2c + iVar5 + 0x43ef8));
              this[iVar12 + 0x13b10] = (cRSubGame)((byte)this[iVar12 + 0x13b10] | 0x20);
            }
            iVar8 = iVar8 + 1;
            if (iVar8 == 9) break;
            iVar2 = *(int *)(pcVar10 + 0x24);
            iVar5 = **(int **)(iVar11 + iVar1);
          }
        }
        iVar9 = iVar9 + 1;
        pcVar10 = pcVar10 + 0x48;
      } while (iVar9 != 8);
      iVar3 = iVar4;
    } while (iVar4 < *(int *)(this + 0x74) + -1);
  }
  return;
}
