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
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  int iVar8;
  uint uVar9;
  undefined4 uVar10;
  cRSubGame *pcVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  cRSubGame *pcVar15;
  cRSubLoc *pcVar16;
  int *piVar17;

  iVar3 = DAT_0006f500;
  iVar8 = DAT_0006f4fc + 0x6eea0;
  cRFringeManager::Init((cRFringeManager *)(**(int **)(iVar8 + DAT_0006f500) + 0x7a52c));
  iVar4 = DAT_0006f504;
  if (0 < *(int *)(this + 0x74)) {
    iVar14 = 0;
    pcVar15 = this + 0x20dedc;
    do {
      uVar9 = *(uint *)pcVar15;
      iVar12 = 0;
      pcVar11 = this + iVar14 * 0x240 + 0x13adc;
      do {
        cVar1 = pcVar11[0x31];
        if (cVar1 == (cRSubGame)0x9) {
          iVar13 = 1;
        }
        else if (cVar1 == (cRSubGame)0x5) {
          iVar13 = 3;
        }
        else if (cVar1 == (cRSubGame)0xa) {
          iVar13 = 2;
        }
        else if (cVar1 == (cRSubGame)0x6) {
          iVar13 = 4;
        }
        else {
          iVar13 = 0;
        }
        cVar2 = pcVar11[0x30];
        if (cVar2 == (cRSubGame)0x2 || cVar2 == (cRSubGame)0x8) {
          iVar13 = 5;
LAB_0006ef60:
          if (cVar2 == (cRSubGame)0x3 || cVar2 == (cRSubGame)0x9) {
            iVar13 = 6;
            goto LAB_0006ef70;
          }
          if ((((cVar2 != (cRSubGame)0xb) && (cVar2 != (cRSubGame)0xc)) && (cVar2 != (cRSubGame)0xd)
              ) && (cVar2 != (cRSubGame)0x6)) goto LAB_0006ef70;
          iVar13 = 6;
        }
        else {
          if (cVar2 != (cRSubGame)0x5) goto LAB_0006ef60;
          iVar13 = 5;
LAB_0006ef70:
          if ((cVar2 == (cRSubGame)0x4 || cVar2 == (cRSubGame)0xa) || (cVar2 == (cRSubGame)0x7)) {
            iVar13 = 7;
          }
        }
        if ((((uVar9 & 4) == 0) && (cVar1 != (cRSubGame)0x0)) &&
           ((cVar2 != (cRSubGame)0x20 && ((*(uint *)(*(int *)(iVar8 + iVar4) + 0x1c) & 0x20) != 0)))
           ) {
          pcVar16 = (cRSubLoc *)(this + iVar14 * 0x240 + iVar12 * 0x48 + 0x13adc);
          iVar5 = TestLoc(this,pcVar16,0,0);
          if (iVar5 == 0) {
            uVar9 = *(uint *)pcVar15;
          }
          else {
            iVar5 = TestLoc(this,pcVar16,0,1);
            if (iVar5 == 0) {
              iVar5 = TestLoc(this,pcVar16,1,1);
              if (iVar5 == 0) {
                iVar5 = TestLoc(this,pcVar16,1,0);
                if (iVar5 == 0) {
                  iVar5 = 6;
                }
                else {
                  iVar5 = 3;
                }
              }
              else {
                iVar5 = 0;
              }
              iVar6 = TestLoc(this,pcVar16,-1,1);
              if (iVar6 == 0) {
                iVar6 = TestLoc(this,pcVar16,-1,0);
                if (iVar6 == 0) {
                  iVar6 = 2;
                }
                else {
                  iVar6 = 1;
                }
              }
              else {
                iVar6 = 0;
              }
              piVar17 = *(int **)(iVar8 + iVar3);
              puVar7 = (undefined4 *)
                       cRFringeManager::GetFringe((cRFringeManager *)(*piVar17 + 0x7a52c));
              uVar10 = *(undefined4 *)
                        ((iVar5 + iVar13 * 0x24 + iVar6 + 0x3a) * 0x2c + *piVar17 + 0x43e48);
              *(undefined4 **)(pcVar11 + 0x38) = puVar7;
              *puVar7 = uVar10;
            }
            else {
              *(undefined4 *)(pcVar11 + 0x38) = 0;
            }
            iVar5 = TestLoc(this,pcVar16,1,0);
            if (iVar5 == 0) {
              iVar6 = TestLoc(this,pcVar16,1,-1);
              iVar5 = 0;
              if (iVar6 == 0) {
                iVar5 = TestLoc(this,pcVar16,0,-1);
                if (iVar5 == 0) {
                  iVar5 = 6;
                }
                else {
                  iVar5 = 3;
                }
              }
              iVar6 = TestLoc(this,pcVar16,1,1);
              if (iVar6 == 0) {
                iVar6 = TestLoc(this,pcVar16,0,1);
                if (iVar6 == 0) {
                  iVar6 = 2;
                }
                else {
                  iVar6 = 1;
                }
              }
              else {
                iVar6 = 0;
              }
              piVar17 = *(int **)(iVar8 + iVar3);
              puVar7 = (undefined4 *)
                       cRFringeManager::GetFringe((cRFringeManager *)(*piVar17 + 0x7a52c));
              uVar10 = *(undefined4 *)
                        ((iVar5 + iVar13 * 0x24 + iVar6 + 0x43) * 0x2c + *piVar17 + 0x43e48);
              *(undefined4 **)(pcVar11 + 0x3c) = puVar7;
              *puVar7 = uVar10;
            }
            else {
              *(undefined4 *)(pcVar11 + 0x3c) = 0;
            }
            iVar5 = TestLoc(this,pcVar16,-1,0);
            if (iVar5 == 0) {
              iVar6 = TestLoc(this,pcVar16,-1,1);
              iVar5 = 0;
              if (iVar6 == 0) {
                iVar5 = TestLoc(this,pcVar16,0,1);
                if (iVar5 == 0) {
                  iVar5 = 6;
                }
                else {
                  iVar5 = 3;
                }
              }
              iVar6 = TestLoc(this,pcVar16,-1,-1);
              if (iVar6 == 0) {
                iVar6 = TestLoc(this,pcVar16,0,-1);
                if (iVar6 == 0) {
                  iVar6 = 2;
                }
                else {
                  iVar6 = 1;
                }
              }
              else {
                iVar6 = 0;
              }
              piVar17 = *(int **)(iVar8 + iVar3);
              puVar7 = (undefined4 *)
                       cRFringeManager::GetFringe((cRFringeManager *)(*piVar17 + 0x7a52c));
              uVar10 = *(undefined4 *)
                        ((iVar5 + iVar13 * 0x24 + iVar6 + 0x4c) * 0x2c + *piVar17 + 0x43e48);
              *(undefined4 **)(pcVar11 + 0x40) = puVar7;
              *puVar7 = uVar10;
            }
            else {
              *(undefined4 *)(pcVar11 + 0x40) = 0;
            }
            iVar5 = TestLoc(this,pcVar16,0,-1);
            if (iVar5 == 0) {
              iVar6 = TestLoc(this,pcVar16,-1,-1);
              iVar5 = 0;
              if (iVar6 == 0) {
                iVar5 = TestLoc(this,pcVar16,-1,0);
                if (iVar5 == 0) {
                  iVar5 = 6;
                }
                else {
                  iVar5 = 3;
                }
              }
              iVar6 = TestLoc(this,pcVar16,1,-1);
              if (iVar6 == 0) {
                iVar6 = TestLoc(this,pcVar16,1,0);
                if (iVar6 == 0) {
                  iVar6 = 2;
                }
                else {
                  iVar6 = 1;
                }
              }
              else {
                iVar6 = 0;
              }
              piVar17 = *(int **)(iVar8 + iVar3);
              puVar7 = (undefined4 *)
                       cRFringeManager::GetFringe((cRFringeManager *)(*piVar17 + 0x7a52c));
              uVar9 = *(uint *)pcVar15;
              uVar10 = *(undefined4 *)
                        ((iVar6 + iVar13 * 0x24 + iVar5 + 0x55) * 0x2c + *piVar17 + 0x43e48);
              *(undefined4 **)(pcVar11 + 0x44) = puVar7;
              *puVar7 = uVar10;
            }
            else {
              uVar9 = *(uint *)pcVar15;
              *(undefined4 *)(pcVar11 + 0x44) = 0;
            }
          }
        }
        else {
          *(undefined4 *)(pcVar11 + 0x44) = 0;
          *(undefined4 *)(pcVar11 + 0x38) = 0;
          *(undefined4 *)(pcVar11 + 0x3c) = 0;
          *(undefined4 *)(pcVar11 + 0x40) = 0;
        }
        if ((uVar9 & 4) != 0) {
          if (*(int *)(pcVar11 + 0x38) != 0) {
            *(undefined4 *)(pcVar11 + 0x38) = 0;
          }
          if (*(int *)(pcVar11 + 0x44) != 0) {
            *(undefined4 *)(pcVar11 + 0x44) = 0;
          }
          if (*(int *)(pcVar11 + 0x3c) != 0) {
            *(undefined4 *)(pcVar11 + 0x3c) = 0;
          }
          if (*(int *)(pcVar11 + 0x40) != 0) {
            *(undefined4 *)(pcVar11 + 0x40) = 0;
          }
        }
        iVar12 = iVar12 + 1;
        pcVar11 = pcVar11 + 0x48;
      } while (iVar12 != 8);
      iVar14 = iVar14 + 1;
      pcVar15 = pcVar15 + 0xdc;
    } while (iVar14 < *(int *)(this + 0x74));
  }
  wprintf((char *)(iVar8 + DAT_0006f508),*(undefined4 *)(**(int **)(iVar8 + iVar3) + 0x8128c));
  return;
}
