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
  cRSubGame cVar3;
  int iVar4;
  int iVar5;
  cRSubGame *pcVar6;
  int iVar7;
  int iVar8;
  int iVar9;

  if (0 < *(int *)(this + 0x74)) {
    iVar9 = 0;
    do {
      iVar8 = iVar9 + 1;
      iVar7 = 1;
      iVar5 = 0;
      iVar1 = iVar9 * 0x240;
      pcVar6 = this + iVar1 + 0x13adc;
      do {
        pcVar6[0x31] = (cRSubGame)0x0;
        iVar2 = iVar1 + iVar5 * 0x48;
        this[iVar2 + 0x13b11] = (cRSubGame)((byte)this[iVar2 + 0x13b11] & 0x7f);
        cVar3 = pcVar6[0x30];
        if ((((cVar3 == (cRSubGame)0x23 || cVar3 == (cRSubGame)0x0) || (cVar3 == (cRSubGame)0x1c))
            || (cVar3 == (cRSubGame)0x1d)) ||
           ((cVar3 == (cRSubGame)0x1e || (cVar3 == (cRSubGame)0xe)))) goto switchD_00080300_default;
        if ((iVar5 == 0) ||
           (iVar2 = cRSubLoc::IsEmpty((cRSubLoc *)(this + iVar2 + 0x13a94)), iVar2 != 0)) {
          pcVar6[0x31] = (cRSubGame)((byte)pcVar6[0x31] | 8);
        }
        if ((iVar5 == 7) ||
           (iVar2 = cRSubLoc::IsEmpty((cRSubLoc *)(this + iVar1 + iVar7 * 0x48 + 0x13adc)),
           iVar2 != 0)) {
          pcVar6[0x31] = (cRSubGame)((byte)pcVar6[0x31] | 4);
          if (iVar9 != 0) goto LAB_000804f0;
LAB_000802d0:
          pcVar6[0x31] = (cRSubGame)((byte)pcVar6[0x31] | 1);
          if (*(int *)(this + 0x74) + -1 <= iVar9) goto LAB_000802ec;
LAB_00080520:
          iVar2 = cRSubLoc::IsEmpty((cRSubLoc *)(this + iVar8 * 0x240 + iVar5 * 0x48 + 0x13adc));
          if (iVar2 != 0) goto LAB_000802ec;
          cVar3 = pcVar6[0x31];
        }
        else {
          if (iVar9 == 0) goto LAB_000802d0;
LAB_000804f0:
          iVar2 = cRSubLoc::IsEmpty((cRSubLoc *)(this + iVar1 + iVar5 * 0x48 + 0x1389c));
          if (iVar2 != 0) goto LAB_000802d0;
          if (iVar9 < *(int *)(this + 0x74) + -1) goto LAB_00080520;
LAB_000802ec:
          cVar3 = (cRSubGame)((byte)pcVar6[0x31] | 2);
          pcVar6[0x31] = cVar3;
        }
        switch(cVar3) {
        case (cRSubGame)0x5:
          iVar2 = iVar1 + iVar5 * 0x48;
          this[iVar2 + 0x13b11] = (cRSubGame)((byte)this[iVar2 + 0x13b11] | 0x80);
          cVar3 = pcVar6[0x30];
          if (((cVar3 == (cRSubGame)0x1 || cVar3 == (cRSubGame)0x14) || (cVar3 == (cRSubGame)0x15))
             || ((cVar3 == (cRSubGame)0x1b ||
                 ((cVar3 == (cRSubGame)0x21 || (cVar3 == (cRSubGame)0x22)))))) {
            iVar2 = iVar1 + iVar5 * 0x48;
            iVar4 = 0x43f50;
LAB_0008036c:
            cRBod::SetObject((cRBod *)(this + iVar2 + 0x13adc),*(cRObject **)(Game + iVar4));
          }
          else if (cVar3 != (cRSubGame)0x16 && cVar3 != (cRSubGame)0xe) {
            iVar4 = cRSubLoc::IsRamp((cRSubLoc *)(this + iVar2 + 0x13adc));
            if (iVar4 == 0) {
              cRBod::SetObject((cRBod *)(this + iVar2 + 0x13adc),*(cRObject **)(Game + 0x440b0));
              goto joined_r0x0008076c;
            }
          }
          break;
        case (cRSubGame)0x6:
          iVar2 = iVar1 + iVar5 * 0x48;
          this[iVar2 + 0x13b11] = (cRSubGame)((byte)this[iVar2 + 0x13b11] | 0x80);
          cVar3 = pcVar6[0x30];
          if ((((cVar3 != (cRSubGame)0x1 && cVar3 != (cRSubGame)0x14) && (cVar3 != (cRSubGame)0x15))
              && (cVar3 != (cRSubGame)0x1b)) &&
             ((cVar3 != (cRSubGame)0x21 && (cVar3 != (cRSubGame)0x22)))) {
            if (cVar3 != (cRSubGame)0x16 && cVar3 != (cRSubGame)0xe) {
              iVar4 = cRSubLoc::IsRamp((cRSubLoc *)(this + iVar2 + 0x13adc));
              if (iVar4 == 0) {
                cRBod::SetObject((cRBod *)(this + iVar2 + 0x13adc),*(cRObject **)(Game + 0x44108));
                goto joined_r0x0008076c;
              }
            }
            break;
          }
          cRBod::SetObject((cRBod *)(this + iVar1 + iVar5 * 0x48 + 0x13adc),
                           *(cRObject **)(Game + 0x43fa8));
          goto joined_r0x0008076c;
        case (cRSubGame)0x7:
          break;
        case (cRSubGame)0x8:
          break;
        case (cRSubGame)0x9:
          iVar2 = iVar1 + iVar5 * 0x48;
          this[iVar2 + 0x13b11] = (cRSubGame)((byte)this[iVar2 + 0x13b11] | 0x80);
          cVar3 = pcVar6[0x30];
          if (((cVar3 == (cRSubGame)0x1 || cVar3 == (cRSubGame)0x14) || (cVar3 == (cRSubGame)0x15))
             || ((cVar3 == (cRSubGame)0x1b ||
                 ((cVar3 == (cRSubGame)0x21 || (cVar3 == (cRSubGame)0x22)))))) {
            iVar2 = iVar1 + iVar5 * 0x48;
            iVar4 = 0x43f24;
            goto LAB_0008036c;
          }
          if (cVar3 != (cRSubGame)0x16 && cVar3 != (cRSubGame)0xe) {
            iVar4 = cRSubLoc::IsRamp((cRSubLoc *)(this + iVar2 + 0x13adc));
            if (iVar4 == 0) {
              cRBod::SetObject((cRBod *)(this + iVar2 + 0x13adc),*(cRObject **)(Game + 0x44084));
              goto joined_r0x0008076c;
            }
          }
          break;
        case (cRSubGame)0xa:
          iVar2 = iVar1 + iVar5 * 0x48;
          this[iVar2 + 0x13b11] = (cRSubGame)((byte)this[iVar2 + 0x13b11] | 0x80);
          cVar3 = pcVar6[0x30];
          if ((((cVar3 == (cRSubGame)0x1 || cVar3 == (cRSubGame)0x14) || (cVar3 == (cRSubGame)0x15))
              || (cVar3 == (cRSubGame)0x1b)) ||
             ((cVar3 == (cRSubGame)0x21 || (cVar3 == (cRSubGame)0x22)))) {
            iVar2 = iVar1 + iVar5 * 0x48;
            iVar4 = 0x43f7c;
            goto LAB_0008036c;
          }
          if (cVar3 != (cRSubGame)0x16 && cVar3 != (cRSubGame)0xe) {
            iVar4 = cRSubLoc::IsRamp((cRSubLoc *)(this + iVar2 + 0x13adc));
            if (iVar4 == 0) {
              cRBod::SetObject((cRBod *)(this + iVar2 + 0x13adc),*(cRObject **)(Game + 0x440dc));
              goto joined_r0x0008076c;
            }
          }
        }
switchD_00080300_default:
joined_r0x0008076c:
        iVar7 = iVar7 + 1;
        pcVar6 = pcVar6 + 0x48;
        iVar5 = iVar5 + 1;
      } while (iVar5 != 8);
      iVar9 = iVar8;
    } while (iVar8 < *(int *)(this + 0x74));
  }
  return;
}
