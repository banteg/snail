/*
 * mangled: _ZN9cRSubGame13CondenseTrackEv
 * demangled: cRSubGame::CondenseTrack()
 * address: 0008111c
 * size: 1568
 */

/* cRSubGame::CondenseTrack() */

void __thiscall cRSubGame::CondenseTrack(cRSubGame *this)

{
  cRSubLoc *pcVar1;
  cRSubGame cVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  cRSubGame *pcVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  cRSubGame *pcVar11;
  cRSubGame *pcVar12;
  cRSubLoc *this_00;
  int iVar13;

  iVar9 = *(int *)(this + 0x74);
  iVar4 = DAT_0008173c + 0x81138;
  if (0 < iVar9) {
    iVar13 = 0;
    do {
      iVar5 = 0;
      do {
        iVar6 = iVar5 + 1;
        iVar5 = iVar13 * 0x240 + iVar5 * 0x48;
        this[iVar5 + 0x13b11] = (cRSubGame)((byte)this[iVar5 + 0x13b11] | 0x60);
        iVar3 = DAT_00081740;
        iVar5 = iVar6;
      } while (iVar6 != 8);
      iVar13 = iVar13 + 1;
    } while (iVar13 < iVar9);
    iVar9 = 0;
    pcVar12 = this + 0x20dedc;
    do {
      iVar5 = 0;
      iVar13 = iVar9 * 0x240;
      pcVar11 = this + iVar13 + 0x13ae0;
      do {
        iVar10 = iVar13 + iVar5 * 0x48;
        this_00 = (cRSubLoc *)(this + iVar10 + 0x13adc);
        iVar6 = cRSubLoc::IsFloor(this_00);
        if (((iVar6 == 0) || ((char)this[iVar10 + 0x13b11] < '\0')) ||
           ((int)((uint)(byte)this[iVar10 + 0x13b10] << 0x19) < 0)) {
          iVar6 = cRSubLoc::IsSlide(this_00);
          if (((iVar6 == 0) || (iVar6 = iVar13 + iVar5 * 0x48, (char)this[iVar6 + 0x13b11] < '\0'))
             || ((int)((uint)(byte)this[iVar6 + 0x13b10] << 0x19) < 0)) {
            cVar2 = pcVar11[0x2c];
            if (cVar2 == (cRSubGame)0xe) {
              iVar6 = iVar5 * 0x48 + iVar13;
              this[iVar6 + 0x13b11] = (cRSubGame)((byte)this[iVar6 + 0x13b11] & 0xf0 | 1);
              if (((iVar5 < 8) && (pcVar11[0x2c] == (cRSubGame)0xe)) &&
                 (((byte)this[iVar5 * 0x48 + iVar13 + 0x13b11] & 0x40) != 0)) {
                iVar6 = 0;
                do {
                  iVar10 = iVar6;
                  iVar6 = iVar10 + 1;
                  if (7 < iVar6 + iVar5) break;
                  pcVar1 = this_00 + 0x78;
                  this_00 = this_00 + 0x48;
                } while (*pcVar1 == (cRSubLoc)0xe);
                if (iVar6 != 1) {
                  iVar8 = iVar13 + iVar5 * 0x48;
                  cRBod::SetObject((cRBod *)(this + iVar8 + 0x13adc),
                                   *(cRObject **)
                                    ((iVar10 + 0x16) * 0x2c + **(int **)(iVar4 + iVar3) + 0x43e48));
                  this[iVar8 + 0x13b11] =
                       (cRSubGame)((byte)this[iVar8 + 0x13b11] & 0xf0 | (byte)iVar6 & 0xf);
                  pcVar7 = this + iVar13 + (iVar10 + iVar5) * 0x48 + 0x13ae0;
                  iVar6 = iVar10 + iVar5;
                  do {
                    iVar10 = iVar10 + -1;
                    iVar8 = iVar13 + iVar6 * 0x48;
                    *(uint *)pcVar7 = *(uint *)pcVar7 & 0xffffffdf;
                    this[iVar8 + 0x13b11] = (cRSubGame)((byte)this[iVar8 + 0x13b11] & 0x9f);
                    pcVar7 = pcVar7 + -0x48;
                    iVar6 = iVar6 + -1;
                  } while (iVar10 != 0);
                }
              }
            }
            else if (cVar2 == (cRSubGame)0x0 || cVar2 == (cRSubGame)0x23) {
              iVar6 = iVar13 + iVar5 * 0x48;
              this[iVar6 + 0x13b11] = (cRSubGame)((byte)this[iVar6 + 0x13b11] & 0xdf);
              if (*(int *)(this + 0x60) == 2) {
                cRBod::SetObject((cRBod *)(this + iVar6 + 0x13adc),
                                 *(cRObject **)(**(int **)(iVar4 + iVar3) + 0x43e48));
              }
              else {
                this[iVar6 + 0x13b11] = (cRSubGame)((byte)this[iVar6 + 0x13b11] & 0xbf);
              }
            }
          }
          else if (iVar5 < 8) {
            iVar6 = 0;
            iVar10 = iVar5;
            do {
              iVar8 = iVar13 + iVar10 * 0x48;
              iVar10 = cRSubLoc::IsSlide((cRSubLoc *)(this + iVar8 + 0x13adc));
              if ((((iVar10 == 0) || ((char)this[iVar8 + 0x13b11] < '\0')) ||
                  (((byte)this[iVar8 + 0x13b11] & 0x40) == 0)) ||
                 ((((byte)this[iVar8 + 0x13b10] & 0x20) != 0 ||
                  (((byte)this[iVar8 + 0x13b10] & 0x40) != 0)))) break;
              iVar6 = iVar6 + 1;
              iVar10 = iVar6 + iVar5;
            } while (iVar10 < 8);
            if (1 < iVar6) {
              cRBod::SetObject((cRBod *)(this + iVar13 + iVar5 * 0x48 + 0x13adc),
                               *(cRObject **)
                                ((iVar6 + 0x2d) * 0x2c + **(int **)(iVar4 + iVar3) + 0x43e48));
              pcVar7 = this + iVar13 + (iVar6 + iVar5) * 0x48 + 0x13adc;
              iVar10 = iVar5 + -1 + iVar6;
              do {
                iVar6 = iVar6 + -1;
                iVar8 = iVar13 + iVar10 * 0x48;
                *(uint *)(pcVar7 + -0x44) = *(uint *)(pcVar7 + -0x44) & 0xffffffdf;
                pcVar7 = pcVar7 + -0x48;
                this[iVar8 + 0x13b11] = (cRSubGame)((byte)this[iVar8 + 0x13b11] & 0x9f);
                iVar10 = iVar10 + -1;
              } while (iVar6 != 1);
            }
          }
        }
        else if (iVar5 < 8) {
          iVar6 = 0;
          iVar10 = iVar5;
          do {
            iVar10 = iVar13 + iVar10 * 0x48;
            cVar2 = this[iVar10 + 0x13b0c];
            if ((((cVar2 != (cRSubGame)0x1 && cVar2 != (cRSubGame)0x15) &&
                 (cVar2 != (cRSubGame)0x1b)) &&
                ((cVar2 != (cRSubGame)0x21 && (cVar2 != (cRSubGame)0x22)))) ||
               (((((char)this[iVar10 + 0x13b11] < '\0' ||
                  (((byte)this[iVar10 + 0x13b11] & 0x40) == 0)) ||
                 (((byte)this[iVar10 + 0x13b10] & 0x20) != 0)) ||
                (((byte)this[iVar10 + 0x13b10] & 0x40) != 0)))) break;
            iVar6 = iVar6 + 1;
            iVar10 = iVar6 + iVar5;
          } while (iVar10 < 8);
          if (1 < iVar6) {
            cRBod::SetObject((cRBod *)(this + iVar13 + iVar5 * 0x48 + 0x13adc),
                             *(cRObject **)
                              ((iVar6 + 0x1d) * 0x2c + **(int **)(iVar4 + iVar3) + 0x43e48));
            pcVar7 = this + iVar13 + (iVar6 + iVar5) * 0x48 + 0x13adc;
            iVar10 = iVar5 + -1 + iVar6;
            do {
              iVar6 = iVar6 + -1;
              iVar8 = iVar13 + iVar10 * 0x48;
              *(uint *)(pcVar7 + -0x44) = *(uint *)(pcVar7 + -0x44) & 0xffffffdf;
              pcVar7 = pcVar7 + -0x48;
              this[iVar8 + 0x13b11] = (cRSubGame)((byte)this[iVar8 + 0x13b11] & 0x9f);
              iVar10 = iVar10 + -1;
            } while (iVar6 != 1);
          }
        }
        if ((*(uint *)pcVar12 & 4) != 0) {
          iVar6 = iVar13 + iVar5 * 0x48;
          *(uint *)pcVar11 = *(uint *)pcVar11 & 0xfffffddd;
          this[iVar6 + 0x13b11] = (cRSubGame)((byte)this[iVar6 + 0x13b11] & 0xbf);
          *(uint *)(pcVar12 + 0xa8) = *(uint *)(pcVar12 + 0xa8) & 0xffffffdf;
        }
        iVar5 = iVar5 + 1;
        pcVar11 = pcVar11 + 0x48;
      } while (iVar5 != 8);
      iVar9 = iVar9 + 1;
      pcVar12 = pcVar12 + 0xdc;
    } while (iVar9 < *(int *)(this + 0x74));
  }
  return;
}
