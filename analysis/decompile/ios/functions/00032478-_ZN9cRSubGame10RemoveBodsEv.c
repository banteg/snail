/*
 * mangled: _ZN9cRSubGame10RemoveBodsEv
 * demangled: cRSubGame::RemoveBods()
 * address: 00032478
 * size: 3656
 */

/* cRSubGame::RemoveBods() */

void __thiscall cRSubGame::RemoveBods(cRSubGame *this)

{
  cRSubGame *pcVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  cRSubGame *pcVar7;
  int local_28;

  pcVar1 = this + 0x1e41e4;
  local_28 = 0;
  do {
    if ((*(uint *)(pcVar1 + -4) & 0x200) != 0) {
      iVar2 = *(int *)PTR__Game_001b60b8;
      if ((*(uint *)(pcVar1 + -4) & 0x40) == 0) {
        iVar4 = *(int *)(pcVar1 + 4);
        if (iVar4 != 0) {
          *(undefined4 *)(iVar4 + 8) = *(undefined4 *)pcVar1;
        }
        if (*(int *)pcVar1 == 0) {
          *(int *)(iVar2 + 0x35c) = iVar4;
        }
        else {
          *(int *)(*(int *)pcVar1 + 0xc) = iVar4;
        }
        *(undefined4 *)(pcVar1 + 4) = *(undefined4 *)(iVar2 + 0x360);
        *(cRSubGame **)(iVar2 + 0x360) = this + local_28 * 0xdc + 0x1e41dc;
        *(uint *)(pcVar1 + -4) = *(uint *)(pcVar1 + -4) & 0xfffffdff;
      }
      else {
        RShellError("List remove NEXTBOD");
      }
    }
    pcVar7 = this + (int)(&PTR_caseD_6_00013458 + local_28 * 0x88);
    iVar2 = 0;
    do {
      while( true ) {
        iVar4 = iVar2;
        iVar2 = *(int *)PTR__Game_001b60b8;
        if ((byte)((char)pcVar7[0x30] - 0x1dU) < 2) {
          uVar5 = ((int)(this + ((int)(&PTR_caseD_6_00013458 + local_28 * 0x88 + iVar4 * 0x11) -
                                (iVar2 + ((byte)this[iVar4 * 0x44 + local_28 * 0x220 + 0x1348a] & 7)
                                         * 0x44 + 0x85fd0))) >> 2) * -0xf0f0f0f;
          if ((int)uVar5 < 0) {
            uVar5 = uVar5 + 7;
          }
          iVar6 = (((int)uVar5 >> 3) * 0x3f - (uVar5 & 0xfffffff8)) * 4 + iVar2;
          if (((*(uint *)(&DAT_00256d50 + iVar6) & 8) != 0) &&
             ((*(uint *)(&DAT_00256df8 + iVar6) & 0x200) != 0)) {
            if ((*(uint *)(&DAT_00256df8 + iVar6) & 0x40) == 0) {
              iVar3 = *(int *)(&DAT_00256e00 + iVar6);
              if (iVar3 != 0) {
                *(undefined4 *)(iVar3 + 8) = *(undefined4 *)(&DAT_00256dfc + iVar6);
              }
              iVar6 = *(int *)(&DAT_00256dfc + iVar6);
              if (iVar6 != 0) {
                *(int *)(iVar6 + 0xc) = iVar3;
              }
              if (iVar6 == 0) {
                *(int *)(iVar2 + 0x35c) = iVar3;
              }
              iVar6 = (((int)uVar5 >> 3) * 0x3f - (uVar5 & 0xfffffff8)) * 4;
              iVar3 = iVar6 + iVar2;
              *(undefined4 *)(&DAT_00256e00 + iVar3) = *(undefined4 *)(iVar2 + 0x360);
              *(int *)(iVar2 + 0x360) = iVar2 + iVar6 + 0x256df4;
              *(uint *)(&DAT_00256df8 + iVar3) = *(uint *)(&DAT_00256df8 + iVar3) & 0xfffffdff;
            }
            else {
              RShellError("List remove NEXTBOD");
            }
          }
        }
        if ((*(uint *)(pcVar7 + 4) & 0x200) != 0) break;
LAB_000325c8:
        pcVar7 = pcVar7 + 0x44;
        iVar2 = iVar4 + 1;
        if (iVar4 + 1 == 8) goto LAB_00032720;
      }
      iVar2 = *(int *)PTR__Game_001b60b8;
      if ((*(uint *)(pcVar7 + 4) & 0x40) == 0) {
        iVar6 = *(int *)(pcVar7 + 0xc);
        if (iVar6 != 0) {
          *(undefined4 *)(iVar6 + 8) = *(undefined4 *)(pcVar7 + 8);
        }
        if (*(int *)(pcVar7 + 8) == 0) {
          *(int *)(iVar2 + 0x35c) = iVar6;
        }
        else {
          *(int *)(*(int *)(pcVar7 + 8) + 0xc) = iVar6;
        }
        *(undefined4 *)(pcVar7 + 0xc) = *(undefined4 *)(iVar2 + 0x360);
        *(cRSubGame **)(iVar2 + 0x360) =
             this + (int)(&PTR_caseD_6_00013458 + local_28 * 0x88 + iVar4 * 0x11);
        *(uint *)(pcVar7 + 4) = *(uint *)(pcVar7 + 4) & 0xfffffdff;
        goto LAB_000325c8;
      }
      RShellError("List remove NEXTBOD");
      pcVar7 = pcVar7 + 0x44;
      iVar2 = iVar4 + 1;
    } while (iVar4 + 1 != 8);
LAB_00032720:
    local_28 = local_28 + 1;
    pcVar1 = pcVar1 + 0xdc;
    if (local_28 == 0xdac) {
      iVar4 = iVar4 + -7;
      pcVar1 = this + 0x29f4;
      do {
        if ((*(uint *)pcVar1 & 0x200) != 0) {
          iVar2 = *(int *)PTR__Game_001b60b8;
          pcVar7 = this + (int)(&DAT_000029f0 + iVar4 * 0x68);
          if ((*(uint *)(pcVar7 + 4) & 0x200) == 0) {
            RShellError("List remove");
          }
          else if ((*(uint *)(pcVar7 + 4) & 0x40) == 0) {
            iVar6 = *(int *)(pcVar7 + 0xc);
            if (iVar6 != 0) {
              *(undefined4 *)(iVar6 + 8) = *(undefined4 *)(pcVar7 + 8);
            }
            if (*(int *)(pcVar7 + 8) == 0) {
              *(int *)(iVar2 + 0x35c) = iVar6;
            }
            else {
              *(int *)(*(int *)(pcVar7 + 8) + 0xc) = iVar6;
            }
            *(undefined4 *)(pcVar7 + 0xc) = *(undefined4 *)(iVar2 + 0x360);
            *(cRSubGame **)(iVar2 + 0x360) = pcVar7;
            *(uint *)(pcVar7 + 4) = *(uint *)(pcVar7 + 4) & 0xfffffdff;
          }
          else {
            RShellError("List remove NEXTBOD");
          }
          *(undefined4 *)(pcVar1 + 0x28) = 0;
        }
        iVar4 = iVar4 + 1;
        pcVar1 = pcVar1 + 0x68;
      } while (iVar4 != 8);
      if ((*(uint *)(this + 0x27d4) & 0x200) != 0) {
        iVar2 = *(int *)PTR__Game_001b60b8;
        if ((*(uint *)(this + 0x27d4) & 0x200) == 0) {
          RShellError("List remove");
        }
        else if ((*(uint *)(this + 0x27d4) & 0x40) == 0) {
          iVar4 = *(int *)(this + 0x27dc);
          if (iVar4 != 0) {
            *(undefined4 *)(iVar4 + 8) = *(undefined4 *)(this + 0x27d8);
          }
          if (*(int *)(this + 0x27d8) == 0) {
            *(int *)(iVar2 + 0x35c) = iVar4;
          }
          else {
            *(int *)(*(int *)(this + 0x27d8) + 0xc) = iVar4;
          }
          *(undefined4 *)(this + 0x27dc) = *(undefined4 *)(iVar2 + 0x360);
          *(cRSubGame **)(iVar2 + 0x360) = this + 0x27d0;
          *(uint *)(this + 0x27d4) = *(uint *)(this + 0x27d4) & 0xfffffdff;
        }
        else {
          RShellError("List remove NEXTBOD");
        }
        *(undefined4 *)(this + 0x2844) = 0;
      }
      if ((*(uint *)(this + 0x287c) & 0x200) != 0) {
        iVar2 = *(int *)PTR__Game_001b60b8;
        if ((*(uint *)(this + 0x287c) & 0x200) == 0) {
          RShellError("List remove");
        }
        else if ((*(uint *)(this + 0x287c) & 0x40) == 0) {
          iVar4 = *(int *)(this + 0x2884);
          if (iVar4 != 0) {
            *(undefined4 *)(iVar4 + 8) = *(undefined4 *)(this + 0x2880);
          }
          if (*(int *)(this + 0x2880) == 0) {
            *(int *)(iVar2 + 0x35c) = iVar4;
          }
          else {
            *(int *)(*(int *)(this + 0x2880) + 0xc) = iVar4;
          }
          *(undefined4 *)(this + 0x2884) = *(undefined4 *)(iVar2 + 0x360);
          *(cRSubGame **)(iVar2 + 0x360) = this + 0x2878;
          *(uint *)(this + 0x287c) = *(uint *)(this + 0x287c) & 0xfffffdff;
        }
        else {
          RShellError("List remove NEXTBOD");
        }
        *(undefined4 *)(this + 0x28a4) = 0;
      }
      pcVar1 = this + 0x5e90;
      iVar2 = 0;
      do {
        iVar4 = iVar2;
        if ((*(uint *)pcVar1 & 0x200) != 0) {
          *(undefined4 *)(pcVar1 + 0x74) = 0;
          iVar2 = *(int *)PTR__Game_001b60b8;
          pcVar7 = this + iVar4 * 0xb8 + 0x5e8c;
          if ((*(uint *)(pcVar7 + 4) & 0x200) == 0) {
            RShellError("List remove");
          }
          else if ((*(uint *)(pcVar7 + 4) & 0x40) == 0) {
            iVar6 = *(int *)(pcVar7 + 0xc);
            if (iVar6 != 0) {
              *(undefined4 *)(iVar6 + 8) = *(undefined4 *)(pcVar7 + 8);
            }
            if (*(int *)(pcVar7 + 8) == 0) {
              *(int *)(iVar2 + 0x35c) = iVar6;
            }
            else {
              *(int *)(*(int *)(pcVar7 + 8) + 0xc) = iVar6;
            }
            *(undefined4 *)(pcVar7 + 0xc) = *(undefined4 *)(iVar2 + 0x360);
            *(cRSubGame **)(iVar2 + 0x360) = pcVar7;
            *(uint *)(pcVar7 + 4) = *(uint *)(pcVar7 + 4) & 0xfffffdff;
          }
          else {
            RShellError("List remove NEXTBOD");
          }
        }
        pcVar1 = pcVar1 + 0xb8;
        iVar2 = iVar4 + 1;
      } while (iVar4 + 1 != 0x32);
      iVar4 = iVar4 + -0x31;
      pcVar1 = this + 0x2d34;
      do {
        if ((*(uint *)pcVar1 & 0x200) != 0) {
          *(undefined4 *)(pcVar1 + 0x70) = 0;
          iVar2 = *(int *)PTR__Game_001b60b8;
          pcVar7 = this + iVar4 * 0xe0 + 0x2d30;
          if ((*(uint *)(pcVar7 + 4) & 0x200) == 0) {
            RShellError("List remove");
          }
          else if ((*(uint *)(pcVar7 + 4) & 0x40) == 0) {
            iVar6 = *(int *)(pcVar7 + 0xc);
            if (iVar6 != 0) {
              *(undefined4 *)(iVar6 + 8) = *(undefined4 *)(pcVar7 + 8);
            }
            if (*(int *)(pcVar7 + 8) == 0) {
              *(int *)(iVar2 + 0x35c) = iVar6;
            }
            else {
              *(int *)(*(int *)(pcVar7 + 8) + 0xc) = iVar6;
            }
            *(undefined4 *)(pcVar7 + 0xc) = *(undefined4 *)(iVar2 + 0x360);
            *(cRSubGame **)(iVar2 + 0x360) = pcVar7;
            *(uint *)(pcVar7 + 4) = *(uint *)(pcVar7 + 4) & 0xfffffdff;
          }
          else {
            RShellError("List remove NEXTBOD");
          }
        }
        pcVar1 = pcVar1 + 0xe0;
        iVar4 = iVar4 + 1;
      } while (iVar4 != 0x10);
      if (*(int *)(this + 0x82f0) != 0) {
        iVar2 = *(int *)PTR__Game_001b60b8;
        if ((*(uint *)(this + 0x8280) & 0x200) == 0) {
          RShellError("List remove");
        }
        else if ((*(uint *)(this + 0x8280) & 0x40) == 0) {
          iVar4 = *(int *)(this + 0x8288);
          if (iVar4 != 0) {
            *(undefined4 *)(iVar4 + 8) = *(undefined4 *)(this + 0x8284);
          }
          if (*(int *)(this + 0x8284) == 0) {
            *(int *)(iVar2 + 0x35c) = iVar4;
          }
          else {
            *(int *)(*(int *)(this + 0x8284) + 0xc) = iVar4;
          }
          *(undefined4 *)(this + 0x8288) = *(undefined4 *)(iVar2 + 0x360);
          *(cRSubGame **)(iVar2 + 0x360) = this + 0x827c;
          *(uint *)(this + 0x8280) = *(uint *)(this + 0x8280) & 0xfffffdff;
        }
        else {
          RShellError("List remove NEXTBOD");
        }
      }
      *(undefined4 *)(this + 0x82f0) = 0;
      if (*(int *)(this + 0x849c) != 0) {
        iVar2 = *(int *)PTR__Game_001b60b8;
        if ((*(uint *)(this + 0x842c) & 0x200) == 0) {
          RShellError("List remove");
        }
        else if ((*(uint *)(this + 0x842c) & 0x40) == 0) {
          iVar4 = *(int *)(this + 0x8434);
          if (iVar4 != 0) {
            *(undefined4 *)(iVar4 + 8) = *(undefined4 *)(this + 0x8430);
          }
          if (*(int *)(this + 0x8430) == 0) {
            *(int *)(iVar2 + 0x35c) = iVar4;
          }
          else {
            *(int *)(*(int *)(this + 0x8430) + 0xc) = iVar4;
          }
          *(undefined4 *)(this + 0x8434) = *(undefined4 *)(iVar2 + 0x360);
          *(cRSubGame **)(iVar2 + 0x360) = this + 0x8428;
          *(uint *)(this + 0x842c) = *(uint *)(this + 0x842c) & 0xfffffdff;
        }
        else {
          RShellError("List remove NEXTBOD");
        }
      }
      *(undefined4 *)(this + 0x849c) = 0;
      if ((*(uint *)(this + 0xf44c) & 0x200) != 0) {
        iVar2 = *(int *)PTR__Game_001b60b8;
        if ((*(uint *)(this + 0xf44c) & 0x40) == 0) {
          iVar4 = *(int *)(this + 0xf454);
          if (iVar4 != 0) {
            *(undefined4 *)(iVar4 + 8) = *(undefined4 *)(this + 0xf450);
          }
          if (*(int *)(this + 0xf450) == 0) {
            *(int *)(iVar2 + 0x35c) = iVar4;
          }
          else {
            *(int *)(*(int *)(this + 0xf450) + 0xc) = iVar4;
          }
          *(undefined4 *)(this + 0xf454) = *(undefined4 *)(iVar2 + 0x360);
          *(cRSubGame **)(iVar2 + 0x360) = this + 0xf448;
          *(uint *)(this + 0xf44c) = *(uint *)(this + 0xf44c) & 0xfffffdff;
        }
        else {
          RShellError("List remove NEXTBOD");
        }
        iVar2 = *(int *)PTR__Game_001b60b8;
        if ((*(uint *)(this + 0x11c44) & 0x200) == 0) {
          RShellError("List remove");
        }
        else if ((*(uint *)(this + 0x11c44) & 0x40) == 0) {
          iVar4 = *(int *)(this + 0x11c4c);
          if (iVar4 != 0) {
            *(undefined4 *)(iVar4 + 8) = *(undefined4 *)(this + 0x11c48);
          }
          if (*(int *)(this + 0x11c48) == 0) {
            *(int *)(iVar2 + 0x35c) = iVar4;
          }
          else {
            *(int *)(*(int *)(this + 0x11c48) + 0xc) = iVar4;
          }
          *(undefined4 *)(this + 0x11c4c) = *(undefined4 *)(iVar2 + 0x360);
          *(cRSubGame **)(iVar2 + 0x360) = this + 0x11c40;
          *(uint *)(this + 0x11c44) = *(uint *)(this + 0x11c44) & 0xfffffdff;
        }
        else {
          RShellError("List remove NEXTBOD");
        }
        iVar2 = *(int *)PTR__Game_001b60b8;
        if ((*(uint *)(this + 77000) & 0x200) == 0) {
          RShellError("List remove");
        }
        else if ((*(uint *)(this + 77000) & 0x40) == 0) {
          iVar4 = *(int *)(this + 0x12cd0);
          if (iVar4 != 0) {
            *(undefined4 *)(iVar4 + 8) = *(undefined4 *)(this + 0x12ccc);
          }
          if (*(int *)(this + 0x12ccc) == 0) {
            *(int *)(iVar2 + 0x35c) = iVar4;
          }
          else {
            *(int *)(*(int *)(this + 0x12ccc) + 0xc) = iVar4;
          }
          *(undefined4 *)(this + 0x12cd0) = *(undefined4 *)(iVar2 + 0x360);
          *(cRSubGame **)(iVar2 + 0x360) = this + 0x12cc4;
          *(uint *)(this + 77000) = *(uint *)(this + 77000) & 0xfffffdff;
        }
        else {
          RShellError("List remove NEXTBOD");
        }
        iVar2 = *(int *)PTR__Game_001b60b8;
        if ((*(uint *)(this + 0x1220c) & 0x200) == 0) {
          RShellError("List remove");
        }
        else if ((*(uint *)(this + 0x1220c) & 0x40) == 0) {
          iVar4 = *(int *)(this + 0x12214);
          if (iVar4 != 0) {
            *(undefined4 *)(iVar4 + 8) = *(undefined4 *)(this + 0x12210);
          }
          if (*(int *)(this + 0x12210) == 0) {
            *(int *)(iVar2 + 0x35c) = iVar4;
          }
          else {
            *(int *)(*(int *)(this + 0x12210) + 0xc) = iVar4;
          }
          *(undefined4 *)(this + 0x12214) = *(undefined4 *)(iVar2 + 0x360);
          *(cRSubGame **)(iVar2 + 0x360) = this + 0x12208;
          *(uint *)(this + 0x1220c) = *(uint *)(this + 0x1220c) & 0xfffffdff;
        }
        else {
          RShellError("List remove NEXTBOD");
        }
        iVar2 = *(int *)PTR__Game_001b60b8;
        if ((*(uint *)(this + 0x125a0) & 0x200) == 0) {
          RShellError("List remove");
        }
        else if ((*(uint *)(this + 0x125a0) & 0x40) == 0) {
          iVar4 = *(int *)(this + 0x125a8);
          if (iVar4 != 0) {
            *(undefined4 *)(iVar4 + 8) = *(undefined4 *)(this + 0x125a4);
          }
          if (*(int *)(this + 0x125a4) == 0) {
            *(int *)(iVar2 + 0x35c) = iVar4;
          }
          else {
            *(int *)(*(int *)(this + 0x125a4) + 0xc) = iVar4;
          }
          *(undefined4 *)(this + 0x125a8) = *(undefined4 *)(iVar2 + 0x360);
          *(cRSubGame **)(iVar2 + 0x360) = this + 0x1259c;
          *(uint *)(this + 0x125a0) = *(uint *)(this + 0x125a0) & 0xfffffdff;
        }
        else {
          RShellError("List remove NEXTBOD");
        }
        iVar2 = *(int *)PTR__Game_001b60b8;
        if ((*(uint *)(this + 0x12934) & 0x200) == 0) {
          RShellError("List remove");
        }
        else if ((*(uint *)(this + 0x12934) & 0x40) == 0) {
          iVar4 = *(int *)(this + 0x1293c);
          if (iVar4 != 0) {
            *(undefined4 *)(iVar4 + 8) = *(undefined4 *)(this + 0x12938);
          }
          if (*(int *)(this + 0x12938) == 0) {
            *(int *)(iVar2 + 0x35c) = iVar4;
          }
          else {
            *(int *)(*(int *)(this + 0x12938) + 0xc) = iVar4;
          }
          *(undefined4 *)(this + 0x1293c) = *(undefined4 *)(iVar2 + 0x360);
          *(cRSubGame **)(iVar2 + 0x360) = this + 0x12930;
          *(uint *)(this + 0x12934) = *(uint *)(this + 0x12934) & 0xfffffdff;
        }
        else {
          RShellError("List remove NEXTBOD");
        }
        iVar2 = *(int *)PTR__Game_001b60b8;
        if ((*(uint *)(this + 0x1331c) & 0x200) == 0) {
          RShellError("List remove");
        }
        else if ((*(uint *)(this + 0x1331c) & 0x40) == 0) {
          iVar4 = *(int *)(this + 0x13324);
          if (iVar4 != 0) {
            *(undefined4 *)(iVar4 + 8) = *(undefined4 *)(this + 0x13320);
          }
          if (*(int *)(this + 0x13320) == 0) {
            *(int *)(iVar2 + 0x35c) = iVar4;
          }
          else {
            *(int *)(*(int *)(this + 0x13320) + 0xc) = iVar4;
          }
          *(undefined4 *)(this + 0x13324) = *(undefined4 *)(iVar2 + 0x360);
          *(cRSubGame **)(iVar2 + 0x360) = this + 0x13318;
          *(uint *)(this + 0x1331c) = *(uint *)(this + 0x1331c) & 0xfffffdff;
        }
        else {
          RShellError("List remove NEXTBOD");
        }
        *(undefined4 *)(this + 0xf844) = 0;
      }
      if (*(int *)(this + 0xfab0) == 1) {
        cRSubGolb::Kill((cRSubGolb *)(this + 0xf88c));
      }
      if (*(int *)(this + 0xfd78) == 1) {
        cRSubGolb::Kill((cRSubGolb *)(this + 0xfb54));
      }
      if (*(int *)(this + 0x10040) == 1) {
        cRSubGolb::Kill((cRSubGolb *)(this + 0xfe1c));
      }
      if (*(int *)(this + 0x10308) == 1) {
        cRSubGolb::Kill((cRSubGolb *)(this + 0x100e4));
      }
      if (*(int *)(this + 0x105d0) == 1) {
        cRSubGolb::Kill((cRSubGolb *)(this + 0x103ac));
      }
      if (*(int *)(this + 0x10898) == 1) {
        cRSubGolb::Kill((cRSubGolb *)(this + 0x10674));
        iVar2 = *(int *)(this + 0x10b60);
      }
      else {
        iVar2 = *(int *)(this + 0x10b60);
      }
      if (iVar2 == 1) {
        cRSubGolb::Kill((cRSubGolb *)(this + 0x1093c));
        iVar2 = *(int *)(this + 0x10e28);
      }
      else {
        iVar2 = *(int *)(this + 0x10e28);
      }
      if (iVar2 == 1) {
        cRSubGolb::Kill((cRSubGolb *)(this + 0x10c04));
        iVar2 = *(int *)(this + 0x110f0);
      }
      else {
        iVar2 = *(int *)(this + 0x110f0);
      }
      if (iVar2 == 1) {
        cRSubGolb::Kill((cRSubGolb *)(this + 0x10ecc));
        iVar2 = *(int *)(this + 0x113b8);
      }
      else {
        iVar2 = *(int *)(this + 0x113b8);
      }
      if (iVar2 == 1) {
        cRSubGolb::Kill((cRSubGolb *)(this + 0x11194));
        iVar2 = *(int *)(this + 0x11680);
      }
      else {
        iVar2 = *(int *)(this + 0x11680);
      }
      if (iVar2 == 1) {
        cRSubGolb::Kill((cRSubGolb *)(this + 0x1145c));
        iVar2 = *(int *)(this + 0x11948);
      }
      else {
        iVar2 = *(int *)(this + 0x11948);
      }
      if (iVar2 == 1) {
        cRSubGolb::Kill((cRSubGolb *)(this + 0x11724));
      }
      if ((*(uint *)(this + 0xf4e0) & 0x200) != 0) {
        iVar2 = *(int *)PTR__Game_001b60b8;
        if ((*(uint *)(this + 0xf4e0) & 0x40) == 0) {
          iVar4 = *(int *)(this + 0xf4e8);
          if (iVar4 != 0) {
            *(undefined4 *)(iVar4 + 8) = *(undefined4 *)(this + 0xf4e4);
          }
          if (*(int *)(this + 0xf4e4) == 0) {
            *(int *)(iVar2 + 0x35c) = iVar4;
          }
          else {
            *(int *)(*(int *)(this + 0xf4e4) + 0xc) = iVar4;
          }
          *(undefined4 *)(this + 0xf4e8) = *(undefined4 *)(iVar2 + 0x360);
          *(cRSubGame **)(iVar2 + 0x360) = this + 0xf4dc;
          *(uint *)(this + 0xf4e0) = *(uint *)(this + 0xf4e0) & 0xfffffdff;
        }
        else {
          RShellError("List remove NEXTBOD");
        }
        *(undefined4 *)(this + 0xf550) = 0;
      }
      if ((*(uint *)(this + 0xf37c) & 0x200) != 0) {
        iVar2 = *(int *)PTR__Game_001b60b8;
        if ((*(uint *)(this + 0xf37c) & 0x40) == 0) {
          iVar4 = *(int *)(this + 0xf384);
          if (iVar4 != 0) {
            *(undefined4 *)(iVar4 + 8) = *(undefined4 *)(this + 0xf380);
          }
          if (*(int *)(this + 0xf380) == 0) {
            *(int *)(iVar2 + 0x35c) = iVar4;
          }
          else {
            *(int *)(*(int *)(this + 0xf380) + 0xc) = iVar4;
          }
          *(undefined4 *)(this + 0xf384) = *(undefined4 *)(iVar2 + 0x360);
          *(cRSubGame **)(iVar2 + 0x360) = this + 0xf378;
          *(uint *)(this + 0xf37c) = *(uint *)(this + 0xf37c) & 0xfffffdff;
        }
        else {
          RShellError("List remove NEXTBOD");
        }
        iVar2 = *(int *)PTR__Game_001b60b8;
        if ((*(uint *)(this + 0xf3a8) & 0x200) == 0) {
          RShellError("List remove");
        }
        else if ((*(uint *)(this + 0xf3a8) & 0x40) == 0) {
          iVar4 = *(int *)(this + 0xf3b0);
          if (iVar4 != 0) {
            *(undefined4 *)(iVar4 + 8) = *(undefined4 *)(this + 0xf3ac);
          }
          if (*(int *)(this + 0xf3ac) == 0) {
            *(int *)(iVar2 + 0x35c) = iVar4;
          }
          else {
            *(int *)(*(int *)(this + 0xf3ac) + 0xc) = iVar4;
          }
          *(undefined4 *)(this + 0xf3b0) = *(undefined4 *)(iVar2 + 0x360);
          *(cRSubGame **)(iVar2 + 0x360) = this + 0xf3a4;
          *(uint *)(this + 0xf3a8) = *(uint *)(this + 0xf3a8) & 0xfffffdff;
        }
        else {
          RShellError("List remove NEXTBOD");
        }
      }
      cRSpriteManager::KillGame();
      return;
    }
  } while( true );
}
