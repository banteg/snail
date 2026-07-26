/*
 * mangled: _ZN8cRBorder2AIEv
 * demangled: cRBorder::AI()
 * address: 0003c410
 * size: 3252
 */

/* cRBorder::AI() */

void __thiscall cRBorder::AI(cRBorder *this)

{
  undefined *puVar1;
  char cVar2;
  char *pcVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  undefined4 uVar9;
  int iVar10;
  uint uVar11;
  undefined4 uVar12;
  bool bVar13;
  float fVar14;
  float fVar15;
  float fVar16;

  uVar6 = *(uint *)(this + 0x194);
  *(uint *)(this + 0x198) = uVar6;
  uVar7 = uVar6 & 0xfffdffff;
  *(uint *)(this + 0x194) = uVar7;
  if ((uVar6 & 0x100000) != 0) {
    *(float *)(this + 0x178) =
         (*(float *)(this + 0x22c) + *(float *)(this + 0x23c) * 0.1 + 4.0) - 12.0;
    *(float *)(this + 0x17c) = (*(float *)(this + 0x22c) + *(float *)(this + 0x23c) * 0.8) - 4.0;
    fVar15 = *(float *)(this + 0x230) + *(float *)(this + 0x240) * 0.5;
    *(float *)(this + 0x180) = fVar15 - 6.0;
    *(float *)(this + 0x184) = (fVar15 + 32.0) - 6.0;
  }
  *(float *)(this + 0x174) =
       *(float *)(this + 0x174) + (*(float *)(this + 0x170) - *(float *)(this + 0x174)) * 0.8;
  if (uVar7 == 0) {
    iVar4 = *(int *)PTR__Game_001b60b8;
    if ((*(uint *)(this + 4) & 0x200) == 0) {
      RShellError("List remove");
    }
    else if ((*(uint *)(this + 4) & 0x40) == 0) {
      iVar10 = *(int *)(this + 0xc);
      if (iVar10 != 0) {
        *(undefined4 *)(iVar10 + 8) = *(undefined4 *)(this + 8);
      }
      if (*(int *)(this + 8) == 0) {
        *(int *)(iVar4 + 0x35c) = iVar10;
      }
      else {
        *(int *)(*(int *)(this + 8) + 0xc) = iVar10;
      }
      *(undefined4 *)(this + 0xc) = *(undefined4 *)(iVar4 + 0x360);
      *(cRBorder **)(iVar4 + 0x360) = this;
      *(uint *)(this + 4) = *(uint *)(this + 4) & 0xfffffdff;
    }
    else {
      RShellError("List remove NEXTBOD");
    }
    if (*(int *)(this + 0x288) != 2) {
      if (*(int *)(this + 0x288) != 3) {
        return;
      }
      cRBorderManager::Kill((cRBorder *)(*(int *)PTR__Game_001b60b8 + 0xd14));
      *(undefined4 *)(this + 0x29c) = 0;
      *(undefined4 *)(this + 0x288) = 1;
      return;
    }
    *(undefined4 *)(this + 0x288) = 1;
    return;
  }
  if ((uVar6 & 0x200) != 0) {
    *(uint *)(this + 0x194) = uVar6 & 0xfffdfdff;
    iVar4 = *(int *)PTR__Game_001b60b8;
    if ((*(uint *)(this + 4) & 0x200) == 0) {
      RShellError("List remove");
    }
    else if ((*(uint *)(this + 4) & 0x40) == 0) {
      iVar10 = *(int *)(this + 0xc);
      if (iVar10 != 0) {
        *(undefined4 *)(iVar10 + 8) = *(undefined4 *)(this + 8);
      }
      if (*(int *)(this + 8) == 0) {
        *(int *)(iVar4 + 0x35c) = iVar10;
      }
      else {
        *(int *)(*(int *)(this + 8) + 0xc) = iVar10;
      }
      *(undefined4 *)(this + 0xc) = *(undefined4 *)(iVar4 + 0x360);
      *(cRBorder **)(iVar4 + 0x360) = this;
      *(uint *)(this + 4) = *(uint *)(this + 4) & 0xfffffdff;
    }
    else {
      RShellError("List remove NEXTBOD");
    }
    iVar4 = *(int *)(this + 0x288);
joined_r0x0003c5ec:
    if (iVar4 == 2) {
      *(undefined4 *)(this + 0x288) = 1;
    }
    else if (iVar4 == 3) {
      cRBorderManager::Kill((cRBorder *)(*(int *)PTR__Game_001b60b8 + 0xd14));
      *(undefined4 *)(this + 0x29c) = 0;
      *(undefined4 *)(this + 0x288) = 1;
    }
    *(undefined4 *)(this + 0x194) = 0;
    return;
  }
  if ((uVar6 & 0x400) == 0) {
    if ((uVar6 & 0x1000) != 0) {
      return;
    }
    if ((uVar6 & 0x8000) == 0) {
      uVar11 = uVar6;
      if ((uVar6 & 2) != 0) {
        uVar11 = 0x3f800000;
        *(undefined4 *)(this + 0x200) = 0x3f800000;
      }
      puVar1 = PTR__Game_001b60b8;
      if (((uVar6 & 0x80000) != 0) &&
         (iVar4 = cRMouse::IsActive((cRMouse *)(*(int *)PTR__Game_001b60b8 + 0x228)), iVar4 != 0)) {
        cVar2 = RShellInkey();
        uVar11 = *(uint *)(this + 0x188);
        if ((int)cVar2 == uVar11) {
          if (*(int *)(this + 0x288) == 2) {
LAB_0003d120:
            *(undefined4 *)(this + 0x288) = 1;
          }
          else if (*(int *)(this + 0x288) == 3) {
            cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
            *(undefined4 *)(this + 0x29c) = 0;
            goto LAB_0003d120;
          }
          uVar11 = *(uint *)(this + 0x194);
          if ((uVar11 & 0x1000000) == 0) {
            iVar4 = *(int *)PTR__Game_001b60b8;
            if (*(char *)(iVar4 + 0x43df8) == '\0') {
              if ((uVar11 & 0x40000000) != 0) {
                cRFade::Start((cRFade *)(iVar4 + 0x24),(_func_void *)0x0);
              }
              *(undefined1 *)(iVar4 + 0x43df8) = 1;
              *(cRBorder **)(iVar4 + 0x43e04) = this;
              *(undefined4 *)(iVar4 + 0x43dfc) = 0;
              *(undefined4 *)(iVar4 + 0x43e00) = 0x3daaaaab;
              uVar11 = 0x20;
              *(undefined4 *)(iVar4 + 0x43df4) = 0x20;
            }
          }
          else {
            *(uint *)(this + 0x194) = uVar11 | 0x20;
          }
        }
      }
      iVar4 = cRMouse::IsActive((cRMouse *)(*(int *)PTR__Game_001b60b8 + 0x228));
      if ((iVar4 != 0) || (uVar6 = *(uint *)(this + 0x194), (uVar6 & 8) != 0)) {
        iVar4 = MouseTest(this);
        if (iVar4 != 0) {
          uVar8 = *(uint *)(this + 0x194);
          uVar7 = uVar8 | 0x20000;
          uVar6 = uVar8 & 4;
          if (uVar6 != 0) {
            *(undefined4 *)(this + 0x200) = 0x3f800000;
            uVar11 = *(uint *)(this + 0x20c);
          }
          *(uint *)(this + 0x194) = uVar7;
          if (uVar6 != 0) {
            *(uint *)(this + 0x210) = uVar11;
          }
          if (((uVar8 & 2) == 0) && (uVar6 != 0)) {
            if ((uVar8 & 0x40000) == 0) {
              cRSound::Play((cRSound *)PTR__gRSound_001b61e0,9);
              uVar7 = *(uint *)(this + 0x194);
            }
            uVar7 = uVar7 | 2;
            *(uint *)(this + 0x194) = uVar7;
          }
          if ((((uVar7 & 0x10) != 0) &&
              (iVar4 = *(int *)PTR__Game_001b60b8, *(char *)(iVar4 + 0x43df8) == '\0')) &&
             ((*(uint *)(*(int *)(iVar4 + 0x224) + 0x30) & 0x4000) != 0)) {
            if ((uVar7 & 0x1000000) == 0) {
              if ((uVar7 & 0x40000000) != 0) {
                cRFade::Start((cRFade *)(iVar4 + 0x24),(_func_void *)0x0);
              }
              *(undefined1 *)(iVar4 + 0x43df8) = 1;
              *(cRBorder **)(iVar4 + 0x43e04) = this;
              *(undefined4 *)(iVar4 + 0x43dfc) = 0;
              *(undefined4 *)(iVar4 + 0x43e00) = 0x3daaaaab;
              *(undefined4 *)(iVar4 + 0x43df4) = 0x20;
              uVar7 = *(uint *)(this + 0x194);
            }
            else {
              uVar7 = uVar7 | 0x20;
              *(uint *)(this + 0x194) = uVar7;
            }
            if ((uVar7 & 0x800000) == 0) {
              cRSound::Play((cRSound *)PTR__gRSound_001b61e0,8);
            }
            if ((*(uint *)(this + 0x28c) & 0x20) == 0) {
              if (*(int *)(this + 0x288) == 2) {
                uVar7 = *(uint *)(this + 0x194);
                *(undefined4 *)(this + 0x288) = 1;
                goto LAB_0003c878;
              }
              if (*(int *)(this + 0x288) == 3) {
                cRBorderManager::Kill((cRBorder *)(*(int *)PTR__Game_001b60b8 + 0xd14));
                *(undefined4 *)(this + 0x29c) = 0;
                *(undefined4 *)(this + 0x288) = 1;
              }
            }
            uVar7 = *(uint *)(this + 0x194);
          }
LAB_0003c878:
          if (((uVar7 & 0x40) != 0) &&
             (iVar4 = *(int *)PTR__Game_001b60b8,
             (*(uint *)(*(int *)(iVar4 + 0x224) + 0x30) & 0x8000) != 0)) {
            if ((uVar7 & 0x1000000) == 0) {
              if (*(char *)(iVar4 + 0x43df8) == '\0') {
                if ((uVar7 & 0x40000000) != 0) {
                  cRFade::Start((cRFade *)(iVar4 + 0x24),(_func_void *)0x0);
                }
                *(undefined1 *)(iVar4 + 0x43df8) = 1;
                *(cRBorder **)(iVar4 + 0x43e04) = this;
                *(undefined4 *)(iVar4 + 0x43dfc) = 0;
                *(undefined4 *)(iVar4 + 0x43e00) = 0x3daaaaab;
                *(undefined4 *)(iVar4 + 0x43df4) = 0x80;
              }
            }
            else {
              *(uint *)(this + 0x194) = uVar7 | 0x80;
            }
            cRSound::Play((cRSound *)PTR__gRSound_001b61e0,8);
            if (*(int *)(this + 0x288) == 2) {
              *(undefined4 *)(this + 0x288) = 1;
            }
            else if (*(int *)(this + 0x288) == 3) {
              cRBorderManager::Kill((cRBorder *)(*(int *)PTR__Game_001b60b8 + 0xd14));
              uVar7 = *(uint *)(this + 0x194);
              *(undefined4 *)(this + 0x29c) = 0;
              *(undefined4 *)(this + 0x288) = 1;
              goto LAB_0003c934;
            }
            uVar7 = *(uint *)(this + 0x194);
          }
          goto LAB_0003c934;
        }
        uVar6 = *(uint *)(this + 0x194);
      }
      uVar7 = uVar6 & 0xffdfffff;
      *(uint *)(this + 0x194) = uVar7;
      if (((uVar6 & 0x2000) == 0) && ((uVar6 & 4) != 0)) {
        *(undefined4 *)(this + 0x200) = 0;
        *(undefined4 *)(this + 0x210) = *(undefined4 *)(this + 0x208);
      }
      bVar13 = (uVar6 & 4) != 0;
      if (bVar13) {
        uVar7 = uVar6 & 0xffdffffd;
      }
      *(undefined4 *)(this + 0x218) = 0;
      if (bVar13) {
        *(uint *)(this + 0x194) = uVar7;
      }
    }
    else {
      uVar7 = uVar6 & 0xfffdfffd;
      *(undefined4 *)(this + 0x218) = 0;
      *(uint *)(this + 0x194) = uVar7;
    }
  }
  else {
    fVar15 = *(float *)(this + 0x25c);
    *(float *)(this + 0x25c) = fVar15 + *(float *)(this + 0x260);
    if (1.0 < fVar15 + *(float *)(this + 0x260)) {
      iVar4 = *(int *)PTR__Game_001b60b8;
      if ((*(uint *)(this + 4) & 0x200) == 0) {
        RShellError("List remove");
      }
      else if ((*(uint *)(this + 4) & 0x40) == 0) {
        iVar10 = *(int *)(this + 0xc);
        if (iVar10 != 0) {
          *(undefined4 *)(iVar10 + 8) = *(undefined4 *)(this + 8);
        }
        if (*(int *)(this + 8) == 0) {
          *(int *)(iVar4 + 0x35c) = iVar10;
        }
        else {
          *(int *)(*(int *)(this + 8) + 0xc) = iVar10;
        }
        *(undefined4 *)(this + 0xc) = *(undefined4 *)(iVar4 + 0x360);
        *(cRBorder **)(iVar4 + 0x360) = this;
        *(uint *)(this + 4) = *(uint *)(this + 4) & 0xfffffdff;
      }
      else {
        RShellError("List remove NEXTBOD");
      }
      iVar4 = *(int *)(this + 0x288);
      goto joined_r0x0003c5ec;
    }
  }
LAB_0003c934:
  if ((uVar7 & 0x8000) != 0) {
    uVar7 = uVar7 & 0xffdfffff;
    *(undefined4 *)(this + 0x200) = 0;
    *(uint *)(this + 0x194) = uVar7;
    *(undefined4 *)(this + 0x210) = *(undefined4 *)(this + 0x208);
  }
  if ((uVar7 & 0x40000) == 0) {
    fVar15 = *(float *)(this + 0x218);
    *(float *)(this + 0x204) =
         *(float *)(this + 0x204) + (*(float *)(this + 0x200) - *(float *)(this + 0x204)) * 0.1;
    *(float *)(this + 0x214) =
         *(float *)(this + 0x214) + (*(float *)(this + 0x210) - *(float *)(this + 0x214)) * 0.1;
    fVar14 = *(float *)(this + 0x21c) + (fVar15 - *(float *)(this + 0x21c)) * 0.1;
    fVar16 = fVar15 - fVar14;
    *(float *)(this + 0x21c) = fVar14;
    if (fVar16 < 0.0) {
      bVar13 = -0.1 < fVar16;
    }
    else if (0.1 <= fVar16) {
      bVar13 = false;
    }
    else {
      bVar13 = true;
    }
    if (bVar13) {
      *(float *)(this + 0x21c) = fVar15;
    }
  }
  else {
    *(uint *)(this + 0x194) = uVar7 & 0xfffbffff;
    *(undefined4 *)(this + 0x204) = *(undefined4 *)(this + 0x200);
    *(undefined4 *)(this + 0x214) = *(undefined4 *)(this + 0x210);
    *(undefined4 *)(this + 0x21c) = *(undefined4 *)(this + 0x218);
  }
  puVar1 = PTR__Game_001b60b8;
  if ((((*(uint *)(this + 0x194) & 0x2000) != 0) &&
      (iVar4 = cRMouse::IsActive((cRMouse *)(*(int *)PTR__Game_001b60b8 + 0x228)), iVar4 != 0)) &&
     (InputText(this), (*(uint *)(this + 0x194) & 0x2000) == 0)) {
    pcVar3 = section_0000158c.segname + *(int *)puVar1;
    iVar4 = 0;
    do {
      uVar7 = *(uint *)(pcVar3 + -0x7c);
      iVar4 = iVar4 + 1;
      if (-1 < (int)uVar7) {
        uVar7 = uVar7 & 0xffff7fff;
        *(uint *)(pcVar3 + -0x7c) = uVar7;
      }
      *(uint *)(pcVar3 + -0x7c) = uVar7 & 0x7fffffff;
      *(undefined4 *)pcVar3 = *(undefined4 *)(pcVar3 + -8);
      *(undefined4 *)(pcVar3 + 4) = *(undefined4 *)(pcVar3 + -8);
      pcVar3[-0xffffffff00000010] = '\0';
      pcVar3[-0xffffffff0000000f] = '\0';
      pcVar3[-0xffffffff0000000e] = '\0';
      pcVar3[-0xffffffff0000000d] = '\0';
      pcVar3 = pcVar3 + 0x71c;
    } while (iVar4 != 0x96);
  }
  if ((*(int *)(this + 0x164) == 1) && (0 < *(int *)(this + 0x168))) {
    iVar4 = 0;
    do {
      cRTwinkle::AI((cRTwinkle *)(this + iVar4 * 0x30 + 0x74));
      iVar4 = iVar4 + 1;
    } while (iVar4 < *(int *)(this + 0x168));
  }
  cRToolTip::AI((cRToolTip *)(this + 0x284));
  uVar6 = *(uint *)(this + 0x194);
  RePosition(this);
  uVar7 = *(uint *)(this + 0x194);
  if ((uVar7 & 0x1000) == 0) {
    fVar15 = *(float *)(this + 0x204);
    fVar16 = 1.0;
    fVar14 = 1.0 - fVar15;
    tColour::Set((tColour *)(this + 0x1a0),
                 fVar15 * *(float *)(this + 0x1c0) + fVar14 * *(float *)(this + 0x1b0),
                 fVar15 * *(float *)(this + 0x1c4) + fVar14 * *(float *)(this + 0x1b4),
                 fVar15 * *(float *)(this + 0x1c8) + fVar14 * *(float *)(this + 0x1b8),
                 fVar15 * *(float *)(this + 0x1cc) + fVar14 * *(float *)(this + 0x1bc));
    fVar15 = *(float *)(this + 0x204);
    fVar16 = fVar16 - fVar15;
    tColour::Set((tColour *)(this + 0x1d0),
                 fVar15 * *(float *)(this + 0x1f0) + fVar16 * *(float *)(this + 0x1e0),
                 fVar15 * *(float *)(this + 500) + fVar16 * *(float *)(this + 0x1e4),
                 fVar15 * *(float *)(this + 0x1f8) + fVar16 * *(float *)(this + 0x1e8),
                 fVar15 * *(float *)(this + 0x1fc) + fVar16 * *(float *)(this + 0x1ec));
    uVar7 = *(uint *)(this + 0x194);
    if ((uVar7 & 0x8000) != 0) {
      *(float *)(this + 0x1d0) = *(float *)(this + 0x1d0) * 0.5;
      *(float *)(this + 0x1d4) = *(float *)(this + 0x1d4) * 0.5;
      *(float *)(this + 0x1d8) = *(float *)(this + 0x1d8) * 0.5;
      *(float *)(this + 0x1dc) = *(float *)(this + 0x1dc) * 0.5;
      *(float *)(this + 0x1a0) = *(float *)(this + 0x1a0) * 0.5;
      *(float *)(this + 0x1a4) = *(float *)(this + 0x1a4) * 0.5;
      *(float *)(this + 0x1a8) = *(float *)(this + 0x1a8) * 0.5;
      *(float *)(this + 0x1ac) = *(float *)(this + 0x1ac) * 0.5;
    }
    if ((uVar7 & 0x800) == 0) {
      if ((uVar7 & 0x10000) == 0) {
        FontType(this + 0x2c4,*(undefined4 *)(this + 0x6e4),*(undefined4 *)(this + 0x6e8),
                 *(undefined4 *)(this + 0x6ec),*(undefined4 *)(this + 0x6f0),this + 0x22c,
                 this + 0x230,this + 0x23c,this + 0x240,*(undefined4 *)(this + 0x21c),
                 *(uint *)(PTR__gConfig_001b60d4 + 0x1c) >> 8 & 1,*(undefined4 *)(this + 0x254),
                 *(undefined4 *)(this + 600),0x1000000,*(undefined4 *)(this + 0x1d0),
                 *(undefined4 *)(this + 0x1d4),*(undefined4 *)(this + 0x1d8),
                 *(undefined4 *)(this + 0x1dc),0,uVar6 >> 8 & 1);
        fVar14 = *(float *)(this + 0x22c) + *(float *)(this + 0x23c) * -0.05;
        fVar15 = *(float *)(this + 0x23c) * 1.1;
        *(float *)(this + 0x22c) = fVar14;
        *(float *)(this + 0x23c) = fVar15;
        if ((*(uint *)(this + 0x194) & 0x100000) != 0) {
          *(undefined4 *)(this + 0x23c) = 0x43c80000;
          *(float *)(this + 0x22c) = fVar14 + fVar15 * 0.5 + -200.0;
          *(float *)(this + 0x240) = *(float *)(this + 0x240) + 50.0;
        }
        if (*(float *)(this + 0x244) != 0.0) {
          *(float *)(this + 0x23c) = *(float *)(this + 0x244);
        }
      }
      else {
        *(undefined4 *)(this + 0x22c) = *(undefined4 *)(this + 0x40);
        *(undefined4 *)(this + 0x230) = *(undefined4 *)(this + 0x44);
        *(undefined4 *)(this + 0x23c) = *(undefined4 *)(this + 0x48);
        *(undefined4 *)(this + 0x240) = *(undefined4 *)(this + 0x4c);
      }
    }
    Draw(this);
    uVar7 = *(uint *)(this + 0x194);
  }
  if (*(int *)(this + 0x270) != 0) {
    *(int *)(this + 0x270) = *(int *)(this + 0x270) + -1;
  }
  puVar1 = PTR__Game_001b60b8;
  *(undefined4 *)(this + 0x274) = *(undefined4 *)(*(int *)PTR__Game_001b60b8 + 0x234);
  *(undefined4 *)(this + 0x278) = *(undefined4 *)(*(int *)puVar1 + 0x238);
  if ((uVar7 & 0x100000) == 0) {
    return;
  }
  iVar4 = *(int *)(this + 0x714);
  if ((*(uint *)(iVar4 + 0x194) & 0x20) == 0) {
    fVar15 = *(float *)(this + 0x170);
  }
  else {
    fVar15 = *(float *)(this + 0x170);
    *(uint *)(iVar4 + 0x194) = *(uint *)(iVar4 + 0x194) & 0xffffffdf;
    fVar15 = fVar15 + 0.2;
    *(float *)(this + 0x170) = fVar15;
    if (0.9 <= fVar15) {
      fVar15 = 1.0;
      *(undefined4 *)(this + 0x170) = 0x3f800000;
    }
  }
  iVar10 = *(int *)(this + 0x710);
  if ((*(uint *)(iVar10 + 0x194) & 0x20) == 0) {
LAB_0003caf0:
    if (fVar15 != 0.0) {
      *(uint *)(iVar10 + 0x194) = *(uint *)(iVar10 + 0x194) & 0xffff7fff;
      goto LAB_0003ca78;
    }
  }
  else {
    *(uint *)(iVar10 + 0x194) = *(uint *)(iVar10 + 0x194) & 0xffffffdf;
    fVar15 = fVar15 - 0.2;
    *(float *)(this + 0x170) = fVar15;
    if (0.1 < fVar15) goto LAB_0003caf0;
    fVar15 = 0.0;
    *(undefined4 *)(this + 0x170) = 0;
  }
  *(uint *)(iVar10 + 0x194) = *(uint *)(iVar10 + 0x194) | 0x8000;
LAB_0003ca78:
  iVar10 = *(int *)(this + 0x718);
  if (fVar15 == 1.0) {
    *(uint *)(iVar4 + 0x194) = *(uint *)(iVar4 + 0x194) | 0x8000;
  }
  else {
    *(uint *)(iVar4 + 0x194) = *(uint *)(iVar4 + 0x194) & 0xffff7fff;
  }
  uVar5 = *(undefined4 *)(this + 0x1d4);
  uVar9 = *(undefined4 *)(this + 0x1d8);
  uVar12 = *(undefined4 *)(this + 0x1dc);
  *(undefined4 *)(iVar10 + 0x1d0) = *(undefined4 *)(this + 0x1d0);
  *(undefined4 *)(iVar10 + 0x1d4) = uVar5;
  *(undefined4 *)(iVar10 + 0x1d8) = uVar9;
  *(undefined4 *)(iVar10 + 0x1dc) = uVar12;
  uVar5 = *(undefined4 *)(this + 0x200);
  *(undefined4 *)(iVar10 + 0x204) = *(undefined4 *)(this + 0x204);
  *(undefined4 *)(iVar10 + 0x200) = uVar5;
  _sprintf((char *)(iVar10 + 0x2c4),"%02i%%",(int)(fVar15 * 100.0 + 0.1));
  return;
}
