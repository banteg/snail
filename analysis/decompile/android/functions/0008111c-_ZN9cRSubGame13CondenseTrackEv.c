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
  cRSubGame *pcVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  cRSubGame *pcVar9;
  cRSubGame *pcVar10;
  cRSubLoc *this_00;
  int iVar11;

  iVar7 = *(int *)(this + 0x74);
  if (0 < iVar7) {
    iVar11 = 0;
    do {
      iVar3 = 0;
      do {
        iVar4 = iVar3 + 1;
        iVar3 = iVar11 * 0x240 + iVar3 * 0x48;
        this[iVar3 + 0x13b11] = (cRSubGame)((byte)this[iVar3 + 0x13b11] | 0x60);
        iVar3 = iVar4;
      } while (iVar4 != 8);
      iVar11 = iVar11 + 1;
    } while (iVar11 < iVar7);
    iVar7 = 0;
    pcVar10 = this + 0x20dedc;
    do {
      iVar3 = 0;
      iVar11 = iVar7 * 0x240;
      pcVar9 = this + iVar11 + 0x13ae0;
      do {
        iVar8 = iVar11 + iVar3 * 0x48;
        this_00 = (cRSubLoc *)(this + iVar8 + 0x13adc);
        iVar4 = cRSubLoc::IsFloor(this_00);
        if (((iVar4 == 0) || ((char)this[iVar8 + 0x13b11] < '\0')) ||
           ((int)((uint)(byte)this[iVar8 + 0x13b10] << 0x19) < 0)) {
          iVar4 = cRSubLoc::IsSlide(this_00);
          if (((iVar4 == 0) || (iVar4 = iVar11 + iVar3 * 0x48, (char)this[iVar4 + 0x13b11] < '\0'))
             || ((int)((uint)(byte)this[iVar4 + 0x13b10] << 0x19) < 0)) {
            cVar2 = pcVar9[0x2c];
            if (cVar2 == (cRSubGame)0xe) {
              iVar4 = iVar3 * 0x48 + iVar11;
              this[iVar4 + 0x13b11] = (cRSubGame)((byte)this[iVar4 + 0x13b11] & 0xf0 | 1);
              if (((iVar3 < 8) && (pcVar9[0x2c] == (cRSubGame)0xe)) &&
                 (((byte)this[iVar3 * 0x48 + iVar11 + 0x13b11] & 0x40) != 0)) {
                iVar4 = 0;
                do {
                  iVar8 = iVar4;
                  iVar4 = iVar8 + 1;
                  if (7 < iVar4 + iVar3) break;
                  pcVar1 = this_00 + 0x78;
                  this_00 = this_00 + 0x48;
                } while (*pcVar1 == (cRSubLoc)0xe);
                if (iVar4 != 1) {
                  iVar6 = iVar11 + iVar3 * 0x48;
                  cRBod::SetObject((cRBod *)(this + iVar6 + 0x13adc),
                                   *(cRObject **)((iVar8 + 0x16) * 0x2c + Game + 0x43e48));
                  this[iVar6 + 0x13b11] =
                       (cRSubGame)((byte)this[iVar6 + 0x13b11] & 0xf0 | (byte)iVar4 & 0xf);
                  pcVar5 = this + iVar11 + (iVar8 + iVar3) * 0x48 + 0x13ae0;
                  iVar4 = iVar8 + iVar3;
                  do {
                    iVar8 = iVar8 + -1;
                    iVar6 = iVar11 + iVar4 * 0x48;
                    *(uint *)pcVar5 = *(uint *)pcVar5 & 0xffffffdf;
                    this[iVar6 + 0x13b11] = (cRSubGame)((byte)this[iVar6 + 0x13b11] & 0x9f);
                    pcVar5 = pcVar5 + -0x48;
                    iVar4 = iVar4 + -1;
                  } while (iVar8 != 0);
                }
              }
            }
            else if (cVar2 == (cRSubGame)0x0 || cVar2 == (cRSubGame)0x23) {
              iVar4 = iVar11 + iVar3 * 0x48;
              this[iVar4 + 0x13b11] = (cRSubGame)((byte)this[iVar4 + 0x13b11] & 0xdf);
              if (*(int *)(this + 0x60) == 2) {
                cRBod::SetObject((cRBod *)(this + iVar4 + 0x13adc),*(cRObject **)(Game + 0x43e48));
              }
              else {
                this[iVar4 + 0x13b11] = (cRSubGame)((byte)this[iVar4 + 0x13b11] & 0xbf);
              }
            }
          }
          else if (iVar3 < 8) {
            iVar4 = 0;
            iVar8 = iVar3;
            do {
              iVar6 = iVar11 + iVar8 * 0x48;
              iVar8 = cRSubLoc::IsSlide((cRSubLoc *)(this + iVar6 + 0x13adc));
              if ((((iVar8 == 0) || ((char)this[iVar6 + 0x13b11] < '\0')) ||
                  (((byte)this[iVar6 + 0x13b11] & 0x40) == 0)) ||
                 ((((byte)this[iVar6 + 0x13b10] & 0x20) != 0 ||
                  (((byte)this[iVar6 + 0x13b10] & 0x40) != 0)))) break;
              iVar4 = iVar4 + 1;
              iVar8 = iVar4 + iVar3;
            } while (iVar8 < 8);
            if (1 < iVar4) {
              cRBod::SetObject((cRBod *)(this + iVar11 + iVar3 * 0x48 + 0x13adc),
                               *(cRObject **)((iVar4 + 0x2d) * 0x2c + Game + 0x43e48));
              pcVar5 = this + iVar11 + (iVar4 + iVar3) * 0x48 + 0x13adc;
              iVar8 = iVar3 + -1 + iVar4;
              do {
                iVar4 = iVar4 + -1;
                iVar6 = iVar11 + iVar8 * 0x48;
                *(uint *)(pcVar5 + -0x44) = *(uint *)(pcVar5 + -0x44) & 0xffffffdf;
                pcVar5 = pcVar5 + -0x48;
                this[iVar6 + 0x13b11] = (cRSubGame)((byte)this[iVar6 + 0x13b11] & 0x9f);
                iVar8 = iVar8 + -1;
              } while (iVar4 != 1);
            }
          }
        }
        else if (iVar3 < 8) {
          iVar4 = 0;
          iVar8 = iVar3;
          do {
            iVar8 = iVar11 + iVar8 * 0x48;
            cVar2 = this[iVar8 + 0x13b0c];
            if ((((cVar2 != (cRSubGame)0x1 && cVar2 != (cRSubGame)0x15) &&
                 (cVar2 != (cRSubGame)0x1b)) &&
                ((cVar2 != (cRSubGame)0x21 && (cVar2 != (cRSubGame)0x22)))) ||
               (((((char)this[iVar8 + 0x13b11] < '\0' || (((byte)this[iVar8 + 0x13b11] & 0x40) == 0)
                  ) || (((byte)this[iVar8 + 0x13b10] & 0x20) != 0)) ||
                (((byte)this[iVar8 + 0x13b10] & 0x40) != 0)))) break;
            iVar4 = iVar4 + 1;
            iVar8 = iVar4 + iVar3;
          } while (iVar8 < 8);
          if (1 < iVar4) {
            cRBod::SetObject((cRBod *)(this + iVar11 + iVar3 * 0x48 + 0x13adc),
                             *(cRObject **)((iVar4 + 0x1d) * 0x2c + Game + 0x43e48));
            pcVar5 = this + iVar11 + (iVar4 + iVar3) * 0x48 + 0x13adc;
            iVar8 = iVar3 + -1 + iVar4;
            do {
              iVar4 = iVar4 + -1;
              iVar6 = iVar11 + iVar8 * 0x48;
              *(uint *)(pcVar5 + -0x44) = *(uint *)(pcVar5 + -0x44) & 0xffffffdf;
              pcVar5 = pcVar5 + -0x48;
              this[iVar6 + 0x13b11] = (cRSubGame)((byte)this[iVar6 + 0x13b11] & 0x9f);
              iVar8 = iVar8 + -1;
            } while (iVar4 != 1);
          }
        }
        if ((*(uint *)pcVar10 & 4) != 0) {
          iVar4 = iVar11 + iVar3 * 0x48;
          *(uint *)pcVar9 = *(uint *)pcVar9 & 0xfffffddd;
          this[iVar4 + 0x13b11] = (cRSubGame)((byte)this[iVar4 + 0x13b11] & 0xbf);
          *(uint *)(pcVar10 + 0xa8) = *(uint *)(pcVar10 + 0xa8) & 0xffffffdf;
        }
        iVar3 = iVar3 + 1;
        pcVar9 = pcVar9 + 0x48;
      } while (iVar3 != 8);
      iVar7 = iVar7 + 1;
      pcVar10 = pcVar10 + 0xdc;
    } while (iVar7 < *(int *)(this + 0x74));
  }
  return;
}
