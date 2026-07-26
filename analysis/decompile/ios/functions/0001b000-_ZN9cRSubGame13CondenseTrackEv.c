/*
 * mangled: _ZN9cRSubGame13CondenseTrackEv
 * demangled: cRSubGame::CondenseTrack()
 * address: 0001b000
 * size: 1916
 */

/* cRSubGame::CondenseTrack() */

void __thiscall cRSubGame::CondenseTrack(cRSubGame *this)

{
  cRSubGame *pcVar1;
  int iVar2;
  cRSubGame cVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint local_30;
  cRSubGame *local_2c;
  cRSubGame *local_28;
  int local_24;

  if (0 < *(int *)(this + 0x6c)) {
    iVar4 = 0;
    do {
      iVar2 = iVar4 + 1;
      this[iVar4 * 0x220 + 0x1348b] = (cRSubGame)((byte)this[iVar4 * 0x220 + 0x1348b] | 0x60);
      this[iVar4 * 0x220 + 0x134cf] = (cRSubGame)((byte)this[iVar4 * 0x220 + 0x134cf] | 0x60);
      this[iVar4 * 0x220 + 0x13513] = (cRSubGame)((byte)this[iVar4 * 0x220 + 0x13513] | 0x60);
      this[iVar4 * 0x220 + 0x13557] = (cRSubGame)((byte)this[iVar4 * 0x220 + 0x13557] | 0x60);
      this[iVar4 * 0x220 + 0x1359b] = (cRSubGame)((byte)this[iVar4 * 0x220 + 0x1359b] | 0x60);
      this[iVar4 * 0x220 + 0x135df] = (cRSubGame)((byte)this[iVar4 * 0x220 + 0x135df] | 0x60);
      this[iVar4 * 0x220 + 0x13623] = (cRSubGame)((byte)this[iVar4 * 0x220 + 0x13623] | 0x60);
      this[iVar4 * 0x220 + 0x13667] = (cRSubGame)((byte)this[iVar4 * 0x220 + 0x13667] | 0x60);
      iVar4 = iVar2;
    } while (iVar2 < *(int *)(this + 0x6c));
    if (0 < *(int *)(this + 0x6c)) {
      local_28 = this + 0x1e41d8;
      local_24 = 0;
      do {
        local_2c = this + (int)(&PTR_caseD_6_00013458 + local_24 * 0x88);
        local_30 = 8;
        iVar4 = 0;
        do {
          cVar3 = local_2c[0x30];
          if ((((cVar3 == (cRSubGame)0x14 || cVar3 == (cRSubGame)0x1) || (cVar3 == (cRSubGame)0x15))
              || (cVar3 == (cRSubGame)0x21)) ||
             ((cVar3 == (cRSubGame)0x22 || (cVar3 == (cRSubGame)0x1b)))) {
            iVar2 = iVar4 * 0x44 + local_24 * 0x220;
            if (((char)this[iVar2 + 0x1348b] < '\0') ||
               (uVar6 = (byte)this[iVar2 + 0x1348a] >> 6 & 1,
               ((byte)this[iVar2 + 0x1348a] >> 6 & 1) != 0)) goto LAB_0001b114;
            if (iVar4 < 8) {
              iVar2 = iVar4;
              pcVar1 = this + (iVar4 + 1) * 0x44 + local_24 * 0x220 + 0x13488;
              while (((cVar3 == (cRSubGame)0x15 || cVar3 == (cRSubGame)0x1 ||
                      (cVar3 == (cRSubGame)0x1b)) ||
                     ((cVar3 == (cRSubGame)0x21 || (cVar3 == (cRSubGame)0x22))))) {
                iVar2 = iVar2 * 0x44 + local_24 * 0x220;
                if (((((char)this[iVar2 + 0x1348b] < '\0') ||
                     (((byte)this[iVar2 + 0x1348b] & 0x40) == 0)) ||
                    (((byte)this[iVar2 + 0x1348a] & 0x20) != 0)) ||
                   (((byte)this[iVar2 + 0x1348a] & 0x40) != 0)) break;
                uVar6 = uVar6 + 1;
                iVar2 = uVar6 + iVar4;
                if (uVar6 == local_30) break;
                cVar3 = *pcVar1;
                pcVar1 = pcVar1 + 0x44;
              }
              if (1 < (int)uVar6) {
                cRBod::SetObject((cRBod *)(this + (int)(&PTR_caseD_6_00013458 +
                                                       local_24 * 0x88 + iVar4 * 0x11)),
                                 *(cRObject **)(uVar6 * 0x2c + *(int *)PTR__Game_001b60b8 + 0x44344)
                                );
                pcVar1 = this + (int)(&PTR_caseD_6_00013458 +
                                     local_24 * 0x88 + (uVar6 + iVar4) * 0x11);
                iVar2 = iVar4 + -1 + uVar6;
                do {
                  *(uint *)(pcVar1 + -0x40) = *(uint *)(pcVar1 + -0x40) & 0xffffffdf;
                  iVar5 = iVar2 * 0x44 + local_24 * 0x220;
                  iVar2 = iVar2 + -1;
                  pcVar1 = pcVar1 + -0x44;
                  this[iVar5 + 0x1348b] = (cRSubGame)((byte)this[iVar5 + 0x1348b] & 0x9f);
                } while (iVar2 != iVar4);
              }
            }
          }
          else {
LAB_0001b114:
            if (((cVar3 == (cRSubGame)0x17 || cVar3 == (cRSubGame)0xf) ||
                ((((cVar3 == (cRSubGame)0x18 || cVar3 == (cRSubGame)0x19) ||
                  cVar3 == (cRSubGame)0x1a) || cVar3 == (cRSubGame)0x10) || cVar3 == (cRSubGame)0x12
                )) || (cVar3 == (cRSubGame)0x13)) {
              iVar2 = iVar4 * 0x44 + local_24 * 0x220;
              if ((-1 < (char)this[iVar2 + 0x1348b]) &&
                 (uVar6 = (byte)this[iVar2 + 0x1348a] >> 6 & 1,
                 ((byte)this[iVar2 + 0x1348a] >> 6 & 1) == 0)) {
                if (iVar4 < 8) {
                  iVar2 = iVar4;
                  pcVar1 = this + (iVar4 + 1) * 0x44 + local_24 * 0x220 + 0x13488;
                  while ((((cVar3 == (cRSubGame)0x17 || cVar3 == (cRSubGame)0xf ||
                           (cVar3 == (cRSubGame)0x18)) || (cVar3 == (cRSubGame)0x19)) ||
                         (((cVar3 == (cRSubGame)0x1a || (cVar3 == (cRSubGame)0x10)) ||
                          ((cVar3 == (cRSubGame)0x12 || (cVar3 == (cRSubGame)0x13))))))) {
                    iVar2 = iVar2 * 0x44 + local_24 * 0x220;
                    if ((((char)this[iVar2 + 0x1348b] < '\0') ||
                        (((byte)this[iVar2 + 0x1348b] & 0x40) == 0)) ||
                       ((((byte)this[iVar2 + 0x1348a] & 0x20) != 0 ||
                        (((byte)this[iVar2 + 0x1348a] & 0x40) != 0)))) break;
                    uVar6 = uVar6 + 1;
                    iVar2 = uVar6 + iVar4;
                    if (uVar6 == local_30) break;
                    cVar3 = *pcVar1;
                    pcVar1 = pcVar1 + 0x44;
                  }
                  if (1 < (int)uVar6) {
                    cRBod::SetObject((cRBod *)(this + (int)(&PTR_caseD_6_00013458 +
                                                           local_24 * 0x88 + iVar4 * 0x11)),
                                     *(cRObject **)
                                      (uVar6 * 0x2c + *(int *)PTR__Game_001b60b8 + 0x44604));
                    pcVar1 = this + (int)(&PTR_caseD_6_00013458 +
                                         local_24 * 0x88 + (uVar6 + iVar4) * 0x11);
                    iVar2 = iVar4 + -1 + uVar6;
                    do {
                      *(uint *)(pcVar1 + -0x40) = *(uint *)(pcVar1 + -0x40) & 0xffffffdf;
                      iVar5 = iVar2 * 0x44 + local_24 * 0x220;
                      iVar2 = iVar2 + -1;
                      pcVar1 = pcVar1 + -0x44;
                      this[iVar5 + 0x1348b] = (cRSubGame)((byte)this[iVar5 + 0x1348b] & 0x9f);
                    } while (iVar2 != iVar4);
                  }
                }
                goto LAB_0001b194;
              }
            }
            if (cVar3 == (cRSubGame)0xe) {
              iVar2 = iVar4 * 0x44 + local_24 * 0x220;
              cVar3 = this[iVar2 + 0x1348b];
              this[iVar2 + 0x1348b] = (cRSubGame)((byte)cVar3 & 0xf1 | 1);
              if (((iVar4 < 8) && (local_2c[0x30] == (cRSubGame)0xe)) && (((byte)cVar3 & 0x40) != 0)
                 ) {
                pcVar1 = this + (int)(&PTR_caseD_6_00013458 + local_24 * 0x88 + iVar4 * 0x11);
                uVar6 = 0;
                do {
                  cVar3 = this[iVar2 + 0x1348b];
                  uVar6 = uVar6 + 1;
                  this[iVar2 + 0x1348b] = (cRSubGame)((byte)cVar3 & 0xf1 | 1);
                  if ((uVar6 == local_30) || (pcVar1[0x74] != (cRSubGame)0xe)) break;
                  pcVar1 = pcVar1 + 0x44;
                } while (((byte)cVar3 & 0x40) != 0);
                if (1 < (int)uVar6) {
                  iVar2 = iVar4 * 0x44 + local_24 * 0x220;
                  cRBod::SetObject((cRBod *)(this + (int)(&PTR_caseD_6_00013458 +
                                                         local_24 * 0x88 + iVar4 * 0x11)),
                                   *(cRObject **)
                                    (uVar6 * 0x2c + *(int *)PTR__Game_001b60b8 + 0x441e4));
                  this[iVar2 + 0x1348b] =
                       (cRSubGame)((byte)uVar6 & 0xf | (byte)this[iVar2 + 0x1348b] & 0xf0);
                  pcVar1 = this + (int)(&PTR_caseD_6_00013458 +
                                       local_24 * 0x88 + (uVar6 + iVar4) * 0x11);
                  iVar2 = iVar4 + -1 + uVar6;
                  do {
                    *(uint *)(pcVar1 + -0x40) = *(uint *)(pcVar1 + -0x40) & 0xffffffdf;
                    iVar5 = iVar2 * 0x44 + local_24 * 0x220;
                    iVar2 = iVar2 + -1;
                    pcVar1 = pcVar1 + -0x44;
                    this[iVar5 + 0x1348b] = (cRSubGame)((byte)this[iVar5 + 0x1348b] & 0x9f);
                  } while (iVar2 != iVar4);
                }
              }
            }
            else if (cVar3 == (cRSubGame)0x23 || cVar3 == (cRSubGame)0x0) {
              iVar2 = iVar4 * 0x44 + local_24 * 0x220;
              cVar3 = this[iVar2 + 0x1348b];
              this[iVar2 + 0x1348b] = (cRSubGame)((byte)cVar3 & 0xdf);
              if (*(int *)(this + 0x58) == 2) {
                cRBod::SetObject((cRBod *)(this + (int)(&PTR_caseD_6_00013458 +
                                                       local_24 * 0x88 + iVar4 * 0x11)),
                                 *(cRObject **)(*(int *)PTR__Game_001b60b8 + 0x43e48));
              }
              else {
                this[iVar2 + 0x1348b] = (cRSubGame)((byte)cVar3 & 0x9f);
              }
            }
          }
LAB_0001b194:
          iVar2 = iVar4 + 1;
          if ((*(uint *)local_28 & 4) != 0) {
            *(uint *)(local_2c + 4) = *(uint *)(local_2c + 4) & 0xfffffddd;
            iVar4 = iVar4 * 0x44 + local_24 * 0x220;
            this[iVar4 + 0x1348b] = (cRSubGame)((byte)this[iVar4 + 0x1348b] & 0xbf);
            *(uint *)(local_28 + 0xa8) = *(uint *)(local_28 + 0xa8) & 0xffffffdf;
          }
          local_30 = local_30 - 1;
          local_2c = local_2c + 0x44;
          iVar4 = iVar2;
        } while (iVar2 != 8);
        local_24 = local_24 + 1;
        local_28 = local_28 + 0xdc;
      } while (local_24 < *(int *)(this + 0x6c));
    }
  }
  return;
}
