/*
 * mangled: _ZN9cRSubGame16SlideSmoothTrackEv
 * demangled: cRSubGame::SlideSmoothTrack()
 * address: 0001a414
 * size: 3048
 */

/* cRSubGame::SlideSmoothTrack() */

void __thiscall cRSubGame::SlideSmoothTrack(cRSubGame *this)

{
  cRSubGame cVar1;
  uint uVar2;
  int iVar3;
  cRSubGame cVar4;
  cRSubGame *pcVar5;
  int iVar6;
  int iVar7;
  uint local_28;

  if (0 < *(int *)(this + 0x6c) + -1) {
    local_28 = 0;
    do {
      uVar2 = local_28 + 1;
      pcVar5 = this + (int)(&PTR_caseD_6_00013458 + local_28 * 0x88);
      iVar6 = 0;
LAB_0001a494:
      do {
        if ((local_28 & 7) == 3) {
          if ((((byte)this[iVar6 * 0x44 + local_28 * 0x220 + 0x1348a] & 0x20) == 0) &&
             (((byte)this[iVar6 * 0x44 + uVar2 * 0x220 + 0x1348a] & 0x20) == 0)) {
            cVar4 = pcVar5[0x30];
            if (((cVar4 == (cRSubGame)0x14 || cVar4 == (cRSubGame)0x1) ||
                ((((cVar4 == (cRSubGame)0x15 || (cVar4 == (cRSubGame)0x21)) ||
                  (cVar4 == (cRSubGame)0x22)) || (cVar4 == (cRSubGame)0x1b)))) &&
               (((cVar1 = pcVar5[0x250], cVar1 == (cRSubGame)0x17 || cVar1 == (cRSubGame)0xf ||
                 (((((cVar1 == (cRSubGame)0x18 || cVar1 == (cRSubGame)0x19) ||
                    cVar1 == (cRSubGame)0x1a) || cVar1 == (cRSubGame)0x10) ||
                  cVar1 == (cRSubGame)0x12) || cVar1 == (cRSubGame)0x13)) ||
                (cVar1 == (cRSubGame)0x1e)))) {
              iVar3 = *(int *)(pcVar5 + 0x24);
              if (iVar3 == *(int *)(*(int *)PTR__Game_001b60b8 + 0x44370)) {
                iVar3 = iVar6 * 0x44 + local_28 * 0x220;
                cRBod::SetObject((cRBod *)(this + (int)(&PTR_caseD_6_00013458 +
                                                       local_28 * 0x88 + iVar6 * 0x11)),
                                 *(cRObject **)(*(int *)PTR__Game_001b60b8 + 0x44630));
                this[iVar3 + 0x1348a] = (cRSubGame)((byte)this[iVar3 + 0x1348a] | 0x40);
                iVar3 = *(int *)(pcVar5 + 0x24);
              }
              if (iVar3 == *(int *)(*(int *)PTR__Game_001b60b8 + 0x43f24)) {
                iVar3 = iVar6 * 0x44 + local_28 * 0x220;
                cRBod::SetObject((cRBod *)(this + (int)(&PTR_caseD_6_00013458 +
                                                       local_28 * 0x88 + iVar6 * 0x11)),
                                 *(cRObject **)(*(int *)PTR__Game_001b60b8 + 0x44084));
                this[iVar3 + 0x1348a] = (cRSubGame)((byte)this[iVar3 + 0x1348a] | 0x40);
                iVar3 = *(int *)(pcVar5 + 0x24);
              }
              if (iVar3 == *(int *)(*(int *)PTR__Game_001b60b8 + 0x43f50)) {
                iVar3 = iVar6 * 0x44 + local_28 * 0x220;
                cRBod::SetObject((cRBod *)(this + (int)(&PTR_caseD_6_00013458 +
                                                       local_28 * 0x88 + iVar6 * 0x11)),
                                 *(cRObject **)(*(int *)PTR__Game_001b60b8 + 0x440b0));
                this[iVar3 + 0x1348a] = (cRSubGame)((byte)this[iVar3 + 0x1348a] | 0x40);
                iVar3 = *(int *)(pcVar5 + 0x24);
              }
              if (iVar3 == *(int *)(*(int *)PTR__Game_001b60b8 + 0x43f7c)) {
                iVar3 = iVar6 * 0x44 + local_28 * 0x220;
                cRBod::SetObject((cRBod *)(this + (int)(&PTR_caseD_6_00013458 +
                                                       local_28 * 0x88 + iVar6 * 0x11)),
                                 *(cRObject **)(*(int *)PTR__Game_001b60b8 + 0x440dc));
                this[iVar3 + 0x1348a] = (cRSubGame)((byte)this[iVar3 + 0x1348a] | 0x40);
                iVar7 = *(int *)PTR__Game_001b60b8;
                if (*(int *)(iVar7 + 0x43fa8) == *(int *)(pcVar5 + 0x24)) goto LAB_0001ab40;
              }
              else {
                iVar7 = *(int *)PTR__Game_001b60b8;
                if (*(int *)(iVar7 + 0x43fa8) == iVar3) {
LAB_0001ab40:
                  iVar3 = iVar6 * 0x44 + local_28 * 0x220;
                  cRBod::SetObject((cRBod *)(this + (int)(&PTR_caseD_6_00013458 +
                                                         local_28 * 0x88 + iVar6 * 0x11)),
                                   *(cRObject **)(iVar7 + 0x44108));
                  this[iVar3 + 0x1348a] = (cRSubGame)((byte)this[iVar3 + 0x1348a] | 0x40);
                }
              }
              if ((((byte)this[iVar6 * 0x44 + local_28 * 0x220 + 0x1348a] & 0x20) != 0) ||
                 (((byte)this[iVar6 * 0x44 + uVar2 * 0x220 + 0x1348a] & 0x20) != 0))
              goto LAB_0001a484;
              cVar4 = pcVar5[0x30];
            }
            if (((((cVar4 == (cRSubGame)0x17 || cVar4 == (cRSubGame)0xf) ||
                  (cVar4 == (cRSubGame)0x18)) || (cVar4 == (cRSubGame)0x19)) ||
                (((cVar4 == (cRSubGame)0x1a || (cVar4 == (cRSubGame)0x10)) ||
                 ((cVar4 == (cRSubGame)0x12 || (cVar4 == (cRSubGame)0x13)))))) &&
               ((((cVar4 = pcVar5[0x250], cVar4 == (cRSubGame)0x14 || cVar4 == (cRSubGame)0x1 ||
                  (cVar4 == (cRSubGame)0x15)) || (cVar4 == (cRSubGame)0x21)) ||
                ((cVar4 == (cRSubGame)0x22 || (cVar4 == (cRSubGame)0x1b)))))) {
              iVar3 = *(int *)(pcVar5 + 0x24);
              if (iVar3 == *(int *)(*(int *)PTR__Game_001b60b8 + 0x44630)) {
                iVar3 = iVar6 * 0x44 + local_28 * 0x220;
                cRBod::SetObject((cRBod *)(this + (int)(&PTR_caseD_6_00013458 +
                                                       local_28 * 0x88 + iVar6 * 0x11)),
                                 *(cRObject **)(*(int *)PTR__Game_001b60b8 + 0x44370));
                this[iVar3 + 0x1348a] = (cRSubGame)((byte)this[iVar3 + 0x1348a] | 0x40);
                iVar3 = *(int *)(pcVar5 + 0x24);
              }
              if (iVar3 == *(int *)(*(int *)PTR__Game_001b60b8 + 0x44084)) {
                iVar3 = iVar6 * 0x44 + local_28 * 0x220;
                cRBod::SetObject((cRBod *)(this + (int)(&PTR_caseD_6_00013458 +
                                                       local_28 * 0x88 + iVar6 * 0x11)),
                                 *(cRObject **)(*(int *)PTR__Game_001b60b8 + 0x43f24));
                this[iVar3 + 0x1348a] = (cRSubGame)((byte)this[iVar3 + 0x1348a] | 0x40);
                iVar3 = *(int *)(pcVar5 + 0x24);
              }
              if (iVar3 == *(int *)(*(int *)PTR__Game_001b60b8 + 0x440b0)) {
                iVar3 = iVar6 * 0x44 + local_28 * 0x220;
                cRBod::SetObject((cRBod *)(this + (int)(&PTR_caseD_6_00013458 +
                                                       local_28 * 0x88 + iVar6 * 0x11)),
                                 *(cRObject **)(*(int *)PTR__Game_001b60b8 + 0x43f50));
                this[iVar3 + 0x1348a] = (cRSubGame)((byte)this[iVar3 + 0x1348a] | 0x40);
                iVar3 = *(int *)(pcVar5 + 0x24);
              }
              if (iVar3 == *(int *)(*(int *)PTR__Game_001b60b8 + 0x440dc)) {
                iVar3 = iVar6 * 0x44 + local_28 * 0x220;
                cRBod::SetObject((cRBod *)(this + (int)(&PTR_caseD_6_00013458 +
                                                       local_28 * 0x88 + iVar6 * 0x11)),
                                 *(cRObject **)(*(int *)PTR__Game_001b60b8 + 0x43f7c));
                this[iVar3 + 0x1348a] = (cRSubGame)((byte)this[iVar3 + 0x1348a] | 0x40);
                iVar3 = *(int *)(pcVar5 + 0x24);
              }
              goto LAB_0001a614;
            }
          }
        }
        else {
          if ((((local_28 & 7) != 5) ||
              (((byte)this[iVar6 * 0x44 + local_28 * 0x220 + 0x1348a] & 0x20) != 0)) ||
             (((byte)this[iVar6 * 0x44 + (local_28 - 1) * 0x220 + 0x1348a] & 0x20) != 0))
          goto LAB_0001a484;
          cVar4 = pcVar5[0x30];
          if ((((cVar4 == (cRSubGame)0x14 || cVar4 == (cRSubGame)0x1) || (cVar4 == (cRSubGame)0x15))
              || ((cVar4 == (cRSubGame)0x21 ||
                  ((cVar4 == (cRSubGame)0x22 || (cVar4 == (cRSubGame)0x1b)))))) &&
             ((cVar1 = pcVar5[-0x1f0], cVar1 == (cRSubGame)0x17 || cVar1 == (cRSubGame)0xf ||
              ((((((cVar1 == (cRSubGame)0x18 || cVar1 == (cRSubGame)0x19) ||
                  cVar1 == (cRSubGame)0x1a) || cVar1 == (cRSubGame)0x10) || cVar1 == (cRSubGame)0x12
                ) || cVar1 == (cRSubGame)0x13 || (cVar1 == (cRSubGame)0x20)))))) {
            iVar3 = *(int *)(pcVar5 + 0x24);
            if (iVar3 == *(int *)(*(int *)PTR__Game_001b60b8 + 0x44370)) {
              iVar3 = iVar6 * 0x44 + local_28 * 0x220;
              cRBod::SetObject((cRBod *)(this + (int)(&PTR_caseD_6_00013458 +
                                                     local_28 * 0x88 + iVar6 * 0x11)),
                               *(cRObject **)(*(int *)PTR__Game_001b60b8 + 0x44630));
              this[iVar3 + 0x1348a] = (cRSubGame)((byte)this[iVar3 + 0x1348a] | 0x40);
              iVar3 = *(int *)(pcVar5 + 0x24);
              iVar7 = *(int *)PTR__Game_001b60b8;
              if (iVar3 == *(int *)(iVar7 + 0x43f24)) goto LAB_0001acc8;
LAB_0001a99c:
              iVar7 = *(int *)PTR__Game_001b60b8;
              if (iVar3 != *(int *)(iVar7 + 0x43f50)) goto LAB_0001a9b8;
LAB_0001ad2c:
              iVar3 = iVar6 * 0x44 + local_28 * 0x220;
              cRBod::SetObject((cRBod *)(this + (int)(&PTR_caseD_6_00013458 +
                                                     local_28 * 0x88 + iVar6 * 0x11)),
                               *(cRObject **)(iVar7 + 0x440b0));
              this[iVar3 + 0x1348a] = (cRSubGame)((byte)this[iVar3 + 0x1348a] | 0x40);
              iVar3 = *(int *)(pcVar5 + 0x24);
              iVar7 = *(int *)PTR__Game_001b60b8;
              if (iVar3 == *(int *)(iVar7 + 0x43f7c)) goto LAB_0001ad90;
LAB_0001a9d4:
              iVar7 = *(int *)PTR__Game_001b60b8;
              if (*(int *)(iVar7 + 0x43fa8) == iVar3) {
LAB_0001adf4:
                iVar3 = iVar6 * 0x44 + local_28 * 0x220;
                cRBod::SetObject((cRBod *)(this + (int)(&PTR_caseD_6_00013458 +
                                                       local_28 * 0x88 + iVar6 * 0x11)),
                                 *(cRObject **)(iVar7 + 0x44108));
                this[iVar3 + 0x1348a] = (cRSubGame)((byte)this[iVar3 + 0x1348a] | 0x40);
              }
            }
            else {
              iVar7 = *(int *)PTR__Game_001b60b8;
              if (iVar3 != *(int *)(iVar7 + 0x43f24)) goto LAB_0001a99c;
LAB_0001acc8:
              iVar3 = iVar6 * 0x44 + local_28 * 0x220;
              cRBod::SetObject((cRBod *)(this + (int)(&PTR_caseD_6_00013458 +
                                                     local_28 * 0x88 + iVar6 * 0x11)),
                               *(cRObject **)(iVar7 + 0x44084));
              this[iVar3 + 0x1348a] = (cRSubGame)((byte)this[iVar3 + 0x1348a] | 0x40);
              iVar3 = *(int *)(pcVar5 + 0x24);
              iVar7 = *(int *)PTR__Game_001b60b8;
              if (iVar3 == *(int *)(iVar7 + 0x43f50)) goto LAB_0001ad2c;
LAB_0001a9b8:
              iVar7 = *(int *)PTR__Game_001b60b8;
              if (iVar3 != *(int *)(iVar7 + 0x43f7c)) goto LAB_0001a9d4;
LAB_0001ad90:
              iVar3 = iVar6 * 0x44 + local_28 * 0x220;
              cRBod::SetObject((cRBod *)(this + (int)(&PTR_caseD_6_00013458 +
                                                     local_28 * 0x88 + iVar6 * 0x11)),
                               *(cRObject **)(iVar7 + 0x440dc));
              this[iVar3 + 0x1348a] = (cRSubGame)((byte)this[iVar3 + 0x1348a] | 0x40);
              iVar7 = *(int *)PTR__Game_001b60b8;
              if (*(int *)(iVar7 + 0x43fa8) == *(int *)(pcVar5 + 0x24)) goto LAB_0001adf4;
            }
            if ((((byte)this[iVar6 * 0x44 + local_28 * 0x220 + 0x1348a] & 0x20) != 0) ||
               (((byte)this[iVar6 * 0x44 + (local_28 - 1) * 0x220 + 0x1348a] & 0x20) != 0))
            goto LAB_0001a484;
            cVar4 = pcVar5[0x30];
          }
          if ((((((cVar4 == (cRSubGame)0x17 || cVar4 == (cRSubGame)0xf) ||
                 (cVar4 == (cRSubGame)0x18)) || (cVar4 == (cRSubGame)0x19)) ||
               ((cVar4 == (cRSubGame)0x1a || (cVar4 == (cRSubGame)0x10)))) ||
              ((cVar4 == (cRSubGame)0x12 || (cVar4 == (cRSubGame)0x13)))) &&
             ((((cVar4 = pcVar5[-0x1f0], cVar4 == (cRSubGame)0x14 || cVar4 == (cRSubGame)0x1 ||
                (cVar4 == (cRSubGame)0x15)) || (cVar4 == (cRSubGame)0x21)) ||
              ((cVar4 == (cRSubGame)0x22 || (cVar4 == (cRSubGame)0x1b)))))) {
            iVar3 = *(int *)(pcVar5 + 0x24);
            if (iVar3 == *(int *)(*(int *)PTR__Game_001b60b8 + 0x44630)) {
              iVar3 = iVar6 * 0x44 + local_28 * 0x220;
              cRBod::SetObject((cRBod *)(this + (int)(&PTR_caseD_6_00013458 +
                                                     local_28 * 0x88 + iVar6 * 0x11)),
                               *(cRObject **)(*(int *)PTR__Game_001b60b8 + 0x44370));
              this[iVar3 + 0x1348a] = (cRSubGame)((byte)this[iVar3 + 0x1348a] | 0x40);
              iVar3 = *(int *)(pcVar5 + 0x24);
            }
            if (iVar3 == *(int *)(*(int *)PTR__Game_001b60b8 + 0x44084)) {
              iVar3 = iVar6 * 0x44 + local_28 * 0x220;
              cRBod::SetObject((cRBod *)(this + (int)(&PTR_caseD_6_00013458 +
                                                     local_28 * 0x88 + iVar6 * 0x11)),
                               *(cRObject **)(*(int *)PTR__Game_001b60b8 + 0x43f24));
              this[iVar3 + 0x1348a] = (cRSubGame)((byte)this[iVar3 + 0x1348a] | 0x40);
              iVar3 = *(int *)(pcVar5 + 0x24);
            }
            if (iVar3 == *(int *)(*(int *)PTR__Game_001b60b8 + 0x440b0)) {
              iVar3 = iVar6 * 0x44 + local_28 * 0x220;
              cRBod::SetObject((cRBod *)(this + (int)(&PTR_caseD_6_00013458 +
                                                     local_28 * 0x88 + iVar6 * 0x11)),
                               *(cRObject **)(*(int *)PTR__Game_001b60b8 + 0x43f50));
              this[iVar3 + 0x1348a] = (cRSubGame)((byte)this[iVar3 + 0x1348a] | 0x40);
              iVar3 = *(int *)(pcVar5 + 0x24);
            }
            if (iVar3 == *(int *)(*(int *)PTR__Game_001b60b8 + 0x440dc)) {
              iVar3 = iVar6 * 0x44 + local_28 * 0x220;
              cRBod::SetObject((cRBod *)(this + (int)(&PTR_caseD_6_00013458 +
                                                     local_28 * 0x88 + iVar6 * 0x11)),
                               *(cRObject **)(*(int *)PTR__Game_001b60b8 + 0x43f7c));
              this[iVar3 + 0x1348a] = (cRSubGame)((byte)this[iVar3 + 0x1348a] | 0x40);
              iVar3 = *(int *)(pcVar5 + 0x24);
            }
LAB_0001a614:
            if (*(int *)(*(int *)PTR__Game_001b60b8 + 0x44108) == iVar3) {
              iVar3 = iVar6 + 1;
              iVar7 = iVar6 * 0x44 + local_28 * 0x220;
              cRBod::SetObject((cRBod *)(this + (int)(&PTR_caseD_6_00013458 +
                                                     local_28 * 0x88 + iVar6 * 0x11)),
                               *(cRObject **)(*(int *)PTR__Game_001b60b8 + 0x43fa8));
              pcVar5 = pcVar5 + 0x44;
              this[iVar7 + 0x1348a] = (cRSubGame)((byte)this[iVar7 + 0x1348a] | 0x40);
              iVar6 = iVar3;
              if (iVar3 == 8) break;
              goto LAB_0001a494;
            }
          }
        }
LAB_0001a484:
        iVar6 = iVar6 + 1;
        pcVar5 = pcVar5 + 0x44;
      } while (iVar6 != 8);
      local_28 = uVar2;
    } while ((int)uVar2 < *(int *)(this + 0x6c) + -1);
  }
  return;
}
