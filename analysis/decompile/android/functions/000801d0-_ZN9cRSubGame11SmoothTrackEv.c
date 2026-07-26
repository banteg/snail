/*
 * mangled: _ZN9cRSubGame11SmoothTrackEv
 * demangled: cRSubGame::SmoothTrack()
 * address: 000801d0
 * size: 1444
 */

/* cRSubGame::SmoothTrack() */

void __thiscall cRSubGame::SmoothTrack(cRSubGame *this)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  cRSubGame cVar6;
  int iVar7;
  int iVar8;
  cRSubGame *pcVar9;
  int iVar10;
  int iVar11;
  int iVar12;

  iVar2 = DAT_00080778;
  iVar4 = DAT_00080774 + 0x801ec;
  if (0 < *(int *)(this + 0x74)) {
    iVar12 = 0;
    do {
      iVar11 = iVar12 + 1;
      iVar10 = 1;
      iVar8 = 0;
      iVar1 = iVar12 * 0x240;
      pcVar9 = this + iVar1 + 0x13adc;
      do {
        pcVar9[0x31] = (cRSubGame)0x0;
        iVar3 = iVar1 + iVar8 * 0x48;
        this[iVar3 + 0x13b11] = (cRSubGame)((byte)this[iVar3 + 0x13b11] & 0x7f);
        cVar6 = pcVar9[0x30];
        if ((((cVar6 == (cRSubGame)0x23 || cVar6 == (cRSubGame)0x0) || (cVar6 == (cRSubGame)0x1c))
            || (cVar6 == (cRSubGame)0x1d)) ||
           ((cVar6 == (cRSubGame)0x1e || (cVar6 == (cRSubGame)0xe)))) goto switchD_00080300_default;
        if ((iVar8 == 0) ||
           (iVar3 = cRSubLoc::IsEmpty((cRSubLoc *)(this + iVar3 + 0x13a94)), iVar3 != 0)) {
          pcVar9[0x31] = (cRSubGame)((byte)pcVar9[0x31] | 8);
        }
        if ((iVar8 == 7) ||
           (iVar3 = cRSubLoc::IsEmpty((cRSubLoc *)(this + iVar1 + iVar10 * 0x48 + 0x13adc)),
           iVar3 != 0)) {
          pcVar9[0x31] = (cRSubGame)((byte)pcVar9[0x31] | 4);
          if (iVar12 != 0) goto LAB_000804f0;
LAB_000802d0:
          pcVar9[0x31] = (cRSubGame)((byte)pcVar9[0x31] | 1);
          if (*(int *)(this + 0x74) + -1 <= iVar12) goto LAB_000802ec;
LAB_00080520:
          iVar3 = cRSubLoc::IsEmpty((cRSubLoc *)(this + iVar11 * 0x240 + iVar8 * 0x48 + 0x13adc));
          if (iVar3 != 0) goto LAB_000802ec;
          cVar6 = pcVar9[0x31];
        }
        else {
          if (iVar12 == 0) goto LAB_000802d0;
LAB_000804f0:
          iVar3 = cRSubLoc::IsEmpty((cRSubLoc *)(this + iVar1 + iVar8 * 0x48 + 0x1389c));
          if (iVar3 != 0) goto LAB_000802d0;
          if (iVar12 < *(int *)(this + 0x74) + -1) goto LAB_00080520;
LAB_000802ec:
          cVar6 = (cRSubGame)((byte)pcVar9[0x31] | 2);
          pcVar9[0x31] = cVar6;
        }
        switch(cVar6) {
        case (cRSubGame)0x5:
          iVar3 = iVar1 + iVar8 * 0x48;
          this[iVar3 + 0x13b11] = (cRSubGame)((byte)this[iVar3 + 0x13b11] | 0x80);
          cVar6 = pcVar9[0x30];
          if (((cVar6 == (cRSubGame)0x1 || cVar6 == (cRSubGame)0x14) || (cVar6 == (cRSubGame)0x15))
             || ((cVar6 == (cRSubGame)0x1b ||
                 ((cVar6 == (cRSubGame)0x21 || (cVar6 == (cRSubGame)0x22)))))) {
            piVar5 = *(int **)(iVar4 + iVar2);
            iVar3 = iVar1 + iVar8 * 0x48;
            iVar7 = 0x43f50;
LAB_0008036c:
            cRBod::SetObject((cRBod *)(this + iVar3 + 0x13adc),*(cRObject **)(*piVar5 + iVar7));
          }
          else if (cVar6 != (cRSubGame)0x16 && cVar6 != (cRSubGame)0xe) {
            iVar7 = cRSubLoc::IsRamp((cRSubLoc *)(this + iVar3 + 0x13adc));
            if (iVar7 == 0) {
              cRBod::SetObject((cRBod *)(this + iVar3 + 0x13adc),
                               *(cRObject **)(**(int **)(iVar4 + iVar2) + 0x440b0));
              goto joined_r0x0008076c;
            }
          }
          break;
        case (cRSubGame)0x6:
          iVar3 = iVar1 + iVar8 * 0x48;
          this[iVar3 + 0x13b11] = (cRSubGame)((byte)this[iVar3 + 0x13b11] | 0x80);
          cVar6 = pcVar9[0x30];
          if ((((cVar6 != (cRSubGame)0x1 && cVar6 != (cRSubGame)0x14) && (cVar6 != (cRSubGame)0x15))
              && (cVar6 != (cRSubGame)0x1b)) &&
             ((cVar6 != (cRSubGame)0x21 && (cVar6 != (cRSubGame)0x22)))) {
            if (cVar6 != (cRSubGame)0x16 && cVar6 != (cRSubGame)0xe) {
              iVar7 = cRSubLoc::IsRamp((cRSubLoc *)(this + iVar3 + 0x13adc));
              if (iVar7 == 0) {
                cRBod::SetObject((cRBod *)(this + iVar3 + 0x13adc),
                                 *(cRObject **)(**(int **)(iVar4 + iVar2) + 0x44108));
                goto joined_r0x0008076c;
              }
            }
            break;
          }
          cRBod::SetObject((cRBod *)(this + iVar1 + iVar8 * 0x48 + 0x13adc),
                           *(cRObject **)(**(int **)(iVar4 + iVar2) + 0x43fa8));
          goto joined_r0x0008076c;
        case (cRSubGame)0x7:
          break;
        case (cRSubGame)0x8:
          break;
        case (cRSubGame)0x9:
          iVar3 = iVar1 + iVar8 * 0x48;
          this[iVar3 + 0x13b11] = (cRSubGame)((byte)this[iVar3 + 0x13b11] | 0x80);
          cVar6 = pcVar9[0x30];
          if (((cVar6 == (cRSubGame)0x1 || cVar6 == (cRSubGame)0x14) || (cVar6 == (cRSubGame)0x15))
             || ((cVar6 == (cRSubGame)0x1b ||
                 ((cVar6 == (cRSubGame)0x21 || (cVar6 == (cRSubGame)0x22)))))) {
            piVar5 = *(int **)(iVar4 + iVar2);
            iVar3 = iVar1 + iVar8 * 0x48;
            iVar7 = 0x43f24;
            goto LAB_0008036c;
          }
          if (cVar6 != (cRSubGame)0x16 && cVar6 != (cRSubGame)0xe) {
            iVar7 = cRSubLoc::IsRamp((cRSubLoc *)(this + iVar3 + 0x13adc));
            if (iVar7 == 0) {
              cRBod::SetObject((cRBod *)(this + iVar3 + 0x13adc),
                               *(cRObject **)(**(int **)(iVar4 + iVar2) + 0x44084));
              goto joined_r0x0008076c;
            }
          }
          break;
        case (cRSubGame)0xa:
          iVar3 = iVar1 + iVar8 * 0x48;
          this[iVar3 + 0x13b11] = (cRSubGame)((byte)this[iVar3 + 0x13b11] | 0x80);
          cVar6 = pcVar9[0x30];
          if ((((cVar6 == (cRSubGame)0x1 || cVar6 == (cRSubGame)0x14) || (cVar6 == (cRSubGame)0x15))
              || (cVar6 == (cRSubGame)0x1b)) ||
             ((cVar6 == (cRSubGame)0x21 || (cVar6 == (cRSubGame)0x22)))) {
            piVar5 = *(int **)(iVar4 + iVar2);
            iVar3 = iVar1 + iVar8 * 0x48;
            iVar7 = 0x43f7c;
            goto LAB_0008036c;
          }
          if (cVar6 != (cRSubGame)0x16 && cVar6 != (cRSubGame)0xe) {
            iVar7 = cRSubLoc::IsRamp((cRSubLoc *)(this + iVar3 + 0x13adc));
            if (iVar7 == 0) {
              cRBod::SetObject((cRBod *)(this + iVar3 + 0x13adc),
                               *(cRObject **)(**(int **)(iVar4 + iVar2) + 0x440dc));
              goto joined_r0x0008076c;
            }
          }
        }
switchD_00080300_default:
joined_r0x0008076c:
        iVar10 = iVar10 + 1;
        pcVar9 = pcVar9 + 0x48;
        iVar8 = iVar8 + 1;
      } while (iVar8 != 8);
      iVar12 = iVar11;
    } while (iVar11 < *(int *)(this + 0x74));
  }
  return;
}
