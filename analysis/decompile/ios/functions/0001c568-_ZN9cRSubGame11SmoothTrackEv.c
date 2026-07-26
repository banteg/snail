/*
 * mangled: _ZN9cRSubGame11SmoothTrackEv
 * demangled: cRSubGame::SmoothTrack()
 * address: 0001c568
 * size: 1540
 */

/* cRSubGame::SmoothTrack() */

void __thiscall cRSubGame::SmoothTrack(cRSubGame *this)

{
  cRSubGame cVar1;
  int iVar2;
  cRSubGame *pcVar3;
  int iVar4;
  int iVar5;
  bool bVar6;

  if (0 < *(int *)(this + 0x6c)) {
    iVar5 = 0;
    do {
      pcVar3 = this + (int)(&PTR_caseD_6_00013458 + iVar5 * 0x88);
      iVar4 = 0;
      do {
        pcVar3[0x31] = (cRSubGame)0x0;
        iVar2 = iVar4 * 0x44 + iVar5 * 0x220;
        this[iVar2 + 0x1348b] = (cRSubGame)((byte)this[iVar2 + 0x1348b] & 0x7f);
        cVar1 = pcVar3[0x30];
        if ((cVar1 == (cRSubGame)0x0 || cVar1 == (cRSubGame)0x23) ||
           (((cVar1 == (cRSubGame)0x1c || cVar1 == (cRSubGame)0x1d) || cVar1 == (cRSubGame)0x1e) ||
            cVar1 == (cRSubGame)0xe)) goto switchD_0001c6cc_caseD_7;
        if (((iVar4 == 0) ||
            (((cVar1 = pcVar3[-0x14], cVar1 == (cRSubGame)0x1c || cVar1 == (cRSubGame)0x0 ||
              (cVar1 == (cRSubGame)0x23)) || (cVar1 == (cRSubGame)0xe)))) ||
           (cVar1 == (cRSubGame)0x1d)) {
          pcVar3[0x31] = (cRSubGame)((byte)pcVar3[0x31] | 8);
          if (iVar4 != 7) goto LAB_0001c630;
LAB_0001cb74:
          pcVar3[0x31] = (cRSubGame)((byte)pcVar3[0x31] | 4);
        }
        else {
          if (iVar4 == 7) goto LAB_0001cb74;
LAB_0001c630:
          cVar1 = pcVar3[0x74];
          if (((cVar1 == (cRSubGame)0x1c || cVar1 == (cRSubGame)0x0) || (cVar1 == (cRSubGame)0x23))
             || ((cVar1 == (cRSubGame)0xe || (cVar1 == (cRSubGame)0x1d)))) goto LAB_0001cb74;
        }
        if (((iVar5 == 0) ||
            (cVar1 = pcVar3[-0x1f0], cVar1 == (cRSubGame)0x1c || cVar1 == (cRSubGame)0x0)) ||
           ((cVar1 == (cRSubGame)0x23 || ((cVar1 == (cRSubGame)0xe || (cVar1 == (cRSubGame)0x1d)))))
           ) {
          pcVar3[0x31] = (cRSubGame)((byte)pcVar3[0x31] | 1);
        }
        if ((((*(int *)(this + 0x6c) + -1 <= iVar5) ||
             (cVar1 = pcVar3[0x250], cVar1 == (cRSubGame)0x1c || cVar1 == (cRSubGame)0x0)) ||
            (cVar1 == (cRSubGame)0x23)) || ((cVar1 == (cRSubGame)0xe || (cVar1 == (cRSubGame)0x1d)))
           ) {
          pcVar3[0x31] = (cRSubGame)((byte)pcVar3[0x31] | 2);
        }
        switch(pcVar3[0x31]) {
        case (cRSubGame)0x5:
          iVar2 = iVar4 * 0x44 + iVar5 * 0x220;
          this[iVar2 + 0x1348b] = (cRSubGame)((byte)this[iVar2 + 0x1348b] | 0x80);
          cVar1 = pcVar3[0x30];
          if (((cVar1 != (cRSubGame)0x14 && cVar1 != (cRSubGame)0x1) &&
              ((cVar1 != (cRSubGame)0x15 && cVar1 != (cRSubGame)0x1b) && cVar1 != (cRSubGame)0x21))
             && (cVar1 != (cRSubGame)0x22)) {
            if (cVar1 != (cRSubGame)0xe && cVar1 != (cRSubGame)0x16) {
              bVar6 = 7 < (byte)cVar1;
              if (cVar1 != (cRSubGame)0x8) {
                bVar6 = 1 < (byte)((char)cVar1 - 2U);
              }
              if ((((bVar6 && (cVar1 != (cRSubGame)0x8 && (byte)((char)cVar1 - 2U) != 2)) &&
                   (((((cVar1 != (cRSubGame)0x9 && cVar1 != (cRSubGame)0xa) &&
                      cVar1 != (cRSubGame)0xb) && cVar1 != (cRSubGame)0xc) &&
                    cVar1 != (cRSubGame)0xd) && cVar1 != (cRSubGame)0x5)) &&
                  (cVar1 != (cRSubGame)0x6)) && (cVar1 != (cRSubGame)0x7)) {
                cRBod::SetObject((cRBod *)(this + (int)(&PTR_caseD_6_00013458 +
                                                       iVar5 * 0x88 + iVar4 * 0x11)),
                                 *(cRObject **)(*(int *)PTR__Game_001b60b8 + 0x440b0));
              }
            }
            break;
          }
          cRBod::SetObject((cRBod *)(this + (int)(&PTR_caseD_6_00013458 +
                                                 iVar5 * 0x88 + iVar4 * 0x11)),
                           *(cRObject **)(*(int *)PTR__Game_001b60b8 + 0x43f50));
          goto joined_r0x0001caf4;
        case (cRSubGame)0x6:
          iVar2 = iVar4 * 0x44 + iVar5 * 0x220;
          this[iVar2 + 0x1348b] = (cRSubGame)((byte)this[iVar2 + 0x1348b] | 0x80);
          cVar1 = pcVar3[0x30];
          if (((cVar1 == (cRSubGame)0x14 || cVar1 == (cRSubGame)0x1) ||
              ((cVar1 == (cRSubGame)0x15 || cVar1 == (cRSubGame)0x1b) || cVar1 == (cRSubGame)0x21))
             || (cVar1 == (cRSubGame)0x22)) {
            cRBod::SetObject((cRBod *)(this + (int)(&PTR_caseD_6_00013458 +
                                                   iVar5 * 0x88 + iVar4 * 0x11)),
                             *(cRObject **)(*(int *)PTR__Game_001b60b8 + 0x43fa8));
            goto joined_r0x0001caf4;
          }
          if (cVar1 != (cRSubGame)0xe && cVar1 != (cRSubGame)0x16) {
            bVar6 = 7 < (byte)cVar1;
            if (cVar1 != (cRSubGame)0x8) {
              bVar6 = 1 < (byte)((char)cVar1 - 2U);
            }
            if (((bVar6 && (cVar1 != (cRSubGame)0x8 && (byte)((char)cVar1 - 2U) != 2)) &&
                (((((cVar1 != (cRSubGame)0x9 && cVar1 != (cRSubGame)0xa) && cVar1 != (cRSubGame)0xb)
                  && cVar1 != (cRSubGame)0xc) && cVar1 != (cRSubGame)0xd) && cVar1 != (cRSubGame)0x5
                )) && ((cVar1 != (cRSubGame)0x6 && (cVar1 != (cRSubGame)0x7)))) {
              cRBod::SetObject((cRBod *)(this + (int)(&PTR_caseD_6_00013458 +
                                                     iVar5 * 0x88 + iVar4 * 0x11)),
                               *(cRObject **)(*(int *)PTR__Game_001b60b8 + 0x44108));
            }
          }
          break;
        case (cRSubGame)0x9:
          iVar2 = iVar4 * 0x44 + iVar5 * 0x220;
          this[iVar2 + 0x1348b] = (cRSubGame)((byte)this[iVar2 + 0x1348b] | 0x80);
          cVar1 = pcVar3[0x30];
          if (((cVar1 == (cRSubGame)0x14 || cVar1 == (cRSubGame)0x1) ||
              ((cVar1 == (cRSubGame)0x15 || cVar1 == (cRSubGame)0x1b) || cVar1 == (cRSubGame)0x21))
             || (cVar1 == (cRSubGame)0x22)) {
            cRBod::SetObject((cRBod *)(this + (int)(&PTR_caseD_6_00013458 +
                                                   iVar5 * 0x88 + iVar4 * 0x11)),
                             *(cRObject **)(*(int *)PTR__Game_001b60b8 + 0x43f24));
            goto joined_r0x0001caf4;
          }
          if (cVar1 != (cRSubGame)0xe && cVar1 != (cRSubGame)0x16) {
            bVar6 = 7 < (byte)cVar1;
            if (cVar1 != (cRSubGame)0x8) {
              bVar6 = 1 < (byte)((char)cVar1 - 2U);
            }
            if (((bVar6 && (cVar1 != (cRSubGame)0x8 && (byte)((char)cVar1 - 2U) != 2)) &&
                (((((cVar1 != (cRSubGame)0x9 && cVar1 != (cRSubGame)0xa) && cVar1 != (cRSubGame)0xb)
                  && cVar1 != (cRSubGame)0xc) && cVar1 != (cRSubGame)0xd) && cVar1 != (cRSubGame)0x5
                )) && ((cVar1 != (cRSubGame)0x6 && (cVar1 != (cRSubGame)0x7)))) {
              cRBod::SetObject((cRBod *)(this + (int)(&PTR_caseD_6_00013458 +
                                                     iVar5 * 0x88 + iVar4 * 0x11)),
                               *(cRObject **)(*(int *)PTR__Game_001b60b8 + 0x44084));
            }
          }
          break;
        case (cRSubGame)0xa:
          iVar2 = iVar4 * 0x44 + iVar5 * 0x220;
          this[iVar2 + 0x1348b] = (cRSubGame)((byte)this[iVar2 + 0x1348b] | 0x80);
          cVar1 = pcVar3[0x30];
          if (((cVar1 == (cRSubGame)0x14 || cVar1 == (cRSubGame)0x1) ||
              ((cVar1 == (cRSubGame)0x15 || cVar1 == (cRSubGame)0x1b) || cVar1 == (cRSubGame)0x21))
             || (cVar1 == (cRSubGame)0x22)) {
            cRBod::SetObject((cRBod *)(this + (int)(&PTR_caseD_6_00013458 +
                                                   iVar5 * 0x88 + iVar4 * 0x11)),
                             *(cRObject **)(*(int *)PTR__Game_001b60b8 + 0x43f7c));
            goto joined_r0x0001caf4;
          }
          if (cVar1 != (cRSubGame)0xe && cVar1 != (cRSubGame)0x16) {
            bVar6 = 7 < (byte)cVar1;
            if (cVar1 != (cRSubGame)0x8) {
              bVar6 = 1 < (byte)((char)cVar1 - 2U);
            }
            if ((((bVar6 && (cVar1 != (cRSubGame)0x8 && (byte)((char)cVar1 - 2U) != 2)) &&
                 (((((cVar1 != (cRSubGame)0x9 && cVar1 != (cRSubGame)0xa) && cVar1 != (cRSubGame)0xb
                    ) && cVar1 != (cRSubGame)0xc) && cVar1 != (cRSubGame)0xd) &&
                  cVar1 != (cRSubGame)0x5)) && (cVar1 != (cRSubGame)0x6)) &&
               (cVar1 != (cRSubGame)0x7)) {
              cRBod::SetObject((cRBod *)(this + (int)(&PTR_caseD_6_00013458 +
                                                     iVar5 * 0x88 + iVar4 * 0x11)),
                               *(cRObject **)(*(int *)PTR__Game_001b60b8 + 0x440dc));
            }
          }
        }
switchD_0001c6cc_caseD_7:
joined_r0x0001caf4:
        pcVar3 = pcVar3 + 0x44;
        iVar4 = iVar4 + 1;
      } while (iVar4 != 8);
      iVar5 = iVar5 + 1;
    } while (iVar5 < *(int *)(this + 0x6c));
  }
  return;
}
