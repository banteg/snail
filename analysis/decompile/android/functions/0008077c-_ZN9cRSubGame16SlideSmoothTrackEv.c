/*
 * mangled: _ZN9cRSubGame16SlideSmoothTrackEv
 * demangled: cRSubGame::SlideSmoothTrack()
 * address: 0008077c
 * size: 1904
 */

/* cRSubGame::SlideSmoothTrack() */

void __thiscall cRSubGame::SlideSmoothTrack(cRSubGame *this)

{
  bool bVar1;
  int iVar2;
  cRSubGame cVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  cRSubGame *pcVar9;
  int iVar10;
  int iVar11;
  int *piVar12;
  int iVar13;
  int local_4c;
  int local_3c;

  iVar4 = DAT_00080ef0;
  iVar5 = DAT_00080eec + 0x80798;
  if (1 < *(int *)(this + 0x74)) {
    local_3c = -1;
    local_4c = 1;
    do {
      iVar13 = 0;
      uVar6 = local_4c - 1;
      iVar2 = uVar6 * 0x240;
      pcVar9 = this + iVar2 + 0x13adc;
      do {
        if ((uVar6 & 7) == 3) {
          iVar10 = iVar13 * 0x48;
          iVar8 = iVar10 + iVar2;
          if (((byte)this[iVar8 + 0x13b10] & 0x20) == 0) {
            if (((byte)this[iVar10 + local_4c * 0x240 + 0x13b10] & 0x20) == 0) {
              iVar11 = cRSubLoc::IsFloor((cRSubLoc *)(this + iVar8 + 0x13adc));
              if (iVar11 == 0) {
                cVar3 = this[iVar8 + 0x13b10];
              }
              else {
                iVar8 = cRSubLoc::IsSlide((cRSubLoc *)(this + local_4c * 0x240 + iVar10 + 0x13adc));
                if ((iVar8 == 0) && (pcVar9[0x270] != (cRSubGame)0x1e)) {
                  iVar10 = uVar6 * 0x240 + iVar10;
                }
                else {
                  iVar10 = *(int *)(pcVar9 + 0x24);
                  if (iVar10 == *(int *)(**(int **)(iVar5 + iVar4) + 0x44370)) {
                    iVar10 = iVar13 * 0x48 + uVar6 * 0x240;
                    cRBod::SetObject((cRBod *)(this + iVar10 + 0x13adc),
                                     *(cRObject **)(**(int **)(iVar5 + iVar4) + 0x44630));
                    this[iVar10 + 0x13b10] = (cRSubGame)((byte)this[iVar10 + 0x13b10] | 0x40);
                    iVar10 = *(int *)(pcVar9 + 0x24);
                  }
                  iVar11 = 5;
                  iVar8 = iVar2 + iVar13 * 0x48;
                  piVar12 = *(int **)(iVar5 + iVar4);
                  while( true ) {
                    iVar7 = iVar11 * 0x2c + *piVar12;
                    iVar11 = iVar11 + 1;
                    if (iVar10 == *(int *)(iVar7 + 0x43e48)) {
                      cRBod::SetObject((cRBod *)(this + iVar8 + 0x13adc),
                                       *(cRObject **)(iVar7 + 0x43fa8));
                      this[iVar8 + 0x13b10] = (cRSubGame)((byte)this[iVar8 + 0x13b10] | 0x40);
                    }
                    if (iVar11 == 9) break;
                    iVar10 = *(int *)(pcVar9 + 0x24);
                  }
                  iVar10 = iVar2 + iVar13 * 0x48;
                }
                cVar3 = this[iVar10 + 0x13b10];
              }
              if (((byte)cVar3 & 0x3f) >> 5 != 0) goto LAB_000808ac;
            }
            iVar10 = iVar13 * 0x48;
            if (((((byte)this[iVar10 + local_4c * 0x240 + 0x13b10] & 0x20) == 0) &&
                (iVar8 = cRSubLoc::IsSlide((cRSubLoc *)(this + iVar10 + iVar2 + 0x13adc)),
                iVar8 != 0)) &&
               (iVar8 = cRSubLoc::IsFloor((cRSubLoc *)(this + local_4c * 0x240 + iVar10 + 0x13adc)),
               iVar8 != 0)) {
              iVar8 = *(int *)(pcVar9 + 0x24);
              if (iVar8 == *(int *)(**(int **)(iVar5 + iVar4) + 0x44630)) {
                iVar10 = uVar6 * 0x240 + iVar10;
                cRBod::SetObject((cRBod *)(this + iVar10 + 0x13adc),
                                 *(cRObject **)(**(int **)(iVar5 + iVar4) + 0x44370));
                this[iVar10 + 0x13b10] = (cRSubGame)((byte)this[iVar10 + 0x13b10] | 0x40);
                iVar8 = *(int *)(pcVar9 + 0x24);
              }
              iVar11 = 0xd;
              iVar10 = iVar2 + iVar13 * 0x48;
              piVar12 = *(int **)(iVar5 + iVar4);
              while( true ) {
                iVar7 = iVar11 * 0x2c + *piVar12;
                iVar11 = iVar11 + 1;
                if (iVar8 == *(int *)(iVar7 + 0x43e48)) {
                  cRBod::SetObject((cRBod *)(this + iVar10 + 0x13adc),
                                   *(cRObject **)(iVar7 + 0x43ce8));
                  this[iVar10 + 0x13b10] = (cRSubGame)((byte)this[iVar10 + 0x13b10] | 0x40);
                }
                if (iVar11 == 0x11) break;
                iVar8 = *(int *)(pcVar9 + 0x24);
              }
            }
          }
        }
        else if ((uVar6 & 7) == 5) {
          iVar10 = iVar13 * 0x48;
          iVar8 = iVar10 + iVar2;
          if (((byte)this[iVar8 + 0x13b10] & 0x20) == 0) {
            if (((byte)this[iVar10 + local_3c * 0x240 + 0x13b10] & 0x20) == 0) {
              iVar11 = cRSubLoc::IsFloor((cRSubLoc *)(this + iVar8 + 0x13adc));
              if (iVar11 == 0) {
                cVar3 = this[iVar8 + 0x13b10];
              }
              else {
                iVar8 = cRSubLoc::IsSlide((cRSubLoc *)(this + local_3c * 0x240 + iVar10 + 0x13adc));
                if ((iVar8 == 0) && (pcVar9[-0x210] != (cRSubGame)0x20)) {
                  iVar10 = uVar6 * 0x240 + iVar10;
                }
                else {
                  iVar10 = *(int *)(pcVar9 + 0x24);
                  if (iVar10 == *(int *)(**(int **)(iVar5 + iVar4) + 0x44370)) {
                    iVar10 = iVar13 * 0x48 + uVar6 * 0x240;
                    cRBod::SetObject((cRBod *)(this + iVar10 + 0x13adc),
                                     *(cRObject **)(**(int **)(iVar5 + iVar4) + 0x44630));
                    this[iVar10 + 0x13b10] = (cRSubGame)((byte)this[iVar10 + 0x13b10] | 0x40);
                    iVar10 = *(int *)(pcVar9 + 0x24);
                  }
                  iVar11 = 5;
                  iVar8 = iVar2 + iVar13 * 0x48;
                  piVar12 = *(int **)(iVar5 + iVar4);
                  while( true ) {
                    iVar7 = iVar11 * 0x2c + *piVar12;
                    iVar11 = iVar11 + 1;
                    if (iVar10 == *(int *)(iVar7 + 0x43e48)) {
                      cRBod::SetObject((cRBod *)(this + iVar8 + 0x13adc),
                                       *(cRObject **)(iVar7 + 0x43fa8));
                      this[iVar8 + 0x13b10] = (cRSubGame)((byte)this[iVar8 + 0x13b10] | 0x40);
                    }
                    if (iVar11 == 9) break;
                    iVar10 = *(int *)(pcVar9 + 0x24);
                  }
                  iVar10 = iVar2 + iVar13 * 0x48;
                }
                cVar3 = this[iVar10 + 0x13b10];
              }
              if (((byte)cVar3 & 0x3f) >> 5 != 0) goto LAB_000808ac;
            }
            iVar10 = iVar13 * 0x48;
            if (((((byte)this[iVar10 + local_3c * 0x240 + 0x13b10] & 0x20) == 0) &&
                (iVar8 = cRSubLoc::IsSlide((cRSubLoc *)(this + iVar10 + iVar2 + 0x13adc)),
                iVar8 != 0)) &&
               (iVar8 = cRSubLoc::IsFloor((cRSubLoc *)(this + local_3c * 0x240 + iVar10 + 0x13adc)),
               iVar8 != 0)) {
              iVar8 = *(int *)(pcVar9 + 0x24);
              if (iVar8 == *(int *)(**(int **)(iVar5 + iVar4) + 0x44630)) {
                iVar10 = uVar6 * 0x240 + iVar10;
                cRBod::SetObject((cRBod *)(this + iVar10 + 0x13adc),
                                 *(cRObject **)(**(int **)(iVar5 + iVar4) + 0x44370));
                this[iVar10 + 0x13b10] = (cRSubGame)((byte)this[iVar10 + 0x13b10] | 0x40);
                iVar8 = *(int *)(pcVar9 + 0x24);
              }
              iVar11 = 0xd;
              iVar10 = iVar2 + iVar13 * 0x48;
              piVar12 = *(int **)(iVar5 + iVar4);
              while( true ) {
                iVar7 = iVar11 * 0x2c + *piVar12;
                iVar11 = iVar11 + 1;
                if (iVar8 == *(int *)(iVar7 + 0x43e48)) {
                  cRBod::SetObject((cRBod *)(this + iVar10 + 0x13adc),
                                   *(cRObject **)(iVar7 + 0x43ce8));
                  this[iVar10 + 0x13b10] = (cRSubGame)((byte)this[iVar10 + 0x13b10] | 0x40);
                }
                if (iVar11 == 0x11) break;
                iVar8 = *(int *)(pcVar9 + 0x24);
              }
            }
          }
        }
LAB_000808ac:
        iVar13 = iVar13 + 1;
        pcVar9 = pcVar9 + 0x48;
      } while (iVar13 != 8);
      local_3c = local_3c + 1;
      bVar1 = local_4c < *(int *)(this + 0x74) + -1;
      local_4c = local_4c + 1;
    } while (bVar1);
  }
  return;
}
