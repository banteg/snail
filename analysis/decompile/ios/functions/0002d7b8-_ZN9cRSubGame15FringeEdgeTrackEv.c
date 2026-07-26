/*
 * mangled: _ZN9cRSubGame15FringeEdgeTrackEv
 * demangled: cRSubGame::FringeEdgeTrack()
 * address: 0002d7b8
 * size: 4596
 */

/* cRSubGame::FringeEdgeTrack() */

void __thiscall cRSubGame::FringeEdgeTrack(cRSubGame *this)

{
  cRSubGame cVar1;
  cRSubGame cVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined **ppuVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  cRSubGame *pcVar10;
  int iVar11;
  cRSubGame *pcVar12;
  int iVar13;
  uint uVar14;
  int iVar15;
  int iVar16;
  uint uVar17;
  int local_44;
  int local_40;
  int local_28;
  int local_24;

  *(undefined4 *)
   (OFChatRoomInstanceService::getTimeSinceLastRoomUpdated + *(int *)PTR__Game_001b60b8) = 0;
  if (0 < *(int *)(this + 0x6c)) {
    pcVar12 = this + 0x1e41d8;
    local_44 = 0;
    do {
      iVar13 = 0;
      pcVar10 = this + (int)(&PTR_caseD_6_00013458 + local_44 * 0x88);
      do {
        cVar1 = pcVar10[0x31];
        if (cVar1 == (cRSubGame)0x9) {
          iVar11 = 1;
        }
        else if (cVar1 == (cRSubGame)0x5) {
          iVar11 = 3;
        }
        else if (cVar1 == (cRSubGame)0xa) {
          iVar11 = 2;
        }
        else if (cVar1 == (cRSubGame)0x6) {
          iVar11 = 4;
        }
        else {
          iVar11 = 0;
        }
        cVar2 = pcVar10[0x30];
        if (cVar2 == (cRSubGame)0x8 || cVar2 == (cRSubGame)0x2) {
          iVar11 = 5;
LAB_0002d87c:
          if (cVar2 == (cRSubGame)0x9 || cVar2 == (cRSubGame)0x3) {
            iVar11 = 6;
            goto LAB_0002d88c;
          }
          if (((cVar2 != (cRSubGame)0xb && cVar2 != (cRSubGame)0xc) && cVar2 != (cRSubGame)0xd) &&
              cVar2 != (cRSubGame)0x6) goto LAB_0002d88c;
          iVar11 = 6;
LAB_0002db08:
          if (cVar2 == (cRSubGame)0x7) goto LAB_0002d898;
          if ((*(uint *)pcVar12 & 4) == 0) goto LAB_0002d8a8;
LAB_0002db1c:
          *(undefined4 *)(pcVar10 + 0x34) = 0;
          *(undefined4 *)(pcVar10 + 0x38) = 0;
          *(undefined4 *)(pcVar10 + 0x3c) = 0;
          *(undefined4 *)(pcVar10 + 0x40) = 0;
LAB_0002db30:
          if ((*(uint *)pcVar12 & 4) != 0) {
            if (*(int *)(pcVar10 + 0x34) != 0) {
              *(undefined4 *)(pcVar10 + 0x34) = 0;
            }
            if (*(int *)(pcVar10 + 0x40) != 0) {
              *(undefined4 *)(pcVar10 + 0x40) = 0;
            }
            if (*(int *)(pcVar10 + 0x38) != 0) {
              *(undefined4 *)(pcVar10 + 0x38) = 0;
            }
            if (*(int *)(pcVar10 + 0x3c) != 0) {
              *(undefined4 *)(pcVar10 + 0x3c) = 0;
            }
          }
        }
        else {
          if (cVar2 != (cRSubGame)0x5) goto LAB_0002d87c;
          iVar11 = 5;
LAB_0002d88c:
          if (cVar2 != (cRSubGame)0xa && cVar2 != (cRSubGame)0x4) goto LAB_0002db08;
LAB_0002d898:
          iVar11 = 7;
          if ((*(uint *)pcVar12 & 4) != 0) goto LAB_0002db1c;
LAB_0002d8a8:
          if (((cVar1 == (cRSubGame)0x0) || (cVar2 == (cRSubGame)0x20)) ||
             ((*(uint *)(PTR__gConfig_001b60d4 + 0x1c) & 0x20) == 0)) goto LAB_0002db1c;
          ppuVar5 = &PTR_caseD_6_00013458 + local_44 * 0x88 + iVar13 * 0x11;
          iVar15 = *(int *)PTR__Game_001b60b8;
          uVar17 = (byte)this[iVar13 * 0x44 + local_44 * 0x220 + 0x1348a] & 7;
          iVar6 = ((int)(this + ((int)ppuVar5 - (iVar15 + uVar17 * 0x44 + 0x85fd0))) >> 2) *
                  -0xf0f0f0f;
          if (iVar6 < 0) {
            iVar6 = iVar6 + 7;
          }
          iVar6 = iVar6 >> 3;
          if ((((-1 < iVar6) && (iVar7 = *(int *)(this + 0x6c), iVar6 < iVar7)) &&
              ((cVar1 = this[uVar17 * 0x44 + iVar6 * 0x220 + 0x13488],
               cVar1 != (cRSubGame)0x1c && cVar1 != (cRSubGame)0x0 &&
               ((cVar1 != (cRSubGame)0x23 && (cVar1 != (cRSubGame)0xe)))))) &&
             ((cVar1 != (cRSubGame)0x1d &&
              ((cVar1 != (cRSubGame)0x0 && cVar1 != (cRSubGame)0x23 &&
               (cVar1 != (cRSubGame)0x1c && cVar1 != (cRSubGame)0x16)))))) {
            iVar4 = iVar6 + 1;
            if (((iVar4 < 0) ||
                (((iVar7 <= iVar4 ||
                  (cVar1 = this[uVar17 * 0x44 + iVar4 * 0x220 + 0x13488],
                  cVar1 == (cRSubGame)0x1c || cVar1 == (cRSubGame)0x0)) ||
                 (cVar1 == (cRSubGame)0x23)))) ||
               ((((cVar1 == (cRSubGame)0xe || (cVar1 == (cRSubGame)0x1d)) ||
                 (cVar1 == (cRSubGame)0x0 || cVar1 == (cRSubGame)0x23)) ||
                (cVar1 == (cRSubGame)0x1c || cVar1 == (cRSubGame)0x16)))) {
              if (uVar17 == 7) {
LAB_0002dc3c:
                local_24 = 6;
              }
              else if (((iVar4 < 0) || (iVar7 <= iVar4)) ||
                      ((cVar1 = this[(uVar17 + 1) * 0x44 + iVar4 * 0x220 + 0x13488],
                       cVar1 == (cRSubGame)0x1c || cVar1 == (cRSubGame)0x0 ||
                       ((((cVar1 == (cRSubGame)0x23 || (cVar1 == (cRSubGame)0xe)) ||
                         (cVar1 == (cRSubGame)0x1d)) ||
                        ((cVar1 == (cRSubGame)0x0 || cVar1 == (cRSubGame)0x23 ||
                         (cVar1 == (cRSubGame)0x1c || cVar1 == (cRSubGame)0x16)))))))) {
                cVar1 = this[(uVar17 + 1) * 0x44 + iVar6 * 0x220 + 0x13488];
                if (((cVar1 == (cRSubGame)0x1c || cVar1 == (cRSubGame)0x0) ||
                    ((cVar1 == (cRSubGame)0x23 || (cVar1 == (cRSubGame)0xe)))) ||
                   ((cVar1 == (cRSubGame)0x1d ||
                    ((cVar1 == (cRSubGame)0x0 || cVar1 == (cRSubGame)0x23 ||
                     (cVar1 == (cRSubGame)0x1c || cVar1 == (cRSubGame)0x16)))))) goto LAB_0002dc3c;
                local_24 = 3;
              }
              else {
                local_24 = 0;
              }
              uVar17 = uVar17 - 1;
              if (uVar17 < 8) {
                if ((((iVar4 < 0) || (iVar7 <= iVar4)) ||
                    (cVar1 = this[uVar17 * 0x44 + iVar4 * 0x220 + 0x13488],
                    cVar1 == (cRSubGame)0x1c || cVar1 == (cRSubGame)0x0)) ||
                   (((local_40 = 0, cVar1 == (cRSubGame)0x23 || (cVar1 == (cRSubGame)0xe)) ||
                    ((cVar1 == (cRSubGame)0x1d ||
                     ((cVar1 == (cRSubGame)0x0 || cVar1 == (cRSubGame)0x23 ||
                      (cVar1 == (cRSubGame)0x1c || cVar1 == (cRSubGame)0x16)))))))) {
                  cVar1 = this[uVar17 * 0x44 + iVar6 * 0x220 + 0x13488];
                  if (((cVar1 == (cRSubGame)0x1c || cVar1 == (cRSubGame)0x0) ||
                      (((cVar1 == (cRSubGame)0x23 || (cVar1 == (cRSubGame)0xe)) ||
                       (cVar1 == (cRSubGame)0x1d)))) ||
                     ((cVar1 == (cRSubGame)0x0 || cVar1 == (cRSubGame)0x23 ||
                      (cVar1 == (cRSubGame)0x1c || cVar1 == (cRSubGame)0x16)))) goto LAB_0002dcd4;
                  local_40 = 1;
                }
              }
              else {
LAB_0002dcd4:
                local_40 = 2;
              }
              if (*(char **)(OFChatRoomInstanceService::getTimeSinceLastRoomUpdated + iVar15) ==
                  "tem/Library/Frameworks/Security.framework/Security") {
                RShellError("Too many Fringes increase RFRINGEMANAGER_NUMBER");
                puVar3 = (undefined4 *)0x0;
              }
              else {
                *(undefined4 *)
                 ((int)*(char **)(OFChatRoomInstanceService::getTimeSinceLastRoomUpdated + iVar15) *
                  4 + iVar15 + 0x7b18c) = 0;
                puVar3 = (undefined4 *)
                         (iVar15 + *(int *)(OFChatRoomInstanceService::getTimeSinceLastRoomUpdated +
                                           iVar15) * 4 + 0x7b18c);
                *(int *)(OFChatRoomInstanceService::getTimeSinceLastRoomUpdated + iVar15) =
                     *(int *)(OFChatRoomInstanceService::getTimeSinceLastRoomUpdated + iVar15) + 1;
              }
              *(undefined4 **)(pcVar10 + 0x34) = puVar3;
              *puVar3 = *(undefined4 *)
                         ((iVar11 * 0x24 + local_24 + local_40 + 0x3a) * 0x2c +
                          *(int *)PTR__Game_001b60b8 + 0x43e48);
            }
            else {
              *(undefined4 *)(pcVar10 + 0x34) = 0;
            }
            iVar15 = *(int *)PTR__Game_001b60b8;
            uVar17 = (byte)this[iVar13 * 0x44 + local_44 * 0x220 + 0x1348a] & 7;
            iVar6 = ((int)(this + ((int)ppuVar5 - (iVar15 + uVar17 * 0x44 + 0x85fd0))) >> 2) *
                    -0xf0f0f0f;
            iVar7 = uVar17 + 1;
            if (iVar6 < 0) {
              iVar6 = iVar6 + 7;
            }
            iVar6 = iVar6 >> 3;
            if (uVar17 == 7) {
              iVar4 = iVar6 + -1;
              if ((iVar4 < 0) || (*(int *)(this + 0x6c) <= iVar4)) {
                iVar8 = 2;
              }
              else {
                iVar9 = iVar4 * 0x20;
                iVar4 = iVar4 * 0x200;
LAB_0002df08:
                cVar1 = this[uVar17 * 0x44 + iVar9 + iVar4 + 0x13488];
                if (((cVar1 == (cRSubGame)0x1c || cVar1 == (cRSubGame)0x0) ||
                    (cVar1 == (cRSubGame)0x23)) ||
                   ((cVar1 == (cRSubGame)0xe ||
                    (((cVar1 == (cRSubGame)0x1d ||
                      (cVar1 == (cRSubGame)0x0 || cVar1 == (cRSubGame)0x23)) ||
                     (cVar1 == (cRSubGame)0x1c || cVar1 == (cRSubGame)0x16)))))) {
                  iVar8 = 2;
                }
                else {
                  iVar8 = 1;
                }
                if (iVar7 != 8) {
LAB_0002df94:
                  iVar16 = iVar8 * 3;
                  goto LAB_0002df9c;
                }
              }
              iVar6 = iVar6 + 1;
              if ((iVar6 < 0) || (*(int *)(this + 0x6c) <= iVar6)) {
LAB_0002e084:
                iVar16 = iVar8 * 3;
                iVar7 = 2;
              }
              else {
                iVar4 = iVar6 * 0x20;
                iVar6 = iVar6 * 0x200;
LAB_0002e01c:
                cVar1 = this[uVar17 * 0x44 + iVar4 + iVar6 + 0x13488];
                if ((cVar1 == (cRSubGame)0x1c || cVar1 == (cRSubGame)0x0) ||
                   (((cVar1 == (cRSubGame)0x23 || (cVar1 == (cRSubGame)0xe)) ||
                    ((cVar1 == (cRSubGame)0x1d ||
                     ((cVar1 == (cRSubGame)0x0 || cVar1 == (cRSubGame)0x23 ||
                      (cVar1 == (cRSubGame)0x1c || cVar1 == (cRSubGame)0x16))))))))
                goto LAB_0002e084;
                iVar16 = iVar8 * 3;
                iVar7 = 1;
              }
LAB_0002e090:
              if (*(char **)(OFChatRoomInstanceService::getTimeSinceLastRoomUpdated + iVar15) ==
                  "tem/Library/Frameworks/Security.framework/Security") {
                RShellError("Too many Fringes increase RFRINGEMANAGER_NUMBER");
                puVar3 = (undefined4 *)0x0;
              }
              else {
                *(undefined4 *)
                 ((int)*(char **)(OFChatRoomInstanceService::getTimeSinceLastRoomUpdated + iVar15) *
                  4 + iVar15 + 0x7b18c) = 0;
                puVar3 = (undefined4 *)
                         (iVar15 + *(int *)(OFChatRoomInstanceService::getTimeSinceLastRoomUpdated +
                                           iVar15) * 4 + 0x7b18c);
                *(int *)(OFChatRoomInstanceService::getTimeSinceLastRoomUpdated + iVar15) =
                     *(int *)(OFChatRoomInstanceService::getTimeSinceLastRoomUpdated + iVar15) + 1;
              }
              *(undefined4 **)(pcVar10 + 0x38) = puVar3;
              *puVar3 = *(undefined4 *)
                         ((iVar11 * 0x24 + iVar7 + iVar16 + 0x43) * 0x2c +
                          *(int *)PTR__Game_001b60b8 + 0x43e48);
            }
            else {
              if ((((((iVar6 < 0) || (*(int *)(this + 0x6c) <= iVar6)) ||
                    (cVar1 = this[iVar7 * 0x44 + iVar6 * 0x220 + 0x13488],
                    cVar1 == (cRSubGame)0x1c || cVar1 == (cRSubGame)0x0)) ||
                   ((cVar1 == (cRSubGame)0x23 || (cVar1 == (cRSubGame)0xe)))) ||
                  (cVar1 == (cRSubGame)0x1d)) ||
                 ((cVar1 == (cRSubGame)0x0 || cVar1 == (cRSubGame)0x23 ||
                  (cVar1 == (cRSubGame)0x1c || cVar1 == (cRSubGame)0x16)))) {
                iVar8 = iVar6 + -1;
                if ((iVar8 < 0) || (*(int *)(this + 0x6c) <= iVar8)) {
                  iVar8 = 2;
                  goto LAB_0002df94;
                }
                iVar4 = iVar8 * 0x200;
                iVar9 = iVar8 * 0x20;
                cVar1 = this[iVar7 * 0x44 + iVar8 * 0x220 + 0x13488];
                if ((((cVar1 == (cRSubGame)0x1c || cVar1 == (cRSubGame)0x0) ||
                     (iVar8 = 0, cVar1 == (cRSubGame)0x23)) || (cVar1 == (cRSubGame)0xe)) ||
                   (((cVar1 == (cRSubGame)0x1d ||
                     (cVar1 == (cRSubGame)0x0 || cVar1 == (cRSubGame)0x23)) ||
                    (iVar16 = iVar8, cVar1 == (cRSubGame)0x1c || cVar1 == (cRSubGame)0x16))))
                goto LAB_0002df08;
LAB_0002df9c:
                iVar9 = iVar6 + 1;
                if ((-1 < iVar9) && (iVar9 < *(int *)(this + 0x6c))) {
                  iVar6 = iVar9 * 0x200;
                  iVar4 = iVar9 * 0x20;
                  cVar1 = this[iVar7 * 0x44 + iVar9 * 0x220 + 0x13488];
                  if ((cVar1 == (cRSubGame)0x1c || cVar1 == (cRSubGame)0x0) ||
                     ((((iVar7 = 0, cVar1 == (cRSubGame)0x23 || (cVar1 == (cRSubGame)0xe)) ||
                       (cVar1 == (cRSubGame)0x1d)) ||
                      ((cVar1 == (cRSubGame)0x0 || cVar1 == (cRSubGame)0x23 ||
                       (cVar1 == (cRSubGame)0x1c || cVar1 == (cRSubGame)0x16))))))
                  goto LAB_0002e01c;
                  goto LAB_0002e090;
                }
                goto LAB_0002e084;
              }
              *(undefined4 *)(pcVar10 + 0x38) = 0;
            }
            iVar15 = *(int *)PTR__Game_001b60b8;
            uVar17 = (byte)this[iVar13 * 0x44 + local_44 * 0x220 + 0x1348a] & 7;
            uVar14 = uVar17 - 1;
            iVar6 = ((int)(this + ((int)ppuVar5 - (iVar15 + uVar17 * 0x44 + 0x85fd0))) >> 2) *
                    -0xf0f0f0f;
            if (iVar6 < 0) {
              iVar6 = iVar6 + 7;
            }
            iVar6 = iVar6 >> 3;
            if (uVar14 < 8) {
              if ((((iVar6 < 0) || (*(int *)(this + 0x6c) <= iVar6)) ||
                  (cVar1 = this[uVar14 * 0x44 + iVar6 * 0x220 + 0x13488],
                  cVar1 == (cRSubGame)0x1c || cVar1 == (cRSubGame)0x0)) ||
                 (((cVar1 == (cRSubGame)0x23 || (cVar1 == (cRSubGame)0xe)) ||
                  ((cVar1 == (cRSubGame)0x1d ||
                   ((cVar1 == (cRSubGame)0x0 || cVar1 == (cRSubGame)0x23 ||
                    (cVar1 == (cRSubGame)0x1c || cVar1 == (cRSubGame)0x16)))))))) {
                iVar9 = iVar6 + 1;
                if ((iVar9 < 0) || (*(int *)(this + 0x6c) <= iVar9)) {
                  iVar9 = 2;
                  goto LAB_0002e250;
                }
                iVar7 = iVar9 * 0x200;
                iVar4 = iVar9 * 0x20;
                cVar1 = this[uVar14 * 0x44 + iVar9 * 0x220 + 0x13488];
                if (((((cVar1 == (cRSubGame)0x1c || cVar1 == (cRSubGame)0x0) ||
                      (iVar8 = 0, cVar1 == (cRSubGame)0x23)) || (cVar1 == (cRSubGame)0xe)) ||
                    ((cVar1 == (cRSubGame)0x1d ||
                     (cVar1 == (cRSubGame)0x0 || cVar1 == (cRSubGame)0x23)))) ||
                   (iVar9 = iVar8, cVar1 == (cRSubGame)0x1c || cVar1 == (cRSubGame)0x16))
                goto LAB_0002e860;
LAB_0002e258:
                iVar6 = iVar6 + -1;
                if ((-1 < iVar6) && (iVar6 < *(int *)(this + 0x6c))) {
                  iVar7 = iVar6 * 0x200;
                  iVar4 = iVar6 * 0x20;
                  cVar1 = this[uVar14 * 0x44 + iVar6 * 0x220 + 0x13488];
                  if ((cVar1 == (cRSubGame)0x1c || cVar1 == (cRSubGame)0x0) ||
                     ((((iVar6 = 0, cVar1 == (cRSubGame)0x23 || (cVar1 == (cRSubGame)0xe)) ||
                       (cVar1 == (cRSubGame)0x1d)) ||
                      ((cVar1 == (cRSubGame)0x0 || cVar1 == (cRSubGame)0x23 ||
                       (cVar1 == (cRSubGame)0x1c || cVar1 == (cRSubGame)0x16))))))
                  goto LAB_0002e2d8;
                  goto LAB_0002e34c;
                }
                goto LAB_0002e340;
              }
              *(undefined4 *)(pcVar10 + 0x3c) = 0;
            }
            else {
              iVar7 = iVar6 + 1;
              if ((iVar7 < 0) || (*(int *)(this + 0x6c) <= iVar7)) {
                iVar9 = 2;
              }
              else {
                iVar4 = iVar7 * 0x20;
                iVar7 = iVar7 * 0x200;
LAB_0002e860:
                cVar1 = this[uVar17 * 0x44 + iVar4 + iVar7 + 0x13488];
                if (((cVar1 == (cRSubGame)0x1c || cVar1 == (cRSubGame)0x0) ||
                    (cVar1 == (cRSubGame)0x23)) ||
                   ((cVar1 == (cRSubGame)0xe ||
                    (((cVar1 == (cRSubGame)0x1d ||
                      (cVar1 == (cRSubGame)0x0 || cVar1 == (cRSubGame)0x23)) ||
                     (cVar1 == (cRSubGame)0x1c || cVar1 == (cRSubGame)0x16)))))) {
                  iVar9 = 2;
                }
                else {
                  iVar9 = 1;
                }
                if (uVar14 < 8) {
LAB_0002e250:
                  iVar8 = iVar9 * 3;
                  goto LAB_0002e258;
                }
              }
              iVar6 = iVar6 + -1;
              if ((iVar6 < 0) || (*(int *)(this + 0x6c) <= iVar6)) {
LAB_0002e340:
                iVar8 = iVar9 * 3;
                iVar6 = 2;
              }
              else {
                iVar4 = iVar6 * 0x20;
                iVar7 = iVar6 * 0x200;
LAB_0002e2d8:
                cVar1 = this[uVar17 * 0x44 + iVar4 + iVar7 + 0x13488];
                if ((cVar1 == (cRSubGame)0x1c || cVar1 == (cRSubGame)0x0) ||
                   (((cVar1 == (cRSubGame)0x23 || (cVar1 == (cRSubGame)0xe)) ||
                    ((cVar1 == (cRSubGame)0x1d ||
                     ((cVar1 == (cRSubGame)0x0 || cVar1 == (cRSubGame)0x23 ||
                      (cVar1 == (cRSubGame)0x1c || cVar1 == (cRSubGame)0x16))))))))
                goto LAB_0002e340;
                iVar8 = iVar9 * 3;
                iVar6 = 1;
              }
LAB_0002e34c:
              if (*(char **)(OFChatRoomInstanceService::getTimeSinceLastRoomUpdated + iVar15) ==
                  "tem/Library/Frameworks/Security.framework/Security") {
                RShellError("Too many Fringes increase RFRINGEMANAGER_NUMBER");
                puVar3 = (undefined4 *)0x0;
              }
              else {
                *(undefined4 *)
                 ((int)*(char **)(OFChatRoomInstanceService::getTimeSinceLastRoomUpdated + iVar15) *
                  4 + iVar15 + 0x7b18c) = 0;
                puVar3 = (undefined4 *)
                         (iVar15 + *(int *)(OFChatRoomInstanceService::getTimeSinceLastRoomUpdated +
                                           iVar15) * 4 + 0x7b18c);
                *(int *)(OFChatRoomInstanceService::getTimeSinceLastRoomUpdated + iVar15) =
                     *(int *)(OFChatRoomInstanceService::getTimeSinceLastRoomUpdated + iVar15) + 1;
              }
              *(undefined4 **)(pcVar10 + 0x3c) = puVar3;
              *puVar3 = *(undefined4 *)
                         ((iVar11 * 0x24 + iVar6 + iVar8 + 0x4c) * 0x2c + *(int *)PTR__Game_001b60b8
                         + 0x43e48);
            }
            iVar15 = *(int *)PTR__Game_001b60b8;
            uVar17 = (byte)this[iVar13 * 0x44 + local_44 * 0x220 + 0x1348a] & 7;
            iVar6 = ((int)(this + ((int)ppuVar5 - (iVar15 + uVar17 * 0x44 + 0x85fd0))) >> 2) *
                    -0xf0f0f0f;
            if (iVar6 < 0) {
              iVar6 = iVar6 + 7;
            }
            iVar6 = iVar6 >> 3;
            iVar7 = iVar6 + -1;
            if ((((iVar7 < 0) || (*(int *)(this + 0x6c) <= iVar7)) ||
                (cVar1 = this[uVar17 * 0x44 + iVar7 * 0x220 + 0x13488],
                cVar1 == (cRSubGame)0x1c || cVar1 == (cRSubGame)0x0)) ||
               (((cVar1 == (cRSubGame)0x23 || (cVar1 == (cRSubGame)0xe)) ||
                ((cVar1 == (cRSubGame)0x1d ||
                 ((cVar1 == (cRSubGame)0x0 || cVar1 == (cRSubGame)0x23 ||
                  (cVar1 == (cRSubGame)0x1c || cVar1 == (cRSubGame)0x16)))))))) {
              uVar14 = uVar17 - 1;
              if (uVar14 < 8) {
                if ((((iVar7 < 0) || (*(int *)(this + 0x6c) <= iVar7)) ||
                    (cVar1 = this[uVar14 * 0x44 + iVar7 * 0x220 + 0x13488],
                    cVar1 == (cRSubGame)0x1c || cVar1 == (cRSubGame)0x0)) ||
                   (((cVar1 == (cRSubGame)0x23 || (cVar1 == (cRSubGame)0xe)) ||
                    ((cVar1 == (cRSubGame)0x1d ||
                     ((cVar1 == (cRSubGame)0x0 || cVar1 == (cRSubGame)0x23 ||
                      (cVar1 == (cRSubGame)0x1c || cVar1 == (cRSubGame)0x16)))))))) {
                  if (((iVar6 < 0) ||
                      (((((*(int *)(this + 0x6c) <= iVar6 ||
                          (cVar1 = this[uVar14 * 0x44 + iVar6 * 0x220 + 0x13488],
                          cVar1 == (cRSubGame)0x1c || cVar1 == (cRSubGame)0x0)) ||
                         (cVar1 == (cRSubGame)0x23)) ||
                        ((cVar1 == (cRSubGame)0xe || (cVar1 == (cRSubGame)0x1d)))) ||
                       (cVar1 == (cRSubGame)0x0 || cVar1 == (cRSubGame)0x23)))) ||
                     (cVar1 == (cRSubGame)0x1c || cVar1 == (cRSubGame)0x16)) goto LAB_0002e5e4;
                  local_28 = 3;
                }
                else {
                  local_28 = 0;
                }
              }
              else {
LAB_0002e5e4:
                local_28 = 6;
              }
              if (uVar17 == 7) {
LAB_0002e6f4:
                iVar7 = 2;
              }
              else if (((iVar7 < 0) || (*(int *)(this + 0x6c) <= iVar7)) ||
                      (((cVar1 = this[(uVar17 + 1) * 0x44 + iVar7 * 0x220 + 0x13488],
                        cVar1 == (cRSubGame)0x1c || cVar1 == (cRSubGame)0x0 ||
                        (((iVar7 = 0, cVar1 == (cRSubGame)0x23 || (cVar1 == (cRSubGame)0xe)) ||
                         (cVar1 == (cRSubGame)0x1d)))) ||
                       ((cVar1 == (cRSubGame)0x0 || cVar1 == (cRSubGame)0x23 ||
                        (cVar1 == (cRSubGame)0x1c || cVar1 == (cRSubGame)0x16)))))) {
                if ((iVar6 < 0) ||
                   ((((*(int *)(this + 0x6c) <= iVar6 ||
                      (cVar1 = this[(uVar17 + 1) * 0x44 + iVar6 * 0x220 + 0x13488],
                      cVar1 == (cRSubGame)0x1c || cVar1 == (cRSubGame)0x0)) ||
                     ((cVar1 == (cRSubGame)0x23 ||
                      (((cVar1 == (cRSubGame)0xe || (cVar1 == (cRSubGame)0x1d)) ||
                       (cVar1 == (cRSubGame)0x0 || cVar1 == (cRSubGame)0x23)))))) ||
                    (cVar1 == (cRSubGame)0x1c || cVar1 == (cRSubGame)0x16)))) goto LAB_0002e6f4;
                iVar7 = 1;
              }
              if (*(char **)(OFChatRoomInstanceService::getTimeSinceLastRoomUpdated + iVar15) ==
                  "tem/Library/Frameworks/Security.framework/Security") {
                RShellError("Too many Fringes increase RFRINGEMANAGER_NUMBER");
                puVar3 = (undefined4 *)0x0;
              }
              else {
                *(undefined4 *)
                 ((int)*(char **)(OFChatRoomInstanceService::getTimeSinceLastRoomUpdated + iVar15) *
                  4 + iVar15 + 0x7b18c) = 0;
                puVar3 = (undefined4 *)
                         (iVar15 + *(int *)(OFChatRoomInstanceService::getTimeSinceLastRoomUpdated +
                                           iVar15) * 4 + 0x7b18c);
                *(int *)(OFChatRoomInstanceService::getTimeSinceLastRoomUpdated + iVar15) =
                     *(int *)(OFChatRoomInstanceService::getTimeSinceLastRoomUpdated + iVar15) + 1;
              }
              *(undefined4 **)(pcVar10 + 0x40) = puVar3;
              *puVar3 = *(undefined4 *)
                         ((iVar11 * 0x24 + iVar7 + local_28 + 0x55) * 0x2c +
                          *(int *)PTR__Game_001b60b8 + 0x43e48);
            }
            else {
              *(undefined4 *)(pcVar10 + 0x40) = 0;
            }
            goto LAB_0002db30;
          }
        }
        iVar13 = iVar13 + 1;
        pcVar10 = pcVar10 + 0x44;
      } while (iVar13 != 8);
      pcVar12 = pcVar12 + 0xdc;
      local_44 = local_44 + 1;
    } while (local_44 < *(int *)(this + 0x6c));
  }
  wprintf("Used %i fringe bods\n",
          *(undefined4 *)
           (OFChatRoomInstanceService::getTimeSinceLastRoomUpdated + *(int *)PTR__Game_001b60b8));
  return;
}
