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
  uint uVar4;
  int iVar5;
  int iVar6;
  cRSubGame *pcVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int local_4c;
  int local_3c;

  if (1 < *(int *)(this + 0x74)) {
    local_3c = -1;
    local_4c = 1;
    do {
      iVar10 = 0;
      uVar4 = local_4c - 1;
      iVar2 = uVar4 * 0x240;
      pcVar7 = this + iVar2 + 0x13adc;
      do {
        if ((uVar4 & 7) == 3) {
          iVar8 = iVar10 * 0x48;
          iVar6 = iVar8 + iVar2;
          if (((byte)this[iVar6 + 0x13b10] & 0x20) == 0) {
            if (((byte)this[iVar8 + local_4c * 0x240 + 0x13b10] & 0x20) == 0) {
              iVar9 = cRSubLoc::IsFloor((cRSubLoc *)(this + iVar6 + 0x13adc));
              if (iVar9 == 0) {
                cVar3 = this[iVar6 + 0x13b10];
              }
              else {
                iVar6 = cRSubLoc::IsSlide((cRSubLoc *)(this + local_4c * 0x240 + iVar8 + 0x13adc));
                if ((iVar6 == 0) && (pcVar7[0x270] != (cRSubGame)0x1e)) {
                  iVar8 = uVar4 * 0x240 + iVar8;
                }
                else {
                  iVar8 = *(int *)(pcVar7 + 0x24);
                  if (iVar8 == *(int *)(Game + 0x44370)) {
                    iVar8 = iVar10 * 0x48 + uVar4 * 0x240;
                    cRBod::SetObject((cRBod *)(this + iVar8 + 0x13adc),
                                     *(cRObject **)(Game + 0x44630));
                    this[iVar8 + 0x13b10] = (cRSubGame)((byte)this[iVar8 + 0x13b10] | 0x40);
                    iVar8 = *(int *)(pcVar7 + 0x24);
                  }
                  iVar9 = 5;
                  iVar6 = iVar2 + iVar10 * 0x48;
                  while( true ) {
                    iVar5 = iVar9 * 0x2c + Game;
                    iVar9 = iVar9 + 1;
                    if (iVar8 == *(int *)(iVar5 + 0x43e48)) {
                      cRBod::SetObject((cRBod *)(this + iVar6 + 0x13adc),
                                       *(cRObject **)(iVar5 + 0x43fa8));
                      this[iVar6 + 0x13b10] = (cRSubGame)((byte)this[iVar6 + 0x13b10] | 0x40);
                    }
                    if (iVar9 == 9) break;
                    iVar8 = *(int *)(pcVar7 + 0x24);
                  }
                  iVar8 = iVar2 + iVar10 * 0x48;
                }
                cVar3 = this[iVar8 + 0x13b10];
              }
              if (((byte)cVar3 & 0x3f) >> 5 != 0) goto LAB_000808ac;
            }
            iVar8 = iVar10 * 0x48;
            if (((((byte)this[iVar8 + local_4c * 0x240 + 0x13b10] & 0x20) == 0) &&
                (iVar6 = cRSubLoc::IsSlide((cRSubLoc *)(this + iVar8 + iVar2 + 0x13adc)), iVar6 != 0
                )) && (iVar6 = cRSubLoc::IsFloor((cRSubLoc *)
                                                 (this + local_4c * 0x240 + iVar8 + 0x13adc)),
                      iVar6 != 0)) {
              iVar6 = *(int *)(pcVar7 + 0x24);
              if (iVar6 == *(int *)(Game + 0x44630)) {
                iVar8 = uVar4 * 0x240 + iVar8;
                cRBod::SetObject((cRBod *)(this + iVar8 + 0x13adc),*(cRObject **)(Game + 0x44370));
                this[iVar8 + 0x13b10] = (cRSubGame)((byte)this[iVar8 + 0x13b10] | 0x40);
                iVar6 = *(int *)(pcVar7 + 0x24);
              }
              iVar9 = 0xd;
              iVar8 = iVar2 + iVar10 * 0x48;
              while( true ) {
                iVar5 = iVar9 * 0x2c + Game;
                iVar9 = iVar9 + 1;
                if (iVar6 == *(int *)(iVar5 + 0x43e48)) {
                  cRBod::SetObject((cRBod *)(this + iVar8 + 0x13adc),*(cRObject **)(iVar5 + 0x43ce8)
                                  );
                  this[iVar8 + 0x13b10] = (cRSubGame)((byte)this[iVar8 + 0x13b10] | 0x40);
                }
                if (iVar9 == 0x11) break;
                iVar6 = *(int *)(pcVar7 + 0x24);
              }
            }
          }
        }
        else if ((uVar4 & 7) == 5) {
          iVar8 = iVar10 * 0x48;
          iVar6 = iVar8 + iVar2;
          if (((byte)this[iVar6 + 0x13b10] & 0x20) == 0) {
            if (((byte)this[iVar8 + local_3c * 0x240 + 0x13b10] & 0x20) == 0) {
              iVar9 = cRSubLoc::IsFloor((cRSubLoc *)(this + iVar6 + 0x13adc));
              if (iVar9 == 0) {
                cVar3 = this[iVar6 + 0x13b10];
              }
              else {
                iVar6 = cRSubLoc::IsSlide((cRSubLoc *)(this + local_3c * 0x240 + iVar8 + 0x13adc));
                if ((iVar6 == 0) && (pcVar7[-0x210] != (cRSubGame)0x20)) {
                  iVar8 = uVar4 * 0x240 + iVar8;
                }
                else {
                  iVar8 = *(int *)(pcVar7 + 0x24);
                  if (iVar8 == *(int *)(Game + 0x44370)) {
                    iVar8 = iVar10 * 0x48 + uVar4 * 0x240;
                    cRBod::SetObject((cRBod *)(this + iVar8 + 0x13adc),
                                     *(cRObject **)(Game + 0x44630));
                    this[iVar8 + 0x13b10] = (cRSubGame)((byte)this[iVar8 + 0x13b10] | 0x40);
                    iVar8 = *(int *)(pcVar7 + 0x24);
                  }
                  iVar9 = 5;
                  iVar6 = iVar2 + iVar10 * 0x48;
                  while( true ) {
                    iVar5 = iVar9 * 0x2c + Game;
                    iVar9 = iVar9 + 1;
                    if (iVar8 == *(int *)(iVar5 + 0x43e48)) {
                      cRBod::SetObject((cRBod *)(this + iVar6 + 0x13adc),
                                       *(cRObject **)(iVar5 + 0x43fa8));
                      this[iVar6 + 0x13b10] = (cRSubGame)((byte)this[iVar6 + 0x13b10] | 0x40);
                    }
                    if (iVar9 == 9) break;
                    iVar8 = *(int *)(pcVar7 + 0x24);
                  }
                  iVar8 = iVar2 + iVar10 * 0x48;
                }
                cVar3 = this[iVar8 + 0x13b10];
              }
              if (((byte)cVar3 & 0x3f) >> 5 != 0) goto LAB_000808ac;
            }
            iVar8 = iVar10 * 0x48;
            if (((((byte)this[iVar8 + local_3c * 0x240 + 0x13b10] & 0x20) == 0) &&
                (iVar6 = cRSubLoc::IsSlide((cRSubLoc *)(this + iVar8 + iVar2 + 0x13adc)), iVar6 != 0
                )) && (iVar6 = cRSubLoc::IsFloor((cRSubLoc *)
                                                 (this + local_3c * 0x240 + iVar8 + 0x13adc)),
                      iVar6 != 0)) {
              iVar6 = *(int *)(pcVar7 + 0x24);
              if (iVar6 == *(int *)(Game + 0x44630)) {
                iVar8 = uVar4 * 0x240 + iVar8;
                cRBod::SetObject((cRBod *)(this + iVar8 + 0x13adc),*(cRObject **)(Game + 0x44370));
                this[iVar8 + 0x13b10] = (cRSubGame)((byte)this[iVar8 + 0x13b10] | 0x40);
                iVar6 = *(int *)(pcVar7 + 0x24);
              }
              iVar9 = 0xd;
              iVar8 = iVar2 + iVar10 * 0x48;
              while( true ) {
                iVar5 = iVar9 * 0x2c + Game;
                iVar9 = iVar9 + 1;
                if (iVar6 == *(int *)(iVar5 + 0x43e48)) {
                  cRBod::SetObject((cRBod *)(this + iVar8 + 0x13adc),*(cRObject **)(iVar5 + 0x43ce8)
                                  );
                  this[iVar8 + 0x13b10] = (cRSubGame)((byte)this[iVar8 + 0x13b10] | 0x40);
                }
                if (iVar9 == 0x11) break;
                iVar6 = *(int *)(pcVar7 + 0x24);
              }
            }
          }
        }
LAB_000808ac:
        iVar10 = iVar10 + 1;
        pcVar7 = pcVar7 + 0x48;
      } while (iVar10 != 8);
      local_3c = local_3c + 1;
      bVar1 = local_4c < *(int *)(this + 0x74) + -1;
      local_4c = local_4c + 1;
    } while (bVar1);
  }
  return;
}
