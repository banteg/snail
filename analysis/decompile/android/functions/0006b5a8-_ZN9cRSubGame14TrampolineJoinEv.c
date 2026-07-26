/*
 * mangled: _ZN9cRSubGame14TrampolineJoinEv
 * demangled: cRSubGame::TrampolineJoin()
 * address: 0006b5a8
 * size: 480
 */

/* cRSubGame::TrampolineJoin() */

void __thiscall cRSubGame::TrampolineJoin(cRSubGame *this)

{
  cRSubGame *pcVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  cRSubGame *pcVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  cRSubGame *pcVar11;
  int iVar12;

  iVar4 = *(int *)(this + 0x74);
  iVar9 = 0;
  do {
    if (iVar4 <= iVar9) {
      return;
    }
    iVar2 = 0;
    iVar12 = iVar9 * 0x240;
    pcVar11 = this + iVar12 + 0x13adc;
    do {
      while ((pcVar11[0x30] != (cRSubGame)0x16 ||
             ((((byte)this[iVar2 * 0x48 + iVar9 * 0x240 + 0x13b11] & 0x20) == 0 &&
              (((byte)this[iVar2 * 0x48 + iVar12 + 0x13b11] & 0x40) == 0))))) {
LAB_0006b5f0:
        iVar2 = iVar2 + 1;
        pcVar11 = pcVar11 + 0x48;
        if (iVar2 == 8) goto LAB_0006b74c;
      }
      iVar10 = iVar2;
      if (iVar2 < 8) {
        pcVar5 = this + iVar2 * 0x48 + iVar12 + 0x13adc;
        do {
          iVar10 = iVar10 + 1;
          if (7 < iVar10) break;
          pcVar1 = pcVar5 + 0x78;
          pcVar5 = pcVar5 + 0x48;
        } while (*pcVar1 == (cRSubGame)0x16);
      }
      iVar8 = iVar9;
      if (iVar9 < *(int *)(this + 0x74)) {
        pcVar5 = this + iVar2 * 0x48 + iVar12 + 0x13adc;
        do {
          iVar8 = iVar8 + 1;
          if (*(int *)(this + 0x74) <= iVar8) break;
          pcVar1 = pcVar5 + 0x270;
          pcVar5 = pcVar5 + 0x240;
        } while (*pcVar1 == (cRSubGame)0x16);
      }
      iVar8 = iVar8 + -1;
      if (iVar8 < iVar9) goto LAB_0006b5f0;
      do {
        if (iVar2 <= iVar10 + -1) {
          iVar6 = iVar10 + -1;
          do {
            iVar7 = iVar6 + -1;
            iVar3 = iVar8 * 0x240 + iVar6 * 0x48;
            if (iVar6 != iVar2 || iVar9 != iVar8) {
              this[iVar3 + 0x13b11] = (cRSubGame)((byte)this[iVar3 + 0x13b11] & 0x9f);
            }
            iVar6 = iVar7;
          } while (iVar2 <= iVar7);
        }
        iVar8 = iVar8 + -1;
      } while (iVar9 <= iVar8);
      iVar2 = iVar2 + 1;
      pcVar11 = pcVar11 + 0x48;
    } while (iVar2 != 8);
LAB_0006b74c:
    iVar9 = iVar9 + 1;
  } while( true );
}
