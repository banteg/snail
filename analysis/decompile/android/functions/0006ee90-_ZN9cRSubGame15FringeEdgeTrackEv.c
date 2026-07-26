/*
 * mangled: _ZN9cRSubGame15FringeEdgeTrackEv
 * demangled: cRSubGame::FringeEdgeTrack()
 * address: 0006ee90
 * size: 1644
 */

/* cRSubGame::FringeEdgeTrack() */

void __thiscall cRSubGame::FringeEdgeTrack(cRSubGame *this)

{
  cRSubGame cVar1;
  cRSubGame cVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  uint uVar6;
  undefined4 uVar7;
  cRSubGame *pcVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  cRSubGame *pcVar12;
  cRSubLoc *pcVar13;

  cRFringeManager::Init((cRFringeManager *)(Game + 0x7a52c));
  if (0 < *(int *)(this + 0x74)) {
    iVar11 = 0;
    pcVar12 = this + 0x20dedc;
    do {
      uVar6 = *(uint *)pcVar12;
      iVar9 = 0;
      pcVar8 = this + iVar11 * 0x240 + 0x13adc;
      do {
        cVar1 = pcVar8[0x31];
        if (cVar1 == (cRSubGame)0x9) {
          iVar10 = 1;
        }
        else if (cVar1 == (cRSubGame)0x5) {
          iVar10 = 3;
        }
        else if (cVar1 == (cRSubGame)0xa) {
          iVar10 = 2;
        }
        else if (cVar1 == (cRSubGame)0x6) {
          iVar10 = 4;
        }
        else {
          iVar10 = 0;
        }
        cVar2 = pcVar8[0x30];
        if (cVar2 == (cRSubGame)0x2 || cVar2 == (cRSubGame)0x8) {
          iVar10 = 5;
LAB_0006ef60:
          if (cVar2 == (cRSubGame)0x3 || cVar2 == (cRSubGame)0x9) {
            iVar10 = 6;
            goto LAB_0006ef70;
          }
          if ((((cVar2 != (cRSubGame)0xb) && (cVar2 != (cRSubGame)0xc)) && (cVar2 != (cRSubGame)0xd)
              ) && (cVar2 != (cRSubGame)0x6)) goto LAB_0006ef70;
          iVar10 = 6;
        }
        else {
          if (cVar2 != (cRSubGame)0x5) goto LAB_0006ef60;
          iVar10 = 5;
LAB_0006ef70:
          if ((cVar2 == (cRSubGame)0x4 || cVar2 == (cRSubGame)0xa) || (cVar2 == (cRSubGame)0x7)) {
            iVar10 = 7;
          }
        }
        if ((((uVar6 & 4) == 0) && (cVar1 != (cRSubGame)0x0)) &&
           ((cVar2 != (cRSubGame)0x20 && ((gConfig._28_4_ & 0x20) != 0)))) {
          pcVar13 = (cRSubLoc *)(this + iVar11 * 0x240 + iVar9 * 0x48 + 0x13adc);
          iVar3 = TestLoc(this,pcVar13,0,0);
          if (iVar3 == 0) {
            uVar6 = *(uint *)pcVar12;
          }
          else {
            iVar3 = TestLoc(this,pcVar13,0,1);
            if (iVar3 == 0) {
              iVar3 = TestLoc(this,pcVar13,1,1);
              if (iVar3 == 0) {
                iVar3 = TestLoc(this,pcVar13,1,0);
                if (iVar3 == 0) {
                  iVar3 = 6;
                }
                else {
                  iVar3 = 3;
                }
              }
              else {
                iVar3 = 0;
              }
              iVar4 = TestLoc(this,pcVar13,-1,1);
              if (iVar4 == 0) {
                iVar4 = TestLoc(this,pcVar13,-1,0);
                if (iVar4 == 0) {
                  iVar4 = 2;
                }
                else {
                  iVar4 = 1;
                }
              }
              else {
                iVar4 = 0;
              }
              puVar5 = (undefined4 *)cRFringeManager::GetFringe((cRFringeManager *)(Game + 0x7a52c))
              ;
              uVar7 = *(undefined4 *)
                       ((iVar3 + iVar10 * 0x24 + iVar4 + 0x3a) * 0x2c + Game + 0x43e48);
              *(undefined4 **)(pcVar8 + 0x38) = puVar5;
              *puVar5 = uVar7;
            }
            else {
              *(undefined4 *)(pcVar8 + 0x38) = 0;
            }
            iVar3 = TestLoc(this,pcVar13,1,0);
            if (iVar3 == 0) {
              iVar4 = TestLoc(this,pcVar13,1,-1);
              iVar3 = 0;
              if (iVar4 == 0) {
                iVar3 = TestLoc(this,pcVar13,0,-1);
                if (iVar3 == 0) {
                  iVar3 = 6;
                }
                else {
                  iVar3 = 3;
                }
              }
              iVar4 = TestLoc(this,pcVar13,1,1);
              if (iVar4 == 0) {
                iVar4 = TestLoc(this,pcVar13,0,1);
                if (iVar4 == 0) {
                  iVar4 = 2;
                }
                else {
                  iVar4 = 1;
                }
              }
              else {
                iVar4 = 0;
              }
              puVar5 = (undefined4 *)cRFringeManager::GetFringe((cRFringeManager *)(Game + 0x7a52c))
              ;
              uVar7 = *(undefined4 *)
                       ((iVar3 + iVar10 * 0x24 + iVar4 + 0x43) * 0x2c + Game + 0x43e48);
              *(undefined4 **)(pcVar8 + 0x3c) = puVar5;
              *puVar5 = uVar7;
            }
            else {
              *(undefined4 *)(pcVar8 + 0x3c) = 0;
            }
            iVar3 = TestLoc(this,pcVar13,-1,0);
            if (iVar3 == 0) {
              iVar4 = TestLoc(this,pcVar13,-1,1);
              iVar3 = 0;
              if (iVar4 == 0) {
                iVar3 = TestLoc(this,pcVar13,0,1);
                if (iVar3 == 0) {
                  iVar3 = 6;
                }
                else {
                  iVar3 = 3;
                }
              }
              iVar4 = TestLoc(this,pcVar13,-1,-1);
              if (iVar4 == 0) {
                iVar4 = TestLoc(this,pcVar13,0,-1);
                if (iVar4 == 0) {
                  iVar4 = 2;
                }
                else {
                  iVar4 = 1;
                }
              }
              else {
                iVar4 = 0;
              }
              puVar5 = (undefined4 *)cRFringeManager::GetFringe((cRFringeManager *)(Game + 0x7a52c))
              ;
              uVar7 = *(undefined4 *)
                       ((iVar3 + iVar10 * 0x24 + iVar4 + 0x4c) * 0x2c + Game + 0x43e48);
              *(undefined4 **)(pcVar8 + 0x40) = puVar5;
              *puVar5 = uVar7;
            }
            else {
              *(undefined4 *)(pcVar8 + 0x40) = 0;
            }
            iVar3 = TestLoc(this,pcVar13,0,-1);
            if (iVar3 == 0) {
              iVar4 = TestLoc(this,pcVar13,-1,-1);
              iVar3 = 0;
              if (iVar4 == 0) {
                iVar3 = TestLoc(this,pcVar13,-1,0);
                if (iVar3 == 0) {
                  iVar3 = 6;
                }
                else {
                  iVar3 = 3;
                }
              }
              iVar4 = TestLoc(this,pcVar13,1,-1);
              if (iVar4 == 0) {
                iVar4 = TestLoc(this,pcVar13,1,0);
                if (iVar4 == 0) {
                  iVar4 = 2;
                }
                else {
                  iVar4 = 1;
                }
              }
              else {
                iVar4 = 0;
              }
              puVar5 = (undefined4 *)cRFringeManager::GetFringe((cRFringeManager *)(Game + 0x7a52c))
              ;
              uVar6 = *(uint *)pcVar12;
              uVar7 = *(undefined4 *)
                       ((iVar4 + iVar10 * 0x24 + iVar3 + 0x55) * 0x2c + Game + 0x43e48);
              *(undefined4 **)(pcVar8 + 0x44) = puVar5;
              *puVar5 = uVar7;
            }
            else {
              uVar6 = *(uint *)pcVar12;
              *(undefined4 *)(pcVar8 + 0x44) = 0;
            }
          }
        }
        else {
          *(undefined4 *)(pcVar8 + 0x44) = 0;
          *(undefined4 *)(pcVar8 + 0x38) = 0;
          *(undefined4 *)(pcVar8 + 0x3c) = 0;
          *(undefined4 *)(pcVar8 + 0x40) = 0;
        }
        if ((uVar6 & 4) != 0) {
          if (*(int *)(pcVar8 + 0x38) != 0) {
            *(undefined4 *)(pcVar8 + 0x38) = 0;
          }
          if (*(int *)(pcVar8 + 0x44) != 0) {
            *(undefined4 *)(pcVar8 + 0x44) = 0;
          }
          if (*(int *)(pcVar8 + 0x3c) != 0) {
            *(undefined4 *)(pcVar8 + 0x3c) = 0;
          }
          if (*(int *)(pcVar8 + 0x40) != 0) {
            *(undefined4 *)(pcVar8 + 0x40) = 0;
          }
        }
        iVar9 = iVar9 + 1;
        pcVar8 = pcVar8 + 0x48;
      } while (iVar9 != 8);
      iVar11 = iVar11 + 1;
      pcVar12 = pcVar12 + 0xdc;
    } while (iVar11 < *(int *)(this + 0x74));
  }
  wprintf("Used %i fringe bods\n",*(undefined4 *)(Game + 0x8128c));
  return;
}
