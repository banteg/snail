/*
 * mangled: _ZN9cRSubGame13GenerateLevelEi
 * demangled: cRSubGame::GenerateLevel(int)
 * address: 0002e9c4
 * size: 1972
 */

/* cRSubGame::GenerateLevel(int) */

void __thiscall cRSubGame::GenerateLevel(cRSubGame *this,int param_1)

{
  cRSubGame cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  cRSubGame *pcVar7;
  bool bVar8;
  int local_2c;
  cRSubGame *local_28;

  *(int *)(this + 0x5c) = param_1;
  SetFeatures(this);
  BuildColours();
  BuildLevel(this);
  PlaceParcels(this);
  SmoothTrack(this);
  if (0 < *(int *)(this + 0x6c) + -1) {
    iVar6 = 0;
    do {
      iVar2 = iVar6 + 1;
      local_28 = this + (int)(&PTR_caseD_6_00013458 + iVar2 * 0x88);
      pcVar7 = this + (int)(&PTR_caseD_6_00013458 + iVar6 * 0x88);
      local_2c = 0;
      do {
        iVar4 = local_2c * 0x44 + iVar6 * 0x220;
        this[iVar4 + 0x1348a] = (cRSubGame)((byte)this[iVar4 + 0x1348a] & 0xdf);
        cVar1 = local_28[0x30];
        if ((((cVar1 == (cRSubGame)0x1c || cVar1 == (cRSubGame)0x0) || (cVar1 == (cRSubGame)0x23))
            || (cVar1 == (cRSubGame)0xe)) || (cVar1 == (cRSubGame)0x1d)) {
          iVar4 = *(int *)(pcVar7 + 0x24);
          iVar5 = *(int *)PTR__Game_001b60b8;
          if ((iVar4 == *(int *)(iVar5 + 0x44370)) || (iVar4 == *(int *)(iVar5 + 0x44630))) {
            iVar4 = local_2c * 0x44 + iVar6 * 0x220;
            cRBod::SetObject((cRBod *)(this + (int)(&PTR_caseD_6_00013458 +
                                                   iVar6 * 0x88 + local_2c * 0x11)),
                             *(cRObject **)(iVar5 + 0x444d0));
            this[iVar4 + 0x1348a] = (cRSubGame)((byte)this[iVar4 + 0x1348a] | 0x20);
            iVar4 = *(int *)(pcVar7 + 0x24);
          }
          iVar5 = *(int *)PTR__Game_001b60b8;
          if ((iVar4 == *(int *)(iVar5 + 0x4439c)) || (iVar4 == *(int *)(iVar5 + 0x4465c))) {
            iVar4 = local_2c * 0x44 + iVar6 * 0x220;
            cRBod::SetObject((cRBod *)(this + (int)(&PTR_caseD_6_00013458 +
                                                   iVar6 * 0x88 + local_2c * 0x11)),
                             *(cRObject **)(iVar5 + 0x444fc));
            this[iVar4 + 0x1348a] = (cRSubGame)((byte)this[iVar4 + 0x1348a] | 0x20);
            iVar4 = *(int *)(pcVar7 + 0x24);
          }
          iVar5 = *(int *)PTR__Game_001b60b8;
          if ((iVar4 == *(int *)(iVar5 + 0x443c8)) || (iVar4 == *(int *)(iVar5 + 0x44688))) {
            iVar4 = local_2c * 0x44 + iVar6 * 0x220;
            cRBod::SetObject((cRBod *)(this + (int)(&PTR_caseD_6_00013458 +
                                                   iVar6 * 0x88 + local_2c * 0x11)),
                             *(cRObject **)(iVar5 + 0x44528));
            this[iVar4 + 0x1348a] = (cRSubGame)((byte)this[iVar4 + 0x1348a] | 0x20);
            iVar4 = *(int *)(pcVar7 + 0x24);
          }
          iVar5 = *(int *)PTR__Game_001b60b8;
          if ((iVar4 == *(int *)(iVar5 + 0x443f4)) || (iVar4 == *(int *)(iVar5 + 0x446b4))) {
            iVar4 = local_2c * 0x44 + iVar6 * 0x220;
            cRBod::SetObject((cRBod *)(this + (int)(&PTR_caseD_6_00013458 +
                                                   iVar6 * 0x88 + local_2c * 0x11)),
                             *(cRObject **)(iVar5 + 0x44554));
            this[iVar4 + 0x1348a] = (cRSubGame)((byte)this[iVar4 + 0x1348a] | 0x20);
            iVar4 = *(int *)(pcVar7 + 0x24);
          }
          iVar5 = *(int *)PTR__Game_001b60b8;
          if ((iVar4 == *(int *)(iVar5 + 0x44420)) || (iVar4 == *(int *)(iVar5 + 0x446e0))) {
            iVar4 = local_2c * 0x44 + iVar6 * 0x220;
            cRBod::SetObject((cRBod *)(this + (int)(&PTR_caseD_6_00013458 +
                                                   iVar6 * 0x88 + local_2c * 0x11)),
                             *(cRObject **)(iVar5 + 0x44580));
            this[iVar4 + 0x1348a] = (cRSubGame)((byte)this[iVar4 + 0x1348a] | 0x20);
            iVar4 = *(int *)(pcVar7 + 0x24);
          }
          iVar5 = *(int *)PTR__Game_001b60b8;
          if ((iVar4 == *(int *)(iVar5 + 0x4444c)) || (iVar4 == *(int *)(iVar5 + 0x4470c))) {
            iVar4 = local_2c * 0x44 + iVar6 * 0x220;
            cRBod::SetObject((cRBod *)(this + (int)(&PTR_caseD_6_00013458 +
                                                   iVar6 * 0x88 + local_2c * 0x11)),
                             *(cRObject **)(iVar5 + 0x445ac));
            this[iVar4 + 0x1348a] = (cRSubGame)((byte)this[iVar4 + 0x1348a] | 0x20);
            iVar4 = *(int *)(pcVar7 + 0x24);
          }
          iVar5 = *(int *)PTR__Game_001b60b8;
          if ((iVar4 == *(int *)(iVar5 + 0x44478)) || (iVar4 == *(int *)(iVar5 + 0x44738))) {
            iVar4 = local_2c * 0x44 + iVar6 * 0x220;
            cRBod::SetObject((cRBod *)(this + (int)(&PTR_caseD_6_00013458 +
                                                   iVar6 * 0x88 + local_2c * 0x11)),
                             *(cRObject **)(iVar5 + 0x445d8));
            this[iVar4 + 0x1348a] = (cRSubGame)((byte)this[iVar4 + 0x1348a] | 0x20);
            iVar4 = *(int *)(pcVar7 + 0x24);
          }
          iVar5 = *(int *)PTR__Game_001b60b8;
          if ((*(int *)(iVar5 + 0x444a4) == iVar4) || (*(int *)(iVar5 + 0x44764) == iVar4)) {
            iVar4 = local_2c * 0x44 + iVar6 * 0x220;
            cRBod::SetObject((cRBod *)(this + (int)(&PTR_caseD_6_00013458 +
                                                   iVar6 * 0x88 + local_2c * 0x11)),
                             *(cRObject **)(iVar5 + 0x44604));
            this[iVar4 + 0x1348a] = (cRSubGame)((byte)this[iVar4 + 0x1348a] | 0x20);
            iVar4 = *(int *)(pcVar7 + 0x24);
          }
          iVar5 = *(int *)PTR__Game_001b60b8;
          if ((iVar4 == *(int *)(iVar5 + 0x43f24)) || (iVar4 == *(int *)(iVar5 + 0x44084))) {
            iVar4 = local_2c * 0x44 + iVar6 * 0x220;
            cRBod::SetObject((cRBod *)(this + (int)(&PTR_caseD_6_00013458 +
                                                   iVar6 * 0x88 + local_2c * 0x11)),
                             *(cRObject **)(iVar5 + 0x43fd4));
            this[iVar4 + 0x1348a] = (cRSubGame)((byte)this[iVar4 + 0x1348a] | 0x20);
            iVar4 = *(int *)(pcVar7 + 0x24);
          }
          iVar5 = *(int *)PTR__Game_001b60b8;
          if ((iVar4 == *(int *)(iVar5 + 0x43f50)) || (iVar4 == *(int *)(iVar5 + 0x440b0))) {
            iVar4 = local_2c * 0x44 + iVar6 * 0x220;
            cRBod::SetObject((cRBod *)(this + (int)(&PTR_caseD_6_00013458 +
                                                   iVar6 * 0x88 + local_2c * 0x11)),
                             *(cRObject **)(iVar5 + 0x44000));
            this[iVar4 + 0x1348a] = (cRSubGame)((byte)this[iVar4 + 0x1348a] | 0x20);
            iVar4 = *(int *)(pcVar7 + 0x24);
          }
          iVar5 = *(int *)PTR__Game_001b60b8;
          if ((iVar4 == *(int *)(iVar5 + 0x43f7c)) || (iVar4 == *(int *)(iVar5 + 0x440dc))) {
            iVar4 = local_2c * 0x44 + iVar6 * 0x220;
            cRBod::SetObject((cRBod *)(this + (int)(&PTR_caseD_6_00013458 +
                                                   iVar6 * 0x88 + local_2c * 0x11)),
                             *(cRObject **)(iVar5 + 0x4402c));
            this[iVar4 + 0x1348a] = (cRSubGame)((byte)this[iVar4 + 0x1348a] | 0x20);
            iVar4 = *(int *)(pcVar7 + 0x24);
            iVar5 = *(int *)PTR__Game_001b60b8;
            if (*(int *)(iVar5 + 0x43fa8) != iVar4) goto LAB_0002ecc0;
          }
          else {
            iVar5 = *(int *)PTR__Game_001b60b8;
            if (*(int *)(iVar5 + 0x43fa8) != iVar4) {
LAB_0002ecc0:
              if (*(int *)(iVar5 + 0x44108) != iVar4) goto LAB_0002ea78;
            }
          }
          iVar4 = local_2c * 0x44 + iVar6 * 0x220;
          cRBod::SetObject((cRBod *)(this + (int)(&PTR_caseD_6_00013458 +
                                                 iVar6 * 0x88 + local_2c * 0x11)),
                           *(cRObject **)(iVar5 + 0x44058));
          this[iVar4 + 0x1348a] = (cRSubGame)((byte)this[iVar4 + 0x1348a] | 0x20);
        }
LAB_0002ea78:
        pcVar7 = pcVar7 + 0x44;
        local_2c = local_2c + 1;
        local_28 = local_28 + 0x44;
      } while (local_2c != 8);
      iVar6 = iVar2;
    } while (iVar2 < *(int *)(this + 0x6c) + -1);
  }
  SlideSmoothTrack(this);
  CondenseTrack(this);
  iVar6 = *(int *)(this + 0x6c);
  if (0 < iVar6 + -1) {
    iVar2 = 0;
    do {
      pcVar7 = this + (int)(&PTR_caseD_6_00013458 + iVar2 * 0x88);
      iVar4 = 0;
      do {
        cVar1 = pcVar7[0x30];
        bVar8 = 0x16 < (byte)cVar1;
        if (cVar1 != (cRSubGame)0x17) {
          bVar8 = 0xb < (byte)((char)cVar1 - 2U);
        }
        if (((!bVar8 || (cVar1 == (cRSubGame)0x17 || (byte)((char)cVar1 - 2U) == 0xc)) ||
            (cVar1 == (cRSubGame)0x19)) || (cVar1 == (cRSubGame)0x21)) {
          iVar3 = 0;
          iVar5 = iVar2;
          do {
            if ((-1 < iVar5) && (iVar5 < iVar6 + -1)) {
              if (iVar4 != 0) {
                iVar6 = (iVar4 + -1) * 0x44 + iVar5 * 0x220;
                this[iVar6 + 0x1348a] = (cRSubGame)((byte)this[iVar6 + 0x1348a] & 0xe7 | 0x18);
                iVar6 = *(int *)(this + 0x6c);
                if (iVar6 + -1 <= iVar5) goto LAB_0002f090;
              }
              if (iVar4 != -1) {
                iVar6 = iVar4 * 0x44 + iVar5 * 0x220;
                this[iVar6 + 0x1348a] = (cRSubGame)((byte)this[iVar6 + 0x1348a] & 0xe7 | 0x18);
                iVar6 = *(int *)(this + 0x6c);
              }
            }
LAB_0002f090:
            iVar3 = iVar3 + -1;
            iVar5 = iVar5 + -1;
          } while (iVar3 != -6);
        }
        iVar4 = iVar4 + 1;
        pcVar7 = pcVar7 + 0x44;
      } while (iVar4 != 8);
      iVar2 = iVar2 + 1;
    } while (iVar2 < iVar6 + -1);
  }
  FringeEdgeTrack(this);
  cRWorld::ReSet((cRWorld *)(this + 0xf378));
  return;
}
